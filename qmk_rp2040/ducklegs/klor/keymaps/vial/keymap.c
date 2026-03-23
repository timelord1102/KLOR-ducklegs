/*

                                        █         █    █            ▄▄▄▀▀▀▀▀▀▄▄▄        █▀▀▀▀▀▀▀▀▀▀█
                                        █        █     █          ▄▀            ▀▄      █          █
                                        █       █      █        ▄▀                ▀▄    █          █
                                        █      █       █        █                  █    █          █
                                        █     █        █       █                    █   █          █
                                        █    █         █       █                    █   █▄▄▄▄▄▄▄▄▄▄█
                                        █   █ █        █       █                    █   █      █
                                        █  █   █       █        █                  █    █       █
                                        █ █     █      █        ▀▄                ▄▀    █        █
                                        ██       █     █          ▀▄            ▄▀      █         █
                                        █         █    █▄▄▄▄▄▄▄▄    ▀▀▀▄▄▄▄▄▄▀▀▀        █          █

                                        ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
                                        D E F A U L T

*/
#include <stdbool.h>
#include <sys/types.h>
#include "action_layer.h"
#include "color.h"
#include "encoder.h"
#include "keyboard.h"
#include "keycodes.h"
#include "oled_driver.h"
#include "progmem.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include "klor.h"
#include "icons.h"

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ D E F I N I T I O N S                                                                                                                      │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   l a y e r s                                 │
// └───────────────────────────────────────────────────────────┘

enum klor_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _LOWER,
    _RAISE,
    _GAME_SWITCH,
    _MARATHON,
    _ADJUST,
};

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   k e y c o d e s                             │
// └───────────────────────────────────────────────────────────┘

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    GAME_SWITCH,
    MARATHON,
    ADJUST,
    OS_SWAP,
    MAKE_H,
    LAYER_SELECT,
    GAME_LAYER_UP,
    GAME_LAYER_DOWN
};

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   m a c r o n a m e s                         │
// └───────────────────────────────────────────────────────────┘

// LEFT HAND HOME ROW MODS ├───────────────────────────────────┐

#define GUI_A MT(MOD_LGUI, KC_A)
#define ALT_R MT(MOD_LALT, KC_R)
#define CTL_S MT(MOD_LCTL, KC_S)
#define SHT_T MT(MOD_LSFT, KC_T)

// RIGHT HAND HOME ROW MODS ├───────────────────────────────────┐

#define SHT_N MT(MOD_RSFT, KC_N)
#define CTL_E MT(MOD_LCTL, KC_E)
#define ALT_I MT(MOD_LALT, KC_I)
#define GUI_O MT(MOD_LGUI, KC_O)


// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   s o u n d s                                 │
// └───────────────────────────────────────────────────────────┘

#ifdef AUDIO_ENABLE
  #define WINXP_SOUND W__NOTE(_DS6), Q__NOTE(_DS5), H__NOTE(_AS5), H__NOTE(_GS5), H__NOTE(_DS5), H__NOTE(_DS6), H__NOTE(_AS5)
  #define MAC_SOUND S__NOTE(_CS5), B__NOTE(_C5)

  float winxp_song[][2] = SONG(WINXP_SOUND);
  float mac_song[][2] = SONG(MAC_SOUND);
#endif // AUDIO_ENABLE

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ K E Y M A P S                                                                                                                              │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

#define MAX_GAME_LAYERS 2

const uint8_t game_layers[] = {
    _QWERTY,
    _MARATHON,
};

// Top of keymap.c
uint8_t current_game_layer = 0;

// The Master packs the single byte into the buffer
void transport_master_user_state(void *buffer) {
    uint8_t *val = (uint8_t *)buffer;
    *val = current_game_layer;
}

