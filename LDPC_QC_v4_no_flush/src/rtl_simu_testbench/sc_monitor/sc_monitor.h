#ifndef _sc_monitor_
#define _sc_monitor_

#include "systemc.h"
#include <iostream>

#ifdef __RTL_SIMULATION__
#include "config.h"
#else
#include "../../module/config.h"
#endif


SC_MODULE(sc_monitor)
{
  sc_in <bool> clk;
  sc_in <bool> reset;

  sc_fifo_in < TYPE_BITS > s;

  sc_in <bool> busy;
  sc_in <bool> load;
  sc_in <bool> store;

  SC_CTOR(sc_monitor)
  {
	SC_CTHREAD(read_fifo, clk.pos());
	reset_signal_is(reset, true);

    SC_CTHREAD(do_busy, clk.pos());
    reset_signal_is(reset, true);

    SC_CTHREAD(do_load, clk.pos());
    reset_signal_is(reset, true);

    SC_CTHREAD(do_store, clk.pos());
    reset_signal_is(reset, true);
  }

private:
	void do_busy(){

		int ctn_proc = 0;
		bool one_time = false;
		wait();

		while(true)
		{
			if(one_time == false)
			{
				while(busy.read() == 0)
					wait();

				while(busy.read() == 1){
					ctn_proc++;
					wait();
				}

				cout << "[MONITOR] PROCESS latency : " << ctn_proc <<endl<< endl;
				fflush( stdout );

				ctn_proc = 0;
			}

			one_time = true;
			wait();
		}

	}

	void do_load(){

		int ctn_load = 0;
		bool one_time = false;
		wait();
		while(true)
		{
			if(one_time == false)
			{
				while(load.read() == 0)
					wait();

				while(load.read() == 1){
					ctn_load++;
					wait();
				}

				cout << "[MONITOR] LOAD latency : " << ctn_load <<endl;
				fflush( stdout );

				ctn_load = 0;
			}

			one_time = true;
			wait();
		}
	}

	void do_store(){

		int ctn_store = 0;
		bool one_time = false;
		wait();
		while(true)
		{
			if(one_time == false)
			{
				while(store.read() == 0)
					wait();

				while(store.read() == 1){
					ctn_store++;
					wait();
				}

				cout << "[MONITOR] STORE latency : " << ctn_store <<endl;
				fflush( stdout );

				ctn_store = 0;
			}

			one_time = true;
			wait();
		}
	}

	void read_fifo(){

		wait();
		while(true)
		{
			TYPE_BITS fifo_in = s.read();
		}
	}
};

#endif
