# LDPC decoder hardware architecture using HLS methodology

### LDPC_QC_v4_no_flush 
This is a generic SystemC source code for Hardware implementation of any LDPC decoder defined with a Quasi-Cyclic matrix.

### CodeGenerator_v4_no_flush 
This is a C++ code that generate Header file used in "LDPC_QC_v4_no_flush" source code. This takes a LDPC matrix stored as in "H_matrix" and generate appropriate header file.

### shared 
This contains a library of SIMD instructions. It is used by SystemC model to express computation parallelism.

### LDPC_QC_v5_generic_1_ILS
This is a generic SystemC source code for Hardware implementation of 5G standard LDPC decoder. 

### CodeGenerator_v5_generic_ILS
This is a C++ code that generate Header file used in "LDPC_QC_v5_generic_1_ILS" source code.

### 5G_matrix
Contains some 5G LDPC matrix


Note : The sources codes were designed using Xilinx Vivado HLS 2019 version. In most recent version of Vivado HLS (VitisHLS) SystemC is no longer supported =(
