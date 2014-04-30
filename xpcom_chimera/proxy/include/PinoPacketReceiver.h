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
#include "PinoField.h"
#include "PinoPacket.h"
#include "PinoComment.h"

using namespace std;

class PinoPacketReceiver : public PinoPacket {

public:

	PinoPacketReceiver(string pkt);
	PinoPacketReceiver(char *pkt, int len);
	~PinoPacketReceiver();

	list<PinoField>		getFieldList();
	list<PinoComment>	getCommentList();
	PinoComment 		getComment();
	list<PinoField>		getFieldListFromString(string ss);
	PinoComment 		getCommentFromString(string pstr);
	PinoField			getFieldFromString(string pstr);

private:
	ushort	getPacketBodyLen();
	string	getPacketHeader();
	void	displayComments(list<PinoComment> cmmt_list);

};
