#ifndef _sc_1_decoder_
#define _sc_1_decoder_

#include "systemc.h"


#ifdef __RTL_SIMULATION__
#include "my_module_rtl_wrapper.h"
#define my_module my_module_rtl_wrapper
#else
#include "../module/my_module.h"
#endif

#include "../wrapper/wrapper_qc.h"


//
//
////////////////////////////////////////////////////////////////////////////////
//
//
SC_MODULE(sc_1_decoder)
{
	sc_in <bool> clk;
	sc_in <bool> reset;

	sc_fifo_in < LLR > e;
	sc_fifo_out< BIT > s;

	SC_CTOR(sc_1_decoder)
	: dec_0      ("dec_0"),
	  wrap		("wrap"),
	  f1 ("f1",  32),
	  f2 ("f2",  32)
	{
		wrap.gen_to_wrap(e);
		wrap.wrap_to_ldpc(f1);
		wrap.ldpc_to_wrap(f2);
		wrap.wrap_to_gen(s);

		dec_0.clk  ( clk         );
		dec_0.reset( reset       );
		dec_0.e   ( f1 );
		dec_0.s   ( f2 );
	}

private:

	my_module dec_0;
	wrapper_qc wrap;

	sc_fifo < TYPE_LLRS > f1;
	sc_fifo < TYPE_BITS > f2;


};

#endif
