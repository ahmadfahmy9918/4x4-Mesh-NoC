#include "packet.h"
SC_MODULE(buf_fifo) {
    sc_in	<packet>		wr;
    sc_out	<packet>		re;	
	sc_in	<sc_uint<1> >	grant;
	sc_out	<sc_uint<7> >	req;
    sc_out	<bool>			ack;
	sc_in	<bool>			bclk;

	void func();

    SC_CTOR(buf_fifo) 
     {
      SC_THREAD(func);
      sensitive << wr;
	  sensitive<< bclk.pos();
    }  
};

struct fifo {
public:

   packet registers[4];
   bool full;
   bool empty;
   int reg_num;
  
   // constructor

   fifo()
    {
      full = false;
      empty = true;
      reg_num = 0;
    };

	// methods

	void packet_in(const packet& data_packet);   
	packet packet_out();
};
