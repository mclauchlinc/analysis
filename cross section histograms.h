#ifndef CROSS_SECTION_HISTOGRAMS_H
#define CROSS_SECTION_HISTOGRAMS_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"

dxs_hist[5][8][11];//{topologies,projections,W binning}
xs_hist[5]; //Topologies

void MakeHist_DXC(){
	std::vector<long> space_dims(3);
  	space_dims[0] = 4; //Topologies
  	space_dims[1] = 8; //projections 
  	space_dims[2] = 11; //W bining

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
    sprintf(hname,"W_Q2_%s_%s",eid_cut[cart[0]],topologies[cart[1]]); //constants.h and otherwise writing the specific cut to the right plot
    WQ2_hist[cart[0]][cart[1]] = new TH2D( hname, hname, WQxres, WQxmin, WQxmax, WQyres, WQymin, WQymax); // constants.h
  }
}

double W_Binning_XC(double Wq){
	bool pass; 
	int binning = 10;
	int WmaxBins = Wbin_start + Wbin_res*binning;
	while(!pass){
		for(int o; o < binning; o++){
			if()
		}
	}
}

void FillHist_DXC(){

}


#endif