// chebyshev.c

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
//#include "vbx_test.h"
//#include "vbx_types.h"
#include "vectorblox_mxp_lin.h"
#define N 256
#define M 16384
#define ops 7
#define MXP

int main(){
#ifdef MXP
    VectorBlox_MXP_Initialize("mxp0","cma");
#else
    printf("MXP Disabled, APP is running entirely on ARM\n");
#endif
vbx_mxp_print_params();
vbx_timestamp_t time_start,time_stop;

int32_t i;
int8_t *x_t = vbx_shared_malloc(M*N*sizeof(int8_t));
vbx_byte_t *vx = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vres = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_dcache_flush_all();
vbx_set_vl(M);
for(i=0;i<M*N;i++){
x_t[i]=2;
}
vbx_timestamp_start();
time_start = vbx_timestamp();
for(i=0;i<M*N;i=i+M){
vbx_dma_to_vector( vx,x_t+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vres,x_t+i,M*sizeof(vbx_byte_t));

vbx( SVB,VMUL,vres,16,vres); 
vbx( VVB,VMUL,vres,vx,vres);
vbx( SVB,VADD,vres,-20,vres);
//temp*x-20

vbx( VVB,VMUL,vres,vx,vres);
vbx( VVB,VMUL,vres,vx,vres);
//x*(temp*x-20)*x

vbx( SVB,VADD,vres,5,vres);
//x*(temp*x-20)*x+5

vbx( VVB,VMUL,vres,vx,vres );
//(x*(x*(temp*x-20)*x+5))
vbx_dma_to_host(x_t+i,vres,M*sizeof(vbx_byte_t));
vbx_sync();
}
time_stop = vbx_timestamp();
/*
for(i=0;i<N*M;i++){
printf("The %d sample is: %d\n",i+1,x_t[i]);
}
*/
//double seconds=vbx_print_scalar_time( time_start, time_stop );
vbx_timestamp_t cycles = time_stop - time_start;
double seconds = ((double) cycles) / ((double) vbx_timestamp_freq());
printf("Maximum Throughput on MXP for chebyshev kernel in (Gops/sec) is -> %g Gops/sec\n",(N*M*ops)/(seconds*pow(10,9)));
vbx_shared_free(x_t);
vbx_sp_free();
return 0;
}

