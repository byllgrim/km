#include <bcm2835.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	if (!bcm2835_init())
		return 1;

	bcm2835_close();
	return 0;
}
