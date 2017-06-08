/***************************************************************************//**
 * @file km_gg.h
 * @brief Settings regarding pin numbering etc.
 ******************************************************************************/

#ifndef SRC_KM_GG_H_
#define SRC_KM_GG_H_

#include "em_gpio.h"

/* TODO Rename file? */

/**
 * Refer to the schematics at github.com/byllgrim/km
 *
 * Upper row pins
 * 5V PB10 PB9 GND PB11 PB12 PD15 GND PD0 PD1 PD2 ...
 *    R7   R5      R3   R1   R6       R4  R2  R0
 */

enum {
  NUM_ROWS = 8,
  NUM_COLS = 8,
}; /* TODO Use short enums. */

const GPIO_Port_TypeDef row_port[NUM_ROWS] =
{
  gpioPortD, //R0 Reds are even
  gpioPortB, //R1 Blues are odd
  gpioPortD, //R2
  gpioPortB, //R3
  gpioPortD, //R4
  gpioPortB, //R5
  gpioPortD, //R6
  gpioPortB, //R7
};

const unsigned int row_pin[NUM_ROWS] =
{
  2,  //R0
  12, //R1
  1,  //R2
  11, //R3
  0,  //R4
  9,  //R5
  15, //R6
  10, //R7
};

/**
 * Bottom row pins
 * 5V PA12 PA13 PA14 GND PE0 PE1 PE2 PE3 GND PC0 ...
 *    C0   C1   C2       C3  C4  C5  C6      C7
 */
const GPIO_Port_TypeDef col_port[NUM_COLS] =
{
    gpioPortA, //C0
    gpioPortA, //C1
    gpioPortA, //C2
    gpioPortE, //C3
    gpioPortE, //C4
    gpioPortE, //C5
    gpioPortE, //C6
    gpioPortC, //C7
};

const unsigned int col_pin[NUM_COLS] =
{
  12, //C0
  13, //C1
  14, //C2
  0,  //C3
  1,  //C4
  2,  //C5
  3,  //C6
  0,  //C7
};

typedef enum {
  /* TODO More descriptive naming. */
  /* TODO Write in hex? */
  MK_LC = 1 << 0 << 8, /* Left ctrl. */
  MK_LS = 1 << 1 << 8, /* Left shift. */
  MK_LA = 1 << 2 << 8, /* Left alt. */
  MK_LG = 1 << 3 << 8, /* Left gui (e.g. win key og cmd). */
  MK_RC = 1 << 4 << 8, /* Right ctrl. */
  MK_RS = 1 << 5 << 8, /* Right shift. */
  MK_RA = 1 << 6 << 8, /* Right alt. */
  MK_RG = 1 << 7 << 8, /* Right gui. */
} ModifierKeys_TypeDef;

