#ifndef PHYSICS_H
#define PHYSICS_H

#include "constants.h"
#include "TMath.h"
#include <TLorentzVector.h>
#include "TVector3.h"
#include <cmath>
#include "headers.h"

double Qsquared(int set, Float_t p, Float_t cx, Float_t cy, Float_t cz)
{
	TVector3 k_mu_3(p*cx,p*cy,p*cz);
	TLorentzVector k_mu;
	switch (set){
		case 0: 
		k_mu = k_mu_e16;
		break;
		case 1:
		k_mu = k_mu_e1f;
		break;
	}
	TLorentzVector k_mu_prime;
	k_mu_prime.SetVectM(k_mu_3,me);
	return -(k_mu - k_mu_prime).Mag2();
}

//This will be the W for a proton target given that this is what I am dealing with in my analysis
double WP(int set, Float_t p, Float_t cx, Float_t cy, Float_t cz)
{
	TLorentzVector k_mu;
	switch (set){
		case 0: 
		k_mu = k_mu_e16;
		break;
		case 1:
		k_mu = k_mu_e1f;
		break;
	}
	TVector3 k_mu_3(p*cx,p*cy,p*cz);
	TLorentzVector k_mu_prime;
	k_mu_prime.SetVectM(k_mu_3,me);
	TLorentzVector q_mu;
	q_mu = (k_mu - k_mu_prime);
	return (p_mu + q_mu).Mag();
}


#endif /* PHYSICS_H */