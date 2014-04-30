#include "rsa.h" 
#include <sstream>
#include <boost/config.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#define KEYBITS 4096
#define NUMTESTS 256
using namespace std; 

int main() 
{
   PublicKeyEncryption * pub = 0; 
   PrivateKeyEncryption * priv = 0; 
   RSACore::createkeypair( pub, priv, KEYBITS ) ; 
   RSAPublicKeyEncryption & testpub = *(RSAPublicKeyEncryption *) pub; 

   ostringstream outs; 
   boost::archive::xml_oarchive oa(outs);
   oa << BOOST_SERIALIZATION_NVP(testpub);
   std::string serialized = outs.str() ; 
   
   cout << outs.str() << endl ; 

        // read serialized version of the public key
   istringstream ins; 
   ins.str(serialized);
   boost::archive::xml_iarchive ia(ins);
   RSAPublicKeyEncryption pubcopy;
   ia >> BOOST_SERIALIZATION_NVP(pubcopy);


   for( int i = 0; i < NUMTESTS; i++ ) 
   {
      UBigNum test, encrypted, recovered;
      test.random(KEYBITS-8);

      pub->Encrypt( encrypted, test )  ; 
      priv->Decrypt( recovered, encrypted ) ; 

      cout << test << endl ; 
      cout << encrypted << endl ; 
      cout << recovered << endl ; 

      assert( test == recovered ) ; 
      cout << test << " == " << recovered << endl ; 
   }

   return 0; 
}
