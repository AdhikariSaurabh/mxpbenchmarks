// mm.c benchmark implemented on the vbx 
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
#define M 512

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

int32_t *i_1 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_3 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_4 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_15 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_5 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_7 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_9 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_18 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_14 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_24 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_19 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_28 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_25 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_34 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_29 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *i_38 = vbx_shared_malloc(N*M*sizeof(int32_t));
int32_t *res = vbx_shared_malloc(N*M*sizeof(int32_t));

vbx_word_t *vi_1 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_3 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_4 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_15 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_5 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_7 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_9 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_18 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_14 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_24 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_19 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_28 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_25 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_34 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_29 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vi_38 = vbx_sp_malloc(M*sizeof(vbx_word_t));


vbx_word_t *vtemp1 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vtemp2 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vtemp3 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vtemp4 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vtemp5 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vtemp6 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vtemp7 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vtemp8 = vbx_sp_malloc(M*sizeof(vbx_word_t));
vbx_word_t *vres = vbx_sp_malloc(M*sizeof(vbx_word_t));

vbx_dcache_flush_all();

vbx_set_vl(M);
for(i=0;i<M*N;i++){
i_1[i]=2;
i_3[i]=2;
i_4[i]=2;
i_15[i]=2;
i_5[i]=2;
i_7[i]=2;
i_9[i]=2;
i_18[i]=2;
i_14[i]=2;
i_24[i]=2;
i_19[i]=2;
i_28[i]=2;
i_25[i]=2;
i_34[i]=2;
i_29[i]=2;
i_38[i]=2;
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
vbx_dma_to_vector( vi_1,i_1+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_3,i_3+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_4,i_4+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_15,i_15+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_5,i_5+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_7,i_7+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_9,i_9+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_18,i_18+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_14,i_14+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_24,i_24+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_19,i_19+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_28,i_28+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_25,i_25+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_34,i_34+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_29,i_29+i,M*sizeof(vbx_word_t));
vbx_dma_to_vector( vi_38,i_38+i,M*sizeof(vbx_word_t));

vbx( VVW,VMUL,vtemp1,vi_1,vi_3);
vbx( VVW,VMUL,vtemp2,vi_4,vi_15);
vbx( VVW,VMUL,vtemp3,vi_5,vi_7);
vbx( VVW,VMUL,vtemp4,vi_9,vi_18);
vbx( VVW,VMUL,vtemp5,vi_14,vi_24);
vbx( VVW,VMUL,vtemp6,vi_19,vi_28);
vbx( VVW,VMUL,vtemp7,vi_25,vi_34);
vbx( VVW,VMUL,vtemp8,vi_29,vi_38);

//int temp_1 = in1 * in3;
//int temp_2 = in4 * in15;
//int temp_3 = in5 * in7;
//int temp_4 = in9 * in18;
//int temp_5 = in14 * in24;
//int temp_6 = in19 * in28;
//int temp_7 = in25 * in34;
//int temp_8 = in29 * in38;

vbx( VVW,VADD,vres,vtemp1,vtemp2);
vbx( VVW,VADD,vres,vres,vtemp3);
vbx( VVW,VADD,vres,vres,vtemp4);
vbx( VVW,VADD,vres,vres,vtemp5);
vbx( VVW,VADD,vres,vres,vtemp6);
vbx( VVW,VADD,vres,vres,vtemp7);
vbx( VVW,VADD,vres,vres,vtemp8);

//temp_1 + temp_2 + temp_3 + temp_4 + temp_5 + temp_6 + temp_7 + temp_8

vbx_dma_to_host(res+i,vres,M*sizeof(vbx_word_t));
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
vbx_shared_free(i_1);
vbx_shared_free(i_3);
vbx_shared_free(i_4);
vbx_shared_free(i_15);
vbx_shared_free(i_5);
vbx_shared_free(i_7);
vbx_shared_free(i_9);
vbx_shared_free(i_18);
vbx_shared_free(i_14);
vbx_shared_free(i_24);
vbx_shared_free(i_19);
vbx_shared_free(i_28);
vbx_shared_free(i_25);
vbx_shared_free(i_34);
vbx_shared_free(i_29);
vbx_shared_free(i_38);
vbx_shared_free(res);
vbx_sp_free();
return 0;
}
