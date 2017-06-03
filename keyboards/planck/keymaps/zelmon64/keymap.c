// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"
#include "led.h"
#include "mousekey.h"

#include "keymap_uk.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum planck_layers {
  _QWERTY,
  _CMODDH,
  _MOUSE,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  CMODDH,
  MOUSE,
  LOWER,
  RAISE,
  BACKLIT,
  // MACRO_BREATH_TOGGLE,
  // MACRO_BREATH_SPEED_INC,
  // MACRO_BREATH_SPEED_DEC,
//   MACRO_BREATH_DEFAULT,
/*
  MACRO_MOUSE_MOVE_UL,
  MACRO_MOUSE_MOVE_UR,
  MACRO_MOUSE_MOVE_DL,
  MACRO_MOUSE_MOVE_DR,
  */
};

// #define M_BACKL             M(MACRO_BACKLIGHT)
// #define M_BRTOG             M(MACRO_BREATH_TOGGLE)
// #define M_BSPDU             M(MACRO_BREATH_SPEED_INC)
// #define M_BSPDD             M(MACRO_BREATH_SPEED_DEC)
// #define M_BDFLT             M(MACRO_BREATH_DEFAULT)
/*
#define M_MS_UL             M(MACRO_MOUSE_MOVE_UL)
#define M_MS_UR             M(MACRO_MOUSE_MOVE_UR)
#define M_MS_DL             M(MACRO_MOUSE_MOVE_DL)
#define M_MS_DR             M(MACRO_MOUSE_MOVE_DR)
*/
#define TG_NKRO             MAGIC_TOGGLE_NKRO

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// #define MACRO_BREATH_TOGGLE             21
// #define MACRO_BREATH_SPEED_INC          23
// #define MACRO_BREATH_SPEED_DEC          24
// #define MACRO_BREATH_DEFAULT            25

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left |  Up  | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC       },
  {KC_ESC,         KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT       },
  {LSFT_T(KC_DEL), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT)},
  {_______,        KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT       }
},

/* Colemak Mod-DH
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   G  |   K  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   D  |   V  |   M  |   H  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Mouse| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | lead | Menu | Ctrl | Ins  |
 * `-----------------------------------------------------------------------------------'
 */
[_CMODDH] = {
  {KC_TAB,         KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN,   KC_BSPC       },
  {KC_ESC,         KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_K,    KC_N,    KC_E,    KC_I,   KC_O,      KC_QUOT       },
  {LSFT_T(KC_DEL), KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_M,    KC_H,    KC_COMM, KC_DOT, KC_SLSH,   RSFT_T(KC_ENT)},
  {MOUSE,          KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEAD, KC_APP, KC_RCTL,   KC_INS        }
},

/* Mouse and Number layer
 * ,-----------------------------------------------------------------------------------.
 * |      |  NL  |   7  |   8  |   9  |   =  |M5_Clk|M1_Clk|  ↑   |M2_Clk|MW_Up |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Alt |   /  |   4  |   5  |   6  |   -  |M4_Clk|  ←   |  ↓   |  →   |MW_Dn | Alt  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   *  |   1  |   2  |   3  |   +  | Ctrl |M3_Clk|MW_Lft|MW_Rgt|  Up  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |CModDH|   ^  |   0  |   .  |Lower |    Enter    |Raise | Ctrl | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */

[_MOUSE] = {
  {XXXXXXX, KC_NLCK, KC_P7, KC_P8,   KC_P9,   KC_EQL,  KC_BTN5, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______},
  {KC_LALT, KC_PSLS, KC_P4, KC_P5,   KC_P6,   KC_PMNS, KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_LGUI},
  {_______, KC_PAST, KC_P1, KC_P2,   KC_P3,   KC_PPLS, KC_LCTL, KC_BTN3, KC_WH_L, KC_WH_R, KC_UP,   _______},
  {CMODDH,  S(KC_6), KC_P0, KC_PDOT, LOWER,   KC_PENT, KC_PENT, RAISE,   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ¬  |  F1  |  F2  |  F3  |  F4  |   £  |   $  | Prev |  Up  | Next | Vol+ | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |PrntSc|  F5  |  F6  |  F7  |  F8  |   !  |   %  | Left | Down |Right | Vol- |  &   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Bksp |  F9  |  F10 |  F11 |  F12 |   ^  |   *  |   +  |   _  |   ~  |   |  | Play |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |     Tab     |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {UK_NOT,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   UK_PND,  KC_DLR,  KC_MPRV, KC_UP,   KC_MNXT, KC_VOLU, KC_DEL         },
  {KC_PSCR,         KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_EXLM, KC_PERC, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_AMPR        },
  {LSFT_T(KC_BSPC), KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_CIRC, KC_ASTR, KC_PLUS, KC_UNDS, UK_TILD, UK_PIPE, RSFT_T(KC_MPLY)},
  {_______,         _______, _______, _______, _______, KC_TAB,  KC_TAB,  _______, _______, _______, _______, _______        }
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   ¦  |   7  |   8  |   9  |   {  |   }  | Home |  Up  | End  |Pg Up | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |PrntSc|   €  |   4  |   5  |   6  |   [  |   ]  | Left | Down |Right |Pg Dn |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Bksp |   0  |   1  |   2  |   3  |   (  |   )  |   =  |   -  |   #  |   \  | Mute |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |     Tab     |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,          UK_BRKP, KC_7,    KC_8,    KC_9,    KC_LCBR, KC_RCBR, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_DEL         },
  {LALT(KC_PSCR),   UK_EURO, KC_4,    KC_5,    KC_6,    KC_LBRC, KC_RBRC, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, UK_QUOT        },
  {LSFT_T(KC_BSPC), KC_0,    KC_1,    KC_2,    KC_3,    KC_LPRN, KC_RPRN, KC_EQL,  KC_MINS, UK_HASH, UK_BSLS, RSFT_T(KC_MUTE)},
  {_______,         _______, _______, _______, _______, KC_TAB,  KC_TAB,  _______, _______, _______, _______, _______        }
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      | BRTOG|BRSPD+|BRSPD-|BRDFLT|BACKLT|      | Sroll| Caps | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|CModDH| Mouse|      | Ins  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      | NKRO |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
 {_______, RESET,   _______, _______, _______, _______, _______, BACKLIT, _______, KC_SLCK, KC_CAPS, KC_DEL },
 {_______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  CMODDH,  MOUSE,   _______, KC_INS },
 {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
 {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TG_NKRO}
}


};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_colemakdh[][2]  = SONG(ZELDA_ITEM);
float tone_mouse[][2]      = SONG(ZELDA_PUZZLE);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] =    SONG(GOODBYE_SOUND);

