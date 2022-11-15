#ifndef _my_module_
#define _my_module_

#define HUGE_FIFO 		INTER_FRAME * DEG_1
#define BIG_FIFO 		INTER_FRAME
#define SMALL_FIFO		1

#include "systemc.h"

#include "config.h"

#include "ldpc_parameters.h"

#include "process_read_write.h"
#include "process_s1.h"
#include "process_s2.h"

#define PAR_IO  true

SC_MODULE(my_module)
{
	sc_in <bool> clk;
	sc_in <bool> reset;

#ifdef _MONITORING_
	sc_out <bool> busy;
	sc_out <bool> load;
	sc_out <bool> store;
#endif

    sc_fifo_in < TYPE_LLRS > e;
    sc_fifo_out< TYPE_BITS > s;

	SC_CTOR(my_module):
		PU_s1			("CN"),
		PU_s2			("VN"),
		PU_contr		("Contr"),
	    s1_mesgs		("FM11", SMALL_FIFO),
		s1_nodes		("FN12", SMALL_FIFO),
		deg1			("DG1",  SMALL_FIFO),
		s2_mesgs		("FM21", SMALL_FIFO),
		s2_nodes		("FN22", SMALL_FIFO),
		deg2			("DG2",  SMALL_FIFO),
		sign_somme		("SS1",  SMALL_FIFO),
		min1			("M12",  SMALL_FIFO),
		min2			("M21",  SMALL_FIFO),
		tab_vContr		("VC1",  DEG_1),
#ifndef FIFO_TO_LUT
		tab_aContr		("AC1",  DEG_1),
		tab_sContr		("SC1",  DEG_1),
#endif
		posVN_f ("f1", HUGE_FIFO),
		CTRL_load_f  ("f7", SMALL_FIFO),
		CTRL_send_f ("f71", SMALL_FIFO),
		END_dec_f("f8", SMALL_FIFO)
	{
		PU_contr.clk(clk);
		PU_contr.reset(reset);
		PU_contr.e(e);
		PU_contr.s(s);

		//Monitor
#ifdef _MONITORING_
		PU_contr.load(load);
		PU_contr.busy(busy);
		PU_contr.store(store);
#endif

		PU_contr.s1_mesgs(s1_mesgs);
		PU_contr.s1_nodes(s1_nodes);
		PU_contr.deg_s1(deg1);

		PU_contr.s2_mesgs(s2_mesgs);
		PU_contr.s2_nodes(s2_nodes);

		PU_contr.posVN_p1(posVN_f);
		PU_contr.posVN_p2(posVN_f);
		PU_contr.CTRL_load_p1(CTRL_load_f);
		PU_contr.END_dec_p1(END_dec_f);
		PU_contr.CTRL_load_p2(CTRL_load_f);
		PU_contr.END_dec_p2(END_dec_f);
		PU_contr.CTRL_send_p1(CTRL_send_f);
		PU_contr.CTRL_send_p2(CTRL_send_f);

		//
		PU_s1.clk(clk);
		PU_s1.reset(reset);
		PU_s1.var_mesgs(s1_mesgs);
		PU_s1.var_nodes(s1_nodes);
		PU_s1.deg(deg1);
		PU_s1.deg_s2(deg2);

		PU_s1.sign_somme(sign_somme);
		PU_s1.min1(min1);
		PU_s1.min2(min2);

		PU_s1.tab_vContr(tab_vContr);
#ifndef FIFO_TO_LUT
		PU_s1.tab_aContr(tab_aContr);
		PU_s1.tab_sContr(tab_sContr);
#endif
		//
		PU_s2.sign_somme(sign_somme);
		PU_s2.min1(min1);
		PU_s2.min2(min2);

		PU_s2.tab_vContr(tab_vContr);
#ifndef FIFO_TO_LUT
		PU_s2.tab_aContr(tab_aContr);
		PU_s2.tab_sContr(tab_sContr);
#endif

		PU_s2.clk(clk);
		PU_s2.reset(reset);
		PU_s2.var_mesgs(s2_mesgs);
		PU_s2.var_nodes(s2_nodes);
		PU_s2.deg(deg2);
	}

/*	~my_module()
	{
		cout << " !!! EXIT !!! " << endl;
		//cout << " 	* e   			: "<< e.num_available() << endl;
		//cout << " 	* s   			: "<< s.num_free() << endl;
 		cout << " 	* s1_nodes   	: "<< s1_nodes.num_available() << endl;
		cout << " 	* s1_mesgs   	: "<< s1_mesgs.num_available() << endl;
		cout << " 	* sign_somme   	: "<< sign_somme.num_available() << endl;
		cout << " 	* min1   		: "<< min1.num_available() << endl;
		cout << " 	* min2   		: "<< min2.num_available() << endl;
		cout << " 	* tab_vContr   	: "<< tab_vContr.num_available() << endl;
		cout << " 	* tab_aContr   	: "<< tab_aContr.num_available() << endl;
		cout << " 	* tab_sContr   	: "<< tab_sContr.num_available() << endl;
		cout << " 	* s2_mesgs   	: "<< s2_mesgs.num_available() << endl;
		cout << " 	* s2_nodes   	: "<< s2_nodes.num_available() << endl;
		cout << " 	* deg1   		: "<< deg1.num_available() << endl;
		cout << " 	* deg2   		: "<< deg2.num_available() << endl;

	}
*/

private:
	// Module
	process_s1 	PU_s1;
	process_s2 	PU_s2;
	read_write 	PU_contr;

	//FIFOs
    sc_fifo < TYPE_MSGS > s1_mesgs;
	sc_fifo < TYPE_LLRS > s1_nodes;
	sc_fifo < sc_uint<6> > deg1;

	sc_fifo < TYPE_MSGS > s2_mesgs;
	sc_fifo < TYPE_LLRS > s2_nodes;
	sc_fifo < sc_uint<6> > deg2;

	sc_fifo < TYPE_MSGS > sign_somme;
	sc_fifo < TYPE_MSGS > min1;
	sc_fifo < TYPE_MSGS > min2;

	sc_fifo < TYPE_LLRS > tab_vContr;
#ifndef FIFO_TO_LUT
	sc_fifo < TYPE_LLRS > tab_aContr;
	sc_fifo < TYPE_LLRS > tab_sContr;
#endif

	sc_fifo < sc_uint< FORMAT > > posVN_f;
	sc_fifo < bool > CTRL_load_f;
	sc_fifo < bool > CTRL_send_f;
	sc_fifo < bool > END_dec_f;

};

#endif
