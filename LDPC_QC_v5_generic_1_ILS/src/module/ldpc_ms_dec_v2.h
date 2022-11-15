#ifndef _my_module_
#define _my_module_


#include "systemc.h"

#include "./config.h"

#include "./ldpc_parameters.h"

#define PAR_IO  true

SC_MODULE(ldpc_ms_dec_v2)
{
	sc_in <bool> clk;
  sc_in <bool> reset;

#if PAR_IO == false
    sc_fifo_in < LLR > e1;
    sc_fifo_out< BIT > s1;
#else
    sc_fifo_in < TYPE_LLRS > e1;
    sc_fifo_out< TYPE_BITS > s1;
#endif

	SC_CTOR(ldpc_ms_dec_v2)
	{
//#pragma HLS STREAM variable=e1 depth=1024 dim=1
//#pragma HLS STREAM variable=s1 depth=1024 dim=1
		SC_CTHREAD(do_action, clk.pos());
    reset_signal_is(reset,true);
	}

private:
	void do_action();

	TYPE_MSGS var_mesgs[MESSAGE];
	TYPE_LLRS var_nodes[NOEUD];
};

#endif
