// crossbar.cpp
#include "packet.h"
#include "crossbar.h"

void crossbar :: func()
	{
	packet v_cross0;
	packet v_cross1;
	packet v_cross2;
	packet v_cross3;
	packet v_cross4;
	sc_uint<15>  v_config;

	// functionality
	while( true )
	{ 
		wait();
		v_config = config.read();
		if (i0.event())
		{  
			v_cross0 = i0.read();
			switch (v_config(2,0)) {
				case 1:	o0.write(v_cross0); break;
				case 2: o1.write(v_cross0); break;
				case 3: o2.write(v_cross0); break;
				case 4: o3.write(v_cross0); break;
				case 5:	o4.write(v_cross0); break;
				default: cout << "---------------------------------wrong destination   " <<endl ;break ;
			}
		}
		if (i1.event())
		{
			v_cross1 = i1.read();
			switch (v_config(5,3)) {
				case 1:	o0.write(v_cross1); break;
				case 2:	o1.write(v_cross1); break;
				case 3: o2.write(v_cross1); break;
				case 4: o3.write(v_cross1); break;
				case 5: o4.write(v_cross1); break;
				default: cout << "------------------------------------wrong destination   " <<endl;  break ;
			}
		}
		if (i2.event())
		{ 
			v_cross2 = i2.read();
			switch (v_config(8,6)) {
				case 1:	o0.write(v_cross2); break;
				case 2: o1.write(v_cross2); break;
				case 3: o2.write(v_cross2); break;
				case 4: o3.write(v_cross2); break;
				case 5: o4.write(v_cross2); break;
				default: cout << "---------------------------------wrong destination   " <<endl; break ;
			}
		}
		if (i3.event())
		{ 
			v_cross3 = i3.read();
			switch (v_config(11,9)) {
				case 1:	o0.write(v_cross3); break;
				case 2: o1.write(v_cross3); break;
				case 3: o2.write(v_cross3); break;
				case 4: o3.write(v_cross3); break;
				case 5: o4.write(v_cross3); break;
				default: cout << "----------------------------------wrong destination   " <<endl; break ;
			}
		}
		if (i4.event())
		{ 
			v_cross4 = i4.read();
			switch (v_config(14,12)) {
				case 1:	o0.write(v_cross4); break;
				case 2: o1.write(v_cross4); break;
				case 3: o2.write(v_cross4); break;
				case 4: o3.write(v_cross4); break;
				case 5: o4.write(v_cross4); break;
				default: cout << "-------------------------------------wrong destination" <<endl ;break ;
			}
		}
	}
}
