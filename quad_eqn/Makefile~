
CC = gcc
 
MXP_IDIR = -I ../../vbxapi/
LDIR     = -L ../../vbxapi/

LIBS     = -lvbxapi -lm -lrt 

NEON_FLAGS = -mfpu=neon -ftree-vectorize
ARM_FLAGS  = --cpu=Cortex-A9
MXP_FLAGS  = -mfloat-abi=hard -mfpu=neon


all: quad_arm quad_mxp quad_neon

quad_arm:
	$(CC) -O3  $(ARM_FLAGS) quad_byte_arm_v7.c -o quad_arm

quad_neon:
	$(CC) -O3  $(NEON_FLAGS) quad_byte_neon.c -o quad_neon

quad_mxp:
	$(CC) -O3  $(MXP_IDIR) $(MXP_FLAGS) quad_byte_mxp.c -o quad_mxp $(LDIR) $(LIBS)

clean:
	rm -f quad_mxp 
	rm -f quad_arm 
	rm -f quad_neon 
	 

