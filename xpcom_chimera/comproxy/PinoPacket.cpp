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

PinoPacket::PinoPacket(string pkt)
{
        /* TODO */   // unsigned char   pkt_type; unsigned short pkt_len; string pkt_stream;
        char* pPkt = convertStreamToPacket(pkt);
        // skip first byte  version
        pPkt++;
        // get packet type
        pkt_type = *pPkt;
        pPkt++;
        // get packet length
        pkt_len = *((unsigned short *) packet);
        pPkt += 2; // skip the length
        // get body length
        unsigned short body_len = *((unsigned short *) pPkt);
        pPkt += 2; // skip the length
        // get body string
        string pkt_body(pPkt);   // cstr to string

        buildPacket(pkt_type, pkt_body, body_len);
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
	pPkt += 2; 

	m_stream = (unsigned char *) malloc (len); 
	memcpy(m_stream, pPkt, len);

	m_body = m_stream + 4; // skip header
}

/*
 * _ONLY_ For PostCommentReq, given by a comment, we setup a PinoPacket 
 *
 */

PinoPacket::PinoPacket(char type, PinoComment cmmt) 
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

/* 
 * _ONLY_ for QueryCommentRequest
 *
 * Given a URL, query all comments under this url
 *
 */
PinoPacket::PinoPacket(char type, string url)
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


 * Parse m_stream to get all comments in this packet
 */
list<PinoComment>
PinoPacket::getCommentList()
{
	list<PinoComment> clst;
	
	/* TODO */
	return clst;
}

/* 
 * Parse m_stream to get one comment in this packet
 */
PinoComment
PinoPacket::getComment()
{
	/* TODO */
	return PinoComment();
}

string
PinoPacket::getPacketStream()
{
	return m_stream;
}

/*
 * Parse m_stream and display all comments
 */
void 
PinoPacket::displayComments()
{
	list<PinoComment>	cmtList;
	list<PinoComment>::iterator it;
	
	cmtList = getCommentList();		

    for (it = cmtList.begin(); it != cmtList.end(); it++)
    {
         cout << "URL:" <<  it->getURL() << endl;
         cout << "Author:" <<  it->getAuthor() << endl;
         cout << "Time:" <<  it->getTime() << endl;
         cout << "Comment:" <<  it->getContent() << endl;
		 cout << " ------------------------------------- " << endl;
    } 
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

