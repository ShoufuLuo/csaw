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

var gBftauth = window.arguments[0];
var gTrustInfo = new Array () ; 


function  doBftShowOK()
{
   return true;
}



function trust_cmp(l , r) 
{
   if( l.pubkey.length != r.pubkey.length ) 
      return l.pubkey.length > r.pubkey.length ? -1 : 1; 
   if( l.tval != r.tval ) 
      return l.tval > r.tval ? -1 : 1 ; 
   if(l.peername.toLowerCase() != r.peername.toLowerCase()) 
      return (l.peername.toLowerCase() < r.peername.toLowerCase()) ? -1 : +1 ;
   return 0;
}




function populate_trusted_info()
{
   if( gTrustInfo.length > 0 ) 
      gTrustInfo.splice( 0, gTrustInfo.length ) ; 

   var count = {};
   var trusted = gBftauth.getTrusted(count);
   var pcount = {};
   var probationary = gBftauth.getProbationary(pcount);  
   var ucount = {};
   var untrusted =  gBftauth.getUntrusted(ucount); 

   var dupallpeers = null ; 
   if( ucount.value > 0 && pcount.value > 0 ) 
      dupallpeers = trusted.concat( probationary.concat(untrusted) ) ; 
   else if( pcount.value > 0 ) 
      dupallpeers = trusted.concat( probationary ) ; 

   //alert( 'got final length = ' + dupallpeers.length ) ; 

   var allpeers = new Array(); 
   dupallpeers.sort(); 
   allpeers[0] = dupallpeers[0] ; 
   for( var i = 1, j  = 0, len = dupallpeers.length; i < len; ++i ) 
      if( dupallpeers[i] != allpeers[j] )
      {
         allpeers[++j] = dupallpeers[i] ; 
      } 
   //alert( 'got unique final length = ' + allpeers.length ) ; 

   var modregex = new RegExp( /\<modulus.*\>\s*\<hex\>([\w\d]*)\<\/hex\>\s*\<\/modulus\>/ ) ;
   var expregex = new RegExp( /\<exponent.*\>\s*\<hex\>([\w\d]*)\<\/hex\>\s*\<\/exponent\>/ ) ; 
   for( i = 0; i < allpeers.length; i++ ) 
   {
      var info = new Object(); 
      info.peername = allpeers[i]; 
      var tval = {}; 
      var unknown = {};
      info.pubkey = gBftauth.getAuthenticatedKey(info.peername, tval, unknown) ; 
      info.tval = tval.value; 
      info.unknown = unknown.value;

      if( info.pubkey == null ) 
         info.pubkey = new String() ; 
      else
      {
         var modulus = new String(); 
         var exponent = new String(); 
         info.unknown = false; 
         info.pubkey = info.pubkey.replace( /\n+/gm , '' );
         info.pubkey = info.pubkey.replace( /\r+/gm , '' );

         if( modregex.test( info.pubkey ) ) 
            modulus = RegExp.$1 ; 
         if( expregex.test( info.pubkey ) )
            exponent =  RegExp.$1 ; 
              //dump( 'exponent = ' + exponent + '\n' ) ; 
              //dump( 'modulus = ' + modulus + '\n' ) ; 
         info.pubkey = exponent + ';' + modulus;        
              //<modulus class_id="4" tracking_level="1" version="0" object_id="_1">
              //         <hex>5ca34211f3503638587aa4c4dc391</hex>
              //  </modulus>
              //  <exponent object_id="_2">
              //          <hex>4fbca7cdd86b91d</hex>
              //  </exponent>

         info.authenticators = new String() ; 
         if( info.pubkey.length > 0 ) 
         {  
            var acount = {} ; 
            var authenticators = gBftauth.getAuthenticators(info.peername, acount);
            for( j = 0; j < authenticators.length; j++ )
               info.authenticators = info.authenticators + "," + authenticators[j] ; 
         }

      }

      gTrustInfo[i] = info; 
   }

   gTrustInfo = gTrustInfo.sort( trust_cmp ) ; 

   return gTrustInfo.length ; 
}




var treeView = {
   treebox : null, 
   selection : null, 
   rowCount : populate_trusted_info() ,
   getCellText : function(row,column) {
      if (column.id =="peer") 
         return gTrustInfo[row].peername ; 
      else if(column.id == "pubkey") 
         return gTrustInfo[row].pubkey ; 
      else if(column.id == "trustvalue") 
         return gTrustInfo[row].tval ; 
      else if(column.id == "authenticators" ) 
         return gTrustInfo[row].authenticators; 
   },
   setTree: function(treebox){ this.treebox=treebox; },
   isContainer: function(row){ return false; },
   isSeparator: function(row){ return false; },
   isSorted: function(row){ return false; },
   getLevel: function(row){ return 0; },
   getImageSrc: function(row,col){ return null; },
   getRowProperties: function(row,props){},
   getCellProperties: function(row,col,props){},
   getColumnProperties: function(colid,col,props){} ,
   refreshData : function() { 
      rowCount = populate_trusted_info(); 
   }
};




function setBftShowView() 
{
   if (treeView.treebox)
      treeView.treebox.invalidate(); 
   treeView.refreshData(); 
   document.getElementById('bft-auth-trusted-tree').view=treeView;
}






function getSelectedList() 
{
   var selected = new Array();
   var selection = document.getElementById('bft-auth-trusted-tree').view.selection ; 
   if( selection.single ) 
   {
      selected[0] = selection.currentIndex ; 
   }
   else
   {  
      var treeview = document.getElementById('bft-auth-trusted-tree').view ; 
      for( i = 0; i < treeview.rowCount; i++ )  
         if( selection.isSelected(i) ) 
            selected[ selected.length ] = i ; 
   }
   return selected; 
}


     // Trust explicitly, override the decisions of authenetication 
function OnMakeTrusted()
{
   var selected = getSelectedList() ; 
   for( var i = 0; i < selected.length; i++ ) 
   {
      var peer = gTrustInfo[selected[i]].peername ;
      if( peer ) 
         gBftauth.setTrusted (peer) ; 
   }
   return setBftShowView();
}



     // Untrust explicitly override decision of authentication 
function OnMakeUntrusted()
{
   var selected = getSelectedList() ; 
   for( var i = 0; i < selected.length; i++ ) 
   {
      var peer = gTrustInfo[selected[i]].peername ;
      if( peer ) 
         gBftauth.setUntrusted (peer) ; 
   }
   return setBftShowView();
}



     // Make it probationary once again 
     // reauthenticate the peer 
function OnReAuthenticate()
{
   var selected = getSelectedList() ; 
   for( var i = 0; i < selected.length; i++ ) 
   {
      var peer = gTrustInfo[selected[i]].peername ;
      if( peer ) 
         gBftauth.setProbationary (peer) ; 
   }
   return setBftShowView();
}
