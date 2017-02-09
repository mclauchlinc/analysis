#ifndef ELECTRON_EC_H
#define ELECTRON_EC_H

#include "constants.h"
#include "fiducial.h"

//Minimum energy deposit in the EC check for electrons
bool min_ec(Float_t etot)
{
	bool pass_min_ec = kFALSE;
	if(etot >= ec_min_e16)
	{
		pass_min_ec = kTRUE;
	}
	return pass_min_ec;
}


//Electron Sampling Fraction cut using the EC
bool sf_e(Float_t p, Float_t etot, Float_t cx, Float_t cy)
{
	bool pass_sf = kFALSE;
	double sf = (double)etot / (double)p;
	int sector = get_sector(cx,cy);
	int sidx = sector -1;
	double low = sf_low_e16[sidx][0] + sf_low_e16[sidx][1]*p + sf_low_e16[sidx][2]*p*p + sf_low_e16[sidx][3]*p*p*p;
	double high = sf_high_e16[sidx][0] + sf_high_e16[sidx][1]*p + sf_high_e16[sidx][2]*p*p + sf_high_e16[sidx][3]*p*p*p;
	if(sf >= low && sf <= high)
	{
		pass_sf = kTRUE;
	}
	return pass_sf;
}


#endif /* ELECTRON_EC_H */