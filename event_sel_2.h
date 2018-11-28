#ifndef EVENT_SEL_2_H
#define EVENT_SEL_2_H

#include "headers.h"

bool e_valid = false;
bool pro_valid = false;
bool pip_valid = false;
bool pro_valid2 = false;
bool pip_valid2 = false;
bool pim_valid = false; 

TLorentzVector Miss_Pro = (0.0,0.0,0.0,0.0);
TLorentzVector Miss_Pip = (0.0,0.0,0.0,0.0);
TLorentzVector Miss_Pim= (0.0,0.0,0.0,0.0);
TLorentzVector Miss_Non = (100.0,100.0,100.0,100.0);

TLorentzVector pro_mu = (0.0,0.0,0.0,0.0);
TLorentzVector pip_mu = (0.0,0.0,0.0,0.0);
TLorentzVector pim_mu = (0.0,0.0,0.0,0.0);
TLorentzVector ele_mu = (0.0,0.0,0.0,0.0);

TLorentzVector ele0_mu = (0.0,0.0,0.0,0.0); 



TLorentzVector Pro_Top(int set, double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, int cc_sect0, int nphe0,int cc_segm0, int level0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1, double sc_r0, double sc_t0,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int cc2, int ec2, double etot2, double vx2, double vy2, double vz2){
	TLorentzVector Boop = (100.0,100.0,100.0,100.0);
	switch(set){
		case 0:
			ele0_mu = k_mu_e16;
		break;
		case 1:
			ele0_mu = k_mu_e1f;
		break;
	}
	e_valid = eid(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0,  cc_sect0, cc_segm0, nphe0, level0 );
	pip_valid = is_pip( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);
	pim_valid = is_pim_plus(0, q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, p0, sc_r0, sc_t0, cc2, ec2, etot2, vx2, vy2, vz2);
	if(e_valid && pip_valid && pim_valid){
		pip_mu = Make4Vec(p1,cx1,cy1,cz1,mpi);
		pim_mu = Make4Vec(p2,cx2,cy2,cz2,mpi);
		ele_mu = Make4Vec(p0,cx0,cy0,cz0,me);
		Boop = (ele0_mu + p_mu - pip_mu - pim_mu - ele_mu);
	}
	return Boop;
}

TLorentzVector Pip_Top(int set, double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, int cc_sect0, int nphe0,int cc_segm0, int level0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1, double sc_r0, double sc_t0,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int cc2, int ec2, double etot2, double vx2, double vy2, double vz2){
	TLorentzVector Boop = (100.0,100.0,100.0,100.0);
	switch(set){
		case 0:
			ele0_mu = k_mu_e16;
		break;
		case 1:
			ele0_mu = k_mu_e1f;
		break;
	}
	e_valid = eid(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0,  cc_sect0, cc_segm0, nphe0, level0 );
	pro_valid = is_pro( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);
	pim_valid = is_pim_plus(0, q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, p0, sc_r0, sc_t0, cc2, ec2, etot2, vx2, vy2, vz2);
	if(e_valid && pip_valid && pim_valid){
		pro_mu = Make4Vec(p1,cx1,cy1,cz1,mp);
		pim_mu = Make4Vec(p2,cx2,cy2,cz2,mpi);
		ele_mu = Make4Vec(p0,cx0,cy0,cz0,me);
		Boop = (ele0_mu + p_mu - pro_mu - pim_mu - ele_mu);
	}
	return Boop;
}

TLorentzVector Pim_Top(int set, double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, int cc_sect0, int nphe0,int cc_segm0, int level0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1, double sc_r0, double sc_t0,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2){
	TLorentzVector Boop = (100.0,100.0,100.0,100.0);
	switch(set){
		case 0:
			ele0_mu = k_mu_e16;
		break;
		case 1:
			ele0_mu = k_mu_e1f;
		break;
	}
	e_valid = eid(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0,  cc_sect0, cc_segm0, nphe0, level0 );
	pro_valid = is_pro( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);
	pip_valid = is_pip( q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, p0, sc_r0, sc_t0);
	if(e_valid && pip_valid && pim_valid){
		pip_mu = Make4Vec(p1,cx1,cy1,cz1,mpi);
		pim_mu = Make4Vec(p2,cx2,cy2,cz2,mpi);
		ele_mu = Make4Vec(p0,cx0,cy0,cz0,me);
		Boop = (ele0_mu + p_mu - pip_mu - pim_mu - ele_mu);
	}
	return Boop;
}

