# EVALUATING THE PERFORMANCE OF COMPUTING PLATFORMS USING A SET OF COMPUTE KERNELS
This project describes the implementation of the standard benchmarks on the FPGA overlay for the performance analysis and comparing the performance measure such as the throughput (Gops/sec) and the speedup against the other embedded hard processors such as ARM coterx A9, SIMD NEON and INTEL I3. MXP VectorBlox is the FPGA overlay that we have used in our work. For detailed information on the power of the MXP soft-vector processor checkout   [MXP](http://vectorblox.com/).  

## Table of Contents
+ [General information](#info) 
    + [MXP](#info-mxp)
    + [Xilinux Distribution](#info-xilinux)
+ [Pre-Requisites](#prereq) 
    + [Zedboard Pre-Requisites](#prereq-zb)
	+ [Repositories](#repo)
+ [Throughput Analysis](#performanceanalysis) 
+ [Speedup Analysis](#speedupanalysis) 

## <a name="info"></a> 1) General Information
### <a name="info-opencl"></a> 1.1: MXP
The VectorBlox Matrix Processor is a scalable soft core processor designed on FPGAs. It implements classic massively parallel vector processor algorithms traditionally used in scientific super-computers.

### <a name="info-xilinux"></a> 1.2: Xilinux Distribution
This project is implemented and tested using Xilinux distribution. Xilinux Distribution is a demo kit with ubuntu 12.04 for Processing System (PS). We have provided the linux support for accessing the MXP overlay on the ZedBoard.    

## <a name="prereq"></a> 2) Pre-Requisites
### <a name="prereq-zb"></a> 2.1: Zedboard Pre-Requisites

* **Booting Xilinux on zedboard:**
In order to install the xilinux on zedboard with the base xillybus bitstream please follow the instructions given in the Mxp Linux set up file mxplinuxsetup.doc that tells about configuring the MXP overlay with the Xilinx Zynq. 
 

### <a name="repo"></a> 2.2: Repositories 
In this project, we used following repositories:

* [mxprepo](https://github.com/VectorBlox/mxp.git) 
* [linuxrepo](https://github.com/VectorBlox/linux-xlnx.git)
* [Ubootrepo](https://github.com/VectorBlox/u-boot-xlnx.git)
* [devicetreerepo](https://github.com/VectorBlox/device-tree-xlnx.git)


## <a name="performanceanalysis"></a> 3) Throughput Analysis

* **PERFORMANCE GRAPHS:**

**FilterGraphs:**
* FILTERGRAPHS consist of the performance graphs for the filters CHEBYSHEV, MIBENCH and QSPLINE

![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/filtergraphs/filter_performance_byte.png?raw=true "Optional Title")

![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/filtergraphs/filter_performance_halfword.png?raw=true "Optional Title")

![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/filtergraphs/filter_performance_word.png?raw=true "Optional Title")


**KernelGraphs:**
* KERNELGRAPHS consist of the FFT, KMEANS, MM, SPMV, STENCIL and MRI. 

![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/kernelgraphs/kernel_performance_byte.png?raw=true "Optional Title")

![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/kernelgraphs/kernel_performance_halfword.png?raw=true "Optional Title")

![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/kernelgraphs/kernel_performance_word.png?raw=true "Optional Title")


**PolytestGraphs:**
* POLYTESTGRAPHS consist of the polynomial performance results.

![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/polytestgraphs/polytest_graph_byte.png?raw=true "Optional Title")

![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/polytestgraphs/polytest_graph_halfword.png?raw=true "Optional Title")

![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/polytestgraphs/polytest_graph_word.png?raw=true "Optional Title")


**PolynomialGraphs:**
* Number of Samples vs time taken plots for the polynomial (quadratic and cubic samples) in different platforms present in      polynomial_graphs_of_samplesvstimetaken(msec).

![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/polynomial_graphsno_of_samples%20vs%20time%20taken(msec)/cubic_samples.png?raw=true "Optional Title")


![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/polynomial_graphsno_of_samples%20vs%20time%20taken(msec)/quadratic_samples.png?raw=true "Optional Title")

## <a name="Speedup Analysis"></a> 4) Speedup Analysis
**Speedup Analysis with respect to ARM cortex A9 at byte, halfword and word level**

![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/speedup_analysis/speedupbyte.png?raw=true "Byte(8-bits) Level Speedup")


![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/speedup_analysis/speeduphalfword.png?raw=true "Halfword(16-bits) Level Speedup")

![Alt text](https://github.com/AdhikariSaurabh/mxpbenchmarks/blob/master/speedup_analysis/speedupword.png?raw=true "Word(32-bits) Level Speedup")
 



