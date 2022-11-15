#include "ldpc_ms_dec_v2.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../../shared/src/vector.h"
#include "./ldpc_code.h"


////////////////////
#define debug false
#if 0
void ldpc_ms_dec_v2::do_action()
{
	wait( );

	while( true ){

        TYPE_MSGS value = VECTOR_SET1( 0 );
        for (int i = 0; i < MESSAGE; i++) {
            var_mesgs[i] = value;
        }
		for (int i = 0; i < NOEUD; i++)
		{
			#pragma HLS PIPELINE
#if PAR_IO == false
            TYPE_LLRS value;
            for (int z = 0; z < Q; z++)
            {
            	value.range(LLR_BITS * (z + 1) - 1, LLR_BITS * z) = e1.read();
            }
            var_nodes[i] = value;
        	//SHOW( value,   "Channel" );
#else
            var_nodes[i] = e1.read();
            TYPE_LLRS c  = var_nodes[i];
        	//SHOW( c,   "Channel" );
#endif
		}

		for(int iterations = 0; iterations < MAX_ITERS; iterations += 1)
		{

			int ptr = 0;

			TYPE_LLRS tab_vContr[DEG_1];
			TYPE_MSGS tab_aContr[DEG_1];
			TYPE_BITS tab_sContr[DEG_1];

	        for (int i = 0; i < DEG_1_COMPUTATIONS; i++)
	        {
//#pragma HLS DATAFLOW
//#pragma HLS PIPELINE
//#pragma HLS UNROLL
	        	TYPE_BITS sign_somme = VECTOR_ZERO(  );
	        	TYPE_MSGS min1       = VECTOR_SET1( MSG_MAXV );
	        	TYPE_MSGS min2       = VECTOR_SET1( MSG_MAXV );
#if debug == true
	        	SHOW( sign_somme );
	        	SHOW( min1, "min_1" );
	        	SHOW( min2, "min_2" );
#endif
	            //
	            // ON UTILISE UNE PETITE ASTUCE AFIN D'ACCELERER LA SIMULATION DU DECODEUR
	            //
	            for (int j = 0; j < DEG_1; j++) {
#pragma HLS PIPELINE
#if debug == true
		        	printf("%d\n", j);
#endif
	            	const unsigned char posVN = PosBlocVNs    [ ptr ];
	            	const unsigned char rotat = CoeffRotations[ ptr ];
	            	const TYPE_LLRS vMessg    = var_mesgs     [ ptr ];
	            	const TYPE_LLRS vNoeud    = var_nodes     [ posVN ];
#if debug == true
		        	SHOW( vNoeud,   "vNoeud  " );
#endif
	            	const TYPE_LLRS rNoeud    = rotate_right( vNoeud, rotat );
#if debug == true
		        	SHOW( rNoeud,   "rNoeud  " );
#endif
	            	const TYPE_LLRS vContr    = VECTOR_SUB( rNoeud, vMessg);
#if debug == true
		        	SHOW( vContr,   "vContr  " );
#endif
	                const TYPE_MSGS absContr  = VECTOR_ABS (vContr);
#if debug == true
		        	SHOW( absContr, "absContr" );
#endif
	                const TYPE_BITS sigContr  = VECTOR_SIGN(vContr);
#if debug == true
		        	SHOW( sigContr, "sigContr" );
#endif
	                tab_vContr[j]             = vContr;
	                tab_aContr[j]             = absContr;
	                tab_sContr[j]             = sigContr;
#if debug == true
		        	SHOW( tab_sContr[j], "TABContr" );
#endif
	                TYPE_MSGS vTemp           = min1;
                    min1                      = VECTOR_MIN( absContr,        min1);
                    min2                      = VECTOR_MIN( absContr, vTemp, min2);
                    sign_somme                = VECTOR_XOR( sign_somme, sigContr );
#if debug == true
	        		SHOW( min1, "min_1" );
	        		SHOW( min2, "min_2" );
#endif
                    ptr += 1;
				}
	            ptr -= DEG_1;

		        const TYPE_MSGS cste_1 = min2;// - (min2 >> 2); //(i32_min2 - offset); cste_1 = (cste_1 < 0) ? 0 : cste_1;
		        const TYPE_MSGS cste_2 = min1;// - (min1 >> 2); //(i32_min  - offset); cste_2 = (cste_2 < 0) ? 0 : cste_2;
#if debug == true
		        printf("\n");
	        	SHOW( sign_somme, "signCN" );
	        	SHOW( cste_1, "cste_1" );
	        	SHOW( cste_2, "cste_2" );
#endif

		        for (int j = 0; j < DEG_1; j++) {
#pragma HLS PIPELINE
#if debug == true
		        	printf("%d\n", j);
#endif
		            const TYPE_LLRS vContr       = tab_vContr[j];
	                const TYPE_MSGS absContr     = tab_aContr[j];
	                const TYPE_BITS sigContr     = tab_sContr[j];
#if debug == true
		        	SHOW( vContr,   "vContr   " );
		        	SHOW( absContr, "absContr " );
		        	SHOW( sigContr, "sigContr " );
#endif
		        	const TYPE_BITS fSign        = VECTOR_EQUAL(absContr, min1);
		            TYPE_MSGS vResultat          = VECTOR_CMOV (fSign, cste_1, cste_2);
#if debug == true
		        	SHOW( vResultat, "vResultat" );
#endif
		            vResultat                    = VECTOR_SIGN(vResultat, VECTOR_XOR(sign_somme, sigContr));
#if debug == true
		        	SHOW( vResultat, "vResultat" );
#endif
		            var_mesgs            [ptr]   = vResultat;
	            	const unsigned char posVN    = PosBlocVNs[ ptr   ];
	            	const unsigned char rotat    = CoeffRotations[ ptr ];
		            TYPE_LLRS nLLR               = VECTOR_ADD(vContr, vResultat);
		            var_nodes[ posVN ]           = rotate_left( nLLR, rotat );
#if debug == true
		        	SHOW( nLLR,		 "new LLRs " );
#endif
                    ptr += 1;
	            }
#if debug == true
	            printf("\n\n");
#endif
	        }

#ifdef DEG_2_COMPUTATIONS

	        for (int i = 0; i < DEG_2_COMPUTATIONS; i++)
		    {
//#pragma HLS DATAFLOW
//#pragma HLS PIPELINE
//#pragma HLS UNROLL
	        	TYPE_BITS sign_somme = VECTOR_ZERO( );
		        TYPE_MSGS min1       = VECTOR_SET1( MSG_MAXV );
		        TYPE_MSGS min2       = VECTOR_SET1( MSG_MAXV );

		        for (int j = 0; j < DEG_2; j++) {
#pragma HLS PIPELINE
	            	const unsigned char posVN = PosBlocVNs    [ ptr ];
	            	const unsigned char rotat = CoeffRotations[ ptr ];
	            	const TYPE_LLRS vMessg    = var_mesgs     [ ptr ];
	            	const TYPE_LLRS vNoeud    = var_nodes     [ posVN ];
	            	const TYPE_LLRS rNoeud    = rotate_right( vNoeud, rotat );
	            	const TYPE_LLRS vContr    = VECTOR_SUB  ( rNoeud, vMessg);
		        	//SHOW( vContr );
	                const TYPE_MSGS absContr  = VECTOR_ABS (vContr);
	                const TYPE_BITS sigContr  = VECTOR_SIGN(vContr);
	                tab_vContr[j]             = vContr;
	                tab_aContr[j]             = absContr;
	                tab_sContr[j]             = sigContr;
	                TYPE_MSGS vTemp           = min1;
                    min1                      = VECTOR_MIN( absContr,        min1);
                    min2                      = VECTOR_MIN( absContr, vTemp, min2);
                    sign_somme                = VECTOR_XOR( sign_somme, sigContr );
                    ptr += 1;
		        }
	            ptr -= DEG_2;

	        	//SHOW( sign_somme );
		        const TYPE_MSGS cste_1 = min2;
		        const TYPE_MSGS cste_2 = min1;

		        for (int j = 0; j < DEG_2; j++) {
#pragma HLS PIPELINE
		            const TYPE_LLRS vContr       = tab_vContr[j];
	                const TYPE_MSGS absContr     = tab_aContr[j];
	                const TYPE_BITS sigContr     = tab_sContr[j];
	                const TYPE_BITS fSign        = VECTOR_EQUAL(absContr, min1);
		            TYPE_MSGS vResultat          = VECTOR_CMOV (fSign, cste_1, cste_2);
		            vResultat                    = VECTOR_SIGN(vResultat, VECTOR_XOR(sign_somme, sigContr));
		        	//SHOW( vResultat );
		            var_mesgs            [ptr]   = vResultat;
	            	const unsigned char posVN    = PosBlocVNs[ ptr   ];
	            	const unsigned char rotat    = CoeffRotations[ ptr ];
		            TYPE_LLRS nLLR               = VECTOR_ADD(vContr, vResultat);
		            var_nodes[ posVN ]           = rotate_left( nLLR, rotat );
                    ptr += 1;
		        }
	            //printf("\n\n");
//		        ptr += DEG_2;
		    }
#endif
		}

		for (int i = 0; i < NOEUD; i++) {
#pragma HLS PIPELINE
#if PAR_IO == false
            TYPE_BITS r = VECTOR_HARD(var_nodes[i]);
            for (int z = 0; z < Q; z++)
            {
                BIT b;
                b = (r[z] == 1);
                s1.write( b );
            }
#else
            s1.write( VECTOR_HARD(var_nodes[i]) );
#endif
		}
	}
}
#else
void ldpc_ms_dec_v2::do_action()
{
//	#pragma HLS resource core=AXI4Stream variable=e1
//	#pragma HLS resource core=AXI4Stream variable=s1
	while( true ){

        TYPE_MSGS value = VECTOR_SET1( 0 );
        for (int i = 0; i < MESSAGE; i++) {
            var_mesgs[i] = value;
        }

		for (int i = 0; i < NOEUD; i++)
		{
			#pragma HLS PIPELINE
#if PAR_IO == false
            TYPE_LLRS value;
            for (int z = 0; z < Q; z++)
            {
            	value.range(LLR_BITS * (z + 1) - 1, LLR_BITS * z) = e1.read();
            }
            var_nodes[i] = value;
        	//SHOW( value,   "Channel" );
#else
            var_nodes[i] = e1.read();
            TYPE_LLRS c  = var_nodes[i];
#endif
		}

		for(int iterations = 0; iterations < MAX_ITERS; iterations += 1)
		{

			unsigned short ptr = 0;

			TYPE_LLRS tab_vContr[DEG_1];
			TYPE_MSGS tab_aContr[DEG_1];
			TYPE_BITS tab_sContr[DEG_1];

	        for (int i = 0; i < _K; i++)
	        {

	        	TYPE_BITS sign_somme = VECTOR_ZERO(  );
	        	TYPE_MSGS min1       = VECTOR_SET1( MSG_MAXV );
	        	TYPE_MSGS min2       = VECTOR_SET1( MSG_MAXV );

	        	unsigned char deg_cn = DegreeCNs[i];
	            for (int j = 0; j < deg_cn; j++) {
#pragma HLS PIPELINE
	            	const unsigned char posVN = PosBlocVNs    [ ptr ];
	            	const unsigned char rotat = CoeffRotations[ ptr ];
	            	const TYPE_LLRS vMessg    = var_mesgs     [ ptr ];
	            	const TYPE_LLRS vNoeud    = var_nodes     [ posVN ];
	            	const TYPE_LLRS rNoeud    = rotate_right( vNoeud, rotat );
	            	const TYPE_LLRS vContr    = VECTOR_SUB( rNoeud, vMessg);
	                const TYPE_MSGS absContr  = VECTOR_ABS (vContr);
	                const TYPE_BITS sigContr  = VECTOR_SIGN(vContr);

	                tab_vContr[j]             = vContr;
	                tab_aContr[j]             = absContr;
	                tab_sContr[j]             = sigContr;

	                TYPE_MSGS vTemp           = min1;
                    min1                      = VECTOR_MIN( absContr,        min1);
                    min2                      = VECTOR_MIN( absContr, vTemp, min2);
                    sign_somme                = VECTOR_XOR( sign_somme, sigContr );

                    ptr += 1;
				}
	            ptr -= deg_cn;

		        const TYPE_MSGS cste_1 = min2;// - (min2 >> 2); //(i32_min2 - offset); cste_1 = (cste_1 < 0) ? 0 : cste_1;
		        const TYPE_MSGS cste_2 = min1;// - (min1 >> 2); //(i32_min  - offset); cste_2 = (cste_2 < 0) ? 0 : cste_2;

		        for (int j = 0; j < deg_cn; j++) {
#pragma HLS PIPELINE
		            const TYPE_LLRS vContr       = tab_vContr[j];
	                const TYPE_MSGS absContr     = tab_aContr[j];
	                const TYPE_BITS sigContr     = tab_sContr[j];

		        	const TYPE_BITS fSign        = VECTOR_EQUAL(absContr, min1);
		            TYPE_MSGS vResultat          = VECTOR_CMOV (fSign, cste_1, cste_2);

		            vResultat                    = VECTOR_SIGN(vResultat, VECTOR_XOR(sign_somme, sigContr));

		            var_mesgs            [ptr]   = vResultat;
	            	const unsigned char posVN    = PosBlocVNs[ ptr   ];
	            	const unsigned char rotat    = CoeffRotations[ ptr ];
		            TYPE_LLRS nLLR               = VECTOR_ADD(vContr, vResultat);
		            var_nodes[ posVN ]           = rotate_left( nLLR, rotat );

                    ptr += 1;
	            }
	        }
		}

		for (int i = 0; i < NOEUD; i++) {
#pragma HLS PIPELINE
#if PAR_IO == false
            TYPE_BITS r = VECTOR_HARD(var_nodes[i]);
            for (int z = 0; z < Q; z++)
            {
                BIT b;
                b = (r[z] == 1);
                s1.write( b );
            }
#else
            s1.write( VECTOR_HARD(var_nodes[i]) );
#endif
		}
	}
}
#endif
