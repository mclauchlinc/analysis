#ifndef EVENT_PRO_H
#define EVENT_PRO_H

#include "constants.h"
#include "TLorentzVector.h"
#include "physics.h"





//Missing Mass for Delta
double MM_2(TLorentzVector k1_mu, TLorentzVector k2_mu){
	return (k_mu_e16 + p_mu - k1_mu - k2_mu).Mag2();
}

bool MM_D((double p1, double cx1,   double cy1,   double cz1,   double m1, double p2=0, double cx2=0, double cy2=0, double cz2=0, double m2 = 0){
	bool pass = false;
	TLorentzVector k1_mu = Make_4Vector(p1,cx1,cy1,cy1,m1);//physics.h
	TLorentzVector k2_mu = Make_4Vector(p2,cx2,cy2,cz2,m2);//physics.h
	//double MM = (k_mu_e16 + p_mu - k1_mu - k2_mu - k3_mu).Mag2();
	double MM = MM_2(k1_mu,k2_mu);
	double upper = MM_D_center + MM_D_sigma;
	double lower = MM_D_center - MM_D_sigma;
	if(MM > lower && MM < upper){
		pass = true;
	}
	return pass;
}


//Event selection for the Delta ++
//Pi minus with MM cut on the Delta
//Measured pi-
bool isDpp_mpim(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int idx_1, int idx_2){
	bool pass = false;
	bool delta_present = false;
	int s = 0;
	bool P_0 = false;
	bool P_1 = false;
	P_0 = eid(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, 4); //eid.h
	P_1 = is_pim( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);	//hid.h
	delta_present = MM_D(p0,cx0,cy0,cz0,me,p1,cx1,cy1,cz1,mpi); //event_pro.h
	if(P_0 && P_1 && delta_present){
		pass = true;
	}
	return pass;
}

//No measured pi-
bool isDpp_nmpim(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int idx_1, int idx_2){
	bool pass1 = false;
	bool pass2 = false;
	bool delta_p = false;
	double p_pim, cx_pim, cy_pim, cz_pim, px_pim, py_pim, pz_pim;
	TVector3 pim_stuff;
	int s = 0;
	bool P_0 = false;
	bool P_1 = false;
	bool P_2 = false;
	bool P_3 = false;
	bool P_4 = false;
	P_0 = eid(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, 4);
	P_1 = is_proton( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);
	P_2 = is_pip( q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, p0, sc_r0, sc_t0);
	P_3 = is_pip( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);
	P_4 = is_proton( q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, p0, sc_r0, sc_t0);
	if(P_0 && P_1 && P_2){
		if(idx_1 != idx_2){ //Makes sure we aren't looking at the same particle
			if(P_1 && !P_3){//Make sure proton doesn't also pass as a pi+
				if(P_2 && !P_4){ //Make sure pi+ doesn't also pass as a proton
					s++;
				}
			}
		}
	}
	if(s == 1){//To make sure the event is unique*/ //Check to see if this cross check is taking out too many guys
		pass1 = true;
	}
	if(pass1){
		pz_pim = energy_e16 - p0*cz0 p1*cz1 - p2*cz2;
		py_pim = -p0*cy0 - p1*cy1 - p2*cy2;
		px_pim = -p0*cx0 - p1*cx1 - p2*cx2;
		pim_stuff.SetXYZ(px_pim,py_pim,pz_pim);
		p_pim = pim_stuff.Mag();
		cx_pim = px_pim/p_pim;
		cy_pim = py_pim/p_pim;
		cz_pim = pz_pim/p_pim; 
		delta_p = MM_D(p0,cx0,cy0,cz0,me,p_pim,cx_pim,cy_pim,cz_pim,mpi);
		if(delta_p){
			pass2 = true;
		}
	}
	return pass2;
}



//Event Selection for the Delta +
/*
proton cut on pi0 or pi + with cut on neutron
Then make sure the MM with just electron comes to the delta
*/
bool isDp_p(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int idx_1, int idx_2){
	bool pass = false;
	bool delta_present = false;
	int s = 0;
	bool P_0 = false;
	bool P_1 = false;
	P_0 = eid(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, 4); //eid.h
	P_1 = is_p( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);	//hid.h
	delta_present = MM_D(p0,cx0,cy0,cz0,me,p1,cx1,cy1,cz1,mpi); //event_pro.h
	if(P_0 && P_1 && delta_present){
		pass = true;
	}
	return pass;
}

bool isDp_pip(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int idx_1, int idx_2){
	bool pass = false;
	bool delta_present = false;
	int s = 0;
	bool P_0 = false;
	bool P_1 = false;
	P_0 = eid(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, 4); //eid.h
	P_1 = is_pip( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);	//hid.h
	delta_present = MM_D(p0,cx0,cy0,cz0,me,p1,cx1,cy1,cz1,mpi); //event_pro.h
	if(P_0 && P_1 && delta_present){
		pass = true;
	}
	return pass;
}



//Event Selection for the Delta 0
//Pi + with MM cut on the Delta


#endif