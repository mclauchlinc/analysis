#ifndef PHYSICS_H
#define PHYSICS_H

#include "constants.h"
#include "TMath.h"
#include <TLorentzVector.h>
#include "TVector3.h"
#include <cmath>
#include "headers.h"
#include "four_vector.h"

int event_helicity(int event_class, int plate){//To give a consistent definition of the helicity by taking into account the status of the half wave plate
	int eh = 0; 
	if(event_class >= 1000){
            eh = 1; 
    }
    if(event_class <= -1000){
            eh = -1; 
    }
    if(event_class < 1000 && event_class > -1000){
        eh = 0; 
    }
    if(plate = 0){
    	plate = 1; //This is treating everything as if the half wave plate is in. Used for looking at non-wave plate dependencies 
    }
    return plate*eh; 
}


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

TVector3 Cross_Product(TLorentzVector p1, TLorentzVector p2){
	TVector3 product(p1[1]*p2[2]-p1[2]*p2[1],p1[2]*p2[0]-p1[0]*p2[2],p1[0]*p2[1]-p1[1]*p2[0]); 
	return product; 
}

TVector3 Cross_Product_v3( TVector3 p1, TVector3 p2){
	TVector3 product(p1[1]*p2[2]-p1[2]*p2[1],p1[2]*p2[0]-p1[0]*p2[2],p1[0]*p2[1]-p1[1]*p2[0]); 
	return product; 
}

double Dot_Product(TVector3 p1, TVector3 p2){
	return p1[0]*p2[0]+p1[1]*p2[1]+p1[2]*p2[2];
}

TVector3 V4_to_V3(TLorentzVector p1){
	TVector3 v1;
	for(int i = 0; i < 3; i++){
		v1[i]=p1[i];
	}
	return v1;
}

double Vec3_Mag(TVector3 p1){
	return sqrt(p1[0]*p1[0]+p1[1]*p1[1]+p1[2]*p1[2]);
}

double Vec3_Mag_fL(TLorentzVector p1){
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
	TVector3 product = Cross_Product_v3(p1,p2);
	other1mag = Vec3_Mag(p1);
	other2mag = Vec3_Mag(p2);
	Cross_Mag = Vec3_Mag(product);
	return Cross_Mag/(other1mag*other2mag);
}



void Rotate_4Vecs(int set, double thet, double phip, TLorentzVector &p0, TLorentzVector &p1, TLorentzVector &p2, TLorentzVector &p3, TLorentzVector &p4){
	TLorentzVector k_mu;
	switch (set){
		case 0: 
		k_mu = k_mu_e16;
		break;
		case 1:
		k_mu = k_mu_e1f;
		break;
	}
	//std::cout<<"4 vector 1" <<"||px: " <<p0[0] <<" py: " <<p0[1] <<" pz: " <<p0[2] <<" E: " <<p0[3] <<std::endl;
	p0.RotateZ(-phip);
	//std::cout<<"Z rotation" <<std::endl;
	//std::cout<<"4 vector 1" <<"||px: " <<p0[0] <<" py: " <<p0[1] <<" pz: " <<p0[2] <<" E: " <<p0[3] <<std::endl;
	//std::cout<<"Y rotation" <<std::endl;
	p0.RotateY(-thet);
	//std::cout<<"4 vector 1" <<"||px: " <<p0[0] <<" py: " <<p0[1] <<" pz: " <<p0[2] <<" E: " <<p0[3] <<std::endl;
	TVector3 nE = (1/(Vec3_Mag_fL(k_mu)*Vec3_Mag_fL(p0)))*Cross_Product(k_mu,p0);
	double phie = TMath::ATan2(nE[0],nE[1]);//Find phi angle of electron scattering plane
	//std::cout<<"Phi E: " <<phie*180/TMath::Pi() <<std::endl;
	p0.RotateZ(-phie);
	//std::cout<<"Rotation e plane" <<std::endl;
	//std::cout<<"4 vector 1" <<"||px: " <<p0[0] <<" py: " <<p0[1] <<" pz: " <<p0[2] <<" E: " <<p0[3] <<std::endl <<std::endl <<std::endl;
	
	p1.RotateZ(-phip);
	p1.RotateY(-thet);
	p1.RotateZ(-phie);
	p2.RotateZ(-phip);
	p2.RotateY(-thet);
	p2.RotateZ(-phie);
	p3.RotateZ(-phip);
	p3.RotateY(-thet);
	p3.RotateZ(-phie);
	p4.RotateZ(-phip);
	p4.RotateY(-thet);
	p4.RotateZ(-phie);
	
	/*std::cout<<"Rotation" <<std::endl;
	std::cout<<"4 vector 2" <<"||px: " <<p1[0] <<" py: " <<p1[1] <<" pz: " <<p1[2] <<" E: " <<p1[3] <<std::endl;
	std::cout<<"Rotation" <<std::endl;
	std::cout<<"4 vector 3" <<"||px: " <<p2[0] <<" py: " <<p2[1] <<" pz: " <<p2[2] <<" E: " <<p2[3] <<std::endl;
	std::cout<<"Rotation" <<std::endl;
	std::cout<<"4 vector 4" <<"||px: " <<p3[0] <<" py: " <<p3[1] <<" pz: " <<p3[2] <<" E: " <<p3[3] <<std::endl;*/
}

