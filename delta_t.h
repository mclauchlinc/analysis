#ifndef DELTA_T_H
#define DELTA_T_H

#include "constants.h"

//Please put TMath Before this


//Takes in data and spits out a delta t
/*
 p = particle momentum p[k]
 p0 = p[0]
 d = sc_r[scindex]
 d0 = sc_r[sc[0]-1]
 t = sc_t[scindex]
 t0 = sc_t[sc[0]-1]
 m = mass you're looking for 
 */
double vert_e(double d, double t)
{
	return t -( d/c_special);
}

double vert_p(double p, double d, double t, double m)
{
	return t-((d/c_special)*sqrt(1.0 + m*m/(p*p)));
}

double delta_t( double p, double p0, double d, double d0, double t, double t0, double m )
{
	double vertex_e = vert_e(d0, t0);
	double vertex_p = vert_p(p, d, t, m);
	return vertex_e - vertex_p;
}

#endif /* DELTA_T_H */