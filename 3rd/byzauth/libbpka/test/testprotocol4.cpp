#include "messageprocessor.h" 
#include "byzantineauthenticationadapter.h" 
#include <map>
#include <set>
#include <vector> 
#include <string>
#include <iostream>
#include <cstring>
#include <cstdio>

#include <sys/stat.h>
#include <sys/types.h>
#include <zlib.h> 
#include <sys/time.h>





float get_milli_seconds(struct timeval & start, struct timeval & end) 
{
   return 1000.0 * ( end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec)/1000000.0 ) ;
}

#define  MAX_NAME  1024
#define  KEYBITS   128
     /**
      * Program takes in an email trace to simulate the progress of 
      * byzantine fault tolerant authentication on the work load 
      *
      * Format of the email trace file:
      *     timeofmail  sizeofmail  mesgid   fromwho  towho ccwho ... \n
      *
      * Logic 
      * Compute all senders and receivers and make an adapter for each.  
      * Load all the messages into sequence by time. 
      * Execute the work load in a synchronous manner using the 
      * receive call at end of every call 
      */


int linebufsize = 64*1024; 

char * linebuf = new char [linebufsize]; 

unsigned int mintime = 0xffffffff;

struct MessageTrace 
{  
   std::string    from; 
   std::vector<std::string>   to; 
   unsigned       date; 
   unsigned       size; 
}; 

std::set<std::string>  peers; 

std::map<unsigned, MessageTrace>    message_trace; 

std::map<std::string, std::vector<std::string> > trustgroups; 

std::map<std::string, ByzantineAuthenticationAdapter *> peer_map;

void transmit_outstanding_messages();



std::string trim(std::string who) 
{
   char name[MAX_NAME]; 
   strcpy( name, who.c_str() ) ; 
   
   int len = who.size();
   for( int i = 0; i < len; i++ ) 
      if( isupper(name[i]) )
         name[i] = tolower(name[i]) ;
   return name; 
}   





int get_compr_size(const std::string& mesg)
{  
   uLongf destLen = (mesg.size() + 12) + (mesg.size()/4); 
   Bytef *dest = new Bytef[destLen]; 
   const Bytef *source = (Bytef *) mesg.data(); 
   uLong sourceLen = mesg.size(); 
   int ret = 0; 
   if( Z_OK != (ret = compress(dest, &destLen, source, sourceLen)))
   {
      std::cerr << "Error in compress " << ret << std::endl; 
      abort() ; 
   }
   delete [] dest; 
   return destLen*3/2;  // for base 64 encoding 
}






bool  load_trace(char * filename) 
{
   FILE * fp = fopen(filename, "r");
   if(!fp)
      return false; 

   std::map<std::string, int> woutcount; 
   std::map<std::string, int> outcount; 
   std::map<std::string, int> incount; 

   const char * tb = " \t\n" ; 
   while(fgets(linebuf, linebufsize, fp))
   {
      char * p = 0; 
      MessageTrace curr;  
      for( int tn = 0; 1; tn++)
      {
         if(!tn)
            p = strtok( linebuf , tb )  ; 
         else
            p = strtok( 0, tb ) ; 
         if(!p)   
            break; 
         switch(tn)
         {
            case 0: curr.date = atoi(p); 
               if (mintime > curr.date)
                  mintime = curr.date; 
               break; 

            case 1: curr.size = atoi(p); 
               break; 

            case 2: break; 

            case 3: curr.from = trim(p); 
               peers.insert(curr.from); 
               break; 

            default:
               curr.to.push_back(trim(p));
               peers.insert(trim(p)); 
               break; 
         }
      }
      message_trace.insert(std::make_pair(curr.date, curr)); 
      outcount[ curr.from ] ++ ; 
      for( std::vector<std::string>::iterator i = curr.to.begin() ; i != curr.to.end() ; i++) 
         incount[ *i ] ++ ; 
      woutcount[curr.from] +=  curr.to.size(); 
   }
   return true; 
}





      
            
         
      
