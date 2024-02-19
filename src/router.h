#include "packet.h"
#include "buf_fifo.h"
#include "crossbar.h"
#include "arbiter.h"
SC_MODULE(router) {
    sc_in<packet>  in0;
    sc_in<packet>  in1;
    sc_in<packet>  in2;
    sc_in<packet>  in3;
	sc_in<packet>  in4;

	sc_in<sc_uint<4> > router_id;

    sc_out<packet>  out0;
    sc_out<packet>  out1;
    sc_out<packet>  out2; 
    sc_out<packet>  out3;
	sc_out<packet>  out4;
	
	sc_in<bool>  inack0;
    sc_in<bool>  inack1;
    sc_in<bool>  inack2;
    sc_in<bool>  inack3;
	sc_in<bool>  inack4;

	sc_out<bool>  outack0;
    sc_out<bool>  outack1;
    sc_out<bool>  outack2;
    sc_out<bool>  outack3;
	sc_out<bool>  outack4;

	sc_in<bool> rclk;
	
	buf_fifo* buf0;
	buf_fifo* buf1;
	buf_fifo* buf2;
	buf_fifo* buf3;
	buf_fifo* buf4;

	arbiter* arbiter0;
	crossbar* crossbar0;

	sc_signal<sc_uint<7>  >  req_s_0;
    sc_signal<sc_uint<7>  >  req_s_1;
    sc_signal<sc_uint<7>  >  req_s_2;
    sc_signal<sc_uint<7>  >  req_s_3;
	sc_signal<sc_uint<7>  >  req_s_4;

	sc_signal<sc_uint<4>  >  free_s;
    sc_signal<sc_uint<15>  >  select_s;

	sc_signal<sc_uint<1> >  gr_s_0;
    sc_signal<sc_uint<1> >  gr_s_1;
    sc_signal<sc_uint<1> >  gr_s_2;
    sc_signal<sc_uint<1> >  gr_s_3;
	sc_signal<sc_uint<1> >  gr_s_4;

	sc_signal<packet>  re_s_0;
    sc_signal<packet>  re_s_1;
    sc_signal<packet>  re_s_2;
    sc_signal<packet>  re_s_3;
	sc_signal<packet>  re_s_4;
	
	void func();
	int pkt_sent;

    SC_CTOR(router) 
		{
		buf0 = new buf_fifo ("buf0");
		buf0->wr(in0);
		buf0->re(re_s_0);
		buf0->ack(outack0);
		buf0->req(req_s_0);
		buf0->grant(gr_s_0);
		buf0->bclk(rclk);

		buf1 = new buf_fifo ("buf1");
		buf1->wr(in1);
		buf1->re(re_s_1);
		buf1->ack(outack1);
		buf1->req(req_s_1);
		buf1->grant(gr_s_1);
		buf1->bclk(rclk);

		buf2 = new buf_fifo ("buf2");
		buf2->wr(in2);
		buf2->re(re_s_2);
		buf2->ack(outack2);
		buf2->req(req_s_2);
		buf2->grant(gr_s_2);
		buf2->bclk(rclk);

		buf3 = new buf_fifo ("buf3");
		buf3->wr(in3);
		buf3->re(re_s_3);
		buf3->ack(outack3);
		buf3->req(req_s_3);
		buf3->grant(gr_s_3);
		buf3->bclk(rclk);

		buf4 = new buf_fifo ("buf4");
		buf4->wr(in4);
		buf4->re(re_s_4);
		buf4->ack(outack4);
		buf4->req(req_s_4);
		buf4->grant(gr_s_4);
		buf4->bclk(rclk);

		arbiter0 = new arbiter ("arbiter0");
		
		arbiter0->arbiter_id(router_id);

		arbiter0->free_out0(inack0);
		arbiter0->free_out1(inack1);
		arbiter0->free_out2(inack2);
		arbiter0->free_out3(inack3);
		arbiter0->free_out4(inack4);
		
		arbiter0->req0(req_s_0);
		arbiter0->req1(req_s_1);
		arbiter0->req2(req_s_2);
		arbiter0->req3(req_s_3);
		arbiter0->req4(req_s_4);

		arbiter0->grant0(gr_s_0);
		arbiter0->grant1(gr_s_1);
		arbiter0->grant2(gr_s_2);
		arbiter0->grant3(gr_s_3);
		arbiter0->grant4(gr_s_4);

		arbiter0->aselect(select_s);

		arbiter0->aclk(rclk);

		crossbar0 = new crossbar ("crossbar0");
		crossbar0->i0(re_s_0);
		crossbar0->i1(re_s_1);
		crossbar0->i2(re_s_2);
		crossbar0->i3(re_s_3);
		crossbar0->i4(re_s_4);

		crossbar0->o0(out0);
		crossbar0->o1(out1);
		crossbar0->o2(out2);
		crossbar0->o3(out3);
		crossbar0->o4(out4);

		crossbar0->config(select_s);

		SC_THREAD(func);
		sensitive << in0 << in1 << in2 << in3 << in4; 
		pkt_sent = 0;
    }   
};

