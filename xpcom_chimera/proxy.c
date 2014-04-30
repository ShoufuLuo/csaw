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
 *	Author: Shoufu Luo (sluo2@stevens.edu)
 * 	Mon Jan 2 6:36:10 EDT 2012 
 *
 */

#include <stdlib.h>
#include <ctime>
#include "nsCOMPtr.h"
#include "nsComponentManagerUtils.h"
#include "nsServiceManagerUtils.h"
#include "nsXPCOM.h"
#include "nsXPCOMGlue.h"
#include "ChimeraRider.h"
#include "chimera.h"

#include "../xpcom_osnapi/iOSN.h"
#include "../xpcom_demo/ihelloxpcom.h"

#include "PinoPacketReceiver.h"
#include "PinoPacketSender.h"
#include "PinoStoreCenter.h"
#include "PinoComment.h"
#include "pthread.h"
#include "proxy.h"

#ifdef __cplusplus
extern "C" {
#endif

#define COMPONENT_OSNAPI_FACEBOOK_CONTRACTID	"@pinocchio.com/OSNAPI/Facebook;1"
#define HELLOXPCOM_CONTRACTID	"@pinocchio.com/XPCOM/xpcomdemo;1"

static PinoStoreCenter<PinoComment>	gStore;
static pthread_t	g_httpd;
static ChimeraState	*g_state;

void*
p2p_httpd(void *)
{

	while (1)
	{
		sleep(1);	
	}

	pthread_exit(0);
}

void
p2p_proxy_init(ChimeraState	*state)
{
	nsresult	rst;
	nsCOMPtr<nsIServiceManager> srvMgr;
	int pthdid = 1;

	gStore = PinoStoreCenter<PinoComment>();
	g_state = state;

	//pthread_create(&g_httpd, NULL, &p2p_httpd, &pthdid);
	//pthread_join(g_httpd, NULL);

#if 0
	rst = NS_InitXPCOM2(getter_AddRefs(srvMgr), nsnull, nsnull);
	if (NS_FAILED(rst)) {
		printf("XPCOM failed %x\n", rst);
		return;
	}
#endif

	rst = NS_GetServiceManager(getter_AddRefs(srvMgr)); 
	if (rst == NS_ERROR_NOT_INITIALIZED)
	{
		printf("Error: XPCOM error to get SM (%x)\n", rst);
		return;
	}

	nsCOMPtr<ihelloxpcom> hxp;
    rst = srvMgr->GetServiceByContractID(HELLOXPCOM_CONTRACTID, 
	                   NS_GET_IID(ihelloxpcom), getter_AddRefs(hxp));    

	//hxp = do_CreateInstance(HELLOXPCOM_CONTRACTID, &rst);					      
	if (NS_FAILED(rst))
	{
		NS_ShutdownXPCOM(nsnull);
		printf("Error: XPCOM error to get COMP (%x)\n", rst);
		return;
	}

	int mut = 0;
	hxp->Multiple(3, 4, &mut);
	printf("String from JS: %d\n", mut);
	return;
}

void
p2p_forward(Key **kp, Message **mp, ChimeraHost **hp)
{
    Key *k = *kp;
    Message *m = *mp;
    ChimeraHost *h = *hp;

    printf ("Routing %s (%s) to %s via %s:%d\n",
	     (m->type == TEST_CHAT) ? ("CHAT") : ("JOIN"), m->payload,
	     k->keystr, h->key.keystr, (h->port));
}

void
p2p_deliver(Key *k, Message *m)
{
	PinoComment			cmmt;
	list<PinoComment>	clst;
	list<PinoField>		params;
	list<PinoComment>::iterator	cit;
	list<PinoField>::iterator	pit;
	string			url;

    fprintf (stderr, "Delivered %s (%s) to %s\n",
	     (m->type == TEST_CHAT) ? ("CHAT") : ("JOIN"), m->payload,
	     k->keystr);

    if (m->type != TEST_CHAT)
		return;

    fprintf (stderr, "** %s **\n", m->payload + 2); 

	PinoPacketReceiver	rpkt = PinoPacketReceiver(m->payload, m->size);
	switch (rpkt.getPacketType()) {
	case PostCommentReq:
		gStore.saveObject(cmmt.getURL(), rpkt.getComment()); 
		break;
	case QueryCommentResp:
		clst = rpkt.getCommentList();
		/* TODO: Push result to upper layer */
		break;
	case QueryCommentReq:
		 /* The first ITEM must be URL.*/
		params =rpkt.getFieldList(); 
		pit = params.begin();
		if (pit->getFieldType() != FIELD_TYPE_URL) {
			fprintf(stderr, "The first field must be URL\n");
			break;
		}
		url = pit->getFieldStr();
		clst = gStore.getObjectsbyKey(url); 
		if (clst.empty())
			break;

		for (pit++; pit != params.end(); pit++) {
			for (cit = clst.begin(); cit != clst.end(); ) {
				if (!cit->match(pit->getFieldType(), pit->getFieldStr())) {
					cit = clst.erase(cit);
					continue;
				}
				cit++;
			}
		}

		PinoPacketSender	spkt = PinoPacketSender(QueryCommentResp, url, clst);	
		chimera_send(g_state, *k, TEST_CHAT, spkt.getPacketLength(), spkt.getPacketCStream());
		break;
	}
}

void
p2p_update(Key *k, ChimeraHost *h, int joined)
{
    if (joined)
	{
	    printf ("Update - Node %s:%s:%d joined neighbor set\n", k->keystr,
		     h->name, h->port);
	}
    else
	{
	    printf ("Update - Node %s:%s:%d leaving neighbor set\n",
		     k->keystr, h->name, h->port);
	}
}

#ifdef __cplusplus
}
#endif
