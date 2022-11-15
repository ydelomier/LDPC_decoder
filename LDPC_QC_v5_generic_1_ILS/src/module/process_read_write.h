#ifndef _read_write_
#define _read_write_

#include "systemc.h"

#include "config.h"

#include "../../../shared/src/vector.h"
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

	sc_in < sc_uint<8> > Z_config;
	sc_in < sc_uint<8> > R_config;

    sc_fifo_in < TYPE_LLRS > e;
    sc_fifo_out< TYPE_BITS > s;

    sc_fifo_out < TYPE_MSGS > s1_mesgs;
	sc_fifo_out < TYPE_LLRS > s1_nodes;

	sc_fifo_in < TYPE_MSGS > s2_mesgs;
	sc_fifo_in < TYPE_LLRS > s2_nodes;

	sc_fifo_out < sc_uint<6> > deg_s1;

    sc_signal< TYPE_LLRS >	ibs_e;
    sc_signal< unsigned char >	ibs_rot;
    sc_signal< TYPE_LLRS >	ibs_s;

	sc_fifo_out < unsigned char > posVN_p1;
	sc_fifo_in < unsigned char > posVN_p2;

	sc_fifo_out < bool > CTRL_load_p2;
	sc_fifo_in < bool > CTRL_load_p1;

	sc_fifo_in < bool > CTRL_send_p2;
	sc_fifo_out < bool > CTRL_send_p1;

	sc_fifo_out < bool > END_dec_p2;
	sc_fifo_in < bool > END_dec_p1;

	sc_signal< sc_uint<10> > _N;
	sc_signal< sc_uint<10> > _K;
	sc_signal< sc_uint<10> > _M;

	sc_out < sc_uint<10> > Mout;
	sc_out <sc_uint<10> > nb_frame;
	sc_out <sc_uint<10> > factor_z;

	sc_fifo_out <bool> READY;
	sc_fifo_in <bool> _ready;

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

		SC_CTHREAD(H_Matrix_gene, clk.pos());
		reset_signal_is(reset,true);
	}

private:

	barrel_shifter bs;

	TYPE_MSGS var_mesgs[INTER_FRAME * MESSAGE];
	TYPE_LLRS var_nodes[INTER_FRAME * NOEUD];

	unsigned char DegreeCNs[INTER_FRAME * _Kmax];
	unsigned char PosBlocVNs[INTER_FRAME * _Mmax];
	unsigned char CoeffRotations[INTER_FRAME * (_Mmax + _Nmax)];

