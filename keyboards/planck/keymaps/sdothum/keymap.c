// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.
//
// To flash planck firmware
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   Reset keyboard or press hw reset button on base (hole)
//
//   cd qmk_firmware/keyboards/planck
//   sudo make KEYMAP=sdothum dfu
//
//   sudo make clean          (good practice before flashing)
//   sudo make KEYMAP=sdothum (to compile check)
//
// Package requirements (for arch linux)
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   avr-gcc-atmel
//   avr-libc-atmel
//   dfu-programmer
//
// Notes
// ▔▔▔▔▔
//   ** E R G O   W I D E   S P L I T ** Layout
//
//   Autocompletion tap dance key pairs (),[],{} are available from the
//   number/symbol layer, as well as, numerous (un)shift key values
//
//   The navigation pad provides a single hand right thumb activated cluster
//   with left hand modifiers
//
// Modifier clusters
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   The num and sym keys together access the navigation pad layer
//
//   ,-----------------------------------------------------------------------------------.
//   | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  |Right |
//   `-----------------------------------------------------------------------------------'
//
// Hint
// ▔▔▔▔
//   For sculpted keycaps such as Cherry or OEM profile, reverse the Alt, Num,
//   Shift, Shift, Nav, Sym keycaps for more ergonomic thumb orientation and
//   actuation
//
// Code
// ▔▔▔▔
//   This source is shamelessly based on the "default" planck layout
//
//   #ifdef/#endif block structures are not indented, as syntax highlighting
//   in vim is sufficient for identification
//
//   c++ commenting style is used throughout
//
// Change history
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   See http://thedarnedestthing.com/planck%20constant

#include "config.h"
#include "planck.h"
#include "keymap_uk.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
#include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

enum planck_layers {
#ifndef MOUSEKEY_ENABLE
#ifdef COLEMAK
  _COLEMAK = 0
 ,_QWERTY
#else
  _QWERTY = 0
 ,_COLEMAK
#endif
#else
  _COLEMAK = 0
#endif
#ifndef MOUSEKEY_ENABLE
 ,_PLOVER
 ,_LCOLEMAK
 ,_RCOLEMAK
 ,_LQWERTY
 ,_RQWERTY
 #else
 ,_LCOLEMAK
 ,_RCOLEMAK
#endif
 ,_NUMBER
 ,_SYMBOL
 ,_REGHEX
 ,_SFTNAV
 ,_FNCKEY
 ,_ADJUST
};

#ifndef MOUSEKEY_ENABLE
#ifdef COLEMAK
static uint8_t _LSHIFT = _LCOLEMAK;
static uint8_t _RSHIFT = _RCOLEMAK;
#else
static uint8_t _LSHIFT = _LQWERTY;
static uint8_t _RSHIFT = _RQWERTY;
#endif
#else
static uint8_t _LSHIFT = _LCOLEMAK;
static uint8_t _RSHIFT = _RCOLEMAK;
#endif

enum planck_keycodes {
  COLEMAK = SAFE_RANGE
  #ifndef MOUSEKEY_ENABLE
 ,QWERTY
 ,PLOVER
 ,PLOVEX
  #endif
 ,BACKLIT
 ,PS_LEFT   // pseudo LT(_SFTNAV, S(KC_LEFT)) for modified key-codes, see process_record_user()
 ,PS_PIPE   // pseudo LT(_SFTNAV, S(UK_BSLS)) for modified key-codes, see process_record_user()
 ,PS_TAB    // pseudo LT(_FNCKEY, S(KC_TAB))  for modified key-codes, see process_record_user()
 ,LT_BSPC = LT (_ADJUST, KC_BSPC)
 ,LT_ESC  = LT (_NUMBER, KC_ESC)
 ,LT_LEFT = LT (_SYMBOL, KC_LEFT)           // see process_record_user() for extended handling
 ,LT_TAB  = LT (_FNCKEY, KC_TAB)
 ,OS_ALT  = OSM(MOD_LALT)
 ,OS_CALT = OSM(MOD_LALT | MOD_LCTL)
 ,OS_CGUI = OSM(MOD_LGUI | MOD_LCTL)
 ,OS_CSFT = OSM(MOD_LSFT | MOD_LCTL)
 ,OS_CTL  = OSM(MOD_LCTL)
 ,OS_GUI  = OSM(MOD_LGUI)
 ,OS_SALT = OSM(MOD_LALT | MOD_LSFT)
 ,OS_SFT  = OSM(MOD_LSFT)
 ,OS_SGUI = OSM(MOD_LGUI | MOD_LSFT)
};

#define TG_NKRO      MAGIC_TOGGLE_NKRO

// modifier keys
#define AT_DOWN ALT_T(KC_DOWN)
#define CT_RGHT CTL_T(KC_RGHT)
#define GT_UP   GUI_T(KC_UP)
#define S_DOWN  S    (KC_DOWN)
#define S_END   S    (KC_END)
#define S_HOME  S    (KC_HOME)
#define S_LEFT  S    (KC_LEFT)
#define S_PGDN  S    (KC_PGDN)
#define S_PGUP  S    (KC_PGUP)
#define S_RGHT  S    (KC_RGHT)
#define S_UP    S    (KC_UP)

