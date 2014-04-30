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
 */

#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include "PinoPacket.h"
#include "PinoStoreCenter.h"

/*
 * _ONLY_ for a complete packet stream
 *
 * Used to construct a PinoPacket from the packet stream we received, 
 * so that, we can call member functions, such as getComent(), getComments()
 * to parse the pino packet (we received) and get what we want, 
 & like Comment(s) in PostCommentReq(QueryCommentResp) 
 * and Parameters of QueryCommentReq
 *
 */

PinoPacket::PinoPacket(char* pPkt, int len)
{
	if (*pPkt++ != VERSION || len < 4) 
	{
		cout << "PinoPacket: unmatched version! " << endl; /* FIXME : Error */
	}

	m_type = *pPkt++;
	pkt_stream = pkt;
	//buildPacket(pkt_type, pkt_body, body_len);
}

PinoPacket::PinoPacket(char type, string url) //Query Comment
{
	string  pkt_body = "";
	unsigned char body_type;
	int	body_len = 0;
        string body_val;
	list<PinoField> fields;
    
	if (type != QueryCommentReq) {
		/* Error! */
		cout << "Packet type does not match!" << endl;
	}    
	/* TODO */
        if (url.empty()) {
		/* Error */
		cout << "URL is empty!" << endl;
	}

        type = QueryCommentResp;
	body_type = FIELD_TYPE_URL;  // url
	body_val = url;
	PinoField pfld(body_type, body_len, body_val);
        fields.push_back(pfld);   

	pkt_body += buildPacketBody(fields);
	body_len += getPacketBodyLen(pkt_body);
        buildPacket(pkt_type, pkt_body, body_len);
}

//??
PinoPacket::PinoPacket(char type, PinoComment cmmt)  //Post Comment
{

	/* TODO */
        string  pkt_body = "";
	int	body_len = 0;
	list<PinoField> fields = getFieldList(cmmt);
        
	if (type != PostCommentReq) {	
             /* Error! */
		cout << "Packet type does not match!" << endl;
	}

	pkt_type = PostCommentReq;
	pkt_body = buildPacketBody(fields);
	body_len = getPacketBodyLen(pkt_body);
	buildPacket(pkt_type, pkt_body, body_len);    
}

PinoPacket::PinoPacket(char type, string url, string author, string content)   //Post Comment
{

	/* TODO */
        string  pkt_body = "";
	int	body_len = 0;
        
	if (type != PostCommentReq) {	
             /* Error! */
		cout << "Packet type does not match!" << endl;
	}
       
	if (url.empty()) {
		/* Error */
		cout << "URL is empty!" << endl;
	}

	if (author.empty()) {
		/* Error */
		cout << "AUTHOR is empty!" << endl;
	}

	if (content.empty()) {
		/* Error */
		cout << "CONTENT is empty!" << endl;
	}
	
	PinoComment cmmt(url, author, content);
	list<PinoField> fields = getFieldList(cmmt);
	pkt_type = PostCommentReq;
	pkt_body = buildPacketBody(fields);
	body_len = getPacketBodyLen(pkt_body);
	buildPacket(pkt_type, pkt_body, body_len);    
}

PinoPacket::PinoPacket(char type, list<PinoField> fields) //Post Comment
{
	string  pkt_body = "";
	int	body_len = 0;

	if (type != PostCommentReq) {	
             /* Error! */
		cout << "Packet type does not match!" << endl;
	}

	pkt_type = PostCommentReq;
	pkt_body = buildPacketBody(fields);
	body_len = getPacketBodyLen(pkt_body);
	buildPacket(pkt_type, pkt_body, body_len);
}



PinoPacket::PinoPacket(char type, string url, list <PinoComment> clst) // Query Resp
{
	//PinoComment cmmt;
	string pkt_body = "";
	list <PinoField> fields;
	list <PinoComment>::iterator it;
	int	body_len = 0;

	if (type != QueryCommentResp) {
		/* Error! */
		cout << "Packet type does not match!" << endl;	
	}
        pkt_type = QueryCommentResp;
	/* TODO */
	if (clst.empty()) {
		/* Error */
		cout << "Comment list is empty!" << endl;
	}
	
	for (it = clst.begin(); it != clst.end(); it++) 
	{
		fields = getFieldList(*it); //get fields list of one comment
		pkt_body += buildPacketBody(fields);
		body_len += getPacketBodyLen(pkt_body);
	}
	buildPacket(pkt_type, pkt_body, body_len);
}

PinoPacket::~PinoPacket()
{
}

// ??
string
PinoPacket::getPacketStream()
{
	/* FIXME: validate */ //
	return pkt_stream;
}

