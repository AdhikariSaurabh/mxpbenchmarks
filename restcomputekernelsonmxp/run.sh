#!bin/bash

gcc -I../../../../repository/lib/vbxapi/obj/LINUX -I../../../../repository/lib/vbxapi -I../../lib/libfixmath -I../../lib/libfixmath/obj/LINUX  -I../../lib/scalar -I../../lib/scalar/obj/LINUX -I../../lib/vbxtest -I../../lib/vbxtest/obj/LINUX -I../../lib/vbxware -I../../lib/vbxware/obj/LINUX -I../../lib/vbxware++ -I../../lib/vbxware++/obj/LINUX -mfloat-abi=hard -mfpu=neon -o out mm.c -L../../../../repository/lib/vbxapi -L../../lib/libfixmath -L../../lib/scalar -L../../lib/vbxtest -L../../lib/vbxware -L../../lib/vbxware++ -lvbxapi -lfixmath -lscalar -lvbxtest -lvbxware -lm -lrt 