// The Slave grabs that single byte from the buffer
void transport_slave_user_state(void *buffer) {
    uint8_t *val = (uint8_t *)buffer;
    current_game_layer = *val;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
  ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

  ┌───────────────────────────────────────────────────────────┐
  │ q w e r t y                                               │
  └───────────────────────────────────────────────────────────┘
            ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
            │    B    │    L    │    D    │    C    │    V    │                    │    J    │    Y    │    O    │    U    │    ,    │
  ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
  │   TAB   │    N    │    R    │    T    │    S    │    G    │                    │    P    │    H    │    A    │    E    │    I    │    "    │
  ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
  │   CTRL  │    X    │    Q    │    M    │    W    │    Z    ││  MUTE  ││PLY/PSE ││    K    │    F    │    '    │    ;    │    .    │    /    │
  └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                │  LALT   │  LOWER  │  SPACE  │   ESC   ││  ENTER  │ BKSPCE  │  RAISE  │   OS    │
                                └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

  [_QWERTY] = LAYOUT_polydactyl(
//╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_B,    KC_L,    KC_D,     KC_C,      KC_V,                          KC_J,    KC_Y,      KC_O,     KC_U,    KC_COMM,
LSFT_T(KC_TAB),  KC_N,    KC_R,    KC_T,   LSFT_T(KC_S),KC_G,                          KC_P, RSFT_T(KC_H), KC_A,     KC_E,    KC_I,  KC_QUOT,
       KC_LCTL, KC_X,    KC_Q,    KC_M,     KC_W,      KC_Z,     KC_MUTE,   KC_MPLY,  KC_K,    KC_F,      KC_APP,  KC_SCLN,  KC_DOT,  KC_SLSH,
                                  KC_LALT,  LOWER,     KC_SPC,  KC_ESC,    KC_ENT,  KC_BSPC,  RAISE,     KC_RGUI
),

/*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌───────────────────────────────────────────────────────────┐
   │ l o w e r                                                 │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │   F1    │   F2    │   F3    │   F4    │   F5    │                    │   F6    │   F7    │   F8    │   F9    │   F10   │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │    -    │    !    │    @    │    #    │    $    │    %    │                    │    ^    │    &    │    `    │    ~    │    =    │    +    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │    _    │    1    │    2    │    3    │    4    │    5    ││  MUTE  ││PLY/PASE││    6    │    7    │    8    │    9    │    0    │    *    │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │         │         │         │  LSHIFT ││  RSHIFT │         │         │         │
                                 └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘

            ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
            │   F1    │   F2    │   F3    │   F4    │   F5    │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │   F6    │   F7    │   F8    │   F9    │   F10   │
  ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
  │    -    │    1    │    2    │    3    │    4    │    5    ├─╯                ╰─┤    6    │    7    │    8    │    9    │    0    │    +    │
  ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
  │    _    │    !    │    @    │    #    │    $    │    %    ││        ││        ││    ^    │    &    │    *    │    (    │    )    │    _    │
  └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                │         │         │         │         ││         │  DEL    │ ALT     │  CTRL   │
                                └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */


   [_LOWER] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_F1,   KC_F2,    KC_F3,    KC_F4,    KC_F5,                         KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,
      KC_MINS,  KC_1   , KC_2 ,    KC_3   ,  KC_4  ,   KC_5   ,                       KC_6   ,  KC_7   ,  KC_8   ,  KC_9   ,  KC_0   ,  KC_PLUS,
      KC_UNDS,  KC_EXLM, KC_AT,    KC_HASH,  KC_DLR,   KC_PERC, KC_MUTE,   KC_MPLY,   KC_CIRC,  KC_AMPR,  KC_GRV,   KC_TILD,  KC_EQL,   KC_ASTR,
                                   KC_TRNS,  KC_TRNS,  KC_TRNS, KC_LSFT,   KC_RSFT,   KC_DEL,  KC_RALT,  KC_RCTL
 ),
 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌───────────────────────────────────────────────────────────┐
   │ r a i s e                                                 │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │ RGB_SPI │ RGB_HUI │         │         │    {    │                    │    }    │   LEFT  │   UP    │  RIGHT  │   HOME  │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │ RGB_BRI │ RGB_EFF │         │         │         │    [    │                    │    ]    │         │  DOWN   │         │  PSCRN  │  P UP   │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │ RGB_BRD │ RGB_SPD │ RGB_HUD │         │         │    (    ││  MUTE  ││PLY/PASE││    )    │         │         │         │   END   │ P DOWN  │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │         │  ADJUST │         │  LSHIFT ││  RSHIFT │         │         │  ADJUST │
                                 └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

   [_RAISE] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
               RGB_SPI,  RGB_HUI,  HF_NEXT,  CK_UP,    KC_LCBR,                       KC_RCBR,  KC_LEFT,  KC_UP,    KC_RGHT,  KC_HOME,
     RGB_VAI,  RGB_MOD,  RGB_M_B,  HF_TOGG,  CK_TOGG,  KC_LBRC,                       KC_RBRC,  KC_TRNS,  KC_DOWN,  KC_TRNS,  KC_PSCR,  KC_PGUP,
     RGB_VAD,  RGB_SPD,  RGB_HUD,  HF_PREV,  CK_DOWN,  KC_LPRN,  KC_MUTE,   KC_MPLY,  KC_RPRN,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_END,   KC_PGDN,
                                   KC_TRNS,  KC_TRNS,  TO(_GAME_SWITCH),  KC_LSFT,   KC_RSFT,  KC_TRNS,  KC_TRNS,  ADJUST
 ),


 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌───────────────────────────────────────────────────────────┐
   │ a d j u s t                                               │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │ AUDIO   │ HAPTIC  │ RGB HUE │ RGB MOD │         │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │         │   F7    │   F8    │   F9    │   F14   │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │  RESET  │ DEBUG   │ QWERTY  │ RGB SAT │         │         ├─╯                ╰─┤         │   F4    │   F5    │   F6    │   F12   │   F13   │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │  MAKE   │ OS SWAP │         │ RGB VAL │         │         ││  MUTE  ││PLY/PSE ││         │   F1    │   F2    │   F3    │   F10   │   F11   │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │    ▼    │    ▼    │    ▼    │    ▼    ││    ▼    │    ▼    │    ▼    │    ▼    │
                                 └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

   [_ADJUST] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
              AU_TOGG,   HF_TOGG,  RGB_HUI,  RGB_MOD,  XXXXXXX,                       XXXXXXX,  KC_F7,    KC_F8,    KC_F9,    KC_F14,
    QK_BOOT,  DB_TOGG,   QWERTY,   RGB_SAI,  XXXXXXX,  XXXXXXX,                       XXXXXXX,  KC_F4,    KC_F5,    KC_F6,    KC_F12,   KC_F13,
    MAKE_H,   OS_SWAP,   KC_TRNS,  RGB_VAI,  XXXXXXX,  XXXXXXX,  KC_MUTE,   KC_MPLY,  XXXXXXX,  KC_F1,    KC_F2,    KC_F3,    KC_F10,   KC_F11,
                                  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______
 ),

 /*
               ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
               │         │         │         │         │         │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │  QWERTY │         │         │         │         │
     ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
     │         │         │         │         │         │         ├─╯                ╰─┤         │         │         │         │         │         │
     ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     │         │         │         │         │         │         ││        ││        ││ PRNTSCRN│         │         │         │         │         │
     └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                   │         │         │         │         ││         │         │         │         │
                                   └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘

  */

   [_GAME_SWITCH] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
               XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                    TO(_QWERTY),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   LAYER_SELECT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
       ),

 /*
               ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
               │   TAB   │   1     │   2     │   3     │   4     │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │  QWERTY │         │         │         │         │
     ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
     │    G    │  SHFT   │   A     │   W     │   D     │    V    ├─╯                ╰─┤         │         │         │         │         │         │
     ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     │    C    │  CTRL   │         │   S     │   F     │    G    ││        ││        ││ PRNTSCRN│         │         │         │         │         │
     └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                   │   M     │         │ SPACE   │         ││         │         │         │         │
                                   └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘

  */

   [_MARATHON] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
               KC_TAB ,  KC_1   ,  KC_2   ,  KC_3   ,  KC_4   ,                    TO(_QWERTY),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     KC_G   ,  KC_LEFT_SHIFT,  KC_A   ,  KC_W   ,  KC_D   ,  KC_V,                       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     KC_C   ,  KC_LEFT_CTRL,  XXXXXXX,  KC_S   ,  KC_F,  KC_G,  XXXXXXX,   XXXXXXX,  KC_PRINT_SCREEN,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                   KC_M,  XXXXXXX,  KC_SPACE,  XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
       ),

 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌───────────────────────────────────────────────────────────┐
   │ t e m p l a t e   p o l y d a c t y l                     │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │         │         │         │         │         │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │         │         │         │         │         │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │         │         │         │         │         │         ├─╯                ╰─┤         │         │         │         │         │         │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │         │         │         │         │         │         ││        ││        ││         │         │         │         │         │         │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │         │         │         │         ││         │         │         │         │
                                 └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘

   [_TEMPLATE] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
              _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______
 )

   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌───────────────────────────────────────────────────────────┐
   │ t e m p l a t e   k o n r a d                             │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │         │         │         │         │         │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │         │         │         │         │         │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │         │         │         │         │         │         ├─╯                ╰─┤         │         │         │         │         │         │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │         │         │         │         │         │         ││        ││        ││         │         │         │         │         │         │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤╰────────╯╰────────╯├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │         │         │         │                    │         │         │         │
                                 └─────────┴─────────┴─────────┘                    └─────────┴─────────┴─────────┘

   [_TEMPLATE] = LAYOUT_konrad(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
              _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                  _______,  _______,  _______,                       _______,  _______,  _______
 )

   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌─────────────────────────────────────────────────┐
   │ t e m p l a t e   y u b i t s u m e             │
   └─────────────────────────────────────────────────┘
   ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
   │         │         │         │         │         │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │         │         │         │         │         │
   ├─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┤
   │         │         │         │         │         ├─╯                ╰─┤         │         │         │         │         │
   ├─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┤
   │         │         │         │         │         ││        ││        ││         │         │         │         │         │
   └─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┘
                       │         │         │         │         ││         │         │         │         │
                       └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘

   [_TEMPLATE] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,
                        _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______
 )


   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌─────────────────────────────────────────────────┐
   │ t e m p l a t e   s a e g e w e r k             │
   └─────────────────────────────────────────────────┘
   ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
   │         │         │         │         │         │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │         │         │         │         │         │
   ├─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┤
   │         │         │         │         │         ├─╯                ╰─┤         │         │         │         │         │
   ├─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┤
   │         │         │         │         │         ││        ││        ││         │         │         │         │         │
   └─────────┴─────────┼─────────┼─────────┼─────────┤╰────────╯╰────────╯├─────────┼─────────┼─────────┼─────────┴─────────┘
                       │         │         │         │                    │         │         │         │
                       └─────────┴─────────┴─────────┘                    └─────────┴─────────┴─────────┘

   [_TEMPLATE] = LAYOUT_saegewerk(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,
                        _______,  _______,  _______,                       _______,  _______,  _______
 )

 */
};



// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ L A Y E R   I N D I C A T O R                                                                                                                                    │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 3:
                rgb_matrix_set_color(i, 80, 0, 0);
                break;
            case 2:
                rgb_matrix_set_color(i, 0, 80, 0);
                break;
            case 1:
                rgb_matrix_set_color(i, 0, 0, 80);
                break;
            default:
                break;
        }
    }
    return false;
}


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ O L E D                                                                                                                                    │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

#ifdef OLED_ENABLE

// ┌───────────────────────────────────────────────────────────┐
// │ d y n a m i c   m a c r o                                 │
// └───────────────────────────────────────────────────────────┘

char layer_state_str[24];
char o_text[24] = "";
int dmacro_num = 0;

#ifdef DYNAMIC_MACRO_ENABLE
    char dmacro_text[4][24] = { "", "RECORDING", "STOP RECORDING",  "PLAY RECORDING"};
    static uint16_t dmacro_timer;
    const char PROGMEM rec_ico[] = {0xD1, 0xE1, 0};
    const char PROGMEM stop_ico[] = {0xD3, 0xE1, 0};
    const char PROGMEM play_ico[] = {0xD2, 0xE1, 0};


    // DYNMACRO RECORD ├─────────────────────────────────────────────────────────────┐
    bool dynamic_macro_record_start_user(int8_t direction) {
          dmacro_num = 1;
        return false;
    }

    // DYNMACRO STOP RECORDING ├─────────────────────────────────────────────────────┐
    bool dynamic_macro_record_end_user(int8_t direction) {
          dmacro_num = 2;
          dmacro_timer = timer_read();
        return false;
    }

    // DYNMACRO PLAY RECORDING ├─────────────────────────────────────────────────────┐
    bool dynamic_macro_play_user(int8_t direction) {
          dmacro_num = 3;
          dmacro_timer = timer_read();
        return false;
    }
