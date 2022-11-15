#ifndef _H_Matrix_gene_
#define _H_Matrix_gene_

#include "systemc.h"

#include "scalar.h"
#include "config.h"
#include "ldpc_parameters.h"
#include "ldpc_code.h"

SC_MODULE(H_Matrix_gene)          // module (class) declaration
{
	sc_in <bool> clk;
	sc_in <bool> reset;

	sc_in < sc_uint<8> > Z_config;
	sc_in < sc_uint<8> > R_config;

	sc_out < unsigned short > Off_Degree;
	sc_out < unsigned short > Off_PosVN;
    sc_out < short > vN;
    sc_out < short > vM;
    sc_out < short > vK;

	SC_CTOR(H_Matrix_gene)
	{
        SC_CTHREAD(do_gen,clk.pos());
    }

private:
    void do_gen();

};

void H_Matrix_gene::do_gen()           // process
{

	while(true)
	{
		wait();
		sc_uint<4> Z_case = Z_config.read();
		sc_uint<4> R_case = R_config.read();

		const sc_uint<10> _N = N_Array [R_case];
		const sc_uint<10> _K = K_Array [R_case];
		const sc_uint<10> _M = M_Array [R_case];

		const sc_uint< N_QC > _Z = Factor_Z [Z_case];

		//////////////////////////////////////////////////////////////////////////
		// First Sort the submatrix H' lines according the decreasing degree of D'

		sc_uint<8> _DegreeArrayTemp_[_Kmax] = {0};
		for(int i = 0; i < _K; i ++ )   // Copy the degree subarray
		{
			_DegreeArrayTemp_[i] = _GenericDegree[i];
		}

		sc_uint<8> Max_index[_Kmax] = {0};
		for(int i = 0; i < _K; i ++ )   // find the decreasing degree index
		{
			sc_uint<8> max = 0;
			sc_uint<8> ind_max = 0;
			for (int j = 0; j < _K ; j++)
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
		for(int i = 0; i < _K; i++)
		{
			for(int j=0; j < INTER_FRAME; j++)
				DegreeCNs[i*INTER_FRAME +j] = _GenericDegree[ Max_index[i] ];
		}

		// sort PosBlocVNs
		short ind = 0;
		for(int i = 0; i < _K; i++)
		{
			sc_uint<8> off = 0;
			for(int j = 0; j <  Max_index[i]; j++)
			{
				off += _GenericDegree[j];
			}
			sc_uint<8> D = _GenericDegree[ Max_index[i] ];

			for(int k = 0; k < INTER_FRAME; k++)
			{
				for(int j = 0; j < D; j++)
				{
					PosBlocVNs[ind] = ( _GenericPosBlocVNs[ off + j ] + _N * k );
					ind++;
				}
			}
		}

		// sort CoeffRotations
		sc_uint< N_QC > old_coeff[_Nmax] = {0};
		short ind = 0;
		for(int i = 0; i < _K; i++)
		{
			sc_uint<8> off = 0;
			for(int j = 0; j <  Max_index[i]; j++)
			{
				off += _GenericDegree[j];
			}
			sc_uint<8> D = _GenericDegree[ Max_index[i] ];

			for(int k = 0; k < INTER_FRAME; k++)
			{
				for(int j = 0; j < D; j++)
				{
					sc_uint< N_QC > vn = _GenericCoeffRotations[ off + j ];
					sc_uint< N_QC > coeff = vn % _Z;
					sc_uint< N_QC > mv = (( _Z + coeff) - old_coeff[ _GenericPosBlocVNs[ off + j ] ] ) % _Z;
					if(k == INTER_FRAME - 1)
						old_coeff[ _GenericPosBlocVNs[ off + j ] ] = off;
					CoeffRotations[ind] = mv;
					ind++;
				}
			}
		}
		for(int i = 0; i < _K; i++)
		{
			sc_uint<8> off = 0;
			for(int j = 0; j <  Max_index[i]; j++)
			{
				off += _GenericDegree[j];
			}
			sc_uint<8> D = _GenericDegree[ Max_index[i] ];

			for(int k = 0; k < INTER_FRAME; k++)
			{
				for(int j = 0; j < D; j++)
				{
					sc_uint< N_QC > vn = _GenericCoeffRotations[ off + j ];
					sc_uint< N_QC > coeff = vn % _Z;
					sc_uint< N_QC > mv = (( _Z + coeff) - old_coeff[ _GenericPosBlocVNs[ off + j ] ] ) % _Z;
					if(k == INTER_FRAME - 1)
						old_coeff[ _GenericPosBlocVNs[ off + j ] ] = off;
					CoeffRotations[ind] = mv;
					ind++;
				}
			}
		}
		for(int k = 0; k < INTER_FRAME; k++)
		{
			for(int j = 0; j < _N; j++)
			{
				sc_uint< N_QC > coeff = 0;
				sc_uint< N_QC > mv = (( _Z + coeff) - old_coeff[j] ) % _Z;
				CoeffRotations[ind] = mv;
				ind++;
			}
		}

		while(1);

	}

}

#endif
