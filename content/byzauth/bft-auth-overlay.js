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


     //---------------------------------------------------------------
     // INITIALIZATION AND GLOBALS 
     //---------------------------------------------------------------

     // The object giving access to the authentication adapter 
     // and the other related objects 
var gBftauth = null ; 
var gBftprofdir = Components.classes["@mozilla.org/file/directory_service;1"].
   getService(Components.interfaces.nsIProperties).get("ProfD", Components.interfaces.nsIFile).path ; 
var gBftauthsavefile = gBftprofdir + "/bft-auth-state.xml" ; 
var gBftpeers = new Array();
var gMsgComposeParams = null ; 
var gComposeWindow = null; 
var gBftself = null; 
var gBftttl = 30*86400; 
var gBfttgshint = 65; 
var gBftpayload = 100; 
var gBftkeylen = 2048;







     //-----------------------------------------------------------------
     // HELPER FUNCTIONS
     //----------------------------------------------------------------

function sstrip(text) 
{
   var retval = new String(); 
   var strarr = text.split(/\n/m);
   for( var i = 0; i < strarr.length ; i++ ) 
   {
      var line = strarr[i]; 
      line = line.replace( /\r+/g , ' ' );  
      line = line.replace( /\s+/g , ' ' );  
      line = line.replace( /^\s+/g , '' );        
      line = line.replace( /\s+$/g , '' );  
      if( line.length > 0 ) 
         retval += retval.length ? (' ' + line) : line; 
   }
   return retval; 
}




function pprint(text) 
{
   dump( '>>> ' + text + '\n' ) ; 
}



function recursive_print_dom(documentElement , depth) 
{
   var prefix = '\t';
   var childNodes = documentElement.childNodes;
   for( var i = 0; i < depth; i++ ) 
      prefix = prefix + '\t' ; 

   for (var i = 0; i < childNodes.length; i++) {
      var child = childNodes[i];
      pprint( prefix + child + child.className ) ; 
      recursive_print_dom(child, depth + 1 ) ; 
   }
}






	//---------------------------------------------------------------
	// MAILBOX AND LOCAL FOLDER TRAVERSAL 
	// Set of functions to iterate over existing messages.  The idea
	// is to extract the bft-auth messages by going over existing 	
	// set of data 
	//---------------------------------------------------------------
function process_message(header, folder, peers) 
{
        // thanks http://thunderbirddocs.blogspot.com/2005_02_01_thunderbirddocs_archive.html
   var offset = new Object();
   var messageSize = new Object();
   try
   {
      s = folder.getOfflineFileStream(header.messageKey, offset, messageSize);
   }
   catch(e)
   {
      pprint("message: "+e.message);
   }
   
   try
   {
      var stream = Components.classes["@mozilla.org/scriptableinputstream;1"].createInstance(Components.interfaces.nsIScriptableInputStream);
      stream.init(s);
      messagebody = stream.read(header.messageSize);

           // get good peers from outgoing messages i.e. on which 
           // the default identity is the sender
      if( gBftself == BftgetAddress(header.mime2DecodedAuthor) )
      { 
         var thismesgpeers = new Array() ;
         BftgetAddresses( header.ccList, thismesgpeers ) ; 
         BftgetAddresses( header.mime2DecodedRecipients, thismesgpeers ) ; 

         for( var i = 0; i < thismesgpeers.length; i++ )   
            if( peers.indexOf(thismesgpeers[i]) == -1 )
               peers.push( thismesgpeers[i] ) ; 
      }

           
//       enabled_peer_regex = new RegExp("^Bft-Auth-*:") ; 
//       if( enabled_peer_regex.test(messagebody) )
//       {
//          var matches = enabled_peer_regex.exec(messagebody); 
//          capable_peers.push( header.from ) ; 
//       }

           //pprint( messagebody ) ; 
           //pprint( '-------------------------------------------------------------------' ) ; 
   
   }
   catch(e)
   {  
      pprint("message: "+e.message);
   }

}





	
function process_folder(_folder, peers) 
{
   folder = _folder.QueryInterface(Components.interfaces.nsIMsgFolder);
   if(!folder) 
      return ; 

        //pprint( 'entering folder ' + folder.prettiestName) ; 
   if( folder.hasSubFolders ) 
   {
      try 
      {
         var subfolders = folder.GetSubFolders();
         for(subfolders.first(); !subfolders.isDone(); subfolders.next() )
         {
            process_folder(subfolders.currentItem(), peers); 
         }
      }
      catch(e) 
      {
              // commented out because it always throws error
              //pprint( 'exception during recursion, message : ' + e.message) ; 
      }
   }

        // process the messages within the folder
   try 
   {
           //pprint( 'entering messages traversal for ' + folder.prettiestName) ; 

           // ok! the top level object has a msgWindow if we can 
           // sufficiently delay the init

           // pprint( 'check for message window ' + msgWindow )  ;       
      var messages = folder.getMessages(msgWindow) ;
      if(!messages)
         return; 

      while( messages.hasMoreElements() ) 
      {
         var message = messages.getNext().QueryInterface(Components.interfaces.nsIMsgDBHdr);
         if(!message)
            continue; 

         process_message(message, folder, peers); 

              //pprint( 'found message with subject ' + message.mime2DecodedSubject ) ; 
      }
   }
   catch(e) 
   {
           // dont display 
           // pprint( 'exception during message traversal loop message : ' + e.message + '\n' ) ; 
   }
}













