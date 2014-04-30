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

#include "diskmessagecache.h" 
#include <fstream>
#include <sstream>




// TODO 
// Change into slow cache and fast cache 
// Read slow cache when we have free send bandwidth 
//



DiskMessageCache::DiskMessageCache(epoch_t & lamport_time, 
                                   epoch_t & causal_time, 
                                   epoch_t & local_time, 
                                   const std::string& persistent,
                                   const std::string& self,
                                   unsigned messages_in_mem) 
   : 
   MessageCache(lamport_time, causal_time, local_time, persistent, self),
   cachefilename( persistent + ".cacheout" ) ,
   cacheloadcount(1),
   cachedout(false), 
   cachesize(0), 
   CACHE_TARGET_SIZE(messages_in_mem)
{
   CacheOut(); 
}






DiskMessageCache::~DiskMessageCache()
{
   Save();
   CacheIn(); 
}








void DiskMessageCache::CacheOut()
{
   if(--cacheloadcount != 0)
      return; 

   if((cachesize = cache.size()) < CACHE_TARGET_SIZE)
   {
      std::ostringstream outs;
      boost::archive::xml_oarchive oa(outs);
      oa << BOOST_SERIALIZATION_NVP(cache);
      nbytes = outs.str().size();
      return; 
   }

   std::ofstream ofs(cachefilename.c_str());
   if(!ofs.good())
      abort(); 

   boost::archive::xml_oarchive oa(ofs);
   oa << BOOST_SERIALIZATION_NVP(cache);

   nmessages = cache.size(); 
   ofs.flush();
   nbytes = ofs.tellp();
   cache.clear(); 
   cachedout = true; 
}







void DiskMessageCache::CacheIn()
{
   if(cacheloadcount++ > 0)
      return; 

   if(!cachedout)
      return; 

   std::ifstream ifs(cachefilename.c_str());
   if(!ifs.good())
      return ; 
   boost::archive::xml_iarchive ia(ifs);
   ia >> BOOST_SERIALIZATION_NVP(cache); 

   nmessages = cache.size(); 
   nbytes = ifs.tellg();
}
