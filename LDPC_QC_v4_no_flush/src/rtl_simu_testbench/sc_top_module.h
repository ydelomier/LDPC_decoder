#ifndef _sc_top_module_
#define _sc_top_module_

//#ifdef __RTL_SIMULATION__
  #include "my_module_rtl_wrapper.h"
  #define sc_fec my_module_rtl_wrapper
//#else
  //#include "../module/my_module.h"
  //#define sc_fec my_module
//#endif

//#ifdef __RTL_SIMULATION__
	#include "sc_monitor.h"
	#include "sc_generator.h"
//#else
	//#include "sc_monitor/sc_monitor.h"
	//#include "sc_generator/sc_generator.h"
//#endif


SC_MODULE(sc_top_module)
{
    sc_in <bool> clk;
    sc_in <bool> reset;

   SC_CTOR(sc_top_module) :
	ldpc  ("ldpc" ),
	monitor ("monit"),
	generator("gene"),
	busy ("busy"),
	load("load"),
	store("store"),
	f8 ("wrap_2_dec",  16),  // TYPE LLR
	f9 ("dec_2_wrap",  16)  // TYPE BITS
    {
	    generator.clk(clk);
        generator.reset(reset);
        generator.e(f8);

        ldpc.clk   ( clk      );
        ldpc.reset ( reset    );
        ldpc.e     ( f8       );
        ldpc.s     ( f9       );
        ldpc.busy (busy);
        ldpc.load (load);
        ldpc.store (store);

        monitor.clk(clk);
        monitor.reset(reset);
        monitor.s(f9);
        monitor.busy (busy);
        monitor.load (load);
        monitor.store (store);
    }

private:

    sc_fec             ldpc;
    sc_monitor		   monitor;
    sc_generator	   generator;

    sc_fifo< TYPE_LLRS > f8;
    sc_fifo< TYPE_BITS > f9;
    sc_signal <bool> busy;
    sc_signal <bool> load;
    sc_signal <bool> store;
};

#endif
