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
#include "vbx_test.h"
#include "vbx_types.h"
#include "vectorblox_mxp_lin.h"
#define vector_len 1
#define MXP

int32_t foo(int32_t x){

vbx_timestamp_t time_start,time_stop;
double seconds;
//int32_t *x_t = vbx_shared_malloc(sizeof(int32_t));
int32_t *x_t=&x;
vbx_word_t *vx = vbx_sp_malloc(sizeof(vbx_word_t));
vbx_word_t *vres = vbx_sp_malloc(sizeof(vbx_word_t));
vbx_dcache_flush_all();
vbx_set_vl(vector_len);
vbx_timestamp_start();
time_start = vbx_timestamp();
vbx_dma_to_vector( vx,x_t,sizeof(vbx_word_t));
vbx_dma_to_vector( vres,x_t,sizeof(vbx_word_t));

vbx( SVW,VMUL,vres,16,vres); 
vbx( VVW,VMUL,vres,vx,vres);
vbx( SVW,VADD,vres,-20,vres);
//temp*x-20

vbx( VVW,VMUL,vres,vx,vres);
vbx( VVW,VMUL,vres,vx,vres);
//x*(temp*x-20)*x

vbx( SVW,VADD,vres,5,vres);
//x*(temp*x-20)*x+5

vbx( VVW,VMUL,vres,vx,vres );
//(x*(x*(temp*x-20)*x+5))
vbx_dma_to_host(x_t,vres,sizeof(vbx_word_t));
vbx_sync();
time_stop = vbx_timestamp();
seconds=vbx_print_scalar_time( time_start, time_stop );
printf("Took timer ticks -> %g s\n" , seconds);
//free(x_t);
vbx_sp_free();

return *x_t;

}
int main()
{

#ifdef MXP
    VectorBlox_MXP_Initialize("mxp0","cma");
#else
    printf("MXP Disabled, APP is running entirely on ARM\n");
#endif
vbx_mxp_print_params();
int32_t x=2;
int32_t result;
result = foo(x);
printf("The result is -> %d \n" , result);
return 0;
}


