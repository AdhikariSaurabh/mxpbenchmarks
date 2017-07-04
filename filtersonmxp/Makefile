
CC = gcc

MXP_IDIR = -I ../../vbxapi/ 
LDIR     = -L ../../vbxapi/ 

LIBS     = -lvbxapi -lm -lrt

MXP_FLAGS = -mfloat-abi=hard -mfpu=neon


all: chebyshev mibench qspline


chebyshev:
	$(CC)  -O3 $(MXP_IDIR) $(MXP_FLAGS) chebyshev.c -o chebyshev $(LDIR) $(LIBS)


mibench:
	$(CC)  -O3 $(MXP_IDIR) $(MXP_FLAGS) mibench.c -o mibench $(LDIR) $(LIBS)

qspline:
	$(CC)  -O3 $(MXP_IDIR) $(MXP_FLAGS) qspline.c -o qspline $(LDIR) $(LIBS)

clean:
	rm -f chebyshev
	rm -f mibench
	rm -f qspline

