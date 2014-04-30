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
#include <zlib.h> 
#include <sys/time.h>


#define  MAX_NAME  1024
#define  KEYBITS   128
     /**
      * Check if the lazy protocol can restart from a saved state 
      */ 


int main(int argc, char * argv[]) 
{
   if( argc != 5 ) 
   {
      std::cout << "Usage " << argv[0] << " <reloadfile> <tgs> <expiryinterval> <nmespayload>" << std::endl;  
      return 1; 
   }

   const char * filename = argv[1]; 
   int tgs = atoi(argv[2]); 
   int expiry = atoi(argv[3]); 
   int payload = atoi(argv[4]); 

   
   ByzantineAuthenticationAdapter * adapter = 
      ByzantineAuthenticationAdapter::New( "example.conf" , tgs, expiry, payload ) ; 

   adapter->Init( filename, time(0) ) ; 


   adapter->DeInit() ; 

   ByzantineAuthenticationAdapter::Delete(adapter) ;

   return 0;
}

                




