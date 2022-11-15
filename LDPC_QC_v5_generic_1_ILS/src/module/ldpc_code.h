#ifndef LDPC_STRUCTURE_H
#define LDPC_STRUCTURE_H


const sc_uint<10> N_Array [10];
const sc_uint<10> K_Array [10];
const sc_uint<10> M_Array [10];

const sc_uint< N_QC > Factor_Z [10];
const sc_uint< N_QC > Nb_FRAME [10];
const int Size_Frame [10];

//
//
//
const unsigned char _GenericDegreeCNs[15] = {
  19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 
   3,  3,  3
};


//
//
//
const unsigned char _GenericPosBlocVNs[237] = {
  /* CN   0 [19] */   0,   1,   2,   3,   5,   6,   9,  10,  11,  12,  13,  15,  16,  18,  19,  20,  21,  22,  23, 
  /* CN   0 [19] */  27,  28,  29,  30,  32,  33,  36,  37,  38,  39,  40,  42,  43,  45,  46,  47,  48,  49,  50, 
  /* CN   0 [19] */  54,  55,  56,  57,  59,  60,  63,  64,  65,  66,  67,  69,  70,  72,  73,  74,  75,  76,  77, 
  /* CN   1 [19] */   0,   2,   3,   4,   5,   7,   8,   9,  11,  12,  14,  15,  16,  17,  19,  21,  22,  23,  24, 
  /* CN   1 [19] */  27,  29,  30,  31,  32,  34,  35,  36,  38,  39,  41,  42,  43,  44,  46,  48,  49,  50,  51, 
  /* CN   1 [19] */  54,  56,  57,  58,  59,  61,  62,  63,  65,  66,  68,  69,  70,  71,  73,  75,  76,  77,  78, 
  /* CN   2 [19] */   0,   1,   2,   4,   5,   6,   7,   8,   9,  10,  13,  14,  15,  17,  18,  19,  20,  24,  25, 
  /* CN   2 [19] */  27,  28,  29,  31,  32,  33,  34,  35,  36,  37,  40,  41,  42,  44,  45,  46,  47,  51,  52, 
  /* CN   2 [19] */  54,  55,  56,  58,  59,  60,  61,  62,  63,  64,  67,  68,  69,  71,  72,  73,  74,  78,  79, 
  /* CN   3 [19] */   0,   1,   3,   4,   6,   7,   8,  10,  11,  12,  13,  14,  16,  17,  18,  20,  21,  22,  25, 
  /* CN   3 [19] */  27,  28,  30,  31,  33,  34,  35,  37,  38,  39,  40,  41,  43,  44,  45,  47,  48,  49,  52, 
  /* CN   3 [19] */  54,  55,  57,  58,  60,  61,  62,  64,  65,  66,  67,  68,  70,  71,  72,  74,  75,  76,  79, 
  /* CN   4 [3] */   0,   1,  26, 
  /* CN   4 [3] */  27,  28,  53, 
  /* CN   4 [3] */  54,  55,  80,
};


