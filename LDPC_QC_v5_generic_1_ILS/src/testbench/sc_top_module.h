/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _sc_top_module_
#define _sc_top_module_

//#define CHANNEL_MKL

//
// PARAMETRAGE DU NOMBRE DE DECODEUR LDPC INSTANCIES DANS L'ARCHITECTURE
// MATERIELLE. VALEURS SUPPORTEES : {ONE_DEC, TWO_DECS, FOUR_DECS}
//
#ifndef LDPC_DECODERS
	#define LDPC_DECODERS 1
#endif

//
// PARAMETRAGE DU NOMBRE DE DECODEUR LDPC INSTANCIES DANS L'ARCHITECTURE
// MATERIELLE. VALEURS SUPPORTEES : {ONE_DEC, TWO_DECS, FOUR_DECS}
//
#define QUANTIZER_BITS   6
#define QUANTIZER_FRAC   2
#define QUANTIZER_FACTOR (1<<(QUANTIZER_FRAC))
#define QUANTIZER_MINVAL (1<<(QUANTIZER_BITS-1)+1)
#define QUANTIZER_MAXVAL (1<<(QUANTIZER_BITS-1)-1)

//
#ifdef __RTL_SIMULATION__
#include "sc_encoder.h"
#else
#include "sc_encoder/sc_encoder.h"
#endif
//
// PARAMETRAGE DU NOMBRE DE DECODEUR LDPC INSTANCIES DANS L'ARCHITECTURE
// MATERIELLE. VALEURS SUPPORTEES : {ONE_DEC, TWO_DECS, FOUR_DECS}
//
#define MODULATION BPSK

#ifdef __RTL_SIMULATION__
#include "sc_bpsk.h"
#else
#include "sc_modulate/sc_bpsk.h"
#endif


//
// PARAMETRAGE DU NOMBRE DE DECODEUR LDPC INSTANCIES DANS L'ARCHITECTURE
// MATERIELLE. VALEURS SUPPORTEES : {ONE_DEC, TWO_DECS, FOUR_DECS}
//
#define RANDOM_GENERATOR xorshift128

//#include "../sc_channel/sc_random/sc_random.h"
//#include "../sc_channel/sc_mtwister/sc_mtwister.h"

#ifdef __RTL_SIMULATION__
#include "sc_xorshift128.h"
#else
#include "sc_channel/sc_xorshift128/sc_xorshift128.h"
#endif

//#include "../sc_channel/sc_xorshift128plus/sc_xorshift128plus.h"
//#include "../sc_channel/sc_xorshift1024star/sc_xorshift1024star.h"
//#include "../sc_channel/sc_intel_mkl/sc_intel_mkl.h"

#ifdef __RTL_SIMULATION__
#include "sc_awgn.h"
#else
#include "sc_channel/sc_awgn/sc_awgn.h"
#endif

//#include "../sc_channel/sc_awgn/sc_fake_awgn.h"

#ifdef __RTL_SIMULATION__
#include "sc_adder.h"
#else
#include "sc_channel/sc_adder/sc_adder.h"
#endif

//
// PARAMETRAGE DU NOMBRE DE DECODEUR LDPC INSTANCIES DANS L'ARCHITECTURE
// MATERIELLE. VALEURS SUPPORTEES :
//	- sc_quantizer
//	- sc_round_quantizer
//
#define QUANTIZER sc_quantizer

#ifdef __RTL_SIMULATION__
#include "sc_quantizer.h"
#else
#include "sc_quantizer/sc_quantizer.h"
#endif

#if LDPC_DECODERS == 1
  #include "sc_1_decoder.h"
  #define sc_fec sc_1_decoder

#endif

#ifdef __RTL_SIMULATION__
#include "sc_error_counter.h"
#include "sc_mbps_compute.h"
#include "sc_xer_compute.h"
#else
#include "sc_error_counter/sc_error_counter.h"
#include "sc_mbps_compute/sc_mbps_compute.h"
#include "sc_xer_compute/sc_xer_compute.h"
#endif