#endif //DYNAMIC_MACRO_ENABLE


void matrix_scan_user(void) {
  #ifdef DYNAMIC_MACRO_ENABLE
    // DynMacroTimer
    if(dmacro_num > 0){
        if (timer_elapsed(dmacro_timer) < 3000) {
            strcpy ( o_text, dmacro_text[dmacro_num] );
          }
        else {
            if (dmacro_num == 1) {
                strcpy ( o_text, dmacro_text[1] );
              }
            else {
                strcpy ( o_text, layer_state_str );
                dmacro_num = 0;
              }
          }
      }
   #endif //DYNAMIC_MACRO_ENABLE
}


// ┌───────────────────────────────────────────────────────────┐
// │ o l e d   g r a p h i c s                                 │
// └───────────────────────────────────────────────────────────┘

void render_os_lock_status(void) {
    static const char PROGMEM sep_v[] = {0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0};
    static const char PROGMEM sep_h1[] = {0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0};
    static const char PROGMEM sep_h2[] = {0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0};
    static const char PROGMEM face_1[] = {0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0xE1, 0};
    static const char PROGMEM face_2[] = {0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xE1, 0};
    static const char PROGMEM face_3[] = {0xE1, 0xE1, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xE1, 0};
    static const char PROGMEM os_m_1[] = {0x95, 0x96, 0};
    static const char PROGMEM os_m_2[] = {0xB5, 0xB6, 0};
    static const char PROGMEM os_w_1[] = {0x97, 0x98, 0};
    static const char PROGMEM os_w_2[] = {0xB7, 0xB8, 0};
    static const char PROGMEM s_lock[] = {0x8F, 0x90, 0};
    static const char PROGMEM n_lock[] = {0x91, 0x92, 0};
    static const char PROGMEM c_lock[] = {0x93, 0x94, 0};
    static const char PROGMEM b_lock[] = {0xE1, 0xE1, 0};
    #ifdef AUDIO_ENABLE
      static const char PROGMEM aud_en[] = {0xAF, 0xB0, 0};
      static const char PROGMEM aud_di[] = {0xCF, 0xD0, 0};
    #endif
    #ifdef HAPTIC_ENABLE
      static const char PROGMEM hap_en[] = {0xB1, 0xB2, 0};
      static const char PROGMEM hap_di[] = {0xCF, 0xD0, 0};
    #endif

// os mode status ────────────────────────────────────────┐

    oled_write_ln_P(sep_v, false);

    if (keymap_config.swap_lctl_lgui) {
        oled_write_P(os_m_1, false); // ──── MAC
    } else {
        oled_write_P(os_w_1, false); // ──── WIN
    }

    oled_write_P(sep_h1, false);
    oled_write_P(face_1, false);

    if (keymap_config.swap_lctl_lgui) {
        oled_write_P(os_m_2, false); // ──── MAC
    } else {
        oled_write_P(os_w_2, false); // ──── WIN
    }

    oled_write_P(sep_h1, false);
    oled_write_P(face_2, false);
    oled_write_P(sep_h1, false);
    oled_write_P(face_3, false);


// lock key layer status ─────────────────────────────────┐

    led_t led_usb_state = host_keyboard_led_state();

    if (led_usb_state.num_lock) {
        oled_write_P(n_lock, false); // ──── NUMLOCK
    } else {
        oled_write_P(b_lock, false);
    }
    if (led_usb_state.caps_lock) {
        oled_write_P(c_lock, false); // ─── CAPSLOCK
    } else {
        oled_write_P(b_lock, false);
    }
    if (led_usb_state.scroll_lock) { // ─ SCROLLLOCK
        oled_write_P(s_lock, false);
    } else {
        oled_write_P(b_lock, false);
    }

// hardware feature status ──────────────────────────────┐

    oled_write_P(sep_h2, false);

    #ifndef AUDIO_ENABLE
        oled_write_P(b_lock, false);
    #endif
    #ifndef HAPTIC_ENABLE
        oled_write_P(b_lock, false);
    #endif

    #ifdef AUDIO_ENABLE // ────────────────── AUDIO
        if (is_audio_on()) {
            oled_write_P(aud_en, false);
        } else {
            oled_write_P(aud_di, false);
        }
    #endif // AUDIO ENABLE

     #ifdef HAPTIC_ENABLE // ─────────────── HAPTIC
//        oled_write_P(hap_en, false);
        if (haptic_get_enable()) {
            oled_write_P(hap_en, false);
        } else {
            oled_write_P(hap_di, false);
        }

     #endif // HAPTIC ENABLE
}


