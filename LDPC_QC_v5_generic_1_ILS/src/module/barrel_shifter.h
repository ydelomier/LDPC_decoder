#ifndef _barrel_shifter_
#define _barrel_shifter_

#include "systemc.h"

#include "config.h"

#include "ldpc_parameters.h"

        SC_MODULE(barrel_shifter)
        {
            sc_in< TYPE_LLRS >	ibs_e;
            sc_in< unsigned char >	ibs_rot;
            sc_out< TYPE_LLRS >	ibs_s;

            SC_CTOR(barrel_shifter)
            {
                SC_METHOD(barrel_shifter_RIGHT);
                sensitive << ibs_e;
                sensitive << ibs_rot;
            }

        private:
            void barrel_shifter_RIGHT(){

             sc_uint< N_QC > c = ibs_rot.read();
             TYPE_LLRS a = ibs_e.read();
             TYPE_LLRS e;


            switch ( c ){
                case   0:  e = a; break;
                case   1 :  e = ((sc_bigint<  1 * LLR_BITS>)a.range(  1 * LLR_BITS - 1, 0), (sc_bigint<175 * LLR_BITS>)a.range(176 * LLR_BITS - 1,   1 * LLR_BITS)); break;
                case   2 :  e = ((sc_bigint<  2 * LLR_BITS>)a.range(  2 * LLR_BITS - 1, 0), (sc_bigint<174 * LLR_BITS>)a.range(176 * LLR_BITS - 1,   2 * LLR_BITS)); break;
                case   3 :  e = ((sc_bigint<  3 * LLR_BITS>)a.range(  3 * LLR_BITS - 1, 0), (sc_bigint<173 * LLR_BITS>)a.range(176 * LLR_BITS - 1,   3 * LLR_BITS)); break;
                case   4 :  e = ((sc_bigint<  4 * LLR_BITS>)a.range(  4 * LLR_BITS - 1, 0), (sc_bigint<172 * LLR_BITS>)a.range(176 * LLR_BITS - 1,   4 * LLR_BITS)); break;
                case   5 :  e = ((sc_bigint<  5 * LLR_BITS>)a.range(  5 * LLR_BITS - 1, 0), (sc_bigint<171 * LLR_BITS>)a.range(176 * LLR_BITS - 1,   5 * LLR_BITS)); break;
                case   6 :  e = ((sc_bigint<  6 * LLR_BITS>)a.range(  6 * LLR_BITS - 1, 0), (sc_bigint<170 * LLR_BITS>)a.range(176 * LLR_BITS - 1,   6 * LLR_BITS)); break;
                case   7 :  e = ((sc_bigint<  7 * LLR_BITS>)a.range(  7 * LLR_BITS - 1, 0), (sc_bigint<169 * LLR_BITS>)a.range(176 * LLR_BITS - 1,   7 * LLR_BITS)); break;
                case   8 :  e = ((sc_bigint<  8 * LLR_BITS>)a.range(  8 * LLR_BITS - 1, 0), (sc_bigint<168 * LLR_BITS>)a.range(176 * LLR_BITS - 1,   8 * LLR_BITS)); break;
                case   9 :  e = ((sc_bigint<  9 * LLR_BITS>)a.range(  9 * LLR_BITS - 1, 0), (sc_bigint<167 * LLR_BITS>)a.range(176 * LLR_BITS - 1,   9 * LLR_BITS)); break;
                case  10 :  e = ((sc_bigint< 10 * LLR_BITS>)a.range( 10 * LLR_BITS - 1, 0), (sc_bigint<166 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  10 * LLR_BITS)); break;
                case  11 :  e = ((sc_bigint< 11 * LLR_BITS>)a.range( 11 * LLR_BITS - 1, 0), (sc_bigint<165 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  11 * LLR_BITS)); break;
                case  12 :  e = ((sc_bigint< 12 * LLR_BITS>)a.range( 12 * LLR_BITS - 1, 0), (sc_bigint<164 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  12 * LLR_BITS)); break;
                case  13 :  e = ((sc_bigint< 13 * LLR_BITS>)a.range( 13 * LLR_BITS - 1, 0), (sc_bigint<163 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  13 * LLR_BITS)); break;
                case  14 :  e = ((sc_bigint< 14 * LLR_BITS>)a.range( 14 * LLR_BITS - 1, 0), (sc_bigint<162 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  14 * LLR_BITS)); break;
                case  15 :  e = ((sc_bigint< 15 * LLR_BITS>)a.range( 15 * LLR_BITS - 1, 0), (sc_bigint<161 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  15 * LLR_BITS)); break;
                case  16 :  e = ((sc_bigint< 16 * LLR_BITS>)a.range( 16 * LLR_BITS - 1, 0), (sc_bigint<160 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  16 * LLR_BITS)); break;
                case  17 :  e = ((sc_bigint< 17 * LLR_BITS>)a.range( 17 * LLR_BITS - 1, 0), (sc_bigint<159 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  17 * LLR_BITS)); break;
                case  18 :  e = ((sc_bigint< 18 * LLR_BITS>)a.range( 18 * LLR_BITS - 1, 0), (sc_bigint<158 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  18 * LLR_BITS)); break;
                case  19 :  e = ((sc_bigint< 19 * LLR_BITS>)a.range( 19 * LLR_BITS - 1, 0), (sc_bigint<157 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  19 * LLR_BITS)); break;
                case  20 :  e = ((sc_bigint< 20 * LLR_BITS>)a.range( 20 * LLR_BITS - 1, 0), (sc_bigint<156 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  20 * LLR_BITS)); break;
                case  21 :  e = ((sc_bigint< 21 * LLR_BITS>)a.range( 21 * LLR_BITS - 1, 0), (sc_bigint<155 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  21 * LLR_BITS)); break;
                case  22 :  e = ((sc_bigint< 22 * LLR_BITS>)a.range( 22 * LLR_BITS - 1, 0), (sc_bigint<154 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  22 * LLR_BITS)); break;
                case  23 :  e = ((sc_bigint< 23 * LLR_BITS>)a.range( 23 * LLR_BITS - 1, 0), (sc_bigint<153 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  23 * LLR_BITS)); break;
                case  24 :  e = ((sc_bigint< 24 * LLR_BITS>)a.range( 24 * LLR_BITS - 1, 0), (sc_bigint<152 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  24 * LLR_BITS)); break;
                case  25 :  e = ((sc_bigint< 25 * LLR_BITS>)a.range( 25 * LLR_BITS - 1, 0), (sc_bigint<151 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  25 * LLR_BITS)); break;
                case  26 :  e = ((sc_bigint< 26 * LLR_BITS>)a.range( 26 * LLR_BITS - 1, 0), (sc_bigint<150 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  26 * LLR_BITS)); break;
                case  27 :  e = ((sc_bigint< 27 * LLR_BITS>)a.range( 27 * LLR_BITS - 1, 0), (sc_bigint<149 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  27 * LLR_BITS)); break;
                case  28 :  e = ((sc_bigint< 28 * LLR_BITS>)a.range( 28 * LLR_BITS - 1, 0), (sc_bigint<148 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  28 * LLR_BITS)); break;
                case  29 :  e = ((sc_bigint< 29 * LLR_BITS>)a.range( 29 * LLR_BITS - 1, 0), (sc_bigint<147 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  29 * LLR_BITS)); break;
                case  30 :  e = ((sc_bigint< 30 * LLR_BITS>)a.range( 30 * LLR_BITS - 1, 0), (sc_bigint<146 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  30 * LLR_BITS)); break;
                case  31 :  e = ((sc_bigint< 31 * LLR_BITS>)a.range( 31 * LLR_BITS - 1, 0), (sc_bigint<145 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  31 * LLR_BITS)); break;
                case  32 :  e = ((sc_bigint< 32 * LLR_BITS>)a.range( 32 * LLR_BITS - 1, 0), (sc_bigint<144 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  32 * LLR_BITS)); break;
                case  33 :  e = ((sc_bigint< 33 * LLR_BITS>)a.range( 33 * LLR_BITS - 1, 0), (sc_bigint<143 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  33 * LLR_BITS)); break;
                case  34 :  e = ((sc_bigint< 34 * LLR_BITS>)a.range( 34 * LLR_BITS - 1, 0), (sc_bigint<142 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  34 * LLR_BITS)); break;
                case  35 :  e = ((sc_bigint< 35 * LLR_BITS>)a.range( 35 * LLR_BITS - 1, 0), (sc_bigint<141 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  35 * LLR_BITS)); break;
                case  36 :  e = ((sc_bigint< 36 * LLR_BITS>)a.range( 36 * LLR_BITS - 1, 0), (sc_bigint<140 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  36 * LLR_BITS)); break;
                case  37 :  e = ((sc_bigint< 37 * LLR_BITS>)a.range( 37 * LLR_BITS - 1, 0), (sc_bigint<139 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  37 * LLR_BITS)); break;
                case  38 :  e = ((sc_bigint< 38 * LLR_BITS>)a.range( 38 * LLR_BITS - 1, 0), (sc_bigint<138 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  38 * LLR_BITS)); break;
                case  39 :  e = ((sc_bigint< 39 * LLR_BITS>)a.range( 39 * LLR_BITS - 1, 0), (sc_bigint<137 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  39 * LLR_BITS)); break;
                case  40 :  e = ((sc_bigint< 40 * LLR_BITS>)a.range( 40 * LLR_BITS - 1, 0), (sc_bigint<136 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  40 * LLR_BITS)); break;
                case  41 :  e = ((sc_bigint< 41 * LLR_BITS>)a.range( 41 * LLR_BITS - 1, 0), (sc_bigint<135 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  41 * LLR_BITS)); break;
                case  42 :  e = ((sc_bigint< 42 * LLR_BITS>)a.range( 42 * LLR_BITS - 1, 0), (sc_bigint<134 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  42 * LLR_BITS)); break;
                case  43 :  e = ((sc_bigint< 43 * LLR_BITS>)a.range( 43 * LLR_BITS - 1, 0), (sc_bigint<133 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  43 * LLR_BITS)); break;
                case  44 :  e = ((sc_bigint< 44 * LLR_BITS>)a.range( 44 * LLR_BITS - 1, 0), (sc_bigint<132 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  44 * LLR_BITS)); break;
                case  45 :  e = ((sc_bigint< 45 * LLR_BITS>)a.range( 45 * LLR_BITS - 1, 0), (sc_bigint<131 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  45 * LLR_BITS)); break;
                case  46 :  e = ((sc_bigint< 46 * LLR_BITS>)a.range( 46 * LLR_BITS - 1, 0), (sc_bigint<130 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  46 * LLR_BITS)); break;
                case  47 :  e = ((sc_bigint< 47 * LLR_BITS>)a.range( 47 * LLR_BITS - 1, 0), (sc_bigint<129 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  47 * LLR_BITS)); break;
                case  48 :  e = ((sc_bigint< 48 * LLR_BITS>)a.range( 48 * LLR_BITS - 1, 0), (sc_bigint<128 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  48 * LLR_BITS)); break;
                case  49 :  e = ((sc_bigint< 49 * LLR_BITS>)a.range( 49 * LLR_BITS - 1, 0), (sc_bigint<127 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  49 * LLR_BITS)); break;
                case  50 :  e = ((sc_bigint< 50 * LLR_BITS>)a.range( 50 * LLR_BITS - 1, 0), (sc_bigint<126 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  50 * LLR_BITS)); break;
                case  51 :  e = ((sc_bigint< 51 * LLR_BITS>)a.range( 51 * LLR_BITS - 1, 0), (sc_bigint<125 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  51 * LLR_BITS)); break;
                case  52 :  e = ((sc_bigint< 52 * LLR_BITS>)a.range( 52 * LLR_BITS - 1, 0), (sc_bigint<124 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  52 * LLR_BITS)); break;
                case  53 :  e = ((sc_bigint< 53 * LLR_BITS>)a.range( 53 * LLR_BITS - 1, 0), (sc_bigint<123 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  53 * LLR_BITS)); break;
                case  54 :  e = ((sc_bigint< 54 * LLR_BITS>)a.range( 54 * LLR_BITS - 1, 0), (sc_bigint<122 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  54 * LLR_BITS)); break;
                case  55 :  e = ((sc_bigint< 55 * LLR_BITS>)a.range( 55 * LLR_BITS - 1, 0), (sc_bigint<121 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  55 * LLR_BITS)); break;
                case  56 :  e = ((sc_bigint< 56 * LLR_BITS>)a.range( 56 * LLR_BITS - 1, 0), (sc_bigint<120 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  56 * LLR_BITS)); break;
                case  57 :  e = ((sc_bigint< 57 * LLR_BITS>)a.range( 57 * LLR_BITS - 1, 0), (sc_bigint<119 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  57 * LLR_BITS)); break;
                case  58 :  e = ((sc_bigint< 58 * LLR_BITS>)a.range( 58 * LLR_BITS - 1, 0), (sc_bigint<118 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  58 * LLR_BITS)); break;
                case  59 :  e = ((sc_bigint< 59 * LLR_BITS>)a.range( 59 * LLR_BITS - 1, 0), (sc_bigint<117 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  59 * LLR_BITS)); break;
                case  60 :  e = ((sc_bigint< 60 * LLR_BITS>)a.range( 60 * LLR_BITS - 1, 0), (sc_bigint<116 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  60 * LLR_BITS)); break;
                case  61 :  e = ((sc_bigint< 61 * LLR_BITS>)a.range( 61 * LLR_BITS - 1, 0), (sc_bigint<115 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  61 * LLR_BITS)); break;
                case  62 :  e = ((sc_bigint< 62 * LLR_BITS>)a.range( 62 * LLR_BITS - 1, 0), (sc_bigint<114 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  62 * LLR_BITS)); break;
                case  63 :  e = ((sc_bigint< 63 * LLR_BITS>)a.range( 63 * LLR_BITS - 1, 0), (sc_bigint<113 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  63 * LLR_BITS)); break;
                case  64 :  e = ((sc_bigint< 64 * LLR_BITS>)a.range( 64 * LLR_BITS - 1, 0), (sc_bigint<112 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  64 * LLR_BITS)); break;
                case  65 :  e = ((sc_bigint< 65 * LLR_BITS>)a.range( 65 * LLR_BITS - 1, 0), (sc_bigint<111 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  65 * LLR_BITS)); break;
                case  66 :  e = ((sc_bigint< 66 * LLR_BITS>)a.range( 66 * LLR_BITS - 1, 0), (sc_bigint<110 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  66 * LLR_BITS)); break;
                case  67 :  e = ((sc_bigint< 67 * LLR_BITS>)a.range( 67 * LLR_BITS - 1, 0), (sc_bigint<109 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  67 * LLR_BITS)); break;
                case  68 :  e = ((sc_bigint< 68 * LLR_BITS>)a.range( 68 * LLR_BITS - 1, 0), (sc_bigint<108 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  68 * LLR_BITS)); break;
                case  69 :  e = ((sc_bigint< 69 * LLR_BITS>)a.range( 69 * LLR_BITS - 1, 0), (sc_bigint<107 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  69 * LLR_BITS)); break;
                case  70 :  e = ((sc_bigint< 70 * LLR_BITS>)a.range( 70 * LLR_BITS - 1, 0), (sc_bigint<106 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  70 * LLR_BITS)); break;
                case  71 :  e = ((sc_bigint< 71 * LLR_BITS>)a.range( 71 * LLR_BITS - 1, 0), (sc_bigint<105 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  71 * LLR_BITS)); break;
                case  72 :  e = ((sc_bigint< 72 * LLR_BITS>)a.range( 72 * LLR_BITS - 1, 0), (sc_bigint<104 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  72 * LLR_BITS)); break;
                case  73 :  e = ((sc_bigint< 73 * LLR_BITS>)a.range( 73 * LLR_BITS - 1, 0), (sc_bigint<103 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  73 * LLR_BITS)); break;
                case  74 :  e = ((sc_bigint< 74 * LLR_BITS>)a.range( 74 * LLR_BITS - 1, 0), (sc_bigint<102 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  74 * LLR_BITS)); break;
                case  75 :  e = ((sc_bigint< 75 * LLR_BITS>)a.range( 75 * LLR_BITS - 1, 0), (sc_bigint<101 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  75 * LLR_BITS)); break;
                case  76 :  e = ((sc_bigint< 76 * LLR_BITS>)a.range( 76 * LLR_BITS - 1, 0), (sc_bigint<100 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  76 * LLR_BITS)); break;
                case  77 :  e = ((sc_bigint< 77 * LLR_BITS>)a.range( 77 * LLR_BITS - 1, 0), (sc_bigint< 99 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  77 * LLR_BITS)); break;
                case  78 :  e = ((sc_bigint< 78 * LLR_BITS>)a.range( 78 * LLR_BITS - 1, 0), (sc_bigint< 98 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  78 * LLR_BITS)); break;
                case  79 :  e = ((sc_bigint< 79 * LLR_BITS>)a.range( 79 * LLR_BITS - 1, 0), (sc_bigint< 97 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  79 * LLR_BITS)); break;
                case  80 :  e = ((sc_bigint< 80 * LLR_BITS>)a.range( 80 * LLR_BITS - 1, 0), (sc_bigint< 96 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  80 * LLR_BITS)); break;
                case  81 :  e = ((sc_bigint< 81 * LLR_BITS>)a.range( 81 * LLR_BITS - 1, 0), (sc_bigint< 95 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  81 * LLR_BITS)); break;
                case  82 :  e = ((sc_bigint< 82 * LLR_BITS>)a.range( 82 * LLR_BITS - 1, 0), (sc_bigint< 94 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  82 * LLR_BITS)); break;
                case  83 :  e = ((sc_bigint< 83 * LLR_BITS>)a.range( 83 * LLR_BITS - 1, 0), (sc_bigint< 93 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  83 * LLR_BITS)); break;
                case  84 :  e = ((sc_bigint< 84 * LLR_BITS>)a.range( 84 * LLR_BITS - 1, 0), (sc_bigint< 92 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  84 * LLR_BITS)); break;
                case  85 :  e = ((sc_bigint< 85 * LLR_BITS>)a.range( 85 * LLR_BITS - 1, 0), (sc_bigint< 91 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  85 * LLR_BITS)); break;
                case  86 :  e = ((sc_bigint< 86 * LLR_BITS>)a.range( 86 * LLR_BITS - 1, 0), (sc_bigint< 90 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  86 * LLR_BITS)); break;
                case  87 :  e = ((sc_bigint< 87 * LLR_BITS>)a.range( 87 * LLR_BITS - 1, 0), (sc_bigint< 89 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  87 * LLR_BITS)); break;
                case  88 :  e = ((sc_bigint< 88 * LLR_BITS>)a.range( 88 * LLR_BITS - 1, 0), (sc_bigint< 88 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  88 * LLR_BITS)); break;
                case  89 :  e = ((sc_bigint< 89 * LLR_BITS>)a.range( 89 * LLR_BITS - 1, 0), (sc_bigint< 87 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  89 * LLR_BITS)); break;
                case  90 :  e = ((sc_bigint< 90 * LLR_BITS>)a.range( 90 * LLR_BITS - 1, 0), (sc_bigint< 86 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  90 * LLR_BITS)); break;
                case  91 :  e = ((sc_bigint< 91 * LLR_BITS>)a.range( 91 * LLR_BITS - 1, 0), (sc_bigint< 85 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  91 * LLR_BITS)); break;
                case  92 :  e = ((sc_bigint< 92 * LLR_BITS>)a.range( 92 * LLR_BITS - 1, 0), (sc_bigint< 84 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  92 * LLR_BITS)); break;
                case  93 :  e = ((sc_bigint< 93 * LLR_BITS>)a.range( 93 * LLR_BITS - 1, 0), (sc_bigint< 83 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  93 * LLR_BITS)); break;
                case  94 :  e = ((sc_bigint< 94 * LLR_BITS>)a.range( 94 * LLR_BITS - 1, 0), (sc_bigint< 82 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  94 * LLR_BITS)); break;
                case  95 :  e = ((sc_bigint< 95 * LLR_BITS>)a.range( 95 * LLR_BITS - 1, 0), (sc_bigint< 81 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  95 * LLR_BITS)); break;
                case  96 :  e = ((sc_bigint< 96 * LLR_BITS>)a.range( 96 * LLR_BITS - 1, 0), (sc_bigint< 80 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  96 * LLR_BITS)); break;
                case  97 :  e = ((sc_bigint< 97 * LLR_BITS>)a.range( 97 * LLR_BITS - 1, 0), (sc_bigint< 79 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  97 * LLR_BITS)); break;
                case  98 :  e = ((sc_bigint< 98 * LLR_BITS>)a.range( 98 * LLR_BITS - 1, 0), (sc_bigint< 78 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  98 * LLR_BITS)); break;
                case  99 :  e = ((sc_bigint< 99 * LLR_BITS>)a.range( 99 * LLR_BITS - 1, 0), (sc_bigint< 77 * LLR_BITS>)a.range(176 * LLR_BITS - 1,  99 * LLR_BITS)); break;
                case 100 :  e = ((sc_bigint<100 * LLR_BITS>)a.range(100 * LLR_BITS - 1, 0), (sc_bigint< 76 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 100 * LLR_BITS)); break;
                case 101 :  e = ((sc_bigint<101 * LLR_BITS>)a.range(101 * LLR_BITS - 1, 0), (sc_bigint< 75 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 101 * LLR_BITS)); break;
                case 102 :  e = ((sc_bigint<102 * LLR_BITS>)a.range(102 * LLR_BITS - 1, 0), (sc_bigint< 74 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 102 * LLR_BITS)); break;
                case 103 :  e = ((sc_bigint<103 * LLR_BITS>)a.range(103 * LLR_BITS - 1, 0), (sc_bigint< 73 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 103 * LLR_BITS)); break;
                case 104 :  e = ((sc_bigint<104 * LLR_BITS>)a.range(104 * LLR_BITS - 1, 0), (sc_bigint< 72 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 104 * LLR_BITS)); break;
                case 105 :  e = ((sc_bigint<105 * LLR_BITS>)a.range(105 * LLR_BITS - 1, 0), (sc_bigint< 71 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 105 * LLR_BITS)); break;
                case 106 :  e = ((sc_bigint<106 * LLR_BITS>)a.range(106 * LLR_BITS - 1, 0), (sc_bigint< 70 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 106 * LLR_BITS)); break;
                case 107 :  e = ((sc_bigint<107 * LLR_BITS>)a.range(107 * LLR_BITS - 1, 0), (sc_bigint< 69 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 107 * LLR_BITS)); break;
                case 108 :  e = ((sc_bigint<108 * LLR_BITS>)a.range(108 * LLR_BITS - 1, 0), (sc_bigint< 68 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 108 * LLR_BITS)); break;
                case 109 :  e = ((sc_bigint<109 * LLR_BITS>)a.range(109 * LLR_BITS - 1, 0), (sc_bigint< 67 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 109 * LLR_BITS)); break;
                case 110 :  e = ((sc_bigint<110 * LLR_BITS>)a.range(110 * LLR_BITS - 1, 0), (sc_bigint< 66 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 110 * LLR_BITS)); break;
                case 111 :  e = ((sc_bigint<111 * LLR_BITS>)a.range(111 * LLR_BITS - 1, 0), (sc_bigint< 65 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 111 * LLR_BITS)); break;
                case 112 :  e = ((sc_bigint<112 * LLR_BITS>)a.range(112 * LLR_BITS - 1, 0), (sc_bigint< 64 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 112 * LLR_BITS)); break;
                case 113 :  e = ((sc_bigint<113 * LLR_BITS>)a.range(113 * LLR_BITS - 1, 0), (sc_bigint< 63 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 113 * LLR_BITS)); break;
                case 114 :  e = ((sc_bigint<114 * LLR_BITS>)a.range(114 * LLR_BITS - 1, 0), (sc_bigint< 62 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 114 * LLR_BITS)); break;
                case 115 :  e = ((sc_bigint<115 * LLR_BITS>)a.range(115 * LLR_BITS - 1, 0), (sc_bigint< 61 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 115 * LLR_BITS)); break;
                case 116 :  e = ((sc_bigint<116 * LLR_BITS>)a.range(116 * LLR_BITS - 1, 0), (sc_bigint< 60 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 116 * LLR_BITS)); break;
                case 117 :  e = ((sc_bigint<117 * LLR_BITS>)a.range(117 * LLR_BITS - 1, 0), (sc_bigint< 59 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 117 * LLR_BITS)); break;
                case 118 :  e = ((sc_bigint<118 * LLR_BITS>)a.range(118 * LLR_BITS - 1, 0), (sc_bigint< 58 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 118 * LLR_BITS)); break;
                case 119 :  e = ((sc_bigint<119 * LLR_BITS>)a.range(119 * LLR_BITS - 1, 0), (sc_bigint< 57 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 119 * LLR_BITS)); break;
                case 120 :  e = ((sc_bigint<120 * LLR_BITS>)a.range(120 * LLR_BITS - 1, 0), (sc_bigint< 56 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 120 * LLR_BITS)); break;
                case 121 :  e = ((sc_bigint<121 * LLR_BITS>)a.range(121 * LLR_BITS - 1, 0), (sc_bigint< 55 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 121 * LLR_BITS)); break;
                case 122 :  e = ((sc_bigint<122 * LLR_BITS>)a.range(122 * LLR_BITS - 1, 0), (sc_bigint< 54 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 122 * LLR_BITS)); break;
                case 123 :  e = ((sc_bigint<123 * LLR_BITS>)a.range(123 * LLR_BITS - 1, 0), (sc_bigint< 53 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 123 * LLR_BITS)); break;
                case 124 :  e = ((sc_bigint<124 * LLR_BITS>)a.range(124 * LLR_BITS - 1, 0), (sc_bigint< 52 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 124 * LLR_BITS)); break;
                case 125 :  e = ((sc_bigint<125 * LLR_BITS>)a.range(125 * LLR_BITS - 1, 0), (sc_bigint< 51 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 125 * LLR_BITS)); break;
                case 126 :  e = ((sc_bigint<126 * LLR_BITS>)a.range(126 * LLR_BITS - 1, 0), (sc_bigint< 50 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 126 * LLR_BITS)); break;
                case 127 :  e = ((sc_bigint<127 * LLR_BITS>)a.range(127 * LLR_BITS - 1, 0), (sc_bigint< 49 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 127 * LLR_BITS)); break;
                case 128 :  e = ((sc_bigint<128 * LLR_BITS>)a.range(128 * LLR_BITS - 1, 0), (sc_bigint< 48 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 128 * LLR_BITS)); break;
                case 129 :  e = ((sc_bigint<129 * LLR_BITS>)a.range(129 * LLR_BITS - 1, 0), (sc_bigint< 47 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 129 * LLR_BITS)); break;
                case 130 :  e = ((sc_bigint<130 * LLR_BITS>)a.range(130 * LLR_BITS - 1, 0), (sc_bigint< 46 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 130 * LLR_BITS)); break;
                case 131 :  e = ((sc_bigint<131 * LLR_BITS>)a.range(131 * LLR_BITS - 1, 0), (sc_bigint< 45 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 131 * LLR_BITS)); break;
                case 132 :  e = ((sc_bigint<132 * LLR_BITS>)a.range(132 * LLR_BITS - 1, 0), (sc_bigint< 44 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 132 * LLR_BITS)); break;
                case 133 :  e = ((sc_bigint<133 * LLR_BITS>)a.range(133 * LLR_BITS - 1, 0), (sc_bigint< 43 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 133 * LLR_BITS)); break;
                case 134 :  e = ((sc_bigint<134 * LLR_BITS>)a.range(134 * LLR_BITS - 1, 0), (sc_bigint< 42 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 134 * LLR_BITS)); break;
                case 135 :  e = ((sc_bigint<135 * LLR_BITS>)a.range(135 * LLR_BITS - 1, 0), (sc_bigint< 41 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 135 * LLR_BITS)); break;
                case 136 :  e = ((sc_bigint<136 * LLR_BITS>)a.range(136 * LLR_BITS - 1, 0), (sc_bigint< 40 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 136 * LLR_BITS)); break;
                case 137 :  e = ((sc_bigint<137 * LLR_BITS>)a.range(137 * LLR_BITS - 1, 0), (sc_bigint< 39 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 137 * LLR_BITS)); break;
                case 138 :  e = ((sc_bigint<138 * LLR_BITS>)a.range(138 * LLR_BITS - 1, 0), (sc_bigint< 38 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 138 * LLR_BITS)); break;
                case 139 :  e = ((sc_bigint<139 * LLR_BITS>)a.range(139 * LLR_BITS - 1, 0), (sc_bigint< 37 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 139 * LLR_BITS)); break;
                case 140 :  e = ((sc_bigint<140 * LLR_BITS>)a.range(140 * LLR_BITS - 1, 0), (sc_bigint< 36 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 140 * LLR_BITS)); break;
                case 141 :  e = ((sc_bigint<141 * LLR_BITS>)a.range(141 * LLR_BITS - 1, 0), (sc_bigint< 35 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 141 * LLR_BITS)); break;
                case 142 :  e = ((sc_bigint<142 * LLR_BITS>)a.range(142 * LLR_BITS - 1, 0), (sc_bigint< 34 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 142 * LLR_BITS)); break;
                case 143 :  e = ((sc_bigint<143 * LLR_BITS>)a.range(143 * LLR_BITS - 1, 0), (sc_bigint< 33 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 143 * LLR_BITS)); break;
                case 144 :  e = ((sc_bigint<144 * LLR_BITS>)a.range(144 * LLR_BITS - 1, 0), (sc_bigint< 32 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 144 * LLR_BITS)); break;
                case 145 :  e = ((sc_bigint<145 * LLR_BITS>)a.range(145 * LLR_BITS - 1, 0), (sc_bigint< 31 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 145 * LLR_BITS)); break;
                case 146 :  e = ((sc_bigint<146 * LLR_BITS>)a.range(146 * LLR_BITS - 1, 0), (sc_bigint< 30 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 146 * LLR_BITS)); break;
                case 147 :  e = ((sc_bigint<147 * LLR_BITS>)a.range(147 * LLR_BITS - 1, 0), (sc_bigint< 29 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 147 * LLR_BITS)); break;
                case 148 :  e = ((sc_bigint<148 * LLR_BITS>)a.range(148 * LLR_BITS - 1, 0), (sc_bigint< 28 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 148 * LLR_BITS)); break;
                case 149 :  e = ((sc_bigint<149 * LLR_BITS>)a.range(149 * LLR_BITS - 1, 0), (sc_bigint< 27 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 149 * LLR_BITS)); break;
                case 150 :  e = ((sc_bigint<150 * LLR_BITS>)a.range(150 * LLR_BITS - 1, 0), (sc_bigint< 26 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 150 * LLR_BITS)); break;
                case 151 :  e = ((sc_bigint<151 * LLR_BITS>)a.range(151 * LLR_BITS - 1, 0), (sc_bigint< 25 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 151 * LLR_BITS)); break;
                case 152 :  e = ((sc_bigint<152 * LLR_BITS>)a.range(152 * LLR_BITS - 1, 0), (sc_bigint< 24 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 152 * LLR_BITS)); break;
                case 153 :  e = ((sc_bigint<153 * LLR_BITS>)a.range(153 * LLR_BITS - 1, 0), (sc_bigint< 23 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 153 * LLR_BITS)); break;
                case 154 :  e = ((sc_bigint<154 * LLR_BITS>)a.range(154 * LLR_BITS - 1, 0), (sc_bigint< 22 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 154 * LLR_BITS)); break;
                case 155 :  e = ((sc_bigint<155 * LLR_BITS>)a.range(155 * LLR_BITS - 1, 0), (sc_bigint< 21 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 155 * LLR_BITS)); break;
                case 156 :  e = ((sc_bigint<156 * LLR_BITS>)a.range(156 * LLR_BITS - 1, 0), (sc_bigint< 20 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 156 * LLR_BITS)); break;
                case 157 :  e = ((sc_bigint<157 * LLR_BITS>)a.range(157 * LLR_BITS - 1, 0), (sc_bigint< 19 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 157 * LLR_BITS)); break;
                case 158 :  e = ((sc_bigint<158 * LLR_BITS>)a.range(158 * LLR_BITS - 1, 0), (sc_bigint< 18 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 158 * LLR_BITS)); break;
                case 159 :  e = ((sc_bigint<159 * LLR_BITS>)a.range(159 * LLR_BITS - 1, 0), (sc_bigint< 17 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 159 * LLR_BITS)); break;
                case 160 :  e = ((sc_bigint<160 * LLR_BITS>)a.range(160 * LLR_BITS - 1, 0), (sc_bigint< 16 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 160 * LLR_BITS)); break;
                case 161 :  e = ((sc_bigint<161 * LLR_BITS>)a.range(161 * LLR_BITS - 1, 0), (sc_bigint< 15 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 161 * LLR_BITS)); break;
                case 162 :  e = ((sc_bigint<162 * LLR_BITS>)a.range(162 * LLR_BITS - 1, 0), (sc_bigint< 14 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 162 * LLR_BITS)); break;
                case 163 :  e = ((sc_bigint<163 * LLR_BITS>)a.range(163 * LLR_BITS - 1, 0), (sc_bigint< 13 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 163 * LLR_BITS)); break;
                case 164 :  e = ((sc_bigint<164 * LLR_BITS>)a.range(164 * LLR_BITS - 1, 0), (sc_bigint< 12 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 164 * LLR_BITS)); break;
                case 165 :  e = ((sc_bigint<165 * LLR_BITS>)a.range(165 * LLR_BITS - 1, 0), (sc_bigint< 11 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 165 * LLR_BITS)); break;
                case 166 :  e = ((sc_bigint<166 * LLR_BITS>)a.range(166 * LLR_BITS - 1, 0), (sc_bigint< 10 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 166 * LLR_BITS)); break;
                case 167 :  e = ((sc_bigint<167 * LLR_BITS>)a.range(167 * LLR_BITS - 1, 0), (sc_bigint<  9 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 167 * LLR_BITS)); break;
                case 168 :  e = ((sc_bigint<168 * LLR_BITS>)a.range(168 * LLR_BITS - 1, 0), (sc_bigint<  8 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 168 * LLR_BITS)); break;
                case 169 :  e = ((sc_bigint<169 * LLR_BITS>)a.range(169 * LLR_BITS - 1, 0), (sc_bigint<  7 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 169 * LLR_BITS)); break;
                case 170 :  e = ((sc_bigint<170 * LLR_BITS>)a.range(170 * LLR_BITS - 1, 0), (sc_bigint<  6 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 170 * LLR_BITS)); break;
                case 171 :  e = ((sc_bigint<171 * LLR_BITS>)a.range(171 * LLR_BITS - 1, 0), (sc_bigint<  5 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 171 * LLR_BITS)); break;
                case 172 :  e = ((sc_bigint<172 * LLR_BITS>)a.range(172 * LLR_BITS - 1, 0), (sc_bigint<  4 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 172 * LLR_BITS)); break;
                case 173 :  e = ((sc_bigint<173 * LLR_BITS>)a.range(173 * LLR_BITS - 1, 0), (sc_bigint<  3 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 173 * LLR_BITS)); break;
                case 174 :  e = ((sc_bigint<174 * LLR_BITS>)a.range(174 * LLR_BITS - 1, 0), (sc_bigint<  2 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 174 * LLR_BITS)); break;
                case 175 :  e = ((sc_bigint<175 * LLR_BITS>)a.range(175 * LLR_BITS - 1, 0), (sc_bigint<  1 * LLR_BITS>)a.range(176 * LLR_BITS - 1, 175 * LLR_BITS)); break;
                default: e = a; break;
            }
        ibs_s.write(e);
    }
};
#endif 
