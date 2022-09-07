// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// Copyright 2022 iliana etaoin <iliana@buttslol.net>
// See "LICENSE" for license details

#include "Kaleidoscope.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-HostPowerManagement.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-LEDEffect-SolidColor.h"
#include "Kaleidoscope-Leader.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-PrefixLayer.h"

static uint32_t rng_value = 0x000005A0;
uint16_t rng(uint16_t ceiling) { return (uint16_t)(rng_value >> 16) % ceiling; }

enum {
  PRIMARY,
  FUNCTION,
  TMUX,
};  // layers

enum {
  MACRO_RESET_BOOTLOADER,
};  // macros

// clang-format off

KEYMAPS(
  [PRIMARY] = KEYMAP_STACKED
  (XXX,          Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDToggle,
   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   ShiftToLayer(FUNCTION),

   LEAD(0),            Key_6, Key_7, Key_8,     Key_9,      Key_0,         LSHIFT(LALT(Key_DownArrow)),
   Key_Enter,          Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
                       Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   ShiftToLayer(TMUX), Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),

  [FUNCTION] = KEYMAP_STACKED
  (XXX,      Key_F1, Key_F2, Key_F3, Key_F4, Key_F5, XXX,
   Key_Tab,  XXX,    XXX,    XXX,    XXX,    XXX,    XXX,
   Key_Home, XXX,    XXX,    XXX,    XXX,    XXX,
   Key_End,  XXX,    XXX,    XXX,    XXX,    XXX,    XXX,
   ___, Key_Delete, ___, ___,
   XXX,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  XXX,              XXX,
   ___,                        Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, XXX,             Key_Backslash,    Key_Pipe,
   ___, ___, XXX, ___,
   XXX),

  [TMUX] = KEYMAP_STACKED
  (XXX, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, XXX, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   XXX, ___,           ___,                  ___,                   ___,             ___,              ___,
   ___, ___,           Key_LeftCurlyBracket, Key_RightCurlyBracket, Key_LeftBracket, Key_RightBracket, ___,
        Key_LeftArrow, Key_DownArrow,        Key_UpArrow,           Key_RightArrow,  ___,              ___,
   ___, ___,           ___,                  ___,                   ___,             ___,              ___,
   ___, ___, ___, ___,
   ___),
)

// clang-format on

/** Toggle LEDs off when suspending and on when resuming */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
    case kaleidoscope::plugin::HostPowerManagement::Suspend:
      LEDControl.disable();
      break;
    case kaleidoscope::plugin::HostPowerManagement::Resume:
      LEDControl.enable();
      break;
  }
}

kaleidoscope::plugin::LEDSolidColor solidViolet(26, 0, 24);

void leader_any(uint8_t seq_index) {
  Macros.tap(Key(Key_A.getKeyCode() + (uint8_t)(rng(36)), KEY_FLAGS));
}

const kaleidoscope::plugin::Leader::dictionary_t leader_dictionary[] PROGMEM =
    LEADER_DICT({LEADER_SEQ(LEAD(0), LEAD(0)), leader_any});

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    switch (macro_id) {
      case MACRO_RESET_BOOTLOADER:
        Macros.tap(Key_Enter);
        delay(5);
        kaleidoscope::Runtime.device().rebootBootloader();
        break;
    }
  }
  return MACRO_NONE;
}

const kaleidoscope::plugin::PrefixLayer::Entry prefix_layers[] PROGMEM = {
    kaleidoscope::plugin::PrefixLayer::Entry(TMUX, LCTRL(Key_B))};

KALEIDOSCOPE_INIT_PLUGINS(Focus, HostPowerManagement, LEDControl, solidViolet, Leader, Macros,
                          PrefixLayer);

void setup() {
  Kaleidoscope.setup();
  Leader.dictionary = leader_dictionary;
  PrefixLayer.setPrefixLayers(prefix_layers);
}

void loop() {
  rng_value = rng_value * 0x41C64E6D + 0x6073;
  Kaleidoscope.loop();
}
