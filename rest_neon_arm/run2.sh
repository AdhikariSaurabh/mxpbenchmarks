#!bin/bash

gcc --cpu=CORTEX-A9 -mfpu=neon -o test_app stencil.c -lm -lrt

