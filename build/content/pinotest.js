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

Components.utils.import("resource://gre/modules/NetUtil.jsm");
Components.utils.import("resource://gre/modules/FileUtils.jsm");

var fbAuthURL = 'https://www.facebook.com/dialog/oauth?';
var redirectURL = 'https://www.facebook.com/connect/login_success.html';
var responseType = 'token';
var pinocchioID = "232949870104101";

var facebook_id = "";
var facebook_name = "Shoufu Luo";
var current_username = "luoshoufu";
var access_token = "";
var initialized = 0;

var cookies =
{
    
    // Detect status/cookie
    getCookie: function()
    {
	var cookie;
	
        try {
            var ios = Components.classes["@mozilla.org/network/io-service;1"]
                                    .getService(Components.interfaces.nsIIOService);
            var uri = ios.newURI(redirectURL, null, null);
	    var cookieSvc = Components.classes["@mozilla.org/cookieService;1"]
	                            .getService(Components.interfaces.nsICookieService);
            cookie = cookieSvc.getCookieString(uri, null);
        } catch (errorInfo) {
            alert(errorInfo);
        }
	return cookie;
    },

	showCookie: function()
	{
        try {
            var ios = Components.classes["@mozilla.org/network/io-service;1"]
                                    .getService(Components.interfaces.nsIIOService);
            var uri = ios.newURI(redirectURL, null, null);
	    	var cookieSvc = Components.classes["@mozilla.org/cookieService;1"]
	                            .getService(Components.interfaces.nsICookieService);
            var cookie = cookieSvc.getCookieString(uri, null);
			var params = cookie.split(';');	
			for (var i = 0; i < params.length; i++) {
				Components.utils.reportError(params[i]);
			//	var sparam = params[i];
			//	var keyval = sparam.split('=');
				
			//	if (keyval[0].indexOf("access_token") == 0) {
			//		access_token = keyval[1];
			//	}
			}
        } catch (errorInfo) {
            alert(errorInfo);
        }
		
	},

    setCookie: function(cookieval)
    {
	 try {
            var ios = Components.classes["@mozilla.org/network/io-service;1"]
                                    .getService(Components.interfaces.nsIIOService);
            var uri = ios.newURI(redirectURL, null, null);
    
	    var cookieSvc = Components.classes["@mozilla.org/cookieService;1"]
	                                .getService(Components.interfaces.nsICookieService);
            cookieSvc.setCookieString(uri, null, cookieval, null)
	    var cookie = cookieSvc.getCookieString(uri, null);
	    
        } catch (errorInfo) {
            alert(errorInfo);
        }
    },

	extractValueFromSetCookie: function (setcookie, start, key) 
	{
		var lines = setcookie.split('\n');

		for (var i = 0; i < lines.length; i++) {
			//alert("line [" + i + "]: " + lines[i]);
			var params = lines[i].split(';');	
			if (params[0].toLowerCase().indexOf(start.toLowerCase()) != 0)
				continue;
			for (var j = 0; j < params.length; j++) {
				var keyval = params[j].split('=');
				//alert("key: " + keyval[0] + "  value: " + keyval[1]);
				if (keyval[0].toLowerCase == key.toLowerCase)
					return keyval[1];
			}
		}
		return "";
	}
}

	
var httpObserver =
{
    observeActivity: function(aHttpChannel, aActivityType, aActivitySubtype, aTimestamp, aExtraSizeData, aExtraStringData)
    {	    
	var nsIHttpActivityObserver = Components.interfaces.nsIHttpActivityObserver;
	
	if (aActivityType == nsIHttpActivityObserver.ACTIVITY_TYPE_HTTP_TRANSACTION)
	{
	    switch(aActivitySubtype)
	    {
		case nsIHttpActivityObserver.ACTIVITY_SUBTYPE_REQUEST_HEADER:
			Components.utils.reportError(aTimestamp + "  type: " + aActivitySubtype + " \n" + aExtraStringData + " (" + aExtraSizeData + ")");
		case nsIHttpActivityObserver.ACTIVITY_SUBTYPE_REQUEST_BODY_SENT:
			break;
		case nsIHttpActivityObserver.ACTIVITY_SUBTYPE_RESPONSE_HEADER:
			Components.utils.reportError(aTimestamp + "  type: " + aActivitySubtype + " \n" + aExtraStringData + " (" + aExtraSizeData + ")");
		// received response header
		// window.alert(aExtraStringData);
		
		    var location_idx = aExtraStringData.indexOf(redirectURL);
		    if (location_idx == -1)
		        break;
		    var location = aExtraStringData.substring(location_idx);
		    var token_idx = location.indexOf("access_token=");
		    var atoken = location.substring(token_idx);		    
		    var lines = atoken.split("\n");
		    var params = lines[0].split('&'); // we only care about firt line (Token)
		    
		    cookies.setCookie(params[0]);
		    cookies.setCookie(params[1]);
			break;
		case nsIHttpActivityObserver.ACTIVITY_SUBTYPE_RESPONSE_COMPLETE:
			// received complete HTTP response
			break;
	    }
	}
    }
}

