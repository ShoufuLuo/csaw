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

/* JS version to implement ihelloxpcom interface */

components.utils.import("resource://gre/modules/XPCOMUtils.jsm");

function helloxpcom() { }

helloxpcom.prototype = {
    /**
     * .classID is required for generateNSGetFactory to work correctly.
     * Make sure this CID matches the "component" in your .manifest file.
     */
    classID: Components.ID("{dea98e50-1dd1-11b2-9344-8902b4805a2e}"),

    /**
     * .classDescription and .contractID are only used for
     * backwards compatibility with Gecko 1.9.2 and
     * XPCOMUtils.generateNSGetModule.
     */
    classDescription: "helloxpcom: js version", // any human-readable string
    contractID: "@pinocchio.org/web/socialannoted;1",

    /**
     * List all the interfaces your component supports.
     * @note nsISupports is generated automatically; you don't need to list it.
     */
    QueryInterface: XPCOMUtils.generateQI([Components.interfaces.ihelloxpcom]),

    /*
     * get and set are new Magic in JS1.5, borrowing the intent -- if not
     * the exact syntax -- from the JS2 design.  They define accessors for
     * properties on the JS object, follow the expected rules for prototype
     * delegation, and make a mean cup of coffee.
     */
    multiple: function (a, b) {
        debug("mySample::writeValue => " + aPrefix + this.val + "\n");
    },
};

if (XPCOMUtils.generateNSGetFactory)
    var NSGetFactory = XPCOMUtils.generateNSGetFactory([helloxpcom]);
else
    var NSGetModule = XPCOMUtils.generateNSGetModule([helloxpcom]);
