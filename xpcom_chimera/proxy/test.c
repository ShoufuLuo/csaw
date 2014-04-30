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
#include "PinoPacketReceiver.h"
#include "PinoPacketSender.h"
#include "PinoStoreCenter.h"
#include "chimera.h"

#define USAGE "test [ -j bootstrap:port ] port key"
#define OPTSTR "j:"

extern char *optarg;
extern int optind;

PinoStoreCenter<PinoComment>	gStore;
ChimeraState	*state;

#define TEST_CHAT	15
#define DUMMY_URL	"www.stevens.edu/sit"

void
proxy_send(Key key, char *pkt, int pkt_len)
{
	/* FIXME: we should pass a URL and generate the key
 	 * for test, we just pass a key generated before proxy_send being called
 	 */
	chimera_send (state, key, TEST_CHAT, pkt_len, pkt);
}

void proxy_fwd (Key ** kp, Message ** mp, ChimeraHost ** hp)
{
    Key *k = *kp;
    Message *m = *mp;
    ChimeraHost *h = *hp;

    fprintf (stderr, "Routing %s (%s) to %s via %s:%d\n",
	     (m->type == TEST_CHAT) ? ("CHAT") : ("JOIN"), m->payload + 2,
	     k->keystr, h->key.keystr, (h->port));
}

void proxy_del (Key *k, Message * m)
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

	fprintf(stderr, "Recieved Packet, PktType='%c'.\n", rpkt.getPacketType());

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
		proxy_send(*k, spkt.getPacketCStream(), spkt.getPacketLength());
		break;
	}
}

void proxy_update (Key * k, ChimeraHost * h, int joined)
{

    if (joined)
	{
	    fprintf (stderr, "Node %s:%s:%d joined neighbor set\n", k->keystr,
		     h->name, h->port);
	}
    else
	{
	    fprintf (stderr, "Node %s:%s:%d leaving neighbor set\n",
		     k->keystr, h->name, h->port);
	}

}

int main (int argc, char **argv)
{
	int		port, joinport;
	int		opt, i;
	Key		key, keyinput;
	char	*hn = NULL;
	char	tmp[256];
	ChimeraHost			*host = NULL;
	
	gStore = PinoStoreCenter<PinoComment>(); 

    while ((opt = getopt (argc, argv, OPTSTR)) != EOF)
	{
	    switch ((char) opt)
		{
		case 'j':
		    for (i = 0; optarg[i] != ':' && i < strlen (optarg); i++);
		    optarg[i] = 0;
		    hn = optarg;
		    sscanf (optarg + (i + 1), "%d", &joinport);
		    break;
		default:
		    fprintf (stderr, "invalid option %c\n", (char) opt);
		    fprintf (stderr, "usage: %s\n", USAGE);
		    exit (1);
		}
	}

    if ((argc - optind) != 2)
	{
	    fprintf (stderr, "usage: %s\n", USAGE);
	    exit (1);
	}

    port = atoi (argv[optind]);

	key_make_hash(&keyinput, argv[optind + 1], strlen(argv[optind+1]));

    state = chimera_init (port);
    if (state == NULL)
	{
	    fprintf (stderr, "unable to initialize chimera \n");
	    exit (1);
	}
    if (hn != NULL)
	{
	    host = host_get (state, hn, joinport);
	}
    chimera_forward (state, proxy_fwd);
    chimera_deliver (state, proxy_del);
    chimera_update (state, proxy_update);
    chimera_setkey (state, keyinput);
    chimera_register (state, TEST_CHAT, 1);

    chimera_join (state, host);
	
    fprintf (stderr,
	     "** send messages to key with command <key> <command> <message> **\n");

    while (fgets (tmp, 256, stdin) != NULL)
	{
	    if (strlen (tmp) > 2)
		{
		    for (i = 0; tmp[i] != '\n'; i++);
	    	tmp[i] = 0;

			string input = tmp;
			string keystr, command, data;

			i = input.find_first_of(' ');
			keystr = input.substr(0, i);

			input = input.substr(i + 1); 
			i = input.find_first_of(' ');
			command = input.substr(0, i);

			data = input.substr(i + 1); 

			key_make_hash(&key, const_cast<char *>(keystr.c_str()), keystr.length());
			
			cout << " > " << command << endl;

			PinoPacketSender spkt;
			if (command.compare("post") == 0) {
				i = data.find_first_of(' ');
				string url = data.substr(0, i);

				data = data.substr(i + 1);
				i = data.find_first_of(' ');
				string author = data.substr(0, i);
				string content = data.substr(i + 1);

				cout << " > '" << content << "' at '" << url << "' by '" << author << "' to " << keystr << endl;
				spkt = PinoPacketSender(PostCommentReq, url, author, content);

			} else if (command.compare("query") == 0) {
				cout << " by '" << data << "' from " << keystr << endl;
				spkt = PinoPacketSender(QueryCommentReq, data);
			} else {
				cout << " Invalid Command '" << command << "'." << endl;
				continue;
			}
			cout << " Sending " << spkt.getPacketCStream() + 2 << "] " << endl;
			proxy_send (key, spkt.getPacketCStream(), spkt.getPacketLength());
		}
	}
}
