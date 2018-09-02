#ifndef PARTITIONS_H
#define PARTITIONS_H

#include "headers.h"

void Fill_eid(double W_val, double p, int q, double cx, double cy, double cz, int dc, int cc, int ec, int sc, int dc_stat, int stat, double etot, int id, int cc_segm, int nphe, int cc_sect){
	 //Electron ID
            //std::cout <<"electron id" <<std::endl;
            //EID Precut
            //double W_val = WP(0,p,cx,cy,cz);//physics.h
            Fill_WQ2( 0, 0, 0, p, cx, cy, cz); //{set,cut,top,p,cx,cy,cz} histograms.h
            Fill_fid(0,0,W_val,cx,cy,cz);//type, cut, cx, cy, cz //fiducial histograms.h
            Fill_sf(0,W_val,etot,p);
            Fill_MinCC(cc_sect,nphe,cc_segm,0);
            //std::cout <<1;
    	    //EID 1
            bool sf_p,fid_p;
            sf_p = false;
            fid_p = false;
           bool cc_p = false;

            if(min_cc( cc_segm, cc_sect, nphe)){
                Fill_sf(6,W_val,etot,p); //sf histograms.h
                cc_p = true;
            }
            else{
                Fill_sf(8,W_val,etot,p);//sf histograms.h
            }
            if(eid_1(dc,cc,ec,sc)){//eid.h
              //  std::cout <<2;
                Fill_WQ2( 0, 1,0, p, cx, cy, cz); // histograms.h
            }
            //EID 2
            if(eid_2(dc,cc,ec,sc,dc_stat,q,stat)){//eid.h
            //    std::cout <<3;
                Fill_WQ2( 0, 2, 0, p, cx, cy, cz); // histograms.h
            }
            //EID 3
            if(eid_3(p, q, cx, cy, cz, dc, cc, ec, sc, dc_stat,stat)){//eid.h
            //    std::cout <<4;
                Fill_WQ2( 0, 3, 0, p, cx, cy, cz); // histograms.h
            }
            //EID 4
            if(eid_4( p, q, cx, cy, cz, dc, cc, ec, sc, dc_stat, stat, etot)){//eid.h
              //  std::cout <<5;
                Fill_WQ2( 0, 4, 0, p, cx, cy, cz); // histograms.h
               // Fill_fid(0,3,W_val,cx,cy,cz);//histograms.h
               // Fill_sf(3,W_val,etot,p); //histograms.h
                //Fill_MinCC(cc_sect, nphe,cc_segm, 4);
            }
            //std::cout<<std::endl <<"Entering eid5 from partitions" <<std::endl;
            if(eid_5( p, q, cx, cy, cz, dc, cc, ec, sc, dc_stat, stat, etot, cc_sect, cc_segm, nphe)){
                Fill_WQ2( 0, 9, 0, p, cx, cy, cz); // histograms.h
                Fill_fid(0,3,W_val,cx,cy,cz);//histograms.h
                Fill_sf(3,W_val,etot,p); //histograms.h
                Fill_MinCC(cc_sect, nphe,cc_segm, 4);
                //std::cout<<" Wrote after eid 5" <<std::endl;
            }
            //Sanity
            if((int)q == -1 && (int)dc_stat > 0 && (int)stat >0){
              //  std::cout <<6;
                Fill_WQ2( 0, 5, 0, p, cx, cy, cz); // histograms.h
            }
            //Fiducial
            if(fid_e(p,cx,cy,cz)){
               // std::cout <<7;
                Fill_WQ2( 0, 6, 0, p, cx, cy, cz); // histograms.h
                Fill_fid(0,1,W_val,cx,cy,cz);//histograms.h
                Fill_MinCC(cc_sect, nphe,cc_segm, 2);
                Fill_sf(5,W_val,etot,p); //histograms.h
                fid_p=true;
            }
            else{
              //  std::cout <<8;
            	Fill_fid(0,2,W_val,cx,cy,cz);//histograms.h
                Fill_sf(7,W_val,etot,p);//sf histograms.h
            }
            //Sampling Fraction
            if(sf_e(p,etot,cx,cy)){
              //  std::cout <<9;
                Fill_WQ2( 0, 7, 0, p, cx, cy, cz); // histograms.h
                Fill_sf(1,W_val,etot,p);
                Fill_MinCC(cc_sect, nphe,cc_segm, 1);
                sf_p=true;
            }
            else{
               // std::cout <<10;
            	Fill_sf(2,W_val,etot,p);//histograms.h
            }
            //ID Bank
            if((int)id==ELECTRON){
               // std::cout <<11;
                Fill_WQ2( 0, 8, 0, p, cx, cy, cz); // histograms.h
                Fill_fid(0,4,W_val,cx,cy,cz);
                Fill_sf(4,W_val,etot,p);
            }
            //Min CC
            if(sf_p && fid_p){
                Fill_MinCC(cc_sect, nphe,cc_segm, 3);
            }
            if(fid_p && cc_p){
                Fill_sf(9,W_val,etot,p);
            }
            else{
                Fill_sf(10,W_val,etot,p);
            }
            
}

