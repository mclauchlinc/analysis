#ifndef MAKE_FILES_H
#define MAKE_FILES_H

#include "histograms.h"
#include "headers.h"

/*
void Fid_Write(){
  	std::vector<long> space_dims(3);
  	space_dims[0] = 6; //Six sectors
  	space_dims[1] = 4; //electron, proton, pi+, pi-
  	space_dims[2] = 4; //No cut, cut, anti-cut, all cuts

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	
  	//in the loop
  	while(cart.GetNextCombination()) {
    	fid_hist[cart[0]][cart[1]][cart[2]]->SetYTitle("#theta");
    	fid_hist[cart[0]][cart[1]][cart[2]]->SetXTitle("#phi");
    	fid_hist[cart[0]][cart[1]][cart[2]]->Write();
    }
}
*/

#endif