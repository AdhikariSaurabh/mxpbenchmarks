//stencil.c in neon 

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <errno.h>
#define N 4194304

int main(int argc, char *argv[]){
int32_t i;

int16_t *x0;
int16_t *x1;
int16_t *x2;
int16_t *x3;
int16_t *x4;
int16_t *x5;
int16_t *x6;
int16_t *x7;
int16_t *x8;
int16_t *x9;
int16_t *x10;
int16_t *x11;
int16_t *x12;
int16_t *x13;
int16_t *x15;
int16_t *y0;
int16_t *y1;
struct timeval tv1, tv2;
//clock_t start,diff;
//double milliseconds;
x0=(int16_t *)malloc(N*sizeof(int16_t));
x1=(int16_t *)malloc(N*sizeof(int16_t));
x2=(int16_t *)malloc(N*sizeof(int16_t));
x3=(int16_t *)malloc(N*sizeof(int16_t));
x4=(int16_t *)malloc(N*sizeof(int16_t));
x5=(int16_t *)malloc(N*sizeof(int16_t));
x6=(int16_t *)malloc(N*sizeof(int16_t));
x7=(int16_t *)malloc(N*sizeof(int16_t));
x8=(int16_t *)malloc(N*sizeof(int16_t));
x9=(int16_t *)malloc(N*sizeof(int16_t));
x10=(int16_t *)malloc(N*sizeof(int16_t));
x11=(int16_t *)malloc(N*sizeof(int16_t));
x12=(int16_t *)malloc(N*sizeof(int16_t));
x13=(int16_t *)malloc(N*sizeof(int16_t));
x15=(int16_t *)malloc(N*sizeof(int16_t));

for(i=0;i<N;i++){
x0[i]=2;
}

for(i=0;i<N;i++){
x1[i]=2;
}

for(i=0;i<N;i++){
x2[i]=2;
}

for(i=0;i<N;i++){
x3[i]=2;
}

for(i=0;i<N;i++){
x4[i]=2;
}

for(i=0;i<N;i++){
x5[i]=2;
}

for(i=0;i<N;i++){
x6[i]=2;
}

for(i=0;i<N;i++){
x7[i]=2;
}

for(i=0;i<N;i++){
x8[i]=2;
}

for(i=0;i<N;i++){
x9[i]=2;
}

for(i=0;i<N;i++){
x10[i]=2;
}

for(i=0;i<N;i++){
x11[i]=2;
}

for(i=0;i<N;i++){
x12[i]=2;
}

for(i=0;i<N;i++){
x13[i]=2;
}


for(i=0;i<N;i++){
x15[i]=2;
}

y0=(int16_t *)malloc(N*sizeof(int16_t));
y1=(int16_t *)malloc(N*sizeof(int16_t));
gettimeofday(&tv1,NULL);
//start=clock();
for(i=0;i<N;i++){
y0[i]=x6[i]*((x0[i]+x1[i]) + (x2[i]+x3[i]) + (x4[i]+x5[i])) - x7[i];
y1[i]=x6[i]*((x8[i]+x9[i]) + (x10[i]+x11[i]) + (x12[i]+x13[i])) - x15[i];
}
gettimeofday(&tv2,NULL);
//diff = clock()-start;
//milliseconds = (diff*1000.0) / CLOCKS_PER_SEC;
//printf("Took timer ticks -> %lf ms \n" , milliseconds);
//for(i=0;i<3;i++){  // just checking the first three values of the output
//printf("%d \n ",res[i]);
//}
//printf("%d\n",y0[0]);
//printf("%d\n",y1[0]);
//printf("%d\n",y2[0]);
//printf("%d",y3[0]);

printf ("Total time = %f seconds\n", 
          (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + 
         (double) (tv2.tv_sec -  tv1.tv_sec));





free(x0);
free(x1);
free(x2);
free(x3);
free(x4);
free(x5);
free(x6);
free(x7);
free(x8);
free(x9);
free(x10);
free(x11);
free(x12);
free(x13);
free(x15);
free(y0);
free(y1);

return 0;

}


