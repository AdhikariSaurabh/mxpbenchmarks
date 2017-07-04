#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
int main()
{
    // Assume 6x6 sparse matrix
    int sparseMatrix[6][6] =
    {
        {0 , 0 , 3 , 0 , 4 },
        {0 , 0 , 5 , 7 , 0 },
        {0 , 0 , 0 , 0 , 0 },
        {0 , 2 , 6 , 0 , 0 },
        {0 , 0 , 0 , 0 , 0 },
        {0 , 0 , 0 , 0 , 0 }
        
    };
    int i=0,j=0,k=0;
    int a;
    int size = 0;
    clock_t start,diff;
    double milliseconds;
    int vect[6]={1,2,3,4,5,6};
    int *value = malloc(sizeof(int)*6);
    int *row_ptr = malloc(sizeof(int)*6);
    int *column=malloc(sizeof(int)*6);
    int resultvector[6];
   // number of columns in compactMatrix (size) must be
   // equal to number of non - zero elements in sparse matrix
 
 start = clock();
   for (i = 0; i < 6; i++)
        for (j = 0; j < 6; j++)
            if (sparseMatrix[i][j] != 0)
                size++;
 
 
    int csrMatrix[3][size];
 
    // Making of new matrix
    for (i = 0; i < 6; i++)
        for (j = 0; j < 6; j++)
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



    for (j = 0; j < 6; j++)
     {
       value[j] = value[j] * vect[column[j]];
     }


     diff = clock() - start;
     milliseconds = (double) (diff) / CLOCKS_PER_SEC;
/*    
    for (j = 0; j < 6; j++)
     {
       value[j] = value[j] * vect[column[j]];
     }
*/


    for (i=0; i<3; i++)
    {
        for (j=0; j<size; j++)
            printf("%d ",csrMatrix[i][j]);
 
        printf("\n");
    }
    
    for(i=0;i<6;i++){
    
            printf("%d \n",value[i]);
         }
 
   

   printf("Timer took -----> %f \n", milliseconds); 
    return 0;
}
