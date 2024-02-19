// source.h
#include "packet.h"
SC_MODULE(source) {

  sc_out<packet> packet_out; 
  sc_in<sc_uint<4> > source_id; 
  sc_in<bool > ach_in;			// input acknowledgment
  sc_in_clk CLK;
  sc_in<int> d_est;
  sc_in<sc_uint<4> > ch_k;
  int pkt_snt;					// variable for recording of packet sent

  void func();
  
  SC_CTOR(source)
    {
      SC_CTHREAD(func, CLK.pos());
	  pkt_snt=0;
    }  
};