// tap dance keys
enum tap_dance {
  _CAPS = 0
   ,_ENT
 ,_LBRC
 ,_LCBR
 ,_LPRN
 ,_LT
 ,_QUOT
 ,_SEND
 ,_SPC
};

#define TD_CAPS TD(_CAPS)
#define TD_ENT  TD(_ENT)
#define TD_LBRC TD(_LBRC)
#define TD_LCBR TD(_LCBR)
#define TD_LPRN TD(_LPRN)
#define TD_LT   TD(_LT)
#define TD_QUOT TD(_QUOT)
#define TD_SEND TD(_SEND)                   // compile time macro string
#define TD_SPC  TD(_SPC)                    // see process_record_user() for extended handling of Spc

// layer keys
#define MO_RHEX MO(_REGHEX)

// keycodes
#define ___x___ KC_TRNS
#define _______ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// ..................................................................... Colemak
//
// http://www.keyboard-layout-editor.com/#/gists/34a2cb32e4f9267275c08a8089ca2d3c
// https://colemakmods.github.io/mod-dh/

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   F  |   P  |   B  | Caps | Caps |   J  |   L  |   U  |   Y  |   ;  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   G  | ^Alt | ^GUI |   K  |   N  |   E  |   I  |   O  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   C  |   D  |   V  |  Tab | Bksp |   M  |   H  |   ,  |   .  |   '  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  |Right |
  // `-----------------------------------------------------------------------------------'

  [_COLEMAK] = {
    {KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    TD_CAPS, TD_CAPS,  KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN},
    {KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    OS_CALT, BACKLIT,  KC_K,    KC_N,    KC_E,    KC_I,   KC_O   },
    {KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    LT_TAB,  LT_BSPC,  KC_M,    KC_H,    KC_COMM, KC_DOT, KC_QUOT},
    {OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC,  TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,  CT_RGHT},
  },
#ifndef MOUSEKEY_ENABLE
// ...................................................................... Qwerty

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   E  |   R  |   T  | Caps | Caps |   Y  |   U  |   I  |   O  |   P  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   S  |   D  |   F  |   G  | ^Alt | BLit |   H  |   J  |   K  |   L  |   ;  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   C  |   V  |   B  |  Tab | Bksp |   N  |   M  |   ,  |   .  |   "  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  |Right |
  // `-----------------------------------------------------------------------------------'

  [_QWERTY] = {
    {KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    TD_CAPS,  TD_CAPS,  KC_Y,    KC_U,    KC_I,    KC_O,   KC_P   },
    {KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    OS_CALT,  BACKLIT,  KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN},
    {KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    LT_TAB,   LT_BSPC,  KC_N,    KC_M,    KC_COMM, KC_DOT, TD_QUOT},
    {OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,   LT_BSPC,  TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,  CT_RGHT},
  },

// ...................................................................... Plover
//
// http://www.keyboard-layout-editor.com/#/gists/7296e3f601a6bb2eee2aa8f034c58a27

  // ,-----------------------------------------------------------------------------------.
  // |   #  |   #  |   #  |   #  |   #  |      |   #  |   #  |   #  |   #  |   #  |   #  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   S  |   T  |   P  |   H  |   *  |      |   *  |   F  |   P  |   L  |   T  |   D  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   S  |   K  |   W  |   R  |   *  |      |   *  |   R  |   B  |   G  |   S  |   Z  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // |      |      |   A  |   O  |      |      |      |   E  |   U  |      |      | Exit |
  // `-----------------------------------------------------------------------------------'

  [_PLOVER] = {
    {KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    _______, KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   },
    {KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC},
    {KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, UK_QUOT},
    {_______, _______, KC_C,    KC_V,    _______, _______, _______, KC_N,    KC_M,    _______, _______, PLOVEX },
  },
