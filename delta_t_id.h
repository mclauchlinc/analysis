#ifndef DELTA_T_ID_H
#define DELTA_T_ID_H


#include "delta_t.h"

//Takes in delta t and determines if it is in the cut
/*
 p = particle momentum p[k]
 p0 = p[0]
 d = sc_r[scindex]
 d0 = sc_r[sc[0]-1]
 t = sc_t[scindex]
 t0 = sc_t[sc[0]-1]
 m = mass you're looking for 
 */

//Remember these are Arjun's cut functions and do not differentiate between in terms of the cut bounds
//Same cuts are used for different delta t's
//NOTE modified input to accept full banks and just input a single index 7-26-16

 //sc index
int sc_index( int sc)
{
 	int scidx = (int)sc-1;
 	return scidx;
}

//Proton Formulae from Arjun
double dt_p_low(double p){
	return DTL[0]+DTL[1]*p+DTL[2]*p*p+DTL[3]*p*p*p;
}

double dt_p_high(double p){
	return DTH[0]+DTH[1]*p+DTH[2]*p*p+DTH[3]*p*p*p;
}

bool delta_t_proton(double p0, double p, double d0, double d, double t0, double t) //Note: d and t need the sc_index 
{
	bool isproton = kFALSE;
	double dt = delta_t( p, p0, d, d0, t, t0, mp );
	if(dt>dt_p_low(p) && dt<dt_p_high(p) )
	{
		isproton = kTRUE;
	}
	return isproton;
}

bool delta_t_pion(double p0, double p, double d0, double d, double t0, double t)
{
	bool ispion = kFALSE;
	double dt = delta_t( p, p0, d, d0, t, t0, mpi);
	if(dt>dt_p_low(p) && dt<dt_p_high(p) ){
		ispion = kTRUE;
	}
	return ispion;
}


#endif /* DELTA_T_CUTS_H */