int main(int argc, char * argv[]) 
{
   if( argc != 7 ) 
   {
      std::cout << "Usage " << argv[0] << " <bsfile> <msgtrace> <tgs> <expiryinterval> <nmespayload> <keysz> " << std::endl;  
      return 1; 
   }

   int tgs = atoi(argv[3]); 
   int expiry = atoi(argv[4]); 
   int payload = atoi(argv[5]); 
   int keysize = atoi(argv[6]); 
   
        // load all the traces 
   for( int i = 2; i < argc; i++ )
      load_trace( argv[i] ) ; 


        // load trusted group information
   FILE * bfp = fopen( argv[1] , "r" ) ;
   while( fgets( linebuf, linebufsize, bfp ) ) 
   {
      char * p = strtok( linebuf, " \t\n" ) ; 
      if(p && peers.find(p) != peers.end())
      {
         std::string self = p; 
         int count = 0; 
         while( (p = strtok( 0, " \t\n" )) &&  peers.find(p) != peers.end() && count < atoi(argv[3]) )
         {
            count++; 
            trustgroups[self].push_back(std::string(p)); 
         }

         if(count < 4) 
            trustgroups.erase(self); 
      }
   }
   std::cout << "loaded trust groups" << std::endl ; 



        // erased peers who have no trust groups
   for( std::set<std::string>::iterator i = peers.begin() ; i != peers.end() ; ) 
   {
      std::set<std::string>::iterator j = i; 
      j++; 
      if( trustgroups.find(*i) == trustgroups.end() )
         peers.erase(*i); 
      i = j; 
   }
   std::cout << "trimmed messages in trace " << peers.size() << " peers left " << std::endl ; 



        // initialize all adapters 
   mkdir( "./peerdata", 0770 ) ; 
   system( "rm -rf peerdata/*" ) ; 

   for( std::set<std::string>::iterator i = peers.begin() ; i != peers.end() ; i++ ) 
   {
      ByzantineAuthenticationAdapter * adapter = 
         ByzantineAuthenticationAdapter::New( "example.conf" , 
                                              atoi(argv[3]),      // trusted group size
                                              atoi(argv[4]),      // expiry interval in seconds
                                              atoi(argv[5]));     // maximum message payload i.e. how many messages to attach on outgoing


      std::string filename = *i + ".xml";
      filename = "./peerdata/" + filename;  
      peerid_t me = *i; 

      if(!adapter->Init(atoi(argv[6]), me, trustgroups[*i], filename.c_str(), mintime))
         return false; 

      peer_map.insert( std::make_pair( *i, adapter ) ) ; 
   }
   std::cout << "initialize all adapters" << std::endl ;


   float totalsendtime; 

        // run the trace
   char filename[1024]; 
   sprintf( filename, "tgs%d.expiry%d.payload%d.data", tgs, expiry, payload ) ; 

   FILE * statfp = fopen( filename, "w" ) ; 
   int done = 0, max = message_trace.size(); 
   int percent, prevpercent = 0; 
   for( std::map<unsigned, MessageTrace>::iterator i = message_trace.begin(); 
        i != message_trace.end() ; i++ ) 
   {
      done++; 
      percent = int( 100.0*done/max ) ; 
      if( percent != prevpercent ) 
      {
         std::cout << percent << " % done " << std::endl;
         prevpercent = percent; 
      }
      std::cout << done << " of " << max << " done\r" << std::flush ; 

      if( peer_map.find(i->second.from) == peer_map.end() ) 
         continue; 

           // the sender
      ByzantineAuthenticationAdapter * pfrom = peer_map[i->second.from];
      pfrom->LocalTime (i->second.date) ;

           // gather message
      std::string mesg;
      std::vector<std::string> outgoingtrimmed; 
      for( std::vector<std::string>::iterator j = i->second.to.begin(); j != i->second.to.end(); j++ ) 
         if( peer_map.find(*j) != peer_map.end() ) 
            outgoingtrimmed.push_back(*j) ; 

      if(outgoingtrimmed.empty())
         continue; 
  
      float sendtime, comprtime, recvtime;  
      struct timeval start, end;
      gettimeofday(&start , 0);
      pfrom->SendMulti( outgoingtrimmed, mesg ) ;  // many send
      gettimeofday(&end , 0);
      totalsendtime += (sendtime = get_milli_seconds(start, end)); 

      gettimeofday(&start , 0);
      int overhead = get_compr_size(mesg); 
      gettimeofday(&end , 0);
      comprtime = get_milli_seconds(start, end); 

      unsigned int ntrusted, nknown; 
      float completion = pfrom->GetCompletion(ntrusted, nknown) ; 
      unsigned nmessages, nbytes; 
      pfrom->GetCacheSize(nmessages, nbytes); 
      fprintf( statfp, "SENDER=%s  TIME=%lu  NUMDEST=%lu OVERHEAD=%d  BASEOVERHEAD=%lu SIZE=%lu  COMPLETION=%f NTRUSTED=%u NKNOWN=%u CACHENMESG=%u CACHENBYTES=%u SNDTIME=%f COMPRTIME=%f KEYSZ=%d\n" , 
               i->second.from.c_str(), 
               (unsigned long) i->second.date, 
               (unsigned long) outgoingtrimmed.size(), 
               overhead, 
               (unsigned long)mesg.size(), 
               (unsigned long)i->second.size, completion, ntrusted, nknown , nmessages, nbytes, sendtime, comprtime, keysize ) ; 

           // send to each receiver
      for( std::vector<std::string>::iterator j = i->second.to.begin(); j != i->second.to.end(); j++ ) 
      {
         std::string pubkey; 
         bool unknown; 
         int trust_value; 

         if( peer_map.find(*j) == peer_map.end() ) 
            continue; 

              // already doing inside 
         pfrom->GetAuthenticatedKey(*j, pubkey, trust_value, unknown); 
       
         ByzantineAuthenticationAdapter * pto = peer_map[*j]; 
         pto->LocalTime(i->second.date) ; 
         gettimeofday(&start , 0);
         pto->Recv( i->second.from, mesg ) ;
         gettimeofday(&end , 0);
         recvtime = get_milli_seconds(start, end); 
      } 
   }

        // de init all adapters
   for( std::map<std::string, ByzantineAuthenticationAdapter *>::iterator i = peer_map.begin(); 
        i != peer_map.end(); i++ ) 
   {
      i->second->DeInit(); 
      ByzantineAuthenticationAdapter::Delete(i->second) ; 
   }

   fclose(statfp);
   return 0;
}

                




