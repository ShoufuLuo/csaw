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
#include <time.h>
#include "PinoField.h"
#include "PinoPacket.h"
#include "PinoComment.h"
#include "PinoPacketSender.h"

PinoPacketSender::PinoPacketSender() 	
{
}

void
PinoPacketSender::buildPacket(char type, string body)
{
	char hdr[3];
	string hdr_str;

	hdr[0] = VERSION;
	hdr[1] = type;
	hdr[2] = '\0';
	hdr_str = hdr;

	m_type = type;
	m_stream = hdr_str + sizeToString(body.length()) + body;
}

PinoPacketSender::PinoPacketSender(char type, list<PinoField> fields) //Query Comment Request with list of params
{
	if (type != PostCommentReq)
	{
		cout << "PinoPacket: invalid type!" << endl;
	}
	string b_str = buildPacketUnitBody(fields);
	buildPacket(PostCommentReq, b_str);
}

PinoPacketSender::PinoPacketSender(char type, string url) 			//QueryCommentReq
{
	if (type != QueryCommentReq)
	{
		cout << "PinoPacket: invalid type." << endl;
	}
	list<PinoField> cflst;
	cflst.push_back(PinoField(FIELD_TYPE_URL, url));
	string b_str = buildPacketUnitBody(cflst);
	buildPacket(QueryCommentReq, b_str);
}

PinoPacketSender::PinoPacketSender(char type, string url, string author, string content)	//PostComment
{
	if (type != PostCommentReq)
	{
		cout << "PinoPacket: invalid type!" << endl;
	}
       
	if (url.length() == 0 || author.empty() || content.empty())
	{
		cout << "URL/author/content cannot be empty!" << endl;
	}

	string b_str = buildPacketBody(PinoComment(url, author, content));
	buildPacket(PostCommentReq, b_str);
}

PinoPacketSender::PinoPacketSender(char type, PinoComment cmmt)		//PostComment
{
	if (type != PostCommentReq)
	{
		cout << "PinoPacket: Invald type!" << endl;
	}
	string b_str = buildPacketBody(cmmt);	
	buildPacket(PostCommentReq, b_str);
}


PinoPacketSender::PinoPacketSender(char type, string url, list<PinoComment> clst)		// QueryCommentResp
{
	if (type != QueryCommentResp)
	{
		cout << "PinoPacket: invald type!" << endl;
	}
	if (url.length() == 0 || clst.empty())
	{
		cout << "PinoPacket: Invalid parameter." << endl;
	}

	string b_str = buildPacketBody(clst);
	buildPacket(QueryCommentResp, b_str);
}

PinoPacketSender::~PinoPacketSender()
{
	/* TODO */
}

string
PinoPacketSender::buildPacketBody(list<PinoComment> cmmts)	// QueryCommentResp
{
	list<PinoComment>::iterator it;
	string u_body;

	for (it = cmmts.begin(); it != cmmts.end(); it++) 
	{
		u_body += buildPacketUnitBody(getFieldList(*it));	
	}
	
	return u_body;
}

string
PinoPacketSender::buildPacketBody(PinoComment cmmt)			// PostComment
{
	return buildPacketUnitBody(getFieldList(cmmt));
}

string
PinoPacketSender::buildPacketUnitBody(list<PinoField> fields)	// QueryCommentReq
{
	list<PinoField>::iterator it;
	string	b_str, s_str;
	size_t	total = 0;
	
	for (it = fields.begin(); it != fields.end(); it++)
	{
		if (it->getFieldStr().length() == 0)
			continue;
		s_str = sizeToString(it->getFieldStr().length()); //size string
		b_str += (char) it->getFieldType() + s_str + it->getFieldStr();
		total += sizeof(char) + s_str.length() + it->getFieldStr().length();
	} 

	return (sizeToString(total) + b_str);
}

list<PinoField>
PinoPacketSender::getFieldList(PinoComment cmmt)
{
	list<PinoField> cflst; 
	
 	string url = cmmt.getURL();
    if(url.empty())
		return cflst;

	cflst.push_back(PinoField(FIELD_TYPE_URL, url));

	string author = cmmt.getAuthor();
	if ( !author.empty() )
	{
		cflst.push_back(PinoField(FIELD_TYPE_AUTHOR, author));
	}

	string content = cmmt.getContent();
	if ( !content.empty() )
	{
		cflst.push_back(PinoField(FIELD_TYPE_CONTENT, content));
	}

	time_t cmt_time = cmmt.getTimeStamp();
    string tStr = ctime(&cmt_time);
	tStr.erase(tStr.find('\n'));
	cflst.push_back(PinoField(FIELD_TYPE_TIMESTAMP, tStr));

	return cflst;
}
