// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

enum layers {
    _NUMPAD,
    _FN,
    _KB_NUMBERS,
    _EXTRAS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_NUMPAD] = LAYOUT(
        KC_MEDIA_PLAY_PAUSE,  KC_HOME,           KC_END,           KC_ESC,
        KC_P7,                KC_P8,             KC_P9,            KC_PSLS,
        KC_P4,                KC_P5,             KC_P6,            KC_PAST,
        KC_P1,                KC_P2,             KC_P3,            KC_PMNS,
        KC_P0,                KC_PDOT,           KC_PPLS,          MO(_EXTRAS)
    ),

    [_FN] = LAYOUT(
        KC_MEDIA_PLAY_PAUSE,  KC_HOME,           KC_END,           KC_ESC,
        KC_F9,                KC_F10,            KC_F11,           KC_F12,
        KC_F5,                KC_F6,             KC_F7,            KC_F8,
        KC_F1,                KC_F2,             KC_F3,            KC_F4,
        KC_PSCR,              KC_DEL,            KC_INS,           KC_APP
    ),

    [_KB_NUMBERS] = LAYOUT(
        KC_MEDIA_PLAY_PAUSE,  KC_HOME,           KC_END,           KC_ESC,
        KC_7,                 KC_8,              KC_9,             KC_PSLS,
        KC_4,                 KC_5,              KC_6,             KC_PAST,
        KC_1,                 KC_2,              KC_3,             KC_PMNS,
        KC_0,                 KC_PDOT,           KC_PPLS,          MO(_EXTRAS)
    ),

    [_EXTRAS] = LAYOUT(
        KC_MEDIA_PLAY_PAUSE,  KC_HOME,           KC_END,           KC_ESC,
        KC_P7,                KC_P8,             KC_P9,            KC_PSLS,
        KC_P4,                KC_UP,             KC_P6,            KC_PAST,
        KC_LEFT,              KC_DOWN,           KC_RIGHT,         KC_BSPC,
        KC_P0,                KC_PENT,           KC_PEQL,          KC_NO
    ),
};


bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t current_layer = get_highest_layer(layer_state);

    switch (index) {
        case 0:
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
            break;
        case 1:
            tap_code(clockwise ? KC_DOWN : KC_UP);
            break;
        case 2:
            tap_code(clockwise ? KC_LEFT : KC_RIGHT);
            break;
        case 3: {

            const uint8_t layers[] = {_NUMPAD, _FN, _KB_NUMBERS};
            const uint8_t num_layers = sizeof(layers) / sizeof(layers[0]);

            uint8_t current_index = 0;
            for (uint8_t i = 0; i < num_layers; i++) {
                if (layers[i] == current_layer) {
                    current_index = i;
                    break;
                }
            }

            uint8_t next_index = (current_index + (clockwise ? 1 : num_layers - 1)) % num_layers;

            layer_move(layers[next_index]);
            break;
        }
    }

    return true;
}



#ifdef OLED_ENABLE

static void render_logo(void) {
    static char logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};

    oled_write_P(logo, false);

}

bool oled_task_user(void) {
    render_logo();
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _NUMPAD:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("FN\n"), false);
            break;
        case _KB_NUMBERS:
            oled_write_P(PSTR("KB Numbers\n"), false);
            break;
        case _EXTRAS:
            oled_write_P(PSTR("Extras\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Default"), false);
    }


    return false;
}

#endif