void Boost_4Vecs(double bet, TLorentzVector &p0, TLorentzVector &p1, TLorentzVector &p2, TLorentzVector &p3, TLorentzVector &p4){
	//std::cout<<"4 vector 1" <<"||px: " <<p0[0] <<" py: " <<p0[1] <<" pz: " <<p0[2] <<" E: " <<p0[3] <<std::endl;
	p0.Boost(0.0,0.0,bet);
	//std::cout<<"Boost" <<std::endl;
	//std::cout<<"4 vector 1" <<"||px: " <<p0[0] <<" py: " <<p0[1] <<" pz: " <<p0[2] <<" E: " <<p0[3] <<std::endl;
	p1.Boost(0.0,0.0,bet);
	p2.Boost(0.0,0.0,bet);
	p3.Boost(0.0,0.0,bet);
	p4.Boost(0.0,0.0,bet);//Also boost the at rest proton so that we can do angle stuff with it
	//std::cout<<"Boost" <<std::endl;
	//std::cout<<"4 vector 1" <<"||px: " <<p0[0] <<" py: " <<p0[1] <<" pz: " <<p0[2] <<" E: " <<p0[3] <<std::endl;
	//std::cout<<"Boost" <<std::endl;
	//std::cout<<"4 vector 2" <<"||px: " <<p1[0] <<" py: " <<p1[1] <<" pz: " <<p1[2] <<" E: " <<p1[3] <<std::endl;
	//std::cout<<"Boost" <<std::endl;
	//std::cout<<"4 vector 3" <<"||px: " <<p2[0] <<" py: " <<p2[1] <<" pz: " <<p2[2] <<" E: " <<p2[3] <<std::endl;
	//std::cout<<"Boost" <<std::endl;
	//std::cout<<"4 vector 4" <<"||px: " <<p3[0] <<" py: " <<p3[1] <<" pz: " <<p3[2] <<" E: " <<p3[3] <<std::endl;
}

