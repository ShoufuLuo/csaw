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

#include "peerfactory.h" 
#include "self.h"
#include "proxypeer.h"
#include "message.h"
#include <fstream>






PeerFactory::PeerFactory(MessageProcessor * p)
   : self(0), processor(p) 
{}





Self * PeerFactory::Create(int keybits, const peerid_t& name, const group_t & bootstrap, std::string cfgfile, 
                           epoch_t * local_time, epoch_t expiry_interval) 
{
   Self * p = new Self(); 
   PublicKeyEncryption *pub = 0; 
   PrivateKeyEncryption *priv = 0; 
   if(!RSACore::createkeypair(pub, priv, keybits))
   {
      delete p; 
      return 0;
   }
   p->encryptor = *( dynamic_cast<RSAPublicKeyEncryption *> (pub) ) ; 
   p->decryptor = *( dynamic_cast<RSAPrivateKeyEncryption *> (priv) ) ;
   delete pub; 
   delete priv;
   p->pid = name; 
   p->trusted = p->probationary = p->bootstrap = bootstrap;
   p->factory = this; 
   p->set_local_time(local_time);
   p->expiry_interval = expiry_interval; 
   p->Init(cfgfile);
   
   return self = p;
}




     /** 
      * Create a self object from serialized representation 
      */ 
bool PeerFactory::Assign(Self * _self) 
{  
   if( self ) 
      return false; 
   self = _self; 
   return true; 
}










   
Peer * PeerFactory::Proxy(const std::string & name)
{
   if( proxyreversemap.find(name) != proxyreversemap.end() ) 
      return proxyreversemap[name]; 

   Peer * p = new ProxyPeer(name, processor); 
   proxymap[p] = name; 
   proxyreversemap[name] = p; 
   return p; 
}
