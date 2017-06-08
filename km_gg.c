/* This file is not modified from, but inspired by the example of API usage
 * as examplified by the STK3700 Software Examples.
 *
 * Dependencies:
 * They can be found in gecko_sdk_suite v1.0, as I won't dare redistribute.
 *
 * descriptors.c
 * descriptors.h
 * usbconfig.h
 * gpiointerrupt.c
 * hidkbd.c
 *
 * em_usbd.c
 * em_usbdch9.c
 * em_usbdep.c
 * em_usbdint.c
 * em_usbhal.c
 * em_usbtimer.c
 *
 * em_cmu.c
 * em_core.c
 * em_gpio.c
 * em_system.c
 * em_timer.c
 */

#include <stdio.h>

#include "em_chip.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_gpio.h"
#include "em_usb.h"
#include "gpiointerrupt.h"
#include "hidkbd.h"
/* TODO Why search locally for these includes? */
/* TODO em_emu.h ? */

#include "print.h"
#include "km_gg.h"
#include "descriptors.h"

/*** Function declarations ***/
static void GpioInterrupts_Callback(uint8_t pin);
static void GpioInterrupts_Setup(void);
static void GpioInterrupts_Enable(void);
static void GpioInterrupts_Disable(void);
static void TimerInterrupts_Enable(void);
static void TimerInterrupts_Disable(void);
static void TimerInterrupts_Callback(void);
static void Hid_Setup(void);
static void Usbd_Setup(void);
static void UsbStateChange(USBD_State_TypeDef oldState,
                           USBD_State_TypeDef newState);
static void SendKeyEvent(uint8_t modifier, uint8_t key[ROLLOVER]);
static void Scan_Keyboard(void); /* TODO Return i-key rollover? */
static uint8_t Scan_Rows(uint8_t col,
                         uint8_t i,
                         uint8_t keys[ROLLOVER],
                         uint8_t layer,
                         uint8_t *mods);
static uint8_t Scan_LowerRaise(void);
static uint8_t Scan_Coordinates(uint8_t row, uint8_t col);

/*** Function definitions ***/
void GpioInterrupts_Callback(uint8_t pin)
{
  GpioInterrupts_Disable();
  /* TODO Scan row imediately? */
  TimerInterrupts_Enable();
}

void GpioInterrupts_Setup(void)
{
  size_t i;

  CMU_ClockEnable(cmuClock_GPIO, true); /* TODO Is it necessary? */
  GPIOINT_Init();

  for (i = 0; i < NUM_ROWS; i++) {
    GPIO_PinModeSet(row_port[i], row_pin[i], gpioModeInputPull, 0);
    GPIOINT_CallbackRegister(row_pin[i], GpioInterrupts_Callback);
  }
}

void GpioInterrupts_Enable(void)
{
  size_t i;

  /* TODO GPIO_IntConfig is deprecated! */
  /* TODO Configure in GpioInterrupts_Setup before enabling here. */
  for (i = 0; i < NUM_ROWS; i++)
    GPIO_IntConfig(row_port[i], row_pin[i], true, false, true);

  for (i = 0; i < NUM_COLS; i++) {
    /* TODO Really set mode each time? Set only high/low? */
    GPIO_PinModeSet(col_port[i], col_pin[i], gpioModePushPull, 0);
    /* TODO Is this the correct gpio mode? */
    GPIO_PinOutSet(col_port[i], col_pin[i]);
  }
}

void GpioInterrupts_Disable(void)
{
  size_t i;

  /* TODO GPIO_IntConfig is deprecated! */
  /* TODO Use  GPIO_IntDisable instead of configuring */
  for (i = 0; i < NUM_ROWS; i++)
    GPIO_IntConfig(row_port[i], row_pin[i], true, false, false);

  for (i = 0; i < NUM_COLS; i++)
    GPIO_PinOutClear(col_port[i], col_pin[i]);
}

void TimerInterrupts_Enable(void)
{
  USBTIMER_Start(TIMER_ID, TIMER_TIMEOUT, TimerInterrupts_Callback);
  /* TODO Replace calls with implementation. */
}

void TimerInterrupts_Disable(void)
{
  /* TODO Implement */
  /* TODO Replace calls with implementation. */
}

/* typedef void(* USBTIMER_Callback_TypeDef) (void) */
void TimerInterrupts_Callback(void)
{
  /* TODO Reset timer bae? */

  Scan_Keyboard();
  TimerInterrupts_Enable(); /* TODO Replace with implementation. */
}

void Hid_Setup(void)
{
  HIDKBD_Init_t hidInitStruct;

  hidInitStruct.hidDescriptor = (void *)USBDESC_HidDescriptor;
  /* TODO Read http://wiki.c2.com/?CastingAwayConst */
  hidInitStruct.setReportFunc = NULL;

  HIDKBD_Init( &hidInitStruct );
}

