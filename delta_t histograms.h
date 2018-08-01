#ifndef DELTA_T_HISTOGRAMS_H
#define DELTA_T_HISTOGRAMS_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"
#include "W Q2 histograms.h"

TH2D* dt_hist[3][5][30]; //delta t, cuts, W binning
TH2D* dt_hist_MM[3][5][30][4]; //particle, cuts, W binning, MM hist cuts
TH2D* dt_hist_pe[5][30];//electron cuts, W binning

TCanvas * c_dt1;//all W delta t {pre, cut, anti, pid, bank} (5x3)
TCanvas * c_dt2;//Proton delta t W variance (4x3)
TCanvas * c_dt3;//Pip delta t W variance (4x3)
TCanvas * c_dt4;//Pim delta t W variance (4x3)
TCanvas * c_dt5;

const double dtw = 4800;
const double dth = 2400;

//Delta t
/*
species: {p, pip, pim}  3
cut: {pre, cut, anti, pid, bank}  5
*/

void MakeHist_dt(){
  std::vector<long> space_dims(3);
    space_dims[0] = 3; //species
    space_dims[1] = 5; //cut
    space_dims[2] = 30;//Wbinning

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
    space_dims[2] = 30;//Wbinning

    c_dt1 = new TCanvas("cdt1","cdt1",dtw,dth);
    c_dt1->Divide(5,3);
    c_dt2 = new TCanvas("cdt2","cdt2",dtw,dth);
    c_dt2->Divide(6,5);
    c_dt3 = new TCanvas("cdt3","cdt3",dtw,dth);
    c_dt3->Divide(6,5);
    c_dt4 = new TCanvas("cdt4","cdt4",dtw,dth);
    c_dt4->Divide(6,5);
    c_dt5 = new TCanvas("cdt5","cdt5",dtw,dth);
    c_dt5->Divide(6,5);

    CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    float top,bot;

    //in the loop
    while(cart.GetNextCombination()) {//CartesianGenerator.hh
    	//Establish W range
      /*
      if(cart[2] == 0 ){
        sprintf(hname, "%s_delta_t_%s",species[cart[0]+1],norm_cut[cart[1]]);
      }
      else{
        top = Wbin_start + (cart[2]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
        sprintf(hname, "%s_delta_t_%s_Wbin:%f-%f",species[cart[0]+1],norm_cut[cart[1]],bot,top);
      }*/
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

      //TCanvas
      if(cart[2]==0){
        c_dt1->cd(5*cart[0]+1+cart[1]);
        dt_hist[cart[0]][cart[1]][cart[2]]->Draw("colz");
      }

      if(cart[1]==0){
        switch(cart[0]){
          case 0: c_dt2->cd(cart[2]+1);
            dt_hist[cart[0]][cart[1]][cart[2]]->Draw("colz");
          break;
          case 1: c_dt3->cd(cart[2]+1);
            dt_hist[cart[0]][cart[1]][cart[2]]->Draw("colz");
          break;
          case 2: c_dt4->cd(cart[2]+1);
            dt_hist[cart[0]][cart[1]][cart[2]]->Draw("colz");
          break;
        }
      }
    }

    c_dt1->SaveAs("Delta T all W.pdf");
    c_dt2->SaveAs("Proton dt W variance.pdf");
    c_dt3->SaveAs("Pip dt W Variance.pdf");
    c_dt4->SaveAs("Pim dt W Variance.pdf");

}

void MakeHist_dt_MM(){
  std::vector<long> space_dims(4);
    space_dims[0] = 3; //species
    space_dims[1] = 5; //cut
    space_dims[2] = 30;//Wbinning
    space_dims[3] = 4; //MM cut

    CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    float top,bot;

    //in the loop
    while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish W range
      if(cart[2] == 0 ){
        sprintf(hname, "%s_delta_t_%s_MM:%s",species[cart[0]+1],norm_cut[cart[1]],species[cart[3]+1]);
      }
      else{
        top = Wbin_start + (cart[2]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
        sprintf(hname, "%s_delta_t_%s_Wbin:%f-%f_MM:%s",species[cart[0]+1],norm_cut[cart[1]],bot,top,species[cart[3]+1]);
      }
      dt_hist_MM[cart[0]][cart[1]][cart[2]][cart[3]] = new TH2D( hname, hname, DTxres, DTxmin, DTxmax, DTyres, DTymin, DTymax);
      //std::cout<< "You just made: " <<hname <<std::endl;
    }
}


