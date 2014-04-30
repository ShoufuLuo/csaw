#include <stdio.h>
#include <unistd.h>
#include "chimera.h"
#include "PinoPacket.h"
#include "PinoStoreCenter.h"

#define USAGE "test [ -j bootstrap:port ] port key"
#define OPTSTR "j:"

extern char *optarg;
extern int optind;

PinoStoreCenter	gStore;
ChimeraState	*state;

#define TEST_CHAT	15
#define DUMMY_URL	"www.stevens.edu/sit"

/* FIXME: we should pass a URL and generate the key
 * for test, we just pass a key generated before proxy_send being called
 */
void
proxy_send(Key key, char *pkt, int pkt_len)
{
	chimera_send (state, key, TEST_CHAT, pkt_len, pkt);
}

void proxy_fwd (Key ** kp, Message ** mp, ChimeraHost ** hp)
{
    Key *k = *kp;
    Message *m = *mp;
    ChimeraHost *h = *hp;

    fprintf (stderr, "Routing %s (%s) to %s via %s:%d\n",
	     (m->type == TEST_CHAT) ? ("CHAT") : ("JOIN"), m->payload,
	     k->keystr, h->key.keystr, (h->port));
}

void proxy_del (Key *k, Message * m)
{
	PinoPacket	ppkt;
	PinoPacket	ppkt2;
	PinoComment	cmmt;
	string	url;
	string	spkt;
	list<PinoComment>	clst;
	char	type;
	map<string, string>		params;
	map<string, string>::iterator	pit;

    fprintf (stderr, "Delivered %s (%s) to %s\n",
	     (m->type == TEST_CHAT) ? ("CHAT") : ("JOIN"), m->payload,
	     k->keystr);

    if (m->type != TEST_CHAT)
		return;

	//FIXME: we are not prepared. print it and return
    fprintf (stderr, "** %s **\n", m->payload);
	return;

	ppkt = PinoPacket(m->payload, m->size);
	type = ppkt.getPacketType();
	switch(type) {
	case PostCommentReq:
		cmmt = ppkt.getComment();
		gStore.storeComment(cmmt); 
		break;
	case QueryCommentReq:
		/* FIXME: 
		 * the parameter could be one or more items of <FIELD_TYPE, FIELD_VALUE> 
		 * e.g. < FIELD_TYPE_URL, "www.stevens.edu/sit/">  
		 * Then, go through all items and get comments required 
		 *
		 * The first ITEM must be URL.	
		 */
		params = ppkt.getReqParameters(); 
		//if (params[0].type != FIELD_TYPE_URL ||
		//	params[0].value.length == 0)
		{
			/* TODO: Response a invalid reqeust */
			//break;
		}
		clst = gStore.getCommentsbyURL(DUMMY_URL); /* Get it from first item of params */
		// TODO
		// for cmmt in cmm_list
		//		for item in params	
		//	 			
		//
		ppkt2 = PinoPacket(QueryCommentResp, DUMMY_URL, clst);	
		spkt = ppkt2.getPacketStream();

		proxy_send(*k, const_cast<char *>(spkt.c_str()), ppkt2.getPacketLength());
		break;
	case QueryCommentResp:
		clst = ppkt.getComments();
		ppkt.displayComments();
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
    int port, joinport;
    int opt, i;
    ChimeraHost	*host = NULL;
    Key key, keyinput;
    char *hn = NULL;
    char tmp[256];
	
	gStore = PinoStoreCenter(); //FIXME 

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
	     "** send messages to key with command <key> <message> **\n");

    while (fgets (tmp, 256, stdin) != NULL)
	{
	    if (strlen (tmp) > 2)
		{
		    for (i = 0; tmp[i] != '\n'; i++);
		    tmp[i] = 0;
		    for (i = 0; tmp[i] != ' ' && i < strlen (tmp); i++);
		    tmp[i] = 0;
		    i++;

			key_make_hash(&key, tmp, i - 1);
		    fprintf (stderr, "sending key: %s -> %s data:%s len:%d\n",
					tmp, key.keystr, tmp + i, strlen (tmp + i));

			string author = "sluo";
			string content = tmp + i;
			string url = DUMMY_URL;
			PinoPacket ppkt = PinoPacket(PostCommentReq, url, author, content);
			string pktstr = ppkt.getPacketStream();

		//FIXME: Unfortunately, we are not prepared!! So, we only send the plain text
		 //   chimera_send (state, key, TEST_CHAT, ppkt.getPacketLength(), 
		//		const_cast<char *>(pktstr.c_str()));
		    chimera_send (state, key, TEST_CHAT, strlen(tmp + i),
				tmp + i);
		}
	}
}
