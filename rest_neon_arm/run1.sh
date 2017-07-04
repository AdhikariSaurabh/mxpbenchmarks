#!bin/bash
gcc --cpu=CORTEX-A9 -O3 --vectorize -c stencil.c  
gcc -o test_app stencil.o -lm -lrt 

