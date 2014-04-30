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

#ifndef __PINO_PACKET_H__
#define __PINO_PACKET_H__

#include <iostream>
#include <string>

using namespace std;

enum PacketType {
	PostCommentReq = 41,
	PostCommentResp = 42,
	QueryCommentReq = 43,
	QueryCommentResp = 44,
};

typedef unsigned short	ushort;

#define PINO_LENSZ	4

#define PINO_PKTHDR_VER		0
#define PINO_PKTHDR_TYPE	1	
#define PINO_PKTHDR_LEN		2	

/* Header: version(1), type(1), length(4) */
#define PINO_PKTHDR_SZ		(2 + PINO_LENSZ)	

#define PINO_FDHDR_TYPE		0
#define PINO_FDHDR_LEN		1
#define PINO_FDHDR_SZ		(1 + PINO_LENSZ)

class PinoPacket {

protected:
  	static const char VERSION = 1;

	char	m_type;
	char*	m_cstr;
	ushort	m_len;
	string 	m_stream;

	ushort 	stringToSize(string sstr);
	string 	sizeToString(size_t size);

public:
	PinoPacket();
	~PinoPacket();

	char*	getPacketCStream();
	char	getPacketType();
	string	getPacketString();

	ushort	getPacketLength();
};

#endif
