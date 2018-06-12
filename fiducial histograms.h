#ifndef FIDUCIAL_HISTOGRAMS_H
#define FIDUCIAL_HISTOGRAMS_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"
#include "directories.h"

//name the histograms being created
TH2D* fid_hist[6][4][5][11]; //Sector, species, cut, W binning


void MakeHist_fid(){
	//Create Pointer for Histograms
	//Indexed: Sector, Species, Cut_Status
	

  	std::vector<long> space_dims(4);
  	space_dims[0] = 6; //Six sectors
  	space_dims[1] = 4; //electron, proton, pi+, pi-
  	space_dims[2] = 5; //No cut, cut, anti-cut, all cuts, bank
    space_dims[3] = 11; //W binnings with 0 being no discrimination 

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	float bot, top; 

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish W range
      if(cart[3] == 0 ){
        sprintf(hname, "%s_fid_sec%d_%s",species[cart[1]],cart[0]+1,norm_cut[cart[2]]); 
      }
      else{
        top = Wbin_start + (cart[3]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
        sprintf(hname, "%s_fid_sec%d_%s_WRange:%f-%f",species[cart[1]],cart[0]+1,norm_cut[cart[2]],bot,top); 
      }
     //hisname = species[cart[1]] + "_fid_sec" + (cart[0]+1) + cut[cart[2]]; //Naming convention: species_type_of_plot_sector#_cut_type
      //histitle = hisname; //For Fiducial I can make them both the same thing. 
      fid_hist[cart[0]][cart[1]][cart[2]][cart[3]] = new TH2D( hname, hname, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
    }
}


void Fill_fid(int type, int level, double Wval, double cx, double cy, double cz)
{
  float bot, top; 
	double phi = phi_center(cx, cy); //fiducial.h
	double theta = get_theta(cz);  //fiducial.h
	int sec = get_sector(cx, cy);  //fiducial.h
  int sidx = sec-1;
  //std::cout<< std::endl <<"The Sector is: " <<sec <<std::endl;
	//Level {0,1,2,3} -> {no cut, cut, anti-cut, all cuts}
  //Type {0,1,2,3} -> {e, p, pip, pim}

 for(int i = 1; i < 11 ; i++){
    top = Wbin_start + (i * Wbin_res);
    bot = top - Wbin_res;
    if(Wval > bot && Wval < top){
      fid_hist[sidx][type][level][i]->Fill(phi, theta);
    }
  }
	fid_hist[sidx][type][level][0]->Fill(phi, theta);//Filling for all the W 
}


void Write_fid(TFile *file ){
	//TDirectory * fid_plot = output -> mkdir("fid_plot");
	TDirectory * fid_plots = file->mkdir("fid_plots");
	fid_plots->cd();
	TDirectory * e_fid_plots = fid_plots->mkdir("e_fid_plots");
	TDirectory * p_fid_plots = fid_plots->mkdir("p_fid_plots");
	TDirectory * pip_fid_plots = fid_plots->mkdir("pip_fid_plots");
	TDirectory * pim_fid_plots = fid_plots->mkdir("pim_fid_plots");
  	std::vector<long> space_dims(4);
  	space_dims[0] = 6; //Six sectors
  	space_dims[1] = 4; //electron, proton, pi+, pi-
  	space_dims[2] = 5; //No cut, cut, anti-cut, all cuts, bank
    space_dims[3] = 11; //W binnings with 0 being no discrimination 

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	float bot, top; 

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish W range
      /*
      if(cart[3] == 0 ){
        bot = 0.0; 
        top = 5.0;
      }
      else{
        top = Wbin_start + (cart[3]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
      }*/
      //Establish directory to place in
      switch(cart[1]){
      	case 0: e_fid_plots->cd();
      	break;
      	case 1: p_fid_plots->cd();
      	break;
      	case 2: pip_fid_plots->cd();
      	break;
      	case 3: pim_fid_plots->cd();
      	break;
      }
      fid_hist[cart[0]][cart[1]][cart[2]][cart[3]]->SetXTitle("Theta (deg)");
      fid_hist[cart[0]][cart[1]][cart[2]][cart[3]]->SetYTitle("Phi (deg)");
      fid_hist[cart[0]][cart[1]][cart[2]][cart[3]]->Write();
    }
}



#endif