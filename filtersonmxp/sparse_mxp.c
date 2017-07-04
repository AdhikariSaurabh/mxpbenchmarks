#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
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
#define MXP 
#define M 6
int main()
{

#ifdef MXP
     VectorBlox_MXP_Initialize("mxp0","cma");
#else
     printf("MXP Disabled, APP is running entirely on ARM\n");
 #endif
 vbx_mxp_print_params();
 vbx_timestamp_t time_start,time_stop;
 
 // Assume 8x8 sparse matrix
    int32_t sparseMatrix[8][8] =
    {
        {0 , 0 , 3 , 0 , 4,0,0,0 },
        {0 , 0 , 5 , 7 , 0,0,0,0 },
        {0 , 0 , 0 , 0 , 0,0,0,0 },
        {0 , 2 , 6 , 0 , 0,0,0,0 },
        {0 , 0 , 0 , 0 , 0,0,0,0 },
        {0 , 0 , 0 , 0 , 0,0,0,0 },
        {0 , 0 , 0 , 0 , 0,0,0,0 },
        {0 , 0 , 0 , 0 , 0,0,0,0 }
    };
    int32_t i=0,j=0,k=0;
    int32_t a;
    double seconds;
    int32_t size = 0;
    int32_t vect[8]={1,2,3,4,5,6,7,8};
    int32_t *value = vbx_shared_malloc(sizeof(int)*M);
    int32_t *row_ptr = vbx_shared_malloc(sizeof(int)*M);
    int32_t *column= vbx_shared_malloc(sizeof(int)*M);
    int32_t *temp= vbx_shared_malloc(sizeof(int)*M);
    int32_t resultvector[M];
    vbx_word_t *v_vect = vbx_sp_malloc(M*sizeof(vbx_word_t));
    vbx_word_t *v_value = vbx_sp_malloc(M*sizeof(vbx_word_t));
    vbx_word_t *v_row_ptr = vbx_sp_malloc(M*sizeof(vbx_word_t));
    vbx_word_t *v_column = vbx_sp_malloc(M*sizeof(vbx_word_t));
    vbx_word_t *vtemp = vbx_sp_malloc(M*sizeof(vbx_word_t));
    vbx_dcache_flush_all();

    vbx_set_vl(M);
    vbx_timestamp_start();
    time_start = vbx_timestamp(); 


  // number of columns in compactMatrix (size) must be
   // equal to number of non - zero elements in sparse matrix
 
   for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            if (sparseMatrix[i][j] != 0)
                size++;
 
 
    int csrMatrix[3][size];
 
    // Making of new matrix
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            if (sparseMatrix[i][j] != 0)
            {
                csrMatrix[0][k] = i;
                csrMatrix[1][k] = j;
                csrMatrix[2][k] = sparseMatrix[i][j];
                k++;
            }  


   for (j = 0; j < 6; j++)
     {
       value[j]=csrMatrix[2][j];
     
       column[j]=csrMatrix[1][j];
     
       row_ptr[j]=csrMatrix[0][j];
     }


  vbx_dma_to_vector(v_column,column,M*sizeof(vbx_word_t));

    
   for (j = 0; j < 6; j++)
     {
       temp[j] = vect[column[j]];
     }

   
  vbx_dma_to_vector(vtemp,temp,M*sizeof(vbx_word_t));
  vbx_dma_to_vector(v_value,value,M*sizeof(vbx_word_t));

  vbx( VVW,VMUL,vtemp,v_value,vtemp);
  vbx_dma_to_host(value,vtemp,M*sizeof(vbx_word_t));
  time_stop = vbx_timestamp();
  seconds=vbx_print_scalar_time( time_start, time_stop );
  printf("Took timer ticks -> %g s\n" , seconds);

    for (i=0; i<3; i++)
    {
        for (j=0; j<size; j++)
            printf("%d ",csrMatrix[i][j]);
 
        printf("\n");
    }
    
    for(i=0;i<6;i++){
    
            printf("%d \n",value[i]);
         }

    return 0;
}


