C_SRCS += vbx_api.c vbx_test.c
CXX_SRCS += Vector.cpp

ifeq ($(TARGET),LINUX)
C_SRCS += vectorblox_mxp_lin.c
endif

ifeq ($(CROSS_COMPILE),arm-altera-eabi-)
C_SRCS += vectorblox_mxp_hps.c
endif
