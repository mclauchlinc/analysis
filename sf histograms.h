#ifndef SF_HISTOGRAMS_H
#define SF_HISTOGRAMS_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"

TH2D* SF_hist[11][30];//Various cuts {pre,cut,anti,pid,bank,fid,cc},{W binning}

TCanvas* tsf1;
TCanvas* tsf2;
TCanvas* tsf3;
TCanvas* tsf4;
TCanvas* tsf5;
TCanvas* tsf6;
TCanvas* tsf7;
TCanvas* tsf8;
TCanvas* tsf9;
TCanvas* tsf10;
TCanvas* tsf11;

const double tsfw = 2400;
const double tsfh = 1200;


void MakeHist_SF(){
  //Create Pointer for Histograms
  /*Indexed: Cut_Status
    - Pre = no cut
    - Cut = EID Cut
    - Anti-Cut = !EID
    - All = All cuts
  */

  std::vector<long> space_dims(2);
  space_dims[0] = 11; //cuts
  space_dims[1] = 30; //W binning

  CartesianGenerator cart(space_dims);//CartesianGenerator.hh
  float bot, top;

  while(cart.GetNextCombination()){
  	//Establish W range
      if(cart[1] == 0 ){
        sprintf(hname,"sf_%s",norm_cut[cart[0]]);
      }
      else{
        top = Wbin_start + (cart[1]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
        sprintf(hname,"sf_%s_Wbin:%f-%f",norm_cut[cart[0]],bot,top);
      }
    SF_hist[cart[0]][cart[1]] = new TH2D( hname, hname, SFxres, SFxmin, SFxmax, SFyres, SFymin, SFymax); // constants.h
  }
}

void Fill_sf(int level, double Wval, double etot, double p){
  double sf_thing = sf(etot,p);
  // Cut: {0,1,2,3} -> {pre,cut,anti,all}
  float top,bot;
  for(int i = 1; i < 30 ; i++){
    top = Wbin_start + (i * Wbin_res);
    bot = top - Wbin_res;
    if(Wval > bot && Wval < top){
      SF_hist[level][i]->Fill(p,sf_thing);
    }
  }
	SF_hist[level][0]->Fill(p,sf_thing);;//Filling for all the W   
}

void Write_sf(TFile *file){
	TDirectory * sf_plots = file->mkdir("sf_plots");
	sf_plots->cd();
	  //Create Pointer for Histograms
  /*Indexed: Cut_Status
    - Pre = no cut
    - Cut = EID Cut
    - Anti-Cut = !EID
    - All = All cuts
  */

   //Create TCanvasas
  tsf1 = new TCanvas("c1","c1",tsfw,tsfh);
  tsf1->Divide(6,5);
  tsf2 = new TCanvas("c2","c2",tsfw,tsfh);
  tsf2->Divide(6,5);
  tsf3 = new TCanvas("c3","c3",tsfw,tsfh);
  tsf3->Divide(6,5);
  tsf4 = new TCanvas("c4","c4",tsfw,tsfh);
  tsf4->Divide(6,5);
  tsf5 = new TCanvas("c5","c5",tsfw,tsfh);
  tsf5->Divide(6,5);
  tsf6 = new TCanvas("c6","c6",tsfw,tsfh);
  tsf6->Divide(6,5);
  tsf7 = new TCanvas("c7","c7",tsfw,tsfh);
  tsf7->Divide(6,5);
  tsf8 = new TCanvas("c8","c8",tsfw,tsfh);
  tsf8->Divide(6,5);
  tsf9 = new TCanvas("c9","c9",tsfw,tsfh);
  tsf9->Divide(6,5);
  tsf10 = new TCanvas("c10","c10",tsfw,tsfh);
  tsf10->Divide(6,5);
  tsf11 = new TCanvas("c11","c11",tsfw,tsfh);
  tsf11->Divide(6,5);

  std::vector<long> space_dims(2);
  space_dims[0] = 11; //cuts
  space_dims[1] = 30; //W binning

  CartesianGenerator cart(space_dims);//CartesianGenerator.hh
  float bot, top;

  while(cart.GetNextCombination()){
    SF_hist[cart[0]][cart[1]]->SetXTitle("Momentum (GeV/c)"); // constants.h
    SF_hist[cart[0]][cart[1]]->SetYTitle("Sampling Fraction");
    SF_hist[cart[0]][cart[1]]->Write();

    switch(cart[0]){
      case 0:
      tsf1->cd(cart[1]+1);
      SF_hist[cart[0]][cart[1]]->Draw("colz");
      break;
      case 1:
      tsf2->cd(cart[1]+1);
      SF_hist[cart[0]][cart[1]]->Draw("colz");
      break;
      case 2:
      tsf3->cd(cart[1]+1);
      SF_hist[cart[0]][cart[1]]->Draw("colz");
      break;
      case 3:
      tsf4->cd(cart[1]+1);
      SF_hist[cart[0]][cart[1]]->Draw("colz");
      break;
      case 4:
      tsf5->cd(cart[1]+1);
      SF_hist[cart[0]][cart[1]]->Draw("colz");
      break;
      case 5:
      tsf6->cd(cart[1]+1);
      SF_hist[cart[0]][cart[1]]->Draw("colz");
      break;
      case 6:
      tsf7->cd(cart[1]+1);
      SF_hist[cart[0]][cart[1]]->Draw("colz");
      break;
      case 7:
      tsf8->cd(cart[1]+1);
      SF_hist[cart[0]][cart[1]]->Draw("colz");
      break;
      case 8:
      tsf9->cd(cart[1]+1);
      SF_hist[cart[0]][cart[1]]->Draw("colz");
      break;
      case 9:
      tsf10->cd(cart[1]+1);
      SF_hist[cart[0]][cart[1]]->Draw("colz");
      break;
      case 10:
      tsf11->cd(cart[1]+1);
      SF_hist[cart[0]][cart[1]]->Draw("colz");
      break;
    }
  }

  tsf1->SaveAs("SF_Pre.pdf");
  tsf2->SaveAs("SF_Cut.pdf");
  tsf3->SaveAs("SF_Anti.pdf");
  tsf4->SaveAs("SF_PID.pdf");
  tsf5->SaveAs("SF_Bank.pdf");
  tsf6->SaveAs("SF_Fid.pdf");
  tsf7->SaveAs("SF_CC.pdf");
  tsf8->SaveAs("SF_Anti-Fid.pdf");
  tsf9->SaveAs("SF_Anti-CC.pdf");
  tsf10->SaveAs("SF_CC+Fid.pdf");
  tsf11->SaveAs("SF_Anti-CC+Fid.pdf");
  tsf1->SaveAs("SF_Pre.root");
  tsf2->SaveAs("SF_Cut.root");
  tsf3->SaveAs("SF_Anti.root");
  tsf4->SaveAs("SF_PID.root");
  tsf5->SaveAs("SF_Bank.root");
  tsf6->SaveAs("SF_Fid.root");
  tsf7->SaveAs("SF_CC.root");
  tsf8->SaveAs("SF_Anti-Fid.root");
  tsf9->SaveAs("SF_Anti-CC.root");
  tsf10->SaveAs("SF_CC+Fid.root");
  tsf11->SaveAs("SF_Anti-CC+Fid.root");

}


#endif