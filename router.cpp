// router.cpp
#include "router.h"
#define SIM_NUM 30

void router :: func()
{
	int sim_count;

  // FILE *result;

  // initialization

  sim_count  = 0;

  // result = fopen("result","w");



  // functionality
  while( sim_count++ < SIM_NUM )
    { 
       wait();
	    if (in0.event()){pkt_sent++;}//cout <<  "			source "<< in0.read().id << "    router" << router_id.read()<< endl;} 
		if (in1.event()){pkt_sent++;}//cout << "			source "<< in1.read().id << "    router" << router_id.read()<< endl;}
		if (in2.event()){pkt_sent++;}//cout << "			source "<< in2.read().id << "    router" << router_id.read()<< endl;}
		if (in3.event()){pkt_sent++;}//cout << "			source "<< in3.read().id << "    router" << router_id.read()<< endl;}
		if (in4.event()){pkt_sent++;}//cout << "			source "<< in4.read().id << "    router" << router_id.read()<< endl;}

    } 

 // sc_stop();
  
}
