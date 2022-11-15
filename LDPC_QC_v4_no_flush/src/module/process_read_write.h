#ifndef _read_write_
#define _read_write_

#include "systemc.h"

#include "config.h"

#ifdef __RTL_SIMULATION__
#include "vector.h"
#else
#include "../../../shared/src/vector.h"
#endif
#include "ldpc_parameters.h"
#include "ldpc_code.h"

#include "barrel_shifter.h"

#define PAR_IO  true

#ifndef __SYNTHESIS__
//#define DEBUG
//#define LIGHT_DEBUG
#endif

SC_MODULE(read_write)
{
	sc_in <bool> clk;
	sc_in <bool> reset;

	// Monitor
#ifdef _MONITORING_
	sc_out <bool> busy;
	sc_out <bool> load;
	sc_out <bool> store;
#endif

    sc_fifo_in < TYPE_LLRS > e;
    sc_fifo_out< TYPE_BITS > s;

    sc_fifo_out < TYPE_MSGS > s1_mesgs;
	sc_fifo_out < TYPE_LLRS > s1_nodes;

	sc_fifo_in < TYPE_MSGS > s2_mesgs;
	sc_fifo_in < TYPE_LLRS > s2_nodes;

	sc_fifo_out < sc_uint<6> > deg_s1;

    sc_signal< TYPE_LLRS >	ibs_e;
    sc_signal< sc_uint< N_QC > >	ibs_rot;
    sc_signal< TYPE_LLRS >	ibs_s;

	sc_fifo_out < sc_uint< FORMAT > > posVN_p1;
	sc_fifo_in < sc_uint< FORMAT > > posVN_p2;

	sc_fifo_out < bool > CTRL_load_p2;
	sc_fifo_in < bool > CTRL_load_p1;

	sc_fifo_in < bool > CTRL_send_p2;
	sc_fifo_out < bool > CTRL_send_p1;

	sc_fifo_out < bool > END_dec_p2;
	sc_fifo_in < bool > END_dec_p1;

	SC_CTOR(read_write):
		bs( "barrel")
	{
		SC_CTHREAD(read_VN, clk.pos());
		reset_signal_is(reset,true);

		SC_CTHREAD(write_VN, clk.pos());
		reset_signal_is(reset,true);

		SC_CTHREAD(read_MSG, clk.pos());
		reset_signal_is(reset,true);

		SC_CTHREAD(write_MSG, clk.pos());
		reset_signal_is(reset,true);

		bs.ibs_e(ibs_e);
		bs.ibs_rot(ibs_rot);
		bs.ibs_s(ibs_s);
	}

private:

	barrel_shifter bs;

	TYPE_MSGS var_mesgs[INTER_FRAME * MESSAGE];
	TYPE_LLRS var_nodes[INTER_FRAME * NOEUD];

void read_VN(){

#ifdef _MONITORING_
		load.write(false);
		store.write(false);
		busy.write(false);
#endif
		wait();

		while( true ){

			CTRL_send_p1.write(true);
			wait();

#ifdef _MONITORING_
			store.write(false);
			load.write(true);
#endif

			// Wait for write_vn to load frame(s) to memory
			CTRL_load_p1.read();
			wait();

#ifdef _MONITORING_
			load.write(false);
			busy.write(true);
#endif

#ifdef DEBUG
			cout << endl <<"[P1_READ_VN] {BEGIN} " << endl;
			fflush( stdout );
			int iter = 0;
#endif
			unsigned short ptr = 0;
			unsigned short cnt_DEG = 0;
			unsigned short ind_DEG = 0;
			unsigned short cnt_MSG = 0;
			int cnt_1Iter = INTER_FRAME * _M;

			IT:for (int i = 0; i < MAX_ITERS * INTER_FRAME * _M; i++)
			{
				#pragma HLS PIPELINE

				if(cnt_MSG == 0 ){
					ptr = 0;
					cnt_MSG = INTER_FRAME * _M;
					ind_DEG = 0;
#ifdef DEBUG
					iter++;
#endif
				}

				if(cnt_DEG == 0){
					unsigned char deg_cn = DegreeCNs[ind_DEG];
					deg_s1.write(deg_cn);
					cnt_DEG = deg_cn;
					ind_DEG++;
				}

				const sc_uint< FORMAT > posVN = PosBlocVNs    [ ptr ];
			    sc_uint< N_QC > rotat;
			    if(cnt_1Iter > 0)
					rotat = CoeffRotations[ ptr];
				else
					rotat = CoeffRotations[ ptr + INTER_FRAME *_M];

				posVN_p1.write( posVN );

				const TYPE_LLRS vNoeud    = var_nodes     [ posVN ];

				ibs_e.write(vNoeud);
				ibs_rot.write(rotat);
				wait();
				const TYPE_LLRS rNoeud = ibs_s.read();

				s1_nodes.write(rNoeud);

#ifdef DEBUG
#ifndef LIGHT_DEBUG
				cout << endl <<"[P1_READ_VN] {PROCESSING} , i : " << i << endl;
				cout << "	* iteration		: "<< iter << endl;
				cout << "	* cnt_MSG     	: "<< cnt_MSG << endl;
				cout << "	* cnt_DEG     	: "<< cnt_DEG << endl;
				cout << "	* cnt_1Iter     : "<< cnt_1Iter << endl;
				cout << "	* ind_DEG     	: "<< ind_DEG << endl;
				cout << "	* ptr     		: "<< ptr << endl;
				cout << "		§§ VN		: ";
				SHOW(rNoeud);
				fflush( stdout );
#endif
#endif

				ptr += 1;
				cnt_MSG -= 1;
				cnt_DEG -=1;
				cnt_1Iter -=1;
			}

			END_dec_p1.read();
			wait();

#ifdef _MONITORING_
			busy.write(false);
			store.write(true);
#endif
			for (int i = 0; i < INTER_FRAME * NOEUD; i++) {
				#pragma HLS PIPELINE
				const sc_uint< N_QC > rotat = CoeffRotations[ i + 2 * INTER_FRAME *_M];
				ibs_e.write(var_nodes[i]);
				ibs_rot.write(rotat);
				wait();
				const TYPE_LLRS rNoeud = ibs_s.read();
				s.write( VECTOR_HARD(rNoeud) );
			}
		}

	}

void write_VN(){

		while (true){

			CTRL_send_p2.read();
			wait();
			// Load INTER_FRAME Frames to memory
			for (int i = 0; i < INTER_FRAME * NOEUD; i++)
			{
				#pragma HLS PIPELINE
					var_nodes[i] = e.read();
#ifndef __SYNTHESIS__
				wait();
#endif
			}

			CTRL_load_p2.write (true);
			wait();

#ifdef DEBUG
			unsigned short cnt_MSG = 0;
			cout << endl <<"[P2_WRITE_VN] {BEGIN} " << endl;
			fflush( stdout );
			int iter = 0;
#endif

			IT:for (int i = 0; i < MAX_ITERS * INTER_FRAME * _M; i++)
			{
				#pragma HLS PIPELINE

				const TYPE_LLRS nLLR = s2_nodes.read();

				const sc_uint< FORMAT > posVN    = posVN_p2.read();

				var_nodes[ posVN ] = nLLR;

#ifdef DEBUG
#ifndef LIGHT_DEBUG
				if(cnt_MSG == 0 ){
					cnt_MSG = INTER_FRAME * _M;
					iter++;
				}
				cout << endl <<"[P2_WRITE_VN] {PROCESSING} , i : " << i << endl;
				cout << "	* iteration		: "<< iter << endl;
				cout << "	* cnt_MSG     	: "<< cnt_MSG << endl;
				cout << "		§§ VN		: ";
				SHOW(nLLR);
				fflush( stdout );
				cnt_MSG -= 1;
#endif
#endif

			}

			END_dec_p2.write (true);
			wait();
		}
	}

void read_MSG(){

		while( true ){

#ifdef DEBUG
			cout << endl <<"[P3_READ_MSG] {BEGIN} " << endl;
			fflush( stdout );
			int iter = 0;
#endif
			int cnt_1Iter = INTER_FRAME * _M ;
			const TYPE_MSGS value = VECTOR_SET1( 0 );
			unsigned short ptr = 0;
			unsigned short cnt_MSG = 0;

			IT:for (int i = 0; i < MAX_ITERS * INTER_FRAME * _M; i++)
			{
				#pragma HLS PIPELINE

				if(cnt_MSG == 0 ){
					ptr = 0;
					cnt_MSG = INTER_FRAME * _M;
#ifdef DEBUG
					iter++;
#endif
				}

				TYPE_MSGS vMessg;

				if(cnt_1Iter > 0)
					vMessg = value;
				else
					vMessg    = var_mesgs     [ ptr ];

				s1_mesgs.write(vMessg);

#ifdef DEBUG
#ifndef LIGHT_DEBUG
				cout << endl <<"[P3_READ_MSG] {PROCESSING} , i : " << i << endl;
				cout << "	* iteration		: "<< iter << endl;
				cout << "	* cnt_MSG     	: "<< cnt_MSG << endl;
				cout << "	* cnt_1Iter     : "<< cnt_1Iter << endl;
				cout << "		§§ MSG		: ";
				SHOW(vMessg);
				fflush( stdout );
#endif
#endif
				ptr += 1;
				cnt_MSG -= 1;
				cnt_1Iter -= 1;
			}
		}
	}

void write_MSG(){

		while( true ){

			unsigned short ptr = 0;
			unsigned short cnt_MSG = 0;
#ifdef DEBUG
			cout << endl <<"[P4_WRITE_MSG] {BEGIN} " << endl;
			fflush( stdout );
			int iter = 0;
#endif

			IT:for (int i = 0; i < MAX_ITERS * INTER_FRAME * _M; i++)
			{
				#pragma HLS PIPELINE

				if(cnt_MSG == 0 ){
					ptr = 0;
					cnt_MSG = INTER_FRAME * _M;
#ifdef DEBUG
				iter++;
#endif
				}

				TYPE_MSGS vResultat = s2_mesgs.read();

				var_mesgs            [ptr]   = vResultat;

#ifdef DEBUG
#ifndef LIGHT_DEBUG
				cout << endl <<"[P4_WRITE_MSG] {PROCESSING} , i : " << i << endl;
				cout << "	* iteration		: "<< iter << endl;
				cout << "	* cnt_MSG     	: "<< cnt_MSG << endl;
				cout << "		§§ MSG		: ";
				SHOW(vResultat);
				fflush( stdout );
#endif
#endif

				ptr += 1;
				cnt_MSG -= 1;
			}
		}
	}

};

#endif
