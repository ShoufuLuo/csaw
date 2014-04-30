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

#ifndef __MESSAGEPROCESSOR_H__
#define __MESSAGEPROCESSOR_H__


#include "defines.h" 
#include <boost/serialization/deque.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

/**
 * message sending and receiving API to the library 
 * 
 * The library makes Send calls to to enque outgoing messages. 
 * Since the system is deferred send, the application will periodically call 
 * the Deque method to gather messages for a given destination 
 *
 */

struct SerializedMessage
{
      std::string mesg; 
      epoch_t     expiry; 

      private:
      friend class boost::serialization::access;
      template<class Archive> void serialize(Archive & ar, const unsigned int version);  
}; 




 
typedef std::map<peerid_t, std::deque<SerializedMessage> >  mesg_queue_t; 


class MessageProcessor  
{
   mesg_queue_t      outgoing; 

   friend class boost::serialization::access;
   template<class Archive> void serialize(Archive & ar, const unsigned int version);   
  public:

        /** 
         * Library calls enque for sending out messages to any given peer 
         */
   bool     EnqueFromLib      (const peerid_t& peer, const std::string &mesg, epoch_t );


        /** 
         * Application calls deque to gather messages when the time is 
         * right (piggy back on applicatio message)
         */
   bool     DequeForApp       (const peerid_t& peer, std::string & mesg, epoch_t &); 
   bool     DequeForAppAnyPeer(peerid_t& peer, std::string & mesg, epoch_t & ); 
};






template<class Archive> 
inline void SerializedMessage::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_NVP(expiry); 
   ar & BOOST_SERIALIZATION_NVP(mesg); 
}



 
template<class Archive> 
inline void MessageProcessor::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_NVP(outgoing); 
}



#endif //__MESSAGEPROCESSOR_H__

