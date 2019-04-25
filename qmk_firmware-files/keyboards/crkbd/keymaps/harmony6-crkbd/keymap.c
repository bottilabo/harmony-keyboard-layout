#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _HARMONY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3


enum custom_keycodes {
  HARMONY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  EISU,
  ROMAJI,
  REPORT_PARAM,
  INC_PARAM,
  DEC_PARAM,
};



#include "romaji.c"
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_HARMONY] = LAYOUT( \
  //,-----------------------------------------------.                ,----------------------------------------------.
     KC_ESC ,KC_Q   ,KC_W   ,KC_R   ,KC_N   ,KC_F                    ,KC_J   ,KC_U   ,KC_O   ,KC_L   ,KC_P   ,KC_BSPC, \
  //|-------+-------+-------+-------+-------+-------|                |-------+-------+-------+-------+-------+------|
     KC_LALT,KC_K   ,KC_S   ,KC_T   ,KC_H   ,KC_M                    ,KC_G   ,KC_I   ,KC_E   ,KC_A   ,KC_Y   ,KC_ENT, \
  //|-------+-------+-------+-------+-------+-------|                |-------+-------+-------+-------+-------+------|
     KC_LCTL,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B                    ,KC_MINS,KC_D   ,KC_COMM,KC_DOT,KC_SLSH ,KC_RCTL, \
  //|-------+-------+-------+-------+-------+-------+------| |-------+-------+-------+-------+-------+-------+------|
                   KC_LGUI,LT(_RAISE,KC_TAB),SFT_T(KC_BSPC)  ,LT(_LOWER,KC_ENT),KC_SPC,KC_RGUI \
                                  //`----------------------' `-----------------------'
  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------.                ,----------------------------------------------.
     KC_GRV ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5                    ,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_DEL,   \
  //|-------+-------+-------+-------+-------+-------|                |-------+-------+-------+-------+-------+------|
     _______,KC_SCLN,KC_LPRN,KC_RPRN,KC_QUOT,KC_GRV                  ,KC_LEFT,KC_DOWN,KC_UP  ,KC_RIGHT,KC_ESC,_______, \
  //|-------+-------+-------+-------+-------+-------|                |-------+-------+-------+-------+-------+------|
     _______,_______,KC_LBRC,KC_RBRC,_______,_______                 ,KC_EQL ,_______,_______,_______,KC_BSLS,_______, \
  //|-------+-------+-------+-------+-------+-------+------| |-------+-------+-------+-------+-------+-------+------|
                                 _______,MO(_ADJUST),_______  ,_______,_______,_______ \
                                  //`----------------------' `-----------------------'
  ),
  
  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------.                ,----------------------------------------------.
     _______,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5                   ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_INS , \
  //|-------+-------+-------+-------+-------+-------|                |-------+-------+-------+-------+-------+------|
     _______,KC_F11 ,KC_F12 ,KC_F13 ,KC_F14 ,KC_F15                  ,KC_HOME,KC_PGDN,KC_PGUP,KC_END ,_______,_______, \
  //|-------+-------+-------+-------+-------+-------|                |-------+-------+-------+-------+-------+------|
     _______,_______,_______,_______,_______,_______                 ,_______,_______,_______,_______,_______,_______, \
  //|-------+-------+-------+-------+-------+-------+------| |-------+-------+-------+-------+-------+-------+------|
                                     _______,_______,_______ ,MO(_ADJUST),_______,_______ \
                                  //`----------------------' `-----------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------.                ,----------------------------------------------.
     RESET  ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                 KC_MUTE,KC_VOLU,KC_MPLY,XXXXXXX,XXXXXXX,XXXXXXX, \
  //|-------+-------+-------+-------+-------+-------|                |-------+-------+-------+-------+-------+------|
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,HARMONY,XXXXXXX,        REPORT_PARAM,DEC_PARAM,INC_PARAM,XXXXXXX,XXXXXXX,XXXXXXX, \
  //|-------+-------+-------+-------+-------+-------|                |-------+-------+-------+-------+-------+------|
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_CAPS,KC_NLCK,                 XXXXXXX,XXXXXXX,XXXXXXX,EISU   ,ROMAJI ,XXXXXXX, \
  //|-------+-------+-------+-------+-------+-------+------| |-------+-------+-------+-------+-------+-------+------|
                                  _______,MO(_ADJUST),_______,MO(_ADJUST),_______,_______ \
                                  //`----------------------' `-----------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
    
    //
    // Always init to default keyboard layout
    //
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    //eeconfig_read_keymap()
    persistent_default_layer_set(0);
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    static const char* strROMAJI = "ROMAJI mode";
    if( _romaji_mode ) {
        matrix_write_ln(matrix,strROMAJI);
    }
    else {
        matrix_write(matrix, read_logo());
    }
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

#define CHANGE_LAYOUT(X)    \
    case X:\
      if (record->event.pressed) {\
        persistent_default_layer_set(1UL<<_##X);\
      }\
      return false;\
      break;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
    // set_timelog();
  }

  if( ! process_romaji(keycode,record) )
    return false;

  switch (keycode) {
    CHANGE_LAYOUT(HARMONY)

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
      break;
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
      break;


  }
  return true;
}

#endif
