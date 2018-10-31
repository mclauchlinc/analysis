#ifndef PHYSICS_H
#define PHYSICS_H

#include "constants.h"
#include "TMath.h"
#include <TLorentzVector.h>
#include "TVector3.h"
#include <cmath>
#include "headers.h"
#include "four_vector.h"


void See_4Vec(TLorentzVector p0){
	std::cout<<std::endl <<"px: " <<p0[0] <<" py: " <<p0[1] <<" pz: " <<p0[2] <<" E: " <<p0[3] ;
}

void See_3Vec(TVector3 p0){
	std::cout<<std::endl <<"px: " <<p0[0] <<" py: " <<p0[1] <<" pz: " <<p0[2];
}



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
	//std::cout<<std::endl<<"momentum: " <<p <<"  cx: " <<cx <<"  cy: " <<cy <<"  cz: " <<cz <<std::endl;
	switch (set){
		case 0: 
		k_mu = k_mu_e16;
		break;
		case 1:
		k_mu = k_mu_e1f;
		break;
		case 2:
		k_mu = k_mu_e16;
		break;
	}

	TVector3 k_mu_3(p*cx,p*cy,p*cz);
	TLorentzVector k_mu_prime;
	k_mu_prime.SetVectM(k_mu_3,me);

	
	TLorentzVector q_mu;
	//Write out
	//std::cout<< "deflected electron four-vector W: {"<<k_mu_prime[0] <<", " <<k_mu_prime[1] <<", " <<k_mu_prime[2] <<", " <<k_mu_prime[3] <<"}" <<std::endl;
	q_mu = (k_mu - k_mu_prime);

	
	//std::cout<< std::endl <<q_mu[0] <<", " <<q_mu[1] <<", " <<q_mu[2] <<", " <<q_mu[3] <<". mass: " <<q_mu.Mag() <<std::endl;
	

	/*if(co<1){
		std::cout<< "k 0:" << k_mu[0] <<std::endl;
	std::cout<< "k 1:" << k_mu[1] <<std::endl;
	std::cout<< "k 2:" << k_mu[2] <<std::endl;
	std::cout<< "k 3:" << k_mu[3] <<std::endl <<std::endl;
	std::cout<< "k' 0:" << k_mu_prime[0] <<std::endl;
	std::cout<< "k' 1:" << k_mu_prime[1] <<std::endl;
	std::cout<< "k' 2:" << k_mu_prime[2] <<std::endl;
	std::cout<< "k' 3:" << k_mu_prime[3] <<std::endl <<std::endl;
	std::cout<< "q 0:" << q_mu[0] <<std::endl;
	std::cout<< "q 1:" << q_mu[1] <<std::endl;
	std::cout<< "q 2:" << q_mu[2] <<std::endl;
	std::cout<< "q 3:" << q_mu[3] <<std::endl <<std::endl;
	std::cout<<std::endl <<"W: " <<(p_mu + q_mu).Mag();
	}*/
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




void Rotate_4Vecs(double thet, double phip, TLorentzVector &p0, TLorentzVector &p1, TLorentzVector &p2, TLorentzVector &p3){
	//std::cout<<"4 vector 1" <<"||px: " <<p0[0] <<" py: " <<p0[1] <<" pz: " <<p0[2] <<" E: " <<p0[3] <<std::endl;
	p0.RotateZ(-phip);
	p0.RotateX(-thet);
	p0.RotateZ(phip);
	//std::cout<<"Rotation" <<std::endl;
	//std::cout<<"4 vector 1" <<"||px: " <<p0[0] <<" py: " <<p0[1] <<" pz: " <<p0[2] <<" E: " <<p0[3] <<std::endl;
	p1.RotateZ(-phip);
	p1.RotateX(-thet);
	p1.RotateZ(phip);
	p2.RotateZ(-phip);
	p2.RotateX(-thet);
	p2.RotateZ(phip);
	p3.RotateZ(-phip);
	p3.RotateX(-thet);
	p3.RotateZ(phip);
	p_mu_event.RotateZ(-phip);
	p_mu_event.RotateX(-thet);
	p_mu_event.RotateZ(phip);
}

void Boost_4Vecs(double bet, TLorentzVector &p0, TLorentzVector &p1, TLorentzVector &p2, TLorentzVector &p3){
	//std::cout<<"4 vector 1" <<"||px: " <<p0[0] <<" py: " <<p0[1] <<" pz: " <<p0[2] <<" E: " <<p0[3] <<std::endl;
	p0.Boost(0.0,0.0,bet);
	//std::cout<<"Boost" <<std::endl;
	//std::cout<<"4 vector 1" <<"||px: " <<p0[0] <<" py: " <<p0[1] <<" pz: " <<p0[2] <<" E: " <<p0[3] <<std::endl;
	p1.Boost(0.0,0.0,bet);
	p2.Boost(0.0,0.0,bet);
	p3.Boost(0.0,0.0,bet);
	p_mu_event.Boost(0.0,0.0,bet);//Also boost the at rest proton so that we can do angle stuff with it
}