float tone_audio_on[][2]   = SONG(CLOSE_ENCOUNTERS_5_NOTE);
float tone_music_on[][2]   = SONG(DOE_A_DEER);
float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
float tone_caps_off[][2]   = SONG(CAPS_LOCK_OFF_SOUND);
float tone_numlk_on[][2]   = SONG(NUM_LOCK_ON_SOUND);
float tone_numlk_off[][2]  = SONG(NUM_LOCK_OFF_SOUND);
float tone_scroll_on[][2]  = SONG(SCROLL_LOCK_ON_SOUND);
float tone_scroll_off[][2] = SONG(SCROLL_LOCK_OFF_SOUND);

#endif /* AUDIO_ENABLE */


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
/*
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case MACRO_BREATH_TOGGLE:
        if (record->event.pressed)
        {
            breathing_toggle();
        }
        break;

    case MACRO_BREATH_SPEED_INC:
        if (record->event.pressed)
        {
            breathing_speed_inc(1);
        }
        break;

    case MACRO_BREATH_SPEED_DEC:
        if (record->event.pressed)
        {
            breathing_speed_dec(1);
        }
        break;

    case MACRO_BREATH_DEFAULT:
        if (record->event.pressed)
        {
            breathing_defaults();
        }
        break;
  }
  return MACRO_NONE;
}
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case CMODDH:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemakdh, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_CMODDH);
      }
      return false;
      break;
    case MOUSE:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_mouse, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_MOUSE);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;

//#ifdef MOUSEKEY_ENABLE
/*
        case MACRO_MOUSE:
            if (record->event.pressed)
            {
                layer_invert(LAYER_MOUSE);
            }
            break;
*
        case MACRO_MOUSE_MOVE_UL:
            if (record->event.pressed)
            {
              mousekey_on(KC_MS_UP);
              mousekey_on(KC_MS_LEFT);
            }
            else
            {
              mousekey_off(KC_MS_UP);
              mousekey_off(KC_MS_LEFT);
            }
            break;

        case MACRO_MOUSE_MOVE_UR:
            if (record->event.pressed)
            {
              mousekey_on(KC_MS_UP);
              mousekey_on(KC_MS_RIGHT);
            }
            else
            {
              mousekey_off(KC_MS_UP);
              mousekey_off(KC_MS_RIGHT);
            }
            break;

        case MACRO_MOUSE_MOVE_DL:
            if (record->event.pressed)
            {
              mousekey_on(KC_MS_DOWN);
              mousekey_on(KC_MS_LEFT);
            }
            else
            {
              mousekey_off(KC_MS_DOWN);
              mousekey_off(KC_MS_LEFT);
            }
            break;

        case MACRO_MOUSE_MOVE_DR:
            if (record->event.pressed)
            {
              mousekey_on(KC_MS_DOWN);
              mousekey_on(KC_MS_RIGHT);
            }
            else
            {
              mousekey_off(KC_MS_DOWN);
              mousekey_off(KC_MS_RIGHT);
            }
            break;
*/
//#endif /* MOUSEKEY_ENABLE */
}
return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void led_set_user(uint8_t usb_led)
{
    static uint8_t old_usb_led = 0;

    _delay_ms(10); // gets rid of tick

    if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
            // If CAPS LK LED is turning on...
            PLAY_NOTE_ARRAY(tone_caps_on,  false, LEGATO);
    }
    else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
            // If CAPS LK LED is turning off...
            PLAY_NOTE_ARRAY(tone_caps_off, false, LEGATO);
    }
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
    else if ((usb_led & (1<<USB_LED_SCROLL_LOCK)) && !(old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
    {
            // If SCROLL LK LED is turning on...
            PLAY_NOTE_ARRAY(tone_scroll_on,  false, LEGATO);
    }
    else if (!(usb_led & (1<<USB_LED_SCROLL_LOCK)) && (old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
    {
            // If SCROLL LED is turning off...
            PLAY_NOTE_ARRAY(tone_scroll_off, false, LEGATO);
    }
    old_usb_led = usb_led;
}

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, STACCATO);
    _delay_ms(2000);
    stop_all_notes();
}

void audio_on_user(void)
{
	PLAY_NOTE_ARRAY(tone_audio_on, false, STACCATO);
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
