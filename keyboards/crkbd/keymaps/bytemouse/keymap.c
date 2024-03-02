#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include <stdio.h>

enum corne_layers {
  _QWERTY,
  _KOY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum plaid_keycodes {
  KOY = QK_USER,
  QWERTY,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define ONEHALF ALGR(DE_4)
#define ONETHIR ALGR(DE_5)
#define ONEQUAR ALGR(DE_6)
#define RAISEBSPC LT(_RAISE, KC_BSPC) // Raise+Backspace 
#define LOWERTAB LT(_LOWER, KC_TAB)  // Lower+Tab
#define ALTTPES LALT_T(KC_ESC)
#define ALTTPEN LT(_ADJUST, KC_ENT)
#define N_PASTE LCTL(KC_V) // CTRL+V
#define N_COPY LCTL(KC_C) // CTRL+C
#define N_CUT LCTL(KC_X) // CTRL+X
#define N_UNDO LCTL(DE_Z) // CTRL+Z
#define N_REDO LCTL(DE_Y) // CTRL+Y

// Home row mods GASC
#define HMOD_GUI LGUI_T(DE_H)
#define HMOD_ALT LALT_T(DE_A)
#define HMOD_SHIFT LSFT_T(DE_E)
#define HMOD_CTRL LCTL_T(DE_I)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    //#                         ╭───────╮                                                                        ╭───────╮                          
    //#                 ╭───────╯   E   ╰───────╮                                                        ╭───────╯   I   ╰───────╮                  
    //#                 │   W   │       │   R   ╭───────╮                                        ╭───────╮   U   │       │   O   │                  
    //# ╭───────╮───────╯       ╰───────╯       │   T   │                                        │   Y   │       ╰───────╯       ╰───────╭───────╮  
    //# │  ⭾   │   Q   ╰───────╯   D   ╰───────╯       │                                        │       ╰───────╯   K   ╰───────╯   P   │   ⌫   │  
    //# │       │       │   S   │       │   F   ╰───────╯                                        ╰───────╯   J   │       │   L   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   G   │                                        │   H   │       ╰───────╯       ╰───────╰───────╯  
    //# │  ⌘   │   A   ╰───────╯   C   ╰───────╯       │                                        │       ╰───────╯  ╰───────╯   ;   │   '   │  
    //# │       │       │   X   │       │   V   ╰───────╯                                        ╰───────╯   M   │       │   .   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   B   │                                        │   N   │       ╰───────╯       ╰───────╰───────╯  
    //# │   ⇧   │   Z   ╰───────╯       ╰───────╯       │                                        │       ╰───────╯       ╰───────╯   /   │   ⇧   │  
    //# │       │       │              ╭───────╮╰───────╯                                        ╰───────╯╭───────╮              │       │       │  
    //# ╰───────╯───────╯              │  Ctrl ╰───────╮                                          ╭───────╯   ⎇⎋  │              ╰───────╰───────╯  
    //#                                │       │   ⇩⭾  ╰───────╮                          ╭───────╯   ⇧⌫  │       │                                 
    //#                                ╰───────╯       │   ⎇⏎  |                          |   ␣   │       ╰───────╯                                 
    //#                                        ╰───────╯       |                          │       ╰───────╯                                         
    //#                                                ╰───────╯                          ╰───────╯                                                 
    //#                                                                                                                                             
  [_QWERTY] = LAYOUT_split_3x6_3(
KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                                                                   KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,    
KC_LGUI,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                                                                   KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,    
KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,                                                                   KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,    
                                                KC_LCTL,    LOWERTAB,   ALTTPEN,                                        KC_SPC,     RAISEBSPC,  ALTTPES                                                     
  ),

    //#                         ╭───────╮                                                                        ╭───────╮                          
    //#                 ╭───────╯   O   ╰───────╮                                                        ╭───────╯   C   ╰───────╮                  
    //#                 │   .   │       │   ,   ╭───────╮                                        ╭───────╮   G   │       │   L   │                  
    //# ╭───────╮───────╯       ╰───────╯       │   Y   │                                        │   V   │       ╰───────╯       ╰───────╭───────╮  
    //# │   Z   │   K   ╰───────╯   ⇧E   ╰───────╯       │                                        │       ╰───────╯   R   ╰───────╯   ß   │   ⌫   │  
    //# │       │       │   ⎇A   │       │   ^I   ╰───────╯                                        ╰───────╯   T   │       │   N   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   U   │                                        │   D   │       ╰───────╯       ╰───────╰───────╯  
    //# │  ⌘   │   ⌘H   ╰───────╯   Ä   ╰───────╯       │                                        │       ╰───────╯   W   ╰───────╯   S   │   F   │  
    //# │       │       │   Q   │       │   Ü   ╰───────╯                                        ╰───────╯   P   │       │   M   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   Ö   │                                        │   B   │       ╰───────╯       ╰───────╰───────╯  
    //# │   ⇧   │   X   ╰───────╯       ╰───────╯       │                                        │       ╰───────╯       ╰───────╯   J   │   ⇧   │  
    //# │       │       │              ╭───────╮╰───────╯                                        ╰───────╯╭───────╮              │       │       │  
    //# ╰───────╯───────╯              │  Ctrl ╰───────╮                                          ╭───────╯   ⎇⎋  │              ╰───────╰───────╯  
    //#                                │       │   ⇩⭾  ╰───────╮                          ╭───────╯   ⇧⌫  │       │                                 
    //#                                ╰───────╯       │   ⎇⏎  |                          |   ␣   │       ╰───────╯                                 
    //#                                        ╰───────╯       |                          │       ╰───────╯                                         
    //#                                                ╰───────╯                          ╰───────╯                                                 
    //#                                                                                                                                             
  [_KOY] = LAYOUT_split_3x6_3(
DE_Z,       DE_K,       DE_DOT,     DE_O,       DE_COMM,    DE_Y,                                                                   DE_V,       DE_G,       DE_C,       DE_L,       DE_SS,      KC_BSPC,    
KC_LGUI,    HMOD_GUI,   HMOD_ALT,   HMOD_SHIFT, HMOD_CTRL,  DE_U,                                                                   DE_D,       DE_T,       DE_R,       DE_N,       DE_S,       DE_F,       
KC_LSFT,    DE_X,       DE_Q,       DE_ADIA,    DE_UDIA,    DE_ODIA,                                                                DE_B,       DE_P,       DE_W,       DE_M,       DE_J,       KC_RSFT,    
                                                KC_LCTL,    LOWERTAB,   ALTTPEN,                                        KC_SPC,     RAISEBSPC,  ALTTPES                                                     
  ),

    //#                         ╭───────╮                                                                        ╭───────╮                          
    //#                 ╭───────╯   3   ╰───────╮                                                        ╭───────╯   8   ╰───────╮                  
    //#                 │   2   │       │   4   ╭───────╮                                        ╭───────╮   7   │       │   9   │                  
    //# ╭───────╮───────╯       ╰───────╯       │   5   │                                        │   6   │       ╰───────╯       ╰───────╭───────╮  
    //# │       │   1   ╰───────╯  ⇤   ╰───────╯       │                                        │       ╰───────╯  ▽   ╰───────╯   0   │   ⌦   │  
    //# │       │       │   ⏯️   │       │  ⇥   ╰───────╯                                        ╰───────╯  ◁   │       │  △   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │  ↶   │                                        │   Z   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │  🕪   ╰───────╯   ⏭️   ╰───────╯       │                                        │       ╰───────╯   ½   ╰───────╯  ▷   │  ⎋   │  
    //# │       │       │   ⏮️   │       │   ⎘C  ╰───────╯                                        ╰───────╯   ⎙   │       │   ⅓   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   ⎘   │                                        │   ²   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │  🕩   ╰───────╯       ╰───────╯       │                                        │       ╰───────╯       ╰───────╯   ¼   │       │  
    //# │       │       │              ╭───────╮╰───────╯                                        ╰───────╯╭───────╮              │       │       │  
    //# ╰───────╯───────╯              │       ╰───────╮                                          ╭───────╯       │              ╰───────╰───────╯  
    //#                                │       │       ╰───────╮                          ╭───────╯   ⚙   │       │                                 
    //#                                ╰───────╯       │       |                          |   ⌦   │       ╰───────╯                                 
    //#                                        ╰───────╯       |                          │       ╰───────╯                                         
    //#                                                ╰───────╯                          ╰───────╯                                                 
    //#                                                                                                                                             
  [_LOWER] = LAYOUT_split_3x6_3(
_______,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                                                                   KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_DEL,     
_______,    KC_VOLU,    KC_MPLY,    KC_HOME,    KC_END,     N_UNDO,                                                                 DE_Z,       KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   KC_ESC,     
_______,    KC_VOLD,    KC_MPRV,    KC_MNXT,    N_COPY,     N_PASTE,                                                                DE_SUP2,    KC_PSCR,    ONEHALF,    ONETHIR,    ONEQUAR,    _______,    
                                                _______,    _______,    _______,                                        KC_DEL,     ADJUST,     _______                                                     
  ),

    //#                         ╭───────╮                                                                        ╭───────╮                          
    //#                 ╭───────╯   [   ╰───────╮                                                        ╭───────╯   >   ╰───────╮                  
    //#                 │   _   │       │   ]   ╭───────╮                                        ╭───────╮   <   │       │   =   │                  
    //# ╭───────╮───────╯       ╰───────╯       │   ^   │                                        │   !   │       ╰───────╯       ╰───────╭───────╮  
    //# │       │   €   ╰───────╯   {   ╰───────╯       │                                        │       ╰───────╯   )   ╰───────╯   &   │       │  
    //# │       │       │   /   │       │   }   ╰───────╯                                        ╰───────╯   (   │       │   -   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   *   │                                        │   ?   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   \   ╰───────╯   |   ╰───────╯       │                                        │       ╰───────╯   "   ╰───────╯   :   │   @   │  
    //# │       │       │   $   │       │   ~   ╰───────╯                                        ╰───────╯   %   │       │   '   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   ´   │                                        │   +   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   #   ╰───────╯       ╰───────╯       │                                        │       ╰───────╯       ╰───────╯   ;   │       │  
    //# │       │       │              ╭───────╮╰───────╯                                        ╰───────╯╭───────╮              │       │       │  
    //# ╰───────╯───────╯              │       ╰───────╮                                          ╭───────╯       │              ╰───────╰───────╯  
    //#                                │       │   ⚙   ╰───────╮                          ╭───────╯       │       │                                 
    //#                                ╰───────╯       │       |                          |       │       ╰───────╯                                 
    //#                                        ╰───────╯       |                          │       ╰───────╯                                         
    //#                                                ╰───────╯                          ╰───────╯                                                 
    //#                                                                                                                                             
  [_RAISE] = LAYOUT_split_3x6_3(
_______,    DE_EURO,    DE_UNDS,    DE_LBRC,    DE_RBRC,    DE_CIRC,                                                                DE_EXLM,    DE_LABK,    DE_RABK,    DE_EQL,     DE_AMPR,    _______,    
_______,    DE_BSLS,    DE_SLSH,    DE_LCBR,    DE_RCBR,    DE_ASTR,                                                                DE_QUES,    DE_LPRN,    DE_RPRN,    DE_MINS,    DE_COLN,    DE_AT,      
_______,    DE_HASH,    DE_DLR,     DE_PIPE,    DE_TILD,    DE_ACUT,                                                                DE_PLUS,    DE_PERC,    DE_DQUO,    DE_QUOT,    DE_SCLN,    _______,    
                                                _______,    ADJUST,     _______,                                        _______,    _______,    _______                                                     
  ),

    //#                         ╭───────╮                                                                        ╭───────╮                          
    //#                 ╭───────╯   F3  ╰───────╮                                                        ╭───────╯   F2  ╰───────╮                  
    //#                 │   F2  │       │   F4  ╭───────╮                                        ╭───────╮   F1  │       │   F3  │                  
    //# ╭───────╮───────╯       ╰───────╯       │   F5  │                                        │   F6  │       ╰───────╯       ╰───────╭───────╮  
    //# │   F12  │   F1  ╰───────╯   ⇧   ╰───────╯       │                                        │       ╰───────╯   F6  ╰───────╯   F4  │   F11  │  
    //# │       │       │  ⎇   │       │  Ctrl ╰───────╯                                        ╰───────╯   F5  │       │   F7  │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │        │                                        │        │       ╰───────╯       ╰───────╰───────╯  
    //# │       │  ⌘   ╰───────╯        ╰───────╯       │                                        │       ╰───────╯   F10  ╰───────╯   F8  │        │  
    //# │       │       │        │       │   KOY ╰───────╯                                        ╰───────╯   F9  │       │   F11  │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │ QWERTY │                                        │        │       ╰───────╯       ╰───────╰───────╯  
    //# │       │        ╰───────╯       ╰───────╯       │                                        │       ╰───────╯       ╰───────╯   F12  │       │  
    //# │       │       │              ╭───────╮╰───────╯                                        ╰───────╯╭───────╮              │       │       │  
    //# ╰───────╯───────╯              │       ╰───────╮                                          ╭───────╯       │              ╰───────╰───────╯  
    //#                                │       │       ╰───────╮                          ╭───────╯       │       │                                 
    //#                                ╰───────╯       │       |                          |       │       ╰───────╯                                 
    //#                                        ╰───────╯       |                          │       ╰───────╯                                         
    //#                                                ╰───────╯                          ╰───────╯                                                 
    //#                                                                                                                                             
  [_ADJUST] = LAYOUT_split_3x6_3(
KC_F12,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,                                                                  KC_F6,      KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F11,     
_______,    KC_LGUI,    KC_LALT,    KC_LSFT,    KC_LCTL,    XXXXXXX,                                                                XXXXXXX,    KC_F5,      KC_F6,      KC_F7,      KC_F8,      XXXXXXX,    
_______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KOY,        QWERTY,                                                                 XXXXXXX,    KC_F9,      KC_F10,     KC_F11,     KC_F12,     _______,    
                                                _______,    _______,    _______,                                        _______,    _______,    _______                                                     
  )

};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            if (biton32(default_layer_state) == _QWERTY) {
                oled_write_ln_P(PSTR("QWERTY"), false);
            } else if (biton32(default_layer_state) == _KOY) {
                oled_write_ln_P(PSTR("KOY"), false);
            }
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KOY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_KOY);
        return false;
      }
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
        return false;
      }
    }
  return true;
}

