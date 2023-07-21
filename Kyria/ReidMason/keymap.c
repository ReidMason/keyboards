/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "os_detection.h"

enum layers {
    _QWERTY = 0,
    _DVORAK,
    _COLEMAK_DH,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // This is the left side
    if (index == 0) {
    // The is the right side
      // Page up/Page down
      if (clockwise) {
        tap_code(KC_BRMU);
      } else {
        tap_code(KC_BRMD);
      }
    } else if (index == 1) {
        // Volume control
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
    }
    return false;
}
#endif

enum my_keycodes {
  HASH = SAFE_RANGE,
  CMD_CTL
};

// Aliases for readability
#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

// #define SFT_TAB  MT(KC_LSFT, KC_TAB)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

#define SFT_TAB LSFT_T(KC_TAB)
#define SFT_QOT RSFT_T(KC_QUOTE)

#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    // Custom hash key for windows and macos
    case HASH:
      if (record->event.pressed) {
        if (detected_host_os() == 3) { 
          tap_code16(LALT(KC_3));
        } else {
          tap_code16(KC_HASH);
        }
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    case CMD_CTL:
      if (record->event.pressed) {
        if (detected_host_os() == 3) { 
          register_code(KC_LGUI);
        } else {
          register_code(KC_RCTL);
        }
      } else {
        if (detected_host_os() == 3) { 
          unregister_code(KC_LGUI);
        } else {
          unregister_code(KC_RCTL);
        }
      }
      return false;
    default:
      return true; // Process all other keycodes normally
  }
}

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ╭─────────┬─────────┬─────────┬─────────┬─────────┬─────────╮                                                 ╭─────────┬─────────┬─────────┬─────────┬─────────┬─────────╮         
//    │ KC_ESC  │ KC_Q    │ KC_W    │ KC_E    │ KC_R    │ KC_T    │                                                 │ KC_Y    │ KC_U    │ KC_I    │ KC_O    │ KC_P    │ KC_BSPC │         
//    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                                                 ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         
//    │ SFT_TAB │ KC_A    │ KC_S    │ KC_D    │ KC_F    │ KC_G    │                                                 │ KC_H    │ KC_J    │ KC_K    │ KC_L    │ KC_SCLN │ SFT_QOT │         
//    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┬─────────╮         ╭─────────┬─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         
//    │ CMD_CTL │ KC_Z    │ KC_X    │ KC_C    │ KC_V    │ KC_B    │ KC_CPYP │ ADJUST  │         │ FKEYS   │         │ KC_N    │ KC_M    │ KC_COMM │ KC_DOT  │ KC_SLSH │ KC_RCTL │         
//    ╰─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────╯         
//                                  │ KC_LALT │ NAV     │ KC_LCTL │ KC_ENT  │ SYM     │         │ SYM     │ KC_SPC  │ NAV     │         │         │                                       
//                                  ╰─────────┴─────────┴─────────┴─────────┴─────────╯         ╰─────────┴─────────┴─────────┴─────────┴─────────╯                                       
[_QWERTY] = LAYOUT(
 KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                                                   KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,          
 SFT_TAB , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,                                                   KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , SFT_QOT ,          
 CMD_CTL , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_CPYP , ADJUST  ,           FKEYS   , _______ , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_RCTL ,          
                               KC_LALT , NAV     , KC_LCTL , KC_ENT  , SYM     ,           SYM     , KC_SPC  , NAV     , _______ , _______                                          
),

//    ╭─────────┬─────────┬─────────┬─────────┬─────────┬─────────╮                                                 ╭─────────┬─────────┬─────────┬─────────┬─────────┬─────────╮         
//    │         │         │         │         │         │         │                                                 │         │         │         │         │         │ KC_DEL  │         
//    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                                                 ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         
//    │         │ KC_LGUI │ KC_LALT │ KC_LCTL │ KC_LSFT │         │                                                 │ KC_LEFT │ KC_DOWN │ KC_UP   │ KC_RGHT │         │         │         
//    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┬─────────╮         ╭─────────┬─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         
//    │         │         │         │         │         │         │         │ KC_SCRL │         │         │         │         │         │         │         │         │         │         
//    ╰─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────╯         
//                                  │         │         │         │         │         │         │         │         │         │         │         │                                       
//                                  ╰─────────┴─────────┴─────────┴─────────┴─────────╯         ╰─────────┴─────────┴─────────┴─────────┴─────────╯                                       
[_NAV] = LAYOUT(
 _______ , _______ , _______ , _______ , _______ , _______ ,                                                   _______ , _______ , _______ , _______ , _______ , KC_DEL  ,          
 _______ , KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , _______ ,                                                   KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______ , _______ ,          
 _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_SCRL ,           _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,          
                               _______ , _______ , _______ , _______ , _______ ,           _______ , _______ , _______ , _______ , _______                                          
),

