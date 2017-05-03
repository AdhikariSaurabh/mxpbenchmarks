// sgfilter.c
// This is the filter for the byte becoming inconsistent as the result of the benchmark exceeding the data type limit
// Refer to the kernel_benchmarks.png for the DAG expression of the Kernel benchmark( Snap taken from Dr Abhishek Kumar Jain Throughput Oriented FPGA Overlays Using DSP Blocks thesis) 

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
#define N 4096
#define M 8192
#define MXP

int main(){
#ifdef MXP
    VectorBlox_MXP_Initialize("mxp0","cma");
#else
    printf("MXP Disabled, APP is running entirely on ARM\n");
#endif
vbx_mxp_print_params();
vbx_timestamp_t time_start,time_stop;

double seconds;
int32_t i;
int16_t *x_t = vbx_shared_malloc(N*M*sizeof(int16_t));
int16_t *y_t = vbx_shared_malloc(N*M*sizeof(int16_t));
int16_t *res = vbx_shared_malloc(N*M*sizeof(int16_t));

vbx_half_t *vx = vbx_sp_malloc(M*sizeof(vbx_half_t));
vbx_half_t *vy = vbx_sp_malloc(M*sizeof(vbx_half_t));
vbx_half_t *vtemp = vbx_sp_malloc(M*sizeof(vbx_half_t));
vbx_half_t *vres = vbx_sp_malloc(M*sizeof(vbx_half_t));
vbx_dcache_flush_all();
vbx_set_vl(M);
for(i=0;i<M*N;i++){
x_t[i]=1;
y_t[i]=1;
}

/*
for(i=0;i<M*N;i++){
printf("%d |",x_t[i]);
}
printf("\n");
*/
vbx_timestamp_start();
time_start = vbx_timestamp();
for(i=0;i<M*N;i=i+M){
vbx_dma_to_vector( vx,x_t+i,M*sizeof(vbx_half_t));
vbx_dma_to_vector( vy,y_t+i,M*sizeof(vbx_half_t));
vbx_dma_to_vector( vtemp,x_t+i,M*sizeof(vbx_half_t));

vbx( SVH,VMUL,vtemp,7,vx);
vbx( SVH,VMUL,vres,-76,vy);
vbx( SVH,VADD,vtemp,7,vtemp);
vbx( VVH,VADD,vtemp,vres,vtemp);
vbx( VVH,VMUL,vtemp,vtemp,vx);

//x*(7*x - 76*y +7)

vbx( SVH,VMUL,vres,92,vy);
vbx( SVH,VADD,vres,-39,vres);
vbx( VVH,VMUL,vres,vres,vy );
vbx( SVH,VADD,vres,7,vres);
vbx( VVH,VADD,vres,vtemp,vres );
vbx( VVH,VMUL,vres,vres,vx);

//x*(x*(7*x - 76*y +7) + y*(92*y - 39) +7)

vbx( SVH,VMUL,vtemp,984,vy);
vbx( SVH,VADD,vtemp,46,vtemp);
vbx( VVH,VMUL,vtemp,vtemp,vy);
vbx( SVH,VADD,vtemp,46,vtemp);
vbx( VVH,VMUL,vtemp,vy,vtemp);

//y*(y*(984*y + 46) + 46)

vbx( SVH,VADD,vtemp,75,vtemp);

// y*(y*(984*y + 46) + 46) +75)

// mind we have taken -ve outside for our implementation
vbx( VVH,VSUB,vres,vres,vtemp);
vbx_dma_to_host(res+i,vres,M*sizeof(vbx_half_t));

vbx_sync();
}
time_stop = vbx_timestamp();
/*
for(i=0;i<N*M;i++){
printf("The %d sample is: %d\n",i+1,res[i]);
}
*/

printf("The sample is: %d %d\n",res[0],res[1]);

seconds=vbx_print_scalar_time( time_start, time_stop );
printf("Took timer ticks -> %g s\n" , seconds);
vbx_shared_free(x_t);
vbx_shared_free(y_t);
vbx_shared_free(res);
vbx_sp_free();
return 0;
}
