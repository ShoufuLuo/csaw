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

#ifndef __LOGGER_H__ 
#define __LOGGER_H__ 


#include <cstdio> 
#include <ctime> 
#include <cassert>
#include <map> 
#include <string>


#define THIS_FILE          __FILE__
#define THIS_LINE          __LINE__
#define COMPILE_DATE       __DATE__
#define COMPILE_TIME       __TIME__


#ifndef __GNUC__ 
#error "currently compiled only for gcc - please port function macro" 
#endif 

#define THIS_FUNCTION      __FUNCTION__
#define COMPILER_VERSION      XLogger::get_compiler_version(__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__) 
#define LOG(logger,fmt...)    XLogger::log_mesg(THIS_FILE,          \
                                 THIS_LINE,COMPILE_DATE,COMPILE_TIME,\
                                 COMPILER_VERSION,THIS_FUNCTION,     \
                                        logger,fmt)




class XLogDestination 
{
   friend class XLogManager; 
   char *            messagebuffer; 
   int               mesgbuflen; 
   FILE *            fp; 
   bool              log_log_time; 
   bool              log_file; 
   bool              log_line; 
   bool              log_function; 
   bool              log_compile_time;
   bool              log_compile_date;
   bool              log_compiler_version;   
   std::string       filename; 


   virtual bool   log_write(const char * message, int); 
   void           copy     (const XLogDestination& c);
  public:

   virtual ~XLogDestination(); 
   XLogDestination(); 
   XLogDestination(const XLogDestination& c); 
   const XLogDestination& operator =(const XLogDestination& c) {this->copy(c); return c;}

   bool           Init(std::string logfile); 

   bool           log_mesg (time_t curr,
                         const char * filename, 
                         int line, 
                         const char * compile_date, 
                         const char * compile_time, 
                         const char * compiler_version,
                         const char * functionname, 
                         const char * message) ;

};




class XLogger 
{
   friend class XLogManager; 
   XLogDestination * dest; 
   char *            messagebuffer; 
   int               mesgbuflen; 
   static char *     compilerbuf;
   std::string       logname; 
   
   
  public:
   XLogger           ();  

   void Init(std::string _logname) { logname = _logname; } 

   static bool log_mesg (const char * filename, 
                         int line, 
                         const char * compile_date, 
                         const char * compile_time, 
                         const char * compiler_version,
                         const char * functionname, 
                         XLogger& logger, 
                         const char * format, ... ) ;

   static char * get_compiler_version(int, int, int); 

   void SetDestination  (XLogDestination * _dest);
};





     /**    
      * Front end for the logging. 
      * Ideally this object should be created by a singleton factory
      * The factory should be contactable remotely through a socket 
      * interface to dynamically change the following:
      *     1. The destination of log messages
      *     2. The detail level of log messages 
      *     3. The batch size at which logs are flushed to destination 
      */




class XLogManager 
{
   std::map<std::string, XLogger> logmap; 
   std::map<std::string, XLogDestination> destmap; 
   static XLogManager * singleton; 

  public: 

   static XLogger* GetLogger( std::string logname ) ; 
   static XLogDestination* GetFileLogDestination(std::string logfile ) ; 
   static void Shutdown();
};








#endif 
