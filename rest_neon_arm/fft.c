// fft on neon and arm 


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

int32_t *x0;
int32_t *x1;
int32_t *x2;
int32_t *x3;
int32_t *x4;
int32_t *x5;
int32_t *y0;
int32_t *y1;
int32_t *y2;
int32_t *y3;
int32_t temp1;
int32_t temp2;
struct timeval tv1, tv2;
//clock_t start,diff;
//double milliseconds;
x0=(int32_t *)malloc(N*sizeof(int32_t));
x1=(int32_t *)malloc(N*sizeof(int32_t));
x2=(int32_t *)malloc(N*sizeof(int32_t));
x3=(int32_t *)malloc(N*sizeof(int32_t));
x4=(int32_t *)malloc(N*sizeof(int32_t));
x5=(int32_t *)malloc(N*sizeof(int32_t));

for(i=0;i<N;i++){
x0[i]=3;
}

for(i=0;i<N;i++){
x1[i]=3;
}

for(i=0;i<N;i++){
x2[i]=3;
}

for(i=0;i<N;i++){
x3[i]=3;
}

for(i=0;i<N;i++){
x4[i]=3;
}

for(i=0;i<N;i++){
x5[i]=3;
}

y0=(int32_t *)malloc(N*sizeof(int32_t));
y1=(int32_t *)malloc(N*sizeof(int32_t));
y2=(int32_t *)malloc(N*sizeof(int32_t));
y3=(int32_t *)malloc(N*sizeof(int32_t));
gettimeofday(&tv1,NULL);
//start=clock();
for(i=0;i<N;i++){
temp1=x1[i]*x2[i] + x3[i]*x4[i];
temp2=x1[i]*x4[i] - x3[i]*x2[i];
y0[i]=x0[i] - temp1;
y1[i]=x0[i] + temp1;
y2[i]=x5[i] - temp2;
y3[i]=x5[i] + temp2;


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
         (double) (tv2.tv_sec - tv1.tv_sec));




free(x0);
free(x1);
free(x2);
free(x3);
free(x4);
free(x5);
free(y0);
free(y1);
free(y2);
free(y3);
return 0;

}