#endif
// ............................................................... Shift Colemak
//
// http://www.keyboard-layout-editor.com/#/gists/3e7b27b824d0c8b71f07354170756803

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   F  |   P  |   B  |^Shift|^Shift|   J  |   L  |   U  |   Y  |   !  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   G  | ^Alt | ^GUI |   K  |   N  |   E  |   I  |   O  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   C  |   D  |   V  |  Tab |  Ins |   M  |   H  |   /  |   ?  |   "  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   -  | Left | Down |  Up  |Right |
  // `-----------------------------------------------------------------------------------'

  [_LCOLEMAK] = {
    {S(KC_Q), S(KC_W), S(KC_F), S(KC_P), S(KC_B), OS_CSFT, OS_CSFT, S(KC_J), S(KC_L), S(KC_U), S(KC_Y), KC_EXLM},
    {S(KC_A), S(KC_R), S(KC_S), S(KC_T), S(KC_G), OS_CALT, OS_CGUI, S(KC_K), S(KC_N), S(KC_E), S(KC_I), S(KC_O)},
    {S(KC_Z), S(KC_X), S(KC_C), S(KC_D), S(KC_V), LT_TAB,  KC_INS,  S(KC_M), S(KC_H), KC_SLSH, KC_QUES, TD_QUOT},
    {OS_CTL,   OS_GUI, OS_ALT,  LT_ESC,  ___x___, LT_TAB,  KC_DEL,  KC_MINS, PS_LEFT, S_DOWN,  S_UP,    S_RGHT },
  },

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   F  |   P  |   B  | Caps |^Shift|   J  |   L  |   U  |   Y  |   :  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   G  | ↑Alt | ↑GUI |   K  |   N  |   E  |   I  |   O  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   C  |   D  |   V  | ↑Tab | Bksp |   M  |   H  |   #  |   ~  |   @  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |   _  | ↑Tab | Bksp |  f() | Left | Down |  Up  |Right |
  // `-----------------------------------------------------------------------------------'

  [_RCOLEMAK] = {
    {S(KC_Q), S(KC_W), S(KC_F), S(KC_P), S(KC_B), TD_CAPS, OS_CSFT, S(KC_J), S(KC_L), S(KC_U), S(KC_Y), KC_COLN},
    {S(KC_A), S(KC_R), S(KC_S), S(KC_T), S(KC_G), OS_SALT, OS_SGUI, S(KC_K), S(KC_N), S(KC_E), S(KC_I), S(KC_O)},
    {S(KC_Z), S(KC_X), S(KC_C), S(KC_D), S(KC_V), PS_TAB,  LT_BSPC, S(KC_M), S(KC_H), UK_HASH, UK_TILD,  UK_AT },
    {OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  KC_UNDS, PS_TAB,  LT_BSPC, ___x___, PS_LEFT, S_DOWN,  S_UP,    S_RGHT },
  },
#ifndef MOUSEKEY_ENABLE
// ................................................................ Shift QWERTY

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   E  |   R  |   T  | Caps |^Shift|   Y  |   U  |   I  |   O  |   P  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   S  |   D  |   F  |   G  | ^Alt | ^GUI |   H  |   J  |   K  |   L  |   :  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   C  |   V  |   B  |  Tab |  Ins |   N  |   M  |   /  |   ?  |   "  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   -  | Left | Down |  Up  |Right |
  // `-----------------------------------------------------------------------------------'

  [_LQWERTY] = {
    {S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), TD_CAPS, OS_CSFT, S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P)},
    {S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G), OS_SALT, OS_SGUI, S(KC_H), S(KC_J), S(KC_K), S(KC_L), KC_COLN},
    {S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), LT_TAB,  KC_INS,  S(KC_N), S(KC_M), KC_SLSH, KC_QUES, KC_DQT },
    {OS_CTL,   OS_GUI, OS_ALT,  LT_ESC,  ___x___, LT_TAB,  KC_DEL,  KC_MINS, PS_LEFT, S_DOWN,  S_UP,    S_RGHT },
  },

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   E  |   R  |   T  | Caps |^Shift|   Y  |   U  |   I  |   O  |   P  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   S  |   D  |   F  |   G  | ^Alt | ^GUI |   H  |   J  |   K  |   L  |   :  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   C  |   V  |   B  | ↑Tab | Bksp |   N  |   M  |   ~  |   `  |   "  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |   _  | ↑Tab | Bksp |  f() | Left | Down |  Up  |Right |
  // `-----------------------------------------------------------------------------------'

  [_RQWERTY] = {
    {S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), TD_CAPS, OS_CSFT, S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P)},
    {S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G), OS_CALT, OS_CGUI, S(KC_H), S(KC_J), S(KC_K), S(KC_L), KC_COLN},
    {S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), PS_TAB,  LT_BSPC, S(KC_N), S(KC_M), UK_TILD, KC_GRV,  KC_DQT },
    {OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  KC_UNDS, PS_TAB,  LT_BSPC, ___x___, PS_LEFT, S_DOWN,  S_UP,    S_RGHT },
  },
#endif
// ......................................................... Number Keypad Layer
//
// http://www.keyboard-layout-editor.com/#/gists/538d5196b49574fffda305a0f845c794

  // .-----------------------------------------------------------------------------------.
  // |   {  |   £  |   €  | ^Alt |   }  |PrntSc|PrntSc|   \  |   7  |   8  |   9  |   /  |
  // |-----------------------------------------------------------------------------------|
  // |   (  | Ctrl |  GUI |  Alt |   )  |      |      |   #  |   4  |   5  |   6  |   *  |
  // |-----------------------------------------------------------------------------------|
  // |   [  |   <  |   >  | ↑Alt |   ]  |      |      |   ^  |   1  |   2  |   3  |   -  |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |  f() |      |       |      |  =  |   0  |   .  |   :  |   +  |
  // '-----------------------------------------------------------------------------------'

  [_NUMBER] = {
    {TD_LCBR, UK_PND,  UK_EURO, OS_CALT, KC_RCBR, KC_PSCR, KC_PSCR, UK_BSLS, KC_7, KC_8,   KC_9,    KC_PSLS},
    {TD_LPRN, OS_CTL,  OS_GUI,  OS_ALT,  KC_RPRN, _______, _______, UK_HASH, KC_4, KC_5,   KC_6,    KC_PAST},
    {TD_LBRC, TD_LT,   KC_GT,   OS_SALT, KC_RBRC, ___x___, ___x___, KC_CIRC, KC_1, KC_2,   KC_3,    KC_PMNS},
    {___x___, ___x___, ___x___, ___x___, KC_FN5,  ___x___, ___x___, KC_EQL,  KC_0, KC_DOT, KC_COLN, KC_PPLS},
  },

