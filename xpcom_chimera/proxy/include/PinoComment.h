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

#ifndef __PINO_COMMENT_H__
#define __PINO_COMMENT_H__

#include <iostream>
#include <string>
#include <list>
#include <ctime>

#include "PinoField.h"

using namespace std;

class PinoComment {
public:
	PinoComment() {};
	PinoComment(string url, string author, string content);
	PinoComment(list<PinoField> pf);
	~PinoComment(); 

	string	getAuthor();
	string	getContent();
	string	getURL();
	time_t	getTimeStamp();  
	char	getType();

	bool	match(PinoFieldType type, string value);

protected:
	string	m_url;
	string	m_author;
	string	m_content;
	time_t	m_timestamp;
	char	m_type;
};
#endif
