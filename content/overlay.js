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

var gP2POverlayNetwok = null;

var PinoInitObserver = { 
   observe : function() 
   {
        //BftAuthFullInit();
		alert("init called\n");
   }
};

function P2PInit()
{
	try {
		gP2POverlayNetwork = Components.classes["@ucsb.edu/XPCOM/ChimeraRider;1"].createInstance().QueryInterface(Components.interfaces.iChimeraRider);
	} catch (e) {
		pprint("Peer-to-peer: " + e.message);
	}
};

function pinocchio_init()
{
	try {
		P2PInit();
//		var pinoService = Components.classes["@mozilla.org/observer-service;1"].getService(Components.interfaces.nsIObserverService);
//		pinoService.addObserver(PinoInitObserver, "defaultInboxLoadedOnStartup" , false);
	} catch(ex) {
			pprint( 'could not get observer for trapping init' + ex) ; 
	}
};

function pprint(text) 
{
   dump( '>>> ' + text + '\n' ) ; 
}

var pinocchio = 
{
	
	onLoad: function(event) {
    		this.initialized = true;

		var comments = ["A good school!", "Always sunny. Sometimes, rainy. Good weather, good place, and good poeple.Good weather, good place, and good poeple.Good weather, good place, and good poeple End.",
				"Good weather, good place, and good poeple.",
				"Too many bars and cars", "When you can to U.S., you can fly to seattle and transfer to New Jersy."];

		for (var i = 0; i < comments.length; i++)
			pinocchio.insertComment(comments[i]);
		
		/*var panel_vbox = document.createElement("container");
		panel_vbox.setAttribute("flex", "1");
		panel_vbox.style.overflowY = "auto";
		panel_vbox.style.overflowX = "auto";
		
		if (panel_vbox.clientHeight > panel.clientHeight) {
			panel_vbox.setAttribute("maxheight", panel.clientHeight - 50);
			panel_vbox.setAttribute("width", panel_vbox.clientWidth + 40);
		}*/
  	},
	
	start: function() {
		neww = window.open("chrome://pinocchio/content/pino.xul", 
			"Pinocchio", "resizable=0, menubar=1, width=400, height=300");
		neww.moveTo(100, 100);
	},
	
	insertComment: function (cmmt) {

		var showsection = document.getElementById("comment-list");
		var icon_url =  "chrome://pinocchio/skin/prof.png";

		var cmtbox = document.createElement("hbox");
		
		var usrimg = document.createElement("image");
		usrimg.setAttribute("src",icon_url);
		usrimg.setAttribute("height", "48px");
		usrimg.setAttribute("width", "48px");
		cmtbox.appendChild(usrimg);

		var hspacer = document.createElement("spacer");
		hspacer.setAttribute("width", "20px");
		cmtbox.appendChild(hspacer);

	/*	var rtbox = document.createElement("vbox");
		rtbox.setAttribute("width", "300px");
		var usrcmt = document.createElement("description");
		usrcmt.setAttribute("width", "300px");
		usrcmt.setAttribute("value", cmmt);
		rtbox.appendChild(usrcmt);
		var cmtimg = document.createElement("image");
		cmtimg.setAttribute("src", "chrome://pinocchio/skin/icon_small.png");
		rtbox.appendChild(cmtimg);
		cmtbox.appendChild(rtbox);
	*/

		var usrtxt = document.createElement("textbox");
		usrtxt.setAttribute("width", "300px");
		usrtxt.setAttribute("multiline", "true");
		usrtxt.setAttribute("readonly", "true");
		usrtxt.setAttribute("style", "overflow: hidden");
		usrtxt.setAttribute("flex","5");
		/*if(document.getElementById('thebox').value.length > document.getElementById('thebox').cols){
			colss=document.getElementById('thebox').value.length;
			usrtxt.setAttribute("cols",colss);
		}*/
		
		usrtxt.setAttribute("class", "plain");
		usrtxt.setAttribute("style","color: #F0F8FF");
		usrtxt.setAttribute("value", cmmt);
		cmtbox.appendChild(usrtxt);
		
		showsection.appendChild(cmtbox);

		var vspacer = document.createElement("spacer");
		vspacer.setAttribute("height", "10px");
		showsection.appendChild(vspacer);
	},

	getInput: function() { 
		var inputbox = document.getElementById("cmmt-box");
		var comment = inputbox.value.replace(new RegExp("^[ \t\r\n]+", "g"), "");
		comment = comment.replace(new RegExp("^[ \t\n\r]+$", "g"), "");
		if (comment == "") {
			//var hint = document.getElementById("cmmt-hint");
			//hint.setAttribute("value", "You cannot submit an empty comment!");
			alert("You cannot submit blank!\n");
			return;
		}
	 
	 	try {
			gP2POverlayNetwork.sendpkt("vpathak@stevens.edu", comment.length, comment);
				
		} catch (e) {
			pprint("Error" + e.message);	
		}

		pinocchio.insertComment(comment);
		inputbox.reset();
	}
};