/*
species for fid: {0,1,2,3}->{e,p,pip,pim}
Fill_fid(species, cut)
species for dt: {0,1,2} -> {p,pip,pim}
*/
void Fill_proton(int q, double W_val, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_t0, double sc_r0, int id){
	
     if(q == 1){
        //std::cout<<" proton id" << std::endl;
        //Pre Cut
    	//std::cout<<std::endl <<"PROTON: ";
        /*Delta T Parameters
        (s, cut, sc, p, p0, sc_r, sc_r0, sc_t, sc_t0)
        s->{0,1,2}->{p,pip,pim}
        cut->{0,1,2,3,4}->{Pre,cut,anti,pid,bank}
        */
        /*Fiducial Parameters
        (s, cut, cx, cy, cz)
        s -> {0,1,2,3} -> {e,p,pip,pim}
        cut -> {0,1,2,3,4}->{pre, cut, anti, pid, bank}
        */
        Fill_fid(1,0,W_val,cx,cy,cz);
    	Fill_dt(W_val,0,0,sc,p, p0, sc_r, sc_r0, sc_t, sc_t0);
        int duck = 0;
    	/*
        //Sanity
    	if(sanity_hadron(dc,sc,stat,dc_stat) && (int) q == 1){
    		Fill_fid(1,1,cx,cy,cz);
    		Fill_dt(0,1,p, p0, sc_r, sc_r0, sc_t, sc_t0);
    	}*/

   
    	//Delta T
    	if(delta_t_proton(p0, p, sc_r0, sc_r, sc_t0, sc_t)){
    	//	std::cout<<"delta_proton ";
            duck ++;
            Fill_dt(W_val,0,1,sc,p, p0, sc_r, sc_r0, sc_t, sc_t0);
           //std::cout<<"Delta T is: " <<delta_t(p,p0,sc_r,sc_r0,sc_t,sc_t0,mp);
    	}
        else{
        //    std::cout<<"delta_proton_anti ";
            Fill_dt(W_val,0,2,sc,p,p0,sc_r,sc_r0,sc_t,sc_t0);
            
        }
    	//Fiducial
    	if(fid_h(p, cx, cy, cz)){
    		//std::cout<<"fid_p ";
            Fill_fid(1,1,W_val,cx,cy,cz);
            duck ++;
    	}
        else{
           // std::cout<<"fid_p ";
            Fill_fid(1,2,W_val,cx,cy,cz);
            
        }
    	//Full ID
        if(is_proton(q, p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r, p0,sc_r0, sc_t0)){
        //if(duck == 2){
            Fill_dt(W_val,0,3,sc,p,p0,sc_r,sc_r0,sc_t,sc_t0);
            Fill_fid(1,3,W_val,cx,cy,cz);
        }
    	//ID Bank
       // std::cout<<" " << id <<std::endl;
    	if((int)id == PROTON){
         //   std::cout<<"I got to this part" <<std::endl;
            //std::cout<<"id_p ";
            Fill_fid(1,4,W_val,cx,cy,cz);
            Fill_dt(W_val,0,4,sc,p, p0, sc_r, sc_r0, sc_t, sc_t0);
            
        }
    }
}

