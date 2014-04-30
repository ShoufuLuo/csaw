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

#ifndef __CONFIG_FILE_H__ 
#define __CONFIG_FILE_H__  

#include <string> 
#include <map> 
#include "regex.h" 

/*
 *------------------------------------------------------------------------
 * Read only configuration file 
 *
 * Configuration parameters have name = value format 
 * Configuration parameters exist within sections 
 *
 * Test if exists 
 * Get default value 
 * support int, float, string, char 
 * Assert validity i.e. duplicates 
 */




class ConfigFile 
{

   std::map<std::string, 
      std::map<std::string, std::string> > section_config_value_map;

   bool     nofile; 
   bool     invalid;
   regex_t  commentexpr; 
   regex_t  namevalueexpr; 
   regex_t  namestringexpr; 
   regex_t  sectionexpr; 

  public: 
   
   ConfigFile() ; 
   ~ConfigFile();

   bool        Init              (std::string filename);
   std::string GetStringValue    (std::string section, std::string name, std::string default_value, bool * found = 0) ;
   long        GetNumericValue   (std::string section, std::string name, long default_value, bool * found = 0) ;
   float       GetStringValue    (std::string section, std::string name, float default_value, bool * found = 0) ;
}; 




#endif 
