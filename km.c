#include <bcm2835.h>
#include <stdio.h>

/* macros and defines */
#define LEN(X) (sizeof X / sizeof X[0])

#define ROWNUM 8
#define COLNUM 8

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

/* function declarations */
static void init(void);
static void updatematrix(void);
static void checkrows(uint8_t col);
static void printmatrix(void);
static void printkeys(void);

/* global variables */
static uint8_t cols[ROWNUM] = {C0, C1, C2, C3, C4, C5, C6, C7};
static uint8_t rows[COLNUM] = {R0, R1, R2, R3, R4, R5, R6, R7};
static uint8_t matrix[4][14] = {0}; /* TODO fix number macros */
static char* keymap[4][14] = {
	{"W", "E", "R", "T", "Z", "U", "I",
	 "O", "P", "7", "8", "9", "ZEILE", "EIN"},
	{"A", "S", "D", "F", "G", "H", "J",
	 "K", "L", "4", "5", "6", "Nº", "AUS"},
	{"Q", "Y", "X", "C", "V", "B", "N",
	 "M", "URDA", "1", "2", "3", "TAB", "CE/CM"},
	{"↑", "TEST", "GCAN", "METH", "RKAT", "ZKAT", "̅̅EICH",
	 "x", "NAME", "0", ".", "-", "PRINT", "ENTER"},
};

/* function definitions */
void
init(void)
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

void
updatematrix(void)
{
	uint8_t m, n;

	for (n = 0; n < LEN(cols); n++) {
		bcm2835_gpio_write(cols[n], HIGH);
		checkrows(n);
		bcm2835_gpio_write(cols[n], LOW);
	}
}

void
checkrows(uint8_t col)
{
	uint8_t i, v, c, r;

	/* TODO merge into 1 for loop if possible */
	for (i = 0; i < LEN(rows); i += 2) { /* red */
		v = bcm2835_gpio_lev(rows[i]);
		r = i/2;
		c = col*2 - 1;
		if (col != 0)
			matrix[r][c] = !!v; /* TODO use real value? */
	}

	for (i = 1; i < LEN(rows); i += 2) { /* blue */
		v = bcm2835_gpio_lev(rows[i]);
		r = (i - 1)/2;
		c = col*2;
		if (col != 7)
			matrix[r][c] = !!v;
	}
}

void
printmatrix(void)
{
	uint8_t m, n;

	for (m = 0; m < 4; m++) {
		for (n = 0; n < 14; n++) {
			matrix[m][n] ? printf("■")
			             : printf("□");
		}
		printf("\n");
	}
}

void
printkeys(void)
{
	uint8_t m, n;

	for (m = 0; m < 4; m++) {
		for (n = 0; n < 14; n++) {
			if (matrix[m][n])
				printf("%s ", keymap[m][n]);
		}
	}

	printf("\n");
}

int
main(int argc, char *argv[])
{
	if (!bcm2835_init())
		return 1;
	init();

	updatematrix();
	printmatrix();
	printkeys();

	bcm2835_close();
	return 0;
}
