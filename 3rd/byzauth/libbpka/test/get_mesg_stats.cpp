#include "message.h"
#include "authenticationrequest.h"
#include "admissionrequestmessage.h"
#include "challenge.h"
#include "response.h"
#include "proof.h"
#include "proofrequest.h"
#include "byzantinefault.h"
#include "byzantineauthenticationmessage.h"
#include "publickeyrequest.h"
#include "rsa.h"
#include "keyrepository.h"

#include <sstream>
#include <cstdio>
#include <zutil.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>




std::string toString(Message &message)
{
   std::ostringstream outs;
   boost::archive::xml_oarchive oa(outs); 
   Message * m = &message; 
   oa << BOOST_SERIALIZATION_NVP(m);  
   return outs.str(); 
}


int main() 
{
   char line[8192]; 
   int total = 0; 
   std::string all; 
   for( int i = 0; i < 10000; i++ ) 
   {
      std::string s; 
      while( fgets(line, 8192, stdin) ) 
      {
         s += line; 
         if( !strncmp( line, "</m>", 4 ) )
            break;
      }
      std::istringstream ins;
      ins.str(s);
      boost::archive::xml_iarchive ia(ins);
      Message *m; 
      ia >> BOOST_SERIALIZATION_NVP(m) ;
      std::string x = toString(*m);
      all += x; 
      total += x.length(); 
      int outlen = compressBound( (uLongf) total ); 
      char * outbuf = (char *) malloc( outlen ) ; 
	std::cout <<      compress ((Bytef*)outbuf, (uLongf*)&outlen, (const Bytef*)all.c_str(), (uLongf)all.length() ) << std::endl  ; 
      delete m; 
      free(outbuf);
      std::cout << i << " " << outlen << " " << total << std::endl ; 
   }
   return 0; 
}