//Fill_dt(0,0,p, p0, sc_r, sc_r0, sc_t, sc_t0);
void Fill_dt_MM(double MM, double Wval, int s, int cut, int m, int sc, double p, double p0, double d, double d0, double t, double t0){
  /*
  for species: {p,pip,pim} -> {0,1,2}
  cut: {pre, cut, anti, pid, bank} -> {0,1,2,3,4}
  m: {p,pip,pim,zer0} -> {0,1,2,3}
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
    for(int i = 1; i < 30 ; i++){
    top = Wbin_start + (i * Wbin_res);
    bot = top - Wbin_res;
    if(Wval > bot && Wval < top){
      if( m = 2){
        if(MM > pim_bot_MM[m] && MM < pim_top_MM[m]){
          dt_hist_MM[s][cut][i][m]->Fill(p, dt);
        }
      }
      else{
        std::cout<< "You haven't put anything for this yet" <<std::endl;
      }
      
    }
  }
  dt_hist_MM[s][cut][0][m]->Fill(p, dt);//Filling for all the W 
  }
}

void Write_dt_MM(TFile *file){
  TDirectory * delta_t_MM_plots = file->mkdir("delta_t_MM_plots");
  delta_t_MM_plots->cd();
  TDirectory * p_dt_MM_plots = delta_t_MM_plots->mkdir("p_dt_MM_plots");
  TDirectory * pip_dt_MM_plots = delta_t_MM_plots->mkdir("pip_dt_MM_plots");
  TDirectory * pim_dt_MM_plots = delta_t_MM_plots->mkdir("pim_dt_MM_plots");
    
 std::vector<long> space_dims(4);
    space_dims[0] = 3; //species
    space_dims[1] = 5; //cut
    space_dims[2] = 30;//Wbinning
    space_dims[3] = 4; //Missing particle 

    CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    float top,bot;

    //in the loop
    while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish W range
      /*
      if(cart[2] == 0 ){
        sprintf(hname, "%s_delta_t_%s_MM:%s",species[cart[0]+1],norm_cut[cart[1]],species[cart[3]+1]);
      }
      else{
        top = Wbin_start + (cart[2]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
        sprintf(hname, "%s_delta_t_%s_Wbin:%f-%f_MM:%s",species[cart[0]+1],norm_cut[cart[1]],bot,top,species[cart[3]+1]);
      }*/
      switch(cart[0]){
        case 0: p_dt_MM_plots->cd();
        break;
        case 1: pip_dt_MM_plots->cd();
        break;
        case 2: pim_dt_MM_plots->cd();
        break;
      }
      dt_hist_MM[cart[0]][cart[1]][cart[2]][cart[3]]->SetXTitle("Momentum (GeV/c)");
      dt_hist_MM[cart[0]][cart[1]][cart[2]][cart[3]]->SetYTitle("Delta t (ns)");
      dt_hist_MM[cart[0]][cart[1]][cart[2]][cart[3]]->Write();
      if(cart[2] == 0 ){
        sprintf(hname, "%s_delta_t_%s_MM:%s",species[cart[0]+1],norm_cut[cart[1]],species[cart[3]+1]);
      }
      else{
        top = Wbin_start + (cart[2]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
        sprintf(hname, "%s_delta_t_%s_Wbin:%f-%f_MM:%s",species[cart[0]+1],norm_cut[cart[1]],bot,top,species[cart[3]+1]);
      }
      //std::cout<<"You just wrote: " <<hname <<std::endl;
    }
}

void MakeHist_dt_pe(){
  std::vector<long> space_dims(2);
    space_dims[0] = 5; //cuts
    space_dims[1] = 30; //W binning

    CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    float top,bot;

    //in the loop
    while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish W range
      if(cart[1] == 0 ){
        sprintf(hname, "pim_delta_t_pe_%s",pe_cut[cart[0]]);
      }
      else{
        top = Wbin_start + (cart[1]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
        //std::cout<<"top: " << top <<"   bot: " <<bot <<std::endl;
        sprintf(hname, "pim_delta_t_pe_%s_Wbin:%f-%f",pe_cut[cart[0]],bot,top);
      }
      dt_hist_pe[cart[0]][cart[1]] = new TH2D( hname, hname, DTxres, DTxmin, DTxmax, DTyres, DTymin, DTymax);
    }
}


//Fill_dt(0,0,p, p0, sc_r, sc_r0, sc_t, sc_t0);
void Fill_dt_pe(double Wval, int cut, int sc, double p, double p0, double d, double d0, double t, double t0){
  /*
  cut: {none, dt, cc, ec, sf} -> {0,1,2,3,4}
  W binning!
  */
  float top,bot;
  if(sc != 0){
    double mass = 20;
    
    double dt = delta_t(p, p0, d, d0, t, t0, mpi );
    //W Binning
    for(int i = 1; i < 30 ; i++){
    top = Wbin_start + (i * Wbin_res);
    bot = top - Wbin_res;
    if(Wval > bot && Wval < top){
      dt_hist_pe[cut][i]->Fill(p, dt);
    }
  }
  dt_hist_pe[cut][0]->Fill(p, dt);//Filling for all the W 
  }
}

void Write_dt_pe(TFile *file){
  TDirectory * delta_t_pe_plots = file->mkdir("delta_t_pe_plots");
  delta_t_pe_plots->cd();
  TDirectory * pim_dt_total_plots = delta_t_pe_plots->mkdir("pim_dt_pe_plots");
  TDirectory * dt_pe_dte = delta_t_pe_plots->mkdir("dt_pe_dte");
  TDirectory * dt_pe_cc = delta_t_pe_plots->mkdir("dt_pe_cc");
  TDirectory * dt_pe_ec = delta_t_pe_plots->mkdir("dt_pe_ec");
  TDirectory * dt_pe_sf = delta_t_pe_plots->mkdir("dt_pe_sf");
    
 std::vector<long> space_dims(2);
    space_dims[0] = 5; //cuts 
    space_dims[1] = 30; //W Binning

    CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    float top,bot;

    //in the loop
    while(cart.GetNextCombination()) {//CartesianGenerator.hh
      switch(cart[0]){
        case 0:
          pim_dt_total_plots->cd();
          break;
        case 1:
          dt_pe_dte->cd();
          break;
        case 2:
          dt_pe_cc->cd();
          break;
        case 3:
          dt_pe_ec->cd();
          break;
        case 4:
          dt_pe_sf->cd();
          break;
      }
      dt_hist_pe[cart[0]][cart[1]]->SetXTitle("Momentum (GeV/c)");
      dt_hist_pe[cart[0]][cart[1]]->SetYTitle("Delta t (ns)");
      dt_hist_pe[cart[0]][cart[1]]->Write();
    }
}

#endif