//Remember TLorentz Vectors {x,y,z,t}
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
	p_mu_event = p_mu;
	TLorentzVector q_mu = k_mu-p0;
	TLorentzVector bulga_mu; //combined photon/proton system
	bulga_mu = q_mu + p_mu;
	//std::cout<<std::endl<<"4 vector COM" <<"||px: " <<bulga_mu[0] <<" py: " <<bulga_mu[1] <<" pz: " <<bulga_mu[2] <<" E: " <<bulga_mu[3] <<std::endl;
	double phigp = TMath::ATan2(bulga_mu[1],bulga_mu[0]);
	//std::cout<<"phi com: " <<phigp <<std::endl;
	
	double pgp = sqrt(bulga_mu[0]*bulga_mu[0]+bulga_mu[1]*bulga_mu[1]+bulga_mu[2]*bulga_mu[2]);
	//Need to allign the vector with the correct orientation
	
	bulga_mu.RotateZ(-phigp);
	//std::cout<<"Rotate -Z" <<std::endl <<"4 vector COM" <<"||px: " <<bulga_mu[0] <<" py: " <<bulga_mu[1] <<" pz: " <<bulga_mu[2] <<" E: " <<bulga_mu[3] <<std::endl;
	double thgp = TMath::ATan2(bulga_mu[0],bulga_mu[2]);
	//std::cout<<"theta com: " <<thgp <<std::endl;
	bulga_mu.RotateY(-thgp);
	//std::cout<<"Rotate -Y" <<std::endl <<"4 vector COM" <<"||px: " <<bulga_mu[0] <<" py: " <<bulga_mu[1] <<" pz: " <<bulga_mu[2] <<" E: " <<bulga_mu[3] <<std::endl;
	bulga_mu.RotateZ(phigp);
	//std::cout<<"Rotate Z" <<std::endl <<"4 vector COM" <<"||px: " <<bulga_mu[0] <<" py: " <<bulga_mu[1] <<" pz: " <<bulga_mu[2] <<" E: " <<bulga_mu[3] <<std::endl;
	double b = bulga_mu.Beta();
	bulga_mu.Boost(0.0,0.0,-b);
	//std::cout<<std::endl<<"post boost"<<std::endl<<"4 vector COM" <<"||px: " <<bulga_mu[0] <<" py: " <<bulga_mu[1] <<" pz: " <<bulga_mu[2] <<" E: " <<bulga_mu[3] <<std::endl;
	Rotate_4Vecs(thgp, phigp, p0, p1, p2, p3);
	Boost_4Vecs(-b,p0,p1,p2,p3);
	/*
	Rotate_x(t,p0);
	Rotate_x(t,p1);
	Rotate_x(t,p2);
	Rotate_x(t,p3);
	Boost_z(b,p0);
	Boost_z(b,p1);
	Boost_z(b,p2);
	Boost_z(b,p3);*/
	//p0.Boost()
}

TVector3 Cross_Product(TLorentzVector p1, TLorentzVector p2){
	TVector3 product(p1[1]*p2[2]-p1[2]*p2[1],p1[0]*p2[2]-p1[2]*p2[0],p1[0]*p2[1]-p1[1]*p2[0]); 
	return product; 
}

double Dot_Product(TVector3 p1, TVector3 p2){
	return p1[0]*p2[0]+p1[1]*p2[1]+p1[2]*p2[2];
}

double Vec3_Mag(TVector3 p1){
	return sqrt(p1[0]*p1[0]+p1[1]*p1[1]+p1[2]*p1[2]);
}

double Cos_Vecs(TVector3 p1, TVector3 p2){
	double other1mag;
	double other2mag;
	double dotpro;
	dotpro = p1 * p2;
	other1mag = Vec3_Mag(p1);
	other2mag = Vec3_Mag(p2);
	return dotpro/(other2mag*other1mag);
}

double Sin_Vecs(TVector3 p1, TVector3 p2){
	double other1mag;
	double other2mag;
	double Cross_Mag;
	TVector3 product = p1.Cross(p2);
	double sign = (Dot_Product(p1,p2)/(Vec3_Mag(p1)*Vec3_Mag(p2)));
	Cross_Mag = Dot_Product(product,product)*sign;
	other1mag = Vec3_Mag(p1);
	other2mag = Vec3_Mag(p2);
	return Cross_Mag/(other1mag*other2mag);
}




