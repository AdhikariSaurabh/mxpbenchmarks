//kmeans for neon

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

int16_t *x3;
int16_t *x14;
int16_t *x5;
int16_t *x16;
int16_t *x7;
int16_t *x18;
int16_t *x9;
int16_t *x20;
int16_t *x11;
int16_t *x22;
int16_t *x35;
int16_t *x46;
int16_t *x47;
int16_t *x58;
int16_t *x59;
int16_t *x70;
int16_t *res;
int16_t temp1;
int16_t temp2;
int16_t temp3;
int16_t temp4;
int16_t temp5;
int16_t temp6;
int16_t temp7;
int16_t temp8;
int16_t t1;
int16_t t2;
int16_t t3;
int16_t t4;
int16_t t5;
int16_t t6;
int16_t t7;
struct timeval tv1, tv2;

//clock_t start,diff;
//double milliseconds;
x3=(int16_t *)malloc(N*sizeof(int16_t));
x14=(int16_t *)malloc(N*sizeof(int16_t));
x5=(int16_t *)malloc(N*sizeof(int16_t));
x16=(int16_t *)malloc(N*sizeof(int16_t));
x7=(int16_t *)malloc(N*sizeof(int16_t));
x18=(int16_t *)malloc(N*sizeof(int16_t));
x9=(int16_t *)malloc(N*sizeof(int16_t));
x20=(int16_t *)malloc(N*sizeof(int16_t));
x11=(int16_t *)malloc(N*sizeof(int16_t));
x22=(int16_t *)malloc(N*sizeof(int16_t));
x35=(int16_t *)malloc(N*sizeof(int16_t));
x46=(int16_t *)malloc(N*sizeof(int16_t));
x47=(int16_t *)malloc(N*sizeof(int16_t));
x58=(int16_t *)malloc(N*sizeof(int16_t));
x59=(int16_t *)malloc(N*sizeof(int16_t));
x70=(int16_t *)malloc(N*sizeof(int16_t));

for(i=0;i<N;i++){
x3[i]=3;
}

for(i=0;i<N;i++){
x14[i]=1;
}

for(i=0;i<N;i++){
x5[i]=3;
}

for(i=0;i<N;i++){
x16[i]=1;
}

for(i=0;i<N;i++){
x7[i]=3;
}

for(i=0;i<N;i++){
x18[i]=1;
}

for(i=0;i<N;i++){
x9[i]=3;
}

for(i=0;i<N;i++){
x20[i]=1;
}

for(i=0;i<N;i++){
x11[i]=3;
}

for(i=0;i<N;i++){
x22[i]=1;
}

for(i=0;i<N;i++){
x35[i]=3;
}

for(i=0;i<N;i++){
x46[i]=1;
}

for(i=0;i<N;i++){
x47[i]=3;
}

for(i=0;i<N;i++){
x58[i]=1;
}

for(i=0;i<N;i++){
x59[i]=3;
}

for(i=0;i<N;i++){
x70[i]=1;
}

res=(int16_t *)malloc(N*sizeof(int16_t));
gettimeofday(&tv1,NULL);
//start=clock();
for(i=0;i<N;i++){
temp1=x3[i] - x14[i];
temp2=x5[i] - x16[i];
temp3=x7[i] - x18[i];
temp4=x9[i] - x20[i];
temp5=x11[i] - x22[i];
temp6=x35[i] - x46[i];
temp7=x47[i] - x58[i];
temp8=x59[i] - x70[i];

t1=temp1*temp1;
t2=temp2*temp2 + t1;
t3=temp3*temp3 + t2;
t4=temp4*temp4 + t3;
t5=temp5*temp5 + t4;
t6=temp6*temp6 + t5;
t7=temp7*temp7 + t6;

res[i]=temp8*temp8+t7;
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



free(x3);
free(x14);
free(x5);
free(x16);
free(x7);
free(x18);
free(x9);
free(x20);
free(x11);
free(x22);
free(x35);
free(x46);
free(x47);
free(x58);
free(x59);
free(x70);
free(res);
return 0;

}


