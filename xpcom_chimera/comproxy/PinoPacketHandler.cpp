m_packetStr = m_packetType + cmt.getURL() + cmt.getAuthor() + cmt.getContent() + cmt.getTimeStamp();
    return m_packetStr;
}
string 
PinoPacketHandler::buildPacket(char type, string url, string author, string content) //Post Comment
{
    m_packetType = type;
    m_packetTimeStamp = getPacketTimeStamp();
    //string tm = convTimeToStr(m_packetTimeStamp);
    //build
    m_packetStr = m_packetType + url + author + content + m_packetTimeStamp;
    return m_packetStr;
}

string
PinoPacketHandler::buildPacket(char type, string url)  //Query Comment
{
    m_packetType = type;
    //build
    m_packetStr = m_packetType + url;
    return m_packetStr;
}

//PinoPacketHandler::buildPacket(char type, string author); //Query Comment
//PinoPacketHandler::buildPacket(char type, time_t start, time_t end); //Query Comment
//PinoPacketHandler::buildPacket(char type, string keywords); //Query Comment

string
PinoPacketHandler::buildPacket(char type, multimap <string, string> cmtList)// Query Resp
{
    m_packetType = type;
    m_packStr = m_packetType;
    m_timestamp = getTimeStamp();
    
    //Read comment list
    multimap <string, string>::iterator itCmtList;
    for (itCmtList = cmtList.begin(); itCmtList != cmtList.end(); itCmtList++)
    {
         m_packetStr = m_packetStr + (*itCmtList).first + (*itCmtList).second;
    }
    return m_packetStr;
}

/*string
PinoPacketHandler::buildPacket(char type, string url, List comments)// Query Resp
{
  string pkt_str;
  Pkt_type pkt;   //PostCommentReq, QueryCommentReq, QueryCommentResp
  switch(pkt) {
         case PostCommentReq:
              PostComment_Req cmt1;      //url,author,content,type,timestamp
              pkt_str=cmt1.url+cmt1.author+cmt1.content+cmt1.type+cmt1.timestamp;
              break;
         case QueryCommentReq:
              QueryComment_Req cmt2;    //url
              pkt_str=cmt2.url;
              break;
         case QueryCommentResp:
              QueryComment_Resp cmt3;   //url,author,content
              pkt_str=cmt3.url+cmt3.author+cmt3.content;
              break;
         default:
              cout<<"THe packet type does not match!"<<endl;
              break;
  return pkt_str;
}*/

//???
multimap <string, string> 
PinoPacketHandler::getCommentListFromPacket(char *packet)
{
    multimap <string, string>  cmtList;
    cmtList.insert(pair<string, string>(cmmt.getURL(), cmmt.getAuthor() + cmmt.getContent()));
}
//???
multimap <string, string> 
PinoPacketHandler::getCommentFromPacket(char *packet)
{
    m_packetData = packet;
    m_packetData->m_packetFieldType;
    multimap <string, string>  cmtList;
    cmtList.insert(pair<string, string>(cmmt.getURL(), cmmt.getAuthor() + cmmt.getContent()));
}

void 
PinoPacketHandler::displayCommentList(multimap <string, string>  cmtList)
{
    multimap <string, string>::iterator itCmtList;
    for (itCmtList = cmtList.begin(); itCmtList != cmtList.end(); itCmtList++)
    {
         cout << "url:" << (*m_it).first << "author and content:" << (*m_it).second << endl;
    }
}


char
PinoPacketHandler::getPacketType(char* packet)
{
    m_packetType = *packet;
    return m_packetType;
}


string 
PinoPacketHandler::getPacketTimeStamp()
{
    time(&m_packetTimeStamp);                      // get the current time
    char* pTs = ctime(&m_packetTimeStamp);
    string pktTmStr = pTs;                         // return char* to string
    return pktTmStr;
}


//convert time_t to string
/*string
PinoPacketHandler::convTimeToStr(std::time_t tm)
{
    string tmStr = time2str(tm);    //...
    return tmStr;
}*/

/*void PinoPacket::sendPkt(string url){
   
   chimera_send (state, key, TEST_CHAT, strlen (tmp + i) + 1,
				  tmp + i);
}*/



