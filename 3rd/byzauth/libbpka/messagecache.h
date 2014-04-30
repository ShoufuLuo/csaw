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

#ifndef __MESSAGE_CACHE_H__
#define __MESSAGE_CACHE_H__ 


#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "defines.h" 
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include <string>
#include "messagecachedebug.h"


struct ets_t 
{
      epoch_t     timestamp;
      epoch_t     encrypted; 
      ets_t() : timestamp(0) {} 
      private:
      friend class boost::serialization::access;
      template<class Archive> void serialize(Archive & ar, const unsigned int version);
};



typedef std::map<std::string, ets_t>  vector_ets_t; 
typedef std::map<std::string, vector_ets_t> matrix_ets_t; 



struct CacheRecord 
{
      epoch_t     local_time; 
      epoch_t     expiry ;
      ets_t       lamport_time; 
      ets_t       causal_time;
      ets_t       stable_read;
      std::string source; 
      std::string destination;
      std::string message; 

      private:
      friend class boost::serialization::access;
      template<class Archive> void serialize(Archive & ar, const unsigned int version);

      public:
      CacheRecord() : local_time(0), expiry(0) {;} ;
}; 



struct Envelope 
{
      std::string    source; 
      ets_t          lt;
      vector_ets_t   ctv;
      ets_t          sr;
      std::set<std::string>    dest; 
      std::vector<CacheRecord> messages; 
      
      private:
      friend class boost::serialization::access;
      template<class Archive> void serialize(Archive & ar, const unsigned int version); 
};



typedef std::multimap<epoch_t, CacheRecord> cached_mesgmap_t; 



class MessageCache 
{
   class CacheLoader 
   {
      MessageCache *    cache; 
     public: 
      CacheLoader       (MessageCache * p) ; 
      ~CacheLoader      (); 
   };

   std::string             self; 
   std::string             persistent;
   std::set<std::string>   peergroup; 
   epoch_t &               lamport_time; 
   epoch_t &               causal_time; 
   epoch_t &               local_time; 
   epoch_t                 stable_read;
   vector_ets_t            ltv; 
   vector_ets_t            srv; 

        // ctm[x][y] is the latest causal 
        // timestamp of y known to x
   matrix_ets_t            ctm; 

   MessageCacheDebug       debugger; 

   void     trim_cache                 (); 
   void     update_stable_read_vec     (); 
   void     delete_delivered_messages  ();

 
  protected:
   cached_mesgmap_t        localmesg; 
   cached_mesgmap_t        cache; 
   unsigned                nmessages; 
   unsigned                nbytes;


   virtual void   CacheOut () {}
   virtual void   CacheIn  () {} 


  public:

   MessageCache            (epoch_t & lamport_time, 
                            epoch_t & causal_time, 
                            epoch_t & local_time, 
                            const std::string& persistent,
                            const std::string& self) ; 

   virtual ~MessageCache   () {}


   void Configure          (std::string config); 

        /*
         * Send out the messages that should go 
         * Caller says how many messages we can carry at this moment
         */
   void     OutGoingEvent  (const std::vector<std::string>& to, std::string& mesg, unsigned int max_num_messages);

        /*
         * Receive messages that have come
         */
   void     InComingEvent  (const std::string& from, const std::string& mesg);

   
        /*
         * persistence 
         */
   bool     Save           ();
   bool     Load           (const std::string& file);


        /*
         * Deliver messages to local application
         */
   bool     DeliverLocal   (std::string& from, std::string & mesg); 

        /*
         * Application delivers message to cache 
         */
   bool     Insert         (const std::string & peer, const std::string & mesg, epoch_t expiry); 

   
        /* 
         * Statistics on how many messages held for who 
         */
   bool     CacheUsage     (std::map<std::string, unsigned>& src, std::map<std::string, unsigned>& dst); 

        /*
         * Clear out messages from or to a given peer 
         */
   void     EraseFrom      (const std::string & peer);
   void     EraseTo        (const std::string & peer); 


   bool     GetCacheSize   (unsigned & messages, unsigned & bytes);

  private:
   friend class boost::serialization::access;
   template<class Archive> void serialize(Archive & ar, const unsigned int version);
};








template<class Archive> 
inline void ets_t::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_NVP(timestamp);
   ar & BOOST_SERIALIZATION_NVP(encrypted);
}


template<class Archive> 
inline void CacheRecord::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_NVP(local_time);
   ar & BOOST_SERIALIZATION_NVP(expiry);
   ar & BOOST_SERIALIZATION_NVP(lamport_time);
   ar & BOOST_SERIALIZATION_NVP(causal_time);
   ar & BOOST_SERIALIZATION_NVP(stable_read);
   ar & BOOST_SERIALIZATION_NVP(source);
   ar & BOOST_SERIALIZATION_NVP(destination);
   ar & BOOST_SERIALIZATION_NVP(message);
}



template<class Archive> 
inline void Envelope::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_NVP(source);
   ar & BOOST_SERIALIZATION_NVP(lt);
   ar & BOOST_SERIALIZATION_NVP(ctv);
   ar & BOOST_SERIALIZATION_NVP(sr);
   ar & BOOST_SERIALIZATION_NVP(dest);
   ar & BOOST_SERIALIZATION_NVP(messages);
}      


template<class Archive> 
inline void MessageCache::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_NVP(cache);
   ar & BOOST_SERIALIZATION_NVP(localmesg); 
   ar & BOOST_SERIALIZATION_NVP(lamport_time);
   ar & BOOST_SERIALIZATION_NVP(causal_time);
   ar & BOOST_SERIALIZATION_NVP(ltv);
   ar & BOOST_SERIALIZATION_NVP(srv);
   ar & BOOST_SERIALIZATION_NVP(ctm);
}

#endif
