/* 
 * test if the initialization and destruction is algrind clean 
 */ 


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



int main() 
{
   std::cout << "IN MAIN" << std::endl; 


   ByzantineAuthenticationAdapter * adapter = 
      ByzantineAuthenticationAdapter::New( "example.conf" ,    // info for logging dir etc. 
                                           8 ,                 // trusted group size
                                           1000000,            // expiry interval  
                                           300 ) ;             // max payload


        // there was an un init problem caused by lack of ini 
        // on time. does this solve the bug?
   adapter->LocalTime(0) ;
   adapter->LocalTime(10) ;
   adapter->LocalTime(20) ;


   peerid_t myid = "testid" ; 
   std::string filename = "./peerdata/" + myid + ".xml";

   std::vector<peerid_t> tgs(10);
   for( int i = 0; i < 10; i++ )
   {
      char name[16];
      sprintf( name, "peer%d" , i ) ;
      tgs[i] = name ; 
   }

   if(!adapter->Init( 256 , myid, tgs, filename.c_str(), 40))
   {
      std::cerr << "can not init" << std::endl;  
      return false; 
   }

   adapter->DeInit(); 
   ByzantineAuthenticationAdapter::Delete(adapter); 

}
