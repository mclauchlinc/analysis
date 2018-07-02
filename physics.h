#ifndef PHYSICS_H
#define PHYSICS_H

#include "constants.h"
#include "TMath.h"
#include <TLorentzVector.h>
#include "TVector3.h"
#include <cmath>
#include "headers.h"
#include "four_vector.h"





double Qsquared(int set, Float_t p, Float_t cx, Float_t cy, Float_t cz){
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
	//std::cout<< std::endl <<k_mu_prime[0] <<", " <<k_mu_prime[1] <<", " <<k_mu_prime[2] <<", " <<k_mu_prime[3] <<". mass: " <<k_mu_prime.Mag() <<std::endl;
	return -(k_mu - k_mu_prime).Mag2();
}

//This will be the W for a proton target given that this is what I am dealing with in my analysis
double WP(int set, Float_t p, Float_t cx, Float_t cy, Float_t cz){
	TLorentzVector k_mu;
	switch (set){
		case 0: 
		k_mu = k_mu_e16;
		break;
		case 1:
		k_mu = k_mu_e1f;
		break;
	}
	//std::cout<< "Position 0:" << k_mu[0] <<std::endl;
	//std::cout<< "Position 1:" << k_mu[1] <<std::endl;
	//std::cout<< "Position 2:" << k_mu[2] <<std::endl;
	//std::cout<< "Position 3:" << k_mu[3] <<std::endl <<std::endl;

	TVector3 k_mu_3(p*cx,p*cy,p*cz);
	TLorentzVector k_mu_prime;
	k_mu_prime.SetVectM(k_mu_3,me);
	TLorentzVector q_mu;
	//Write out
	//std::cout<< "deflected electron four-vector W: {"<<k_mu_prime[0] <<", " <<k_mu_prime[1] <<", " <<k_mu_prime[2] <<", " <<k_mu_prime[3] <<"}" <<std::endl;
	q_mu = (k_mu - k_mu_prime);
	//std::cout<< std::endl <<q_mu[0] <<", " <<q_mu[1] <<", " <<q_mu[2] <<", " <<q_mu[3] <<". mass: " <<q_mu.Mag() <<std::endl;
	return (p_mu + q_mu).Mag();
}

double Beta(double m, double p){
	return p/sqrt(m*m+p*p);
}

//Missing mass from three four vectors
//Used to find missing mass of missing particle
double MM_3(TLorentzVector k1_mu, TLorentzVector k2_mu, TLorentzVector k3_mu){
	return (k_mu_e16 + p_mu - k1_mu - k2_mu - k3_mu).Mag();
}

//Missing Mass from four four vectors
//Used to find missing mass of zero for all identified topology
double MM_4(TLorentzVector k1_mu, TLorentzVector k2_mu, TLorentzVector k3_mu, TLorentzVector k4_mu){
	return (k_mu_e16 + p_mu - k1_mu - k2_mu - k3_mu - k4_mu).Mag2();//Changed this to Mag2() 6/19/18 to try and actually get a zero peak
}

//Gives a Missing Mass value from momentum/mass data from three particles
//This is always used to identify a missing particle for my reaction
double MM_3_com(double p1, double p2, double p3, double cx1, double cx2, double cx3, double cy1, double cy2, double cy3, double cz1, double cz2, double cz3, double m1, double m2, double m3){
	TLorentzVector k1_mu;
	TLorentzVector k2_mu;
	TLorentzVector k3_mu;
	double MM = 0;
	k1_mu = Make_4Vector(p1, cx1, cy1, cz1, m1);
	k2_mu = Make_4Vector(p2, cx2, cy2, cz2, m2);
	k3_mu = Make_4Vector(p3, cx3, cy3, cz3, m3);
	MM = MM_3(k1_mu,k2_mu,k3_mu);
	return MM;
}

