//bicg.c benchmark implemented on the vbx 
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
#define M 1

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
int32_t *A_8 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *p_0 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *p_1 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *p_2 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *q_0 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *q_1 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *q_2 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *r_0 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *r_1 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *r_2 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *s_0 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *s_1 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *s_2 = vbx_shared_malloc(N*M*sizeof(int32_t));

vbx_word_t *vA_0 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_1 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_2 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_3 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_4 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_5 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_6 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_7 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vA_8 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vq_0 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vq_1 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vq_2 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vp_0 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vp_1 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vp_2 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vr_0 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vr_1 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vr_2 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vs_0 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vs_1 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vs_2 = vbx_sp_malloc(M*sizeof(vbx_word_t));

//vbx_word_t *vtemp1 = vbx_sp_malloc(M*sizeof(vbx_word_t));
//vbx_word_t *vtemp2 = vbx_sp_malloc(M*sizeof(vbx_word_t));
//vbx_word_t *vtemp3 = vbx_sp_malloc(M*sizeof(vbx_word_t));
//vbx_word_t *vtemp4 = vbx_sp_malloc(M*sizeof(vbx_word_t));
//vbx_word_t *vtemp5 = vbx_sp_malloc(M*sizeof(vbx_word_t));


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
A_8[i]=2;
p_0[i]=2;
p_1[i]=2;
p_2[i]=2;
r_0[i]=2;
r_1[i]=2;
r_2[i]=2;
}


/*
for(i=0;i<M*N;i++){
printf("%d |",x_t[i]);
}
printf("\n");
*/

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
vbx_dma_to_vector( vA_8,A_8+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vr_0,r_0+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vr_1,r_1+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vr_2,r_2+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vp_0,p_0+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vp_1,p_1+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vp_2,p_2+i,M*sizeof(vbx_word_t));

vbx( VVW,VMUL,vs_0,vA_0,vp_0);
vbx( VVW,VMUL,vs_1,vA_1,vp_1);
vbx( VVW,VMUL,vs_2,vA_2,vp_2);
vbx( VVW,VADD,vs_2,vs_1,vs_2);
vbx( VVW,VADD,vq_0,vs_2,vs_0);

vbx( VVW,VMUL,vs_0,vA_3,vp_0);
vbx( VVW,VMUL,vs_1,vA_4,vp_1);
vbx( VVW,VMUL,vs_2,vA_5,vp_2);
vbx( VVW,VADD,vs_2,vs_1,vs_2);
vbx( VVW,VADD,vq_1,vs_2,vs_0);

vbx( VVW,VMUL,vs_0,vA_6,vp_0);
vbx( VVW,VMUL,vs_1,vA_7,vp_1);
vbx( VVW,VMUL,vs_2,vA_8,vp_2);
vbx( VVW,VADD,vs_2,vs_1,vs_2);
vbx( VVW,VADD,vq_2,vs_2,vs_0);

 //q[0] = A[0] * p[0] + A[1] * p[1] + A[2] * p[2];
   //     q[1] = A[3] * p[0] + A[4] * p[1] + A[5] * p[2];
    //    q[2] = A[6] * p[0] + A[7] * p[1] + A[8] * p[2];

vbx( VVW,VMUL,vp_0,vA_0,vr_0);
vbx( VVW,VMUL,vp_1,vA_3,vr_1);
vbx( VVW,VMUL,vp_2,vA_6,vr_2);
vbx( VVW,VADD,vp_2,vp_1,vp_2);
vbx( VVW,VADD,vs_0,vp_2,vp_0);

vbx( VVW,VMUL,vp_0,vA_1,vr_0);
vbx( VVW,VMUL,vp_1,vA_4,vr_1);
vbx( VVW,VMUL,vp_2,vA_7,vr_2);
vbx( VVW,VADD,vp_2,vp_1,vp_2);
vbx( VVW,VADD,vs_1,vp_2,vp_0);

vbx( VVW,VMUL,vp_0,vA_2,vr_0);
vbx( VVW,VMUL,vp_1,vA_5,vr_1);
vbx( VVW,VMUL,vp_2,vA_8,vr_2);
vbx( VVW,VADD,vp_2,vp_1,vp_2);
vbx( VVW,VADD,vs_2,vp_2,vp_0);

 //s[0] = A[0] * r[0] + A[3] * r[1] + A[6] * r[2];
 //       s[1] = A[1] * r[0] + A[4] * r[1] + A[7] * r[2];
 //       s[2] = A[2] * r[0] + A[5] * r[1] + A[8] * r[2];
vbx_dma_to_host(s_0+i,vs_0,M*sizeof(vbx_word_t));
vbx_dma_to_host(s_1+i,vs_1,M*sizeof(vbx_word_t));
vbx_dma_to_host(s_2+i,vs_2,M*sizeof(vbx_word_t));
vbx_sync();
}
time_stop = vbx_timestamp();
/*
for(i=0;i<N*M;i++){
printf("The %d sample is: %d\n",i+1,res[i]);
}
*/
printf("The sample is: %d\n",s_0[0]);
printf("The sample is: %d\n",s_1[0]);
printf("The sample is: %d\n",s_2[0]);

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
vbx_shared_free(A_8);
vbx_shared_free(p_0);
vbx_shared_free(p_1);
vbx_shared_free(p_2);
vbx_shared_free(s_0);
vbx_shared_free(s_1);
vbx_shared_free(s_2);
vbx_shared_free(r_0);
vbx_shared_free(r_1);
vbx_shared_free(r_2);
vbx_shared_free(q_0);
vbx_shared_free(q_1);
vbx_shared_free(q_2);
vbx_sp_free();
return 0;
}

