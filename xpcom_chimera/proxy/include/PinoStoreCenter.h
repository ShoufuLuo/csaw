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
#include <map>

using namespace std;

template<class T>
class PinoStoreCenter {
public:
	PinoStoreCenter() {};
	~PinoStoreCenter() {}; 
	
	void solidRecordsToDiskFile()
	{
		/* TODO */
	};

	void initRecordsFromDiskFile()
	{
		/* TODO */
	};

	void saveObject(string key, T obj)
	{
		m_warehouse.insert(pair<string, T>(key, obj));
	};

	list<T>	getObjectsbyKey(string key)
	{
		class multimap<string, T>::iterator	itLow, itUp;
		list<T>		cmtlt;

		// FIXME: 
		// m_it = m_warehouse.find(key);
		// if (m_it == m_it.end()) 
		//		return cmtlt;

		// FIXME: 
		itLow = m_warehouse.lower_bound(key);
		itUp = m_warehouse.upper_bound(key);

		for (m_it = itLow; m_it != itUp; m_it++)
		{
			cmtlt.push_back(m_it->second);
		}

		return cmtlt;
	};

private:
	multimap<string, T>		m_warehouse;
	class multimap<string, T>::iterator	m_it;
};
