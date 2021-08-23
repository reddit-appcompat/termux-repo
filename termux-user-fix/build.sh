#!/bin/bash
clang -fPIC -shared -o fixuser.so fixuser.c
termux-create-package manifest.json