//
//
//
const sc_uint< N_QC > _GenericCoeffRotations[555] = {
  /* OFFSETS FOR FIRST ITERATION */
  /* CN   0 [19] */  74,  69,  50, 159, 100,  10,  59,  53, 110,  15,   9,  19,  23,  14,  35,  63,  31,   1,   0, 
  /* CN   0 [19] */  74,  69,  50, 159, 100,  10,  59,  53, 110,  15,   9,  19,  23,  14,  35,  63,  31,   1,   0, 
  /* CN   0 [19] */  74,  69,  50, 159, 100,  10,  59,  53, 110,  15,   9,  19,  23,  14,  35,  63,  31,   1,   0, 
  /* CN   1 [19] */ 104,  13, 134, 124, 147,  46, 104, 114, 110,  87, 109, 113, 119, 155,  44, 173, 175,   0,   0, 
  /* CN   1 [19] */ 104,  13, 134, 124, 147,  46, 104, 114, 110,  87, 109, 113, 119, 155,  44, 173, 175,   0,   0, 
  /* CN   1 [19] */ 104,  13, 134, 124, 147,  46, 104, 114, 110,  87, 109, 113, 119, 155,  44, 173, 175,   0,   0, 
  /* CN   2 [19] */ 104,  42, 122, 115,  46,  83,   7,  73,  98, 162, 133, 116,  93,  90,  15, 172,  54,   0,   0, 
  /* CN   2 [19] */ 104,  42, 122, 115,  46,  83,   7,  73,  98, 162, 133, 116,  93,  90,  15, 172,  54,   0,   0, 
  /* CN   2 [19] */ 104,  42, 122, 115,  46,  83,   7,  73,  98, 162, 133, 116,  93,  90,  15, 172,  54,   0,   0, 
  /* CN   3 [19] */  15, 154, 143, 133,  57,  78,  66,  97,  42, 144,  77, 162,  98,   7,  39,  27, 160,   1,   0, 
  /* CN   3 [19] */  15, 154, 143, 133,  57,  78,  66,  97,  42, 144,  77, 162,  98,   7,  39,  27, 160,   1,   0, 
  /* CN   3 [19] */  15, 154, 143, 133,  57,  78,  66,  97,  42, 144,  77, 162,  98,   7,  39,  27, 160,   1,   0, 
  /* CN   4 [3] */  36,  13,   0, 
  /* CN   4 [3] */  36,  13,   0, 
  /* CN   4 [3] */  36,  13,   0, 
  /* OFFSETS TO ALL THE OTHER DECODING ITERATIONS */
  /* CN   0 [19] */  93, 143,  41,  75, 159,  36, 140,  93,  24, 121, 142, 146, 135, 122, 136,  95,  19,   0,   0, 
  /* CN   0 [19] */  93, 143,  41,  75, 159,  36, 140,  93,  24, 121, 142, 146, 135, 122, 136,  95,  19,   0,   0, 
  /* CN   0 [19] */  93, 143,  41,  75, 159,  36, 140,  93,  24, 121, 142, 146, 135, 122, 136,  95,  19,   0,   0, 
  /* CN   1 [19] */ 104,  13, 134, 104, 147,  91,  37, 114, 110,  87,  74, 113, 119,  79,  44, 173, 175,   0,   0, 
  /* CN   1 [19] */ 104,  13, 134, 104, 147,  91,  37, 114, 110,  87,  74, 113, 119,  79,  44, 173, 175,   0,   0, 
  /* CN   1 [19] */ 104,  13, 134, 104, 147,  91,  37, 114, 110,  87,  74, 113, 119,  79,  44, 173, 175,   0,   0, 
  /* CN   2 [19] */ 104,  42, 122, 115,  46,  83,   7,  73,  98, 162, 133, 116,  93,  90,  15, 172,  54,   0,   0, 
  /* CN   2 [19] */ 104,  42, 122, 115,  46,  83,   7,  73,  98, 162, 133, 116,  93,  90,  15, 172,  54,   0,   0, 
  /* CN   2 [19] */ 104,  42, 122, 115,  46,  83,   7,  73,  98, 162, 133, 116,  93,  90,  15, 172,  54,   0,   0, 
  /* CN   3 [19] */  15, 154, 143, 133,  57,  78,  66,  97,  42, 144,  77, 162,  98,   7,  39,  27, 160,   1,   0, 
  /* CN   3 [19] */  15, 154, 143, 133,  57,  78,  66,  97,  42, 144,  77, 162,  98,   7,  39,  27, 160,   1,   0, 
  /* CN   3 [19] */  15, 154, 143, 133,  57,  78,  66,  97,  42, 144,  77, 162,  98,   7,  39,  27, 160,   1,   0, 
  /* CN   4 [3] */  36,  13,   0, 
  /* CN   4 [3] */  36,  13,   0, 
  /* CN   4 [3] */  36,  13,   0, 
  /* OFFSETS TO COME BACK 0 */
   19,  74, 167,  92, 156,  59,  26,  45, 109,  81,  40,  90, 106, 133, 141, 127, 112, 100, 108, 101,  32, 164, 175,   0,   0,   0,   0,  19,  74, 167,  92, 156,  59,  26,  45, 109,  81,  40,  90, 106, 133, 141, 127, 112, 100, 108, 101,  32, 164, 175,   0,   0,   0,   0,  19,  74, 167,  92, 156,  59,  26,  45, 109,  81,  40,  90, 106, 133, 141, 127, 112, 100, 108, 101,  32, 164, 175,   0,   0,   0,   0,
};

#endif //LDPC_STRUCTURE_H