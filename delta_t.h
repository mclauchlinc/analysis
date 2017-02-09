#ifndef DELTA_T_H
#define DELTA_T_H



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
double vert_e(Float_t d, Float_t t)
{
	return (double)t - (double)d/c_special;
}

double vert_p(Float_t p, Float_t d, Float_t t, double m)
{
	return (double)t-((double)d/c_special)*sqrt(1.0 + m*m/((double)p*(double)p));
}

double delta_t( Float_t p, Float_t p0, Float_t d, Float_t d0, Float_t t, Float_t t0, double m )
{
	double vertex_e = vert_e(d0, t0);
	double vertex_p = vert_p(p, d, t, m);
	return vertex_e - vertex_p;
}

#endif /* DELTA_T_H */