//Remember TLorentz Vectors {x,y,z,t}
void COM_gp(int set, TLorentzVector &p0, TLorentzVector &p1, TLorentzVector &p2, TLorentzVector &p3, TLorentzVector &p4){
	//std::cout<< std::endl <<std::endl <<std::endl <<"Center of Mass stuff" <<std::endl;
	TLorentzVector k_mu;
	switch (set){
		case 0: 
		k_mu = k_mu_e16;
		break;
		case 1:
		k_mu = k_mu_e1f;
		break;
	}
	//p_mu_event = p_mu;
	TLorentzVector q_mu = k_mu-p0;
	TLorentzVector bulga_mu; //combined photon/proton system
	bulga_mu = q_mu + p_mu;
	//TVector3 nE = (1/(Vec3_Mag_fL(k_mu)*Vec3_Mag_fL(p0)))*Cross_Product(k_mu,p0);
	//std::cout<<std::endl<<"4 vector COM" <<"||px: " <<bulga_mu[0] <<" py: " <<bulga_mu[1] <<" pz: " <<bulga_mu[2] <<" E: " <<bulga_mu[3] <<std::endl;
	double phigp = TMath::ATan2(bulga_mu[1],bulga_mu[0]);
	//std::cout<<"phi com: " <<phigp <<std::endl;
	
	double pgp = sqrt(bulga_mu[0]*bulga_mu[0]+bulga_mu[1]*bulga_mu[1]+bulga_mu[2]*bulga_mu[2]);
	//Need to allign the vector with the correct orientation
	
	bulga_mu.RotateZ(-phigp);//Get all horizontal momentum on x axis by rotating around z axis
	//std::cout<<"Rotate -Z" <<std::endl <<"4 vector COM" <<"||px: " <<bulga_mu[0] <<" py: " <<bulga_mu[1] <<" pz: " <<bulga_mu[2] <<" E: " <<bulga_mu[3] <<std::endl;
	double thgp = TMath::ATan2(bulga_mu[0],bulga_mu[2]);
	//std::cout<<"theta com: " <<thgp*180/TMath::Pi() <<std::endl;
	bulga_mu.RotateY(-thgp);//Rotate towards z axis to get all momentum in z axis
	//std::cout<<"Rotate -Y" <<std::endl <<"4 vector COM" <<"||px: " <<bulga_mu[0] <<" py: " <<bulga_mu[1] <<" pz: " <<bulga_mu[2] <<" E: " <<bulga_mu[3] <<std::endl;
	
	//bulga_mu.RotateZ(-phie);//Rotate so that electron scattering plane is oriented along x-axis 
	//std::cout<<"Phi e: " <<phie <<std::endl;
	//std::cout<<"Rotate Z" <<std::endl <<"4 vector COM" <<"||px: " <<bulga_mu[0] <<" py: " <<bulga_mu[1] <<" pz: " <<bulga_mu[2] <<" E: " <<bulga_mu[3] <<std::endl;
	double b = bulga_mu.Beta();
	bulga_mu.Boost(0.0,0.0,-b);
	//std::cout<<std::endl<<"post boost"<<std::endl<<"4 vector COM" <<"||px: " <<bulga_mu[0] <<" py: " <<bulga_mu[1] <<" pz: " <<bulga_mu[2] <<" E: " <<bulga_mu[3] <<std::endl;
	Rotate_4Vecs(set,thgp, phigp, p0, p1, p2, p3,p4);
	Boost_4Vecs(-b,p0,p1,p2,p3,p4);
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






//Angle between Hadron scattering plane and electron scattering plane
//4-Momentum should already be both boosted and rotated
//{p' ,p, pip, pim}
double alpha(int top, TLorentzVector p1, TLorentzVector p2, TLorentzVector p3, TLorentzVector p4){
	//pi -> {0,1,2,3} -> {e,p,pip,pim}
	//top -> {p/pip, p/pim, pip,pim}
	//double other1mag;
	//double other2mag;
	double dotpro;
	double alph; 
	double sin, cos; 
	double theta_b, phi_b, phi_c; 
	TVector3 norm1, norm2, delta_v, gamma_v, beta_v, v1, v2, v3, v4, norm3;
	switch(top){
		//v1 = Target particle (the particle whose theta and phi angles are being measured) {pi-, p, pi+}
		//v2 = Paired particle for  scattering plane {p, pp, p}
		// v3= First particle in other scattering plane {pp, pi+, pp}
		// v4 = second particle in other scattering plane{pi+, pi-, pi-}
		case 0:
		v1 = V4_to_V3(p3);
		v2 = V4_to_V3(p4);
		v3 = V4_to_V3(p1);
		v4 = V4_to_V3(p2);
		break;
		case 1:
		v1 = V4_to_V3(p4);
		v2 = V4_to_V3(p1);
		v3 = V4_to_V3(p2);
		v4 = V4_to_V3(p3);
		break;
		case 2:
		v1 = V4_to_V3(p2);
		v2 = V4_to_V3(p1);
		v3 = V4_to_V3(p4);
		v4 = V4_to_V3(p3);
		break;
	}
	delta_v = -(1/Vec3_Mag(v1))*v1;
	beta_v = (1/(Vec3_Mag(Cross_Product_v3(Cross_Product_v3(v2,v4),delta_v))))*Cross_Product_v3(Cross_Product_v3(v2,v4),delta_v);
	gamma_v = -(1/(Vec3_Mag(Cross_Product_v3(Cross_Product_v3(v3,v1),delta_v))))*Cross_Product_v3(Cross_Product_v3(v3,v1),delta_v);
	///std::cout<<"Mag delta = " <<Vec3_Mag(delta_v) <<"mag beta = " <<Vec3_Mag(beta_v) <<"|| mag gamma = " <<Vec3_Mag(gamma_v) <<std::endl;
	//We want to then rotate beta_v such that it is alligned with an x-axis
	//double phigp = TMath::ATan2(bulga_mu[1],bulga_mu[0]);
	phi_b = TMath::ATan2(delta_v[1],delta_v[0]);//Angle from x axis to y-axis
	//std::cout<<std::endl <<"Pre delta_v: " <<delta_v[0] <<" " <<delta_v[1] <<" " <<delta_v[2] <<" " <<std::endl;
	delta_v.RotateZ(-phi_b);
	beta_v.RotateZ(-phi_b);
	gamma_v.RotateZ(-phi_b);
	//std::cout<<"Post delta_v: " <<delta_v[0] <<" " <<delta_v[1] <<" " <<delta_v[2] <<" " <<std::endl;
	//std::cout<<"Post beta_v: " <<beta_v[0] <<" " <<beta_v[1] <<" " <<beta_v[2] <<" " <<std::endl;
	//std::cout<<"Post gamma_v: " <<gamma_v[0] <<" " <<gamma_v[1] <<" " <<gamma_v[2] <<" " <<std::endl;
	theta_b = TMath::ATan2(delta_v[0],delta_v[2]);
	delta_v.RotateY(-theta_b+TMath::Pi());
	beta_v.RotateY(-theta_b+TMath::Pi());
	gamma_v.RotateY(-theta_b+TMath::Pi());
	//std::cout<<"Post delta_v: " <<delta_v[0] <<" " <<delta_v[1] <<" " <<delta_v[2] <<" " <<std::endl;
	//std::cout<<"Post beta_v: " <<beta_v[0] <<" " <<beta_v[1] <<" " <<beta_v[2] <<" " <<std::endl;
	//std::cout<<"Post gamma_v: " <<gamma_v[0] <<" " <<gamma_v[1] <<" " <<gamma_v[2] <<" " <<std::endl;
	phi_c = TMath::ATan2(beta_v[1],beta_v[0]);
	delta_v.RotateZ(-phi_c);
	beta_v.RotateZ(-phi_c);
	gamma_v.RotateZ(-phi_c);
	//std::cout<<"Post delta_v: " <<delta_v[0] <<" " <<delta_v[1] <<" " <<delta_v[2] <<" " <<std::endl;
	//std::cout<<"Post beta_v: " <<beta_v[0] <<" " <<beta_v[1] <<" " <<beta_v[2] <<" " <<std::endl;
	//std::cout<<"Post gamma_v: " <<gamma_v[0] <<" " <<gamma_v[1] <<" " <<gamma_v[2] <<" " <<std::endl;
	alph = TMath::ATan2(gamma_v[1],gamma_v[0])*180/TMath::Pi();

	/*
	std::cout<<std::endl;
	sin = Sin_Vecs(norm1, norm2);
	std::cout<<std::endl <<"Sin alpha = " <<sin;
	cos = Cos_Vecs(norm1, norm2);
	std::cout<<std::endl <<"Cos alpha = " <<cos;
	alph = TMath::ACos(cos)*180.0/TMath::Pi();
	std::cout<<" ||alpha is: " <<alph <<std::endl;
	//std::cout<<std::endl <<"alpha pre= " <<alph;*/
	if(alph < 0){
		alph = 360 + alph; 
	} 
	
	//std::cout<<"alpha post = " <<alph <<std::endl;
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

//Faraday Cup Counting
int QFaraday(int q_last, int q_next, int q_tot){
	if(q_next < q_last){
		q_tot = q_tot + q_next; 
	}
	else{
		q_tot = q_tot + (q_next - q_last);
	}
	return q_tot;
}

#endif /* PHYSICS_H */