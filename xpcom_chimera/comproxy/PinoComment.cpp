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
#include "PinoComment.h"

using namespace std;

PinoComment::PinoComment(string url, string author, string content)
{
	m_url = url;
	m_author = author;
	m_content = content;
	m_timestamp = time(NULL);
	// m_type = type;
}

PinoComment::~PinoComment()
{
}

string 
PinoComment::getAuthor()
{
  return m_author;
}

string 
PinoComment::getContent()
{
  return m_content;
}

string 
PinoComment::getURL()
{
  return m_url;
}

time_t
PinoComment::getTimeStamp()
{
    return m_timestamp;
}


