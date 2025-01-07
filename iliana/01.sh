#!/usr/bin/env bash
exec make \
    -f "$(git rev-parse --show-toplevel)/etc/makefiles/sketch.mk" \
    "$@" \
    FQBN=keyboardio:avr:model01 \
    LOCAL_CFLAGS="-DKALEIDOSCOPE_FIRMWARE_VERSION=\\\"$(git describe --dirty --broken)\\\""
