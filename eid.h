#ifndef EID_H
#define EID_H

#include "constants.h"
#include "sanity_cuts.h"
#include "vertex.h"
#include "fiducial.h"
#include "electron_ec.h"

/*
Identifies electrons
Sanity cuts: dc, cc, ec, sc, stat, dc_stat, q
Vertex Cuts: vz (eventually p, vx, vy)
Fiducial Cuts: p, cx, cy, cz
Min Energy in EC cuts: 
Sampling Fraction Cut: 
 */
//Level 1 is it registering in all detector systems
bool eid_1 ( UChar_t dc, UChar_t cc, UChar_t ec, UChar_t sc){
	bool pass = kFALSE;
	if( (int)dc>0 && (int)cc>0 && (int)sc>0 && (int)ec>0){
		pass = kTRUE;
	}
	return pass;
}

//Level 2 is a sanity check on charge and stats
bool eid_2( UChar_t dc, UChar_t cc, UChar_t ec, UChar_t sc, UChar_t dc_stat, Char_t q, UChar_t stat){
	bool pass = kFALSE;
	//pass Level 1 && Sanity Electron
	if(eid_1(dc,cc,ec,sc) && (int)q == -1 && (int)dc_stat > 0 && (int)stat >0){
		pass = kTRUE;
	}
	return pass;
}

//Level 3 are adding fiducial cuts
bool eid_3(Float_t p, Char_t q, Float_t cx, Float_t cy, Float_t cz, UChar_t dc, UChar_t cc, UChar_t ec, UChar_t sc, UChar_t dc_stat, UChar_t stat){
	bool pass = kFALSE;
	//pass Level 1 & 2 plus fiducial
	if(eid_2(dc,cc,ec,sc,dc_stat,q,stat) && fid_e(p,cx,cy,cz)){
		pass = kTRUE;
	}
	return pass;
}

//Level 4 adds minimum energy and sampling fraction 
bool eid_4(Float_t p, Char_t q, Float_t cx, Float_t cy, Float_t cz, UChar_t dc, UChar_t cc, UChar_t ec, UChar_t sc, UChar_t dc_stat, UChar_t stat, Float_t etot){
	//Pass Level 1, 2, & 3 plus EC things
	bool pass = kFALSE;
	if(eid_3(p,q,cx,cy,cz,dc,cc,ec,sc,dc_stat,stat) && min_ec(etot) && sf_e(p,etot,cx,cy)){
		pass = kTRUE;
	}
	return pass;
}

//Level 5 adds vertex corrections and cuts
//bool eid_5
//Not done yet

bool eid( Float_t p, Char_t q, Float_t cx, Float_t cy, Float_t cz, Float_t vx, Float_t vy, Float_t vz, UChar_t dc, UChar_t cc, UChar_t ec, UChar_t sc, UChar_t dc_stat, Float_t etot, Char_t stat, int level)
{
	bool is_electron = kFALSE;
	
	if(level>=1){
		switch(level){
			case 1:
				if(eid_1(dc,cc,ec,sc)){
					is_electron = kTRUE;
				}
			case 2:
				if(eid_2(dc,cc,ec,sc,dc_stat,q,stat)){
					is_electron = kTRUE;
				}
			case 3:
				if(eid_3(p,q,cx,cy,cz,dc,cc,ec,sc,dc_stat,stat)){
					is_electron = kTRUE;
				}
			case 4:
				if(eid_4(p,q,cx,cy,cz,dc,cc,ec,sc,dc_stat,stat,etot)){
					is_electron = kTRUE;
				}
		}
	}

	return is_electron;
}

#endif /* EID_H */