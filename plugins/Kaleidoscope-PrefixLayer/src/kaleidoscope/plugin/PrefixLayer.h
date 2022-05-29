/* -*- mode: c++ -*-
 * Kaleidoscope-PrefixLayer -- Sends a prefix key for every key in a layer.
 * Copyright (C) 2017, 2022  iliana etaoin <iliana@buttslol.net>
 * Copyright (C) 2017  James Cash
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>  // for uint8_t

#include "kaleidoscope/KeyEvent.h"              // for KeyEvent
#include "kaleidoscope/event_handler_result.h"  // for EventHandlerResult
#include "kaleidoscope/key_defs.h"              // for Key
#include "kaleidoscope/plugin.h"                // for Plugin

namespace kaleidoscope {
namespace plugin {

class PrefixLayer : public Plugin {
 public:
  EventHandlerResult onKeyEvent(KeyEvent &event);
  EventHandlerResult beforeReportingState(const KeyEvent &event);

  struct Entry {
    uint8_t layer;
    Key prefix;

    constexpr Entry(uint8_t layer, Key prefix)
      : layer(layer), prefix(prefix) {}
  };

  void setPrefixLayers(const Entry *prefix_layers);
  const Entry *getPrefixLayers();
  uint8_t getPrefixLayersLength();

 private:
  const Entry *prefix_layers_ PROGMEM = {};
  uint8_t prefix_layers_length_       = 0;
  bool clear_modifiers_               = false;
};

}  // namespace plugin
}  // namespace kaleidoscope

extern kaleidoscope::plugin::PrefixLayer PrefixLayer;
