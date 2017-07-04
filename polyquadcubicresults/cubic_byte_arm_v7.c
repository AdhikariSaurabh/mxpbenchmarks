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
#define N 2097152
#define a 2
#define b 2
#define c 2
#define d 2
#define ops 9

int main(int argc, char *argv[]){
int32_t i;
int8_t *X;
int8_t *Y;
clock_t start,diff;
double milliseconds;
X=(int8_t *)malloc(N*sizeof(int8_t));

for(i=0;i<N;i++){
X[i]=1;
}
Y=(int8_t *)malloc(N*sizeof(int8_t));

start=clock();

for(i=0;i<N;i++){
Y[i]=a*X[i]*X[i]*X[i]+ b*X[i]*X[i] + c*X[i] + d;
}
diff = clock()-start;
milliseconds = (double)(diff)*1000 / CLOCKS_PER_SEC;
printf("Maximum Throughput for Poly3 kernel on ARM v7 in (Gops/sec) is -> %g Gops/sec\n",(N*ops*pow(10,3))/(milliseconds*pow(10,9)));
free(X);
free(Y);
return 0;

}






