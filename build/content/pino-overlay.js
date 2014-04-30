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

var pino = {

	utils: {
		get_current_window : function() {
			var manager = Components.classes["@mozilla.org/appshell/window-mediator;1"].getService();
			var intf = manager.QueryInterface(Components.interfaces.nsIWindowMediator);
			var cwin = intf.getMostRecentWindow( "navigator:browser");
			return cwin;
		}
	},

	sidebar: {
		onLoad: function () {
			Components.utils.reportError("Loading sidebar ...");
			// Get URL and Send Query Comment Request
		}, 

		onUnload: function () {
		},

		show: function () {
			pino.utils.get_current_window().toggleSidebar('viewPinoSidebar', false);
		},

		close: function () {
			toggleSidebar('viewPinoSidebar');
		}
	},

};
