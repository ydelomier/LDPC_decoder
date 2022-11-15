#ifndef GEN_PAR_CPP_H
#define GEN_PAR_CPP_H

#define SINGLE_DEG_CHK_NODES false
#define NB_DEG_CHK_NODES 1
#define DEG_1_CHK_NODES  6
#define NB_DEG_1_CNODES  8
#define NB_DEG_CHK_NODES 2
#define DEG_2_CHK_NODES  7
#define NB_DEG_2_CNODES  4

#define SINGLE_DEG_VAR_NODES false
#define NB_DEG_VAR_NODES 1
#define DEG_1_VAR_NODES  2
#define NB_DEG_1_VNODES  11
#define NB_DEG_VAR_NODES 2
#define DEG_2_VAR_NODES  3
#define NB_DEG_2_VNODES  8
#define NB_DEG_VAR_NODES 3
#define DEG_3_VAR_NODES  6
#define NB_DEG_3_VNODES  5

//
//
//
const unsigned char nbVariableParParite[12] = {
  6, 7, 7, 6, 6, 7, 6, 6, 7, 6, 6, 6
};

//
//
//
const unsigned char nbPariteParVariable[24] = {
  3, 3, 6, 3, 3, 6, 3, 6, 3, 6, 3, 6, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

//
//
//
const unsigned short transpose[76] = {
  /* CN 0 */ 3, 6, 33, 36, 51, 54, 
  /* CN 1 */ 4, 18, 24, 27, 45, 55, 56, 
  /* CN 2 */ 12, 15, 19, 28, 46, 57, 58, 
  /* CN 3 */ 0, 7, 34, 37, 59, 60, 
  /* CN 4 */ 8, 25, 38, 42, 61, 62, 
  /* CN 5 */ 16, 20, 29, 47, 52, 63, 64, 
  /* CN 6 */ 9, 13, 39, 43, 65, 66, 
  /* CN 7 */ 5, 10, 26, 40, 67, 68, 
  /* CN 8 */ 1, 17, 21, 30, 48, 69, 70, 
  /* CN 9 */ 22, 31, 44, 49, 71, 72, 
  /* CN 10 */ 11, 14, 35, 41, 73, 74, 
  /* CN 11 */ 2, 23, 32, 50, 53, 75
};


//
//
//
const unsigned char gf[76] = {
  /* CN 0 */ 94, 73, 55, 83, 7, 0, 
  /* CN 1 */ 27, 22, 79, 9, 12, 0, 0, 
  /* CN 2 */ 24, 22, 81, 33, 0, 0, 0, 
  /* CN 3 */ 61, 47, 65, 25, 0, 0, 
  /* CN 4 */ 39, 84, 41, 72, 0, 0, 
  /* CN 5 */ 46, 40, 82, 79, 0, 0, 0, 
  /* CN 6 */ 95, 53, 14, 18, 0, 0, 
  /* CN 7 */ 11, 73, 2, 47, 0, 0, 
  /* CN 8 */ 12, 83, 24, 43, 51, 0, 0, 
  /* CN 9 */ 94, 59, 70, 72, 0, 0, 
  /* CN 10 */ 7, 65, 39, 49, 0, 0, 
  /* CN 11 */ 43, 66, 41, 26, 7, 0
};



#endif //GEN_PAR_CPP_H
