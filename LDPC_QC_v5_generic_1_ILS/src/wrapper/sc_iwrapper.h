#ifndef _sc_iwrapper_
#define _sc_iwrapper_

#include "systemc.h"

#ifdef __RTL_SIMULATION__
#include "config.h"
#include "ldpc_parameters.h"
#else
#include "../module/config.h"
#include "../module/ldpc_parameters.h"
#endif


SC_MODULE(sc_iwrapper)          // module (class) declaration
{
    sc_in <bool> clk;
    sc_in <bool> reset;

	sc_fifo_in < LLR       > e;
	sc_fifo_out< TYPE_LLRS > s1;
	sc_fifo_out< TYPE_LLRS > s2;

  // Config choice :
	  // CONFIG = 0 => QC = 27
	  // CONFIG = 1 => QC = 54
	  // CONFIG = 2 => QC = 81
	sc_in < sc_uint<8> > choice_conf;
	sc_in <sc_uint<10> > nb_frame;
	sc_in <sc_uint<10> > factor_z;

	SC_CTOR(sc_iwrapper)
	{
        SC_CTHREAD(do_gen, clk.pos());
        reset_signal_is(reset, true);
    }

private:
    void do_gen();

    LLR RAM[Zmax*_Nmax];
};

void sc_iwrapper::do_gen()           // process
{
	while( true ){
		sc_uint<8> CASE = choice_conf.read();
		int NFrame	 	= nb_frame.read();
		int _Z 			= factor_z.read();
		int size		= _Z[CASE];

		for (int i = 0; i < NFrame; i++)
		{
			for (int j = 0; j < size; j++)
			{
				#pragma HLS PIPELINE
				const unsigned int k = j * NFrame + i;
				RAM[k] = e.read();
			}
		}

		TYPE_LLRS c1;
		TYPE_LLRS c2;
		for (int i=0; i < _N; i++)
		{
			for (int j=0; j < Q; j++)
			{
				#pragma HLS PIPELINE
				LLR data = RAM[i*2*Q+j];
				if(j < Q)
					c2.range(LLR_BITS * (j+1) - 1, LLR_BITS * j) = data;
				else
					c1.range(LLR_BITS * (j-Q+1) - 1, LLR_BITS * (j-Q)) = data;
			}
	        s1.write( c1 );
	        s2.write( c2 );
		}

	}
}

#endif
