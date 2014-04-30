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
#include <math.h>
#include "PinoPacket.h"

PinoPacket::PinoPacket()
{
	m_cstr = NULL;
	m_len = 0;
}

PinoPacket::~PinoPacket()
{
	if (m_cstr != NULL)
		delete m_cstr;
}

char*
PinoPacket::getPacketCStream()
{
	if (m_stream.size() == 0)
		return NULL;

	m_len = m_stream.size() + 1;
    m_cstr = new char[m_len];
    strcpy(m_cstr, m_stream.c_str()); 
	return m_cstr;
}

string
PinoPacket::getPacketString()
{
	return m_stream;
}

char
PinoPacket::getPacketType()
{
	return m_type;
}

ushort
PinoPacket::getPacketLength()
{
	if (m_len == 0)
		m_len = m_stream.size() + 1;
	return m_len;
}

/* 
 * Convert integer to four chars 
 * e.g. 
 *  Input: size_t size = 28; --> hex: 0x1C
 *  Output: string("001C")
 *
 */
string
PinoPacket::sizeToString(size_t size)
{
	char c_str[5];
	char c_hex[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7', 
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};
	//cout << "PinoPacket: input size=" << size;	
	c_str[0] = c_hex[(size>>12) % 16];
	c_str[1] = c_hex[(size>>8) % 16];
	c_str[2] = c_hex[(size>>4) % 16];
	c_str[3] = c_hex[size % 16];
	c_str[4] = '\0';
	//cout << " output '" << c_str << "'" << endl;
		
	return c_str;
}

/**
 * Convert 4 bytes string to short (size_t)
 * Input: "001C" 
 * Output 28
 *
 */
unsigned short
PinoPacket::stringToSize(string sstr) 
{
	unsigned short size = 0;

	if (sstr.length() != 4)
	{
		cout << "PinoPacket: Invalid string." << endl;	
		return 0;
	}

	//cout << "PinoPacket: input '" << sstr << "' " << endl;
	for (int i = 0; i < 4; i++)
	{
		if (sstr.at(i) >= '0' && sstr.at(i) <= '9')
		{
			size += (sstr.at(i) - '0') * pow(16, 3 - i);
		}
		else if (sstr.at(i) >= 'a' && sstr.at(i) <= 'f')
		{
			size += ((sstr.at(i) - 'a') + 10) * pow(16, 3 - i);
		}
		else if (sstr.at(i) >= 'A' && sstr.at(i) <= 'F')
		{
			size += ((sstr.at(i) - 'A') + 10) * pow(16, 3 - i);
		} 
		else
		{
			cout << "PinoPacket: invalid char in string." << endl;
			size = 0;
			break;
		}
		//cout << " '" << sstr.at(i)  << "' size= " << size << endl;
	}
	//cout << "output=" << size << endl;

	return size;
}

