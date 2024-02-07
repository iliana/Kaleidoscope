#!/usr/bin/env bash
exec make -f "$(git rev-parse --show-toplevel)/etc/makefiles/sketch.mk" "$@" FQBN=keyboardio:gd32:keyboardio_model_100
