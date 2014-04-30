#include "message.h"
#include "proof.h"
#include "rsa.h"
#include "keyrepository.h"
#include <sstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

const unsigned long KEYBITS = 32; 
const unsigned long NUMKEYS = 16; 
const char * KEYREPFILE = "keyrep.xml" ;

using namespace std; 

int main() 
{
   KeyRepository keyrep; 


   cout << "creating keys" << endl;  
   for( unsigned int i = 0; i < NUMKEYS; i++ ) 
   {
      char name[1024]; 
      snprintf( name, 1024, "peer%d" , i ) ; 

      PublicKeyEncryption * pub = 0; 
      PrivateKeyEncryption * priv = 0; 
      RSACore::createkeypair( pub, priv, KEYBITS ) ; 
      delete priv; 
      keyrep.add(pub, name, 0, 0 ) ; 
      cout << i << "\r" << flush ; 
   }
   
   cout << "done creating keys" << endl; 

   keyrep.save(KEYREPFILE); 

   keyrep.clear(); 

   cout << "restoring" << endl ; 
   keyrep.restore(KEYREPFILE); 

   cout << "restored" << endl ; 

   return 0; 
}
