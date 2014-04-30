/*
 * Copyright (c) 2007, Rutgers, The State University of New Jersey. 
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of  Rutgers, The State University of New Jersey, 
 *       nor the names of its contributors may be used to endorse or promote 
 *       products derived from this software without specific prior written 
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY  Rutgers, The State University of New Jersey 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Rutgers, The State University of 
 * New Jersey BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * Author:  Vivek Pathak 
 * Wed Mar 21 02:43:10 EDT 2007
 *
 *
 */

#include "self.h"
#include "peerfactory.h"
#include "authenticationrequest.h"
#include "admissionrequestmessage.h" 
#include "challenge.h" 
#include "response.h" 
#include "proof.h"
#include "proofrequest.h"
#include "byzantinefault.h" 
#include "byzantineauthenticationmessage.h"
#include "publickeyrequest.h" 
#include <cmath> 
#include "logger.h" 
#include "messagecache.h" 
#include "messagecachedebug.h"
#include "configfile.h"





XLogger& debugcache = * XLogManager::GetLogger("debugcachelog"); 


   
void MessageCacheDebug::Configure(std::string configfile)
{
   ConfigFile cfg;
   if(!cfg.Init(configfile))
   {
      std::cerr << "Cannot init configfile " << configfile << std::endl;
      ::abort();
   }

   std::string logdir =
      cfg.GetStringValue( "Logging" , "LogDirectory" , "." ) ;


   std::string debugcachelogfile =
      cfg.GetStringValue( "Logging" , "CacheDebugLogFile" , "debugmessagecache.log" ) ;
   debugcache.SetDestination(
      XLogManager::GetFileLogDestination( logdir + "/" + debugcachelogfile )
      );
}




MessageCacheDebug::MessageCacheDebug() 
   : report(false)
{}





MessageCacheDebug::MessageCacheDebug(const std::string & _self) 
   : report(true) , self(_self) 
{}




Message * MessageCacheDebug::deserialize(const std::string& mesg)
{
   if(!report) 
      return 0; 

   std::istringstream ins;
   ins.str(mesg); 
   boost::archive::xml_iarchive ia(ins);

   Message * m = 0; 
   ia >> BOOST_SERIALIZATION_NVP(m) ;

   assert(m); 
   return m; 
}






void MessageCacheDebug::Insert(const std::string& mesg) 
{
   Message * m = deserialize(mesg); 
   if(m)
      LOG( debugcache , "Insert" 
           " Self=%s MessageType=%s Expiration=%llu CausalID=%lu DataSize=%u bytes FromPeer=%s ToPeer=%s", 
           self.c_str(),  m->messagetype.c_str(), m->expiration, m->causalid, mesg.size(), m->from.c_str(), m->to.c_str()) ; 
   delete m; 
}






void MessageCacheDebug::Expire(const std::string& mesg) 
{
   Message * m = deserialize(mesg); 
   if(m)
      LOG( debugcache , "Expire" 
           " Self=%s MessageType=%s Expiration=%llu CausalID=%lu DataSize=%u bytes FromPeer=%s ToPeer=%s", 
           self.c_str(),  m->messagetype.c_str(), m->expiration, m->causalid, mesg.size(), m->from.c_str(), m->to.c_str()) ; 
   delete m; 
}







void MessageCacheDebug::Trim(const std::string& mesg) 
{
   Message * m = deserialize(mesg); 
   if(m)
      LOG( debugcache , "Trim" 
           " Self=%s MessageType=%s Expiration=%llu CausalID=%lu DataSize=%u bytes FromPeer=%s ToPeer=%s", 
           self.c_str(),  m->messagetype.c_str(), m->expiration, m->causalid, mesg.size(), m->from.c_str(), m->to.c_str()) ; 
   delete m; 
}







void MessageCacheDebug::Deliver(const std::string& mesg) 
{
   Message * m = deserialize(mesg); 
   if(m)
      LOG( debugcache , "Deliver" 
           " Self=%s MessageType=%s Expiration=%llu CausalID=%lu DataSize=%u bytes FromPeer=%s ToPeer=%s", 
           self.c_str(),  m->messagetype.c_str(), m->expiration, m->causalid, mesg.size(), m->from.c_str(), m->to.c_str()) ; 
   delete m; 
}







