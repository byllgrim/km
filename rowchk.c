/*
 * See LICENSE file
 *
 * This "script" was used to figure out which rows connects to which pins.
 * It's used with the pulldown resistors on raspberry pi GPIOs.
 */

#include <bcm2835.h>
#include <stdio.h>

#define COL RPI_V2_GPIO_P1_03
#define ROW RPI_V2_GPIO_P1_08

int
main(int argc, char *argv[])
{
	uint8_t r, rh, k;
	if (!bcm2835_init())
		return 1;

	bcm2835_gpio_fsel(COL, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(COL, HIGH);

	bcm2835_gpio_fsel(ROW, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(ROW, BCM2835_GPIO_PUD_DOWN);

	r = rh = -1;
	for (k = 0; k < 10; k++) {
		printf("%d\t", k);

		r = bcm2835_gpio_lev(ROW);
		(r != rh) ? printf("r = %d\n", (rh = r))
		          : printf("\n");
			
		delay(1000);
	}

	bcm2835_close();
	return 0;
}
