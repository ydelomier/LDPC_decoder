/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "systemc.h"
#include "../module/config.h"
#include "../../../shared/src/vector.h"

SC_MODULE(wrapper_qc)          // module (class) declaration
{
	sc_fifo_in < LLR       > gen_to_wrap;
	sc_fifo_out< TYPE_LLRS > wrap_to_ldpc;

	sc_fifo_in < TYPE_BITS > ldpc_to_wrap;
	sc_fifo_out< BIT       > wrap_to_gen;

	SC_CTOR(wrapper_qc)
	{
		SC_THREAD(wrapper_qc_p1);
		SC_THREAD(wrapper_qc_p2);
	}

	void wrapper_qc_p1()           // process
	{
		int cnt = 0;
		while( true ){
			TYPE_LLRS c;

			for (int k = 0; k < QC; k++){
				LLR llr = gen_to_wrap.read();
				c.range(LLR_BITS * (k + 1) - 1, LLR_BITS * k) = llr;
			}
			//SHOW( c, "wrapper");
			wrap_to_ldpc.write( c );
		}
	}

	void wrapper_qc_p2()           // process
	{
	//	int cnt = 0;
		while( true ){
			TYPE_BITS c = ldpc_to_wrap.read();

			for (int k = 0; k < QC; k++){
				BIT ref     = c.test(k);
				wrap_to_gen.write( ref );
			}
		}
	}


};