/* TODO KeyCode in the format uint16_t {modifier, keycode}? */
/* TODO typedef or struct the uint16_t format? */
typedef enum {
  /* TODO
   * TODO Better naming.
   * TODO Correct order.
   * TODO Correct all 0 values.
   * TODO Align assignments?
   */
  KC_OOB = 0, /* Out-Off-Bounds are non-existent keys. See schematics. */
  KC_NIU = 0, /* Not-In-Use is non-qwerty extra buttons. */
  KC_A = 0x04,
  KC_B,
  KC_C,
  KC_D,
  KC_E,
  KC_F,
  KC_G,
  KC_H,
  KC_I,
  KC_J,
  KC_K,
  KC_L,
  KC_M,
  KC_N,
  KC_O,
  KC_P,
  KC_Q,
  KC_R,
  KC_S,
  KC_T,
  KC_U,
  KC_V,
  KC_W,
  KC_X,
  KC_Y,
  KC_Z,
  //TODO missing pieces
  KC_TAB = 0x2B,
  KC_BACK = 0x2A, /* Backspace. TODO KC_BS? */
  KC_ESC = 0x29,
  KC_SEM = 0x33, /* Semicolon. */
  KC_AP = 0x34, /* Apostrophe. */
  KC_SH = 0 | MK_LS, /* Shift. */
  KC_CM = 0x36, /* Comma. */
  KC_PR = 0x37, /* Period. */
  KC_FR = 0x38, /* Forward slash. */
  KC_ENT = 0x28, /* Enter. */
  KC_BL = 0, /* TODO BL is special to Planck. */
  KC_CT = 0 | MK_LC, /* Ctrl. */
  KC_AL = 0 | MK_LA, /* Alt. */
  KC_OS = 0 | MK_LG, /* OS key (left gui) e.g. win key */
  KC_LW = 0, /* TODO Lower is special. */
  KC_SP = 0x2C, /* Space. */
  KC_RS = 0, /* TODO Raise is special. */
  KC_LE = 0x50, /* Left arrow key. */
  KC_DO = 0x51, /* Down arrow key. */
  KC_UP = 0x52, /* Up arrow key. */
  KC_RI = 0x4F, /* Right arrow key */
  KC_GA = 0x35,/* Grave accent. */
  KC_DEL = 0x2A, /* Delete. */
  KC_1 = 0x1E,
  KC_2,
  KC_3,
  KC_4,
  KC_5,
  KC_6,
  KC_7,
  KC_8,
  KC_9,
  KC_0,
  KC_F1 = 0x3A,
  KC_F2,
  KC_F3,
  KC_F4,
  KC_F5,
  KC_F6,
  KC_F7,
  KC_F8,
  KC_F9,
  KC_F10,
  KC_F11,
  KC_F12,
  KC_MIN = 0x2D, /* Minus '-'. */
  KC_EQ = 0x2E, /* Equal '='. */
  KC_SL = 0x2F, /* Square bracket Left. */
  KC_SR = 0x30, /* Square bracket Right. */
  KC_BS = 0x31, /* BackSlash. */
  KC_NX = 0, /* TODO Music NeXt track! */
  KC_VM = 0x81, /* Volume minus. TODO Rename Volume Down? */
  KC_VP = 0x80, /* Volume plus. */
  KC_PL = 0,/* TODO Music play. */
  KC_TLD = KC_GA | MK_LS, /* Tilde. */
  KC_XM = KC_1 | MK_LS, /* Exclamation mark. */
  KC_AT, /* '@'. */
  KC_HSH, /* Hash tag. */
  KC_DL, /* Dollar sign. */
  KC_PC, /* Percentage. */
  KC_PW, /* Power '^'. */
  KC_AM, /* Ampersand. */
  KC_AS, /* Asterisk. */
  KC_LP, /* Left parentheses. */
  KC_RP, /* Right parentheses. */
  KC_UN = KC_MIN | MK_LS, /* Underscore. */
  KC_AD = KC_EQ | MK_LS, /* Addition '+'. */
  KC_LB = KC_SL | MK_LS, /* Left braces '{' */
  KC_RB = KC_SR | MK_LS, /* Right braces '}'. */
  KC_PP = KC_BS | MK_LS, /* Pipe '|'. */
} KeyCode_TypeDef;
/* TODO Comment all keycodes with '/' ascii symbol. */

static const uint32_t TIMER_ID = 1; /* Timer used to scan keyboard. */
static const uint32_t TIMER_TIMEOUT = 50; /* Milliseconds to elapse. TODO 50? */
enum {ROLLOVER = 6}; /* Max simultaneous keypress. TODO rename NKEY_... */
enum {
  NUM_LAYERS = 4, /* TODO Necessary? */
  LAYER_NORMAL = 0, /* TODO LAYER_QWERTY? */
  LAYER_LOWER = 1,
  LAYER_RAISE = 2,
  LAYER_ADJUST = LAYER_LOWER + LAYER_RAISE
  /* Keymap index adds to 0, 1, 2, 3 for normal, lower, raise, adjust */
}; /* Planck lower/raise layers. */
/* TODO Move placement of these definitions. */

