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
#include <map>
#include <list>
#include "PinoStoreCenter.h"


using namespace std;

PinoStoreCenter::PinoStoreCenter()
{
	
}

PinoStoreCenter::~PinoStoreCenter()
{
   
}


void
PinoStoreCenter::storeObject(string key, T obj)
{
    m_warehouse.insert(pair<string, T>(key, obj));
 
}

list <T>
PinoStoreCenter::getObjectsbyKey(string key)
{
    m_it = m_warehouse.find(key);
    if (m_it == m_it.end()) return;
    itLow = m_warehouse.lower_bound(key);
    itUp = m_warehouse.upper_bound(key);
    //T cmtStr;
    list <T> cmtlt;
    for (m_it = itLow; m_it < itUp; m_it++)
    {
      cmtlt.push_back((*m_it).second);
      //cmtStr = cmtStr + (*m_it).first + (*m_it).second + '\n';
    }
    return cmtlt;
}
 
/*string PinoStoreCenter::solidRecordsToDiskFile()
{

}*/
        
/*string PinoStoreCenter::initRecordsFromDiskFile()
{

}*/