//    ╭─────────┬─────────┬─────────┬─────────┬─────────┬─────────╮                                                 ╭─────────┬─────────┬─────────┬─────────┬─────────┬─────────╮         
//    │ KC_GRV  │ KC_1    │ KC_2    │ KC_3    │ KC_4    │ KC_5    │                                                 │ KC_6    │ KC_7    │ KC_8    │ KC_9    │ KC_0    │ KC_EQL  │         
//    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                                                 ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         
//    │         │ KC_EXLM │ KC_AT   │ HASH    │ KC_DLR  │ KC_MINS │                                                 │ KC_UNDS │ KC_LPRN │ KC_RPRN │ KC_LBRC │ KC_RBRC │ KC_BSLS │         
//    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┬─────────╮         ╭─────────┬─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         
//    │         │ KC_BSLS │ KC_ASTR │ KC_AMPR │ KC_PERC │ KC_PLUS │         │         │         │         │         │         │ KC_LCBR │ KC_RCBR │         │         │         │         
//    ╰─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────╯         
//                                  │         │         │         │         │         │         │         │         │         │         │         │                                       
//                                  ╰─────────┴─────────┴─────────┴─────────┴─────────╯         ╰─────────┴─────────┴─────────┴─────────┴─────────╯                                       
[_SYM] = LAYOUT(
 KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                                                   KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_EQL  ,          
 _______ , KC_EXLM , KC_AT   , HASH    , KC_DLR  , KC_MINS ,                                                   KC_UNDS , KC_LPRN , KC_RPRN , KC_LBRC , KC_RBRC , KC_BSLS ,          
 _______ , KC_BSLS , KC_ASTR , KC_AMPR , KC_PERC , KC_PLUS , _______ , _______ ,           _______ , _______ , _______ , KC_LCBR , KC_RCBR , _______ , _______ , _______ ,          
                               _______ , _______ , _______ , _______ , _______ ,           _______ , _______ , _______ , _______ , _______                                          
),

//    ╭─────────┬─────────┬─────────┬─────────┬─────────┬─────────╮                                                 ╭─────────┬─────────┬─────────┬─────────┬─────────┬─────────╮         
//    │         │ KC_F9   │ KC_F10  │ KC_F11  │ KC_F12  │         │                                                 │         │         │         │         │         │         │         
//    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                                                 ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         
//    │         │ KC_F5   │ KC_F6   │ KC_F7   │ KC_F8   │         │                                                 │         │ KC_RSFT │ KC_RCTL │ KC_LALT │ KC_RGUI │         │         
//    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┬─────────╮         ╭─────────┬─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         
//    │         │ KC_F1   │ KC_F2   │ KC_F3   │ KC_F4   │         │         │         │         │         │         │         │         │         │         │         │         │         
//    ╰─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────╯         
//                                  │         │         │         │         │         │         │         │         │         │         │         │                                       
//                                  ╰─────────┴─────────┴─────────┴─────────┴─────────╯         ╰─────────┴─────────┴─────────┴─────────┴─────────╯                                       
[_FUNCTION] = LAYOUT(
 _______ , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ ,                                                   _______ , _______ , _______ , _______ , _______ , _______ ,          
 _______ , KC_F5   , KC_F6   , KC_F7   , KC_F8   , _______ ,                                                   _______ , KC_RSFT , KC_RCTL , KC_LALT , KC_RGUI , _______ ,          
 _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , _______ , _______ , _______ ,           _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,          
                               _______ , _______ , _______ , _______ , _______ ,           _______ , _______ , _______ , _______ , _______                                          
),

//    ╭──────────┬──────────┬──────────┬──────────┬──────────┬──────────╮                                                      ╭──────────┬──────────┬──────────┬──────────┬──────────┬──────────╮          
//    │          │          │          │          │          │          │                                                      │          │          │          │          │          │          │          
//    ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                                                      ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤          
//    │          │          │          │          │          │          │                                                      │ RGB_TOG  │ RGB_SAI  │ RGB_HUI  │ RGB_VAI  │ RGB_MOD  │          │          
//    ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┬──────────╮          ╭──────────┬──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤          
//    │          │          │          │          │          │          │          │          │          │          │          │          │ RGB_SAD  │ RGB_HUD  │ RGB_VAD  │ RGB_RMOD │          │          
//    ╰──────────┴──────────┴──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤          ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┴──────────┴──────────╯          
//                                     │          │          │          │          │          │          │          │          │          │          │          │                                           
//                                     ╰──────────┴──────────┴──────────┴──────────┴──────────╯          ╰──────────┴──────────┴──────────┴──────────┴──────────╯                                           
[_ADJUST] = LAYOUT(
 _______  , _______  , _______  , _______  , _______  , _______  ,                                                        _______  , _______  , _______  , _______  , _______  , _______  ,           
 _______  , _______  , _______  , _______  , _______  , _______  ,                                                        RGB_TOG  , RGB_SAI  , RGB_HUI  , RGB_VAI  , RGB_MOD  , _______  ,           
 _______  , _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , RGB_SAD  , RGB_HUD  , RGB_VAD  , RGB_RMOD , _______  ,           
                                  _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______                                               
),


};

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev3.1\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Symbols\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif

/* DELETE THIS LINE TO UNCOMMENT (1/2)
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif
DELETE THIS LINE TO UNCOMMENT (2/2) */
