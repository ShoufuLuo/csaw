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
#include "PinoField.h"

PinoField::PinoField(PinoFieldType type, string value)
{
	m_type = type;
	m_value = value;
}

PinoField::~PinoField()
{
}

PinoFieldType
PinoField::getFieldType()
{
	return m_type;
}

string
PinoField::getFieldStr()
{
	return m_value;
}

short
PinoField::getFieldLength()
{
	return m_value.length();
}
