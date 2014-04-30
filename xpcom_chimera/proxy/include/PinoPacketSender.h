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
#include "PinoField.h"
#include "PinoPacket.h"
#include "PinoComment.h"

class PinoPacketSender : public PinoPacket {

public:
	PinoPacketSender();
	PinoPacketSender(char type, string url); 			//QueryCommentReq
	PinoPacketSender(char type, PinoComment obj);		//PostComment
	PinoPacketSender(char type, string url, string author, string content);	//PostComment
	PinoPacketSender(char type, string url, list<PinoComment> clst);		// QueryCommentResp
	PinoPacketSender(char type, list<PinoField> flst);		// QueryCommentReq
	~PinoPacketSender();

private:
	string	buildPacketBody(list<PinoComment> cmmts);	// QueryCommentResp
	string	buildPacketBody(PinoComment cmmt);			// PostComment
	string	buildPacketUnitBody(list<PinoField> fields);	// QueryCommentReq
	void	buildPacket(char type, string body);

	list<PinoField> getFieldList(PinoComment cmmt);
};

