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
#include <map>
#include <list>
#include "PinoPacket.h"
#include "PinoComment.h"
#include "PinoPacketReceiver.h"

PinoPacketReceiver::PinoPacketReceiver(string pkt)
{
	if (pkt.length() < PINO_PKTHDR_SZ)
	{
		cout << "PinoPacketReceiver: invalid packet." << endl;
	}

	m_stream = pkt;

	if (m_stream.at(PINO_PKTHDR_VER) != VERSION)
	{
		cout << "PinoPacketReceiver: invalid version." << endl;
	}

	m_type = m_stream.at(PINO_PKTHDR_TYPE);

	m_len = getPacketBodyLen() + PINO_PKTHDR_SZ; 
	if (m_len != pkt.length())
	{ 
		cout << "PinoPacketReceiver: malformat packet, len=" << pkt.length() << ", m_len=" << m_len << endl; 
	}
}

PinoPacketReceiver::PinoPacketReceiver(char *pkt, int len)
{
	m_stream = pkt;

	if (m_stream.at(PINO_PKTHDR_VER) != VERSION || len < PINO_PKTHDR_SZ) 
	{
		cout << "PinoPacket: unsupport version, ver=" << *(pkt - 1) << " len=" << len << endl; 
	}

	m_type = m_stream.at(PINO_PKTHDR_TYPE);
	m_len = stringToSize(m_stream.substr(PINO_PKTHDR_LEN, PINO_LENSZ));
	if (m_len != (len - PINO_PKTHDR_SZ))
	{ 
		cout << "PinoPacketReceiver: malformat packet, len=" << len << ", m_len=" << m_len << endl; 
	}
}

PinoPacketReceiver::~PinoPacketReceiver()
{
}

PinoField
PinoPacketReceiver::getFieldFromString(string pstr)
{
	size_t	f_len = stringToSize(pstr.substr(PINO_FDHDR_LEN, PINO_LENSZ));  
	return PinoField((PinoFieldType) pstr.at(PINO_FDHDR_TYPE), pstr.substr(PINO_FDHDR_SZ, f_len)); 
}

PinoComment
PinoPacketReceiver::getCommentFromString(string pstr)
{
	return PinoComment(getFieldListFromString(pstr));
}

list<PinoField>
PinoPacketReceiver::getFieldList()
{
	return getFieldListFromString(m_stream.substr(PINO_PKTHDR_SZ));
}

list<PinoField>
PinoPacketReceiver::getFieldListFromString(string bstr)
{
	size_t	b_len, f_len, pos;
	list<PinoField>	flst;

	b_len = stringToSize(bstr.substr(0, PINO_LENSZ));
	pos = PINO_LENSZ;

	while (b_len > 0)
	{
		f_len = stringToSize(bstr.substr(pos + PINO_FDHDR_LEN, PINO_LENSZ));
		flst.push_back(getFieldFromString(bstr.substr(pos, f_len + PINO_FDHDR_SZ)));
		pos += f_len + PINO_FDHDR_SZ;
		b_len -= f_len + PINO_FDHDR_SZ;
	}
			
	return flst;
}

list<PinoComment>
PinoPacketReceiver::getCommentList()
{
	list<PinoComment>	clst;
	size_t	b_len, pos, c_len;	
	string	body;

	if (m_type != QueryCommentResp)
	{
		return clst;
	}

	body = m_stream.substr(PINO_PKTHDR_SZ);
	b_len = getPacketBodyLen();
	pos = 0;	

	while (b_len > 0) 
	{
		c_len = stringToSize(body.substr(pos, PINO_LENSZ));
		clst.push_back(getCommentFromString(body.substr(pos, c_len + PINO_LENSZ)));
		pos += PINO_LENSZ + c_len;
		b_len -= c_len + PINO_LENSZ;
	}

	return clst;
}

PinoComment
PinoPacketReceiver::getComment()
{
	string	body;
	size_t	c_len;	

	if (m_type != PostCommentReq)
	{
		return PinoComment();
	}

	body = m_stream.substr(PINO_PKTHDR_SZ);
	c_len = stringToSize(body.substr(0, PINO_LENSZ));

	return getCommentFromString(body.substr(0, c_len + PINO_LENSZ));
}

void
PinoPacketReceiver::displayComments(list<PinoComment> cmmt_list)
{
}

ushort
PinoPacketReceiver::getPacketBodyLen()
{
	return stringToSize(m_stream.substr(PINO_PKTHDR_LEN, PINO_LENSZ));
}

string
PinoPacketReceiver::getPacketHeader()
{
	return m_stream.substr(0, PINO_PKTHDR_SZ);
}


