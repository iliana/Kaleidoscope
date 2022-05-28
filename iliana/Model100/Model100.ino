// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// Copyright 2022 iliana etaoin <iliana@buttslol.net>
// See "LICENSE" for license details

#include "Kaleidoscope.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-LEDEffect-SolidColor.h"
#include "Kaleidoscope-HostPowerManagement.h"

enum {
  MACRO_ANY,
  MACRO_RESET_BOOTLOADER,
};  // macros

enum {
  PRIMARY,
  FUNCTION,
  PROG_KEY,
};  // layers

// clang-format off

KEYMAPS(
  [PRIMARY] = KEYMAP_STACKED
  (ShiftToLayer(PROG_KEY), Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick,           Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,             Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown,           Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY), Key_6, Key_7, Key_8,     Key_9,      Key_0,         XXX,
   Key_Enter,    Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
                 Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   XXX,          Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),

  [FUNCTION] = KEYMAP_STACKED
  (XXX,      Key_F1, Key_F2, Key_F3, Key_F4, Key_F5, XXX,
   Key_Tab,  XXX,    XXX,    XXX,    XXX,    XXX,    XXX,
   Key_Home, XXX,    XXX,    XXX,    XXX,    XXX,
   Key_End,  XXX,    XXX,    XXX,    XXX,    XXX,    XXX,
   XXX, Key_Delete, XXX, XXX,
   XXX,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  XXX,              XXX,
   XXX,                        Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, XXX,             Key_Backslash,    Key_Pipe,
   XXX, XXX, XXX, XXX,
   XXX),

  [PROG_KEY] = KEYMAP_STACKED
  (XXX, XXX, XXX, XXX, XXX, XXX, XXX,
   XXX, XXX, XXX, XXX, XXX, XXX, XXX,
   XXX, XXX, XXX, XXX, XXX, XXX,
   XXX, XXX, XXX, XXX, XXX, XXX, XXX,
   XXX, XXX, XXX, XXX,
   XXX,

   XXX,                       XXX, XXX, XXX, XXX, XXX, XXX,
   M(MACRO_RESET_BOOTLOADER), XXX, XXX, XXX, XXX, XXX, XXX,
                              XXX, XXX, XXX, XXX, XXX, XXX,
   XXX,                       XXX, XXX, XXX, XXX, XXX, XXX,
   XXX, XXX, XXX, XXX,
   XXX)
)

// clang-format on

static kaleidoscope::plugin::LEDSolidColor solidViolet(130, 0, 120);

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {
  case MACRO_ANY:
    if (keyToggledOn(event.state)) {
      event.key.setKeyCode(Key_A.getKeyCode() + (uint8_t)(millis() % 36));
      event.key.setFlags(0);
    }
    break;
  case MACRO_RESET_BOOTLOADER:
    if (keyToggledOn(event.state)) {
      Macros.tap(Key_Enter);
      kaleidoscope::Runtime.device().rebootBootloader();
    }
    break;
  }
  return MACRO_NONE;
}

/** Toggle LEDs off when suspending and on when resuming */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    break;
  }
}

KALEIDOSCOPE_INIT_PLUGINS(
  LEDControl,
  LEDOff,
  solidViolet,
  Macros,
  HostPowerManagement);

void setup() {
  Kaleidoscope.setup();
  LEDOff.activate();
}

void loop() {
  Kaleidoscope.loop();
}
