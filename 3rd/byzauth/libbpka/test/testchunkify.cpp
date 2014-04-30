#include "chunkifier.h" 
#include <iostream>



int main() 
{
   UBigNum modn; 
   modn.random(1024); 

   Chunkifier cc; 
   cc.init(modn); 
 
   char line[1024]; 
   while( fgets( line, 1024, stdin ) ) 
   {
      if( line[strlen(line)-1] == '\n' ) 
         line[strlen(line)-1] = 0; 

      std::string s = line; 
      
      std::vector<UBigNum> vbn; 
      cc.chunkify( s, vbn ) ; 

      std::vector<UBigNum>::iterator i = vbn.begin();
      while( i != vbn.end() )
      { 
         std::cout << i->print(10) << std::endl ;  
         i++;
      }

      std::string t; 
      cc.dechunkify(vbn, t); 

      std::cout << s << std::endl ; 
   }
}



