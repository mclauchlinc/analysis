#ifndef HID_H
#define HID_H

#include "constants.h"
#include "TROOT.h"
#include "sanity_cuts.h"
#include "delta_t_id.h" 
#include "delta_t.h"
#include "fiducial.h"

bool hid_sanity(int dc, int sc, int stat, int dc_stat){
	bool pass = false;
	if(dc > 0 && sc > 0 && stat > 0 && dc_stat >0){
		pass = true;
	}
	return pass;
}

// q, p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r, p0,sc_r0, sc_t0
bool is_proton( int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_r0, double sc_t0)
{
	bool proton = false;
	if(hid_sanity(dc, sc, stat, dc_stat) && q == 1)
	{
		if(delta_t_proton(p0, p, sc_r0, sc_r, sc_t0, sc_t))
		{
			if( fid_h( p, cx, cy, cz))
			{
				proton = true;
			}
		}
	}
	return proton;
}

bool is_pip( int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_r0, double sc_t0)
{
	bool pass = false;
	if(hid_sanity(dc, sc, stat, dc_stat) && q == 1 )
	{
		if(delta_t_pion(p0, p, sc_r0, sc_r, sc_t0, sc_t))
		{
			if( fid_h( p, cx, cy, cz))
			{
				pass = true;
			}
		}
	}
	return pass;
}
bool is_pim( int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_r0, double sc_t0)
{
	bool pass = false;
	if(hid_sanity(dc, sc, stat, dc_stat) && q == -1)
	{
		if(delta_t_pion(p0, p, sc_r0, sc_r, sc_t0, sc_t))
		{
			if( fid_h( p, cx, cy, cz))
			{
				pass = true;
			}
		}
	}
	return pass;
}

#endif /* HID_H */