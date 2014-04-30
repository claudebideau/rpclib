#!/bin/bash
if [ ! -d "m4" ]; then
    mkdir m4
fi
autoreconf --force --install -I config -I m4