TLorentzVector Non_Top(int set, double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, int cc_sect0, int nphe0,int cc_segm0, int level0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1, double sc_r0, double sc_t0,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int q3, double p3, double cx3, double cy3, double cz3, int dc3, int sc3, int stat3, int dc_stat3, double sc_t3, double sc_r3, int cc3, int ec3, double etot3, double vx3, double vy3, double vz3){
	TLorentzVector Boop = (100.0,100.0,100.0,100.0);
	switch(set){
		case 0:
			ele0_mu = k_mu_e16;
		break;
		case 1:
			ele0_mu = k_mu_e1f;
		break;
	}
	e_valid = eid(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0,  cc_sect0, cc_segm0, nphe0, level0 );
	pro_valid = is_pro( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);
	pip_valid = is_pip( q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, p0, sc_r0, sc_t0);
	pim_valid = is_pim_plus(0, q3, p3, cx3, cy3, cz3, dc3, sc3, stat3, dc_stat3, sc_t3, sc_r3, p0, sc_r0, sc_t0, cc3, ec3, etot3, vx3, vy3, vz3);
	if(e_valid && pip_valid && pim_valid){
		pro_mu = Make4Vec(p1,cx1,cy1,cz1,mp);
		pip_mu = Make4Vec(p2,cx2,cy2,cz2,mpi);
		ele_mu = Make4Vec(p0,cx0,cy0,cz0,me);
		pim_mu = Make4Vec(p3,cx3,cy3,cz3,mpi)
		Boop = (ele0_mu + p_mu - pro_mu - pip_mu - pim_mu - ele_mu);
	}
	return Boop;
}

bool Pro_Miss_Pass(TLorentzVector Proton_mu){
	double 
}

void Event_Selector(int set, double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, int cc_sect0, int nphe0,int cc_segm0, int level0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1, double sc_r0, double sc_t0,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int q3, double p3, double cx3, double cy3, double cz3, int dc3, int sc3, int stat3, int dc_stat3, double sc_t3, double sc_r3, int cc3, int ec3, double etot3, double vx3, double vy3, double vz3){
	//set, p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, cc_sect0, nphe0, cc_segm0, level0, q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, p0, sc_r0, sc_t0, q3, p3, cx3, cy3, cz3, dc3, sc3, stat3, dc_stat3, sc_t3, sc_r3, cc3, ec3, etot3, vx3, vy3, vz3
	Miss_Pro = Pro_Top(set, p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, cc_sect0, nphe0, cc_segm0, level0, q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, sc_r0, sc_t0, q3, p3, cx3, cy3, cz3, dc3, sc3, stat3, dc_stat3, sc_t3, sc_r3, cc3, ec3, etot3, vx3, vy3, vz3);
	Miss_Pip = Pip_Top(set, p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, cc_sect0, nphe0, cc_segm0, level0, q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, sc_r0, sc_t0, q3, p3, cx3, cy3, cz3, dc3, sc3, stat3, dc_stat3, sc_t3, sc_r3, cc3, ec3, etot3, vx3, vy3, vz3)
	Miss_Pim = Pim_Top(set, p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, cc_sect0, nphe0, cc_segm0, level0, q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, sc_r0, sc_t0, q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2)
	Miss_Non = Non_Top(set, p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, cc_sect0, nphe0, cc_segm0, level0, q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, sc_r0, sc_t0, q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, q3, p3, cx3, cy3, cz3, dc3, sc3, stat3, dc_stat3, sc_t3, sc_r3, cc3, ec3, etot3, vx3, vy3, vz3);

}


#endif