#ifndef W_Q2_HISTOGRAMS_H
#define W_Q2_HISTOGRAMS_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"

TH2D* WQ2_hist[9][6]; //electron cuts, topologies 
//TH2D* WQ2_hist_ES[5];//Topology

int W_binning(double W){
  int j = 0;
  double top, bot; 
  for(int i = 1; i < 11; i++){
    top = Wbin_start + i*Wbin_res;
    bot = top - Wbin_res; 
    if(W < top && W > bot){
      j = i; 
    }
  }
  return j; 
}


void MakeHist_WQ2(){
  //Create Pointer for Histograms
  //cut {0,1,2,3,4,5,6,7,8}->{"pre","eid1","eid2","eid3","eid4","sanity","efid","sf","bank"};
	//top {0,1,2,3,4,5} -> {none,p,pip,pim,all,combined}
	std::vector<long> space_dims(2);
  	space_dims[0] = 10; //Various Electron Cuts
  	space_dims[1] = 6; //Topologies 

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
  TDirectory * WQ2_plots_no = WQ2_plots->mkdir("WQ2_No_Top");
  TDirectory * WQ2_plots_p = WQ2_plots->mkdir("WQ2_p");
  TDirectory * WQ2_plots_pip = WQ2_plots->mkdir("WQ2_pip");
  TDirectory * WQ2_plots_pim = WQ2_plots->mkdir("WQ2_pim");
  TDirectory * WQ2_plots_all = WQ2_plots->mkdir("WQ2_all");
  TDirectory * WQ2_plots_combo = WQ2_plots->mkdir("WQ2_combo");
	/*Indexed: Cut_Status
    - Pre = no cut
    - Cut = EID Cut
    - Anti-Cut = !EID
    - All = All cuts
  */
	//top {0,1,2,3,4,5} -> {none,p,pip,pim,all,combined}
	std::vector<long> space_dims(2);
  	space_dims[0] = 10; //Various Electron Cuts
  	space_dims[1] = 6; //Topologies 

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
      switch(cart[1]){
        case 0:
        WQ2_plots_no->cd();
        break;
        case 1:
        WQ2_plots_p->cd();
        break;
        case 2:
        WQ2_plots_pip->cd();
        break;
        case 3:
        WQ2_plots_pim->cd();
        break;
        case 4:
        WQ2_plots_all->cd();
        break;
        case 5:
        WQ2_plots_combo->cd();
        break;
      }
    WQ2_hist[cart[0]][cart[1]] -> SetXTitle("W (GeV)");
    WQ2_hist[cart[0]][cart[1]] -> SetYTitle("Q2 (GeV^2)");
    WQ2_hist[cart[0]][cart[1]] -> Write();
  }
}

#endif