/* The keymap is based on Planck OLKB default keymap v4.0. */
const uint16_t keyMaps[NUM_LAYERS][NUM_ROWS][NUM_COLS] = {
  [LAYER_NORMAL] =
  {
  /*C0 C0   C1 C1   C2 C2   C3 C3   C4 C4   C5 C5   C6 C6   C7 C7*/
  {KC_OOB,  KC_TAB, KC_W,   KC_R,   KC_Y,   KC_I,   KC_P,   KC_NIU},
    {KC_NIU,   KC_Q,   KC_E,   KC_T,   KC_U,   KC_O,   KC_BACK, KC_OOB},

  {KC_OOB,  KC_ESC, KC_S,   KC_F,   KC_H,   KC_K,   KC_SEM, KC_NIU},
    {KC_NIU,   KC_A,   KC_D,   KC_G,   KC_J,   KC_L,   KC_AP,  KC_OOB},

  {KC_OOB,  KC_SH,  KC_X,   KC_V,   KC_N,   KC_CM,  KC_FR,  KC_NIU},
    {KC_NIU,   KC_Z,   KC_C,   KC_B,   KC_M,   KC_PR,  KC_ENT, KC_OOB},

  {KC_OOB,  KC_BL,   KC_AL, KC_LW,  KC_SP,  KC_LE,  KC_UP,  KC_NIU},
    {KC_NIU,   KC_CT,  KC_OS,  KC_SP,  KC_RS,  KC_DO,  KC_RI,  KC_OOB},
  },
  /* Note that the row layout is weird. Consult the schematics. */

  [LAYER_LOWER] =
  {
  /*C0 C0   C1 C1   C2 C2   C3 C3   C4 C4   C5 C5   C6 C6   C7 C7*/
  {KC_OOB,  KC_TLD, KC_AT,  KC_DL,  KC_PW,  KC_AS,  KC_RP,  KC_NIU},
    {KC_NIU,   KC_XM,  KC_HSH, KC_PC,  KC_AM,  KC_LP,  0,      KC_OOB},

  {KC_OOB,  KC_DEL, KC_F2,  KC_F4,  KC_F6,  KC_AD,  KC_RB,      KC_NIU},
    {KC_NIU,   KC_F1,  KC_F3,  KC_F5,  KC_UN,  KC_LB,  KC_PP,      KC_OOB},

  {KC_OOB,  0,      KC_F8,  KC_F10, KC_F12, 0,      0,      KC_NIU},
    {KC_NIU,   KC_F7,  KC_F9,  KC_F11, 0,      0,      0,      KC_OOB},

  {KC_OOB,  0,      0,      0,      KC_SP,  KC_NX,  KC_VP,  KC_NIU},
    {KC_NIU,   0,      0,      KC_SP,  0,      KC_VM,  KC_PL,  KC_OOB},
  },

  [LAYER_RAISE] =
  {
  /*C0 C0   C1 C1   C2 C2   C3 C3   C4 C4   C5 C5   C6 C6   C7 C7*/
  {KC_OOB,  KC_GA,  KC_2,   KC_4,   KC_6,   KC_8,   KC_0,   KC_NIU},
    {KC_NIU,   KC_1,   KC_3,   KC_5,   KC_7,   KC_9,   0,      KC_OOB},

  {KC_OOB,  KC_DEL, KC_F2,  KC_F4,  KC_F6,  KC_EQ,  KC_SR,  KC_NIU},
    {KC_NIU,   KC_F1,  KC_F3,  KC_F5,  KC_MIN, KC_SL,  KC_BS,  KC_OOB},

  {KC_OOB,  0,      KC_F8,  KC_F10, KC_F12, 0,      0,      KC_NIU},
    {KC_NIU,   KC_F7,  KC_F9,  KC_F11, 0,      0,      0,      KC_OOB},

  {KC_OOB,  0,      0,      0,      KC_SP,  KC_NX,  KC_VP,  KC_NIU},
    {KC_NIU,   0,      0,      KC_SP,  0,      KC_VM,  KC_PL,  KC_OOB},
  },
  /* TODO KC_RA = 0 for raise, lower etc? */

  [LAYER_ADJUST] = /* TODO Fill in the adjust layer? */
  {
  /*C0 C0   C1 C1   C2 C2   C3 C3   C4 C4   C5 C5   C6 C6   C7 C7*/
  {KC_OOB,  0,      0,      0,      0,      0,      0,      KC_NIU},
    {KC_NIU,   0,      0,      0,      0,      0,      0,      KC_OOB},

  {KC_OOB,  0,      0,      0,      0,      0,      0,      KC_NIU},
    {KC_NIU,   0,      0,      0,      0,      0,      0,      KC_OOB},

  {KC_OOB,  0,      0,      0,      0,      0,      0,      KC_NIU},
    {KC_NIU,   0,      0,      0,      0,      0,      0,      KC_OOB},

  {KC_OOB,  0,      0,      0,      0,      0,      0,      KC_NIU},
    {KC_NIU,   0,      0,      0,      0,      0,      0,      KC_OOB},
  },
};

/* TODO Sort this file. */

#endif /* SRC_KM_GG_H_ */
