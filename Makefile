# GSDK @ https://github.com/SiliconLabs/gecko_sdk.git

INC = \
	-I gecko_sdk/platform/emlib/inc/ \
	-I gecko_sdk/platform/Device/SiliconLabs/EFM32GG11B/Include/ \
	-I gecko_sdk/platform/CMSIS/Core/Include/ \
	-I gecko_sdk/platform/common/inc/ \
	-I gecko_sdk/platform/middleware/usb_gecko/inc/ \
	-I gecko_sdk/platform/middleware/usbxpress/inc/ \
	-I gecko_sdk/platform/emdrv/gpiointerrupt/inc/ \
	-I gecko_sdk/hardware/kit/common/drivers/

SRC = \
	./gecko_sdk/platform/emlib/src/em_gpio.c \
	km_gg.c \

DEVICE = EFM32GG11B820F2048GL192

all:
	arm-none-eabi-gcc -D${DEVICE} ${INC} -o km_gg ${SRC}
	#cc -o rowchk rowchk.c ${LDFLAGS}