// layer status ──────────────────────────────────────────┐

int layerstate = 0;

layer_state_t layer_state_set_kb(layer_state_t state) {
    // Use the 'state' passed in rather than the global 'layer_state'
    // to get the most immediate update.
    uint8_t highest_layer = get_highest_layer(state | default_layer_state);

    switch (highest_layer) {
        case _QWERTY:      strcpy(layer_state_str, "BASE QWERTY"); break;
        case _LOWER:       strcpy(layer_state_str, "LOWER");       break;
        case _RAISE:       strcpy(layer_state_str, "RAISE");       break;
        case _GAME_SWITCH: strcpy(layer_state_str, "GAME SELECT"); break;
        case _MARATHON:    strcpy(layer_state_str, "MARATHON");    break;
        case _ADJUST:      strcpy(layer_state_str, "ADJUST");      break;
        default:           strcpy(layer_state_str, "UNKNOWN");     break;
    }

    // Immediately update o_text if not recording a macro
    if (dmacro_num < 1) {
        strcpy(o_text, layer_state_str);
    }

    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


// ┌───────────────────────────────────────────────────────────┐
// │ w r i t e   t o   o l e d                                 │
// └───────────────────────────────────────────────────────────┘
const static char* game_icons [] = {keyboard_icon, marathon_icon};

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {  // ────────────────────────── PRIMARY SIDE
        // layer status ──────────────────────────────────────────────────┐
        oled_clear();

        if (IS_LAYER_ON(_GAME_SWITCH)) {
            oled_write_raw_P(game_icons[current_game_layer], sizeof(marathon_icon));
            return false;
        }

        if (IS_LAYER_ON(_MARATHON)) {
            oled_write_raw_P(marathon_icon, sizeof(marathon_icon));
            return false;
        }

        #ifdef DYNAMIC_MACRO_ENABLE
            if(dmacro_num == 1){ oled_write_P(rec_ico, false); }
            if(dmacro_num == 2){ oled_write_P(stop_ico, false); }
            if(dmacro_num == 3){ oled_write_P(play_ico, false); }
        #endif //DYNAMIC_MACRO_ENABLE

        oled_write_ln(o_text, false);
        render_os_lock_status();

    } else {  // ─────────────────────────────────────────── SECONDARY SIDE
        oled_write_raw_P(ducklegs, sizeof(ducklegs));
    }
    return false;
}
#endif // OLED_ENABLE

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ M A C R O S                                                                                                                                │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case OS_SWAP:
            if (record->event.pressed) {
                if (!keymap_config.swap_lctl_lgui) {
                  keymap_config.swap_lctl_lgui = true;  // ─── MAC
                  #ifdef AUDIO_ENABLE
                    PLAY_SONG(mac_song);
                  #endif // AUDIO_ENABLE
                }
                else {
                  keymap_config.swap_lctl_lgui = false; // ─── WIN
                  #ifdef AUDIO_ENABLE
                    PLAY_SONG(winxp_song);
                  #endif // AUDIO_ENABLE
                }
//              #ifdef HAPTIC_ENABLE
//                drv2605l_pulse(52);
//              #endif // HAPTIC_ENABLE
            eeconfig_update_keymap(&keymap_config);
            clear_keyboard();  // ──── clear to prevent stuck keys
            return false;
          }
        case LAYER_SELECT:
            if (record->event.pressed) {
                layer_move(game_layers[current_game_layer]);
            }
            return false;

        case GAME_LAYER_UP:
            if (record->event.pressed) {
                if (current_game_layer < (MAX_GAME_LAYERS - 1)) {
                    current_game_layer++;
                } else {
                    current_game_layer = 0;
                }
            }
            return false;
        case GAME_LAYER_DOWN:
            if (record->event.pressed) {
                if (current_game_layer > 0) {
                    current_game_layer--;
                } else {
                    current_game_layer = MAX_GAME_LAYERS - 1;
                }
            }
            return false;




