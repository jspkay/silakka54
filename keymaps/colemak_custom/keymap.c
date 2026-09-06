// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_italian.h"

// clang-format off

enum {
    BASE,
    QWERTY,

    FIRST,
    SECOND,

    EXTRA,
    MORE,

    SETTINGS,

    F_STUFF,
    MOVING_AROUND,
    ADDITIONAL_SYMBOLS,
    SYMBOLS,
    NUMBERS,

    EMPTY
};

enum {
    TD_LSHT_CAPS,
    TD_RSHT_CAPS,
    TD_CTRL_REP
};

enum custom_keycodes {
    LOCK_COMBO = SAFE_RANGE,
};


static uint8_t active_layer;
layer_state_t layer_state_set_user(layer_state_t state) {
    active_layer = get_highest_layer(state);
    return state;
}

static bool gui_is_held = false;
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
#ifdef SWAY
    static uint8_t registered_key = KC_NO;
#endif

    // stuff that is ok with other layers
    switch(keycode){
        case KC_LGUI: // Types ../ to go up a directory on the shell.
            gui_is_held = record->event.pressed;
            if(gui_is_held){
                register_code(KC_LGUI);
            }else{
                unregister_code(KC_LGUI);
            }
            break;
        case LOCK_COMBO:
            if(record->event.pressed){
                register_code(KC_LALT);
                register_code(KC_SPC);
            }else{
                unregister_code(KC_LALT);
                unregister_code(KC_SPC);
            }
            return false;
    }

#ifdef SWAY
    // to avoid interference with other layers we do this
    if(active_layer > BASE) return true;

    // TODO: This function is called only when a new key is pressed
    // and the switch applies only to that key. It would be amazing
    // if there was a way to check whether the key SPACE is being
    // pressed, rather than checking only the event of pressing it.
    // So, check if there is a function which has a key as an input
    // and outputs true or false depending on the key being held
    // in that moment :)
    switch (keycode) {

        case KC_J:
            if(record->event.pressed){
                registered_key = (gui_is_held) ? KC_1 : KC_J;
                register_code(registered_key);
            }else{
                unregister_code(registered_key);
            }
            return false;
        case KC_L:
            if(record->event.pressed){
                registered_key = (gui_is_held) ? KC_2 : KC_L;
                register_code(registered_key);
            }else{
                unregister_code(registered_key);
            }
            return false;
        case KC_U:
            if(record->event.pressed){
                registered_key = (gui_is_held) ? KC_3 : KC_U;
                register_code(registered_key);
            }else{
                unregister_code(registered_key);
            }
            return false;
        case KC_Y:
            if(record->event.pressed){
                registered_key = (gui_is_held) ? KC_4 : KC_Y;
                register_code(registered_key);
            }else{
                unregister_code(registered_key);
            }
            return false;
        case KC_MINS:
            if(record->event.pressed){
                registered_key = (gui_is_held) ? KC_5 : KC_MINS;
                register_code(registered_key);
            }else{
                unregister_code(registered_key);
            }
            return false;
    }
#endif

    return true;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LSHT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_RSHT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
    [TD_CTRL_REP] = ACTION_TAP_DANCE_DOUBLE(QK_REP, KC_LCTL)
};

