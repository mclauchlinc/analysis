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

char * htitle; //The name on the graph itself (can have spaces)
char * hname; //The name shown in the TBrowser (should have no spaces)
TH2D* fid_hist[6][4][4]; 

std::string histitle; //It is easier to manipulate strings so I put what I want in first then convert to a char*
std::string hisname;

//Conversion from string to char *
char* Str2CharS( std::string str){
  char * write = new char[str.size()+1]; //Creates a char* with the proper dimensions for the string
  std::copy(str.begin(),str.end(),write); //Copies the string over into the char array that is the char*
  return write; 
}

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
		//sprintf(hname, "%s_fid_sec%d_%s",species[cart[1]],cart[0]+1,cut[cart[2]]);
    //	sprintf(htitle, "%s_fid_sec%d_%s",species[cart[1]],cart[0]+1,cut[cart[2]]);
    //	fid_hist[cart[0]][cart[1]][cart[2]] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
      hisname = species[cart[1]] + "_fid_sec" + (cart[0]+1) + cut[cart[2]]; //Naming convention: species_type_of_plot_sector#_cut_type
      histitle = hisname; //For Fiducial I can make them both the same thing. 
      htitle = Str2CharS(histitle); //TH2D takes char* into it as opposed to strings
      hname = Str2CharS(hisname); //TH2D takes char * into it as opposed to strings so one must convert
      fid_hist[cart[0]][cart[1]][cart[2]] = new TH2D( hname, htitle, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
      delete hname;
      delete htitle; 
    }
}

void Fill_fid(int type, int level, Float_t cx, Float_t cy, Float_t cz)
{
	double phi = phi_center(cx, cy);
	double theta = get_theta(cz);
	int sec = get_sector(cx, cy);
	//Level {0,1,2,3} -> {no cut, cut, anti-cut, all cuts}
  //Type {0,1,2,3} -> {e, p, pip, pim}
	fid_hist[sec-1][type][level]->Fill(phi, theta);
}


/*
void Fid_Write()
{
	//Sector
	for(int sec = 0; sec<6; sec++){
		//Species
		for(int spe = 0; spe < 4; spe++){
			//cut
			for(int c = 0; c < 4; c++){
				fid_hist[sec][spe][c]->SetYTitle("#theta");
    			fid_hist[sec][spe][c]->SetXTitle("#phi");
    			fid_hist[sec][spe][c]->Write();
			}
		}
	}
}
*/

//Delta t


#endif