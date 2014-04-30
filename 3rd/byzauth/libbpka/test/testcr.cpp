#include "message.h"
#include "proof.h"
#include "rsa.h"
#include "keyrepository.h"

#include <sstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>




/*
 * July 2. 
 * The program works i.e. verifies the challenge and response are related as they should via the 
 * public key. 
 * When we run challenge response protocol in the simulation, the validation fails.  Is this because challenge 
 * and response are signed in the protocol but unsigned here ? Also copy over the exact challenge response from 
 * the implementation that is giving a problem 
 */ 


const unsigned long KEYBITS = 4096; 

using namespace std; 

std::string toString(Message &message)
{
   std::ostringstream outs;
   boost::archive::xml_oarchive oa(outs); 
   Message * m = &message; 
   oa << BOOST_SERIALIZATION_NVP(m);  
   return outs.str(); 
}


Message * toMessage(const std::string& mesg) 
{
   std::istringstream ins;
   ins.str(mesg); 
   boost::archive::xml_iarchive ia(ins);
   Message * m = 0; 
   ia >> BOOST_SERIALIZATION_NVP(m) ;
   return m; 
}





int main() 
{
   KeyRepository keyrep; 

        // 0. Add signature ti the challenge and response messages 
        //

        // simulating two peers A and B.  A send challenge to B and B responds. 
        // trying to introduce the complexity in a step by step manner to see where it fails
        // 1. multipeer 
   PublicKeyEncryption * pub = 0; 
   PrivateKeyEncryption * priv = 0; 
   RSACore::createkeypair( pub, priv, KEYBITS ) ; 

   keyrep.add( pub, "me", 0, 0 ) ; 
   
   Message mymessage; 

   mymessage.from = "vpathak" ; 
   mymessage.to = "whoever" ; 
   
   cout << toString(mymessage) << endl; 

   Proof p;
   p.from = "me" ; 
   p.to = "b" ; 
   p.challenger = "sdf" ; 
   p.responder = "sdf" ; 
   p.observer = "fdskj" ; 
   p.challenge.challenge = 3355 ; 
   p.challenge.sign(*priv);
   p.response.response = 7777 ; 
   p.response.sign(*priv);
   p.sign(*priv); 


   cout << toString(p) << endl ;

   std::string serialp = toString(p); 
   Message *mrecovered = toMessage(serialp); 
   cout << mrecovered->verify(*pub)   << endl ;
   
   
   cout << toString(*mrecovered) << endl ;
   cout << typeid(*mrecovered).name() << endl ; 

   keyrep.save("keyrep.xml"); 

   delete mrecovered; 
   return 0; 
}
