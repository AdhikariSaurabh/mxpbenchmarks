//stencil 

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
#define ops 14
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
int8_t *i_0 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_1 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_2 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_3 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_4 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_5 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_6 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_7 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_8 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_9 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_10 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_11 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_12 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_13 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *i_15 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *o_0 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *o_1 = vbx_shared_malloc(N*M*sizeof(int8_t));

vbx_byte_t *vi_0 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_1 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_2 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_3 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_4 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_5 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_6 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_7 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_8 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_9 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_10 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_11 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_12 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_13 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_15 = vbx_sp_malloc(M*sizeof(vbx_byte_t));

vbx_byte_t *vo_0 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vo_1 = vbx_sp_malloc(M*sizeof(vbx_byte_t));

vbx_dcache_flush_all();

vbx_set_vl(M);
for(i=0;i<M*N;i++){
i_0[i]=2;
}

for(i=0;i<M*N;i++){
i_1[i]=2;
}

for(i=0;i<M*N;i++){
i_2[i]=2;
}

for(i=0;i<M*N;i++){
i_3[i]=2;
}

for(i=0;i<M*N;i++){
i_4[i]=2;
}

for(i=0;i<M*N;i++){
i_5[i]=2;
}

for(i=0;i<M*N;i++){
i_6[i]=2;
}


for(i=0;i<M*N;i++){
i_7[i]=2;
}


for(i=0;i<M*N;i++){
i_8[i]=2;
}


for(i=0;i<M*N;i++){
i_9[i]=2;
}

for(i=0;i<M*N;i++){
i_10[i]=2;
}


for(i=0;i<M*N;i++){
i_11[i]=2;
}

for(i=0;i<M*N;i++){
i_12[i]=2;
}


for(i=0;i<M*N;i++){
i_13[i]=2;
}

for(i=0;i<M*N;i++){
i_15[i]=2;
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
vbx_dma_to_vector( vi_0,i_0+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_1,i_1+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_2,i_2+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_3,i_3+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_4,i_4+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_5,i_5+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_6,i_6+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_7,i_7+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_8,i_8+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_9,i_9+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_10,i_10+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_11,i_11+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_12,i_12+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_13,i_13+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vi_15,i_15+i,M*sizeof(vbx_byte_t));

vbx( VVB,VADD,vo_0,vi_0,vi_1);
vbx( VVB,VADD,vo_0,vo_0,vi_2);
vbx( VVB,VADD,vo_0,vo_0,vi_3);
vbx( VVB,VADD,vo_0,vo_0,vi_4);
vbx( VVB,VADD,vo_0,vo_0,vi_3);
vbx( VVB,VMUL,vo_0,vo_0,vi_6);
vbx( VVB,VSUB,vo_0,vo_0,vi_7);

vbx( VVB,VADD,vo_1,vi_8,vi_9);
vbx( VVB,VADD,vo_1,vo_1,vi_10);
vbx( VVB,VADD,vo_1,vo_1,vi_11);
vbx( VVB,VADD,vo_1,vo_1,vi_12);
vbx( VVB,VADD,vo_1,vo_1,vi_13);
vbx( VVB,VMUL,vo_1,vo_1,vi_6);
vbx( VVB,VSUB,vo_1,vo_1,vi_15);


vbx_dma_to_host(o_0+i,vo_0,M*sizeof(vbx_byte_t));
vbx_dma_to_host(o_1+i,vo_1,M*sizeof(vbx_byte_t));
vbx_sync();
}
time_stop = vbx_timestamp();
vbx_timestamp_t cycles = time_stop - time_start;
double seconds = ((double) cycles) / ((double) vbx_timestamp_freq());
printf("Maximum Throughput on MXP for stencil kernel in (Gops/sec) is -> %g Gops/sec\n",(N*M*ops)/(seconds*pow(10,9))); 

vbx_shared_free(i_0);
vbx_shared_free(i_1);
vbx_shared_free(i_2);
vbx_shared_free(i_3);
vbx_shared_free(i_4);
vbx_shared_free(i_5);
vbx_shared_free(i_6);
vbx_shared_free(i_7);
vbx_shared_free(i_8);
vbx_shared_free(i_9);
vbx_shared_free(i_10);
vbx_shared_free(i_11);
vbx_shared_free(i_12);
vbx_shared_free(i_13);
vbx_shared_free(i_15);

vbx_shared_free(o_0);
vbx_shared_free(o_1);
vbx_sp_free();
return 0;
}
