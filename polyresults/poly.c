nclude <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <errno.h>
#include <math.h>
#ifdef MXP
#include "vbx.h"
#include "vbx_port.h"
#include "vbx_common.h"
#include "vectorblox_mxp_lin.h"
#endif
#define N 128
#define M 65536
#define ops 5

uint32_t i;

#ifdef MXP

void kernel_mxp(int8_t **X, int8_t **Y, int nx, int ny)
{
int8_t a = 2;
int8_t b = 2;
int8_t c = 2;
*X=(int8_t*)vbx_shared_malloc(nx*ny*sizeof(int8_t));
*Y=(int8_t*)vbx_shared_malloc(nx*ny*sizeof(int8_t));

int8_t *sc_X = *X;
int8_t *sc_Y = *Y;
for(i=0;i<nx*ny;i++){
	sc_X[i]=1;
        sc_Y[i]=0;
}
vbx_timestamp_t time_start,time_stop;
vbx_dcache_flush_all(); // not required since using the uncached region 

vbx_byte_t *vx = vbx_sp_malloc( ny*sizeof(vbx_byte_t));
vbx_byte_t *vy = vbx_sp_malloc( ny*sizeof(vbx_byte_t));
vbx_byte_t *vara = vbx_sp_malloc( ny*sizeof(vbx_byte_t));
vbx_set_vl(ny);

vbx_timestamp_start();
time_start = vbx_timestamp();
for(i=0;i<M*N;i=i+M){
	vbx_dma_to_vector( vx, sc_X+i,ny*sizeof(vbx_byte_t));
	vbx( SVB,VMUL,vy,a,vx);
	vbx( VVB,VMUL,vy,vy,vx);
	vbx( SVB,VMUL,vara,b,vx);
	vbx( VVB,VADD,vy,vy,vara );
	vbx( SVB,VADD,vy,c,vy);
	vbx_dma_to_host( sc_Y+i, vy,ny*sizeof(vbx_byte_t));
	vbx_sync();
}
time_stop = vbx_timestamp();
vbx_timestamp_t cycles = time_stop - time_start;
double seconds = ((double) cycles) / ((double) vbx_timestamp_freq());

printf("Maximum Throughput for Poly2 kernel on MXP in (Gops/sec) is -> %g
Gops/sec\n",(nx*ny*ops)/(seconds*pow(10,9)));
vbx_sp_free();
vbx_shared_free(sc_X);
vbx_shared_free(sc_Y);
}

#endif


void kernel(int8_t **X, int8_t **Y, int nx, int ny)
{
int8_t a = 2;
int8_t b = 2;
int8_t c = 2;
clock_t start,diff;
double milliseconds;
*X=(int8_t*)malloc(nx*ny*sizeof(int8_t));
*Y=(int8_t*)malloc(nx*ny*sizeof(int8_t));
int8_t *x = *X;
int8_t *y = *Y;
for(i=0;i<nx*ny;i++){
	x[i]=1;
        y[i]=0;
}

start=clock();
for(i=0;i<nx*ny;i++){
y[i]=a*x[i]*x[i]+ b*x[i] + c;
}

diff = clock()-start;
milliseconds = (double)(diff)*1000 / CLOCKS_PER_SEC;
printf("%f",milliseconds);
#ifdef NEON
printf("Maximum Throughput for Poly2 kernel on Neon in (Gops/sec) is----> %g
Gops/sec\n",(nx*ny*ops*pow(10,3))/(milliseconds*pow(10,9)));
#endif
#ifdef ARM
printf("Maximum Throughput for Poly2 kernel on ARM in (Gops/sec) is----> %g
Gops/sec\n",(nx*ny*ops*pow(10,3))/(milliseconds*pow(10,9)));
#endif
free(x);
free(y);

}


int main(int argc, char *argv[])
{

#ifdef MXP
VectorBlox_MXP_Initialize("mxp0","cma");
#endif
 
int8_t *X=NULL,*Y=NULL;
int nx = N;
int ny = M;

#ifdef MXP
// used to initialize and compute kernel
kernel_mxp(&X,&Y,nx,ny);
#else

int8_t a = 2;
int8_t b = 2;
int8_t c = 2;
clock_t start,diff;
double milliseconds;
X=(int8_t *)malloc(nx*ny*sizeof(int8_t));
Y=(int8_t *)malloc(nx*ny*sizeof(int8_t));
for(i=0;i<nx*ny;i++){
	X[i]=1;
        Y[i]=0;
}

start=clock();
for(i=0;i<nx*ny;i++){
Y[i]=a*X[i]*X[i]+ b*X[i] + c;
}

diff = clock()-start;
milliseconds = (double)(diff)*1000 / CLOCKS_PER_SEC;
//printf("%f",milliseconds);
#ifdef NEON
printf("Maximum Throughput for Poly2 kernel on Neon in (Gops/sec) is----> %g
Gops/sec\n",(nx*ny*ops*pow(10,3))/(milliseconds*pow(10,9)));
#endif
#ifdef ARM
printf("Maximum Throughput for Poly2 kernel on ARM in (Gops/sec) is----> %g
Gops/sec\n",(nx*ny*ops*pow(10,3))/(milliseconds*pow(10,9)));
#endif
free(X);
free(Y);

#endif

return 0;
}
