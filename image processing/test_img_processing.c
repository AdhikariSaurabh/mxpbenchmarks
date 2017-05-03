// Image Processing : Scaling and inverting the image 


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
#include "vbx_types.h"
#include "vbx_test.h"
#include "vectorblox_mxp_lin.h"
#include "vbx.h"
#include "vbx_port.h"
//#include "vbx_common.h"
#include "pgm.h"
/** Enable below define for measuring time in application or comment it*/
#define PROFILER
#define MXP
//#define DEBUG_PRINT

#define PASS 0
#define FAIL -1
pgm_t opgm;
pgm_t ipgm;
int img_size = 0;
/** Enable below define for seeing the values read by this application or comment it*/
//#define DEBUG

int verify_output(int *p)
{
    int i;
    for(i = 0; i < img_size; i++)
    {
	if( opgm.buf[i] != (255 - ipgm.buf[i]) )
	{
	    *p = i;
	    return FAIL;
	}
    }
    return PASS;
}

/** Starting point of application*/
int main(int argc, char *argv[])
{
    

    vbx_timestamp_t time_start,time_stop;
  
    double seconds;
    int i,index;
    int rc = PASS;
    uint32_t failed_loc;
    unsigned char *vb,*v_db,*temp;
    int max = 255;
    int max_sp_size = 65536;
    char outfile[100] = "out_";
    const char *outfilename = NULL;
	if(argc != 2)
	{
		printf("Not enough arguments. Please specify input image name\n");
		return -1; 
	}
#ifdef MXP
    VectorBlox_MXP_Initialize("mxp0","cma");
#else
    printf("MXP Disabled, APP is running entirely on ARM\n");
#endif

    vbx_mxp_print_params();

    //Reading image
    readPGM(&ipgm,argv[1]);
    img_size = (ipgm.width * ipgm.height);// >> 3;

#ifdef DEBUG_PRINT
    for( i = 0; i < img_size; i++)
    {
	printf("in[%d] = 0x%x\n",i,ipgm.buf[i]);
    }
#endif

    opgm.width = ipgm.width;
    opgm.height = ipgm.height;
    opgm.buf = (unsigned char*)vbx_shared_malloc(ipgm.width * ipgm.height * sizeof(unsigned char));

    //Processing image
    vbx_dcache_flush_all();

    vb = (unsigned char *)vbx_sp_malloc(max_sp_size*sizeof(unsigned char ));
    //v_db = (unsigned char *)vbx_sp_malloc(30000*sizeof(unsigned char));
    // freq = vbx_timestamp_freq(); // timer
    time_start = vbx_timestamp();
    vbx_dma_to_vector(vb, ipgm.buf, max_sp_size);
    vbx_set_vl(max_sp_size);

   vbx(SVBU, VSUB, vb, max, vb);
   // logic for scale down
   // float factor = 0.5;
   // vbx(SVBU, VMUL, vb, factor, vb);

    vbx_dma_to_host(opgm.buf, vb, max_sp_size);

    vbx_sync();
    time_stop = vbx_timestamp();
   // milliseconds = (float)(end-start) / freq * ms_per_sec;
    // print the timer results
    seconds=vbx_print_scalar_time( time_start, time_stop );
    //printf("Took %u timer ticks -> %g ms\n" , end-start, milliseconds);
    printf("Took timer ticks -> %g s\n" , seconds);
    //Writing image
    strcat(outfile,argv[1]);
#ifdef DEBUG_PRINT
    for( i = 0; i < img_size; i++)
    {
		printf("out[%d] = 0x%x\n",i,opgm.buf[i]);
    }
#endif
    outfilename = outfile;
    writePGM(&opgm,outfilename);

    //verify output
    rc = verify_output(&failed_loc);
    if(PASS == rc)
    {
		printf("\nOutput verified success !! \n");
    }
    else
    {
		printf("\n Failed at location %d\n",failed_loc);
    }
    vbx_sp_free();	
    vbx_shared_free(ipgm.buf);
    vbx_shared_free(opgm.buf);
}
