#ifndef HID_H
#define HID_H

#include "constants.h"
#include "TROOT.h"
#include "sanity_cuts.h"
#include "delta_t_id.h" 
#include "delta_t.h"
#include "fiducial.h"


bool is_proton( Char_t q, Float_t p, Float_t beta, Float_t cx, Float_t cy, Float_t cz, UChar_t dc, UChar_t sc, Char_t stat, Char_t dc_stat, Float_t sc_t, Float_t sc_r)
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

bool is_pion(Float_t p, Float_t beta, Float_t cx, Float_t cy, Float_t cz, UChar_t dc, UChar_t sc, Char_t stat, Char_t dc_stat, Float_t sc_t, Float_t sc_r)
{
	bool pion = kFALSE;
	if(sanity_hadron(dc,sc,stat,dc_stat)==kTRUE)
	{
		if(delta_t_pion(idx, p, sc_r, sc_t, sc) == kTRUE)
		{
			if( fid_h( p, cx, cy, cz) == kTRUE)
			{
				pion = kTRUE;
			}
		}
	}
	return pion;
}

bool is_pip( Char_t q, Float_t p, Float_t beta, Float_t cx, Float_t cy, Float_t cz, UChar_t dc, UChar_t sc, Char_t stat, UChar_t dc_stat, Float_t sc_t, Float_t sc_r)
{
	bool pip = kFALSE;
	if(is_pion( p, beta, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r) == kTRUE)
	{
		if( (int)q == 1)
		{
			pip = kTRUE;
		}
	}
	return pip;
}

bool is_pim( Char_t q, Float_t p, Float_t beta, Float_t cx, Float_t cy, Float_t cz, UChar_t dc, UChar_t sc, Char_t stat, Char_t dc_stat, Float_t sc_t, Float_t sc_r)
{
	bool pim = kFALSE;
	if(is_pion( p, beta, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r) == kTRUE)
	{
		if( (int)q == -1)
		{
			pim = kTRUE;
		}
	}
	return pim;
}

#endif /* HID_H */