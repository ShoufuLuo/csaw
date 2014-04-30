
#include "stdio.h"
#include "hellopino.h"

int
main(int argc, char *argv[])
{
	hellopino _pino = hellopino(4, 6);

	printf("Hello, Pinocchio: %ld\n", _pino.multiple());

	return 0;
}
