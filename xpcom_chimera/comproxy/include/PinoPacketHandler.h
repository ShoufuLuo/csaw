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

typedef struct _PinoPacket {
	char pkt_version;
	char pkt_type;
	short pkt_len;
	void *data;

} PinoPacket;

enum PacketType {
	PostCommentReq = 1,
	QueryCommentReq,
	QueryCommentResp
};

enum PacketFieldType {
	url = 1,
	author,
	comment,
	timestamp
};

struct _PinoPacketField {
	unsigned char	type;
	unsigned short	len;
	void *data;
};

/* TODO: Protocol

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

/*struct _PostComment {
    std::string url;
    std::string author;
    std::string content;
    unsigned char type;
    std::time_t timestamp;
};

struct QueryComment {
    std::string url;
};

struct QueryComment_Resp {
    std::string url;
    std::string author;
    std::string content;   
};*/

class PinoPacket{
public:


private:
     	char pkt_version;
	char pkt_type;
	short pkt_len;
	void *data;
};

class PinoPacketHandler : public PinoPacket{

public:
        PinoPacketHandler() {}
        PinoPacketHandler(PinoComment ct);
        ~PinoPacketHandler() {};
        void handleReq(char *packet);
	buildPacket(char type, PinoComment commnt); //Post Comment
	buildPacket(char type, string url, string author, string content); //Post Comment
	buildPacket(char type, string url); //Query Comment
	buildPacket(char type, string author); //Query Comment
	//buildPacket(char type, time_t start, time_t end); //Query Comment
	//buildPacket(char type, string keywords); //Query Comment

	buildPacket(char type, string url, List comments);// Query Resp
      
        List getCommentListFromPacket(char *packet);
        List getCommentFromPacket(char *packet);
        void displayCommentList(List ctlist);
        char getPacketType(char* packet);
          
private:

};

