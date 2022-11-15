#ifndef _process_s1_
#define _process_s1_

#include "systemc.h"

#include "config.h"

#include "ldpc_parameters.h"
#include "../../../shared/src/vector.h"

#ifndef __SYNTHESIS__
//#define DEBUG1
//#define LIGHT_DEBUG
#define COMPARE
#endif


#define PAR_IO  true

SC_MODULE(process_s1)
{
	sc_in <bool> clk;
	sc_in <bool> reset;

	sc_in < sc_uint<10> > vM;

	sc_fifo_in < TYPE_MSGS > var_mesgs;
	sc_fifo_in < TYPE_LLRS > var_nodes;

	sc_fifo_in < sc_uint<6> > deg;
	sc_fifo_out < sc_uint<6> > deg_s2;

	sc_fifo_out < TYPE_MSGS > sign_somme;
	sc_fifo_out < TYPE_MSGS > min1;
	sc_fifo_out < TYPE_MSGS > min2;

	sc_fifo_out < TYPE_LLRS > tab_vContr;

	SC_CTOR(process_s1)
	{
		SC_CTHREAD(do_action, clk.pos());
		reset_signal_is(reset,true);

	}

private:

void do_action(){

	int frame = 0;
	sc_uint<10> _M = vM.read();

	while( true ){

		unsigned short cnt = 0;
		TYPE_BITS vsign_somme = VECTOR_ZERO(  );
		TYPE_MSGS vmin1       = VECTOR_SET1( MSG_MAXV );
		TYPE_MSGS vmin2       = VECTOR_SET1( MSG_MAXV );

#ifdef DEBUG1
				cout << endl <<"[S1_PROCESS] {BEGIN}" << endl;
				fflush( stdout );
#endif

		IT:for (int i = 0; i < MAX_ITERS * INTER_FRAME * _M; i++)
		{
#pragma HLS LOOP_TRIPCOUNT min=2640 max=2640 avg=2640
			#pragma HLS PIPELINE

				if(cnt == 0){
					cnt = deg.read();
					deg_s2.write(cnt);
					vsign_somme = VECTOR_ZERO(  );
					vmin1       = VECTOR_SET1( MSG_MAXV );
					vmin2       = VECTOR_SET1( MSG_MAXV );
				}

				const TYPE_MSGS vMessg    = var_mesgs.read();

				const TYPE_LLRS vNoeud    = var_nodes.read();

				const TYPE_LLRS vContr    = VECTOR_SUB( vNoeud, vMessg);
				const TYPE_MSGS absContr  = VECTOR_ABS (vContr);
				const TYPE_BITS sigContr  = VECTOR_SIGN(vContr);

				tab_vContr.write( vContr );

				TYPE_MSGS vTemp           	= vmin1;
				vmin1                      = VECTOR_MIN( absContr,        vmin1);
				vmin2                      = VECTOR_MIN( absContr, vTemp, vmin2);
				vsign_somme                = VECTOR_XOR( vsign_somme, sigContr );

#ifdef DEBUG1
#ifndef LIGHT_DEBUG
				cout << endl <<"[S1_PROCESS] {PROCESSING} , i : " << i << endl;
				cout << "	* cnt_DEG     	: "<< cnt << endl;
				fflush( stdout );
#endif
#endif
				cnt --;

				if(cnt == 0){
					sign_somme.write( vsign_somme );
					min1.write( vmin1 );
					min2.write( vmin2 );
#ifdef DEBUG1
#ifndef LIGHT_DEBUG
					SHOW(vsign_somme);
					SHOW(vmin1);
					SHOW(vmin2);
				cout << endl <<"[S1_PROCESS] {PROCESSING} , i : " << i <<" , cnt : " << cnt << " , write min1 & min2" <<endl;
#endif
#endif
				}

			//frame++;

		}
	}
}

};

#endif
