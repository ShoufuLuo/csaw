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
#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__ 



#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <cassert>

#define SEPRARATOR ((char)1)

#define __no_impl__ {return __no_impl(__FILE__,__LINE__);} 


/**
 * Base class for archive class that is used as the 
 * serialization target 
 */

class ARCHIVE   
{
  protected:
   virtual ~ARCHIVE() {} 
 
   ARCHIVE & __no_impl(const char f[], int l) 
   {
      std::cerr<< "Unimplemented\t@" << f << ":" << l <<std::endl;
      return *this;
   }

  public:

   class SERIALIZABLE { 
     public : 
      virtual bool serialize(ARCHIVE & ar) = 0 ; 
   };

   virtual ARCHIVE &  operator & (double& _value)        __no_impl__  
   virtual ARCHIVE &  operator & (long& _value)          __no_impl__  
   virtual ARCHIVE &  operator & (std::string& _value)   __no_impl__  
};
     





class W_ARCHIVE : public ARCHIVE 
{ 
   std::ofstream&          wstream; 
   const char              separator; 

  public: 

   W_ARCHIVE(std::ofstream& filestream)  
      : wstream(filestream), separator( SEPRARATOR )  
   {}

   ARCHIVE &  operator & (double& _value) { 
      return wstream << _value, wstream << separator, *this ; 
   }

   ARCHIVE &  operator & (long& _value) { 
      return wstream << _value, wstream << separator, *this ;   
   }

   ARCHIVE &  operator & (std::string& _value) { 
      return wstream << _value, wstream << separator, *this ; 
   }
};



template<typename T> W_ARCHIVE & operator & (W_ARCHIVE & in, T & o) 
{
   ARCHIVE::SERIALIZABLE& serializable_object = o; 
   bool success = serializable_object.serialize(in); 
   assert(success) ; 
   return in; 
}






class R_ARCHIVE : public ARCHIVE 
{ 
   std::ifstream&          rstream; 
   const char              separator; 
   std::string             fldbuf; 


        /**
         * Reads until a \001 is found and assigns it to 
         * the fld buf string 
         */ 
   inline bool getfield() 
   {
      int c; 
      if(rstream.eof())
         return false; 

      fldbuf.clear(); 

      while( (c = rstream.get()) != separator ) 
         if(rstream.eof())
         {
            std::cerr<< "Unterminated field->" << fldbuf << 
               "<-at eof\t@" << __FILE__ << ":" << __LINE__ << std::endl;
            return false; 
         }
         else
            fldbuf.append(1, c); 

      return true; 
   }


  public: 


   R_ARCHIVE(std::ifstream& filestream)  
      : 
      rstream(filestream), 
      separator( SEPRARATOR )
   {}

   virtual ARCHIVE &  operator & (double& _value) { 
      getfield() ; 
      std::stringstream sstream(fldbuf);
      return sstream >> _value, *this ; 
   }

   virtual ARCHIVE &  operator & (long& _value) { 
      getfield() ; 
      std::stringstream sstream(fldbuf);
      return sstream >> _value, *this ; 
   }

   virtual ARCHIVE &  operator & (std::string& _value) { 
      getfield() ; 
      std::stringstream sstream(fldbuf);
      return sstream >> _value, *this ; 
   }
};





template<typename T> R_ARCHIVE & operator & (R_ARCHIVE & in, T & o) 
{
   ARCHIVE::SERIALIZABLE& serializable_object = o; 
   bool success = serializable_object.serialize(in); 
   assert(success) ; 
   return in; 
}




#endif /*__ARCHIVE_H__*/