unsigned short
PinoPacket::getPacketLength()
{
	//char .at(1); //
	return pkt_len;
}

unsigned char
PinoPacket::getPacketType()
{
	/* TODO */  //	
	return pkt_type; 
}

// ??
multimap<string, string>
PinoPacket::getReqParameters()
{
	multimap<string, string> pmap;
	string key;

	// read fields from pkt_stream
	char* pPkt = convertStreamToPacket(pkt_stream);
	// skip packet (version:1, type:1, length:2)
	pPkt += 4;
        // get body length
	int body_len = *((int *) pPkt);
	body_len -= 2;    // delete 2 bytes for body_len in pkt_stream
	// skip body (length:2),  
        pPkt += 2;
	body_len -= 2;
	
	while (body_len)
	{

        	// get field type
        	unsigned char field_type = *pPkt;
		switch(field_type)
		{
			case FIELD_TYPE_URL:
				key = "URL";
				break;
			case FIELD_TYPE_AUTHOR:
				key = "AUTHOR";
				break;
			case FIELD_TYPE_CONTENT:
				key = "CONTENT";
				break;
			case FIELD_TYPE_TIMESTAMP:
				key = "TIMESTAMP";
				break;
			default:
				cout << "Field type does not match!" << endl;
				break;
		}
		// skip field type
		pPkt++;
		body_len -= 1;
        	// get field length
		field_len = *((int *) packet);
		// skip field length
		pPkt ++;
		body_len -= 1;
		// get body value
		string val(pPkt);
		pmap.insert(pair<string, string>(key, val));
		// skip body value
        	pPkt += field_len; 
		body_len -= field_len;
	}
	
	/* FIXME: TODO */
	return pmap;
}

list<PinoComment>	
PinoPacket::getComments()
{
	/* TODO */
	PinoComment cmmt;
	list<PinoComment> clst;
	map<string, string> fldMap = getReqParameters();
	map<string, string> :: iterator itFldMap;
	//string key;
	//string val;
	string url, author, content, timestamp;
	itFldMap = fldMap.begin();
	while( itFldMap != fldMap.end() ) 
	{
		url = (*itFldMap).second;
		itFldMap++;
		author = (*itFldMap).second;
		itFldMap++;		
		content = (*itFldMap).second;
		itFldMap++;
		timestamp = (*itFldMap).second;
		itFldMap++;
		clst.push_back(cmmt(url, author, content));
		/*switch(key_type)
		{
			case "URL":
				url = val;
				itFldMap++;
				break;
			case "AUTHOR":
				author = val;
				itFldMap++;
				break;
			case "CONTENT":
				content = val;
				itFldMap++;
				break;
			case "TIMESTAMP":
				timestamp = val;
				itFldMap++;
				break;
			default:
				break;
		}
		*/
		
	}
	return clst;
}


// ??
PinoComment
PinoPacket::getComment()
{
	/* TODO */
	list<PinoComment> clst;
	map<string, string> fldMap = getReqParameters();
	map<string, string> :: iterator itFldMap;

	string url, author, content, timestamp;
	itFldMap = fldMap.begin();

	url = (*itFldMap).second;
	itFldMap++;
	author = (*itFldMap).second;
	itFldMap++;		
	content = (*itFldMap).second;
	itFldMap++;
	timestamp = (*itFldMap).second;
	itFldMap++;

	PinoComment cmmt(url, author, content);

	return cmmt;
}



// ??
void 
PinoPacket::displayComments()
{
    /* TODO */
	list<PinoComment> clst = getComments();
	list<PinoComment>::iterator itClst;
        PinoComment cmmt;

    	for (itClst = clst.begin(); itClst != clst.end(); itClst++)
   	{
		cmmt = *itClst;
		cout << "Display comment " << endl;
		cout << "URL: " << cmmt.getURL() << endl;
		cout << "AUTHOR: " << cmmt.getAuthor() << endl;   
		cout << "CONTENT: " << cmmt.getContent() << endl;
	} 
}

// 
list<PinoField>
PinoPacket::getFieldList(PinoComment cmmt) 
{
	list<PinoField> fields;
	string			body;

	if (type != PostCommentReq)
	{
		cout << "PinoPacket: invalid parameter." << endl; /* FIXME: Error! */
	}

	fields = getFieldList(&cmmt);
	if (fields.empty())
	{
		cout << "PinoPacket: invalid parameter." << endl; /* FIXME: Error! */
	}
	m_type = PostCommentReq;
	m_body = buildPacketUnitBody(fields);
	m_len = getPacketUnitBodyLen(m_body);

	/* FIXME:: Allocate memory for ptk_stream, otherwise use C++ string */

	m_stream[0] = VERSION;
	m_stream[1] = PostCommentReq;
	*((unsigned char *) m_stream)	= m_len;
	
	/* TODO: copy m_body to m_stream */
}

