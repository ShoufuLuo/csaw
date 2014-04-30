#include "message.h"
#include "proof.h"
#include "rsa.h"
#include "proofrepository.h"
#include "logger.h" 
#include <sstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

const unsigned long KEYBITS = 4096; 
const char * PREPFILE = "proofrep.xml" ;

using namespace std; 

XLogDestination d2("test.log");
XLogger testlog(d2);


int main() 
{
   LOG( testlog, "Completed test" ) ; 

   PublicKeyEncryption * apub = 0; 
   PrivateKeyEncryption * apriv = 0; 
   RSACore::createkeypair( apub, apriv, KEYBITS ) ; 

   PublicKeyEncryption * bpub = 0; 
   PrivateKeyEncryption * bpriv = 0; 
   RSACore::createkeypair( bpub, bpriv, KEYBITS ) ; 

   Proof p;
   p.challenger = "a" ; 
   p.responder = "b" ; 
   p.observer = "a" ; 

   ProofRepository rep; 

   UBigNum test, encrypted, recovered;
   test.random(KEYBITS-8);

   bpub->Encrypt( encrypted, test )  ;
   p.challenge.challenge = encrypted; 


   bpriv->Decrypt( recovered, encrypted ) ;
   p.response.response = recovered; 

   assert( recovered == test ) ; 


   rep.putProof(p); 
   rep.save(PREPFILE); 
   rep.clear(); 

   cout << "restoring" << endl ; 
   rep.restore(PREPFILE); 

   cout << "restored" << endl ; 

   LOG( testlog, "Completed test" ) ; 
   return 0; 
}
