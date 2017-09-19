#ifndef FOUR_VECTOR_H
#define FOUR_VECTOR_H

#include "headers.h"

TLorentzVector Make_4Vector(double p, double cx, double cy, double cz, double m){
	TVector3 k_mu_3(p*cx, p*cy, p*cz);
	TLorentzVector k_mu;
	k_mu.SetVectM(k_mu_3,m);
	return k_mu;
}

#endif