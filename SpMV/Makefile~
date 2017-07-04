

CC = gcc

MXP_IDIR = -I ../../vbxapi/ 
LDIR     = -L ../../vbxapi/ 

LIBS     = -lvbxapi -lm -lrt

MXP_FLAGS = -mfloat-abi=hard -mfpu=neon


all: sparse_mxp_50*25 sparse_mxp_25*25


sparse_mxp_50*25:
	$(CC)  -O3 $(MXP_IDIR) $(MXP_FLAGS) sparse_mxp_50*25.c -o sparse_mxp_50*25 $(LDIR) $(LIBS)


sparse_mxp_25*25:
	$(CC)  -O3 $(MXP_IDIR) $(MXP_FLAGS) sparse_mxp_25*25.c -o  sparse_mxp_25*25 $(LDIR) $(LIBS)

clean:
	rm -f sparse_mxp_50*25
	rm -f sparse_mxp_25*25