var pinotest =
{
	start: function() {
		neww = window.open("chrome://pinocchio/content/pinotest.xul", 
			"Pinocchio", "toolbar=1, location=1, status=1, menubar=1, resizable=1, width=400, height=300");
		neww.moveTo(100, 100);
	},
	
    get_fb_whoami: function ()
    {
			var httpRequest;
			
			if (window.XMLHttpRequest) { // Mozilla, Safari, ...  
				httpRequest = new XMLHttpRequest();  
			} else {
				window.alert("Unable Send Http Resuest!");
			}
			if (!httpRequest) {
				window.alert("Give Up. Cannot create Http Request!");
				return;
			}
	
			httpRequest.onreadystatechange = 
				function () {  
						if (httpRequest.readyState == 4)
						{
							if (httpRequest.status == 200) {
								var response = JSON.parse(httpRequest.responseText);
								current_username = response.username;
								facebook_name = response.name;
								facebook_id = response.id;
								document.getElementById("pino-headpic").setAttribute('src',
									'https://graph.facebook.com/' + current_username + '/picture');
							} else {
								alert(httpRequest.status);
							}
						} else {
							// waiting
						}
				};
			
			httpRequest.open('GET', 'https://graph.facebook.com/me?fields=id,name,username&access_token=' + access_token, true);  
			httpRequest.send(null);
    },
    
    // initial function when mian window is loaded
    load: function()
    {
		if (initialized == 1)
			return;

		initialized = 1;
		var activityDistributor = Components.classes["@mozilla.org/network/http-activity-distributor;1"]
										.getService(Components.interfaces.nsIHttpActivityDistributor);
		activityDistributor.addObserver(httpObserver);

		// TODO:
		// 	1. detect cookie/status for facebook.com
		//	2. if exists, autologin and show profile picture and some comments for friends
		//	3. if not, show facebook login button and some lastest comments
	
		var cookie = cookies.getCookie();

		if (cookie != null) {
			var params = cookie.split(';');	


			for (var i = 0; i < params.length; i++) {
				Components.utils.reportError(params[i]);
				var sparam = params[i];
				var keyval = sparam.split('=');
				
				if (keyval[0].indexOf("access_token") == 0) {
					access_token = keyval[1];
				}
			}
		}

		var pinohead = document.getElementById("pino-headerline");
		var elem;
			
		if (access_token == "") {
			elem = document.createElement("button");
			elem.setAttribute('oncommand', 'pinotest.fb_req_signon()')
			elem.setAttribute('id', 'pino-button-login');
			var logintxt = document.createTextNode("login");
			elem.appendChild(logintxt);

			var elem2 = document.createElement("button");
			elem2.setAttribute('oncommand', 'cookies.showCookie()');
			elem2.setAttribute('id', 'pino-button-login');
			var logintxt = document.createTextNode("login_open");
			elem2.appendChild(logintxt);
        	pinohead.appendChild(elem2);
		} else {
			// FIXME : Check Expired time???
			pinotest.get_fb_whoami();
			elem = document.createElement("image");
			elem.setAttribute('id', 'pino-headpic');
			//elem.setAttribute('src', 'https://graph.facebook.com/' + current_username + '/picture');
			var logintxt = document.createTextNode("Image");
			elem.appendChild(logintxt);
		}
        pinohead.appendChild(elem);
    },

	fb_signon: function(refer, next_url)
	{
			var httpRequest;
			
			if (window.XMLHttpRequest) { // Mozilla, Safari, ...  
				httpRequest = new XMLHttpRequest();  
			} else {
				window.alert("Unable Send Http Resuest!");
			}
			if (!httpRequest) {
				window.alert("Give Up. Cannot create Http Request!");
				return;
			}
	
			httpRequest.onreadystatechange = 
				function () {  
				    if (httpRequest.readyState == 4)
				    {
							if (httpRequest.status == 200) {
								alert("Yes, Success!");
								Components.utils.reportError(httpRequest.getAllResponseHeaders());	
							}
				    }
				};
			
			var url = 'https://www.facebook.com/login.php?login_attempt=1&fbconnect=1&display=page&' + next_url + '&legacy_return=1';
		   Components.utils.reportError('Post to [' + url + ']');	


			httpRequest.setRequestHeader('Referer', refer);
			httpRequest.open('POST', url, true);  
			httpRequest.send();
	},

	fb_req_signon: function() 
	{
			var httpRequest;
			
			if (window.XMLHttpRequest) { // Mozilla, Safari, ...  
				httpRequest = new XMLHttpRequest();  
			} else {
				window.alert("Unable Send Http Resuest!");
			}
			if (!httpRequest) {
				window.alert("Give Up. Cannot create Http Request!");
				return;
			}
	
			httpRequest.onreadystatechange = 
				function () {  
						if (httpRequest.readyState == 4)
						{
							if (httpRequest.status == 200) {
									alert("OK!----->");
									var setcookie = httpRequest.getResponseHeader("Set-Cookie");
									var fbref = cookies.extractValueFromSetCookie(setcookie, "reg_fb_ref", "reg_fb_ref");
									//alert(setcookie.search("/reg_fb_ref=/i"));
									//var fbref = setcookie.substr(setcookie.search("/reg_fb_ref=/i"));
									if (fbref == "") 
										alert("Error: no reg_fb_gate parameter!");
									//alert("reg_fb_ref=" + fbref);
									var nextidx = fbref.indexOf("%26next%3D");
									var next_url = fbref.substr(nextidx + 10);
									if (next_url == null)
										alert("Error: no next= parameter");
									Components.utils.reportError("next url:\n" + next_url);
									pinotest.fb_signon(fbref, "next=" + next_url);
							} else {
								alert("Status:" + httpRequest.status);
							}
						} else {
							// waiting
						}
				};
			
			var queryParams = ['client_id=' + pinocchioID, 'redirect_uri=' + redirectURL, 'response_type=' + responseType];
			var url = fbAuthURL + queryParams.join('&');

			httpRequest.open('GET', url, true);  
			httpRequest.send(null);
	},

    // login to Facebook
    fb_auth: function()
    {
        var queryParams = ['client_id=' + pinocchioID, 'redirect_uri=' + redirectURL, 'response_type=' + responseType];
        var url = fbAuthURL + queryParams.join('&');

		// FIXME: we need customize this window
		window.open(url);
    },

    // Show comments in the Pinocchio Main Window
    showComments: function()
    {
        var pinocomments = document.getElementById("pino-comments");
        var newcmmt = document.createElement("div");
        var cmmt = document.createTextNode("- Stranger: Hey buddy, it's a good website!");
        
        newcmmt.appendChild(cmmt);
        pinocomments.appendChild(newcmmt);
    },

    // Show comments from friends in the Pinocchio Main Window
    showSelectedComments: function()
    {
        var pinocomments = document.getElementById("pino-comments");
        var newcmmt = document.createElement("div");
        var cmmt = document.createTextNode("- Bill Gates: Do you know what WWW stands for? Welcome to Windows World!");
        
        newcmmt.appendChild(cmmt);
        pinocomments.appendChild(newcmmt);

alert("To show hello OSN API");
	hello_twitter();
    },

    // test function
    addComment: function()
    {
        var pinocomments = document.getElementById("pino-comments");
        var newcmmt = document.createElement("div");
        var cmmt = document.createTextNode("- Jobs Steve: Hey buddy, MacBook is better!");
	        
        newcmmt.appendChild(cmmt);
        pinocomments.appendChild(newcmmt);


	alert("WE are going to call xpcom.\n");

        var hpino = Components.classes["@pinocchio.com/XPCOM/Demo;1"].createInstance();
       	hpino = hpino.QueryInterface(Components.interfaces.ihelloxpcom);
        var uri = hpino.multiple(24, 20);

	alert("Answer:" + uri);
	
	alert("To show hello OSN API");
	hello_facebook();
	
    }
}

function hello_facebook() {
    try {
	alert("yes, it is facebook!");
        var myComponent = Components.classes['@pinocchio.com/OSNAPI/Facebook;1']  
                                    .createInstance(Components.interfaces.iOSNAPI);  
  
        alert(myComponent.helloOSNAPI());  
    } catch (anError) {  
        dump("ERROR: " + anError);  
    }
}

function hello_twitter() {
    try {
	alert("yes, it is twitter!");
        var myComponent = Components.classes['@pinocchio.com/OSNAPI/Twitter;1']  
                                    .createInstance(Components.interfaces.iOSNAPI);  
  
        alert(myComponent.helloOSNAPI());  
    } catch (anError) {  
        dump("ERROR: " + anError);  
    }
}
