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

/* -*- Mode: Java; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*-*/

var gBftaddress_regex = new Array(); 
gBftaddress_regex[0] = new RegExp( /\<((\S+)\@(.*))\>/ ) ;
gBftaddress_regex[1] = new RegExp( /((\S*)\@(\S*))/ ) ; 
 


function BftgetAddress (address) 
{
   for( var i = 0; i < 2; i++ ) 
   {
      if( gBftaddress_regex[i].test(address) )
      {
         var matches = gBftaddress_regex[i].exec(address) ; 
         return RegExp.$1; 
      }
   }
}



function BftgetAddresses(addresses, retval) 
{
   if( addresses == null ) 
      return ; 
   if( addresses.length == 0 ) 
      return ; 
   address_array = addresses.split(/,|;/) ; 
   for( var i = 0; i < address_array.length ; i++ ) 
   {
      var address = BftgetAddress(address_array[i]) ; 
      if( address.length > 0 ) 
         retval.push( address ) ; 
   }
   return retval; 
}