/*==================================================
 * RECOVER AUTH MESSAGES ON RECV
 *=================================================
 */

     /*
      * To process message receive events 
      */ 
function bftonRecvMessage(parentItem, item, view)
{
   if( item instanceof Components.interfaces.nsIMsgDBHdr ) 
   {
      var folder = item.folder.QueryInterface(Components.interfaces.nsIMsgFolder) ;
      if( folder.abbreviatedName == "Inbox" ) 
      {
              //pprint( ' in inbox processing ' ) ; 
              //pprint( 'item message id = ' + item.messageId ) ; 
              //pprint( 'item key = ' + item.messageKey ) ; 
              //var mesguri = folder.generateMessageURI(item.messageKey) ; 
         var offset = new Object(); 
         var size = new Object(); 
         var mstr = folder.getOfflineFileStream( item.messageKey, offset, size ) ; 
         

         var factory = Components.classes["@mozilla.org/scriptableinputstream;1"];
         var s = factory.createInstance(Components.interfaces.nsIScriptableInputStream);
         s.init(mstr);
         

         var recoveredMessage = s.read(item.messageSize);
         var sign_message = getSignatureAndMessage(recoveredMessage) ;
         if( sign_message.length == 3 ) 
         {
            var unknown = new Boolean(true);
                 // signed message from authenticated sender
            if( gBftauth.Verify(sign_message[0], 
                                sign_message[1], 
                                sign_message[2],
                                unknown))
            {
               item.setProperty( "Bft-Auth-Signed" , "true" );
               item.setProperty( "Bft-Auth-Verified" , "true" );
               item.setProperty( "Bft-Auth-Valid" , "true" );
               item.markFlagged (true); 
               return ; 
            }

                 // unknown new sender 
            else if( unknown.value ) 
            {
               item.setProperty( "Bft-Auth-Signed" , "true" );
               item.setProperty( "Bft-Auth-Verified" , "false" );
               item.setProperty( "Bft-Auth-Valid" , "unknown" );
               return;
            }

            else
            {
               var tval = new Number(0);
               var pubkey =  gBftauth.getAuthenticatedKey(
                  sign_message[2], tval, unknown) ;

                    // bad message - sender is known and authenticated 
                    // but message is incorrectly signed - need 
                    // to mark as bad
               if( pubkey.length && tval > 0 ) 
               {
                  item.setProperty( "Bft-Auth-Signed" , "true" );
                  item.setProperty( "Bft-Auth-Verified" , "true" );
                  item.setProperty( "Bft-Auth-Valid" , "false" );
                  window.alert( 'malicious or forged message received' ) ; 
                  return; 
               }
            }
         }
      }
   }
}


