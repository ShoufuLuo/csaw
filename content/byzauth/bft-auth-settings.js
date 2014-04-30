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

var params = window.arguments[0];


function doBftSettingsOK()
{
   window.arguments[0].out = { ttl : parseInt( document.getElementById("ttl-text-textbox").value ) * 86400 , 
                               tgs : parseInt( document.getElementById("tgs-text-textbox").value ) , 
                               payload : parseInt( document.getElementById("payload-text-textbox").value  ) , 
                               keylen : parseInt(  document.getElementById("keylen-text-textbox").value ) } ; 
   return true; 
}


function onBftSettingsLoad()
{
   var ttl = params.ttl/86400 ; 
   document.getElementById("ttl-text-textbox").value = ttl.toString(); 
   document.getElementById("tgs-text-textbox").value = params.tgs.toString(); 
   document.getElementById("payload-text-textbox").value = params.payload.toString(); 
   document.getElementById("keylen-text-textbox").value = params.keylen.toString(); 
   return true;    
}


function doBftSettingsCancel()
{
   window.arguments[0].out = null ;
}
