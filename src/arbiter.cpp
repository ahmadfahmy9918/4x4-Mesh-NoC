//arbiter.cpp
#undef SC_INCLUDE_FX

#include "packet.h"
#include "arbiter.h"

void arbiter :: func()
{
	sc_uint<1> v_connected_input[5]; //set when input is connected to an output
	sc_uint<1> v_reserved_output[6]; //set when output is reserved by a input (one output more for simple coding)
	sc_uint<4> v_req[5];
	sc_uint<5> v_free;	// status of output in term of being free
	sc_uint<4> v_id;
	sc_uint<5> v_arbit;
	sc_uint<15> v_select;	
	for(int i=0;i<5;i++){v_connected_input[i]=0;v_reserved_output[i]=0;v_req[i]=0;}
	v_free = 31;  // '11111'
	v_arbit = 0;
	v_select = 0;


	// functionality

	while( true )
	{ 
		wait();
		grant0.write(0);				// reset grant
		grant1.write(0);				// reset grant
		grant2.write(0);				// reset grant
		grant3.write(0);				// reset grant
		grant4.write(0);				// reset grant
		if (!free_out0.read()) {v_free = v_free | 1 ; }  // set the bit 0 showing the output 0 is free
		if (!free_out1.read()) {v_free = v_free | 2 ; }
		if (!free_out2.read()) {v_free = v_free | 4 ; }
		if (!free_out3.read()) {v_free = v_free | 8 ; }
		if (!free_out4.read()) {v_free = v_free | 16 ;}
//for(int i=0;i<5;i++){cout<< "Request"<< i << req0.read()[i] <<endl;}

		v_id = arbiter_id.read();
	//cout <<" ID "<< v_id <<endl;
		if (!req0.read()[4]) //if FIFO buffer is not empty 
		
		{
			//if(!v_connected_input[0]) // if input is not connected i.e. it is header
			if(v_id[1] < req0.read()[1]) v_req[0]=3; // go to east
			else {	
				if(v_id[1] > req0.read()[1])v_req[0]=5; //go to west
				else{
					if(v_id[3] < req0.read()[3])v_req[0]=4; // go to south
					else{
						if(v_id[3] > req0.read()[3])v_req[0]=2; //go to north
						else{ 
							 if(v_id[2] < req0.read()[2])v_req[0]=4; // go to south	
							 else{	
								 if(v_id[2] > req0.read()[2])v_req[0]=2; //go to north
								 else{
									 if(v_id[0] < req0.read()[0]) v_req[0]=3;// go to east
									 else{
										 if(v_id[0] > req0.read()[0])v_req[0]=5; //go to west
										 else v_req[0]=1; // that is the destination
									}
								}
							}
						}
					}
				}
			}
			switch (v_req[0]) {
				case 1:	v_arbit=v_free &  1; break;
				case 2: v_arbit=v_free &  2; break;
				case 3: v_arbit=v_free &  4; break;
				case 4: v_arbit=v_free &  8; break;
				case 5: v_arbit=v_free &  16; break;
				default: break ;
			}
			if(!v_connected_input[0]) // if input is not connected // isnt this always 0 if its been intialized as 0. 
			{
				if (v_reserved_output[v_req[0]])v_arbit=0; // if the requested output was reserved, go to next input 
			}			
			if(v_arbit!=0){
				grant0.write(1);				// set grant
				v_select.range(2,0) = v_req[0];
				v_free  = v_free & (~v_arbit);   // inactive the related output
				v_connected_input[0]=1; // input 0 is connected
				v_reserved_output[v_req[0]]=1; // output is reserved
				if(req0.read()[5]){
					v_connected_input[0]=0;v_reserved_output[v_req[0]]=0;} // if it is tail flit, reset connection and reservation
			}
		}
		if (!req1.read()[4]) //if buffer is not empty 
		{
			//if(!v_connected_input[1]) // if input is not connected i.e. it is header
			if(v_id[1] < req1.read()[1]) v_req[1]=3; // go to east
			else {	
				if(v_id[1] > req1.read()[1])v_req[1]=5; //go to west
				else {
					if(v_id[3] < req1.read()[3])v_req[1]=4; // go to south
					else {
						if(v_id[3] > req1.read()[3])v_req[1]=2; //go to north
						else{
							if(v_id[2] < req1.read()[2])v_req[1]=4; // go to south
							else{
								if(v_id[2] > req1.read()[2])v_req[1]=2; //go to north
								else{
									if(v_id[0] < req1.read()[0]) v_req[1]=3; // go to east
									else{
										if(v_id[0] > req1.read()[0])v_req[1]=5; //go to west
										else v_req[1]=1; // that is the destination
									}
								}
							}
						}
					}
				}
			}
			switch (v_req[1]) {
				case 1:	v_arbit=v_free &  1; break;
				case 2: v_arbit=v_free &  2; break;
				case 3: v_arbit=v_free &  4; break;
				case 4: v_arbit=v_free &  8; break;
				case 5: v_arbit=v_free &  16; break;
				default: break ;
			}
			if(!v_connected_input[1]) // if input is not connected
			{
				if (v_reserved_output[v_req[1]])v_arbit=0; // if the requested output was reserved, go to next input 
			}
			if(v_arbit!=0){					// if there is any free output
				grant1.write(1);	// set grant
				v_select.range(5,3) = v_req[1];
				v_free  = v_free & (~v_arbit);   // inactive the related outputs
				v_connected_input[1]=1; // input 1 is connected
				v_reserved_output[v_req[1]]=1; // output is reserved
				if(req1.read()[5]){v_connected_input[1]=0;v_reserved_output[v_req[1]]=0;} // if it is tail flit, reset connection and reservation
			}
		}
		if (!req2.read()[4]) //if buffer is not empty 
		{
			//if(!v_connected_input[2]) // if input is not connected i.e. it is header
			if(v_id[1] < req2.read()[1]) v_req[2]=3; // go to east
			else {	
				if(v_id[1] > req2.read()[1])v_req[2]=5; //go to west
				else {
					if(v_id[3] < req2.read()[3])v_req[2]=4; // go to south
					else {
						if(v_id[3] > req2.read()[3])v_req[2]=2; //go to north
						else{
							if(v_id[2] < req2.read()[2])v_req[2]=4; // go to south
							else{
								if(v_id[2] > req2.read()[2])v_req[2]=2; //go to north
								else{
									if(v_id[0] < req2.read()[0]) v_req[2]=3; // go to east
									else{
										if(v_id[1] > req2.read()[1])v_req[2]=5; //go to west
										else v_req[2]=1; // that is the destination
									}
								}
							}
						}
					}
				}
			}			
			switch (v_req[2]) {
				case 1:	v_arbit=v_free &  1; break;
				case 2: v_arbit=v_free &  2; break;
				case 3: v_arbit=v_free &  4; break;
				case 4: v_arbit=v_free &  8; break;
				case 5: v_arbit=v_free &  16; break;
				default: break ;
			}
			if(!v_connected_input[2]) // if input is not connected
			{
				if (v_reserved_output[v_req[2]])v_arbit=0; // if the requested output was reserved, go to next input 
			}
			if(v_arbit!=0){
				grant2.write(1);	// set grant
				v_select.range(8,6) = v_req[2];
				v_free  = v_free & (~v_arbit);   // inactive the related outputs
				v_connected_input[2]=1; // input 1 is connected
				v_reserved_output[v_req[2]]=1; // output is reserved
				//if(req2.read()[5]){v_connected_input[2]=0;v_reserved_output[v_req[2]]=0;} // if it is tail flit, reset connection and reservation
			}
		}

		if (!req3.read()[4]) //if buffer is not empty 
		{
			//if(!v_connected_input[3]) // if input is not connected i.e. it is header
			if(v_id[1] < req3.read()[1]) v_req[3]=3; // go to east
			else {	
				if(v_id[1] > req3.read()[1])v_req[3]=5; //go to west
				else {
					if(v_id[3] < req3.read()[3])v_req[3]=4; // go to south
					else {
						if(v_id[3] > req3.read()[3])v_req[3]=2; //go to north
						else{
							if(v_id[2] < req3.read()[2])v_req[3]=4; // go to south
							else{
								if(v_id[2] > req3.read()[2])v_req[3]=2; //go to north
								else{
									if(v_id[0] < req3.read()[0]) v_req[3]=3; // go to east
									else{
										if(v_id[0] > req3.read()[0])v_req[3]=5; //go to west
										else v_req[3]=1; // that is the destination
									}
								}
							}
						}
					}
				}
			}			
			switch (v_req[3]) {
				case 1:	v_arbit=v_free &  1; break;
				case 2: v_arbit=v_free &  2; break;
				case 3: v_arbit=v_free &  4; break;
				case 4: v_arbit=v_free &  8; break;
				case 5: v_arbit=v_free &  16; break;
				default: break ;
			}
			if(!v_connected_input[3]) // if input is not connected
			{
				if (v_reserved_output[v_req[3]])v_arbit=0; // if the requested output was reserved, go to next input 
			}
			if(v_arbit!=0){
				grant3.write(1);	// set grant
				v_select.range(11,9) = v_req[3];
				v_free  = v_free & (~v_arbit);   // inactive the related outputs
				v_connected_input[3]=1; // input 3 is connected
				v_reserved_output[v_req[3]]=1; // output is reserved
				if(req3.read()[5]){v_connected_input[3]=0;v_reserved_output[v_req[3]]=0;} // if it is tail flit, reset connection and reservation
			}
		}

		if (!req4.read()[4]) //if buffer is not empty  
		{
			//if(!v_connected_input[4]) // if input is not connected i.e. it is header
			if(v_id[1] < req4.read()[1]) v_req[4]=3; // go to east
			else {	
				if(v_id[1] > req4.read()[1])v_req[4]=5; //go to west
				else {
					if(v_id[3] < req4.read()[3])v_req[4]=4; // go to south
					else {
						if(v_id[3] > req4.read()[3])v_req[4]=2; //go to north
						else{
							if(v_id[2] < req4.read()[2])v_req[4]=4; // go to south
							else{
								if(v_id[2] > req4.read()[2])v_req[4]=2; //go to north
								else{
									if(v_id[0] < req4.read()[0]) v_req[4]=3; // go to east
									else{
										if(v_id[0] > req4.read()[0])v_req[4]=5; //go to west
										else v_req[4]=1; // that is the destination
									}
								}
							}
						}
					}
				}
			}			
			switch (v_req[4]) {
				case 1:	v_arbit=v_free &  1; break;
				case 2: v_arbit=v_free &  2; break;
				case 3: v_arbit=v_free &  4; break;
				case 4: v_arbit=v_free &  8; break;
				case 5: v_arbit=v_free &  16; break;
				default: break ;
			}
			if(!v_connected_input[4]) // if input is not connected
			{
				if (v_reserved_output[v_req[4]])v_arbit=0; // if the requested output was reserved, go to next input 
			}
			if(v_arbit!=0){
				grant4.write(1);	// set grant
				v_select.range(14,12) = v_req[4];
				v_free  = v_free & (~v_arbit);   // inactive the related outputs
				v_connected_input[4]=1; // input 4 is connected
				v_reserved_output[v_req[4]]=1; // output is reserved
				if(req4.read()[5]){v_connected_input[4]=0;v_reserved_output[v_req[4]]=0;} // if it is tail flit, reset connection and reservation
			}
		}
	aselect.write(v_select);
	}
}
