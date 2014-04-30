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
 *	Author: Shoufu Luo
 * 	Mon Jan 2 6:36:10 EDT 2012 
 *
 */

#include <stdlib.h>
#include "nsCOMPtr.h"
#include "nsComponentManagerUtils.h"
#include "nsServiceManagerUtils.h"
#include "nsXPCOM.h"
#include "nsXPCOMGlue.h"
#include "chimera.h"

#include "proxy.h"
#include "PinoPacket.h"
#include "PinoPacketSender.h"
#include "PinoField.h"
#include "../xpcom_osnapi/iOSN.h"

#include "ChimeraRider.h"

NS_IMPL_ISUPPORTS1(ChimeraRider, iChimeraRider)

ChimeraRider::ChimeraRider()
{
	char dummy_key[] = "connector";	
	char dummy_master[] = "127.0.0.1";
    ChimeraHost *host = NULL;
#if 0
	nsresult	rst;
	char 	*hstr;
	nsCOMPtr<nsIServiceManager> srvMgr;
	nsCOMPtr<iOSNAPI> osnapi;
	//nsIServiceManager *srvMgr = NULL;

	//XPCOMGlueStartup(nsnull);
	rst = NS_InitXPCOM2(getter_AddRefs(srvMgr), nsnull, nsnull);
	if (NS_FAILED(rst)) {
		printf("Init XPCOM failed %x\n", rst);
		return;
	}
	osnapi = do_CreateInstance("@rutgers.edu/XPCOM/byzauthAdapter;1" 
/*"@pinocchio.com/OSNAPI/Facebook;1"*/, &rst);
	if (NS_FAILED(rst)) {
		printf("xInit XPCOM failed %x\n", rst);
	} else {
		printf("XPCOM startup.\n");
	#if 0
		if (osnapi) {
				osnapi->HelloOSNAPI((char **) &hstr);
				if (hstr == NULL) 
					printf("failed\n");
				else
					printf("String from JS: %s\n", hstr);
		}
	#endif
	}
#endif

	key_make_hash(&m_nodeKey, dummy_key, strlen(dummy_key));

	m_state = chimera_init(7118);
	if (m_state == NULL)
	{ 
		return;
	}

	host = host_get (m_state, dummy_master, 7117);
	if (host == NULL)
	{
		return;
	}

	chimera_forward(m_state, p2p_forward);
	chimera_deliver(m_state, p2p_deliver);
	chimera_update(m_state, p2p_update);
    chimera_setkey(m_state, m_nodeKey);
    chimera_register(m_state, TEST_CHAT, 1);

	chimera_join(m_state, host);

	p2p_proxy_init(m_state);
}

ChimeraRider::~ChimeraRider()
{
}

NS_IMETHODIMP
ChimeraRider::SubmitComment(const char *url, const char *author, const char *content, PRInt32 inherit, PRInt32 permission)
{
	Key		key; /* FIXME: How to calcuate KEY */
			
	PinoPacketSender spkt = PinoPacketSender(PostCommentReq, url, author, content);
	chimera_send(m_state, key, TEST_CHAT, spkt.getPacketLength(), spkt.getPacketCStream());

    return NS_OK;
}

NS_IMETHODIMP
ChimeraRider::QueryCmmtsbyURL(const char *url, iQueryCmmtCB *func)
{
	Key		key; /* FIXME: How to calcuate KEY */

	PinoPacketSender spkt = PinoPacketSender(QueryCommentReq, url);
	chimera_send(m_state, key, TEST_CHAT, spkt.getPacketLength(), spkt.getPacketCStream());

    return NS_OK;
}

NS_IMETHODIMP
ChimeraRider::QueryCmmtsbyURLAuthor(const char *url, const char *author, iQueryCmmtCB *func)
{
	Key key; /* FIXME: How to calcuate KEY */
	list<PinoField>	flst;

	flst.push_back(PinoField(FIELD_TYPE_URL, url));
	flst.push_back(PinoField(FIELD_TYPE_AUTHOR, author));
	
	PinoPacketSender spkt = PinoPacketSender(QueryCommentReq, flst);
	chimera_send(m_state, key, TEST_CHAT, spkt.getPacketLength(), spkt.getPacketCStream());

    return NS_OK;
}

NS_IMETHODIMP
ChimeraRider::QueryCmmtsbyURLKeyword(const char *url, const char *keyword, iQueryCmmtCB *func)
{
	Key key; /* FIXME: How to calcuate KEY */
	list<PinoField>	flst;

	flst.push_back(PinoField(FIELD_TYPE_URL, url));
	flst.push_back(PinoField(FIELD_TYPE_CONTENT, keyword));
	
	PinoPacketSender spkt = PinoPacketSender(QueryCommentReq, flst);
	chimera_send(m_state, key, TEST_CHAT, spkt.getPacketLength(), spkt.getPacketCStream());

    return NS_OK;
}

