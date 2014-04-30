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
 *	Author: Shoufu Luo
 * 	Mon Jan 2 6:36:10 EDT 2012 
 *
 */

Components.utils.import("resource://gre/modules/XPCOMUtils.jsm");  
  
function FBAPI()
{
	// initialize this component here	
}  
    
//class declaration
FBAPI.prototype = {  
	classDescription: "OSN (Facebook) Javascript API for Pinocchio",  
	classID: Components.ID("{D535D85D-D063-44B4-81F3-B521697408CD}"),
	contractID:  "@pinocchio.com/OSNAPI/Facebook;1",  
    QueryInterface: XPCOMUtils.generateQI([Components.interfaces.iOSNAPI]),  
 
 	helloOSNAPI: function()
	{
		return "Hello, Pinocchio! Connecting... "; 
	}
};  

if (XPCOMUtils.generateNSGetFactory)  
    const NSGetFactory = XPCOMUtils.generateNSGetFactory([FBAPI]);  
else  
    const NSGetModule = XPCOMUtils.generateNSGetModule([FBAPI]);
