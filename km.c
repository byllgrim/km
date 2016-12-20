#include <bcm2835.h>
#include <stdio.h>

/* macros and defines */
#define LEN(X) (sizeof X / sizeof X[0])

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

/* global variables */
static uint8_t cols[8] = {C0, C1, C2, C3, C4, C5, C6, C7};
static uint8_t rows[8] = {R0, R1, R2, R3, R4, R5, R6, R7};

/* function definitions */
void
init()
{
	uint8_t i;

	for (i = 0; i < LEN(cols); i++) {
		bcm2835_gpio_fsel(cols[i], BCM2835_GPIO_FSEL_OUTP);
		bcm2835_gpio_write(cols[i], LOW);
	}

	for (i = 0; i < LEN(rows); i++) {
		bcm2835_gpio_fsel(rows[i], BCM2835_GPIO_FSEL_INPT);
		bcm2835_gpio_set_pud(rows[i], BCM2835_GPIO_PUD_DOWN);
	}
}

int
main(int argc, char *argv[])
{
	if (!bcm2835_init())
		return 1;
	init();

	bcm2835_close();
	return 0;
}
