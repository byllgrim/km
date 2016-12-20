#include <bcm2835.h>
#include <stdio.h>

#define C0 RPI_V2_GPIO_P1_03
#define C1 RPI_V2_GPIO_P1_05
#define C2 RPI_V2_GPIO_P1_07
#define C3 RPI_V2_GPIO_P1_11
#define C4 RPI_V2_GPIO_P1_13
#define C5 RPI_V2_GPIO_P1_15
#define C6 RPI_V2_GPIO_P1_19
#define C7 RPI_V2_GPIO_P1_21

#define R7 RPI_V2_GPIO_P1_08
#define R5 RPI_V2_GPIO_P1_10
#define R3 RPI_V2_GPIO_P1_12
#define R1 RPI_V2_GPIO_P1_16
#define R6 RPI_V2_GPIO_P1_18
#define R4 RPI_V2_GPIO_P1_22
#define R2 RPI_V2_GPIO_P1_24
#define R0 RPI_V2_GPIO_P1_26

int
main(int argc, char *argv[])
{
	if (!bcm2835_init())
		return 1;

	bcm2835_close();
	return 0;
}
