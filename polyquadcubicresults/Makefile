
CC = gcc

MXP_IDIR = -I ../../vbxapi/ 
LDIR     = -L ../../vbxapi/ 

LIBS     = -lvbxapi -lm -lrt

ARM_FLAGS = --cpu=Cortex-A9 -O3 
NEON_FLAGS = -O3 -mfpu=neon -ftree-vectorize
MXP_FLAGS = -mfloat-abi=hard -mfpu=neon


all: quad_arm quad_neon quad_mxp cubic_arm cubic_neon cubic_mxp

quad_arm:
	$(CC)  $(ARM_FLAGS)  quad_byte_arm_v7.c -o quad_arm

cubic_arm:
	$(CC)  $(ARM_V7_IDIR) $(ARM_FLAGS) cubic_byte_arm_v7.c -o cubic_arm

quad_neon:
	$(CC)  $(NEON_GCC_IDIR) $(NEON_FLAGS) quad_byte_neon.c  -o quad_neon

cubic_neon:
	$(CC)  $(NEON_GCC_IDIR) $(NEON_FLAGS) cubic_byte_neon.c -o cubic_neon
quad_mxp:
	$(CC) -O3  $(MXP_IDIR) $(MXP_FLAGS) quad_byte_mxp.c -o quad_mxp $(LDIR) $(LIBS)

cubic_mxp:
	$(CC) -O3 $(MXP_IDIR) $(MXP_FLAGS) cubic_byte_mxp.c -o cubic_mxp $(LDIR) $(LIBS)


clean:
	rm -f quad_arm 
	rm -f quad_neon 
	rm -f quad_mxp
	rm -f cubic_arm 
	rm -f cubic_neon 
	rm -f cubic_mxp 
