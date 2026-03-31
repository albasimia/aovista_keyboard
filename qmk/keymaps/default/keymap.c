#include QMK_KEYBOARD_H

// Day1 scaffold: joystick / RGB logic intentionally omitted.

#ifndef KC_HENK
#    define KC_HENK KC_NO
#endif
#ifndef KC_MHEN
#    define KC_MHEN KC_NO
#endif
#ifndef KC_HAEN
#    define KC_HAEN KC_NO
#endif
#ifndef KC_KANA
#    define KC_KANA KC_NO
#endif

enum layers {
    _BASE,
    _FN,
    _SEL,
};

enum custom_keycodes {
    EMACS = SAFE_RANGE,
    APP_NEXT,
    APP_PREV,
    APP_OK,
    TAB_NEXT,
    TAB_PREV,
    TAB_CLOSE,
    OS_WIN,
    OS_MAC,
};

static bool aorazer_os_is_mac = false;
static bool emacs_held = false;

bool process_detected_host_os_user(os_variant_t detected_os) {
    if (detected_os == OS_MACOS || detected_os == OS_IOS) {
        aorazer_os_is_mac = true;
    } else if (detected_os == OS_WINDOWS || detected_os == OS_LINUX) {
        aorazer_os_is_mac = false;
    }
    return true;
}

static bool send_emacs_combo(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case KC_A:
            tap_code(KC_HOME);
            return false;
        case KC_E:
            tap_code(KC_END);
            return false;
        case KC_H:
            tap_code(KC_BSPC);
            return false;
        case KC_B:
            tap_code(KC_LEFT);
            return false;
        case KC_F:
            tap_code(KC_RGHT);
            return false;
        case KC_P:
            tap_code(KC_UP);
            return false;
        case KC_N:
            tap_code(KC_DOWN);
            return false;
        case KC_J:
            tap_code(KC_F6);
            return false;
        case KC_K:
            tap_code(KC_F7);
            return false;
        case KC_L:
            tap_code(KC_F8);
            return false;
        case KC_SCLN:
            tap_code(KC_F9);
            return false;
        case KC_QUOT:
            tap_code(KC_F10);
            return false;
        default:
            return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (emacs_held && send_emacs_combo(keycode, record) == false) {
        return false;
    }

    switch (keycode) {
        case EMACS:
            if (record->event.pressed) {
                emacs_held = true;
                register_code(aorazer_os_is_mac ? KC_LGUI : KC_LCTL);
            } else {
                unregister_code(aorazer_os_is_mac ? KC_LGUI : KC_LCTL);
                emacs_held = false;
            }
            return false;

        case APP_NEXT:
            if (record->event.pressed) {
                if (aorazer_os_is_mac) {
                    register_mods(MOD_BIT(KC_LGUI));
                    tap_code(KC_TAB);
                    unregister_mods(MOD_BIT(KC_LGUI));
                } else {
                    register_mods(MOD_BIT(KC_LALT));
                    tap_code(KC_TAB);
                    unregister_mods(MOD_BIT(KC_LALT));
                }
            }
            return false;

        case APP_PREV:
            if (record->event.pressed) {
                if (aorazer_os_is_mac) {
                    register_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
                    tap_code(KC_TAB);
                    unregister_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
                } else {
                    register_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT));
                    tap_code(KC_TAB);
                    unregister_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT));
                }
            }
            return false;

        case APP_OK:
            if (record->event.pressed) {
                tap_code(KC_ENT);
            }
            return false;

        case TAB_NEXT:
            if (record->event.pressed) {
                if (aorazer_os_is_mac) {
                    register_mods(MOD_BIT(KC_LCTL));
                    tap_code(KC_TAB);
                    unregister_mods(MOD_BIT(KC_LCTL));
                } else {
                    register_mods(MOD_BIT(KC_LCTL));
                    tap_code(KC_PGDN);
                    unregister_mods(MOD_BIT(KC_LCTL));
                }
            }
            return false;

        case TAB_PREV:
            if (record->event.pressed) {
                if (aorazer_os_is_mac) {
                    register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
                    tap_code(KC_TAB);
                    unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
                } else {
                    register_mods(MOD_BIT(KC_LCTL));
                    tap_code(KC_PGUP);
                    unregister_mods(MOD_BIT(KC_LCTL));
                }
            }
            return false;

        case TAB_CLOSE:
            if (record->event.pressed) {
                register_mods(MOD_BIT(aorazer_os_is_mac ? KC_LGUI : KC_LCTL));
                tap_code(KC_W);
                unregister_mods(MOD_BIT(aorazer_os_is_mac ? KC_LGUI : KC_LCTL));
            }
            return false;

        case OS_WIN:
            if (record->event.pressed) aorazer_os_is_mac = false;
            return false;
        case OS_MAC:
            if (record->event.pressed) aorazer_os_is_mac = true;
            return false;
    }

    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        tap_code16(clockwise ? APP_NEXT : APP_PREV);
    } else if (index == 1) {
        tap_code16(clockwise ? TAB_NEXT : TAB_PREV);
    }
    return false;
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_4,    KC_5,    KC_6,    KC_3,    KC_GRV,  KC_1,    KC_2,               KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,
        KC_E,    KC_R,    KC_T,    KC_W,    KC_PGUP, KC_TAB,  KC_Q,               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
        KC_D,    KC_F,    KC_G,    KC_S,    KC_PGDN, EMACS,   KC_A,               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,
        KC_C,    KC_V,    KC_B,    KC_X,    KC_HOME, KC_LSFT, KC_Z,               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSFT,
        KC_NO,   KC_SPC,  KC_ESC,  MO(_FN), KC_LCTL, KC_LALT, KC_LGUI, KC_END,   KC_ENT,  KC_SPC,  KC_BSPC, KC_RGUI, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT(
        KC_F4,   KC_F5,   KC_F6,   KC_F3,   KC_F11,  KC_F1,   KC_F2,              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, KC_MSTP, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, OS_WIN,  KC_BRIU, OS_MAC,
        KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_BRID, KC_RGHT
    ),

    [_SEL] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
    )
};
