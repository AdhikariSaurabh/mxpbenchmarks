// qspline.c

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
#define N 256
#define M 16384
#define ops 27
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
int8_t *a_t = vbx_shared_malloc(N*M*sizeof(char));
int8_t *b_t = vbx_shared_malloc(N*M*sizeof(char));
int8_t *q_t = vbx_shared_malloc(N*M*sizeof(char));
int8_t *u_t = vbx_shared_malloc(N*M*sizeof(char));
int8_t *v_t = vbx_shared_malloc(N*M*sizeof(char));
int8_t *w_t = vbx_shared_malloc(N*M*sizeof(char));
int8_t *z_t = vbx_shared_malloc(N*M*sizeof(char));
int8_t *res = vbx_shared_malloc(N*M*sizeof(char));

vbx_byte_t *va = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vb = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vq = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vu = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vv = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vw = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vz = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vtemp = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vtemp1 = vbx_sp_malloc(M*sizeof(vbx_byte_t));
vbx_byte_t *vres = vbx_sp_malloc(M*sizeof(vbx_byte_t));

vbx_dcache_flush_all();
vbx_set_vl(M);
for(i=0;i<M*N;i++){
a_t[i]=1; 
}

for(i=0;i<M*N;i++){
b_t[i]=1; 
}


for(i=0;i<M*N;i++){
q_t[i]=1; 
}

for(i=0;i<M*N;i++){
u_t[i]=1; 
}

for(i=0;i<M*N;i++){
v_t[i]=1; 
}

for(i=0;i<M*N;i++){
w_t[i]=1; 
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
vbx_dma_to_vector( va,a_t+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vb,b_t+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vq,q_t+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vu,u_t+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vv,v_t+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vw,w_t+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vz,z_t+i,M*sizeof(vbx_byte_t));
vbx_dma_to_vector( vres,b_t+i,M*sizeof(vbx_byte_t));

//temp3
vbx( VVB,VMUL,vz,vz,vu);
vbx( VVB,VMUL,vz,vz,vu);
vbx( VVB,VMUL,vz,vz,vu);

//temp_3 = z*u*u*u;
//temp6

vbx( VVB,VMUL,vq,vq,vv);
vbx( VVB,VMUL,vq,vq,vv);
vbx( VVB,VMUL,vq,vq,vv);

//v*v*v*q



//temp7 or temp8


vbx( VVB,VMUL,vtemp,vv,vu);
//u*v



//temp 11
vbx( VVB,VMUL,va,va,vu);
vbx( SVB,VMUL,va,4,va);
vbx( VVB,VMUL,va,va,vu);
vbx( VVB,VMUL,va,va,vu);
vbx( VVB,VMUL,va,va,vv);

//v*u*u*4*a*u


//temp14

vbx( VVB,VMUL,vtemp1,vtemp,vw);
vbx( SVB,VMUL,vtemp1,4,vtemp1);
vbx( VVB,VMUL,vtemp1,vtemp1,vv);
vbx( VVB,VMUL,vtemp1,vtemp1,vv);

//v*v*4*w*u*v

vbx( VVB,VMUL,vz,vz,vu);
vbx( VVB,VADD,vz,vz,va);
vbx( VVB,VADD,vz,vz,vtemp1);
vbx( VVB,VMUL,vq,vq,vv);
vbx( VVB,VADD,vz,vz,vq);
vbx( VVB,VMUL,vres,vres,vtemp);
vbx( VVB,VMUL,vres,vres,vtemp);
vbx( SVB,VMUL,vres,6,vres);
vbx( VVB,VADD,vres,vres,vz);

vbx_dma_to_host(res+i,vres,M*sizeof(vbx_byte_t));
vbx_sync();

}
time_stop = vbx_timestamp();
/*
for(i=0;i<N*M;i++){
printf("The %d sample is: %d\n",i+1,res[i]);
}
*/

//printf("The sample is: %d %d\n",res[0],res[1]);

vbx_timestamp_t cycles = time_stop - time_start;
double seconds = ((double) cycles) / ((double) vbx_timestamp_freq());
printf("Maximum Throughput on MXP for qspline kernel in (Gops/sec) is -> %g Gops/sec\n",(N*M*ops)/(seconds*pow(10,9))); 

vbx_shared_free(a_t);
vbx_shared_free(b_t);
vbx_shared_free(q_t);
vbx_shared_free(u_t);
vbx_shared_free(v_t);
vbx_shared_free(w_t);
vbx_shared_free(z_t);
vbx_shared_free(res);
vbx_sp_free();
return 0;
}

