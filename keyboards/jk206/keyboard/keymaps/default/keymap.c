// Copyright 2025-2026 Jhonatan Ferrer (@JhonatanFerrer)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _GAME,
    _FN,
    _SYM,
};

bool is_windows = true;

enum custom_keycodes {
    ENIE = SAFE_RANGE,
    PREGUNTA,
    GRADO,
    VIRGUL,
    AC_GRAV,
    CHANGE_OS
};

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_WINDOWS:
            is_windows = true;
            break;
        case OS_LINUX:
            is_windows = false;
            break;
        case OS_MACOS:
            break;
        case OS_IOS:
            break;
        case OS_UNSURE:
            break;
    }

    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Base */
    [_BASE] = LAYOUT_ortho_5x12(
        KC_MPLY,        KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_PSCR,
        KC_ESC,         KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
        KC_TAB,         KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
        KC_LSFT,        KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_ENT,
        KC_LCTL,        KC_LGUI,    KC_APP,     KC_LALT,    MO(_SYM),   KC_SPC,     KC_SPC,     MO(_SYM),   KC_RALT,    KC_APP,     KC_RCTL,    MO(_FN)
    ),
    /* Layer 1: Game */
    [_GAME] = LAYOUT_ortho_5x12(
        KC_MPLY,        KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_PSCR,
        KC_ESC,         KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
        KC_TAB,         KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
        KC_LSFT,        KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_UP,      KC_SLSH,    KC_ENT,
        KC_LCTL,        KC_LGUI,    TO(_BASE),  KC_LALT,    KC_SPC,     KC_SPC,     KC_SPC,     MO(_SYM),   KC_LEFT,    KC_DOWN,    KC_RGHT,    MO(_FN)
    ),
    /* Layer 2: FN */
    [_FN] = LAYOUT_ortho_5x12(
        KC_F1,          KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
        KC_ESC,         KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
        KC_TAB,         KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
        KC_CAPS,        KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_UP,      KC_SLSH,    KC_ENT,
        KC_LCTL,        KC_LGUI,    KC_APP,     KC_LALT,    MO(_SYM),   KC_SPC,     KC_SPC,     MO(_SYM),   KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_TRNS
    ),
    /* Layer 3: Symbols */
    [_SYM] = LAYOUT_ortho_5x12(
        CHANGE_OS,      KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       TO(_GAME),
        GRADO,          KC_PLUS,    KC_MINS,    KC_EQL,     KC_UNDS,    KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_DEL,
        KC_PGUP,        KC_LCBR,    KC_RCBR,    KC_PIPE,    KC_BSLS,    KC_G,       KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_SCLN,    KC_QUOT,
        KC_PGDN,        KC_LBRC,    KC_RBRC,    VIRGUL,     AC_GRAV,    KC_B,       ENIE,       KC_M,       KC_COMM,    KC_DOT,     PREGUNTA,   KC_ENT,
        KC_LCTL,        KC_LGUI,    KC_APP,     KC_LALT,    KC_TRNS,    KC_SPC,     KC_SPC,     KC_TRNS,    KC_RALT,    KC_APP,     KC_RCTL,    KC_TRNS
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case ENIE:
            if (record->event.pressed) {
                tap_code16(KC_TILD);
                tap_code16(KC_N);
            }
            return false;

        case PREGUNTA:
        if (is_windows){
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code16(KC_P1);
                tap_code16(KC_P6);
                tap_code16(KC_P8);
                unregister_code(KC_LALT);
            }
        }
        else{
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                tap_code(KC_U);
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
                tap_code(KC_B);
                tap_code(KC_F);
                tap_code16(KC_SPC);
            }
        }

        return false;

        case GRADO:
            if (is_windows){
                if (record->event.pressed) {
                    register_code(KC_LALT);
                    tap_code16(KC_P2);
                    tap_code16(KC_P4);
                    tap_code16(KC_P8);
                    unregister_code(KC_LALT);
                }
            }
            else{
                if (record->event.pressed) {
                    register_code(KC_LCTL);
                    register_code(KC_LSFT);
                    tap_code(KC_U);
                    unregister_code(KC_LCTL);
                    unregister_code(KC_LSFT);
                    tap_code(KC_B);
                    tap_code(KC_0);
                    tap_code16(KC_SPC);
                }
            }

            return false;

        case VIRGUL:
            if (record->event.pressed) {
                tap_code16(KC_TILD);
                tap_code16(KC_SPC);
            }
            return false;

        case AC_GRAV:
            if (record->event.pressed) {
                tap_code16(KC_GRV);
                tap_code16(KC_SPC);
            }
            return false;

        case CHANGE_OS:
            if (record->event.pressed) {
                is_windows = !is_windows;
            }
            return false;

        default:
            return true;
    }
}



bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return false;
}


#ifdef OLED_ENABLE

static void render_logo(void) {
    static char logo[] = {
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
      0};

    oled_write_P(logo, false);

}

static void render_os(void) {
    static char linux[] = {
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x99, 0x9A, 0x80,
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xB9, 0xBA, 0x80,
      0};

    static char windows[] = {
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x97, 0x98, 0x80,
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xB7, 0xB8, 0x80,
      0};

    oled_write_P(is_windows ? windows : linux, false);

}

bool oled_task_user(void) {
    render_logo();
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("BASE\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("FUNCTION\n"), false);
            break;
        case _SYM:
            oled_write_P(PSTR("SYMBOLS\n"), false);
            break;
        case _GAME:
            oled_write_P(PSTR("GAME MODE\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Default"), false);
    }
    render_os();

    return false;
}

#endif
