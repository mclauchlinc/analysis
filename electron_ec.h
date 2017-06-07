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

double sf(Float_t etot, Float_t p){
	return (double)etot/(double)p;
}

double sf_low(Float_t p, int sidx, int r =1){
	//If no run is given assume e16
	//1 = e16
	//2 = e1f
	/* haven't defined e1f parameters yet
	if(r = 2){
		return sf_low_e1f[sidx][0] + sf_low_e1f[sidx][1]*p + sf_low_e1f[sidx][2]*p*p + sf_low_e1f[sidx][3]*p*p*p;
	}
	else
	*/
	return sf_low_e16[sidx][0] + sf_low_e16[sidx][1]*p + sf_low_e16[sidx][2]*p*p + sf_low_e16[sidx][3]*p*p*p;
}

double sf_high(Float_t p, int sidx, int r=1){
	//If no run is given assume e16
	//1 = e16
	//2 = e1f
	/*haven't defined e1f parameters yet
	if(r = 2){
		return sf_high_e1f[sidx][0] + sf_high_e1f[sidx][1]*p + sf_high_e1f[sidx][2]*p*p + sf_high_e1f[sidx][3]*p*p*p;
	}
	else
		*/
	return sf_high_e16[sidx][0] + sf_high_e16[sidx][1]*p + sf_high_e16[sidx][2]*p*p + sf_high_e16[sidx][3]*p*p*p;
}
//Electron Sampling Fraction cut using the EC
bool sf_e(Float_t p, Float_t etot, Float_t cx, Float_t cy, int r = 1)
{
	bool pass_sf = kFALSE;
	double s_f = sf(etot,p);
	int sector = get_sector(cx,cy);
	int sidx = sector -1;
	double low = sf_low( p, sidx, r);
	double high = sf_high(p, sidx, r);
	if(s_f >= low && s_f <= high)
	{
		pass_sf = kTRUE;
	}
	return pass_sf;
}


#endif /* ELECTRON_EC_H */