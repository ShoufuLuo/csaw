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
