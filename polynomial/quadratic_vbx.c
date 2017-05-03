// Quadratic equation on mxp 

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
#include "vbx_test.h"
#include "vbx_types.h"
#include "vectorblox_mxp_lin.h"
#define N 2048
#define M 32768                                                                 
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

double seconds;
uint32_t i;

uint8_t *X;
X=vbx_shared_malloc(N*M*sizeof(char));
for(i=0;i<M*N;i++){
X[i]=1;
}

uint8_t *Y;
Y=vbx_shared_malloc(N*M*sizeof(char) );
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
vbx_byte_t *vara;
//Transfer from the main memory to sp
//vbx_dma_to_vector( vy, Y, num_bytes );
// setting the vector length

vbx_timestamp_start();

time_start = vbx_timestamp();
vbx_set_vl( M );
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
seconds=vbx_print_scalar_time( time_start, time_stop );
//for(i=0;i<N*M;i++){
//printf("The %d sample is: %d\n",i+1,Y[i]);
//}
// Print the results
printf("Took timer ticks -> %g s\n" , seconds);
vbx_sp_free();
vbx_shared_free(X);
vbx_shared_free(Y);
return 0;
}
