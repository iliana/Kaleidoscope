// -*- mode: c++ -*-

#include <Kaleidoscope.h>
#include <Kaleidoscope-PrefixLayer.h>

enum {
  PRIMARY,
  TMUX,
};  // layers

static const kaleidoscope::plugin::PrefixLayer::Entry prefix_layers[] PROGMEM = {
  kaleidoscope::plugin::PrefixLayer::Entry(TMUX, LCTRL(Key_B)),
};

// clang-format off
KEYMAPS(
  [PRIMARY] = KEYMAP_STACKED
  (XXX,          Key_1, Key_2, Key_3, Key_4, Key_5, XXX,
   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   XXX,

   XXX,                Key_6, Key_7, Key_8,     Key_9,      Key_0,         XXX,
   Key_Enter,          Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
                       Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   ShiftToLayer(TMUX), Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,
   Key_RightShift, Key_RightAlt, Key_Spacebar, Key_RightControl,
   XXX),

  [TMUX] = KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   ___, ___,           ___,           ___,         ___,            ___, ___,
   ___, ___,           ___,           ___,         ___,            ___, ___,
        Key_LeftArrow, Key_DownArrow, Key_UpArrow, Key_RightArrow, ___, ___,
   ___, ___,           ___,           ___,         ___,            ___, ___,
   ___, ___, ___, ___,
   ___),
)
// clang-format on

KALEIDOSCOPE_INIT_PLUGINS(PrefixLayer);

void setup() {
  Kaleidoscope.setup();
  PrefixLayer.prefix_layers = prefix_layers;
  PrefixLayer.prefix_layers_length = 1;
}

void loop() {
  Kaleidoscope.loop();
}