var bftRecvListener = { 
   OnItemAdded: function (parentItem, item, view) 
   { 
      bftonRecvMessage(parentItem, item, view); 
   },  

   OnItemRemoved: function( parentItem, item, view) {},

   OnItemPropertyChanged: function( item, property, oldValue,newValue) {}, 

   OnItemIntPropertyChanged: function( item, property, oldValue,newValue) {}, 

   OnItemBoolPropertyChanged: function( item, property, oldValue,newValue) {}, 

   OnItemUnicharPropertyChanged: function( item, property, oldValue,newValue) {}, 

   OnItemPropertyFlagChanged: function( item, property, oldFlag,newFlag) {}, 

   OnItemEvent: function(folder, event) {} 
}; 


function getSignatureAndMessage(recoveredMessage) 
{
   var isnix = 1; 
   var boundary = recoveredMessage.indexOf("\n\n"); //marks the end of the //headers
   if( boundary == -1 ) 
   {
      isnix = 0; 
      boundary = recoveredMessage.indexOf("\r\n\r\n");
      if( boundary == -1 )
         return '' ;
   }
 
   var body = recoveredMessage.substring(boundary + 1);
   var hdr = recoveredMessage.substring(0,boundary) ; 
 
        // Get all the fields from the header 
   var fieldvalues = new Array();
   var fieldnames = new Array() ; 
   var fieldregex = new RegExp( /^(\S+)(\s*):(\s*)(.*)$/ ) ;
   var fieldcont = new RegExp( /^(\s+)(.*)$/ ) ; 

   var lines = isnix ? hdr.split(/\n/m) : hdr.split(/\r\n/m) ;
   for( var i = 0; i < lines.length; i++ ) 
   {
      if( fieldregex.test( lines[i] ) ) 
      {
         var fn = fieldnames.length ; 
         fieldnames[fn] = RegExp.$1;
         fieldvalues[fn] = RegExp.$4;
      }
      else if(fieldcont.test( lines[i]) )
      {
         var fn = fieldnames.length - 1;
         if( fn >= 0 ) 
            fieldvalues[fn] += RegExp.$2;
      }
   }

   var bodyStr = sstrip(body) ; 
   var fromStr = new String(); 
   var toStr = new String(); 
   var ccStr = new String(); 
   var subjectStr = new String(); 

   if( fieldnames.indexOf( "From" ) >= 0 ) 
      fromStr = fieldvalues[fieldnames.indexOf( "From" )] ;  

   if( fieldnames.indexOf( "To" ) >= 0 ) 
      toStr = fieldvalues[fieldnames.indexOf( "To" )] ;  

   if( fieldnames.indexOf( "Cc" ) >= 0 ) 
      ccStr = fieldvalues[fieldnames.indexOf( "Cc" )] ;  
   
   if( fieldnames.indexOf( "Subject" ) >= 0 ) 
      subjectStr = fieldvalues[fieldnames.indexOf( "Subject" )] ;  


        // Deliver message to authentication library 
   if( fieldnames.indexOf( "X-Bft-Auth-Data" ) >= 0 ) 
   {
      var message = fieldvalues[fieldnames.indexOf("X-Bft-Auth-Data")];
      message = message.replace( /\s+/ , '' ) ; 
      
      gBftauth.receiveIncomingAuthenticationMessage( 
         BftgetAddress(fromStr) , message ) ; 
   }


   var canonicalmessage =  (fromStr + '\n' + 
                            toStr + '\n' + 
                            ccStr + '\n' + 
                            subjectStr + '\n' + 
                            bodyStr) ; 


   var signature = new String(); 
   if( fieldnames.indexOf( "X-Bft-Auth-Signature" ) >= 0 ) 
      signature = fieldvalues[fieldnames.indexOf( "X-Bft-Auth-Signature" )];   


   var retval = new Array(); 
   retval[0] = canonicalmessage; 
   retval[1] = signature; 
   retval[2] = BftgetAddress(fromStr); 
   return retval; 
}
























/*==================================================
 * ATTACH AUTH MESSAGES ON SEND 
 *=================================================
 */

     /*
      * get the authentication messages from the library and send them out 
      */ 
