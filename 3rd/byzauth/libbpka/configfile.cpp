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

#include "configfile.h" 
#include "regex.h" 
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib> 
#include <cassert>




static const char * comment_re = "^#" ;  
static const char * name_value_re = "([a-zA-Z_][a-zA-Z0-9_]*)=([a-zA-Z0-9_]+)" ; 
static const char * name_string_re =  "([a-zA-Z_][a-zA-Z0-9_]*)=[\\'\\\"](.*)[\\'\\\"]" ;  
static const char * section_re = "\\[([a-zA-Z0-9]*)\\]" ; 




ConfigFile::~ConfigFile() 
{
   regfree(&commentexpr); 
   regfree(&namevalueexpr);
   regfree(&namestringexpr);
   regfree(&sectionexpr);
}



ConfigFile::ConfigFile() 
{
   int ret;
   try 
   {
      if((ret = regcomp(&commentexpr,comment_re,REG_EXTENDED)))
         throw ret; 
      if((ret = regcomp(&namevalueexpr,name_value_re,REG_EXTENDED)))
         throw ret; 
      if((ret = regcomp(&namestringexpr,name_string_re,REG_EXTENDED)))
         throw ret; 
      if((ret = regcomp(&sectionexpr,section_re,REG_EXTENDED)))
         throw ret; 
      invalid = false; 
   }
   catch(int err)
   {
      invalid = true; 
   }
}




bool ConfigFile::Init(std::string filename)
{
   nofile = false; 
   FILE * fp = fopen( filename.c_str(), "r" ) ; 
   if (!fp) 
   {
      nofile = true; 
      return false;
   }
   
   std::string section; 
   bool has_section = false; 

   int nmatches = 16; 
   regmatch_t matches[nmatches];
   char line[8192]; 
   while( fgets(line, 8192, fp) ) 
   {
      if(!regexec(&commentexpr, line, 16, matches, 0))
         continue; 
      
      if(!regexec(&sectionexpr, line, 16, matches, 0))
      {
         assert( matches[1].rm_so >= 0 ); 
         section.assign( line + matches[1].rm_so,  matches[1].rm_eo - matches[1].rm_so ) ; 
         has_section = true; 
         continue; 
      }

      if(!regexec(&namestringexpr, line, 16, matches, 0) || 
         !regexec(&namevalueexpr, line, 16, matches, 0))
      {
         std::string name, value; 

         assert( matches[1].rm_so >= 0 && matches[2].rm_so >= 0) ; 

         name.assign( line + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so ) ; 
         value.assign( line + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so ) ; 

         assert(has_section);

         section_config_value_map[section][name] = value; 

      }
   }
   fclose(fp); 
   return true; 
}




std::string ConfigFile::GetStringValue(std::string section, std::string name, std::string default_value, bool * found) 
{
   if( section_config_value_map.find(section) == section_config_value_map.end() ||  
       section_config_value_map[section].find(name) == section_config_value_map[section].end() )
   {
      if(found)
         *found = false; 
      return default_value; 
   }

   if(found)
      *found = true; 

   return section_config_value_map[section][name] ; 
}



