#ifndef FIDUCIAL_H
#define FIDUCIAL_H

//#include "constants.h"
//#include "TMath.h"
//#include <stdio.h>

//Calculating Theta and Phi 
//Phi has sector 1 centered at phi = 0
double get_theta(Float_t cz)
{
	double degree = 180.0/TMath::Pi();
	double theta = TMath::ACos((double)cz)*degree; //Calculates theta in the lab frame using cz
	return theta;
}

double get_phi( Float_t cx, Float_t cy)
{
	double degree = 180.0/TMath::Pi();
	double phi0 = TMath::ATan2((double)cy,(double)cx)*degree; // Calculates phi in the lab frame using cx and cy
	return phi0;
}

//Figures out which sector you are in based on phi
int get_sector(Float_t cx, Float_t cy)
{
	int sector;
	double phi = get_phi(cx, cy);
	if(phi>=-30 && phi <=30)
	{
		sector = 1;
	}
	if(phi>=30 && phi<=90)
	{
		sector = 2;
	}
	if(phi>=90 && phi <=150)
	{
		sector = 3;
	}
	if(phi>=150 || phi<=-150)
	{
		sector = 4;
	}
	if(phi>=-150 && phi<=-90)
	{
		sector = 5;
	}
	if(phi>=-90 && phi<=-30)
	{
		sector = 6;
	}
	return sector;
}

//Phi centering 
double phi_center( Float_t cx, Float_t cy)
{
	double phi_corr;
	double phi0 = get_phi(cx, cy);
	int sector = get_sector(cx,cy);

	if(sector ==1)
	{
		phi_corr = phi0;
	}
	if(sector==2)
	{
		phi_corr = phi0-60;
	}
	if(sector==3)
	{
		phi_corr = phi0-120;
	}
	if(sector == 4)
	{
		if(phi0<=-150)
		{
			phi_corr = phi0+180;
		}
		if(phi0>=150)
		{
			phi_corr = phi0-180;
		}
	}
	if(sector==5)
	{
		phi_corr = phi0+120;
	}
	if(sector==6)
	{
		phi_corr = phi0+60;
	}

	//Not working, but elegant. Adjust for elegance later
	/*phi0 = phi0 +180;
	int mod6 = ((int)phi0+210)/60;
	phi_corr = phi0 - (double)mod6*60.0;
	*/
	return phi_corr;
}


//Fiducial cut for the electron
bool fid_e ( Float_t p, Float_t cx, Float_t cy, Float_t cz)
{
	bool in_fid = kFALSE;

	//degree Conversion
	double degree = 180.0/TMath::Pi();

	//Calculate angles and sector
	double theta = get_theta(cz);
	double phi_c = phi_center(cx, cy);
	int sector = get_sector(cx, cy);

	//Creating the cut function
	double theta_cut = c1e + c2e / ((double)p+p_shift_e);
	double expon = c3e * TMath::Power((double)p,factor_e);
	double del_phi = c4e * TMath::Power((TMath::Sin((theta-theta_cut)/degree)),expon);
	

	//Actual application of the cut
	if(TMath::Abs(phi_c)<=del_phi && theta>=theta_cut)
	{
		in_fid = kTRUE;
	}

	return in_fid;
}
//Fiducial cut for hadrons
//momentum is in there in case a dependence is added later
bool fid_h ( Float_t p, Float_t cx, Float_t cy, Float_t cz)
{
	bool in_fid = kFALSE;


	//degree Conversion
	double degree = 180.0/TMath::Pi();

	//Calculate angles and sector
	//Phi is centered for the sector
	double theta = get_theta(cz);
	double phi_c = phi_center(cx, cy);
	int sector = get_sector(cx, cy);

	int sec_indx = sector -1;

	/*
	//Calculating phi and theta
	double phi;
	double degree = 180.0/TMath::Pi(); //Converts from radians to degrees
	double theta = TMath::ACos((double)cz)*degree; //Calculates theta in the lab frame using cz
	double phi0 = TMath::ATan2((double)cy,(double)cx)*degree; // Calculates phi in the lab frame using cx and cy
	

	//Centering phi for each sector 
	phi = phi0 +180.0;
	int sector = ((int)phi+30)/60;
	phi = phi - (double)sector*60.0;
	*/

	//Creating the cut functions for each sector from Arjun's fiducuial cut
	double phi_min = -(a0mh[sec_indx])*(1.0-TMath::Exp(-a1mh[sec_indx]*(theta-a2mh[sec_indx])))+a3mh[sec_indx];
	double phi_max = a0xh[sec_indx]*(1.0-TMath::Exp(-a1xh[sec_indx]*(theta-a2xh[sec_indx])))+a3xh[sec_indx];

	//Not sure why electrons get a momentum dependence while hadrons don't

	//Actual application of the cut
	if(phi_c>=phi_min && phi_c<=phi_max)
	{
		in_fid = kTRUE;
	}

	return in_fid;
}

//Goal is to make individual fiducial cuts for protons and pions 

#endif /* FIDUCIAL_H */