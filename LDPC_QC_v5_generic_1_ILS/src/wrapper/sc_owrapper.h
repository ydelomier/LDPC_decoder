/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "systemc.h"
#ifdef __RTL_SIMULATION__
#include "config.h"
#include "generic_parameters.h"
#include "ldpc_parameters_generic.h"
#else
#include "../module/config.h"
#include "../module/ldpc_parameters.h"
#endif

SC_MODULE(sc_owrapper)          // module (class) declaration
{
    sc_in <bool> clk;
    sc_in <bool> reset;

	sc_fifo_in < TYPE_BITS > e1;
	sc_fifo_in < TYPE_BITS > e2;
	sc_fifo_out< BIT       > s;

  // Config choice :
	  // choice_conf = 0 => QC = 27
	  // choice_conf = 1 => QC = 54
	  // choice_conf = 2 => QC = 81
	sc_in < sc_uint<8> > choice_conf;
	sc_in <sc_uint<10> > nb_frame;

	SC_CTOR(sc_owrapper)
	{
        SC_CTHREAD(do_gen, clk.pos());
        reset_signal_is(reset, true);
    }

private:
    void do_gen();

    BIT RAM[2*Q*_N];
    TYPE_BITS c1;
	TYPE_BITS c2;

};

void sc_owrapper::do_gen()
{
	while( true ){
		sc_uint<8> CASE = choice_conf.read();
		int NFrame	 	= nb_frame[CASE];
		int size		= size_frame[CASE];

		// Read input
		for (int i=0; i < _N; i++)
		{
			c1 	= e1.read();
			c2 	= e2.read();
			for (int j=0; j < 2*Q; j++)
			{
				#pragma HLS PIPELINE
				BIT bit;
				if(j < Q)
					bit = c2[j];
				else
					bit = c1[j-Q];
				RAM[i*2*Q+j] = bit;
			}
		}

		for (int i = 0; i < NFrame; i++)
		{
			for (int j = 0; j < size; j++)
			{
				#pragma HLS PIPELINE
				const unsigned int add = (j * NFrame + i);
				BIT bit = RAM[add];
				s.write(bit);
			}
		}

	}
}