SC_MODULE(sc_top_module)
{
    sc_in <bool> clk;
    sc_in <bool> reset;
    sc_in <bool> enable;
    sc_in < sc_uint<8> > 	choice_conf;
    sc_in < float > 		SIGMA;
    sc_in < sc_uint<8> > 	BETA;
    sc_in < sc_int<8> > 	VSATN;
    sc_in < sc_int<8> > 	VSATP;
    sc_in < sc_uint<8> > 	NBIT;
    sc_out< sc_uint<16> > 	CPT;

    sc_in < sc_uint<8> > seed;

    sc_out< sc_uint<64> > err_bits;
    sc_out< sc_uint<64> > err_frames;
    sc_out< sc_uint<64> > proc_bits;
    sc_out< sc_uint<64> > proc_frames;

    sc_out< sc_uint<32> > ber_value;
    sc_out< sc_uint<32> > fer_value;
    sc_out< sc_uint<32> > mbps_value;

    SC_CTOR(sc_top_module) :
        encoder("enc" ),
        bpsk   ("bpsk"),
//        rand1 ("rand1"),
//        rand2 ("rand2"),
        randc ("rand1"),
        awgn  ("awgn" ),
        adder ("adder"),
        quant ("quant"),
        ldpc  ("ldpc" ),
        err_counter("err_counter"),
        mbps_compute("mbps_compute"),
        ber_counter("ber_counter"),
        fer_counter("fer_counter"),
//        term("term"),
    f1 ("enc_2_bpsk"   , 32768),  // TYPE BIT
    f2 ("bpsk_2_adder" ,    32),  // TYPE BIT
    f3 ("rand1_2_awgn" ,    32),  // TYPE FLOAT
    f4 ("rand2_2_awgn" ,    32),  // TYPE FLOAT
    f5 ("awgn_2_adder" ,    32),  // TYPE FLOAT
    f6 ("adder_2_quant",    32),  // TYPE FLOAT
    f7 ("quant_2_decoder",  32),  // TYPE LLR
    f10("decoder_2_err",    32),  // TYPE BIT
    f11("enc_2_err"    , 32768),  // TYPE BIT
    dec_frame    ("dec_frame"),
    err_frame    ("err_frame"),
    _proc_bits   ("_proc_bits"),
    _proc_frames ("_dec_frame"),
    _err_bits    ("_err_bits"),
    _err_frames  ("_err_frame"),
    __proc_bits  ("__proc_bits"),
    __proc_frames("__dec_frame"),
    __err_bits   ("__err_bits"),
    __err_frames ("__err_frame")
    {
        encoder.clk   ( clk      );
        encoder.reset ( reset    );
        encoder.enable( enable   );
        encoder.s1    ( f1       );
        encoder.s2    ( f11      );
        encoder.choice_conf(choice_conf);
        encoder.cpt(CPT);

        bpsk.clk  ( clk   );
        bpsk.reset( reset );
        bpsk.e    ( f1    );
        bpsk.s    ( f2    );

        randc.clk  ( clk   );
        randc.reset( reset );
        randc.seed ( seed  );
        randc.s1   ( f3    );
        randc.s2   ( f4    );

        awgn.clk   ( clk   );
        awgn.reset ( reset );
        awgn.e1    ( f3    );
        awgn.e2    ( f4    );
        awgn.s     ( f5    );

        adder.clk   ( clk   );
        adder.reset ( reset );
        adder.sigma ( SIGMA   );
        adder.e1    ( f2    ); // enc. bits
        adder.e2    ( f5    ); // noise
        adder.s     ( f6    );

        quant.clk   ( clk   );
        quant.reset ( reset );
        quant.e     ( f6    );
        quant.s     ( f7    );
        quant.BETA     ( BETA    );
        quant.VSATN     ( VSATN    );
        quant.VSATP     ( VSATP    );


        ldpc.clk   ( clk      );
        ldpc.reset ( reset    );
        ldpc.e     ( f7       );
        ldpc.s     ( f10       );

        err_counter.clk   ( clk   );
        err_counter.reset ( reset );
        err_counter.dec   ( f10   );
        err_counter.ref   ( f11   );
        err_counter.dec_frame  ( dec_frame    );
        err_counter.err_frame  ( err_frame    );
        err_counter.err_bits   ( _err_bits    );
        err_counter.err_frames ( _err_frames  );
        err_counter.proc_bits  ( _proc_bits   );
        err_counter.proc_frames( _proc_frames );
        err_counter.choice_conf(choice_conf);

        mbps_compute.clk       ( clk   );
        mbps_compute.reset     ( reset );
        mbps_compute.dec_frame ( dec_frame  );
        mbps_compute.mbps      ( mbps_value );
        mbps_compute.choice_conf(choice_conf);

        ber_counter.clk  ( clk         );
        ber_counter.reset( reset       );
        ber_counter.decs ( __proc_bits );
        ber_counter.errs ( __err_bits  );
        ber_counter.xer  ( ber_value   );

        fer_counter.clk  ( clk           );
        fer_counter.reset( reset         );
        fer_counter.decs ( __proc_frames );
        fer_counter.errs ( __err_frames  );
        fer_counter.xer  ( fer_value     );

        SC_CTHREAD(do_gen, clk.pos());
        reset_signal_is(reset, true);

        SC_METHOD(gen_signals);
        sensitive << seed;
    }

    void gen_signals()
    {
        __proc_bits   = _proc_bits.read().range  (31, 0);
        __proc_frames = _proc_frames.read().range(31, 0);
        __err_bits    = _err_bits.read().range   (31, 0);
        __err_frames  = _err_frames.read().range (31, 0);
    }

    ~sc_top_module()
    {
//        cout << "Fifo f1 : " << f1.num_available() << endl;
    }

    void do_gen()
    {
        proc_bits.write  ( 0 );
        proc_frames.write( 0 );
        err_bits.write   ( 0 );
        err_frames.write ( 0 );
        wait();

        while( true )
        {
            proc_bits.write  (_proc_bits  );
            proc_frames.write(_proc_frames);
            err_bits.write   (_err_bits   );
            err_frames.write (_err_frames );
            wait();
        }
    }


private:
    sc_encoder         encoder;
    sc_bpsk            bpsk;
#ifndef CHANNEL_MKL
    sc_xorshift128     randc;
    sc_awgn            awgn;
#else
    sc_intel_mkl       randc;
    sc_fake_awgn       awgn;
#endif
    sc_adder           adder;
    sc_quantizer       quant;
    sc_fec             ldpc;
    sc_error_counter   err_counter;
    sc_mbps_compute    mbps_compute;

    sc_xer_compute     ber_counter;
    sc_xer_compute     fer_counter;

    sc_fifo< BIT       > f1;
    sc_fifo< float     > f2;
    sc_fifo< float     > f3;
    sc_fifo< float     > f4;
    sc_fifo< float     > f5;
    sc_fifo< float     > f6;
    sc_fifo< LLR       > f7;
//    sc_fifo< TYPE_LLRS > f8;
//    sc_fifo< TYPE_BITS > f9;
    sc_fifo< BIT       > f10;
    sc_fifo< BIT       > f11;

    sc_signal< BIT > s1;
    sc_signal< BIT > s2;
    sc_signal< BIT > dec_frame;
    sc_signal< BIT > err_frame;

    sc_signal< sc_uint<64> > _proc_bits;
    sc_signal< sc_uint<64> > _proc_frames;
    sc_signal< sc_uint<64> > _err_bits;
    sc_signal< sc_uint<64> > _err_frames;

    sc_signal< sc_uint<32> > __proc_bits;
    sc_signal< sc_uint<32> > __proc_frames;
    sc_signal< sc_uint<32> > __err_bits;
    sc_signal< sc_uint<32> > __err_frames;

};

#endif