void Fill_pip(int q, double W_val ,double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_t0, double sc_r0, int id){
    if(q == 1){
        //Pre Cut
        //std::cout<<std::endl <<"PIP: ";
        Fill_fid(2,0,W_val,cx,cy,cz);
        Fill_dt(W_val,1,0,sc,p, p0, sc_r, sc_r0, sc_t, sc_t0);
        int duck = 0;
       // std::cout<< "pi plus id" <<std::endl;
        /*//Sanity
        if(sanity_hadron(dc,sc,stat,dc_stat) && (int) q == 1){
            Fill_fid(2,1,cx,cy,cz);
            Fill_dt(1,1,p, p0, sc_r, sc_r0, sc_t, sc_t0);
        }*/
       // Fill_dt_vert(1,p,sc_r,sc_t);
        //Charge
    
        //Delta T
        
        if(delta_t_pion(p0, p, sc_r0, sc_r, sc_t0, sc_t)){
            //std::cout<<"dt_pip ";
            Fill_dt(W_val,1,1,sc,p, p0, sc_r, sc_r0, sc_t, sc_t0);
            duck++;
           // std::cout<<delta_t(p,p0,sc_r,sc_r0,sc_t,sc_t0,mp);
        }
        else{
           // std::cout<<"dt_pip_anti ";
            Fill_dt(W_val,1,2,sc,p,p0,sc_r,sc_r0,sc_t,sc_t0);
            
        }
        //Fiducial
        if(fid_h(p, cx, cy, cz)){
           // std::cout<<"fid_pip ";
            Fill_fid(2,1,W_val,cx,cy,cz);
            duck++;
            
        }
        else{
           // std::cout<<"fid_pip_anti ";
            Fill_fid(2,2,W_val,cx,cy,cz);
            
        }
        
        //Full ID
        if(is_pip(q, p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r, p0,sc_r0, sc_t0)){
        //if(duck == 2){
            Fill_fid(2,3,W_val,cx,cy,cz);
            Fill_dt(W_val,1,3,sc,p,p0,sc_r,sc_r0,sc_t,sc_t0);
        }
        //ID Bank
        if((int)id == PION){
           // std::cout<<"bank_pip ";
            Fill_fid(2,4,W_val,cx,cy,cz);
            Fill_dt(W_val,1,4,sc,p, p0, sc_r, sc_r0, sc_t, sc_t0);
            
        }
    }
}

void Fill_pim(int q, double W_val, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_t0, double sc_r0, double cc, double ec, double etot, double vx, double vy, double vz, int id){
   // std::cout<<std::endl <<"q is: " <<q <<std::endl;
    if( q == -1){
        //Pre Cut
       // std::cout<<std::endl <<"PIM: ";
       // std::cout<< "pi minus id" <<std::endl;
        Fill_fid(3,0,W_val,cx,cy,cz);
        Fill_dt(W_val,2,0,sc,p, p0, sc_r, sc_r0, sc_t, sc_t0);
        int duck = 0;
      //  Fill_dt_vert(2,p,sc_r,sc_t);
       /* //Sanity
        if(sanity_hadron(dc,sc,stat,dc_stat) && (int) q == -1){
            Fill_fid(3,1,cx,cy,cz);
            Fill_dt(2,1,p, p0, sc_r, sc_r0, sc_t, sc_t0);
        }*/
    
        //Delta T
        if(delta_t_pion(p0, p, sc_r0, sc_r, sc_t0, sc_t)){
        //    std::cout<<"dt_pi- ";
            Fill_dt(W_val,2,1,sc,p, p0, sc_r, sc_r0, sc_t, sc_t0);
            duck ++;
        }
        else{
         //   std::cout<<"dt_pi-_anti ";
            Fill_dt(W_val,2,2,sc,p,p0,sc_r,sc_r0,sc_t,sc_t0);
            
        }
        //Fiducial
        if(fid_h(p, cx, cy, cz)){
         //   std::cout<<"fid_pi- ";
            Fill_fid(3,1,W_val,cx,cy,cz);
            duck++ ; 
        }
        else{
         //   std::cout<<"fid_pi-_anti ";
            Fill_fid(3,2,W_val,cx,cy,cz);
            
        }
    
    //Full ID
    //if(is_pim_plus(q, p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r, p0,sc_r0, sc_t0, cc, ec, etot, vx, vy, vz)){
        if(is_pim_plus(0,q, p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r, p0,sc_r0, sc_t0, cc, ec, etot, vx, vy, vz)){
    //if(duck == 2){
        Fill_fid(3,3,W_val,cx,cy,cz);
        Fill_dt(W_val,2,3,sc,p,p0,sc_r,sc_r0,sc_t,sc_t0);
    }
    //ID Bank
    if((int)id == -PION){
        Fill_fid(3,4,W_val,cx,cy,cz);
        Fill_dt(W_val,2,4,sc,p, p0, sc_r, sc_r0, sc_t, sc_t0);

    }
}
}
//q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1], p[0], sc_t[sc[0]-1], sc_r[sc[0]-1], id[j]);

void Fill_Hadron(int q, double W_val, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_t0, double sc_r0, double cc, double ec, double etot, double vx, double vy, double vz, int id){
   // std::cout<<std::endl <<"Fill Proton Enter" <<std::endl;
    Fill_proton(q, W_val, p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r, p0, sc_t0, sc_r0, id);
    //std::cout<<std::endl <<"Fill Pip Enter" <<std::endl;
    Fill_pip(q, W_val, p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r, p0, sc_t0, sc_r0, id);
    //std::cout<<std::endl <<"Fill Pim Enter" <<std::endl;
    Fill_pim(q, W_val, p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r, p0, sc_t0, sc_r0, cc, ec, etot, vx, vy, vz, id);
    //std::cout<<std::endl <<"Leaving Hadron Filling" <<std::endl;
}


#endif