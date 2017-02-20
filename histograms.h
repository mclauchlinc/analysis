#ifndef HISTOGRAMS_H
#define HISTOGRAMS_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"

/* Gary stuff
#include "CartesianGenerator.hh"
//Sector, species, cut_status
  TH2D* fid_hist[6][4][4];

  std::vector<long> space_dims(3);
  space_dims[0] = 6;
  space_dims[1] = 4;
  space_dims[2] = 4;

  CartesianGenerator cartgen(space_dims);
  //in the loop
  while(cartgen.GetNextCombination()) {
	sprintf(hname, "%s_fid_sec%d_%s",species[cart[1]],cart[0]+1,cut[cart[2]]);
    sprintf(htitle, "%s_fid_sec%d_%s",species[cart[1]],cart[0]+1,cut[cart[2]]);
    fid_hist[cart[0]][cart[1]][cart[2]] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
  }
*/

//Fiducial
/*int fid_num = 6;
int fid_types = 4;
int fid_tot = 24;
TH2D * e_fid_hist[24];
TH2D * p_fid_hist[24];
TH2D * pip_fid_hist[24];
TH2D * pim_fid_hist[24];
*/

char htitle[200];
char hname[100];
TH2D* fid_hist[6][4][4];

void MakeHist_fid(){
	//Create Pointer for Histograms
	//Indexed: Sector, Species, Cut_Status
	

  	std::vector<long> space_dims(3);
  	space_dims[0] = 6; //Six sectors
  	space_dims[1] = 4; //electron, proton, pi+, pi-
  	space_dims[2] = 4; //No cut, cut, anti-cut, all cuts

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	
  	//in the loop
  	while(cart.GetNextCombination()) {
		sprintf(hname, "%s_fid_sec%d_%s",species[cart[1]],cart[0]+1,cut[cart[2]]);
    	sprintf(htitle, "%s_fid_sec%d_%s",species[cart[1]],cart[0]+1,cut[cart[2]]);
    	fid_hist[cart[0]][cart[1]][cart[2]] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
    }
}

//Make all the fiducial plots needed 
//dimensions of plots are in the constants.h
/*
void makeHist_fid()
{
	for( int sec = 0; sec < fid_tot; sec++)
	{
		for( int sp = 0; sp <4 ; sp++)
		{
			for( int which = 0; which <4; which++)
			{
				if(sec <fid_num)
				{
					sprintf(hname, "%s_fid_sec%d_%s", species[sp],sec+1, cut[which]);
					sprintf(htitle, "%s_fid_sec%d_%s", species[sp], sec+1, cut[which]);
					e_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
				}
			}
			/*
			else if(sec>=fid_num && sec < 2*fid_num)
			{
				sprintf(hname, "%s_fid_sec%d_cut", species[sp], sec-5);
				sprintf(htitle, "%s_fid_sec%d_cut", species[sp], sec-5);
				e_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
			}
			else if(sec >= 2*fid_num && sec < 3*fid_num)
			{
				sprintf(hname, "e_fid_sec%d_anti", sec-11);
				sprintf(htitle, "e_fid_sec%d_anti", sec-11);
				e_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
			}
			else if(sec >= 3*fid_num && sec < 4*fid_num)
			{
			sprintf(hname, "e_fid_sec%d_all", sec-17);
			sprintf(htitle, "e_fid_sec%d_all", sec-17);
			e_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
			}
			*/
		/*}

		/*
		//Electron
		if(sec <fid_num)
		{
			sprintf(hname, "e_fid_sec%d_pre", sec+1);
			sprintf(htitle, "e_fid_sec%d_pre", sec+1);
			e_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		else if(sec>=fid_num && sec < 2*fid_num)
		{
			sprintf(hname, "e_fid_sec%d_cut", sec-5);
			sprintf(htitle, "e_fid_sec%d_cut", sec-5);
			e_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		else if(sec >= 2*fid_num && sec < 3*fid_num)
		{
			sprintf(hname, "e_fid_sec%d_anti", sec-11);
			sprintf(htitle, "e_fid_sec%d_anti", sec-11);
			e_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		else if(sec >= 3*fid_num && sec < 4*fid_num)
		{
			sprintf(hname, "e_fid_sec%d_all", sec-11);
			sprintf(htitle, "e_fid_sec%d_all", sec-11);
			e_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		//Proton
		if(sec <fid_num)
		{
			sprintf(hname, "p_fid_sec%d_pre", sec+1);
			sprintf(htitle, "p_fid_sec%d_pre", sec+1);
			p_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		else if(sec>=fid_num && sec < 2*fid_num)
		{
			sprintf(hname, "e_fid_sec%d_cut", sec-5);
			sprintf(htitle, "e_fid_sec%d_cut", sec-5);
			e_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		else if(sec >= 2*fid_num && sec < 3*fid_num)
		{
			sprintf(hname, "e_fid_sec%d_anti", sec-11);
			sprintf(htitle, "e_fid_sec%d_anti", sec-11);
			e_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		else if(sec >= 3*fid_num && sec < 4*fid_num)
		{
			sprintf(hname, "e_fid_sec%d_all", sec-11);
			sprintf(htitle, "e_fid_sec%d_all", sec-11);
			e_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		//Pi+
		if(sec <6)
		{
			sprintf(hname, "pip_fid_sec%d_pre", sec+1);
			sprintf(htitle, "pip_fid_sec%d_pre", sec+1);
			pip_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		else if(sec>=6 && sec < 12)
		{
			sprintf(hname, "pip_fid_sec%d_cut", sec-5);
			sprintf(htitle, "pip_fid_sec%d_cut", sec-5);
			pip_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		else if(sec >= 12 && sec < 18)
		{
			sprintf(hname, "pip_fid_sec%d_all", sec-11);
			sprintf(htitle, "pip_fid_sec%d_all", sec-11);
			pip_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		//Pi-
		if(sec <6)
		{
			sprintf(hname, "pim_fid_sec%d_pre", sec+1);
			sprintf(htitle, "pim_fid_sec%d_pre", sec+1);
			pip_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		else if(sec>=6 && sec < 12)
		{
			sprintf(hname, "pim_fid_sec%d_cut", sec-5);
			sprintf(htitle, "pim_fid_sec%d_cut", sec-5);
			pim_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		else if(sec >= 12 && sec < 18)
		{
			sprintf(hname, "pim_fid_sec%d_all", sec-11);
			sprintf(htitle, "pim_fid_sec%d_all", sec-11);
			pim_fid_hist[sec] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
		}
		*/
/*	}
}
*/

void Fill_fid(std::string type, int level, Float_t cx, Float_t cy, Float_t cz)
{
	double phi = phi_center(cx, cy);
	double theta = get_theta(cz);
	int sec = get_sector(cx, cy);
	//Level {0,1,2,3} -> {no cut, cut, anti-cut, all cuts}
	if(type == 'e')
	{
		fid_hist[sec][0][level]->Fill(phi, theta);
	}
}

/*
void Fid_Write()
{
	for(int sec = 0; sec < 18; sec++)
	{
		//Electron
		fid_hist[sec]->SetXTitle("#phi");
		fid_hist[sec]->SetYTitle("#theta");
		fid_hist[sec]->Write();
	}
}*/

//Delta t


#endif