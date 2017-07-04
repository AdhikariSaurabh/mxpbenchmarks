// mibench.c

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
#define ops 15
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
int8_t *x_t = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *y_t = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *z_t = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *res = vbx_shared_malloc(N*M*sizeof(int8_t));
vbx_byte_t *vx = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vy = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vz = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vres = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vtemp = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_dcache_flush_all();

vbx_set_vl(M);
for(i=0;i<M*N;i++){
x_t[i]=1; 
}

for(i=0;i<M*N;i++){
y_t[i]=1; 
}


for(i=0;i<M*N;i++){
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
vbx_dma_to_vector( vx,x_t+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vy,y_t+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vz,z_t+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vres,z_t+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vtemp,y_t+i,M*sizeof(vbx_byte_t));

vbx( SVB,VMUL,vres,6,vres);
vbx( SVB,VADD,vres,43,vres);
// temp = vres = 6*z + 43

vbx( SVB,VMUL,vtemp,2,vtemp);
vbx( VVB,VADD,vtemp,vx,vtemp);
vbx( VVB,VADD,vtemp,vres,vtemp);
vbx( VVB,VMUL,vtemp,vtemp,vx);
//x*(x + 2*y + temp)

vbx( VVB,VADD,vres,vres,vy);
vbx( VVB,VMUL,vres,vres,vy);
// vy = y*(y+temp)

vbx( VVB,VADD,vres,vtemp,vres);
vbx( SVB,VMUL,vtemp,9,vz);
vbx( SVB,VADD,vtemp,1,vtemp);
vbx( VVB,VMUL,vtemp,vtemp,vz);
vbx( VVB,VADD,vres,vtemp,vres);
vbx_dma_to_host(res+i,vres,M*sizeof(vbx_byte_t));
vbx_sync();
}
time_stop = vbx_timestamp();

vbx_shared_free(x_t);
vbx_shared_free(y_t);
vbx_shared_free(z_t);
vbx_timestamp_t cycles = time_stop - time_start;
double seconds = ((double) cycles) / ((double) vbx_timestamp_freq());
printf("Maximum Throughput on MXP for mibench kernel in (Gops/sec) is -> % g Gops/sec\n",(N*M*ops)/(seconds*pow(10,9)));

vbx_shared_free(res);
vbx_sp_free();
return 0;
}

