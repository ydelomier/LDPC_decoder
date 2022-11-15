/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _sc_error_counter_
#define _sc_error_counter_

#include "systemc.h"

#ifdef __RTL_SIMULATION__
#include "config.h"
#include "generic_parameters.h"
#else
#include "../../module/config.h"
#include "../../module/ldpc_parameters.h"
#endif


#include <iostream>
using namespace std;

SC_MODULE(sc_error_counter)
{
    sc_in <bool> clk;
    sc_in <bool> reset;
    sc_in < sc_uint<8> > choice_conf;

    sc_fifo_in< BIT > dec;
    sc_fifo_in< BIT > ref;

    sc_out    < BIT > dec_frame;
    sc_out    < BIT > err_frame;

    sc_out    < sc_uint<64> > err_bits;
    sc_out    < sc_uint<64> > err_frames;

    sc_out    < sc_uint<64> > proc_bits;
    sc_out    < sc_uint<64> > proc_frames;

    SC_CTOR(sc_error_counter)
    {
        SC_CTHREAD(do_gen, clk.pos());
        reset_signal_is(reset, true);
    }

private:
    void do_gen();

};
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
void sc_error_counter::do_gen()
{
	dec_frame.write  ( 0 );
	err_frame.write  ( 0 );
	err_bits.write   ( 0 );
	err_frames.write ( 0 );
	proc_bits.write  ( 0 );
	proc_frames.write( 0 );

	sc_uint<64> errBE   = 0;
	sc_uint<64> errFE   = 0;
	sc_uint<64> pBits   = 0;
	sc_uint<64> pFrames = 0;

	wait();

	while( true )
	{
		const sc_uint<8> CASE 			= choice_conf.read();
		// TODO: ADAPTER LA VALEUR 10 AU CODE LDPC !
		sc_uint<10> err = 0;

		for(int i = 0; i < (_N * QC); i += 1)
		{
			#pragma HLS PIPELINE
			const BIT bit_1 = dec.read();
			const BIT bit_2 = ref.read();
			err += (bit_1 != bit_2);
		}

		//
		// ON MET A JOUR LES STATISTIQUES
		//
		errBE   += err;
		errFE   += err.or_reduce();
		pBits   += (_N * QC);
		pFrames += 1;

		//
		// ON RESCALE LES BEs CAR CELA MONTE TRES VITE !
		//
		err_bits.write   ( errBE   );
		err_frames.write ( errFE   );
		proc_bits.write  ( pBits   );
		proc_frames.write( pFrames );

		err_frame.write  ( err.or_reduce() );
		dec_frame.write  ( 1 );
		wait( );

		err_frame.write  ( 0 );
		dec_frame.write  ( 0 );
		wait( );
	}
}
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
#endif
