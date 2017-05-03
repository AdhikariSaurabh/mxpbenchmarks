//conv.c benchmark implemented on the vbx 

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
#define N 1
#define M 1024

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


int32_t *A_0 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *A_1 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *A_2 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *A_3 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *A_4 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *A_5 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *A_6 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *A_7 = vbx_shared_malloc(N*M*sizeof(int32_t));

int32_t *B_0 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *B_1 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *B_2 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *B_3 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *B_4 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *B_5 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *B_6 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *B_7 = vbx_shared_malloc(N*M*sizeof(int32_t));


int32_t *C_0 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *C_1 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *C_2 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *C_3 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *C_4 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *C_5 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *C_6 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *C_7 = vbx_shared_malloc(N*M*sizeof(int32_t));


int32_t *o_0 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *o_1 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *o_2 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *o_3 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *o_4 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *o_5 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *o_6 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *o_7 = vbx_shared_malloc(N*M*sizeof(int32_t));


vbx_word_t *vA_0 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_1 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_2 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_3 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_4 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_5 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_6 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_7 = vbx_sp_malloc(M*sizeof(vbx_word_t));


vbx_word_t *vB_0 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vB_1 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vB_2 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vB_3 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vB_4 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vB_5 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vB_6 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vB_7 = vbx_sp_malloc(M*sizeof(vbx_word_t));


vbx_word_t *vC_0 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vC_1 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vC_2 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vC_3 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vC_4 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vC_5 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vC_6 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vC_7 = vbx_sp_malloc(M*sizeof(vbx_word_t));

vbx_word_t *vo_0 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vo_1 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vo_2 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vo_3 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vo_4 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vo_5 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vo_6 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vo_7 = vbx_sp_malloc(M*sizeof(vbx_word_t));


vbx_dcache_flush_all();

vbx_set_vl(M);

for(i=0;i<M*N;i++){
A_0[i]=2;
A_1[i]=2;
A_2[i]=2;
A_3[i]=2;
A_4[i]=2;
A_5[i]=2;
A_6[i]=2;
A_7[i]=2;
B_0[i]=2;
B_1[i]=2;
B_2[i]=2;
B_3[i]=2;
B_4[i]=2;
B_5[i]=2;
B_6[i]=2;
B_7[i]=2;
C_0[i]=2;
C_1[i]=2;
C_2[i]=2;
C_3[i]=2;
C_4[i]=2;
C_5[i]=2;
C_6[i]=2;
C_7[i]=2;

}


vbx_timestamp_start();
time_start = vbx_timestamp();
for(i=0;i<M*N;i=i+M)
{
vbx_dma_to_vector( vA_0,A_0+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vA_1,A_1+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vA_2,A_2+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vA_3,A_3+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vA_4,A_4+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vA_5,A_5+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vA_6,A_6+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vA_7,A_7+i,M*sizeof(vbx_word_t));


vbx_dma_to_vector( vB_0,B_0+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vB_1,B_1+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vB_2,B_2+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vB_3,B_3+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vB_4,B_4+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vB_5,B_5+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vB_6,B_6+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vB_7,B_7+i,M*sizeof(vbx_word_t));


vbx_dma_to_vector( vC_0,C_0+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vC_1,C_1+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vC_2,C_2+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vC_3,C_3+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vC_4,C_4+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vC_5,C_5+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vC_6,C_6+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vC_7,C_7+i,M*sizeof(vbx_word_t));


vbx( VVW,VMUL,vB_0,vB_0,vC_0);
vbx( VVW,VADD,vo_0,vA_0,vB_0);

vbx( VVW,VMUL,vB_1,vB_1,vC_1);
vbx( VVW,VADD,vo_1,vA_1,vB_1);

vbx( VVW,VMUL,vB_2,vB_2,vC_2);
vbx( VVW,VADD,vo_2,vA_2,vB_2);

vbx( VVW,VMUL,vB_3,vB_3,vC_3);
vbx( VVW,VADD,vo_3,vA_3,vB_3);

vbx( VVW,VMUL,vB_4,vB_4,vC_4);
vbx( VVW,VADD,vo_4,vA_4,vB_4);

vbx( VVW,VMUL,vB_5,vB_5,vC_5);
vbx( VVW,VADD,vo_5,vA_5,vB_5);

vbx( VVW,VMUL,vB_6,vB_6,vC_6);
vbx( VVW,VADD,vo_6,vA_6,vB_6);

vbx( VVW,VMUL,vB_7,vB_7,vC_7);
vbx( VVW,VADD,vo_7,vA_7,vB_7);

vbx_dma_to_host(o_0+i,vo_0,M*sizeof(vbx_word_t));
vbx_dma_to_host(o_1+i,vo_1,M*sizeof(vbx_word_t));
vbx_dma_to_host(o_2+i,vo_2,M*sizeof(vbx_word_t));
vbx_dma_to_host(o_3+i,vo_3,M*sizeof(vbx_word_t));
vbx_dma_to_host(o_4+i,vo_4,M*sizeof(vbx_word_t));
vbx_dma_to_host(o_5+i,vo_5,M*sizeof(vbx_word_t));
vbx_dma_to_host(o_6+i,vo_6,M*sizeof(vbx_word_t));
vbx_dma_to_host(o_7+i,vo_7,M*sizeof(vbx_word_t));

vbx_sync();
}
time_stop = vbx_timestamp();
/*
for(i=0;i<N*M;i++){
printf("The %d sample is: %d\n",i+1,res[i]);
}
*/
printf("The sample is: %d\n",o_0[0]);
printf("The sample is: %d\n",o_1[0]);
printf("The sample is: %d\n",o_2[0]);
printf("The sample is: %d\n",o_3[0]);
printf("The sample is: %d\n",o_4[0]);
printf("The sample is: %d\n",o_5[0]);
printf("The sample is: %d\n",o_6[0]);
printf("The sample is: %d\n",o_7[0]);

seconds=vbx_print_scalar_time( time_start, time_stop );
printf("Took timer ticks -> %g s\n" , seconds);
vbx_shared_free(A_0);
vbx_shared_free(A_1);
vbx_shared_free(A_2);
vbx_shared_free(A_3);
vbx_shared_free(A_4);
vbx_shared_free(A_5);
vbx_shared_free(A_6);
vbx_shared_free(A_7);


vbx_shared_free(B_0);
vbx_shared_free(B_1);
vbx_shared_free(B_2);
vbx_shared_free(B_3);
vbx_shared_free(B_4);
vbx_shared_free(B_5);
vbx_shared_free(B_6);
vbx_shared_free(B_7);


vbx_shared_free(C_0);
vbx_shared_free(C_1);
vbx_shared_free(C_2);
vbx_shared_free(C_3);
vbx_shared_free(C_4);
vbx_shared_free(C_5);
vbx_shared_free(C_6);
vbx_shared_free(C_7);

vbx_shared_free(o_0);
vbx_shared_free(o_1);
vbx_shared_free(o_2);
vbx_shared_free(o_3);
vbx_shared_free(o_4);
vbx_shared_free(o_5);
vbx_shared_free(o_6);
vbx_shared_free(o_7);

vbx_sp_free();
return 0;
}