// ................................................................ Symbol Layer
//
// http://www.keyboard-layout-editor.com/#/gists/b14e93e60f484a7e7c0d89351ea5c663

  // .-----------------------------------------------------------------------------------.
  // |   {  |   .  |   *  |   &  |   }  |      |      | PgUp | Home |  Up  |  End |      |
  // |-----------------------------------------------------------------------------------|
  // |   (  |   ^  |   %  |   $  |   )  |      |      | PgDn | Left | Down | Right|Reghex|
  // |-----------------------------------------------------------------------------------|
  // |   [  |   #  |   @  |   !  |   ]  |      |      |      | PgDn | PgUp |      |      |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |   \  |   |  |      |      |      |  f() |      |      |      |
  // '-----------------------------------------------------------------------------------'

  [_SYMBOL] = {
    {TD_LCBR, KC_DOT,  KC_ASTR, KC_AMPR, KC_RCBR, _______, _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______},
    {TD_LPRN, KC_CIRC, KC_PERC, KC_DLR,  KC_RPRN, _______, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, MO_RHEX},
    {TD_LBRC, KC_GRV,  UK_NOT,  UK_PND,  KC_RBRC, ___x___, ___x___, _______, KC_PGDN, KC_PGUP, _______, _______},
    {___x___, ___x___, ___x___, UK_BSLS, PS_PIPE, ___x___, ___x___, KC_FN5,  ___x___, ___x___, ___x___, ___x___},
  },

// ....................................................... Number Symbol Overlay
//
// http://www.keyboard-layout-editor.com/#/gists/a5af1dc7defc033feac465339f0cd6bc

  // .-----------------------------------------------------------------------------------.
  // |      |   ?  |   +  |   ~  | Wb_Hm| Stop | Stop |M5_Clk|M1_Clk|   ↑  |M2_Clk|Select|
  // |-----------------------------------------------------------------------------------|
  // |  f() | Wb_Bk| Wb_Rf| Wb_Fd|Wb_Stp| Eject| Play |M4_Clk|   ←  |   ↓  |   →  |  f() |
  // |-----------------------------------------------------------------------------------|
  // |      |   <  |   >  |   =  |Wb_Sch|MW_Lft|MW_Rgt| MW_Up|M3_Clk| Play | Mute |      |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |   :  |      |      |      | MW_Dn| Prev | Vol- | Vol+ | Next |
  // '-----------------------------------------------------------------------------------'
#ifdef MOUSEKEY_ENABLE
  [_REGHEX] = {
    {___x___, KC_QUES, KC_PLUS, UK_TILD, KC_WHOM, KC_MSTP, KC_MSTP, KC_BTN5, KC_BTN1, KC_MS_U, KC_BTN2, KC_MSEL},
    {___x___, KC_WBAK, KC_WREF, KC_WFWD, KC_WSTP, KC_EJCT, KC_MPLY, KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R, ___x___},
    {___x___, TD_LT,   KC_GT,   KC_EQL,  KC_WSCH, KC_WH_L, KC_WH_R, KC_WH_U, KC_BTN3, KC_MPLY, KC_MUTE, ___x___},
    {___x___, ___x___, ___x___, KC_COLN, KC_LSFT, ___x___, ___x___, KC_WH_D, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT},
  },
#else
  [_REGHEX] = {
    {___x___, KC_QUES, KC_PLUS, UK_TILD, KC_WHOM, KC_MSTP, KC_MSTP, KC_PMNS, KC_KP_5, KC_KP_8, KC_PDOT, KC_NLCK},
    {___x___, KC_WBAK, KC_WREF, KC_WFWD, KC_WSTP, KC_EJCT, KC_MPLY, KC_PSLS, KC_KP_4, KC_KP_2, KC_KP_6, ___x___},
    {___x___, TD_LT,   KC_GT,   KC_EQL,  KC_WSCH, ___x___, ___x___, KC_PAST, KC_KP_0, KC_MPLY, KC_MUTE, ___x___},
    {___x___, ___x___, ___x___, KC_COLN, KC_LSFT, ___x___, ___x___, ___x___, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT},
  },
#endif
// ...................................................... Shift Navigation Layer
//
// http://www.keyboard-layout-editor.com/#/gists/3e7b27b824d0c8b71f07354170756803
// http://www.keyboard-layout-editor.com/#/gists/b14e93e60f484a7e7c0d89351ea5c663

  // .-----------------------------------------------------------------------------------.
  // |      |      |      |      |      |      |      |      | ↑Home|  ↑Up | ↑End |      |
  // |-----------------------------------------------------------------------------------|
  // |      | Ctrl |  GUI |  Alt |      |      |      |      | ↑Left| ↑Down|↑Right|      |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |      |      |      | ↑PgDn| ↑PgUp|      |      |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |  f() |      |      |      |  f() |      |      |      |
  // '-----------------------------------------------------------------------------------'

  [_SFTNAV] = {
    {_______, _______, _______, _______, _______, _______, _______, _______, S_HOME,  S_UP,    S_END,   _______},
    {_______, OS_CTL,  OS_GUI,  OS_ALT,  _______, _______, _______, _______, S_LEFT,  S_DOWN,  S_RGHT,  _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, S_PGDN,  S_PGUP,  _______, _______},
    {_______, _______, _______, _______, ___x___, _______, _______, _______, ___x___, _______, _______, _______},
  },

