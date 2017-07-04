
CC = gcc

MXP_IDIR = -I ../vbxapi/ 
LDIR     = -L ../vbxapi/ 

LIBS     = -lvbxapi -lm -lrt

MXP_FLAGS = -mfloat-abi=hard -mfpu=neon


all: fft kmeans mm spmv mri stencil


fft:
	$(CC)  -O3 $(MXP_IDIR) $(MXP_FLAGS) fft.c -o fft $(LDIR) $(LIBS)

kmeans:
	$(CC)  -O3 $(MXP_IDIR) $(MXP_FLAGS) kmeans.c -o kmeans $(LDIR) $(LIBS)

mm:
	$(CC)  -O3 $(MXP_IDIR) $(MXP_FLAGS) mm.c -o mm $(LDIR) $(LIBS)

spmv:
	$(CC)  -O3 $(MXP_IDIR) $(MXP_FLAGS) spmv.c -o spmv $(LDIR) $(LIBS)

mri:
	$(CC)  -O3 $(MXP_IDIR) $(MXP_FLAGS) mri.c -o mri $(LDIR) $(LIBS)
stencil:
	$(CC)  -O3 $(MXP_IDIR) $(MXP_FLAGS) stencil.c -o stencil $(LDIR) $(LIBS)
clean:
	rm -f fft
	rm -f kmeans
	rm -f mm
	rm -f spmv
	rm -f mri
	rm -f stencil


