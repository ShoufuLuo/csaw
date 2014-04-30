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
  
function TWTAPI()
{
	// initialize this component here	
}  
    
//class declaration
TWTAPI.prototype = {  
	classDescription: "OSN (Twitter) Javascript API for Pinocchio",  
	classID: Components.ID("{3E1B79A5-9641-4D54-8CDF-486C5A32499A}"),
	contractID:  "@pinocchio.com/OSNAPI/Twitter;1",  
    QueryInterface: XPCOMUtils.generateQI([Components.interfaces.iOSNAPI]),  
 
 	helloOSNAPI: function()
	{
		return "Hello, Pinocchio! This is Twitter!"; 
	}
};  

if (XPCOMUtils.generateNSGetFactory)  
    const NSGetFactory = XPCOMUtils.generateNSGetFactory([TWTAPI]);  
else  
    const NSGetModule = XPCOMUtils.generateNSGetModule([TWTAPI]);
