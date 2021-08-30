#!/bin/bash
clang -fPIC -shared -o fixuser.so fixuser.c
gzip -k -f termux-user-fix.7
termux-create-package manifest.json
