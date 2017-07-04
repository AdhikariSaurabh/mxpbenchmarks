// mm.c for the neon 
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

int8_t *x1;
int8_t *x3;
int8_t *x4;
int8_t *x15;
int8_t *x5;
int8_t *x7;
int8_t *x9;
int8_t *x18;
int8_t *x14;
int8_t *x24;
int8_t *x19;
int8_t *x28;
int8_t *x25;
int8_t *x34;
int8_t *x29;
int8_t *x38;
int8_t *res;
int8_t temp1;
int8_t temp2;
int8_t temp3;
int8_t temp4;
int8_t temp5;
int8_t temp6;
int8_t temp7;
int8_t temp8;
struct timeval tv1, tv2;
//clock_t start,diff;
//double milliseconds;
x1=(int8_t *)malloc(N*sizeof(int8_t));
x3=(int8_t *)malloc(N*sizeof(int8_t));
x4=(int8_t *)malloc(N*sizeof(int8_t));
x15=(int8_t *)malloc(N*sizeof(int8_t));
x5=(int8_t *)malloc(N*sizeof(int8_t));
x7=(int8_t *)malloc(N*sizeof(int8_t));
x9=(int8_t *)malloc(N*sizeof(int8_t));
x18=(int8_t *)malloc(N*sizeof(int8_t));
x14=(int8_t *)malloc(N*sizeof(int8_t));
x24=(int8_t *)malloc(N*sizeof(int8_t));
x19=(int8_t *)malloc(N*sizeof(int8_t));
x28=(int8_t *)malloc(N*sizeof(int8_t));
x25=(int8_t *)malloc(N*sizeof(int8_t));
x34=(int8_t *)malloc(N*sizeof(int8_t));
x29=(int8_t *)malloc(N*sizeof(int8_t));
x38=(int8_t *)malloc(N*sizeof(int8_t));

for(i=0;i<N;i++){
x1[i]=2;
}

for(i=0;i<N;i++){
x3[i]=2;
}

for(i=0;i<N;i++){
x4[i]=2;
}

for(i=0;i<N;i++){
x15[i]=2;
}

for(i=0;i<N;i++){
x5[i]=2;
}

for(i=0;i<N;i++){
x7[i]=2;
}

for(i=0;i<N;i++){
x9[i]=2;
}

for(i=0;i<N;i++){
x18[i]=2;
}

for(i=0;i<N;i++){
x14[i]=2;
}

for(i=0;i<N;i++){
x24[i]=2;
}

for(i=0;i<N;i++){
x19[i]=2;
}

for(i=0;i<N;i++){
x28[i]=2;
}

for(i=0;i<N;i++){
x25[i]=2;
}

for(i=0;i<N;i++){
x34[i]=2;
}

for(i=0;i<N;i++){
x29[i]=2;
}

for(i=0;i<N;i++){
x38[i]=2;
}

res=(int8_t *)malloc(N*sizeof(int8_t));
gettimeofday(&tv1,NULL);
//start=clock();
for(i=0;i<N;i++){
temp1=x1[i] * x3[i];
temp2=x4[i] * x15[i];
temp3=x5[i] * x7[i];
temp4=x9[i] * x18[i];
temp5=x14[i] * x24[i];
temp6=x19[i] * x28[i];
temp7=x25[i] * x34[i];
temp8=x29[i] *x38[i];

res[i]=temp1 + temp2 + temp3 + temp4 + temp5 +temp6 + temp7 + temp8;
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

free(x1);
free(x3);
free(x4);
free(x15);
free(x5);
free(x7);
free(x9);
free(x18);
free(x14);
free(x24);
free(x19);
free(x28);
free(x25);
free(x34);
free(x29);
free(x38);
free(res);
return 0;

}


