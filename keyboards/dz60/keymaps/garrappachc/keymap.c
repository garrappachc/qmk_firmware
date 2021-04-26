#include QMK_KEYBOARD_H

#define COLOR_LAYER_DEFAULT_HUE 0
#define COLOR_LAYER_DEFAULT_SAT 0

#define COLOR_LAYER_1_HUE 106
#define COLOR_LAYER_1_SAT 255

#define COLOR_VALUE_LOW 128
#define COLOR_VALUE_HIGH 192

static bool color_overridden = false;
static uint8_t hue = COLOR_LAYER_DEFAULT_HUE;
static uint8_t sat = COLOR_LAYER_DEFAULT_SAT;
static uint8_t val = COLOR_VALUE_LOW;

static void update_rgblight(void) {
    if (!color_overridden) {
        rgblight_sethsv_noeeprom(hue, sat, val);
    }
}

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  rgblight_sethsv(hue, sat, val);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 1:
        hue = COLOR_LAYER_1_HUE;
        sat = COLOR_LAYER_1_SAT;
        update_rgblight();
        break;

    default:
        hue = COLOR_LAYER_DEFAULT_HUE;
        sat = COLOR_LAYER_DEFAULT_SAT;
        update_rgblight();
        break;
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_LSFT: {
        val = record->event.pressed ? COLOR_VALUE_HIGH : COLOR_VALUE_LOW;
        update_rgblight();
        return true;
    }

    case KC_SPC:
        color_overridden = record->event.pressed;
        if (record->event.pressed) {
            rgblight_sethsv_noeeprom(21, 255, COLOR_VALUE_HIGH);
        } else {
            update_rgblight();
        }
        return true;

    default:
        return true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, XXXXXXX,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,  KC_SPC,  KC_SPC,           _______, KC_RALT, MO(1),   KC_RGUI, KC_RCTL
    ),

    LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_UP,   KC_PGDN, KC_TRNS, KC_PSCR, KC_TRNS, _______,
        _______, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,  KC_DEL,           _______,
        KC_TRNS, _______, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_END,  KC_TRNS, KC_TRNS, KC_TRNS, _______, _______, _______,
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, _______, _______, KC_TRNS
    )
};
