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


class PinoComment {

public:
        PinoComment(std::string url, std::string author, std::string content);
        ~PinoComment();
       
        std::string getAuthor();
        std::string getContent();
        std::string getURL();
        std::time_t getTimeStamp();  
        //std::time_t m_timestamp;
        //unsigned char m_type;

private:
        std::string m_author;
        std::string m_content;
        std::string m_url;
        std::time_t m_timestamp;
        unsigned char m_type;
};
