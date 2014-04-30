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


class PinoPacketSender {

public:
	PinoPacketSender(char type, string url);		//Query Comment
	PinoPacketSender(char type, PinoComment cmt);	//Post Comment
	PinoPacketSender(char type, string url, string author, string content); //Post Comment
	PinoPacketSender(char type, string url, list<PinoComment> clst);// Query Resp



};

