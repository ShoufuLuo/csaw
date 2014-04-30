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

#include "logger.h"
#include <cstdio>
#include <ctime>
#include <cstdarg> 
#include <cstring> 





bool XLogDestination::Init(std::string logfile)
{
   if(fp)
      fclose(fp);
   filename = logfile; 
   fp = fopen( logfile.c_str(), "a" );
   return true; 
}





XLogDestination::XLogDestination()
   : 
   fp(0),
   log_log_time(true), 
   log_file(true), 
   log_line(true),
   log_function(true),
   log_compile_time(true),
   log_compile_date(true),
   log_compiler_version(true) 
{
   mesgbuflen = 64*1024; 
   messagebuffer = new char [mesgbuflen+1]; 
}
   



XLogDestination::XLogDestination(const XLogDestination& c)
   : 
   messagebuffer(0),
   fp(0),
   log_log_time(true), 
   log_file(true), 
   log_line(true),
   log_function(true),
   log_compile_time(true),
   log_compile_date(true),
   log_compiler_version(true) 
{
   this->copy(c);
}





void XLogDestination::copy(const XLogDestination& c)
{
   if(messagebuffer)
      delete [] messagebuffer; 
   mesgbuflen = c.mesgbuflen ; 
   messagebuffer = new char [mesgbuflen+1]; 
   if(fp)
      fclose(fp);
   filename = c.filename; 
   fp = fopen( filename.c_str(), "a" );
   log_log_time = c.log_log_time ; 
   log_file = c.log_file ; 
   log_line = c.log_line ;
   log_function = c.log_function ; 
   log_compile_time = c.log_compile_time ; 
   log_compile_date = c.log_compile_date ; 
   log_compiler_version = c.log_compiler_version;
}





XLogDestination::~XLogDestination()
{
   if(fp)
      fclose(fp);
   if(messagebuffer)
      delete [] messagebuffer; 
}






bool XLogDestination::log_write(const char * message, int mlen) 
{
   int written = fwrite( message, mlen, 1, fp ); 
   if( message[mlen-1] != '\n' )
      fputc('\n', fp ) ; 
   fflush(fp); 
   return written == 1 ; 
}




bool XLogDestination::log_mesg(time_t curr,
                               const char * filename, 
                               int line, 
                               const char * compile_date, 
                               const char * compile_time, 
                               const char * compiler_version,
                               const char * functionname, 
                               const char * message)
{
   messagebuffer[0] = 0; 
   int currlen = 0;
   int written = 0; 

   if(log_log_time)
   {
      char timebuf[80];
      strcpy( timebuf, ctime(&curr) ) ; 
      char * p = strtok( timebuf, "\n" ) ; 
      if( 0 > (written = snprintf(messagebuffer + currlen, mesgbuflen - currlen, 
                                  "%s\t" , p)) || currlen >= mesgbuflen )
         return false; 
      currlen += written; 
   }



   if(log_file)
   {
      if( 0 > (written = snprintf(messagebuffer + currlen, mesgbuflen - currlen, 
                                  "%s " , filename)) || currlen >= mesgbuflen )
         return false; 
      currlen += written; 
   }   


   if(log_line)
   {
      if( 0 > (written = snprintf(messagebuffer + currlen, mesgbuflen - currlen, 
                                  "%d " , line)) || currlen >= mesgbuflen )
         return false; 
      currlen += written; 
   }   

   if(log_compile_date)
   {
      if( 0 > (written = snprintf(messagebuffer + currlen, mesgbuflen - currlen, 
                                  "%s " , compile_date)) || currlen >= mesgbuflen )
         return false; 
      currlen += written; 
   }   

   if(log_compile_time)
   {
      if( 0 > (written = snprintf(messagebuffer + currlen, mesgbuflen - currlen, 
                                  "%s\t" , compile_time)) || currlen >= mesgbuflen )
         return false; 
      currlen += written; 
   }   



   if(log_function)
   {
      if( 0 > (written = snprintf(messagebuffer + currlen, mesgbuflen - currlen, 
                                  "%s\t" , functionname)) || currlen >= mesgbuflen )
         return false; 
      currlen += written; 
   }   

   
   if( 0 > (written = snprintf(messagebuffer + currlen, mesgbuflen - currlen, 
                               "%s\t" , message)) || currlen >= mesgbuflen )
      return false; 
   currlen += written; 
      

   if(log_compiler_version)
   {
      if( 0 > (written = snprintf(messagebuffer + currlen, mesgbuflen - currlen, 
                                  "%s\t" , compiler_version)) || currlen >= mesgbuflen )
         return false; 
      currlen += written; 
   }

   return log_write(messagebuffer, currlen) ; 
}












char * XLogger::compilerbuf = new char [128]; 

char * XLogger::get_compiler_version(int a, int b, int c)
{
   snprintf( compilerbuf, 128, "gcc%d.%d.%d", a, b, c );   
   return compilerbuf; 
}


XLogger::XLogger()
   : 
   dest(0), 
   messagebuffer(new char [8192+1]) ,
   mesgbuflen(8192)
{}




void  XLogger::SetDestination(XLogDestination * _dest)
{
   dest = _dest; 
}



bool XLogger::log_mesg(const char * filename, 
                       int line, 
                       const char * compile_date, 
                       const char * compile_time, 
                       const char * compiler_version,
                       const char * functionname, 
                       XLogger& logger, 
                       const char * format, ... ) 
{
   time_t curr;
   time(&curr);

   va_list ap;
   va_start(ap, format);
   vsnprintf(logger.messagebuffer, logger.mesgbuflen, format, ap);
   va_end(ap);

   if(logger.dest)    
      return logger.dest->log_mesg(curr, filename, line, compile_date, 
                                   compile_time, compiler_version, 
                                   functionname, logger.messagebuffer) ;
   return false; 
}


















XLogManager * XLogManager::singleton = 0; 



XLogger* XLogManager::GetLogger( std::string logname ) 
{
   if(!singleton)
      singleton = new XLogManager(); 

   if( singleton->logmap.find(logname) == singleton->logmap.end() ) 
   {
      singleton->logmap[logname].Init(logname); 
   }
   return & singleton->logmap[logname]; 
}


      



XLogDestination* XLogManager::GetFileLogDestination(std::string logfile ) 
{
   if(!singleton)
      singleton = new XLogManager();
   if( singleton->destmap.find(logfile) == singleton->destmap.end() ) 
      singleton->destmap[logfile].Init(logfile); 
   return &singleton->destmap[logfile];
}





void XLogManager::Shutdown()
{
   delete singleton; 
}







