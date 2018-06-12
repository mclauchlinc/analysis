#ifndef EID_H
#define EID_H

#include "constants.h"
#include "sanity_cuts.h"
#include "vertex.h"
#include "fiducial.h"
#include "electron_ec.h"
#include "cc_cut.h"
#include "cc_hist.h"
#include "headers.h"

/*
Identifies electrons
Sanity cuts: dc, cc, ec, sc, stat, dc_stat, q
Vertex Cuts: vz (eventually p, vx, vy)
Fiducial Cuts: p, cx, cy, cz
Min Energy in EC cuts: 
Sampling Fraction Cut: 
 */
//Level 1 is it registering in all detector systems
bool eid_1 ( int dc, int cc, int ec, int sc){
	bool pass = kFALSE;
	if( (int)dc>0 && (int)cc>0 && (int)sc>0 && (int)ec>0){
		pass = kTRUE;
	}
	return pass;
}

//Level 2 is a sanity check on charge and stats
bool eid_2( int dc, int cc, int ec, int sc, int dc_stat, int q, int stat){
	bool pass = kFALSE;
	//pass Level 1 && Sanity Electron
	if(eid_1(dc,cc,ec,sc) && (int)q == -1 && (int)dc_stat > 0 && (int)stat >0){ //Changed q to +1 9/21/2017
		pass = kTRUE;
	}
	return pass;
}

//Level 3 are adding fiducial cuts
bool eid_3(double p, int q, double cx, double cy, double cz, int dc, int cc, int ec, int sc, int dc_stat, int stat){
	bool pass = kFALSE;
	//pass Level 1 & 2 plus fiducial
	if(eid_2(dc,cc,ec,sc,dc_stat,q,stat) && fid_e(p,cx,cy,cz)){
		pass = kTRUE;
	}
	return pass;
}

//Level 4 adds minimum energy and sampling fraction 
bool eid_4(double p, int q, double cx, double cy, double cz, int dc, int cc, int ec, int sc, int dc_stat, int stat, double etot){
	//Pass Level 1, 2, & 3 plus EC things
	bool pass = kFALSE;
	if(eid_3(p,q,cx,cy,cz,dc,cc,ec,sc,dc_stat,stat) && min_ec(etot) && sf_e(p,etot,cx,cy)){
		pass = kTRUE;
	}
	return pass;
}

bool eid_5(double p, int q, double cx, double cy, double cz, int dc, int cc, int ec, int sc, int dc_stat, int stat, double etot, int cc_sect, int cc_segm, int nphe){
	bool pass = false;
	if(eid_4(p, q, cx, cy, cz, dc, cc, ec, sc,dc_stat, stat, etot) && min_cc(cc_segm,cc_sect,nphe)){
		pass = true;
	}
}

//Level 5 adds vertex corrections and cuts
//bool eid_5
//Not done yet

bool eid( double p, int q, double cx, double cy, double cz, double vx, double vy, double vz, int dc, int cc, int ec, int sc, int dc_stat, double etot, int stat, int cc_sect, int cc_segm, int nphe, int level)
{
	bool is_electron = kFALSE;
	
	if(level>=1){
		switch(level){
			case 1:
				if(eid_1(dc,cc,ec,sc)){
					is_electron = kTRUE;
				}
			break;
			case 2:
				if(eid_2(dc,cc,ec,sc,dc_stat,q,stat)){
					is_electron = kTRUE;
				}
			break;
			case 3:
				if(eid_3(p,q,cx,cy,cz,dc,cc,ec,sc,dc_stat,stat)){
					is_electron = kTRUE;
				}
			break;
			case 4:
				if(eid_4(p,q,cx,cy,cz,dc,cc,ec,sc,dc_stat,stat,etot)){
					is_electron = kTRUE;
				}
			break;
			case 5:
				if(eid_5(p,q,cx,cy,cz,dc,cc,ec,sc,dc_stat,stat,etot,cc_segm,cc_sect,nphe)){
					is_electron = true;
				}
			break;
	}

	return is_electron;
}

#endif /* EID_H */