#!/bin/bash
mkdir -p build/mac
cp -r res build/mac/

# Detect Homebrew installation path
if [ -d "/opt/homebrew" ]; then
    # Apple Silicon Mac
    HOMEBREW_PREFIX="/opt/homebrew"
else
    # Intel Mac
    HOMEBREW_PREFIX="/usr/local"
fi

g++ main.cpp -g -ggdb -w \
    -I${HOMEBREW_PREFIX}/include \
    -L${HOMEBREW_PREFIX}/lib \
    -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf \
    -o build/mac/main