// ............ .................................................. Function Keys
//
// http://www.keyboard-layout-editor.com/#/gists/d937a7bb9dec5dc6e73b28bf95d4d517

  // .-----------------------------------------------------------------------------------.
  // |      |      |      | Pause|      |      |      |      |  F7  |  F8  |  F9  |  F12 |
  // |-----------------------------------------------------------------------------------|
  // | Ctrl |  GUI |  Alt | Shift| Send |      |      |      |  F4  |  F5  |  F6  |  F11 |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |  f() |  App |      |  F1  |  F2  |  F3  |  F10 |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |  f() |  f() |   +  |  App |      |      |      |
  // '-----------------------------------------------------------------------------------'

  [_FNCKEY] = {
    {_______, _______, _______, KC_PAUS, _______, _______, _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F12 },
    {OS_SFT,  OS_CTL,  OS_GUI,  OS_ALT,  TD_SEND, KC_CALC, KC_MYCM, _______, KC_F4,   KC_F5,   KC_F6,   KC_F11 },
    {_______, _______, _______, _______, KC_EQL,  ___x___, KC_APP,  _______, KC_F1,   KC_F2,   KC_F3,   KC_F10 },
    {_______, _______, _______, _______, _______, ___x___, ___x___, KC_PLUS, KC_APP,  _______, _______, _______},
  },

// ................................................................ Adjust Layer
//
// http://www.keyboard-layout-editor.com/#/gists/ac56b98d8737118f2beef3d6855d760e

  // ,-----------------------------------------------------------------------------------.
  // | Power| Power|      | Sleep| Wake |      |      | BkLit|      | NKRO |      | Reset|
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |AGnorm|Voice-|Audoff|Musoff|MIDIof|      |      |Qwerty|Colemk|      |      |      |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |AGswap|Voice+|Aud on|Mus on|MIDIon| Menu |  f() |      |      |   <  |   >  |      |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // |      |      |      | Menu |   =  |  f() |  f() |      |      |      |      |Plover|
  // `-----------------------------------------------------------------------------------'
#ifndef MOUSEKEY_ENABLE
  [_ADJUST] = {
    {KC_PWR, KC_POWER, _______, KC_SLEP, KC_WAKE, _______, _______, BACKLIT, _______, TG_NKRO, _______, RESET  },
    {AG_NORM, MUV_DE,  AU_OFF,  MU_OFF,  MI_OFF,  _______, _______, QWERTY,  COLEMAK, _______, _______, _______},
    {AG_SWAP, MUV_IN,  AU_ON,   MU_ON,   MI_ON,   KC_MENU, ___x___, _______, _______, TD_LT,   KC_GT,   _______},
    {_______, _______, _______, KC_MENU, KC_EQL,  ___x___, ___x___, _______, _______, _______, _______, PLOVER },
  },
#else
  [_ADJUST] = {
    {KC_PWR, KC_POWER, _______, KC_SLEP, KC_WAKE, _______, _______, BACKLIT, _______, TG_NKRO, _______, RESET  },
    {AG_NORM, MUV_DE,  AU_OFF,  MU_OFF,  MI_OFF,  _______, _______, _______, COLEMAK, _______, _______, _______},
    {AG_SWAP, MUV_IN,  AU_ON,   MU_ON,   MI_ON,   KC_MENU, ___x___, _______, _______, TD_LT,   KC_GT,   _______},
    {_______, _______, _______, KC_MENU, KC_EQL,  ___x___, ___x___, _______, _______, _______, _______, _______},
  },
#endif
};

const uint16_t PROGMEM fn_actions[] = {
  ACTION_SWAP_HANDS_TAP_KEY(KC_SPC),
  ACTION_SWAP_HANDS_TOGGLE(),
  ACTION_SWAP_HANDS_TAP_TOGGLE(),
  ACTION_SWAP_HANDS_ON(),
  ACTION_SWAP_HANDS_OFF(),
  ACTION_SWAP_HANDS_TAP_TOGGLE(),
};

#ifdef AUDIO_ENABLE
#define CAPSLOCK_ON_SOUND   E__NOTE(_E7)  \
                           ,Q__NOTE(_GS7)
#define CAPSLOCK_OFF_SOUND  E__NOTE(_GS7) \
                           ,Q__NOTE(_E7)
