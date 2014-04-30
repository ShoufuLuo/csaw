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
		return "Hello, Pinocchio! This is Facebook!"; 
	}
};  

if (XPCOMUtils.generateNSGetFactory)  
    const NSGetFactory = XPCOMUtils.generateNSGetFactory([FBAPI]);  
else  
    const NSGetModule = XPCOMUtils.generateNSGetModule([FBAPI]);
