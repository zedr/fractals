#!/bin/bash

gcc sier.c -s gfx/gfx.c -I gfx -o sier -Wall -Wformat -lX11 -lm
