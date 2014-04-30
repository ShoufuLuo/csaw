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
	unsigned char	m_type;
	unsigned short	m_len;
	unsigned char 	*m_body;
	unsigned char 	*m_stream;

public:
  	static const char VERSION = 1;

	~PinoPacket();

	PinoPacket(char *packet, int len);
	PinoPacket(char type, string url); //Query Comment
	PinoPacket(char type, PinoComment obj); //Post Comment
	PinoPacket(char type, string url, string author, string content); //Post Comment
	PinoPacket(char type, string url, list<PinoComment> clst);// Query Resp
	//PinoPacket(char type, string author); //Query Comment
	//PinoPacket(char type, time_t start, time_t end); //Query Comment
	//PinoPacket(char type, string keywords); //Query Comment

	/* Getter */
	char*			getPacketStream(); /* FIXME: string */
	unsigned char	getPacketType();
	unsigned short	getPacketLength();
	unsigned short	getPacketBodyLen()

	multimap<string, string>	getCommentParameters();
	list<PinoComment>		getComments();
	PinoComment 			getComment();

	/* Utility : for dev */
	void	displayComments(); 

protect:
	/* Functions for constructing a packet when sending */
	list<PinoField> getFieldList(PinoComment cmmt);
	string	buildPacketUnitBody(list<PinoField> fields);
};

