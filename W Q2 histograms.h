#ifndef W_Q2_HISTOGRAMS_H
#define W_Q2_HISTOGRAMS_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"

TH2D* WQ2_hist[9][6]; //electron cuts, topologies 
//TH2D* WQ2_hist_ES[5];//Topology

void MakeHist_WQ2(){
  //Create Pointer for Histograms
  /*Indexed: Cut_Status
    - Pre = no cut
    - Cut = EID Cut
    - Anti-Cut = !EID
    - All = All cuts
  */
	//top {0,1,2,3,4,5} -> {none,p,pip,pim,all,combined}
	std::vector<long> space_dims(3);
  	space_dims[0] = 9; //Various Electron Cuts
  	space_dims[1] = 5; //Topologies 

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
    sprintf(hname,"W_Q2_%s_%s",eid_cut[cart[0]],topologies[cart[1]]); //constants.h and otherwise writing the specific cut to the right plot
    WQ2_hist[cart[0]][cart[1]] = new TH2D( hname, hname, WQxres, WQxmin, WQxmax, WQyres, WQymin, WQymax); // constants.h
  }
}

void Fill_WQ2(int set, int cut, int top, double p, double cx, double cy, double cz){
  double W, Q2;
  //Set refers to the data set, due to them having different beam energies: 1->e16 and 2->e1f
  W = WP(set, p, cx, cy, cz); // physics.h  
  Q2 = Qsquared(set , p, cx, cy, cz); // physics.h
  // Cut: {0,1,2,3} -> {pre,cut,anti,all}
  WQ2_hist[cut][top]->Fill(W,Q2);
}


void Write_WQ2(TFile *file){
	TDirectory * WQ2_plots = file->mkdir("WQ2_plots");
	WQ2_plots -> cd();
	/*Indexed: Cut_Status
    - Pre = no cut
    - Cut = EID Cut
    - Anti-Cut = !EID
    - All = All cuts
  */
	//top {0,1,2,3,4,5} -> {none,p,pip,pim,all,combined}
	std::vector<long> space_dims(3);
  	space_dims[0] = 9; //Various Electron Cuts
  	space_dims[1] = 5; //Topologies 

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
    WQ2_hist[cart[0]][cart[1]] -> SetXTitle("W (GeV)");
    WQ2_hist[cart[0]][cart[1]] -> SetYTitle("Q2 (GeV^2)");
    WQ2_hist[cart[0]][cart[1]] -> Write();
  }
}


/*
//Now let's move on to Event Selection things
void MakeHist_WQ2_ES(){
  //Create Pointer for Histograms

  int space_dims = 5;//The cuts in constants.h;
  for(int w = 0; (w < space_dims); w++){ 
    sprintf(hname,"W_Q2_ES_%s",topologies[w]); //constants.h and otherwise writing the specific cut to the right plot
    WQ2_hist_ES[w] = new TH2D( hname, hname, WQ2xres, WQxmin, WQxmax, WQ2yres, WQymin, WQymax); // constants.h
  }
}

void Fill_WQ2_ES(int top, double p, double cx, double cy, double cz){
  //top {0,1,2,3,4} -> {p,pip,pim,all,combined}
  double W, Q2;
  //Set refers to the data set, due to them having different beam energies: 0->e16 and 1->e1f
  W = WP(0, p, cx, cy, cz); // physics.h  
  Q2 = Qsquared(0, p, cx, cy, cz); // physics.h
  // Cut: {0,1,2,3} -> {pre,cut,anti,all}
  WQ2_hist_ES[top]->Fill(W,Q2);
}
*/

#endif