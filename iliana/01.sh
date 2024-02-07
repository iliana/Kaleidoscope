#!/usr/bin/env bash
KALEIDOSCOPE_DIR=$(git rev-parse --show-toplevel) \
    exec make "$@" FQBN=keyboardio:avr:model01