function bftonSendMessage()
{
   try 
   {
           // attach the byzauth data to outgoing message
      var thismesgrecipients = new Array() ;
      BftgetAddresses( gMsgComposeParams.composeFields.bcc , thismesgrecipients ) ; 
      BftgetAddresses( gMsgComposeParams.composeFields.cc , thismesgrecipients ) ; 
      BftgetAddresses( gMsgComposeParams.composeFields.to , thismesgrecipients ) ; 

      var mesgtoattach = gBftauth.sendOutgoingAuthenticationMessage(thismesgrecipients.length, thismesgrecipients) ;
      var header = "X-Bft-Auth-Data:" ;
      var lines = mesgtoattach.split(/\n/m) ; 
      var ln = 0; 
      for ( ln = 0; ln < lines.length; ln++ ) 
      {
         header += ' ' ;                     // rfc 822 needs whitespace after new line to extend header
         header += lines[ln] + '\n' ;  
      }
      gMsgComposeParams.composeFields.otherRandomHeaders += header;    
      

           // get the signature
      var signablemessage = get_signable_message() ;
      var signature = gBftauth.Sign(signablemessage); 
      header = "X-Bft-Auth-Signature: " + signature + "\n" ; 
      gMsgComposeParams.composeFields.otherRandomHeaders += header;
   }
   catch(e)
   {
      window.alert("exception in bft attach on send message message: "+ e.message);
   }
}


      
function get_signable_message() 
{
   var editorList = gComposeWindow.document.getElementsByTagName("editor");
   var editorElement = editorList.item(0); 
   var editor = editorElement.getEditor(editorElement.contentWindow);
        //pprint( 'editor = ' + editor  + ' type is ' + typeof(editor) ) ; 

   var bodyStr =  sstrip(editor.outputToString ( "text/plain", 0 ));
        //pprint (bodyStr) ;

   var fromStr = gMsgComposeParams.composeFields.from ; 
        //pprint ('from = ' + gMsgComposeParams.composeFields.from ) ; 

   var toStr = gMsgComposeParams.composeFields.to ; 
        //pprint ('to = ' + gMsgComposeParams.composeFields.to ) ; 

   var ccStr = gMsgComposeParams.composeFields.cc ; 
        //pprint ('cc = ' + gMsgComposeParams.composeFields.cc ) ; 

   var subjectStr = gMsgComposeParams.composeFields.subject ; 
        //pprint ('subject = ' + gMsgComposeParams.composeFields.subject ) ; 

   return (fromStr + '\n' + 
           toStr + '\n' + 
           ccStr + '\n' + 
           subjectStr + '\n' + 
           bodyStr) ; 
}







var bftSendObserver = { 
   observe : function(composewindow, topic, data ) 
   {
      composewindow.addEventListener('compose-send-message', bftonSendMessage, true);
      gMsgComposeParams = composewindow.arguments[0].QueryInterface(Components.interfaces.nsIMsgComposeParams) ; 
      gComposeWindow = composewindow; 
   }
};






















function BftAuth_show_contacts() 
{
   window.openDialog( "chrome://pinocchio/content/byzauth/bft-auth-show.xul", 
                      "showmore",
                      "chrome,dialog", gBftauth).focus();
}











function BftAuth_about()
{
   var params = {inn:{enabled:true}, out:null};  
   window.openDialog( "chrome://pinocchio/content/byzauth/bft-auth-about.xul", 
                      "showmore",
                      "chrome,dialog", params).focus();
}













/*==================================================
 * INITIALIZATION 
 *=================================================
 */

/* var bftInitObserver = { 
   observe : function() 
   {
      if(gBftauth == null)
         BftAuthFullInit();
   }
};
*/

function bftMessageUnSelect() 
{
   var tree = document.getElementById("threadTree");
   if(!tree || tree.view.selection.count <= 0)
      document.getElementById( "bft-auth-showmesgstatus" ).setAttribute('disabled','true'); 
}

var gBftAuthSelectedMessageURI = null ; 

var bftMessageSelectedObserver = {
   observe : function(window, mesg, uri)
   {
      document.getElementById( "bft-auth-showmesgstatus").setAttribute('disabled','false'); 
      gBftAuthSelectedMessageURI = uri; 

      var tree = document.getElementById("threadTree");
      if(tree)
         tree.addEventListener('select', bftMessageUnSelect, false);
   } 
};

