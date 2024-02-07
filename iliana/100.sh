#!/usr/bin/env bash
KALEIDOSCOPE_DIR=$(git rev-parse --show-toplevel) \
    exec make "$@" FQBN=keyboardio:gd32:keyboardio_model_100
