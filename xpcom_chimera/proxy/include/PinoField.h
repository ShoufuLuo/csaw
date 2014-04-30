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

#ifndef __PINO_FIELD_H__
#define __PINO_FIELD_H__

#include <iostream>
#include <string>

enum PinoFieldType {
	FIELD_TYPE_URL = 65,
	FIELD_TYPE_AUTHOR = 66,
	FIELD_TYPE_CONTENT = 67,
	FIELD_TYPE_TIMESTAMP = 68,
};

using namespace std;

class PinoField {

private:
	PinoFieldType	m_type;
	string			m_value;	

public:
	PinoField(PinoFieldType type, string value);
	~PinoField();

	PinoFieldType	getFieldType();
	short	getFieldLength();
	string	getFieldStr();
};
#endif
