#include "messagecache.h" 
#include "logger.h"
#include <sstream>
#include <fstream>
#include <cstdio>
#include <map>
#include <queue>
#include <iostream>


int log(cached_mesgmap_t& cache)
{
   for( cached_mesgmap_t::iterator i = cache.begin(); i != cache.end(); i++ )
   {
      CacheRecord & record = i->second; 
      std::cout << 
         "LamportTime=" << record.lamport_time.timestamp << "\t" << 
         "CausalTime=" << record.causal_time.timestamp << "\t" << 
         "StableTime=" << record.stable_read.timestamp << "\t" << 
         "Source=" << record.source << "\t" <<          
         "Destination=" << record.destination << "\t" << std::endl ; 
   }

   return 0;
}

int sum(cached_mesgmap_t& cache)
{
   std::map<std::string, int> totcount; 
   for( cached_mesgmap_t::iterator i = cache.begin(); i != cache.end(); i++ )
   {
      if( totcount.find(i->second.source) == totcount.end() )
         totcount[i->second.source] = 0; 
      totcount[i->second.source]++; 
   }

   
   for( std::map<std::string, int>::iterator i = totcount.begin(); i != totcount.end(); i++ )
      std::cout << i->first << "\t" << i->second << std::endl ; 

   return 0; 
}



int main(int argc, char * argv[]) 
{
   if( argc == 1 ) 
   {
      std::cout << "Usage : " << argv[0] << " <cachefilename> <format=1|2>" << std::endl ; 
      exit(1); 
   }


   int reporttype = atoi(argv[2]); 

   cached_mesgmap_t cache;

   std::ifstream ifs(argv[1]);
   if(!ifs.good())
      return -1; 
   boost::archive::xml_iarchive ia(ifs);
   ia >> BOOST_SERIALIZATION_NVP(cache); 


   switch(reporttype) 
   {
      case 1: return log(cache); 
      case 2: return sum(cache); 
      default :
         std::cerr << "Unknown reporttype" << std::endl ; 
   }
}


