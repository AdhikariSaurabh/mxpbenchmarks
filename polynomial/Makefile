// polynomial on the MXP Vectorblox


CC = gcc

IDIR = -I../../../../repository/lib/vbxapi 
LDIR = -L../../../../repository/lib/vbxapi -L../../lib/libfixmath -L../../lib/scalar -L../../lib/vbxtest -L../../lib/vbxware -L../../lib/vbxware++ 
LIBS = -lvbxapi -lfixmath -lscalar -lvbxtest -lvbxware -lm -lrt

CFLAGS = -mfloat-abi=hard -mfpu=neon

SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c 
	$(CC) $(IDIR) $(CFLAGS) -o $@ $< $(LDIR) $(LIBS)

 
