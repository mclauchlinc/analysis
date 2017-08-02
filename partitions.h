#ifndef PARTITIONS_H
#define PARTITIONS_H

#include "headers.h"

void Fill_eid(double p, int q, double cx, double cy, double cz, int dc, int cc, int ec, int sc, int dc_stat, int stat, double etot, int id){
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
            if((int)id==ELECTRON){
                Fill_WQ2( 0, 8, p, cx, cy, cz); // histograms.h
                Fill_fid(0,4,cx,cy,cz);
                Fill_sf(4,etot,p);
            }
}

/*
species for fid: {0,1,2,3}->{e,p,pip,pim}
Fill_fid(species, cut)
species for dt: {0,1,2} -> {p,pip,pim}
*/
void Fill_proton(int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_t0, double sc_r0, int id){
	//std::cout<<" " << id;
    //Pre Cut
	Fill_fid(1,0,cx,cy,cz);
	Fill_dt(0,0,p, p0, sc_r, sc_r0, sc_t, sc_t0);
    Fill_dt_vert(0,p,-sc_r,0);
    Fill_dt_vert(1,p,0,sc_t);
    Fill_dt_vert(2,p,0,sc_t0);
	/*
    //Sanity
	if(sanity_hadron(dc,sc,stat,dc_stat) && (int) q == 1){
		Fill_fid(1,1,cx,cy,cz);
		Fill_dt(0,1,p, p0, sc_r, sc_r0, sc_t, sc_t0);
	}*/
	//Delta T
	if(delta_t_proton(p0, p, sc_r0, sc_r, sc_t0, sc_t)){
		Fill_dt(0,1,p, p0, sc_r, sc_r0, sc_t, sc_t0);
	}
    else{
        Fill_dt(0,2,p,p0,sc_r,sc_r0,sc_t,sc_t0);
    }
	//Fiducial
	if(fid_h(p, cx, cy, cz)){
		Fill_fid(1,1,cx,cy,cz);
	}
    else{
        Fill_fid(1,2,cx,cy,cz);
    }
	//Full ID
	//ID Bank
   // std::cout<<" " << id <<std::endl;
	if((int)id == PROTON){
     //   std::cout<<"I got to this part" <<std::endl;
        Fill_fid(1,4,cx,cy,cz);
        Fill_dt(0,4,p, p0, sc_r, sc_r0, sc_t, sc_t0);
    }
}

void Fill_pip(int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_t0, double sc_r0, int id){
    //Pre Cut
    Fill_fid(2,0,cx,cy,cz);
    Fill_dt(1,0,p, p0, sc_r, sc_r0, sc_t, sc_t0);
    /*//Sanity
    if(sanity_hadron(dc,sc,stat,dc_stat) && (int) q == 1){
        Fill_fid(2,1,cx,cy,cz);
        Fill_dt(1,1,p, p0, sc_r, sc_r0, sc_t, sc_t0);
    }*/
   // Fill_dt_vert(1,p,sc_r,sc_t);
    //Delta T
    if(delta_t_proton(p0, p, sc_r0, sc_r, sc_t0, sc_t)){
        Fill_dt(1,1,p, p0, sc_r, sc_r0, sc_t, sc_t0);
    }
    else{
        Fill_dt(1,2,p,p0,sc_r,sc_r0,sc_t,sc_t0);
    }
    //Fiducial
    if(fid_h(p, cx, cy, cz)){
        Fill_fid(2,1,cx,cy,cz);
    }
    else{
        Fill_fid(2,2,cx,cy,cz);
    }
    //Full ID
    //ID Bank
    if((int)id == PION && (int)q == 1){
        Fill_fid(2,4,cx,cy,cz);
        Fill_dt(1,4,p, p0, sc_r, sc_r0, sc_t, sc_t0);
    }
}

void Fill_pim(int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_t0, double sc_r0, int id){
    //Pre Cut
    Fill_fid(3,0,cx,cy,cz);
    Fill_dt(2,0,p, p0, sc_r, sc_r0, sc_t, sc_t0);
  //  Fill_dt_vert(2,p,sc_r,sc_t);
   /* //Sanity
    if(sanity_hadron(dc,sc,stat,dc_stat) && (int) q == -1){
        Fill_fid(3,1,cx,cy,cz);
        Fill_dt(2,1,p, p0, sc_r, sc_r0, sc_t, sc_t0);
    }*/
    //Delta T
    if(delta_t_proton(p0, p, sc_r0, sc_r, sc_t0, sc_t)){
        Fill_dt(2,1,p, p0, sc_r, sc_r0, sc_t, sc_t0);
    }
    else{
        Fill_dt(2,2,p,p0,sc_r,sc_r0,sc_t,sc_t0);
    }
    //Fiducial
    if(fid_h(p, cx, cy, cz)){
        Fill_fid(3,1,cx,cy,cz);
    }
    else{
        Fill_fid(3,2,cx,cy,cz);
    }
    //Full ID
    //ID Bank
    if((int)id == PION && (int)q == -1){
        Fill_fid(3,4,cx,cy,cz);
        Fill_dt(2,4,p, p0, sc_r, sc_r0, sc_t, sc_t0);
    }
}
//q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1], p[0], sc_t[sc[0]-1], sc_r[sc[0]-1], id[j]);

void Fill_Hadron(int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_t0, double sc_r0, int id){
    Fill_proton(q, p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r, p0, sc_t0, sc_r0, id);
    Fill_pip(q, p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r, p0, sc_t0, sc_r0, id);
    Fill_pim(q, p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r, p0, sc_t0, sc_r0, id);
}


#endif