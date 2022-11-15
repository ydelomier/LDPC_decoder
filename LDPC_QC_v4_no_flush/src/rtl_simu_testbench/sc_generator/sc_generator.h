#ifndef _sc_generator_
#define _sc_generator_

#include "systemc.h"
#include "math.h"

#ifdef __RTL_SIMULATION__
#include "config.h"
#else
#include "../../module/config.h"
#endif

#include <iostream>


SC_MODULE(sc_generator)
{
  sc_in <bool> clk;
  sc_in <bool> reset;

  sc_fifo_out < TYPE_LLRS > e;

  SC_CTOR(sc_generator)
  {
	SC_CTHREAD(write_fifo, clk.pos());
	reset_signal_is(reset, true);
  }

private:

	void write_fifo(){

		wait();
		while(true)
		{
			TYPE_LLRS value = (TYPE_LLRS) 21;
			e.write(value);
			wait();
		}
	}
};

#endif