/*
qmk-keyboard-format:json:begin
{
    "name": "CRKBD",
    "numkeys": 42,
    "svg": "CRKBD.svg",
    "rows": [
        [  0,  1,  2,  3,  4,  5, -1, -1, -2, -1, -1,  6,  7,  8,  9, 10, 11 ],
        [ 12, 13, 14, 15, 16, 17, -1, -1, -2, -1, -1, 18, 19, 20, 21, 22, 23 ],
        [ 24, 25, 26, 27, 28, 29, -1, -1, -2, -1, -1, 30, 31, 32, 33, 34, 35 ],
        [ -1, -1, -1, -1, 36, 37, 38, -1, -2, -1, 39, 40, 41, -1, -1, -1, -1 ]
    ],
    "spacing": [
        10,
        10,
        8
    ],
    "vizemits": [
        {"line": "[_QWERTY] = LAYOUT_split_3x6_3(", "layer": "_QWERTY"},
        {"line": "[_KOY] = LAYOUT_split_3x6_3(", "layer": "_KOY"},
        {"line": "[_LOWER] = LAYOUT_split_3x6_3(", "layer": "_LOWER"},
        {"line": "[_RAISE] = LAYOUT_split_3x6_3(", "layer": "_RAISE"},
        {"line": "[_ADJUST] = LAYOUT_split_3x6_3(", "layer": "_ADJUST"}
    ],
    "vizline": "//#",
    "vizboard": [
        "    //#                         ╭───────╮                                                                        ╭───────╮                          ",
        "    //#                 ╭───────╯ _003_ ╰───────╮                                                        ╭───────╯ _008_ ╰───────╮                  ",
        "    //#                 │ _002_ │       │ _004_ ╭───────╮                                        ╭───────╮ _007_ │       │ _009_ │                  ",
        "    //# ╭───────╮───────╯       ╰───────╯       │ _005_ │                                        │ _006_ │       ╰───────╯       ╰───────╭───────╮  ",
        "    //# │ _000_ │ _001_ ╰───────╯ _015_ ╰───────╯       │                                        │       ╰───────╯ _020_ ╰───────╯ _010_ │ _011_ │  ",
        "    //# │       │       │ _014_ │       │ _016_ ╰───────╯                                        ╰───────╯ _019_ │       │ _021_ │       │       │  ",
        "    //# ╰───────╯───────╯       ╰───────╯       │ _017_ │                                        │ _018_ │       ╰───────╯       ╰───────╰───────╯  ",
        "    //# │ _012_ │ _013_ ╰───────╯ _027_ ╰───────╯       │                                        │       ╰───────╯ _032_ ╰───────╯ _022_ │ _023_ │  ",
        "    //# │       │       │ _026_ │       │ _028_ ╰───────╯                                        ╰───────╯ _031_ │       │ _033_ │       │       │  ",
        "    //# ╰───────╯───────╯       ╰───────╯       │ _029_ │                                        │ _030_ │       ╰───────╯       ╰───────╰───────╯  ",
        "    //# │ _024_ │ _025_ ╰───────╯       ╰───────╯       │                                        │       ╰───────╯       ╰───────╯ _034_ │ _035_ │  ",
        "    //# │       │       │              ╭───────╮╰───────╯                                        ╰───────╯╭───────╮              │       │       │  ",
        "    //# ╰───────╯───────╯              │ _036_ ╰───────╮                                          ╭───────╯ _041_ │              ╰───────╰───────╯  ",
        "    //#                                │       │ _037_ ╰───────╮                          ╭───────╯ _040_ │       │                                 ",
        "    //#                                ╰───────╯       │ _038_ |                          | _039_ │       ╰───────╯                                 ",
        "    //#                                        ╰───────╯       |                          │       ╰───────╯                                         ",
        "    //#                                                ╰───────╯                          ╰───────╯                                                 ",
        "    //#                                                                                                                                             "
    ],
  "vizsymbols": {
    "KC_TRANS": "     ",
    "KC_A": "  A  ",
    "KC_B": "  B  ",
    "KC_C": "  C  ",
    "KC_D": "  D  ",
    "KC_E": "  E  ",
    "KC_F": "  F  ",
    "KC_G": "  G  ",
    "KC_H": "  H  ",
    "KC_I": "  I  ",
    "KC_J": "  J  ",
    "KC_K": "  K  ",
    "KC_L": "  L  ",
    "KC_M": "  M  ",
    "KC_N": "  N  ",
    "KC_O": "  O  ",
    "KC_P": "  P  ",
    "KC_Q": "  Q  ",
    "KC_R": "  R  ",
    "KC_S": "  S  ",
    "KC_T": "  T  ",
    "KC_U": "  U  ",
    "KC_V": "  V  ",
    "KC_W": "  W  ",
    "KC_X": "  X  ",
    "KC_Y": "  Y  ",
    "KC_Z": "  Z  ",
    "KC_COMMA": "  ,  ",
    "KC_DOT": "  .  ",
    "KC_SCOLON": "  ;  ",
    "KC_SCLN": "  :  ",
    "KC_SLASH": "  \/  ",
    "KC_ESC": " ⎋  ",
    "KC_CUT": " ✄  ",
    "KC_UNDO": " ↶  ",
    "KC_REDO": " ↷  ",
    "KC_VOLU": " 🕪  ",
    "KC_VOLD": " 🕩  ",
    "KC_MUTE": "  🕨",
    "KC_TAB": " ⭾  ",
    "KC_MENU": "  𝌆  ",
    "KC_CAPSLOCK": "  ⇪  ",
    "KC_NUMLK": "  ⇭  ",
    "KC_SCRLK": "  ⇳  ",
    "KC_PRSCR": "  ⎙  ",
    "KC_PAUSE": "  ⎉  ",
    "KC_BREAK": "  ⎊  ",
    "KC_ENTER": "  ⏎  ",
    "KC_BSPACE": " ⌫  ",
    "KC_DELETE": " ⌦ ",
    "KC_INSERT": " ⎀  ",
    "KC_LEFT": " ◁  ",
    "KC_RIGHT": " ▷  ",
    "KC_UP": " △  ",
    "KC_DOWN": " ▽  ",
    "KC_HOME": " ⇤  ",
    "KC_END": " ⇥  ",
    "KC_PGUP": " ⇞  ",
    "KC_PGDOWN": " ⇟  ",
    "KC_LSFT": "  ⇧  ",
    "KC_RSFT": "  ⇧  ",
    "KC_LCTL": "  ^  ",
    "KC_RCTL": "  ^  ",
    "KC_LALT": " ⎇  ",
    "KC_RALT": " ⎇  ",
    "KC_HYPER": "  ✧  ",
    "KC_LGUI": " ⌘  ",
    "KC_RGUI": " ⌘  ",
    "KC_CIRC": "  ^  ", 
    "KC_1": "  1  ",
    "KC_2": "  2  ",
    "KC_3": "  3  ",
    "KC_4": "  4  ",
    "KC_5": "  5  ",
    "KC_6": "  6  ",
    "KC_7": "  7  ",
    "KC_8": "  8  ",
    "KC_9": "  9  ",
    "KC_0": "  0  ",
    "KC_SS": "  ß  ",
    "KC_ACUT": "  ´  ", 
    "KC_UDIA": "  Ü  ",
    "KC_PLUS": "  +  ",
    "KC_ODIA": "  Ö  ",
    "KC_ADIA": "  Ä  ",
    "KC_HASH": "  #  ",
    "KC_LABK": "  <  ",
    "KC_MINS": "  -  ",
    "KC_DEG": "  °  ",
    "KC_EXLM": "  !  ",
    "KC_DQUO": "  \"  ",
    "KC_SECT": "  §  ",
    "KC_DLR": "  $  ",
    "KC_PERC": "  %  ",
    "KC_AMPR": "  &  ",
    "KC_SLSH": "  \/  ",
    "KC_LPRN": "  (  ",
    "KC_RPRN": "  )  ",
    "KC_EQL": "  =  ",
    "KC_QUES": "  ?  ",
    "KC_GRV": "  `  ",
    "KC_ASTR": "  *  ",
    "KC_QUOT": "  '  ",
    "KC_RABK": "  >  ",
    "KC_SCLN": "  ;  ",
    "KC_COLN": "  :  ",
    "KC_UNDS": "  _  ",
    "KC_SUP2": "  ²  ",
    "KC_SUP3": "  ³  ",
    "KC_LCBR": "  {  ",
    "KC_LBRC": "  [  ",
    "KC_RBRC": "  ]  ",
    "KC_RCBR": "  }  ",
    "KC_BSLS": "  \\  ",
    "KC_AT": "  @  ",
    "KC_EURO": "  €  ",
    "KC_TILD": "  ~  ",
    "KC_PIPE": "  |  ",
    "KC_MICR": "  µ  ",
    "RAISE": "  ⇧  ",
    "ADJUST": "  ⚙  ",
    "ONEHALF": "  ½  ",
    "ONETHIR": "  ⅓  ",
    "ONEQUAR": "  ¼  ",
    "RAISEBSPC": "  ⇧⌫ ",
    "LOWERTAB": "  ⇩⭾ ",
    "ALTTPES": "  ⎇⎋ ",
    "ALTTPEN": "  ⎇⏎ ",
    "N_PASTE": "  ⎘  ",
    "N_COPY": "  ⎘C ",
    "N_CUT": "  ✄  ",
    "N_UNDO": " ↶  ",
    "N_REDO": " ↷  ",
    "DE_Z": "  Z  ",
    "DE_Y": "  Y  ",
    "DE_X": "  X  ",
    "DE_W": "  W  ",
    "DE_V": "  V  ",
    "DE_U": "  U  ",
    "DE_T": "  T  ",
    "DE_S": "  S  ",
    "DE_R": "  R  ",
    "DE_Q": "  Q  ",
    "DE_P": "  P  ",
    "DE_O": "  O  ",
    "DE_N": "  N  ",
    "DE_M": "  M  ",
    "DE_L": "  L  ",
    "DE_K": "  K  ",
    "DE_J": "  J  ",
    "DE_I": "  I  ",
    "DE_H": "  H  ",
    "DE_G": "  G  ",
    "DE_F": "  F  ",
    "DE_E": "  E  ",
    "DE_D": "  D  ",
    "DE_C": "  C  ",
    "DE_B": "  B  ",
    "DE_A": "  A  ",
    "DE_COMM": "  ,  ",
    "DE_DOT": "  .  ",
    "DE_ADIA": "  Ä  ",
    "DE_ODIA": "  Ö  ",
    "DE_UDIA": "  Ü  ",
    "DE_SS": "  ß  ",
    "DE_EURO": "  €  ",
    "DE_UNDS": "  _  ",
    "DE_LBRC": "  [  ",
    "DE_RBRC": "  ]  ",
    "DE_CIRC": "  ^  ",
    "DE_EXLM": "  !  ",
    "DE_LABK": "  <  ",
    "DE_RABK": "  >  ",
    "DE_EQL": "  =  ",
    "DE_AMPR": "  &  ",
    "DE_BSLS": "  \\  ",
    "DE_SLSH": "  \/  ",
    "DE_LCBR": "  {  ",
    "DE_RCBR": "  }  ",
    "DE_ASTR": "  *  ",
    "DE_QUES": "  ?  ",
    "DE_LPRN": "  (  ",
    "DE_RPRN": "  )  ",
    "DE_MINS": "  -  ",
    "DE_COLN": "  :  ",
    "DE_AT": "  @  ",
    "DE_HASH": "  #  ",
    "DE_DLR": "  $  ",
    "DE_PIPE": "  |  ",
    "DE_TILD": "  ~  ",
    "DE_ACUT": "  ´  ",
    "DE_PLUS": "  +  ",
    "DE_PERC": "  %  ",
    "DE_DQUO": "  \"  ",
    "DE_QUOT": "  '  ",
    "DE_SCLN": "  ;  ",
    "DE_SUP2": "  ²  ",
    "KC_SPC": "  ␣  ",
    "KC_MPLY": "  ⏯️  ",
    "KC_MPRV": "  ⏮️  ",
    "KC_MNXT": "  ⏭️  ",
    "KC_LCTL": " Ctrl",
    "_______": "     ",
    "KC_PSCR": "  ⎙  ",
    "KC_DEL": "  ⌦  ",
    "KC_F1": "  F1 ",
    "KC_F2": "  F2 ",
    "KC_F3": "  F3 ",
    "KC_F4": "  F4 ",
    "KC_F5": "  F5 ",
    "KC_F6": "  F6 ",
    "KC_F7": "  F7 ",
    "KC_F8": "  F8 ",
    "KC_F9": "  F9 ",
    "KC_F10": "  F10 ",
    "KC_F11": "  F11 ",
    "KC_F12": "  F12 ",
    "KOY": "  KOY",
    "QWERTY": "QWERTY",
    "XXXXXXX": "      ",
    "LGUI_T(DE_H)": "  ⌘H ",
    "LALT_T(DE_A)": "  ⎇A ",
    "LSFT_T(DE_E)": "  ⇧E ",
    "LCTL_T(DE_I)": "  ^I ",
    "HMOD_GUI": "  ⌘H  ",
    "HMOD_ALT": "  ⎇A  ",
    "HMOD_SHIFT": "  ⇧E  ",
    "HMOD_CTRL": "  ^I  ",
    "KC_BSPC": "  ⌫  "
  }
}
qmk-keyboard-format:json:end
*/
