#include "messageprocessor.h" 
#include "byzantineauthenticationadapter.h" 
#include <map>
#include <set>
#include <vector> 
#include <string>
#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>

#define  MAX_NAME  1024

     /**
      * Program takes in an email trace to simulate the progress of 
      * byzantine fault tolerant authentication on the work load 
      *
      * Format of the email trace file:
      *     timeofmail  sizeofmail fromwho towho ccwho ... \n
      *
      * Logic 
      * Compute all senders and receivers and make an adapter for each.  
      * Load all the messages into sequence by time. 
      * Execute the work load 
      */


int linebufsize = 64*1024; 

char * linebuf = new char [linebufsize]; 

struct MessageTrace 
{  
   std::string    from; 
   std::vector<std::string>   to; 
   unsigned       date; 
   unsigned       size; 
}; 

std::set<std::string>  peers; 

std::multimap<std::string, std::string>  domain_map; 

std::map<unsigned, MessageTrace>    message_trace; 



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



bool  add_peer(std::string who) 
{
   if( peers.find(who) != peers.end() ) 
      return true; 

   std::string::size_type at = who.find('@'); 
   if( at == std::string::npos ) 
      return false; 

   std::string domain; 
   domain.assign(who, at + 1, who.size() - at - 1); 
   domain_map.insert( make_pair(domain, who) ) ; 
   peers.insert(who); 
   return true; 
}





bool  load_trace(char * filename) 
{
   FILE * fp = fopen(filename, "r");
   if(!fp)
      return false; 

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
               break; 
            case 1: curr.size = atoi(p); 
               break; 
            case 2: curr.from = trim(p); 
               add_peer(curr.from);
               break; 
            default:
               curr.to.push_back(trim(p));
               add_peer(trim(p));
               break; 
         }
      }
      message_trace.insert(std::make_pair(curr.date, curr)); 
   }
   return true; 
}
      
            
         
      
int main(int argc, char * argv[]) 
{
   for( int i = 1; i < argc; i++ )
      load_trace( argv[i] ) ; 

   std::map<std::string, std::vector<std::string> > trustgroups; 
   std::map<std::string, ByzantineAuthenticationAdapter *> peer_map;

   for( std::multimap<std::string, std::string>::iterator i=domain_map.begin();
        i != domain_map.end() ; )
   {
      std::multimap<std::string, std::string>::iterator j = i ; 
      std::vector<std::string> trustgroup; 
      while( j != domain_map.end() && j->first == i->first ) 
      {
         trustgroup.push_back(j->second) ;
         j++; 
      }
      
      j = i; 
      while( j != domain_map.end() && j->first == i->first ) 
      {
         trustgroups[j->second] = trustgroup; 
         j++;
      }
      i = j; 
   } 

        // initialize all adapters 
   mkdir( "./peerdata", 0770 ) ; 
   for( std::set<std::string>::iterator i = peers.begin() ; i != peers.end() ; i++ ) 
   {
      ByzantineAuthenticationAdapter * adapter = ByzantineAuthenticationAdapter::New() ; 

      std::string filename = *i + ".xml";
      filename = "./peerdata/" + filename;  
      peerid_t me = *i; 
      if(!adapter->Init(256, me, trustgroups[*i], filename.c_str()))
         return false; 

      peer_map.insert( std::make_pair( *i, adapter ) ) ; 
   }


   for( std::map<std::string, ByzantineAuthenticationAdapter *>::iterator i = peer_map.begin(); 
        i != peer_map.end(); i++ ) 
      i->second->Debug(); 
   int mcount = 0; 

   for( std::map<unsigned, MessageTrace>::iterator i = message_trace.begin(); 
        i != message_trace.end() ; i++ ) 
   {
      ByzantineAuthenticationAdapter * pfrom = peer_map[i->second.from];
      
      for( std::vector<std::string>::iterator j = i->second.to.begin(); j != i->second.to.end(); j++ ) 
      {
         std::string pubkey; 
         bool unknown; 
         int trust_value; 
         pfrom->GetAuthenticatedKey(*j, pubkey, trust_value, unknown); 
         ByzantineAuthenticationAdapter * pto = peer_map[*j]; 
         
         std::string mesg;
         while( pfrom->Send( *j, mesg ) )
         {
            mcount++; 
            pto->Recv( i->second.from, mesg ) ; 
            pto->Debug(); 
         }
      } 
   }



   for( std::map<std::string, ByzantineAuthenticationAdapter *>::iterator i = peer_map.begin(); 
        i != peer_map.end(); i++ ) 
      i->second->Debug(); 



        // any outstanding messages must be completed 
   while(1)  
   {
      bool sent = false; 
      for( std::map<unsigned, MessageTrace>::iterator i = message_trace.begin(); 
           i != message_trace.end() ; i++ ) 
      {
         ByzantineAuthenticationAdapter * pfrom = peer_map[i->second.from];
         for( std::vector<std::string>::iterator j = i->second.to.begin(); j != i->second.to.end(); j++ ) 
         {  
            ByzantineAuthenticationAdapter * pto = peer_map[*j]; 
            std::string mesg;
            while( pfrom->Send( *j, mesg ) )
            {
               pto->Recv( i->second.from, mesg ) ; 
               sent = true; 
            }
         }
      }
      if(!sent) 
         break; 
   }

      
   for( std::map<std::string, ByzantineAuthenticationAdapter *>::iterator i = peer_map.begin(); 
        i != peer_map.end(); i++ ) 
      i->second->Debug(); 



        // de init all adapters
   for( std::map<std::string, ByzantineAuthenticationAdapter *>::iterator i = peer_map.begin(); 
        i != peer_map.end(); i++ ) 
   {
      i->second->DeInit(); 
      delete i->second; 
   }

   exit(0);
}

                