// ┌───────────────────────────────────────────────────────────┐
// │ l a y e r                                                 │
// └───────────────────────────────────────────────────────────┘
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
//                #ifdef HAPTIC_ENABLE
//                  drv2605l_pulse(64);
//                #endif // HAPTIC_ENABLE
            }
            return false;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
//                #ifdef HAPTIC_ENABLE
//                  drv2605l_pulse(17);
//                #endif // HAPTIC_ENABLE
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
//                #ifdef HAPTIC_ENABLE
//                  drv2605l_pulse(17);
//                #endif // HAPTIC_ENABLE
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
//                #ifdef HAPTIC_ENABLE
//                  drv2605l_pulse(17);
//                #endif // HAPTIC_ENABLE
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case GAME_SWITCH:
            if (record->event.pressed) {
                layer_on(_GAME_SWITCH);
            } else {
                layer_off(_GAME_SWITCH);
            }
            return false;
        case MARATHON:
            if (record->event.pressed) {
                layer_on(_MARATHON);
            } else {
                layer_off(_MARATHON);
            }
            return false;


// ┌───────────────────────────────────────────────────────────┐
// │ q m k                                                     │
// └───────────────────────────────────────────────────────────┘

        case MAKE_H:
          if (record->event.pressed) {
            #ifdef KEYBOARD_klor_kb2040
              SEND_STRING ("qmk compile -kb klor/2040 -km default");
            #else
              SEND_STRING ("qmk compile -kb klor -km default");
            #endif
            tap_code(KC_ENTER);
          }
          break;