/* 
function BftAuthInit() 
{
        // Setup event handler to allow loading of message folders for delayed 
        // initialization of byzuaht  
   try 
   {
      var observerService = Components.classes["@mozilla.org/observer-service;1"].getService(Components.interfaces.nsIObserverService);
      observerService.addObserver(bftInitObserver , "defaultInboxLoadedOnStartup" , false);
   }
   catch(ex)
   {
      pprint( 'could not get observer for trapping init' + ex) ; 
   }
}
*/






function BftAuthFullInit() 
{
    if(gBftauth == null)
	  return;
	
        // get access to all mail accounts to traverse all the folders
        // and get access to basic trusted group (as defined by heuristic) 
   try 
   {
      var testfile =  Components.classes["@mozilla.org/file/local;1"].createInstance(Components.interfaces.nsILocalFile); 
      testfile.initWithPath(gBftauthsavefile); 

      var alerted = new Boolean(false)
      var account_manager = Components.classes["@mozilla.org/messenger/account-manager;1"].getService(Components.interfaces.nsIMsgAccountManager);
           // thanks http://split-s.blogspot.com/2005/02/duplicate-message-remover-01.html#comments
           // for explanations 

      
      if(account_manager)
      {
              // detect the canonical self name
         gBftself = account_manager.defaultAccount.defaultIdentity.identityName ; 
         gBftself = BftgetAddress(gBftself) ; 

         for( var i = 0; i < account_manager.allServers.Count(); i++ ) 
         {
            var server = account_manager.allServers.QueryElementAt(i, Components.interfaces.nsIMsgIncomingServer);
            if(!server)
               continue; 
                 // construct the set of recommended bootstrapping
                 // peers for the library if needed
                 //alert( 'checking testfile exists = ' + testfile.exists()) ;
            if(!testfile.exists()) 
            {
               if(!alerted) 
                  window.alert( 'Initializing trusted groups from stored messages' ) ; 
               alerted = true; 
               process_folder(server.rootFolder, gBftpeers);           
            }
         }          
      
      }
   }
   catch(e) 
   {
           // dont show because traversal always gives exception 
           // pprint( 'exception during bft-auth-init :' + e.message); 
   }


        //  Setup event handlers to trap message send events 
   try 
   {
      var observerService = Components.classes["@mozilla.org/observer-service;1"].getService(Components.interfaces.nsIObserverService);
      observerService.addObserver(bftSendObserver , "mail:composeOnSend" , false);

      observerService.addObserver(bftMessageSelectedObserver, "MsgMsgDisplayed", false);
      
      var mailSession = Components.classes["@mozilla.org/messenger/services/session;1"].getService(Components.interfaces.nsIMsgMailSession); 
      var notifyFlags = Components.interfaces.nsIFolderListener.all; 
      mailSession.AddFolderListener( bftRecvListener, notifyFlags); 
           //pprint( 'done adding listeners for send and receive' ) ; 
   }
   catch(ex)
   {
      pprint( 'could not get observer for trapping message send events' + ex) ; 
   }






         // start byzantine authentication adapter plugin 
    try 
    {
       BftAuth_load_global_settings() ;

       gBftauth = Components.classes["@rutgers.edu/XPCOM/ByzauthAdapter;1"].createInstance().QueryInterface(Components.interfaces.IByzantineAuthenticationAdapter);
            //pprint ( 'bftauth created empty object = ' + gBftauth ) ; 


            // initialize the bootstrap set for plugin with peers from the outgoing emails  
       var testfile =  Components.classes["@mozilla.org/file/local;1"].createInstance(Components.interfaces.nsILocalFile); 
       testfile.initWithPath(gBftauthsavefile); 

       if(testfile.exists()) 
       {
          if(!gBftauth.warmStart(gBftauthsavefile, gBftttl, gBfttgshint, gBftpayload))
          {
             if(!gBftauth.coldStart(gBftkeylen, gBftself, gBftpeers.length, gBftpeers, gBftauthsavefile, gBftttl, gBfttgshint, gBftpayload))
                window.alert( 'could not cold start bft-auth as last chance from file = ' + gBftauthsavefile.toString() ) ; 
          }
          pprint ( 'bftauth created : ' + gBftauth ) ; 
       }
       else
       {
          gBftauth.coldStart(gBftkeylen, gBftself, gBftpeers.length, gBftpeers, gBftauthsavefile, gBftttl, gBfttgshint, gBftpayload) ; 
          pprint ( 'bftauth created : ' + gBftauth ) ; 
       }
    }
    catch(ex)
    {
       pprint( 'could not init bftauth for ' + ex.message ) ; 
    }
}


 






