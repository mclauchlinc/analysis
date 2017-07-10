#ifndef PARTITIONS_H
#define PARTITIONS_H

#include "headers.h"

void Fill_eid(Float_t p, Char_t q, Float_t cx, Float_t cy, Float_t cz, UChar_t dc, UChar_t cc, UChar_t ec, UChar_t sc, UChar_t dc_stat, UChar_t stat, Float_t etot, Char_t id){
	 //Electron ID
            //EID Precut
            Fill_WQ2( 0, 0, p, cx, cy, cz); // histograms.h
            Fill_fid(0,0,cx,cy,cz);//type, cut, cx, cy, cz //histograms.h
            Fill_sf(0,etot,p);
    	    //EID 1
            if(eid_1(dc,cc,ec,sc)){//eid.h
                Fill_WQ2( 0, 1, p, cx, cy, cz); // histograms.h
            }
            //EID 2
            if(eid_2(dc,cc,ec,sc,dc_stat,q,stat)){//eid.h
                Fill_WQ2( 0, 2, p, cx, cy, cz); // histograms.h
            }
            //EID 3
            if(eid_3(p, q, cx, cy, cz, dc, cc, ec, sc, dc_stat,stat)){//eid.h
                Fill_WQ2( 0, 3, p, cx, cy, cz); // histograms.h
            }
            //EID 4
            if(eid_4( p, q, cx, cy, cz, dc, cc, ec, sc, dc_stat, stat, etot)){//eid.h
                Fill_WQ2( 0, 4, p, cx, cy, cz); // histograms.h
                Fill_fid(0,3,cx,cy,cz);//histograms.h
                Fill_sf(3,etot,p); //histograms.h
            }
            //Sanity
            if((int)q == -1 && (int)dc_stat > 0 && (int)stat >0){
                Fill_WQ2( 0, 5, p, cx, cy, cz); // histograms.h
            }
            //Fiducial
            if(fid_e(p,cx,cy,cz)){
                Fill_WQ2( 0, 6, p, cx, cy, cz); // histograms.h
                Fill_fid(0,1,cx,cy,cz);//histograms.h
            }
            else{
            	Fill_fid(0,2,cx,cy,cz);//histograms.h
            }
            //Sampling Fraction
            if(sf_e(p,etot,cx,cy)){
                Fill_WQ2( 0, 7, p, cx, cy, cz); // histograms.h
                Fill_sf(1,etot,p);
            }
            else{
            	Fill_sf(2,etot,p);//histograms.h
            }
            //ID Bank
            if(id==ELECTRON){
                Fill_WQ2( 0, 8, p, cx, cy, cz); // histograms.h
                Fill_fid(0,4,cx,cy,cz);
                Fill_sf(4,etot,p);
            }
}

void Fill_proton(){
	//Pre Cut
	Fill_fid(1,0,cx,cy,cz);
	Fill_dt(0,0,p);
	//Sanity
	if(sanity_hadron(dc,sc,stat,dc_stat) && (int) q == 1){
		Fill_fid(1,1,cx,cy,cz);
		Fill_dt(0,1,p);
	}
	//Delta T
	if(delta_t_proton()){
		Fill_dt(0,2,p);
	}
	//Fiducial
	if(fid_h(p, cx, cy, cz)){
		Fill_fid(1,2,cx,cy,cz);
	}
	//Full ID
	//ID Bank
	if(id == PROTON)
}

#endif