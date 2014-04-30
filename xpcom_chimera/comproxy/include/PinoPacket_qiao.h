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
#include <ctime>
#include <map>
#include <list>
#include "PinoComment.h"
#include "PinoField.h"

using namespace std;

enum PacketType {
	PostCommentReq = 1,
	QueryCommentReq,
	QueryCommentResp
};

enum PacketFieldType {
	FIELD_TYPE_URL = 1,
	FIELD_TYPE_AUTHOR,
	FIELD_TYPE_CONTENT,
	FIELD_TYPE_TIMESTAMP
};

/* TODO: Protocol

typedef struct _PinoPacket {
	char pkt_version;
	char pkt_type;
	short pkt_len;
	void *data;

} PinoPacket;

struct _PinoPacketField {
	unsigned char	type;
	unsigned short	len;
	void *data;
};

	PostCommentPacket : PinoPacket
		data -> 
			short len; <-- comment length
				char type; // URL, author, timestampe, content
				short len; // length of field
				void* data; // data 
			 
				...

	QueryComment : PinoPacket
		data->
			short len;  // unused 
				char type; // URL
				short len;
				void *data;

				char type; // author
				short len;
				void *data;
				... 

	QueryCommentResp: PinoPacket
		data->
			short len; <-- comment length
				char type;
				short len;
				void *data;
				...
			short len; <-- comment length
				char type;
				short len;
				void *data;
				...	
			...
*/

class PinoPacket {

private:
	unsigned char	pkt_type;
	unsigned short	pkt_len;
	string		pkt_stream;

public:
  	static const char VERSION = 1;


	PinoPacket(char *packet, int len);
	PinoPacket(char type, string url); //Query Comment
	PinoPacket(char type, PinoComment cmmt); //Post Comment
	PinoPacket(char type, string url, string author, string content); //Post Comment
	PinoPacket(char type, list<PinoField> fields) //Post Comment
	PinoPacket(char type, string url, list<PinoComment> clst);// Query Resp
	//PinoPacket(char type, string author); //Query Comment
	//PinoPacket(char type, time_t start, time_t end); //Query Comment
	//PinoPacket(char type, string keywords); //Query Comment
	
	~PinoPacket();
	
	string		getPacketStream();
	unsigned short	getPacketLength();
	unsigned char	getPacketType();

	multimap<string, string>	getReqParameters();
	list<PinoComment>		getComments();
	PinoComment 			getComment();

	void			displayComments();

        list<PinoField>		getFieldList(PinoComment cmmt);
	list<PinoField>		getFieldList();
	unsigned short		getPacketBodyLen(string pkt_body);
	string			buildPacketBody(list<PinoField> fields);
	void 		buildPacket(char type, string pkt_body, short body_len)
	char* 		convertStreamToPacket(string str);
	//string convertHexToStr(unsigned short value);
};

