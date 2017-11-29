#ifndef HIST_PROJECT_H
#define HIST_PROJECT_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"

char hpname[100];
TH1D* MM_hist_p[7][2][3];//Which delta{D++,D+,D0}, topology{each has two}, cut {PRE,par_pre,par_cut,par_anti,D_pre,D_cut,D_anti}
TH2D* WQ_hist_p[7][2][3];
/*
delta -> p_deltas
topologies -> p_top_*delta*
cut-> p_cuts

*/

//Makes all Missing mass plots
void MakeHist_MM_p(){
  std::vector<long> space_dims(3);
    space_dims[0] = 7; //cut
    space_dims[1] = 2; //topologies
    space_dims[2] = 3; //deltas 
    int shift;
  CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    
  //in the loop
  while(cart.GetNextCombination()) {//CartesianGenerator.hh
    shift = cart[2]*2;
    sprintf(hpname, "%s_MM_%s_%s",p_deltas[cart[2]],p_top[shift+cart[1]],p_cuts[cart[0]]);  
    MM_hist_p[cart[0]][cart[1]][cart[2]] = new TH1D( hpname, hpname, p_MMxres, p_MMxmin, p_MMxmax);
  }   
}

void Fill_MM_p(int species, int top, int cut, double mm){
  MM_hist_p[cut][top][species]->Fill(mm);
}

void MakeHist_WQ2_p(){
  //Create Pointer for Histograms
	std::vector<long> space_dims(3);
    space_dims[0] = 7; //cut
    space_dims[1] = 2; //topologies
    space_dims[2] = 3; //deltas
    int shift;
  CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    
  //in the loop
  while(cart.GetNextCombination()) {//CartesianGenerator.hh
    shift = cart[2]*2;
    sprintf(hpname, "W_Q2_p_%s_%s_%s",p_deltas[cart[2]],p_top[shift+cart[1]],p_cuts[cart[0]]);  
    WQ_hist_p[cart[0]][cart[1]][cart[2]] = new TH2D( hpname, hpname, WQxres, WQxmin, WQxmax, WQyres, WQymin, WQymax);
  }  
}

void Fill_WQ2_p(int species,int top, int cut, double W, double Q2){
  //top {0,1,2,3,4} -> {p,pip,pim,all,combined}
  //Set refers to the data set, due to them having different beam energies: 0->e16 and 1->e1f

  // Cut: {0,1,2,3} -> {pre,cut,anti,all}
  WQ_hist_p[cut][top][species]->Fill(W,Q2);
}


#endif