void Usbd_Setup(void)
{
  static const USBD_Callbacks_TypeDef callbacks =
  {
    .usbReset        = NULL,
    .usbStateChange  = UsbStateChange,
    .setupCmd        = HIDKBD_SetupCmd,
    .isSelfPowered   = NULL,
    .sofInt          = NULL
  }; /* TODO static? */

  const USBD_Init_TypeDef usbInitStruct =
  {
    .deviceDescriptor    = &USBDESC_deviceDesc,
    .configDescriptor    = USBDESC_configDesc,
    .stringDescriptors   = USBDESC_strings,
    .numberOfStrings     = sizeof(USBDESC_strings)/sizeof(void*),
    .callbacks           = &callbacks,
    .bufferingMultiplier = USBDESC_bufferingMultiplier,
    .reserved            = 0
    /* declare outside function as 'static const' to load in ROM? */
  };

  USBD_Init( &usbInitStruct );
}

void UsbStateChange(USBD_State_TypeDef oldState,
                 USBD_State_TypeDef newState)
{
  /* TODO Change function name. */
  HIDKBD_StateChangeEvent( oldState, newState );

  /*
  if ( newState == USBD_STATE_CONFIGURED )
  {
  */
    GpioInterrupts_Enable();
    TimerInterrupts_Disable();
  /*
  }
  else
  {
    GpioInterrupts_Disable();
    TimerInterrupts_Enable();
  }
  */

  /* TODO Figure out this logic. */
}

void SendKeyEvent(uint8_t modifier, uint8_t key[ROLLOVER])
{
  HIDKBD_KeyReport_t report;

  report.modifier = modifier;
  report.reserved = 0;
  report.key[0] = key[0];
  report.key[1] = key[1];
  report.key[2] = key[2];
  report.key[3] = key[3];
  report.key[4] = key[4];
  report.key[5] = key[5];
  /* TODO Make more efficient. memcpy() or something. */

  HIDKBD_KeyboardEvent(&report);
}

void Scan_Keyboard(void)
{
  size_t c, i;
  uint8_t keys[ROLLOVER] = {0}; /* TODO Make all arrays plural. */
  uint8_t mods = 0, layer = 0;

  /* TODO Put other columns in high Z. */
  layer = Scan_LowerRaise();
  for (c = i = 0; c < NUM_COLS; c++) {
    GPIO_PinOutSet(col_port[c], col_pin[c]);
    i = Scan_Rows(c, i, keys, layer, &mods);
    GPIO_PinOutClear(col_port[c], col_pin[c]);
  }

  SendKeyEvent(mods, keys); /* TODO Move to Scan_Keyboard(). */
}
/* TODO Consistent naming capitalization scheme. */

uint8_t Scan_Rows(uint8_t col, /* TODO Make a struct for the arguments? */
                  uint8_t i, /* TODO Pass by reference? */
                  uint8_t keys[ROLLOVER],
                  uint8_t layer,
                  uint8_t *mods)
{
  /* TODO Too many parameters? */
  size_t r;
  uint16_t keyCode = 0;

  printf("Scan_Rows @%d\n", col); /* TODO Why can't I remove this? */

  for (r = 0; r < NUM_COLS && i < ROLLOVER; r++) {
    if(GPIO_PinInGet(row_port[r], row_pin[r]))
    { /* TODO Fix if styles. */
      printf("Keypress @%d,%d %x\n", r, col, keyMaps[layer][r][col]); /* TODO Remove. */
      keyCode = keyMaps[layer][r][col];
      keys[i++] = keyCode & 0xFF;
      *mods |= keyCode >> 8;
      printf("mods = %x\n", *mods);
      /* TODO Reverse over 0 keyCode? */
    }
  }

  return i;
}

uint8_t Scan_LowerRaise(void)
{
  uint8_t layer = 0;

  /* TODO Some bug allows raise+l to trigger l keypress. */

  /* TODO Define a constant LOWER_COL, LOWER_ROW = c3, r6. */
  if (Scan_Coordinates(6, 3))
    layer += LAYER_LOWER;

  /* TODO Define a constant RAISE_COL, RAISE_ROW = c4, r7. */
  if (Scan_Coordinates(7, 4))
    layer += LAYER_RAISE;

  return layer;
}
/* TODO Check all code for possible optimization. */

/**
 *  @brief Used for checking specific coordinate.
 *  Not for intensive loops!
 */
uint8_t Scan_Coordinates(uint8_t row, uint8_t col)
{
  uint8_t value = 0;

  /* TODO Integrate with Scan_Rows? */
  GPIO_PinOutSet(col_port[col], col_pin[col]);
  value = GPIO_PinInGet(row_port[row], row_pin[row]);
  GPIO_PinOutClear(col_port[col], col_pin[col]);

  return value;
}
/* TODO Proper formatting of doxygen. Use doxygen at all? */

int main(void)
{
  CHIP_Init();
  SWO_SetupForPrint();
  GpioInterrupts_Setup();
  Hid_Setup();
  Usbd_Setup();

  printf("KC_SH %x\n", KC_SH); /* TODO Remove! */

  while (1) {
  }
}
