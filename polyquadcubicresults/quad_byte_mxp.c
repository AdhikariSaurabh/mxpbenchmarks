#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <errno.h>
#include <math.h>
#include "vbx.h"
#include "vbx_port.h"
#include "vbx_common.h"
#include "vectorblox_mxp_lin.h"
#define N 256
#define M 65536
#define ops 5
#define MXP

uint32_t i;

// kernel compute prototype have 4 arguments 
// Two for the host pointers and rest for specifying the Datasize
void kernel_poly2(int8_t **, int8_t **, int, int);

void kernel_poly2(int8_t **X, int8_t **Y, int nx, int ny)
{
int8_t a = 2;
int8_t b = 2;
int8_t c = 2;
int8_t *sc_X = *X;
int8_t *sc_Y = *Y;
vbx_timestamp_t time_start,time_stop;
vbx_dcache_flush_all(); // not required since using the uncached region 

// Allocating the space in scratchpad
vbx_byte_t *vx = vbx_sp_malloc( ny*sizeof(vbx_byte_t));
vbx_byte_t *vy = vbx_sp_malloc( ny*sizeof(vbx_byte_t));
vbx_byte_t *vara = vbx_sp_malloc( ny*sizeof(vbx_byte_t));

// setting the vector length
vbx_set_vl(ny);
vbx_timestamp_start();
time_start = vbx_timestamp();
for(i=0;i<M*N;i=i+M){
vbx_dma_to_vector( vx, sc_X+i,ny*sizeof(vbx_byte_t));
vbx( SVB,VMUL,vy,a,vx);
vbx( VVB,VMUL,vy,vy,vx);
vbx( SVB,VMUL,vara,b,vx);
vbx( VVB,VADD,vy,vy,vara );
vbx( SVB,VADD,vy,c,vy);
vbx_dma_to_host( sc_Y+i, vy,ny*sizeof(vbx_byte_t));
vbx_sync();
}
time_stop = vbx_timestamp();
vbx_timestamp_t cycles = time_stop - time_start;
double seconds = ((double) cycles) / ((double) vbx_timestamp_freq());

printf("Maximum Throughput for Poly2 kernel on MXP in (Gops/sec) is -> %g Gops/sec\n",(nx*ny*ops)/(seconds*pow(10,9)));
vbx_sp_free();
vbx_shared_free(sc_X);
vbx_shared_free(sc_Y);
}

int main(int argc, char *argv[])
{

 #ifdef MXP
 VectorBlox_MXP_Initialize("mxp0","cma");
 //vbx_mxp_print_params();
 #else
 printf("MXP Disabled, APP is running entirely on ARM\n");
 #endif
 int8_t *X, *Y;
 // Retrieving the Datasize to be computed using the Kernel
 int nx = N;
 int ny = M;
 X=vbx_shared_malloc(nx*ny*sizeof(int8_t));
 Y=vbx_shared_malloc(nx*ny*sizeof(int8_t));

 for(i=0;i<nx*ny;i++){
 X[i]=1;
 Y[i]=0;
  }
 kernel_poly2(&X,&Y,nx,ny);
  return 0;
}
