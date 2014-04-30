/**
 *  Copyright (c) 2012 Stevens Institute of Technology. 
 *  
 *  All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *	Author: Vivek Pathak
 * 	Mon Jan 2 6:36:10 EDT 2012 
 *
 */

#include <iostream> 
#include <string>
#include <stdio.h>
#include <assert.h>

static char translation[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=" ; 
static int inverse[256]; 
static int LINE_WRAP_LEN = 65; 


void get_inverse_translation() 
{
   for( int i = 0; i < 256; i++ ) 
      inverse[i] = -1; 
   for( int i = 0; i < 64; i++ ) 
      inverse[(unsigned int)translation[i]] = i ;  
   inverse[(unsigned int)'='] = 0; 
}



bool to_base_64(std::string & out, const std::string & in)
{
   int linelen = 0; 
   int padding = 0; 
   const int step = 3; 
   const unsigned char * const end = (const unsigned char *) in.data() + in.length() ; 
   for( const unsigned char *q = (const unsigned char *) in.data(); q < end; q += step ) 
   {
      unsigned int value = 0; 
      for( int i = 0; i < step; i++ ) 
         value = (value<<8) + ( 
               ((q+i) < end) ?  
               (q[i]) :  
               (padding++, 0) ); 

      char encoded[5]; encoded[4] = 0; 
      for( int j = 3; j >= 0; j-- ) 
      {
         encoded[j] = translation[ value & ((1<<6)-1) ] ; 
         value >>= 6 ; 
      }

      for( int j = 3; j >= 0 && padding > 0; j-- , padding-- )
      {
         encoded[j] = '=' ; 
      }

      out.append(encoded) ; 

      linelen += 4;              // encoded has constant length
      if( linelen > LINE_WRAP_LEN ) 
      {
         out.append("\n"); 
         linelen = 0; 
      }
   }

        // delete trailing new line
   while(true) 
   {
      std::string::reverse_iterator i = out.rbegin(); 
      int length = out.length() ; 
      if( !length || *i != '\n' ) 
         break; 
      out.erase(length-1 , length); 
   }

   return true; 
}






bool from_base_64(std::string& out, const std::string& in) 
{
   static bool firsttime = true; 
   if( firsttime ) 
   {
      get_inverse_translation() ; 
      firsttime = false; 
   }

   const int step = 4; 
   const unsigned char * q = (const unsigned char * ) in.data(); 
   const unsigned char * const end =  (const unsigned char * ) in.data() + in.length(); 

   while( q < end ) 
   {
      unsigned int value = 0; 
      for( int i = 0; i < step; q++ ) 
      {
         if( q >= end ) 
            return false; 
         if( *q == '\n' ) 
            continue; 
         if( inverse[*q] < 0 )
            return false; 
         value = (value << 6) + ( *q == '=' ? 0 : inverse[*q] ) ;
         i++;
      }

      char abc[4]; 
      for( int i = 2; i >= 0; i-- ) 
      {  
         abc[i] = (value & ((1<<8)-1)) ;  
         value >>= 8; 
      }
      abc[3] = 0; 

      if( q != end ) 
         out.append(abc, 3); 
      else
         out.append(abc); 
   }

        // delete trailing 0
   /*
   while(true) 
   {
      std::string::reverse_iterator i = out.rbegin(); 
      int length = out.length() ; 
      if( !length || *i != 0 ) 
         break; 
      out.erase(length-1 , length); 
   }
   */

   return true; 
}



#ifdef SELF_TEST
int main(int argc, char * argv[]) 
{
   FILE * fp = stdin; 
   if( argc > 1 ) 
      fp = fopen(argv[1], "r" ) ; 
   assert(fp);
   char line[8192]; 
   while(fgets(line, 8192, fp))
   {
      line[8191] = 0; 
      char * p = strtok( line, "\n" ); 
      if(!p) 
         continue; 
      std::string in = p, out, recover; 
      to_base_64(out, in); 
      std::cout << in << std::endl; 
      std::cout << out << std::endl; 
      from_base_64(recover, out); 
      std::cout << recover << std::endl; 
      assert( recover == in ) ; 
   }
}
#endif 