list<PinoField>
PinoPacket::getFieldList() 
{
	/* TODO: get field list from pkt_stream */

	unsigned char body_type;
	int	body_len = 0;
        string body_val;
	list<PinoField> cflst;

	pkt_stream
	unsigned char body_type;
	int	body_len = 0;
        string body_val;
	list<PinoField> cflst;

        // add url 
 	string url = cmmt.getURL();
        if ( !url.empty() )
	{
		body_type = FIELD_TYPE_URL;
		body_len = url.length();
        	body_value = url;
		PinoField pfld_url(body_type, body_len, body_value);
        	cflst.push_back(pfld_url);
	}
	// add author
	string author = cmmt.getAuthor();
	if ( !author.empty() )
	{
		body_type = FIELD_TYPE_AUTHOR;
		body_len = author.length();
        	body_value = author;
		PinoField pfld_author(body_type, body_len, body_value);
        	cflst.push_back(pfld_author);
	}
	// add content
	string content = cmmt.getContent();
	if ( !content.empty() )
	{
		body_type = FIELD_TYPE_CONTENT;
		body_len = content.length();
        	body_value = content;
		PinoField pfld_author(body_type, body_len, body_value);
        	cflst.push_back(pfld_content);
	}
	// add timestamp
	string timestamp = cmmt.getTimeStamp();
	if ( !timestamp.empty() )
	{
		body_type = FIELD_TYPE_TIMESTAMP;
		body_len = timestamp.length();
        	body_value = timestamp;
		PinoField pfld_timestamp(body_type, body_len, body_value);
        	cflst.push_back(pfld_timestamp);
	}
 
        if( url.empty() && author.empty() && content.empty() && timestamp.empty() ) 
	{
		return;
	}

	return cflst;

        
}

unsigned short
PinoPacket::getPacketBodyLen(string pkt_body)
{
	string  pkt_body = "";
	unsigned char body_type;
	int	body_len = 0;
     string body_val;
	list<PinoField> fields;
    
	if (type != QueryCommentReq || url.empty())
	{
		cout << "Packet type does not match!" << endl; /* FIXME: Error! */
	}    

	fields.push_back(PinoField(FIELD_TYPE_URL, url.length, url));

    m_type = QueryCommentReq;
	m_body = buildPacketUnitBody(fields);
	m_len = getPacketUnitBodyLen(pkt_body);

	/* FIXME:: Allocate memory for ptk_stream, otherwise use C++ string */

	m_stream[0] = VERSION;
	m_stream[1] = QueryCommentReq;
	*((unsigned char *) m_stream)	= m_len;
	
	/* TODO: copy m_body to m_stream. Use C++ style */
}

/*
 * _ONLY_ for QueryCommentResp
 *
 * Response to QueryCommentReq, for specified URL with a list of Comments
 *
 */

PinoPacket::PinoPacket(char type, string url, list <PinoComment> clst)// Query Resp
{
	list<PinoField>		fields;
	list<PinoComment>::iterator it;

	if (type != QueryCommentResp || clst.empty())
	{
		cout << "PinoPacket: Invalid Parameters!" << endl;	/* Error! */
	}
	m_type = QueryCommentResp;
	
	for (it = clst.begin(); it != clst.end(); it++) 
	{
		fields = getFieldList(it); //get fields list of one comment
		if (fields.empty())
			continue;

		m_body += buildPacketUnitBody(fields);
		m_len += getPacketUnitBodyLen(pkt_body);
	}

	/* FIXME:: Allocate memory for ptk_stream, otherwise use C++ string */

	m_stream[0] = VERSION;
	m_stream[1] = QueryCommentResp;
	*((unsigned char *) m_stream)	= m_len;
	
	/* TODO: copy m_body to m_stream. Use C++ style */
}

PinoPacket::~PinoPacket()
{
	if (m_stream != 0)
		free(m_stream); /* FIXME: not C++ style ??? */
}

/* 
char* 
PinoPacket::convertStreamToPacket(string str)
{
    char* cstr;
    cstr = new char [str.size()+1];
    strcpy (cstr, str.c_str());  // string to cstr
    
    char* pkt;
    const int pktBuf_len = (int) pkt_len;   //???
    pkt = new char [pktBuf_len];

    memset(pkt, 0, sizeof(pkt));

    len = strlen(cstr);

    pkt[0] = pkt_type;
    *((unsigned short *) &pkt[1]) = pkt_len;
    strncpy((unsigned char *) &pkt[3], cstr, len);
    //delete cstr;                        //???
    return pkt;
}
*/
  

