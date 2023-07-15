#!/bin/sh

set -xe

CFLAGS="-O3 -Wall -Wextra -I./thirdparty/"
LIBS="-lraylib -lglfw -ldl -lpthread -lm"

rm -rf build
mkdir build

cc $CFLAGS -o build/game main.c $LIBS
