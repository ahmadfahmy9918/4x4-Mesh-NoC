#include "systemc.h"
SC_MODULE(arbiter) {

	sc_in<sc_uint<4> > arbiter_id;
    sc_in<sc_uint<7>  >  req0;
    sc_in<sc_uint<7>  >  req1;
    sc_in<sc_uint<7>  >  req2;
    sc_in<sc_uint<7>  >  req3;
	sc_in<sc_uint<7>  >  req4;

	sc_in<bool  >  free_out0;
	sc_in<bool  >  free_out1;
	sc_in<bool  >  free_out2;
	sc_in<bool  >  free_out3;
	sc_in<bool  >  free_out4;

    sc_out<sc_uint<15> >  aselect;

	sc_out<sc_uint<1> >  grant0;
    sc_out<sc_uint<1> >  grant1;
    sc_out<sc_uint<1> >  grant2;
    sc_out<sc_uint<1> >  grant3;
	sc_out<sc_uint<1> >  grant4;

	sc_in<bool> aclk;
	
	void func();

    SC_CTOR(arbiter) 
     {
      SC_THREAD(func);
	  sensitive << aclk.neg();
    }   
};
