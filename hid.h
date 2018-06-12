#ifndef HID_H
#define HID_H

#include "constants.h"
#include "TROOT.h"
#include "sanity_cuts.h"
#include "delta_t_id.h" 
#include "delta_t.h"
#include "fiducial.h"
#include "eid.h"

bool hid_sanity(int dc, int sc, int stat, int dc_stat){
	bool pass = false;
	if( (dc > 0) && (sc > 0)){ //&& (stat > 0) && (dc_stat >0)){
		pass = true;
	}
	return pass;
}

// q, p, cx, cy, cz, dc, sc, stat, dc_stat, sc_t, sc_r, p0,sc_r0, sc_t0
bool is_proton( int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_r0, double sc_t0)
{
	bool proton = false;
	if(hid_sanity(dc, sc, stat, dc_stat))
	{
		if(q == 1){
			if(delta_t_proton(p0, p, sc_r0, sc_r, sc_t0, sc_t)){
				if(!delta_t_pion(p0,p,sc_r0,sc_r,sc_t0,sc_t)){
					if( fid_h( p, cx, cy, cz))
					{
						proton = true;
					}
				}
			}
		}
	}
	return proton;
}

bool is_pip( int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_r0, double sc_t0)
{
	bool pass = false;
	if(hid_sanity(dc, sc, stat, dc_stat))
	{
		if( q == 1){ //Note that charge is strange right now 9/22
			if(delta_t_pion(p0, p, sc_r0, sc_r, sc_t0, sc_t)){
				if(!delta_t_proton(p0, p, sc_r0, sc_r, sc_t0, sc_t)){
					if( fid_h( p, cx, cy, cz)){
						pass = true;
					}
				}
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
		if(q == -1){
			if(delta_t_pion(p0, p, sc_r0, sc_r, sc_t0, sc_t))
			{
				if( fid_h( p, cx, cy, cz))
				{
					pass = true;
				}
			}
		}
	}
	return pass;
}


double e_dt_cut(double p){
	return (dt_e_A*TMath::Exp(-dt_e_a*p)+dt_e_b);
}

//A cut along the delta t of the electron, but when trying to identify a pi- 
bool dt_electron(double p, double sc_r0, double sc_r, double sc_t0, double sc_t, double m){
	bool pass = false;
	double delt_d = sc_r*(sqrt((m*m+p*p)/(me*me+p*p))-1);
	double delt_te = delta_t(p,0.0,sc_r, sc_r0, sc_t, sc_t0, me);
	double delt_tp = delta_t(p,0.0,sc_r, sc_r0, sc_t, sc_t0, m); 
	double delt_up1 = e_dt_cut(p) + dt_e_sig; 
	double delt_do1 = e_dt_cut(p) - dt_e_sig;
	double delt_up2 = delt_d + dt_e_sig;
	double delt_do2 = delt_d - dt_e_sig;

	//std::cout<<std::endl <<"Momentum: " <<p <<std::endl;
	//std::cout<<"delta_t: " <<delt_tp <<"| electron: " <<delt_d <<std::endl;

	if(delt_te > dt_e_sig || delt_te < -dt_e_sig){
		pass = true;
	}
	return pass;
}

bool pim_eid(int eid_par, double p, double sc_r0, double sc_r, double sc_t0, double sc_t, double cc, double etot, double ec, double cx, double cy){
	bool pass = false;
	switch(eid_par){
				//no eid cut
				case 0:
					pass = true;
					break;
				//the cut along the delta t electron band
				case 1:
					if(dt_electron(p,sc_r0,sc_r,sc_t0,sc_t,mpi)){
					pass = true;
					}
					break;
				//If it passes the CC then it doesn't pass 
				case 2:
					if(cc == 0){
						pass = true; 
					}
					break;
				//If it passes the EC then it doesn't pass
				case 3:
					if(ec == 0){
						pass = true;
					}
				//If it passes the SF then it doesn't pass
				case 4:
					if(!sf_e(p,etot,cx,cy)){
						pass = true;
					}
					break;
			}
	return pass; 
}


bool is_pim_plus(int eid_par, int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_r0, double sc_t0, double cc, double ec, double etot, double vx, double vy, double vz){
	bool pass = false;
	if(is_pim(q,p,cx,cy,cz,dc,sc,stat,dc_stat,sc_t,sc_r,p0,sc_r0, sc_t0)){
		//if(!eid(p,q,cx,cy,cz,vx,vy,vz,dc,cc,ec,sc,dc_stat,stat,etot,4)){
		//if(true){
			//Cutting out various parts of electron ID
			pass = pim_eid(eid_par, p, sc_r0, sc_r, sc_t0, sc_t, cc, etot, ec, cx, cy);
		//}
	}
	return pass;
}



#endif /* HID_H */