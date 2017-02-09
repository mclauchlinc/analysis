#ifndef VERTEX_H
#define VERTEX_H


#include "constants.h"


/*
double vertex_corr( Float_t p, Float_t cx, Float_t cy, Float_t cz, Float_t vx, Float_t vy, Float_t vz)
{
	double px = (double)p*(double)cx;
	double py = (double)p*(double)cy;
	double pz = (double)p*(double)cz;
	
}
*/


bool vertex_cut(Float_t vz)
{
	bool in_target = kFALSE;
	if(vz>VX_ZMIN)
	{
		if(vz<VX_ZMAX)
		{
			in_target = kTRUE;
		}
	}
	return in_target;
}


#endif /* VERTEX_H */