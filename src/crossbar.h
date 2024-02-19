#include "packet.h"
SC_MODULE(crossbar) {

    sc_in<packet>  i0;
    sc_in<packet>  i1;
    sc_in<packet>  i2;
    sc_in<packet>  i3;
	sc_in<packet>  i4;

    sc_out<packet>  o0;
    sc_out<packet>  o1;
    sc_out<packet>  o2; //error here
    sc_out<packet>  o3; // error here
	sc_out<packet>  o4;

	sc_in<sc_uint<15> >  config;
	
	void func();
    SC_CTOR(crossbar) 
		{
		SC_THREAD(func);
		sensitive << i0;
		sensitive << i1;
		sensitive << i2;
		sensitive << i3;
		sensitive << i4;
    }  
};
