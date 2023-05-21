// main.cpp
#include "systemc.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "packet.h"
#include "source.h"
#include "sink.h"
#include "router.h"


int sc_main(int argc, char *argv[])
{
	sc_signal<packet> si_source[4];
	sc_signal<packet> si_input[16];
	sc_signal<packet> si_zero[16];
	sc_signal<packet> si_sink[4];
	sc_signal<packet> si_output[16];
	sc_signal<bool>  si_ack_src[4],si_ack_ou[16];
	sc_signal<bool>  si_ack_sink[4],si_ack_in[16];
	sc_signal<bool>  si_ack_zero[16];
	sc_signal<sc_uint<4> >  siid0,siid1,siid2,siid3;
	sc_signal<sc_uint<4> > scid0,scid1, scid2, scid3;
	sc_signal<sc_uint<4> > id0,id1, id2, id3;
	sc_signal<int> scinput;
	sc_signal<sc_uint<4> > check,check2,check3,check4;
	sc_signal <packet> sioutput[4];
	int i,j;
	sc_clock s_clock("S_CLOCK", 125, SC_NS, 0.5, 0.0, SC_NS); // source clock
	//sc_clock s_clock("S_CLOCK", 5, SC_NS, 0.5, 10.0, SC_NS); // source clk = router clk
	sc_clock r_clock("R_CLOCK", 5, SC_NS, 0.5, 10.0, SC_NS);	// router clock
	sc_clock d_clock("D_CLOCK", 5, SC_NS, 0.5, 10.0, SC_NS);	// destination clock
	
	// Module instiatiations follow
	// Note that modules can be connected by hooking up ports 
	// to signals by name or by using a positional notation
	
	
	source source0("source0");
	source0(si_source[0], scid0, si_ack_src[0], s_clock, scinput,check);
	
	
    source source1("source1");
	source1(si_source[1], scid1, si_ack_src[1], s_clock, scinput,check);

	source source2("source2");
	source2(si_source[2], scid2, si_ack_src[2], s_clock, scinput,check);
	
	
	source source3("source3");
	source3(si_source[3], scid3, si_ack_src[3], s_clock, scinput,check);


	//source source4("source4");
	//source4(si_source[4], id4, si_ack_src[4], s_clock);
	//need codes
	//need codes
	//need codes

	//need codes
	//need codes


	router router0("router0");
	// hooking up signals to ports by name
	router0.in0(si_source[0]);
	router0.in1(si_output[2]);
	router0.in2(si_output[4]);
	router0.in3(si_zero[0]);
	router0.in4(si_zero[1]);

	router0.router_id(id0);
	//router0.router_id(0);

	router0.out0(si_sink[0]);
	router0.out2(si_output[0]);
	router0.out3(si_output[1]);
	router0.out1(si_zero[2]);
	router0.out4(si_zero[3]);

	router0.inack0(si_ack_sink[0]);
	router0.inack1(si_ack_in[2]);
	router0.inack2(si_ack_in[4]);
	router0.inack3(si_ack_zero[0]);
	router0.inack4(si_ack_zero[1]);

	router0.outack0(si_ack_src[0]);
	router0.outack2(si_ack_in[0]);
	router0.outack3(si_ack_in[1]);
	router0.outack1(si_ack_zero[2]);
	router0.outack4(si_ack_zero[3]);

	router0.rclk(r_clock);

	router router1("router1");
	// hooking up signals to ports by name
	router1.in0(si_source[1]);
	router1.in1(si_output[0]);
	router1.in2(si_output[6]);
	router1.in3(si_zero[4]);
	router1.in4(si_zero[5]);
	

	router1.router_id(id1);
	//router1.router_id(1);

	router1.out0(si_sink[1]);
	router1.out4(si_output[2]);
	router1.out3(si_output[3]);
	router1.out1(si_zero[6]);
	router1.out2(si_zero[7]);

	router1.inack0(si_ack_sink[1]);
	router1.inack1(si_ack_in[0]);
	router1.inack2(si_ack_in[6]);
	router1.inack3(si_ack_zero[4]);
	router1.inack4(si_ack_zero[5]);

	router1.outack0(si_ack_src[1]);
	router1.outack4(si_ack_in[2]);
	router1.outack3(si_ack_in[3]);
	router1.outack2(si_ack_zero[6]);
	router1.outack1(si_ack_zero[7]);

	router1.rclk(r_clock);
	//need 64 code statement

	router router2("router2");
	// hooking up signals to ports by name
	router2.in0(si_source[2]);
	router2.in1(si_output[1]);
	router2.in2(si_output[7]);
	router2.in3(si_zero[8]);
	router2.in4(si_zero[9]);
	

	router2.router_id(id2);
	//router2.router_id(2);

	router2.out0(si_sink[2]);
	router2.out1(si_output[4]);
	router2.out2(si_output[5]);
	router2.out3(si_zero[10]);
	router2.out4(si_zero[11]);
	

	router2.inack0(si_ack_sink[2]);
	router2.inack1(si_ack_in[1]);
	router2.inack2(si_ack_in[7]);
	router2.inack3(si_ack_zero[8]);
	router2.inack4(si_ack_zero[9]);
	

	router2.outack0(si_ack_src[2]);
	router2.outack1(si_ack_in[4]);
	router2.outack2(si_ack_in[5]);
	router2.outack3(si_ack_zero[10]);
	router2.outack4(si_ack_zero[11]);
	

	router2.rclk(r_clock);

	router router3("router3");
	// hooking up signals to ports by name
	router3.in0(si_source[3]);
	router3.in1(si_output[3]);
	router3.in2(si_output[5]);
	router3.in3(si_zero[12]);
	router3.in4(si_zero[13]);

	router3.router_id(id3);
	//router3.router_id(3);

	router3.out0(si_sink[3]);
	router3.out1(si_output[6]);
	router3.out4(si_output[7]);
	router3.out2(si_zero[14]);
	router3.out3(si_zero[15]);
	

	router3.inack0(si_ack_sink[3]);
	router3.inack1(si_ack_in[3]);
	router3.inack2(si_ack_in[5]);
	router3.inack3(si_ack_zero[12]);
	router3.inack4(si_ack_zero[13]);
	

	router3.outack0(si_ack_src[3]);
	router3.outack1(si_ack_in[6]);
	router3.outack4(si_ack_in[7]);
	router3.outack2(si_ack_zero[14]);
	router3.outack3(si_ack_zero[15]);

	router3.rclk(r_clock);

  	//need codes

	sink sink0("sink0");
	sink0(si_sink[0], si_ack_sink[0], siid0, d_clock, sioutput[0]);


	sink sink1("sink1");
	sink1(si_sink[1], si_ack_sink[1], siid1, d_clock, sioutput[1]);


	sink sink2("sink2");
	sink2(si_sink[2], si_ack_sink[2], siid2, d_clock, sioutput[2]);
	
	
	sink sink3("sink3");
	sink3(si_sink[3], si_ack_sink[3], siid3, d_clock, sioutput[3]);

	//sink sink4("sink4");
	//sink4(si_sink[4], si_ack_sink[4], id1, d_clock);
	
	



//sc_start(0, SC_NS);
  // tracing:
	// trace file creation
	sc_trace_file *tf = sc_create_vcd_trace_file("graph");
	// External Signals
//sc_trace(tf, s_clock.signal(), "s_clock");
//sc_trace(tf, d_clock.signal(), "d_clock");
	sc_trace(tf, s_clock, "s_clock");
	sc_trace(tf, d_clock, "d_clock");
	sc_trace(tf, r_clock, "r_clock");
	sc_trace(tf, si_source[0], "si_source[0]");
	sc_trace(tf, si_source[1], "si_source[1]");
	sc_trace(tf, si_source[2], "si_source[2]");
	sc_trace(tf, si_source[3], "si_source[3]");
	//need codes
	//need codes
	sc_trace(tf, si_sink[0], "si_sink[0]");
	sc_trace(tf, si_sink[1], "si_sink[1]");
	sc_trace(tf, si_sink[2], "si_sink[2]");
	sc_trace(tf, si_sink[3], "si_sink[3]");
	//need codes
	//need codes
	
	cout<< "Enter source ID from 0 to 3: ";
	cin >> i;
	cout<<"Enter Destination from 0 to 3: ";
	cin >> j;
	scinput.write(j);

	id0.write(0);
	id1.write(1);
	id2.write(2);
	id3.write(3);
	//sioutput.write(j);
	//if(i==0)scid0.write(0);
	//if(i==1)scid1.write(1);
	//if(i==2)scid2.write(2);
	//if(i==3)scid3.write(3);
	check.write(i);
	//check2.write(1);
	//check3.write(2);
	//check4.write(3);

	scid0.write(0);
	scid1.write(1);
	scid2.write(2);
	scid3.write(3);
	//if(j==0)siid0.write(0);
	//if(j==1)siid1.write(1);
	//if(j==2)siid2.write(2);
	//if(j==3)siid3.write(3);
	siid0.write(0);
	siid1.write(1);
	siid2.write(2);
	siid3.write(3);
	//need codes
	//need codes

	cout << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << endl << " 2X2 mesh NOC simulator containing 2 5x5 Wormhole router " << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "This is the simulation of a 2x2 Wormhole router.  " << endl; 
	cout << "We assume the router has 5 input/output ports, with 4 buffers per input port " << endl;
	cout << "and each flit has 21 bits width " << endl;
	cout << "  Press \"Return\" key to start the simulation..." << endl << endl;

	getchar();
	sc_start(10*125+124,SC_NS); // during [(10*125)+124] ns 10 packets will be sent and received 

	sc_close_vcd_trace_file(tf);

	cout << endl << endl << "-------------------------------------------------------------------------------" << endl;
	cout << "End of switch operation..." << endl;
	if(i==0)cout << "Total number of packets sent: " <<  source0.pkt_snt<< endl;//need codes to be added
	if(j==0)cout << "Total number of packets received: " <<  sink0.pkt_recv<< endl;//need codes to be added
	if(i==1)	cout << "Total number of packets sent: " <<  source1.pkt_snt<< endl;//need codes to be added
	if(j==1)cout << "Total number of packets received: " <<  sink1.pkt_recv<< endl;//need codes to be added
	if(i==2)	cout << "Total number of packets sent: " <<  source2.pkt_snt<< endl;//need codes to be added
	if(j==2)cout << "Total number of packets received: " <<  sink2.pkt_recv<< endl;//need codes to be added
	if(i==3)	cout << "Total number of packets sent: " <<  source3.pkt_snt<< endl;//need codes to be added
	if(j==3)cout << "Total number of packets received: " <<  sink3.pkt_recv<< endl;//need codes to be added

	cout << "-------------------------------------------------------------------------------" << endl;
    cout << "  Press \"Return\" key to end the simulation..." << endl << endl;
	getchar();
  return 0;

}