#define ___ _______


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        KC_GRV,           KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    IT_PLUS,
        OS_LALT,          KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                               KC_J,    KC_L,    KC_U,    KC_Y, KC_BSPC,    OS_RALT,
        OS_LGUI,  LSFT_T(KC_A),    KC_R,    KC_S,    KC_T,    KC_D,                               KC_H,    KC_N,    KC_E,    KC_I,RSFT_T(KC_O),OS_RGUI,
        OS_LCTL,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_K,    KC_M,    KC_COMM, KC_DOT,KC_SLSH,   OS_RCTL,
                        KC_TAB,   MO(FIRST), LT(MORE, KC_SPC),                   LT(SECOND, KC_ENT),  MO(EXTRA), MT(MOD_RALT, KC_ESC)
    ),
    [QWERTY] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                              _______, _______, _______, _______, _______, _______,
        _______,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, _______,
        _______,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                 KC_H,    KC_J,    KC_K,    KC_L, KC_MINS, _______,
        _______,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                 KC_N,    KC_M,    _______, _______, _______, _______,
                                            _______, _______, _______,            _______, _______, _______
    ),


    [SECOND] = LAYOUT(
        XXX,  XXX, XXX, XXX, XXX, XXX,                                XXX,     XXX,     XXX,     XXX,  XXX, XXX,
        ___,  XXX, XXX, XXX, XXX, XXX,                                XXX,     XXX,     XXX,     XXX,  XXX, ___,
        ___,  XXX, XXX, XXX, XXX, XXX,                            KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_O, ___,
        ___,  XXX, XXX, XXX, XXX, XXX,                            KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  XXX, ___,
                                            XXX, XXX, XXX,            XXX,     XXX, XXX
    ),


    [FIRST] = LAYOUT(
        XXX,  XXX, XXX, XXX, XXX, XXX,                    XXX,      XXX,          XXX, XXX, XXX, XXX,
        ___,  XXX, XXX, XXX, XXX, KC_GRAVE,          KC_MINUS, KC_EQUAL,          XXX, XXX, XXX, ___,
        ___,  XXX, XXX, XXX, XXX, KC_DEL,             KC_LBRC,  KC_RBRC,      KC_SLSH, XXX, XXX, ___,
        ___,  XXX, XXX, XXX, XXX, KC_NUBS,       KC_SEMICOLON, KC_QUOTE, KC_BACKSLASH, XXX, XXX, ___,
                             XXX, XXX, XXX,           XXX, XXX, XXX
    ),
    [MORE] = LAYOUT(
        XXX,  XXX, XXX, XXX, XXX, XXX,                           XXX, XXX, XXX, XXX, XXX, XXX,
        ___,  XXX, KC_MUTE, KC_VOLD, KC_VOLU, XXX,          KC_MINUS, XXX, XXX, XXX, XXX, XXX,
        ___,  XXX, KC_MPRV, KC_MPLY, KC_MNXT, XXX,           KC_LBRC, XXX, XXX, XXX, XXX, XXX,
        ___,  XXX, XXX, XXX, XXX, KC_NUBS,                       XXX, XXX, XXX, XXX, XXX, KC_CAPS,
                                            XXX, XXX, XXX,           XXX, XXX, XXX
    ),


    // This layer contains mostly function keys: the traditional, the media keys ant alt
    [F_STUFF] = LAYOUT(
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  TG(QWERTY),
        _______,  KC_PSCR, KC_MUTE, KC_VOLD, KC_VOLU, _______,                            KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_F11,  _______,
        _______,  _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_LBRC, KC_RBRC,
        _______,  _______, _______, _______, _______, _______,                            KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, _______, TG(NUMBERS),
                                            _______, _______, _______,                   XXXXXXX, KC_DEL,  KC_RALT
    ),
    // This layer contains stuff to move around and accents
    [MOVING_AROUND] = LAYOUT(
        _______,  _______, _______, _______, _______, _______,                            _______, _______, IT_UGRV, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______,                            KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______, _______,
        _______,  IT_AGRV, _______, _______, _______, _______,                            KC_H,       KC_J,    KC_K,    KC_L, _______, _______,
        _______,  _______, _______, _______, _______, _______,                            _______, IT_EGRV, IT_EACU, IT_IGRV, IT_OGRV, _______,
                                            _______, _______, /*TG(QWERTY)*/ ,           _______, _______, _______
    ),
    // This layer contains additoinal symbols mostly related to programming
    [ADDITIONAL_SYMBOLS] = LAYOUT(
        _______,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, KC_SLEP ,
        KC_KB_POWER,  _______, S(IT_PLUS) /*star*/,          IT_LCBR, IT_RCBR, _______,                            _______, XXXXXXX, XXXXXXX, _______, LOCK_COMBO, _______,
        _______,  IT_CIRC /*hat*/, ALGR(IT_IGRV) /*tilde*/,    IT_LBRC, IT_RBRC, IT_HASH,                            _______, _______, _______, _______, _______, _______,
            _______,  _______, ALGR(IT_QUOT) /*backtick*/,  IT_LABK, S(IT_LABK), IT_AT,                            _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),
    [SYMBOLS] = LAYOUT(
        _______,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______,  _______, S(IT_PLUS) /*star*/,          IT_LCBR, IT_RCBR, _______,                            _______, XXXXXXX, XXXXXXX, KC_ALGR, _______, _______,
        _______,  IT_CIRC /*hat*/, ALGR(IT_IGRV) /*tilde*/,    IT_LBRC, IT_RBRC, IT_HASH,                            _______, _______, _______, _______, _______, _______,
            _______,  _______, ALGR(IT_QUOT) /*backtick*/,  IT_LABK, S(IT_LABK), IT_AT,                            _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),
    [NUMBERS] = LAYOUT(
        _______,  _______, KC_7, KC_8, KC_9, _______,                            _______, KC_7, KC_8, KC_9, _______, _______,
        _______,  _______, KC_4, KC_5, KC_6, _______,                            _______, KC_4, KC_5, KC_6, _______, _______,
        _______,  _______, KC_1, KC_2, KC_3, _______,                            _______, KC_1, KC_2, KC_3, _______, _______,
        _______,  _______, _______, _______, KC_0, _______,                            _______, KC_0, _______, _______, _______, TG(NUMBERS),
                                            _______, KC_ENT, KC_0,        KC_0, KC_ENT, _______
    ),
    // This layer is empty on purpose to have a template for new layers
    [EMPTY] = LAYOUT(
        _______,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    )
};

