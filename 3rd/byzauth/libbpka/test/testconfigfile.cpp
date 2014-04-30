#include "configfile.h" 
#include <string> 
#include <iostream> 

using namespace std; 


char * testconf = "test.conf" ; 
int main() 
{
   ConfigFile cfg; 
   if(!cfg.Init(testconf))
      std::cout << "cannot init " << endl ; 
   
   string sval = "default" ; 
//   long lval = 33; 
 //  float fval = 55.1; 

   cout << "found:" << cfg.GetStringValue("TestConfig", "strtest", sval ) ;
   return 0; 
}
   
