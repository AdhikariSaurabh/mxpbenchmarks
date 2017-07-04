//fft 

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
#define ops 10
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
int8_t *o_0 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *o_1 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *o_2 = vbx_shared_malloc(N*M*sizeof(int8_t));
int8_t *o_3 = vbx_shared_malloc(N*M*sizeof(int8_t));

vbx_byte_t *vi_0 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_1 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_2 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_3 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_4 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vi_5 = vbx_sp_malloc(M*sizeof(vbx_byte_t));

vbx_byte_t *vo_0 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vo_1 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vo_2 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vo_3 = vbx_sp_malloc(M*sizeof(vbx_byte_t));

vbx_byte_t *vtemp1 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vtemp2 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vtemp3 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vtemp4 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_dcache_flush_all();

vbx_set_vl(M);
for(i=0;i<M*N;i++){
i_0[i]=3;
}

for(i=0;i<M*N;i++){
i_1[i]=3;
}

for(i=0;i<M*N;i++){
i_2[i]=3;
}

for(i=0;i<M*N;i++){
i_3[i]=3;
}

for(i=0;i<M*N;i++){
i_4[i]=3;
}

for(i=0;i<M*N;i++){
i_5[i]=3;
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

vbx( VVB,VMUL,vtemp1,vi_1,vi_2);
vbx( VVB,VMUL,vtemp2,vi_3,vi_4);
vbx( VVB,VADD,vtemp1,vtemp1,vtemp2);

// int temp_1 = i[1]*i[2] + i[3]*i[4]

vbx( VVB,VMUL,vtemp3,vi_1,vi_4);
vbx( VVB,VMUL,vtemp4,vi_3,vi_2);
vbx( VVB,VSUB,vtemp3,vtemp3,vtemp4);

//int temp_1 = i[1]*i[2] + i[3]*i[4]


vbx( VVB,VSUB,vo_0,vi_0,vtemp1);
vbx( VVB,VADD,vo_1,vi_0,vtemp1);
vbx( VVB,VSUB,vo_2,vi_5,vtemp3);
vbx( VVB,VADD,vo_3,vi_5,vtemp3);
//o[0] = i[0] - temp_1        
//o[1] = i[0] + temp_1        
//o[2] = i[5] - temp_3       
//o[3] = i[5] + temp_3

//The result can be stored in the unused input space rather than creating new 
//space for the outputs and then can be transferred to the main memory 

//i[1] = i[0] - temp_1        
//i[2] = i[0] + temp_1        
//i[3] = i[5] - temp_3       
//i[4] = i[5] + temp_3

//vbx_dma_to_host(o_0+i,vi_1,M*sizeof(vbx_byte_t));
//vbx_dma_to_host(o_1+i,vi_2,M*sizeof(vbx_byte_t));
//vbx_dma_to_host(o_2+i,vi_3,M*sizeof(vbx_byte_t));
//vbx_dma_to_host(o_3+i,vi_4,M*sizeof(vbx_byte_t));

//The same input vector can be used to store the output at last or separate 
//vectors can be taken

vbx_dma_to_host(o_0+i,vo_0,M*sizeof(vbx_byte_t));
vbx_dma_to_host(o_1+i,vo_1,M*sizeof(vbx_byte_t));
vbx_dma_to_host(o_2+i,vo_2,M*sizeof(vbx_byte_t));
vbx_dma_to_host(o_3+i,vo_3,M*sizeof(vbx_byte_t));
vbx_sync();
}
time_stop = vbx_timestamp();
/*
for(i=0;i<N*M;i++){

printf("The sample is: %d\n",o_0[i]);
printf("The sample is: %d\n",o_1[i]);
printf("The sample is: %d\n",o_2[i]);
printf("The sample is: %d\n",o_3[i]);
}
*/
vbx_timestamp_t cycles = time_stop - time_start;
double seconds = ((double) cycles) / ((double) vbx_timestamp_freq());
printf("Maximum Throughput on MXP for fft kernel in (Gops/sec) is -> %g Gops/sec\n",(N*M*ops)/(seconds*pow(10,9))); 

vbx_shared_free(i_0);
vbx_shared_free(i_1);
vbx_shared_free(i_2);
vbx_shared_free(i_3);
vbx_shared_free(i_4);
vbx_shared_free(i_5);
vbx_shared_free(o_0);
vbx_shared_free(o_1);
vbx_shared_free(o_2);
vbx_shared_free(o_3);
vbx_sp_free();
return 0;
}