function BftAuth_clear()
{
   var testfile =  Components.classes["@mozilla.org/file/local;1"].createInstance(Components.interfaces.nsILocalFile); 
   testfile.initWithPath(gBftauthsavefile); 
   if(testfile.exists()) 
      testfile.remove(); 
   window.alert( 'State cleared' ) ; 
}





function BftAuth_show_mesgstatus_frompopup(event)
{
	pprint( 'event = ' + event ) ; 
	var t = event.originalTarget;
	
	if (t.localName == "menuitem") 
	{
		var tree = document.getElementById("threadTree");
	   var row = new Object;
      var col = new Object;
      var child = new Object;
	      // figure out what cell the click was in
   	tree.treeBoxObject.getCellAt(event.clientX, event.clientY, row, col, child);
   	pprint( 'row = ' + row.value + ' col = ' + col.value + 'child = ' + child.value ) ;
      if (row.value == -1)
       	return;
	
		var view = GetDBView();
		gBftAuthSelectedMessageURI = view.getURIForViewIndex(row.value); 
		return BftAuth_show_mesgstatus(); 	
	}
}




function BftAuth_show_mesgstatus()
{
   var view = GetDBView();
   if( view.numSelected == 0 ) 
      return; 

   var item = messenger.messageServiceFromURI(gBftAuthSelectedMessageURI).messageURIToMsgHdr(gBftAuthSelectedMessageURI);
   if( item instanceof Components.interfaces.nsIMsgDBHdr ) 
   {
      var signed =  item.getProperty ( "Bft-Auth-Signed" ) ; 
      if( signed == '' ) 
         signed = "false" ; 
      var verified =  item.getProperty(  "Bft-Auth-Verified" ) ; 
      if( verified == '' ) 
         verified = "false" ; 
      var valid = item.getProperty( "Bft-Auth-Valid" ) ; 
      if( valid == '' ) 
         valid = false; 
      window.openDialog( "chrome://pinocchio/content/byzauth/bft-auth-showmesgstatus.xul", 
                         "showmore",
                         "chrome,dialog", signed, verified, valid).focus();      
   }
}







function BftAuth_Settings() 
{
   BftAuth_load_global_settings(); 

   var params = {
      ttl : gBftttl , 
      tgs : gBfttgshint , 
      payload : gBftpayload, 
      keylen : gBftkeylen, 
      out_ttl : {} , 
      out_tgs : {} , 
      out_payload : {} , 
      out_keylen : {} ,
      out : {} 
   }; 

   window.openDialog( "chrome://pinocchio/content/byzauth/bft-auth-settings.xul", 
                      "showmore",
                      "chrome,dialog,modal,resizable=yes", params ).focus();
   if (params.out) 
   {
      gBftttl = new Number(params.out.ttl); 
      gBfttgshint = new Number(params.out.tgs); 
      gBftpayload = new Number(params.out.payload); 
      gBftkeylen = new Number(params.out.keylen);

      BftAuth_save_global_settings();
   }

   return params.out; ;
}








