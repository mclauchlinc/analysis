#ifndef HID_H
#define HID_H

#include "constants.h"
#include "TROOT.h"
#include "sanity_cuts.h"
#include "delta_t_id.h" 
#include "delta_t.h"
#include "fiducial.h"


bool is_proton( int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r)
{
	bool proton = kFALSE;
	if(sanity_hadron(dc,sc,stat,dc_stat)==kTRUE && (int)q==1)
	{
		if(delta_t_proton(p, sc_r, sc_t, sc) == kTRUE)
		{
			if( fid_h( p, cx, cy, cz) == kTRUE)
			{
				proton = kTRUE;
			}
		}
	}
	return proton;
}

bool is_pion(double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r)
{
	bool pion = kFALSE;
	if(sanity_hadron(dc,sc,stat,dc_stat)==kTRUE)
	{
		if(delta_t_pion( p, sc_r, sc_t, sc) == kTRUE)
		{
			if( fid_h( p, cx, cy, cz) == kTRUE)
			{
				pion = kTRUE;
			}
		}
	}
	return pion;
}

bool is_pip( int q, double p,  double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r)
{
	bool pip = kFALSE;
	if(is_pion( p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r) == kTRUE)
	{
		if( (int)q == 1)
		{
			pip = kTRUE;
		}
	}
	return pip;
}

bool is_pim( int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r)
{
	bool pim = kFALSE;
	if(is_pion( p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r) == kTRUE)
	{
		if( (int)q == -1)
		{
			pim = kTRUE;
		}
	}
	return pim;
}

#endif /* HID_H */