float tone_startup  [][2] = SONG   (ZELDA_PUZZLE);
float tone_colemak  [][2] = SONG   (COLEMAK_SOUND);
#ifndef MOUSEKEY_ENABLE
float tone_qwerty   [][2] = SONG   (QWERTY_SOUND);
float tone_plover   [][2] = SONG   (PLOVER_SOUND);
float tone_plover_gb[][2] = SONG   (PLOVER_GOODBYE_SOUND);
float tone_numlk_on [][2] = SONG   (NUM_LOCK_ON_SOUND);
float tone_numlk_off[][2] = SONG   (NUM_LOCK_OFF_SOUND);
#endif
float tone_caps_on  [][2] = SONG   (CAPSLOCK_ON_SOUND);
float tone_caps_off [][2] = SONG   (CAPSLOCK_OFF_SOUND);/*
float tone_scroll_on[][2] = SONG   (SCROLL_LOCK_ON_SOUND);
float tone_scroll_off[][2]= SONG   (SCROLL_LOCK_OFF_SOUND);*/
float music_scale   [][2] = SONG   (MUSIC_SCALE_SOUND);
float tone_goodbye  [][2] = SONG   (GOODBYE_SOUND);
#endif

// .......................................................... Keycode Primitives

// register simple key press
void tap_key(uint16_t keycode)
{
  register_code  (keycode);
  unregister_code(keycode);
}

void shift_key(uint16_t keycode)
{
  register_code  (KC_LSFT);
  tap_key        (keycode);
  unregister_code(KC_LSFT);
}

static uint16_t key_timer = 0;

// key press for com_layer() and lts_layer() macros
bool key_press(uint16_t keycode)
{
  if (keycode) {
    if (timer_elapsed(key_timer) < TAPPING_TERM) {
      shift_key(keycode);
      return true;
    }
  }
  return false;
}

// ................................................................... Mod Masks

// tap dance persistant mods, see process_record_user()
// keyboard_report->mods (?) appears to be cleared by tap dance
static uint8_t mods = 0;

void tap_mods(keyrecord_t *record, uint16_t keycode)
{
  if (record->event.pressed) {
    mods |= MOD_BIT(keycode);
  }
  else {
    mods &= ~(MOD_BIT(keycode));
  }
}

// (un)register modifiers
void modifier(void (*f)(uint8_t))
{
  if (mods & MOD_BIT(KC_LCTL)) {
    (*f)(KC_LCTL);
  }
  if (mods & MOD_BIT(KC_LGUI)) {
    (*f)(KC_LGUI);
  }
  if (mods & MOD_BIT(KC_LALT)) {
    (*f)(KC_LALT);
  }
}

// ......................................................... Tap Dance Sequences

// tap dance LT (LAYER, KEY) emulation with <KEY><DOWN> -> <KEY><SHIFT> and auto-repeat extensions!
void tap_shift(qk_tap_dance_state_t *state, uint16_t keycode, uint8_t layer)
{
  // double tap plus down: repeating keycode
  if (state->count > 2) {
    register_code(keycode);
  }
  // tap plus down: keycode shift
  else if (state->count > 1) {
    layer_on(layer);
    tap_key (keycode);
  }
  // down: shift
  else if (state->pressed) {
    layer_on(layer);
  }
  // tap: keycode
  else {
    modifier(register_code);
    tap_key (keycode);
    modifier(unregister_code);
  }
}

void tap_reset(uint16_t keycode, uint8_t layer)
{
  unregister_code(keycode);
  layer_off      (layer);
}

// augment pseudo LT (_RSHIFT, KC_ENT) handling below for rapid <ENTER><SHIFT> sequences
void enter(qk_tap_dance_state_t *state, void *user_data)
{
  tap_shift(state, KC_ENT, _RSHIFT);
}

void enter_reset(qk_tap_dance_state_t *state, void *user_data)
{
  tap_reset(KC_ENT, _RSHIFT);
}

// augment pseudo LT (_LSHIFT, KC_SPC) handling below for rapid <SPACE><SHIFT> sequences
void space(qk_tap_dance_state_t *state, void *user_data)
{
  tap_shift(state, KC_SPC, _LSHIFT);
}

void space_reset(qk_tap_dance_state_t *state, void *user_data)
{
  tap_reset(KC_SPC, _LSHIFT);
}

// ............................................................. Tap Dance Pairs

// tap dance shift rules
#define S_NEVER  0
#define S_SINGLE 1
#define S_DOUBLE 2
#define S_ALWAYS S_SINGLE | S_DOUBLE

// tap dance symbol pairs
void tap_pair(qk_tap_dance_state_t *state, uint8_t shift, uint16_t left, uint16_t right, uint8_t layer)
{
  // double tap: left right
  if (state->count > 1) {
    if (shift & S_DOUBLE) {
      shift_key(left);
      shift_key(right);
    }
    else {
      tap_key(left);
      tap_key(right);
    }
#ifdef VIM_CURSOR
    // place cursor between symbol pair a la vim :-)
    tap_key(KC_LEFT);
#endif
  }
  // down: layer
  else if (state->pressed) {
    if (layer) {
      layer_on(layer);
    }
  }
  // tap: left
  else {
    if (shift & S_SINGLE) {
      shift_key(left);
    }
    else {
      tap_key(left);
    }
  }
  reset_tap_dance(state);
}

void paren(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_9, KC_0, _REGHEX);
}

