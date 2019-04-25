#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _HARMONY 0
#define _HARMONY_SxS 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

enum custom_keycodes {
  HARMONY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST,
  EISU,
  ROMAJI,
  REPORT_PARAM,
  INC_PARAM,
  DEC_PARAM,
};

#include "romaji.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_HARMONY] = LAYOUT( 
  KC_Q,       KC_W,   KC_R,   KC_N,    KC_F,                          KC_J,    KC_U,    KC_O,    KC_L,   KC_P, \
  KC_K,       KC_S,   KC_T,   KC_H,    KC_M,                          KC_G,    KC_I,    KC_E,    KC_A,   KC_Y, \
  KC_Z,       KC_X,   KC_C,   KC_V,    KC_B,                          KC_MINS, KC_D,    KC_COMM, KC_DOT, KC_SLSH, \
  KC_ESC,     KC_LCTL,KC_LALT,KC_LGUI, LT(_RAISE,KC_TAB), SFT_T(KC_BSPC), \
                                                   LT(_LOWER,KC_ENT), KC_SPC,  KC_RGUI, KC_RALT, KC_RCTL, KC_BSPC
  ),

 [_LOWER] = LAYOUT( \
  KC_1   , KC_2   , KC_3 ,  KC_4 ,  KC_5 ,                        KC_6   , KC_7 ,   KC_8   , KC_9  ,  KC_0, \
  KC_SCLN, KC_LPRN, KC_RPRN,KC_QUOT,KC_GRV,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_ESC, \
  _______, KC_LBRC, KC_RBRC,_______,_______,                      KC_EQL , _______, _______, _______, KC_BSLS, \
  _______, _______, _______,_______,MO(_ADJUST) ,_______, \
                                                        _______,   _______, _______, _______, _______, KC_DEL 
  ),

 [_RAISE] = LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,  KC_F4,  KC_F5,                        KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10, \
  KC_F11,  KC_F12,  KC_F13, KC_F14, KC_F15,                       KC_HOME,KC_PGDN, KC_PGUP, KC_END,  _______, \
  _______, _______, _______,_______,_______,                      _______, _______, _______,_______, _______, \
  _______, _______, _______,_______,_______ ,_______, \
                                                        MO(_ADJUST),   _______, _______, _______, _______, KC_INS 
  ),

 [_ADJUST] = LAYOUT( \
  RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    KC_MUTE, KC_VOLU, KC_MPLY, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, HARMONY, XXXXXXX,              REPORT_PARAM,DEC_PARAM,INC_PARAM,XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS, KC_NLCK,                    XXXXXXX, XXXXXXX, EISU   , ROMAJI , XXXXXXX, \
  _______, _______, _______,_______,MO(_RAISE) ,_______, \
                                                        MO(_LOWER),   _______, _______, _______, _______, _______ 
  ) 
};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if( ! process_romaji(keycode,record) )
    return false;
  
  switch (keycode) {
    case HARMONY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_HARMONY);
      }
      return false;
    case EISU:
      if (record->event.pressed) {
        romaji_reset();
        _romaji_mode = false;

        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
    case ROMAJI:
      if (record->event.pressed) {
        romaji_reset();
        _romaji_mode = true;

        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
  }
  return true;
}

