// Running the code using the Arm V7 processor 
// gcc --cpu=Cortex-A9 -O3 source.c -o out 

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
#define a 2
#define b 2
#define c 2
#define ops 5

int main(int argc, char *argv[]){
int32_t i;
int16_t *X;
int16_t *Y;
struct timeval tv1, tv2;
//clock_t start,diff;
//double milliseconds;
X=(int16_t *)malloc(N*sizeof(int16_t));

for(i=0;i<N;i++){
X[i]=1;
}
Y=(int16_t *)malloc(N*sizeof(int16_t));
gettimeofday(&tv1,NULL);
//start=clock();
for(i=0;i<N;i++){
Y[i]=a*X[i]*X[i]+ b*X[i] + c;
}
gettimeofday(&tv2,NULL); 
//diff = clock()-start;
//milliseconds = (double)(diff)*1000 / CLOCKS_PER_SEC;
//printf("%g\n",milliseconds);
//printf("Maximum Throughput on ARM v7 for POly2(Quad) in (Gops/sec) is -> %g Gops/sec\n",(N*ops*pow(10,3))/(milliseconds*pow(10,9)));
printf ("Total time = %f seconds\n", 
          (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + 
         (double) (tv2.tv_sec - tv1.tv_sec));

free(X);
free(Y);
return 0;

}






