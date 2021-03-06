// mibench.c benchmark on mxp
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
#define N 256
#define M 4096 
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
int32_t *x_t = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *y_t = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *z_t = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *res = vbx_shared_malloc(N*M*sizeof(int32_t));
vbx_word_t *vx = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vy = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vz = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vres = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vtemp = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_dcache_flush_all();

vbx_set_vl(M);
for(i=0;i<M*N;i++){
x_t[i]=1;
y_t[i]=1;
z_t[i]=1;
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
vbx_dma_to_vector( vx,x_t+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vy,y_t+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vz,z_t+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vres,z_t+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vtemp,y_t+i,M*sizeof(vbx_word_t));

vbx( SVW,VMUL,vres,6,vres);
vbx( SVW,VADD,vres,43,vres);
// temp = vres = 6*z + 43

vbx( SVW,VMUL,vtemp,2,vtemp);
vbx( VVW,VADD,vtemp,vx,vtemp);
vbx( VVW,VADD,vtemp,vres,vtemp);
vbx( VVW,VMUL,vtemp,vtemp,vx);
//x*(x + 2*y + temp)

vbx( VVW,VADD,vres,vres,vy);
vbx( VVW,VMUL,vres,vres,vy);
// vy = y*(y+temp)

vbx( VVW,VADD,vres,vtemp,vres);
vbx( SVW,VMUL,vtemp,9,vz);
vbx( SVW,VADD,vtemp,1,vtemp);
vbx( VVW,VMUL,vtemp,vtemp,vz);
vbx( VVW,VADD,vres,vtemp,vres);
vbx_dma_to_host(res+i,vres,M*sizeof(vbx_word_t));
vbx_sync();
}
time_stop = vbx_timestamp();
/*
for(i=0;i<N*M;i++){
printf("The %d sample is: %d\n",i+1,res[i]);
}
*/
printf("The sample is: %d\n",res[0]);

seconds=vbx_print_scalar_time( time_start, time_stop );
printf("Took timer ticks -> %g s\n" , seconds);
vbx_shared_free(x_t);
vbx_shared_free(y_t);
vbx_shared_free(z_t);
vbx_shared_free(res);

vbx_sp_free();
return 0;
}