void read_VN(){

		_ready.read();
		sc_uint<10> vM = _M.read();

		while( true ){

			CTRL_send_p1.write(true);
			wait();

			// Wait for write_vn to load frame(s) to memory
			CTRL_load_p1.read();
			wait();

#ifdef DEBUG
			cout << endl <<"[P1_READ_VN] {BEGIN} " << endl;
			fflush( stdout );
			int iter = 0;
#endif
			unsigned short ptr = 0;
			unsigned short cnt_DEG = 0;
			unsigned short ind_DEG = 0;
			unsigned short cnt_MSG = 0;
			int cnt_1Iter = INTER_FRAME * vM;

			IT:for (int i = 0; i < MAX_ITERS * INTER_FRAME * vM; i++)
			{
				#pragma HLS LOOP_TRIPCOUNT min=2640 max=2640 avg=2640
				#pragma HLS PIPELINE

				if(cnt_MSG == 0 ){
					ptr = 0;
					cnt_MSG = INTER_FRAME * vM;
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

				const unsigned char posVN = PosBlocVNs    [ ptr ];
			    sc_uint< N_QC > rotat;
			    if(cnt_1Iter > 0)
					rotat = CoeffRotations[ ptr];
				else
					rotat = CoeffRotations[ ptr + INTER_FRAME *vM];

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

			for (int i = 0; i < INTER_FRAME * NOEUD; i++) {
				#pragma HLS PIPELINE
				const sc_uint< N_QC > rotat = CoeffRotations[ i + 2 * INTER_FRAME *vM];
				ibs_e.write(var_nodes[i]);
				ibs_rot.write(rotat);
				wait();
				const TYPE_LLRS rNoeud = ibs_s.read();
				s.write( VECTOR_HARD(rNoeud) );
			}
		}

	}

void write_VN(){

	sc_uint<10> vM = _M.read();

		while (true){

			CTRL_send_p2.read();
			wait();
			// Load INTER_FRAME Frames to memory
			for (int i = 0; i < INTER_FRAME * NOEUD; i++)
			{
				#pragma HLS PIPELINE
					var_nodes[i] = e.read();
			}

			CTRL_load_p2.write (true);
			wait();

#ifdef DEBUG
			unsigned short cnt_MSG = 0;
			cout << endl <<"[P2_WRITE_VN] {BEGIN} " << endl;
			fflush( stdout );
			int iter = 0;
#endif

			IT:for (int i = 0; i < MAX_ITERS * INTER_FRAME * vM; i++)
			{
#pragma HLS LOOP_TRIPCOUNT min=2640 max=2640 avg=2640
				#pragma HLS PIPELINE

				const TYPE_LLRS nLLR = s2_nodes.read();

				const unsigned char posVN    = posVN_p2.read();

				var_nodes[ posVN ] = nLLR;

#ifdef DEBUG
#ifndef LIGHT_DEBUG
				if(cnt_MSG == 0 ){
					cnt_MSG = INTER_FRAME * vM;
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

	sc_uint<10> vM = _M.read();

		while( true ){

#ifdef DEBUG
			cout << endl <<"[P3_READ_MSG] {BEGIN} " << endl;
			fflush( stdout );
			int iter = 0;
#endif
			int cnt_1Iter = INTER_FRAME * vM ;
			const TYPE_MSGS value = VECTOR_SET1( 0 );
			unsigned short ptr = 0;
			unsigned short cnt_MSG = 0;

			IT:for (int i = 0; i < MAX_ITERS * INTER_FRAME * vM; i++)
			{
#pragma HLS LOOP_TRIPCOUNT min=2640 max=2640 avg=2640
				#pragma HLS PIPELINE

				if(cnt_MSG == 0 ){
					ptr = 0;
					cnt_MSG = INTER_FRAME * vM;
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

	sc_uint<10> vM = _M.read();

		while( true ){

			unsigned short ptr = 0;
			unsigned short cnt_MSG = 0;
#ifdef DEBUG
			cout << endl <<"[P4_WRITE_MSG] {BEGIN} " << endl;
			fflush( stdout );
			int iter = 0;
#endif

			IT:for (int i = 0; i < MAX_ITERS * INTER_FRAME * vM; i++)
			{
#pragma HLS LOOP_TRIPCOUNT min=2640 max=2640 avg=2640
				#pragma HLS PIPELINE

				if(cnt_MSG == 0 ){
					ptr = 0;
					cnt_MSG = INTER_FRAME * vM;
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

void H_Matrix_gene()           // process
{

	while(true)
	{
		wait();
		sc_uint<4> Z_case = Z_config.read();
		sc_uint<4> R_case = R_config.read();

		sc_uint<10> Nframe = Nb_FRAME [Z_case];

		sc_uint<10> vN = N_Array [R_case];
		sc_uint<10> vK = K_Array [R_case];
		sc_uint<10> vM = M_Array [R_case];

		_N.write(vN);
		_K.write(vK);
		_M.write(vM);

		const sc_uint< N_QC > _Z = Factor_Z [Z_case];
		sc_uint<10> _Nbframe = Nb_FRAME [Z_case];

		factor_z.write(_Z);
		nb_frame.write(_Nbframe);

		//////////////////////////////////////////////////////////////////////////
		// First Sort the submatrix H' lines according the decreasing degree of D'

		sc_uint<8> _DegreeArrayTemp_[_Kmax] = {0};
		for(int i = 0; i < vK; i ++ )   // Copy the degree subarray
		{
			_DegreeArrayTemp_[i] = _GenericDegreeCNs[i];
		}

		sc_uint<8> Max_index[_Kmax] = {0};
		for(int i = 0; i < vK; i ++ )   // find the decreasing degree index
		{
			sc_uint<8> max = 0;
			sc_uint<8> ind_max = 0;
			for (int j = 0; j < vK ; j++)
			{
				sc_uint<8> m = _DegreeArrayTemp_[j];
				if(m > max){
					ind_max =j;
					max = m;
				}

			}
			Max_index[i] = ind_max;
			_DegreeArrayTemp_[ind_max] = 0;
		}

		///////////////////////////////////////////////////////////////////////////
		// Write output Arrays _DegreeCNs, _PosBlocVNs, _CoeffRotations

		// sort DegreeCNs
		for(int i = 0; i < vK; i++)
		{
			for(int j=0; j < INTER_FRAME; j++)
				DegreeCNs[i*INTER_FRAME +j] = _GenericDegreeCNs[ Max_index[i] ];
		}

		// sort PosBlocVNs
		short ind = 0;
		for(int i = 0; i < vK; i++)
		{
			sc_uint<8> off = 0;
			for(int j = 0; j <  Max_index[i]; j++)
			{
				off += _GenericDegreeCNs[j];
			}
			sc_uint<8> D = _GenericDegreeCNs[ Max_index[i] ];

			for(int k = 0; k < INTER_FRAME; k++)
			{
				for(int j = 0; j < D; j++)
				{
					PosBlocVNs[ind] = ( _GenericPosBlocVNs[ off + j ] + vN * k );
					ind++;
				}
			}
		}

		// sort CoeffRotations
		sc_uint< N_QC > old_coeff[_Nmax] = {0};
		ind = 0;
		for(int i = 0; i < vK; i++)
		{
			sc_uint<8> off = 0;
			for(int j = 0; j <  Max_index[i]; j++)
			{
				off += _GenericDegreeCNs[j];
			}
			sc_uint<8> D = _GenericDegreeCNs[ Max_index[i] ];

			for(int k = 0; k < INTER_FRAME; k++)
			{
				for(int j = 0; j < D; j++)
				{
					sc_uint< N_QC > vn = _GenericCoeffRotations[ off + j ];
					sc_uint< N_QC > coeff = vn % _Z;
					sc_uint< N_QC > mv = (( _Z + coeff) - old_coeff[ _GenericPosBlocVNs[ off + j ] ] ) % _Z;
					if(k == INTER_FRAME - 1)
						old_coeff[ _GenericPosBlocVNs[ off + j ] ] = off;
					CoeffRotations[ind] = mv * _Nbframe;
					ind++;
				}
			}
		}
		for(int i = 0; i < vK; i++)
		{
			sc_uint<8> off = 0;
			for(int j = 0; j <  Max_index[i]; j++)
			{
				off += _GenericDegreeCNs[j];
			}
			sc_uint<8> D = _GenericDegreeCNs[ Max_index[i] ];

			for(int k = 0; k < INTER_FRAME; k++)
			{
				for(int j = 0; j < D; j++)
				{
					sc_uint< N_QC > vn = _GenericCoeffRotations[ off + j ];
					sc_uint< N_QC > coeff = vn % _Z;
					sc_uint< N_QC > mv = (( _Z + coeff) - old_coeff[ _GenericPosBlocVNs[ off + j ] ] ) % _Z;
					if(k == INTER_FRAME - 1)
						old_coeff[ _GenericPosBlocVNs[ off + j ] ] = off;
					CoeffRotations[ind] = mv * _Nbframe;
					ind++;
				}
			}
		}
		for(int k = 0; k < INTER_FRAME; k++)
		{
			for(int j = 0; j < vN; j++)
			{
				sc_uint< N_QC > coeff = 0;
				sc_uint< N_QC > mv = (( _Z + coeff) - old_coeff[j] ) % _Z;
				CoeffRotations[ind] = mv * _Nbframe;
				ind++;
			}
		}

		READY.write(true);

		while(1);

	}

}

};

#endif
