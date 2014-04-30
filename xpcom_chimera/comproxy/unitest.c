
#include "stdio.h"

void
hexdump(char *pkt, int len)
{
	int i;

	printf("\n");
	printf("The packet stream: \n");
	for (i = 0; i < len ; i++) {
		printf(" %02x", *(pkt + i));
		if ((i + 1) % 8 == 0)
			printf(" ");
		if ((i + 1) % 16 == 0)
			printf("\n");
	}
	printf("\n\n");
}


int
main(int argc, char *agrv[])
{
	int 	i;
	char	type = 1;
	short 	len;
	char	len_buf[2]; // short int only take two byes, so, 2 is enough
	char	pkt[64];
	char	body[] = "Hello, Pinocchio! Hava good night!";

	memset(pkt, 0, sizeof(pkt));

	len = strlen(body);

	printf("The packet lenght: %d\n", len);

	pkt[0] = type;
	*((short *) &pkt[1]) = len; 
//	pkt[1] = len_buf[0];
//	pkt[2] = len_buf[1];

	strncpy((char *) &pkt[3], body, len);

	// Ok, we finish construct the packet

	// let look at what is like
	hexdump(pkt, 40);

	/* Send out */
	
	/* then, somebody receive it : the pkt */	
	char *packet = pkt;
	
	packet++; // ignore type

	char len_b[2];
	short int r_len;
	r_len = *((short *) packet);
	packet += 2; // skip the length

	printf("The recved pkt length: %d (0x%x)\n", r_len, r_len);
	printf("The message: %s\n\n", packet);



}
