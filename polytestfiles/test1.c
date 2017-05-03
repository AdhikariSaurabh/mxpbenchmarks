
// byte
// ax
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
#define N 3
#define M 65536
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
//const float ms_per_sec = 1000.0;
//unsigned freq;
double seconds;
uint32_t i;
//uint32_t num_bytes = vector_len * sizeof(int);
uint8_t *X;
X=vbx_shared_malloc(N*M*sizeof(char));
for(i=0;i<M*N;i++){
X[i]=1;
}

uint8_t *Y;
Y=vbx_shared_malloc(N*M*sizeof(char));
//for(i=0;i<M*N;i++){
//printf("%d |",X[i]);
//}
//printf("\n");
//for(i=0;i<M*N;i++){
//printf("%d |",Y[i]);
//}
//printf("\n");
uint8_t a = 2;
vbx_dcache_flush_all(); // not required since using the uncached region 
// Allocating the space in scratchpad
vbx_byte_t *vx = vbx_sp_malloc( M*sizeof(vbx_byte_t));
//Transfer from the main memory to sp
//vbx_dma_to_vector( vy, Y, num_bytes );
// setting the vector length
//start=clock();
vbx_timestamp_start();
//freq = vbx_timestamp_freq();
time_start = vbx_timestamp();
//milliseconds1 = (float)(start)* ms_per_sec/ freq;
//printf("Took timer1 ticks -> %f ms\n" , milliseconds1);
vbx_set_vl( M );
for(i=0;i<M*N;i=i+M){
vbx_dma_to_vector( vx, X+i,M*sizeof(vbx_byte_t));
vbx( SVB,VMUL,vx,a,vx);
vbx_dma_to_host( Y+i, vx,M*sizeof(vbx_byte_t));
vbx_sync();
}
//diff = clock()-start;
//milliseconds = (double)(diff)*1000 / CLOCKS_PER_SEC;
time_stop = vbx_timestamp();
//milliseconds2 = (float)(end)* ms_per_sec/ freq;
//printf("Took timer2 ticks -> %f ms\n" , milliseconds2);
seconds=vbx_print_scalar_time( time_start, time_stop );
/*for(i=0;i<N*M;i++){
printf("The %d sample is: %d\n",i+1,Y[i]);
}
*/
//milliseconds = ((float)(end-start) / freq) * ms_per_sec;
// Print the results
//printf("Took %u timer ticks -> %8f ms\n" , end-start, milliseconds);
printf("Took timer ticks -> %g s\n" , seconds);
vbx_sp_free();
vbx_shared_free(X);
vbx_shared_free(Y);
return 0;
}
	