//Angle between Hadron scattering plane and electron scattering plane
//4-Momentum should already be both boosted and rotated
//{p' ,p, pip, pim}
double alpha(int top, TLorentzVector p1, TLorentzVector p2, TLorentzVector p3, TLorentzVector p4){
	//pi -> {0,1,2,3} -> {e,p,pip,pim}
	//top -> {p/pip, p/pim, pip,pim}
	double other1mag;
	double other2mag;
	double dotpro;
	double alph; 
	double sin, cos; 
	TVector3 other1, other2;
	switch(top){
		case 0:
		other1 = Cross_Product(p1,p3);
		other2 = Cross_Product(p2,p4);
		break;
		case 1:
		other1 = Cross_Product(p3,p4);
		other2 = Cross_Product(p1,p2);
		break;
		case 2:
		other1 = Cross_Product(p1,p4);
		other2 = Cross_Product(p2,p3);
		break;
	}
	//See_4Vec(other1);
	//See_4Vec(other2);
	/*
	std::cout<<std::endl<<std::endl;
	See_3Vec(other1);
	See_3Vec(other2);
	dotpro = (other1[0]*other2[0]+other1[1]*other2[1]+other1[2]*other2[2]);
	std::cout<<std::endl <<"dot product = " <<dotpro;
	other1mag = sqrt(other1[0]*other1[0]+other1[1]*other1[1]+other1[2]*other1[2]);
	other2mag = sqrt(other2[0]*other2[0]+other2[1]*other2[1]+other2[2]*other2[2]);
	std::cout<<std::endl <<"mags: " <<other1mag <<" and " <<other2mag;
	std::cout<<std::endl <<"Cosine: " <<(dotpro)/(other1mag*other2mag);
	*/
	sin = Sin_Vecs(other1, other2);
	//std::cout<<std::endl <<"Sin alpha = " <<sin;
	cos = Cos_Vecs(other1, other2);
	//std::cout<<std::endl <<"Cos alpha = " <<cos;
	alph = TMath::ACos(cos)*180.0/TMath::Pi();
	//std::cout<<std::endl <<"alpha pre= " <<alph;
	if(sin < 0){
		alph = 180.0 - (alph - 180.0); 
	} 
	
	//std::cout<<std::endl <<"alpha post = " <<alph <<std::endl;
	//std::cout<<std::endl <<"aCos(-.5)" <<TMath::ACos(-0.5) <<std::endl;

	
	return alph; 

	//std::cout<<std::endl <<"dot product " <<(other1[0]*other2[0]+other1[1]*other2[1]+other1[2]*other2[2]);

	/*if(TMath::ACos((dotpro)/(other1mag*other2mag))*180.0/TMath::Pi() == 0){
		See_4Vec(other1);
		See_4Vec(other2);
		std::cout<<std::endl <<"dot product: " <<dotpro <<std::endl;
		std::cout<< "product of mags" <<other1mag*other2mag <<std::endl;
		std::cout<<"alpha?: " <<TMath::ACos((dotpro)/(other1mag*other2mag))*180.0/TMath::Pi() <<std::endl;
	}	*/
	//std::cout<<std::endl <<"product of mags " <<other1mag*other2mag;
	//std::cout<<std::endl <<"Just the Cosine " <<(dotpro)/(other1mag*other2mag);
	//std::cout<<" alpha = "<<TMath::ACos((dotpro)/(other1mag*other2mag))*180.0/TMath::Pi();
	//return TMath::ATan2(other1[1],other1[0]);
	//return TMath::ACos((dotpro)/(other1mag*other2mag))*180.0/TMath::Pi();
}

double theta_com(TLorentzVector p0){
	double r = sqrt(p0[0]*p0[0]+p0[1]*p0[1]);
	return TMath::ATan2(r,p0[2])*180.0/TMath::Pi(); //Fixed from Sin 8/7/18
}

double MM_2(TLorentzVector p1, TLorentzVector p2){
	return (p1+p2).Mag();
}

//Luminosity
/*
const lt_e16 = 5.0; //Target length in cm
const Dt_e16 = 0.073; //Density of target in g/cm^3
const NA = 6.022 * 10^23; //Avogadro's number
const qe = 1.602 * 10^-19; // fundamental Coulomb charge 
const Mt_e16 = 1.007; //Molar mass of target in g/mole
const Qt_e16 = 21.32*10^-3;
*/
//double Luminosity()


//virtual photon transverse polarization
double epsilon(int set, double Ep, double Q2 ){
	double Enp, omega;//E not prime
	switch(set){
		case 0: Enp = energy_e16;
		break;
		case 1: Enp = energy_e1f;
		break;
	}
	omega = Enp - Ep;
	return 1.0/(1+(2*(Q2+omega)/(4*Enp*Ep-Q2)));
}

//Virtual photon flux
double Gamma_nu(int set, double Ep, double Q2, double W){
	double Enp;//E not prime
	switch(set){
			case 0: Enp = energy_e16;
			break;
			case 1: Enp = energy_e1f;
			break;
		}
	return fine_structure*W*(W*W-mp*mp)/(4*TMath::Pi()*Enp*Enp*mp*mp*(1-epsilon(set,Ep,Q2))*Q2);
}

#endif /* PHYSICS_H */