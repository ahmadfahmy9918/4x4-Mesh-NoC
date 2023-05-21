// buf_fifo.cpp

#include "buf_fifo.h"

    void fifo::packet_in(const packet& data_packet)
    {
      registers[reg_num++] = data_packet; 
	  empty = false;
      if (reg_num == 4) full = true;      
    }

    packet fifo::packet_out()
    {
		reg_num--;
		packet temp;
		temp = registers[0];
		if (reg_num == 0) empty = true;
		else 
	{ 
        registers[0] = registers[1];
	    registers[1] = registers[2];
	    registers[2] = registers[3];
        }
	   full = false;
      return(temp);  
    }

void buf_fifo :: func()
{
	fifo q0;	// define a FIFO buffer
	q0.reg_num = 0;
	q0.full  = false;
	q0.empty = true;
	packet b_temp;
	req.write((q0.registers[0].h_t,q0.empty, q0.registers[0].dest));// this outputs header or tail flit while empty and destination ID
	//cout << "header/tail flit" << q0.registers[0].h_t <<endl;

	// functionality
	while( true )
	{ 
		wait();
		
		
		/////received packet/////     
		if (wr.event()) 
		{			
			q0.packet_in(wr.read());
			ack.write(q0.full);
			req.write((q0.registers[0].h_t, q0.empty, q0.registers[0].dest));
			//cout << "header/tail flit" << q0.registers[0].h_t <<endl;
		}
	    ///// sent packets out/////    
		if (bclk.event()) 
		{
//			req.write((q0.empty, q0.registers[0].dest));
			if(grant.read() == 1)
			{
				b_temp = q0.packet_out();
				re.write(b_temp);
				ack.write(q0.full);
				req.write((q0.registers[0].h_t, q0.empty, q0.registers[0].dest));
				//cout << "header/tail flit" << q0.registers[0].h_t <<endl;
			}
		}
	}
}