void paren_reset(qk_tap_dance_state_t *state, void *user_data)
{
  layer_off(_REGHEX);
}

void angle(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_COMM, KC_DOT, 0);
}

void brace(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_NEVER, KC_LBRC, KC_RBRC, 0);
}

void curly(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_LBRC, KC_RBRC, 0);
}

void quote(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, UK_QUOT, UK_QUOT, 0);
}

// ............................................................ Tap Dance Single

void caps(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    tap_key(KC_CAPS);
  }
  else {
    set_oneshot_mods(MOD_LSFT);
  }
  reset_tap_dance(state);
}

void send(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
//#ifdef COMPILE_STRING
//#include "compile_string.h"
//#endif
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [_CAPS] = ACTION_TAP_DANCE_FN         (caps)
 ,[_ENT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, enter, enter_reset)
 ,[_LBRC] = ACTION_TAP_DANCE_FN         (brace)
 ,[_LCBR] = ACTION_TAP_DANCE_FN         (curly)
 ,[_LPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, paren, paren_reset)
 ,[_LT]   = ACTION_TAP_DANCE_FN         (angle)
 ,[_QUOT] = ACTION_TAP_DANCE_FN         (quote)
 ,[_SEND] = ACTION_TAP_DANCE_FN         (send)
 ,[_SPC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, space, space_reset)
};

// .............................................................. Dynamic Layers

#define        LEFT    1
#define        RIGHT   2
static uint8_t thumb = 0;

// LEFT (KC_SPC, S(UK_BSLS)), RIGHT (KC_LEFT, S(KC_LEFT)) opposite thumb combinations, see process_record_user()
// up,   up   -> _COLEMAK
// up,   down -> _SYMBOL
// down, up   -> _NUMBER
// down, down -> _SFTNAV
#define THUMBS_DOWN _SFTNAV

static uint8_t overlayer = THUMBS_DOWN;

// left right layer combinations
void com_layer(keyrecord_t *record, uint8_t side, uint16_t keycode, uint8_t layer, uint8_t default_layer)
{
  if (record->event.pressed) {
    // layer_on via tap_layer(), see process_record_user()
    key_timer = timer_read();
    thumb     = thumb | side;
  }
  else {
    layer_off(layer);
    // opposite com_layer() thumb may have switched effective layer!
    if (overlayer) {
      layer_off(overlayer);
      overlayer = THUMBS_DOWN;
    }
    if (!key_press(keycode)) {
      // opposite thumb down? see left right combination layer table above
      if (thumb & (side == LEFT ? RIGHT : LEFT)) {
        layer_on(default_layer);
        overlayer = default_layer;
      }
    }
    clear_mods();
    thumb     = thumb & ~side;
    key_timer = 0;
  }
}

// LT for S(keycode)
void lts_layer(keyrecord_t *record, uint16_t keycode, uint8_t layer)
{
  if (record->event.pressed) {
    layer_on(layer);
    key_timer = timer_read();
  }
  else {
    layer_off(layer);
    // for shifted keycodes, hence, LT_SHIFT
    key_press(keycode);
    clear_mods();
    key_timer = 0;
  }
}

// set layer asap to overcome macro latency errors, notably tap dance and LT usage
// this routine inexplicably (?) sets layer_on() faster than can be done in com_layer()
void tap_layer(keyrecord_t *record, uint8_t layer)
{
  if (record->event.pressed) {
    layer_on(layer);
  }
  else {
    layer_off(layer);
  }
}

// ..................................................................... Keymaps

void persistant_default_layer_set(uint16_t default_layer)
{
  eeconfig_update_default_layer(default_layer);
  default_layer_set            (default_layer);
}

void clear_layers(void)
{
  uint8_t layer;
  for (layer = 0; layer <= _ADJUST; layer++) {
    layer_off(layer);
  }
}

void colemak(keyrecord_t *record)
{
  if (record->event.pressed) {
#ifdef AUDIO_ENABLE
    PLAY_NOTE_ARRAY(tone_colemak, false, 0);
#endif
    clear_layers();
    persistant_default_layer_set(1UL<<_COLEMAK);
    _LSHIFT = _LCOLEMAK;
    _RSHIFT = _RCOLEMAK;
  }
}
#ifndef MOUSEKEY_ENABLE
void qwerty(keyrecord_t *record)
{
  if (record->event.pressed) {
#ifdef AUDIO_ENABLE
    PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
#endif
    clear_layers();
    persistant_default_layer_set(1UL<<_QWERTY);
    _LSHIFT = _LQWERTY;
    _RSHIFT = _RQWERTY;
  }
}

void toggle_plover(void)
{
  // toggle window manager plover application, see herbstluftwm/config/appbinds
  register_code  (KC_LGUI);
  shift_key      (KC_RGHT);
  unregister_code(KC_LGUI);
}

void plover(keyrecord_t *record)
{
  if (record->event.pressed) {
#ifdef AUDIO_ENABLE
    PLAY_NOTE_ARRAY(tone_plover, false, 0);
#endif
    clear_layers();
    layer_on(_PLOVER);
    if (!eeconfig_is_enabled()) {
      eeconfig_init();
    }
    keymap_config.raw  = eeconfig_read_keymap();
    keymap_config.nkro = 1;
    eeconfig_update_keymap(keymap_config.raw);
    toggle_plover();
  }
}