function BftAuth_save_global_settings()  
{
   try
   {
      var file = Components.classes["@mozilla.org/file/local;1"].createInstance(Components.interfaces.nsILocalFile).
         QueryInterface(Components.interfaces.nsIFile);

      file.initWithPath( gBftprofdir + '/BftAuthSettings.txt' );

      if( file.exists() == true ) 
         file.remove( false );

      var strm = Components.classes["@mozilla.org/network/file-output-stream;1"].createInstance(Components.interfaces.nsIFileOutputStream).
         QueryInterface(Components.interfaces.nsIOutputStream);

      strm.init( file, 0x04 | 0x08 | 0x20, 420, 0 );

      var settings = 'gBftttl=' + gBftttl + '\n' ; 
      settings += 'gBfttgshint=' + gBfttgshint + '\n' ; 
      settings += 'gBftpayload=' + gBftpayload + '\n' ; 
      settings += 'gBftkeylen=' + gBftkeylen + '\n' ; 

      strm.write( settings, settings.length );
      strm.flush();
      strm.close();
   }
   catch(ex)
   {
      window.alert(ex.message);
   }
}








function BftAuth_load_global_settings() 
{
   try
   {
      pprint( 'starting file read' ) ; 

      var file = Components.classes["@mozilla.org/file/local;1"].createInstance(Components.interfaces.nsILocalFile).
         QueryInterface(Components.interfaces.nsIFile);

      file.initWithPath( gBftprofdir + '/BftAuthSettings.txt' );

      if( file.exists() == false ) 
      {
              //alert( 'file doesnt exist, returning from load global settings' ) ; 
         return ;
      }

      var stream = Components.classes["@mozilla.org/network/file-input-stream;1"].createInstance(Components.interfaces.nsIFileInputStream).
         QueryInterface(Components.interfaces.nsILineInputStream);

      stream.init( file,  0x04, 420, 0 );

      var rttl = new RegExp( /^gBftttl=(\d*)$/ ) ; 
      var rtgs = new RegExp( /^gBfttgshint=(\d*)$/ ) ; 
      var rpayload = new RegExp( /^gBftpayload=(\d*)$/ ) ; 
      var rkeylen = new RegExp( /^gBftkeylen=(\d*)$/ ) ; 
      while( true ) 
      {
         var line = {} ; 
         if(!stream.readLine(line)) 
            break; 
         else
            line = line.value; 

         if( rttl.test(line) ) 
            gBftttl = RegExp.$1; 

         else if( rtgs.test(line) ) 
            gBfttgshint = RegExp.$1;

         else if( rpayload.test(line) ) 
            gBftpayload = RegExp.$1;

         else if( rkeylen.test(line) ) 
            gBftkeylen = RegExp.$1;
      }
   }
   catch(ex)
   {
      window.alert(ex.message);
   }
}








/*==================================================
 * TODO  
 *=================================================
 */
// use rdf for settings 

///////////////////////////////////////
// TODO 
// function analyzeFolderForJunk()
// {
//   MsgJunkMailInfo(true);
//      var view = GetDBView();

//   // need to expand all threads, so we analyze everything
//   view.doCommand(nsMsgViewCommandType.expandAll);

//   var treeView = view.QueryInterface(Components.interfaces.nsITreeView);
//   var count = treeView.rowCount;
//   if (!count)
//     return;

//   var messages = new Array(count)
//   for (var i = 0; i < count; i++) {
//     try
//     {
//       messages[i] = view.getURIForViewIndex(i);
//     }
//     catch (ex) {} // blow off errors here - dummy headers will fail
//   }
//   analyzeMessages(messages);
// }

// not used yet, but soon
//function analyzeMessagesForJunk()
//{
 // var messages = GetSelectedMessages();
//"mailCommands.js" 734 lines --85%--                        

// var sendListener = { 
//    onGetDraftFolderURL  : function (folderURI) {} , 
//    onProgress           : function (msgID, progress, progressMax) {} , 
//    onSendNotPerformed   : function (msgID, status) {} , 
//    onStartSending       : function (msgID, msgSize) {} , 
//    onStatus             : function (msgID, msg) {} , 
//    onStopSending        : function (msgID, status, msg, returnFileSpec ) {} 
// } ; 


// function BftAuth_share_spam_fingerprints()
// {
// }

   
        //var ds = Components.classes['@mozilla.org/rdf/datasource;1?name=local-store'].createInstance(); 
        //ds = ds.QueryInterface(Components.interfaces.nsIRDFDataSource);
