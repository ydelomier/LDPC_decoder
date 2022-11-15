#ifndef _process_s2_
#define _process_s2_

#include "systemc.h"

#include "config.h"

#include "ldpc_parameters.h"
#ifdef __RTL_SIMULATION__
#include "vector.h"
#else
#include "../../../shared/src/vector.h"
#endif

#ifndef __SYNTHESIS__
//#define DEBUG2
//#define LIGHT_DEBUG
#define COMPARE
#endif

#define PAR_IO  true

SC_MODULE(process_s2)
{
	sc_in <bool> clk;
	sc_in <bool> reset;

	sc_fifo_out < TYPE_MSGS > var_mesgs;
	sc_fifo_out < TYPE_LLRS > var_nodes;

	sc_fifo_in < sc_uint<6> > deg;

	sc_fifo_in < TYPE_MSGS > sign_somme;
	sc_fifo_in < TYPE_MSGS > min1;
	sc_fifo_in < TYPE_MSGS > min2;

	sc_fifo_in < TYPE_LLRS > tab_vContr;
#ifndef FIFO_TO_LUT
	sc_fifo_in < TYPE_LLRS > tab_aContr;
	sc_fifo_in < TYPE_LLRS > tab_sContr;
#endif

	SC_CTOR(process_s2)
	{
		SC_CTHREAD(do_action, clk.pos());
		reset_signal_is(reset,true);

	}

private:

void do_action()
	{

		int frame = 0;

		while( true ){

			unsigned short cnt = 0;

			TYPE_BITS vsign_somme = 0;
			TYPE_MSGS vmin1       = 0;
			TYPE_MSGS vmin2       = 0;

#ifdef DEBUG2
				cout << endl <<"[S2_PROCESS] {BEGIN}" << endl;
				fflush( stdout );
#endif

			IT:for (int i = 0; i < MAX_ITERS * INTER_FRAME * _M; i++)
			{
#pragma HLS LOOP_TRIPCOUNT min=2640 max=2640 avg=2640
				#pragma HLS PIPELINE

				if(cnt == 0){
					cnt = deg.read();
					vsign_somme = sign_somme.read();
					vmin1       = min1.read();
					vmin2       = min2.read();

#ifdef DEBUG2
#ifndef LIGHT_DEBUG
				cout << endl <<"[S2_PROCESS] {PROCESSING} , cnt : " << cnt << " , read min1 &min 2" << endl;
				fflush( stdout );
#endif
#endif
				}

				const TYPE_LLRS vContr       = tab_vContr.read();
#ifndef FIFO_TO_LUT
				const TYPE_LLRS absContr       = tab_aContr.read();
				const TYPE_LLRS sigContr       = tab_sContr.read();
#else
				const TYPE_MSGS absContr  	= VECTOR_ABS (vContr);
				const TYPE_BITS sigContr  	= VECTOR_SIGN(vContr);
#endif

				const TYPE_BITS fSign        = VECTOR_EQUAL(absContr, vmin1);
				TYPE_MSGS vResultat          = VECTOR_CMOV (fSign, vmin2, vmin1);

				vResultat                    = VECTOR_SIGN(vResultat, VECTOR_XOR(vsign_somme, sigContr));

				TYPE_LLRS nLLR               = VECTOR_ADD(vContr, vResultat);

				var_mesgs.write( vResultat );

				var_nodes.write( nLLR );

#ifdef DEBUG2
#ifndef LIGHT_DEBUG
				cout << endl <<"[S2_PROCESS] {PROCESSING} , i : " << i << endl;
				cout << "	* cnt_DEG     	: "<< cnt << endl;
				fflush( stdout );
#endif
#endif
				cnt --;

			}
	}
}


};

#endif