void plovex(keyrecord_t *record)
{
  if (record->event.pressed) {
#ifdef AUDIO_ENABLE
    PLAY_NOTE_ARRAY(tone_plover_gb, false, 0);
#endif
    clear_layers();
    toggle_plover();
  }
}
#endif
// ........................................................... User Keycode Trap

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {
    case OS_CTL:
      tap_mods(record, KC_LCTL);
      break;
    case OS_GUI:
      tap_mods(record, KC_LGUI);
      break;
    case OS_ALT:
      tap_mods(record, KC_LALT);
      break;
    case AT_DOWN:
      tap_mods(record, KC_LALT);
      break;
    case GT_UP:
      tap_mods(record, KC_LGUI);
      break;
    case CT_RGHT:
      tap_mods(record, KC_LCTL);
      break;
    case LT_ESC:
      tap_layer(record, _NUMBER);
      break;
    case TD_SPC:
      tap_layer(record, _LSHIFT);
      // LT (_LSHIFT, KC_SPC) left right combination layer, see tap dance space
      com_layer(record, LEFT, 0, _LSHIFT, _SYMBOL);
      break;
    case TD_ENT:
      tap_layer(record, _RSHIFT);
      // LT (_RSHIFT, KC_ENT) emulation, see tap dance enter
      break;
    case PS_PIPE:
      tap_layer(record, _SFTNAV);
      // LT (_SFTNAV, S(UK_BSLS)) left right combination layer
      com_layer(record, LEFT, UK_BSLS, _SFTNAV, _SYMBOL);
      break;
    case PS_TAB:
      // LT (_FNCKEY, S(KC_TAB)) emulation
      lts_layer(record, KC_TAB, _FNCKEY);
      break;
    case LT_LEFT:
      tap_layer(record, _SYMBOL);
      // LT (_SYMBOL, KC_LEFT) left right combination layer
      com_layer(record, RIGHT, 0, _SYMBOL, _LSHIFT);
      break;
    case PS_LEFT:
      tap_layer(record, _SFTNAV);
      // LT (_SFTNAV, S(KC_LEFT)) left right combination layer
      com_layer(record, RIGHT, KC_LEFT, _SFTNAV, _LSHIFT);
      break;
    case COLEMAK:
      colemak(record);
      return false;
#ifndef MOUSEKEY_ENABLE
    case QWERTY:
      qwerty(record);
      return false;
    case PLOVER:
      plover(record);
      return false;
    case PLOVEX:
      plovex(record);
      return false;
#endif
    case BACKLIT:
      if (record->event.pressed) {
        //register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        //unregister_code(KC_RSFT);
      }
      return false;
      break;
  }
  return true;
}

// ....................................................................... Audio

void matrix_init_user(void)
{
#ifdef AUDIO_ENABLE
  startup_user();
#endif
}

#ifdef AUDIO_ENABLE
#ifdef BACKLIGHT_ENABLE
void led_set_user(uint8_t usb_led)
{
  static uint8_t old_usb_led = 0;
  _delay_ms(10);                            // gets rid of tick
  if (!is_playing_notes()) {
    if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK))) {
      // if capslock LED is turning on
      PLAY_NOTE_ARRAY(tone_caps_on,  false, 0);
    }
    else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK))) {
      // if capslock LED is turning off
      PLAY_NOTE_ARRAY(tone_caps_off, false, LEGATO);
    }
#ifndef MOUSEKEY_ENABLE
    else if ((usb_led & (1<<USB_LED_NUM_LOCK)) && !(old_usb_led & (1<<USB_LED_NUM_LOCK)))
    {
            // If NUM LK LED is turning on...
            PLAY_NOTE_ARRAY(tone_numlk_on,  false, LEGATO);
    }
    else if (!(usb_led & (1<<USB_LED_NUM_LOCK)) && (old_usb_led & (1<<USB_LED_NUM_LOCK)))
    {
            // If NUM LED is turning off...
            PLAY_NOTE_ARRAY(tone_numlk_off, false, LEGATO);
    }
#endif/*
    else if ((usb_led & (1<<USB_LED_SCROLL_LOCK)) && !(old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
    {
            // If SCROLL LK LED is turning on...
            PLAY_NOTE_ARRAY(tone_scroll_on,  false, LEGATO);
    }
    else if (!(usb_led & (1<<USB_LED_SCROLL_LOCK)) && (old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
    {
            // If SCROLL LED is turning off...
            PLAY_NOTE_ARRAY(tone_scroll_off, false, LEGATO);
    }*/
  }
  old_usb_led = usb_led;
}
#endif

void startup_user(void)
{
  _delay_ms(20);                            // gets rid of tick
  PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user(void)
{
  PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
  _delay_ms(150);
  stop_all_notes();
}

void music_on_user(void)
{
  music_scale_user();
}

void music_scale_user(void)
{
  PLAY_NOTE_ARRAY(music_scale, false, 0);
}
#endif
