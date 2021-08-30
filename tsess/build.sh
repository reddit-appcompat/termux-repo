#!/bin/bash

cd "$(dirname "$0")"
gzip -k -f tsessc.1 tsessd.1
termux-create-package manifest.json