// ┌───────────────────────────────────────────────────────────┐
// │ p r o d u c t i v i t y                                   │
// └───────────────────────────────────────────────────────────┘

      case KC_MPLY:
        if (record->event.pressed) {
//          #ifdef HAPTIC_ENABLE
//                  drv2605l_pulse(4);
//          #endif // HAPTIC_ENABLE
        }
        break;
    }
    return true;
}

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ L E D S                                                                                                                                    │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

bool rgb_matrix_indicators_user(void) {
    float brightness = 0.5;
    const RGB arasaka_red = { 255 * brightness, 0, 0 };
    const RGB aperture_blue = { 0, 130 * brightness, 196 * brightness };
    const RGB black_mesa_yellow = { 238 * brightness, 127 * brightness, 27 * brightness };

    const RGB royal_purple = { 255 * brightness, 0, 255 * brightness };

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            if (is_keyboard_master()) {
                rgb_matrix_set_color_all(255*brightness, 255*brightness, 255*brightness);
                rgb_matrix_set_color(12, aperture_blue.r, aperture_blue.g, aperture_blue.b);
                rgb_matrix_set_color(11, aperture_blue.r, aperture_blue.g, aperture_blue.b);
                rgb_matrix_set_color(10, aperture_blue.r, aperture_blue.g, aperture_blue.b);
                rgb_matrix_set_color(13, aperture_blue.r, aperture_blue.g, aperture_blue.b);
                rgb_matrix_set_color(14, aperture_blue.r, aperture_blue.g, aperture_blue.b);
                rgb_matrix_set_color(6, aperture_blue.r, aperture_blue.g, aperture_blue.b);
                rgb_matrix_set_color(7, aperture_blue.r, aperture_blue.g, aperture_blue.b);
                rgb_matrix_set_color(19, aperture_blue.r, aperture_blue.g, aperture_blue.b);
                rgb_matrix_set_color(9, black_mesa_yellow.r, black_mesa_yellow.g, black_mesa_yellow.b);
            } else {
                rgb_matrix_set_color_all(255*brightness, 255*brightness, 255*brightness);

                // araska

                rgb_matrix_set_color(12, arasaka_red.r, 0, 0);
                rgb_matrix_set_color(11, arasaka_red.r, 0, 0);
                rgb_matrix_set_color(10, arasaka_red.r, 0, 0);
                rgb_matrix_set_color(13, arasaka_red.r, 0, 0);
                rgb_matrix_set_color(14, arasaka_red.r, 0, 0);
                rgb_matrix_set_color(6, arasaka_red.r, 0, 0);
                rgb_matrix_set_color(7, arasaka_red.r, 0, 0);
                rgb_matrix_set_color(19, arasaka_red.r, 0, 0);
                rgb_matrix_set_color(9, black_mesa_yellow.r, black_mesa_yellow.g, black_mesa_yellow.b);
            }
            // Set WASD to Red (replace numbers with your LED indices)

            break;
        case _MARATHON:
        if (is_keyboard_master()) {
            rgb_matrix_set_color_all(0,0,0);
            rgb_matrix_set_color(11, arasaka_red.r, 0, 0);
            rgb_matrix_set_color(10, arasaka_red.r, 0, 0);
            rgb_matrix_set_color(14, arasaka_red.r, 0, 0);
            rgb_matrix_set_color(7, arasaka_red.r, 0, 0);

            rgb_matrix_set_color(4, royal_purple.r, 0, royal_purple.b);
            rgb_matrix_set_color(3, royal_purple.r, 0, royal_purple.b);
            rgb_matrix_set_color(8, royal_purple.r, 0, royal_purple.b);
            rgb_matrix_set_color(19, royal_purple.r, 0, royal_purple.b);
            rgb_matrix_set_color(20, royal_purple.r, 0, royal_purple.b);
            rgb_matrix_set_color(16, royal_purple.r, 0, royal_purple.b);
            rgb_matrix_set_color(17, royal_purple.r, 0, royal_purple.b);
            rgb_matrix_set_color(18, royal_purple.r, 0, royal_purple.b);


            rgb_matrix_set_color(13, black_mesa_yellow.r, black_mesa_yellow.g, black_mesa_yellow.b);
            rgb_matrix_set_color(12, black_mesa_yellow.r, black_mesa_yellow.g, black_mesa_yellow.b);
            rgb_matrix_set_color(6, black_mesa_yellow.r, black_mesa_yellow.g, black_mesa_yellow.b);
            rgb_matrix_set_color(5, black_mesa_yellow.r, black_mesa_yellow.b, black_mesa_yellow.b);
        } else {
            rgb_matrix_set_color_all(0,0,0);
            rgb_matrix_set_color(5, royal_purple.r, 0, royal_purple.b);
            rgb_matrix_set_color(3, royal_purple.r, 0, royal_purple.b);

        }
            break;
    }
    return false;
}

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ E N C O D E R                                                                                                                              │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(KC_WBAK, KC_WFWD) },
    [_LOWER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_RAISE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_ADJUST] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_GAME_SWITCH] = { ENCODER_CCW_CW(KC_NO, KC_NO),               ENCODER_CCW_CW(GAME_LAYER_DOWN, GAME_LAYER_UP) },
    [_MARATHON] = { ENCODER_CCW_CW(KC_NO, KC_NO),               ENCODER_CCW_CW(KC_NO, KC_NO) }

};
#endif

/*

                                                       ▐█    ▟▛ ▐█     ▄▆▀▀▀▀▀▀▆▄  ▐█▀▀▀▀▀█▌
                                                       ▐█   ▟▛  ▐█    ▟▛        ▜▙ ▐█     █▌
                                                       ▐█  ▟▛   ▐█   ▐█          █▋▐█     █▌
                                                       ▐█ ▟█▙   ▐█   ▐█          █▋▐█▀▀▜█▀▀▘
                                                       ▐█▟▛ ▜▙  ▐█    ▜▙        ▟▛ ▐█   ▜▙
                                                       ▐█▛   ▜▙ ▐█▄▄▄▄ ▀▜▆▄▄▄▄▆▛▀  ▐█    ▜▙

                                                                 ▄██████████████▄
                                                                 ████████████████
                                                            ▄██████▀  ▀████▀  ▀██████▄
                                                            ███████▄  ▄████▄  ▄███████
                                                            ███████████▀▀▀▀███████████
                                                            ▀█████████▀ ▄▄ ▀█████████▀
                                                                 ████▀ ▄██▄ ▀████
                                                                 ████▄▄████▄▄████

*/
