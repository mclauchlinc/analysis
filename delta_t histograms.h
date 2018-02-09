#ifndef DELTA_T_HISTOGRAMS_H
#define DELTA_T_HISTOGRAMS_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"

TH2D* dt_hist[3][5][11]; //delta t, cuts, W binning


//Delta t
/*
species: {p, pip, pim}  3
cut: {pre, cut, anti, pid, bank}  5
*/

void MakeHist_dt(){
  std::vector<long> space_dims(3);
    space_dims[0] = 3; //species
    space_dims[1] = 5; //cut
    space_dims[2] = 11;//Wbinning

    CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    float top,bot;

    //in the loop
    while(cart.GetNextCombination()) {//CartesianGenerator.hh
    	//Establish W range
      if(cart[2] == 0 ){
        sprintf(hname, "%s_delta_t_%s",species[cart[0]+1],norm_cut[cart[1]]);
      }
      else{
        top = Wbin_start + (cart[2]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
        sprintf(hname, "%s_delta_t_%s_Wbin:%f-%f",species[cart[0]+1],norm_cut[cart[1]],bot,top);
      }
      dt_hist[cart[0]][cart[1]][cart[2]] = new TH2D( hname, hname, DTxres, DTxmin, DTxmax, DTyres, DTymin, DTymax);
    }
}


//Fill_dt(0,0,p, p0, sc_r, sc_r0, sc_t, sc_t0);
void Fill_dt(double Wval, int s, int cut, int sc, double p, double p0, double d, double d0, double t, double t0){
  /*
  for species: {p,pip,pim} -> {0,1,2}
  cut: {pre, cut, anti, pid, bank} -> {0,1,2,3,4}
  */
	float top,bot;
  if(sc != 0){
    double mass = 20;
    if(s == 0){
      mass = mp;
     // std::cout<< " Proton dt! " ;
    }
    if((s == 1) || (s == 2)){
      mass = mpi;
     // std::cout<< "Pion dt! " ;
    }
    if(s >2 || s < 0){
      std::cout << "you fucked up, friend" <<std::endl;
    }
    double dt = delta_t(p, p0, d, d0, t, t0, mass );
    //W Binning
    for(int i = 1; i < 11 ; i++){
    top = Wbin_start + (i * Wbin_res);
    bot = top - Wbin_res;
    if(Wval > bot && Wval < top){
      dt_hist[s][cut][i]->Fill(p, dt);
    }
  }
	dt_hist[s][cut][0]->Fill(p, dt);//Filling for all the W 
  }
}

void Write_dt(TFile *file){
	TDirectory * delta_t_plots = file->mkdir("delta_t_plots");
	delta_t_plots->cd();
	TDirectory * p_dt_plots = delta_t_plots->mkdir("p_dt_plots");
	TDirectory * pip_dt_plots = delta_t_plots->mkdir("pip_dt_plots");
	TDirectory * pim_dt_plots = delta_t_plots->mkdir("pim_dt_plots");
  	
 std::vector<long> space_dims(3);
    space_dims[0] = 3; //species
    space_dims[1] = 5; //cut
    space_dims[2] = 11;//Wbinning

    CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    float top,bot;

    //in the loop
    while(cart.GetNextCombination()) {//CartesianGenerator.hh
    	//Establish W range
      if(cart[2] == 0 ){
        sprintf(hname, "%s_delta_t_%s",species[cart[0]+1],norm_cut[cart[1]]);
      }
      else{
        top = Wbin_start + (cart[2]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
        sprintf(hname, "%s_delta_t_%s_Wbin:%f-%f",species[cart[0]+1],norm_cut[cart[1]],bot,top);
      }
      switch(cart[0]){
      	case 0: p_dt_plots->cd();
      	break;
      	case 1: pip_dt_plots->cd();
      	break;
      	case 2: pim_dt_plots->cd();
      	break;
      }
      dt_hist[cart[0]][cart[1]][cart[2]]->SetXTitle("Momentum (GeV/c)");
      dt_hist[cart[0]][cart[1]][cart[2]]->SetYTitle("Delta t (ns)");
      dt_hist[cart[0]][cart[1]][cart[2]]->Write();
    }
}

#endif