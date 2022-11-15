//#include "./sc_top_module/sc_dual_top_module.h"

#include "sc_top_module.h"
#include <iomanip>

//#define DEBUG

#ifdef __RTL_SIMULATION__
#include "sc_terminal.h"
#else
#include "sc_terminal/sc_terminal.h"
#endif


#define _CONF	0
#define _VSATN	-31
#define _VSATP	31
#define _BETA	4
#define _NBIT	10

int main (int argc, char * argv []){

	cout << "(II) Parametres de simulation : " << endl;
	cout << "     - CONFIG 	  : " << (_CONF) << endl;
	cout << "     - width     : "  << (_N)                       << endl;
	cout << "     - height    : "  << (_K)                       << endl;
	cout << "     - SIMD width: "  << (Q)                        << endl;
	cout << "     - LLR width : "  << (LLR_BITS)                 << endl;
	cout << "     - MSB width : "  << (MSG_BITS)                 << endl;
	cout << "     - LLR bus   : [" << (Q * LLR_BITS-1) << ", 0]" << endl;
	cout << "     - MSB bus   : [" << (Q * MSG_BITS-1) << ", 0]" << endl;
	cout << "     - MAX_ITERS : " << (_NBIT) << endl;
	cout << "     - QUANT  	  : [" << (_BETA) <<", " << (_VSATN) <<", " << (_VSATP)<< "]" << endl;

	sc_signal< sc_uint<8> > conf;
	sc_signal< float > 		sigma;
	sc_signal< sc_uint<8> > beta;
	sc_signal< sc_int<8> > 	vsatn;
	sc_signal< sc_int<8> > 	vsatp;
	sc_signal< sc_uint<8> > nbit;
	sc_signal< sc_uint<16> > cpt;
	sc_clock clock("clock", 10, SC_NS, 0.5);
	sc_signal< bool > reset;

	sc_signal< bool       > enable;
	//sc_signal< sc_uint<5> > snr;
	sc_signal< sc_uint<8> > seed;

	sc_signal< sc_uint<64> > err_bits;
	sc_signal< sc_uint<64> > err_frames;
	sc_signal< sc_uint<64> > proc_bits;
	sc_signal< sc_uint<64> > proc_frames;
	sc_signal< sc_uint<32> > mbps_value;
	sc_signal< sc_uint<32> > ber_value;
	sc_signal< sc_uint<32> > fer_value;

	sc_signal< BIT > err_frame;

	sc_top_module top ( "top"  );
	/* Co-simulation */
	//sc_top_module_rtl_wrapper top ( "top"  );
	//sc_dual_top_module top ( "top"  );
	top.clk      ( clock     );
	top.reset    ( reset     );
	top.enable   ( enable    );
	top.SIGMA    ( sigma    );
	top.seed     ( seed      );
	top.choice_conf (conf);
	top.BETA (beta);
	top.VSATN (vsatn);
	top.VSATP (vsatp);
	top.NBIT (nbit);
	top.CPT(cpt);

	top.err_bits   ( err_bits    );
	top.err_frames ( err_frames  );
	top.proc_bits  ( proc_bits   );
	top.proc_frames( proc_frames );
	top.ber_value  ( ber_value   );
	top.fer_value  ( fer_value   );
	top.mbps_value ( mbps_value  );

	sc_terminal     term( "term" );
	term.clk        ( clock       );
	term.reset      ( reset       );
	term.err_bits   ( err_bits    );
	term.err_frames ( err_frames  );
	term.proc_bits  ( proc_bits   );
	term.proc_frames( proc_frames );
	term.mbps_value ( mbps_value  );
	term.fer_value  ( fer_value   );

	cout << "(II) Reset the system" << endl;

	beta = _BETA;
	vsatn = _VSATN;
	vsatp = _VSATP;
	nbit = _NBIT;
	conf = _CONF;

	//snr    = 2.00f * (4); // x4 a cause du format de codage en vigule fixe
	float snr = 2.0f;
	float _R = 0.5f;
#ifdef DEBUG
	//sigma = 1.0f / sqrtf( 2.f * _R * powf( 10.f , snr/10.f ) );
	sigma = 0.0f;
#else
	float sigma1 = 1.0f / sqrtf( 2.f * _R * powf( 10.f , snr/10.f ) );
	sigma = sigma1;
	cout << "		(!!!) Sigma = " <<std::fixed << std::setprecision(4) << sigma1 << " (!!!)" << endl;


#endif

	enable = false;
	reset  = true;
	seed   = 0xF0;

	sc_start( 100, SC_NS );
	reset  = false;
	sc_start( 100, SC_NS );

	cout << "(II) Running the system" << endl;
	enable = true;
#ifdef DEBUG
	sc_start( 2000, SC_US );
#else
	sc_start(1000, SC_MS);
#endif

  return 0;
}
