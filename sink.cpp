// sink.cpp
#include "sink.h"
void sink::receive_data(){

	packet v_packet;
	if ( sclk.event() ) ack_out.write(false);
	if (packet_in.event() ) {
	 //if (sink_id.read()== (packet_in.read()).dest) {
	 
		pkt_recv++ ;
		ack_out.write(true);
		v_packet= packet_in.read();
		cout << "			New Pkt:  " << (int)v_packet.data<< " is received from source: " << (int)v_packet.id  << " by sink:  " << (int)sink_id.read() << endl;
		//}		
	// else {
			
	// v_packet= packet_in.read();
	 //cout << "			New Pkt:  " << (int)v_packet.data<< " is received from source: " << (int)v_packet.id  << " by sink:  " << (int)sink_id.read() << endl;
	 //packet_out_sink.write(v_packet);
	 //cout<< "packet in this sink has now outputted to router" <<endl;
	//	 }
	
  }
}
