C = gcc

MXP_IDIR = -I ../vbxapi/ 
LDIR     = -L ../vbxapi/ 

LIBS     = -lvbxapi -lm -lrt

ARM_FLAGS = --cpu=Cortex-A9 -O3 
NEON_FLAGS = -O3 -mfpu=neon -ftree-vectorize
MXP_FLAGS = -mfloat-abi=hard -mfpu=neon


all: poly_arm poly_neon poly_mxp 

poly_arm:
	$(CC)  $(ARM_FLAGS) -DARM poly.c -o poly_arm

poly_neon:
	$(CC)  $(NEON_GCC_IDIR) $(NEON_FLAGS) -DNEON poly.c -o poly_neon

poly_mxp:
	$(CC) -O3  $(MXP_IDIR) $(MXP_FLAGS) -DMXP poly.c -o poly_mxp $(LDIR)
$(LIBS)

clean:
	rm -f poly_arm 
	rm -f poly_neon 
	rm -f poly_mxp