//Gives a missing mass value from momentum/mass data from four particles
//Always used for exclusive explicit identification of all particles
double MM_4_com(double p1, double p2, double p3, double p4, double cx1, double cx2, double cx3, double cx4, double cy1, double cy2, double cy3, double cy4, double cz1, double cz2, double cz3, double cz4, double m1, double m2, double m3, double m4){
	TLorentzVector k1_mu;
	TLorentzVector k2_mu;
	TLorentzVector k3_mu;
	TLorentzVector k4_mu;
	double MM; 
	k1_mu = Make_4Vector(p1, cx1, cy1, cz1, m1);
	k2_mu = Make_4Vector(p2, cx2, cy2, cz2, m2);
	k3_mu = Make_4Vector(p3, cx3, cy3, cz3, m3);
	k4_mu = Make_4Vector(p4, cx4, cy4, cz4, m4);
	MM = MM_4(k1_mu,k2_mu,k3_mu,k4_mu);
	return MM;
}

void Boost_z(double beta, TLorentzVector &p0){
	double m = sqrt(p0[3]*p0[3]-p0[0]*p0[0]-p0[1]*p0[1]-p0[2]*p0[2]);
	double p = sqrt(p0[0]*p0[0]+p0[1]*p0[1]+p0[2]*p0[2]);
	p0[2] = (p0[2]/sqrt(1-beta*beta))-p0[3]*beta/sqrt(1-beta*beta);
	p0[3] = (p0[3]/sqrt(1-beta*beta))+p0[2]*beta/sqrt(1-beta*beta);
}

void Rotate_x(double theta, TLorentzVector &k){
	k[0] = k[0]*TMath::Cos(theta)+k[1]*TMath::Sin(theta);
	k[1] = k[1]*TMath::Cos(theta)-k[0]*TMath::Sin(theta);
}

double angle_x(TLorentzVector p0){
 	return TMath::ATan2(p0[1],p0[0]); 
}

//All boosts also rotate the frame such that the scattered electron lies in the y=0 plane
void COM_ep(TLorentzVector &p0, TLorentzVector &p1, TLorentzVector &p2, TLorentzVector &p3){
	double p = sqrt(p0[0]*p0[0]+p0[1]*p0[1]+p0[2]*p0[2]);
	double b = (me/(me+mp))*(p/p0[3]);
	double t = angle_x(p0);
	Boost_z(b,p0);
	Boost_z(b,p1);
	Boost_z(b,p2);
	Boost_z(b,p3);
	Rotate_x(t,p0);
	Rotate_x(t,p1);
	Rotate_x(t,p2);
	Rotate_x(t,p3);
}

void COM_gp(int set, TLorentzVector &p0, TLorentzVector &p1, TLorentzVector &p2, TLorentzVector &p3){
	TLorentzVector k_mu;
	switch (set){
		case 0: 
		k_mu = k_mu_e16;
		break;
		case 1:
		k_mu = k_mu_e1f;
		break;
	}
	TLorentzVector q_mu = k_mu-p0;
	TLorentzVector bulga_mu; //combined photon/proton system
	bulga_mu = q_mu + p_mu;
	double p = sqrt(bulga_mu[0]*bulga_mu[0]+bulga_mu[1]*bulga_mu[1]+bulga_mu[2]*bulga_mu[2]);
	double b = (p/bulga_mu[3]);
	double t = angle_x(p0);
	Boost_z(b,p0);
	Boost_z(b,p1);
	Boost_z(b,p2);
	Boost_z(b,p3);
	Rotate_x(t,p0);
	Rotate_x(t,p1);
	Rotate_x(t,p2);
	Rotate_x(t,p3);
}



//Angle between Hadron scattering plane and electron scattering plane
//4-Momentum should already be both boosted and rotated
double alpha(int top, TLorentzVector p0, TLorentzVector p1, TLorentzVector p2, TLorentzVector p3){
	//pi -> {0,1,2,3} -> {e,p,pip,pim}
	//top -> {p/pip, p/pim, pip,pim}
	double a = 40;
	TLorentzVector other;
	switch(top){
		case 0:
		other = p1+p2;
		break;
		case 1:
		other = p1+p3;
		break;
		case 2:
		other = p2+p3;
		break;
	}
	return TMath::ATan2(other[1],other[0]);
}

double theta_com(TLorentzVector p0){
	return TMath::ATan2(sqrt(p0[0]*p0[0]+p0[1]*p0[1]),p0[2]); 
}

double MM_2(TLorentzVector p1, TLorentzVector p2){
	return (p1+p2).Mag();
}

#endif /* PHYSICS_H */