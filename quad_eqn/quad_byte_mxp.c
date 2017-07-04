
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
int main()
{

#ifdef MXP
    VectorBlox_MXP_Initialize("mxp0","cma");
#else
    printf("MXP Disabled, APP is running entirely on ARM\n");
#endif
vbx_mxp_print_params();
vbx_timestamp_t time_start,time_stop;
uint32_t i;
uint8_t *X;
uint8_t *Y;

X=vbx_shared_malloc(N*M*sizeof(int8_t));
for(i=0;i<M*N;i++){
X[i]=1;
}

Y=vbx_shared_malloc(N*M*sizeof(int8_t) );
for(i=0;i<M*N;i++){
Y[i]=0;
}

uint8_t a = 2;
uint8_t b = 2;
uint8_t c = 2;

vbx_dcache_flush_all(); // not required since using the uncached region 
// Allocating the space in scratchpad
vbx_byte_t *vx = vbx_sp_malloc( M*sizeof(vbx_byte_t));
vbx_byte_t *vy = vbx_sp_malloc( M*sizeof(vbx_byte_t));
vbx_byte_t *vara = vbx_sp_malloc( M*sizeof(vbx_byte_t));

//Transfer from the main memory to sp
//vbx_dma_to_vector( vy, Y, num_bytes );
// setting the vector length

vbx_set_vl( M );
vbx_timestamp_start();
//freq = vbx_timestamp_freq();
time_start = vbx_timestamp();

for(i=0;i<M*N;i=i+M){
vbx_dma_to_vector( vx, X+i,M*sizeof(vbx_byte_t));
vbx( SVB,VMUL,vy,a,vx);
vbx( VVB,VMUL,vy,vy,vx);
vbx( SVB,VMUL,vara,b,vx);
vbx( VVB,VADD,vy,vy,vara );
vbx( SVB,VADD,vy,c,vy);
vbx_dma_to_host( Y+i, vy,M*sizeof(vbx_byte_t));
vbx_sync();
}

time_stop = vbx_timestamp();
vbx_timestamp_t cycles = time_stop - time_start;
double seconds = ((double) cycles) / ((double) vbx_timestamp_freq());
seconds=vbx_print_scalar_time( time_start, time_stop );
printf("Maximum Throughput by MXP for Poly2(Quad) in (Gops/sec) is -> %g Gops/sec\n",(N*M*ops)/(seconds*pow(10,9)));

vbx_sp_free();
vbx_shared_free(X);
vbx_shared_free(Y);
return 0;
}
	
