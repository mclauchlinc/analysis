#ifndef PARTICLE_CLASS_H
#define PARTICLE_CLASS_H

class Electron{//Objects that will have all the info necessary for Electron ID
public:
	int q_e;
	int dc_e;
	int sc_e;
	int ec_e;
	int cc_e;
	int stat_e;
	int dc_stat_e;
	double p_e;
	double cx_e;
	double cy_e;
	double cz_e;
	double etot_e;
};

class Hadron{ //Objects that will have all the info necessary for Hadron ID
	public:
	int charge;
	int dc_h;
	int sc_h;
	int stat_h;
	int dc_stat_h;
	double p_h;
	double cx_h;
	double cy_h;
	double cz_h;
	double sc_t_h;
	double sc_r_h;
	double sc_t0_h;
	double sc_r0_h;
};



#endif