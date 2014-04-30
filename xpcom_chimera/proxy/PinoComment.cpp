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
#include <list>
#include "PinoField.h"
#include "PinoComment.h"

PinoComment::PinoComment(string url, string author, string content)
{
	m_url = url;
	m_author = author;
	m_content = content;
	m_timestamp = time(NULL);
}

PinoComment::PinoComment(list<PinoField> pf)
{
	list<PinoField>::iterator	pit;
	bool	valid = false;
	
	cout << "PinoComment: ";
	for (pit = pf.begin(); pit != pf.end(); pit++) 
	{
		switch (pit->getFieldType()) {
		case FIELD_TYPE_URL:
			m_url = pit->getFieldStr();
			valid = true;
			cout << " URL='" << m_url << "'";
			break;
		case FIELD_TYPE_AUTHOR:
			m_author = pit->getFieldStr();
			cout << " Author='" << m_author << "'";
			break;
		case FIELD_TYPE_CONTENT:
			m_content = pit->getFieldStr();
			cout << " Content='" << m_content << "'";
			break;
		case FIELD_TYPE_TIMESTAMP:
			cout << " Time='" << pit->getFieldStr() << "'";
			//m_timestamp = pit->getFieldStr();
			break;
		}
	}
	cout << endl;
	if (!valid)
	{
		cout << "PinoComment: invalid comment." << endl;
	}
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

bool
PinoComment::match(PinoFieldType type, string value)
{
	bool matched = false;

	switch (type) {
	case FIELD_TYPE_URL:
		return m_url.compare(value);
	case FIELD_TYPE_AUTHOR:
		return m_author.compare(value);
	case FIELD_TYPE_CONTENT:
		/* TODO: we can support multiple keyword or phrase */
		return (m_content.find(value) != string::npos);
	case FIELD_TYPE_TIMESTAMP:
		/* TODO */
		break;
	}

	return matched;
}

