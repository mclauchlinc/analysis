#ifndef MM_HISTOGRAMS_H
#define MM_HISTOGRAMS_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"
#include "TCanvas.h"

TH1D* MM_hist[4][3][30];//Topology, Cut, W Binning
TH2D* MM_Cross_hist[6][30];//Topology crosses, W Binning 

//TCanvas
TCanvas* c_MM1;//Missing^2 {pre,cut,anti} (3x4)
TCanvas* c_MM2;//proton missing W range (4x3)
TCanvas* c_MM3;//pip missing W range (4x3)
TCanvas* c_MM4;//pim missing W range (4x3)
TCanvas* c_MM5;//zero missing W range (4x3)


const double MMw = 4800;
const double MMh = 2400;

void MakeHist_MM(){
	//Create Pointer for Histograms
	//Indexed: Sector, Species, Cut_Status
	

  	std::vector<long> space_dims(3);
  	space_dims[0] = 4; //proton, pip, pim, zero
  	space_dims[1] = 3; //No cut, cut, anti-cut
    space_dims[2] = 30; //W binnings with 0 being no discrimination 

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	float bot, top; 

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish W range
      if(cart[2] == 0 ){
        sprintf(hname, "%s_MM_%s",species[cart[0]+1],norm_cut[cart[1]]); 
      }
      else{
        top = Wbin_start + (cart[2]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
        sprintf(hname, "%s_MM_%s_WRange:%f-%f",species[cart[0]+1],norm_cut[cart[1]],bot,top); 
      }
     //hisname = species[cart[1]] + "_fid_sec" + (cart[0]+1) + cut[cart[2]]; //Naming convention: species_type_of_plot_sector#_cut_type
      //histitle = hisname; //For Fiducial I can make them both the same thing. 
      MM_hist[cart[0]][cart[1]][cart[2]] = new TH1D( hname, hname, MMxres, MMxmin, MMxmax);
    }
}

void Fill_MM(int part, int cut, double Wval, double MM){
	float bot, top;
	for(int i = 1; i < 30 ; i++){
    top = Wbin_start + (i * Wbin_res);
    bot = top - Wbin_res;
    if(Wval > bot && Wval < top){
      MM_hist[part][cut][i]->Fill(MM);
    }
  }
	MM_hist[part][cut][0]->Fill(MM);//Filling for all the W 
}

void Write_MM(TFile *file){
	TDirectory * MM_plots = file->mkdir("MM_plots");
	MM_plots->cd();
	TDirectory * p_MM_plots = MM_plots->mkdir("p_MM_plots");
	TDirectory * pip_MM_plots = MM_plots->mkdir("pip_MM_plots");
	TDirectory * pim_MM_plots = MM_plots->mkdir("pim_MM_plots");
	TDirectory * zero_MM_plots = MM_plots->mkdir("zero_MM_plots");

	c_MM1 = new TCanvas("cmm1","cmm1",MMw,MMh);
	c_MM1->Divide(3,4);
	c_MM2 = new TCanvas("cmm2","cmm2",MMw,MMh);
	c_MM2->Divide(6,5);
	c_MM3 = new TCanvas("cmm3","cmm3",MMw,MMh);
	c_MM3->Divide(6,5);
	c_MM4 = new TCanvas("cmm4","cmm4",MMw,MMh);
	c_MM4->Divide(6,5);
	c_MM5 = new TCanvas("cmm5","cmm5",MMw,MMh);
	c_MM5->Divide(6,5);

  	std::vector<long> space_dims(3);
  	space_dims[0] = 4; //proton, pip, pim, zero
  	space_dims[1] = 3; //No cut, cut, anti-cut
    space_dims[2] = 30; //W binnings with 0 being no discrimination 

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	float bot, top; 

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish which directory to write
      switch(cart[0]){
      	case 0: p_MM_plots->cd();
      	break;
      	case 1: pip_MM_plots->cd();
      	break;
      	case 2: pim_MM_plots->cd();
      	break;
      	case 3: zero_MM_plots->cd();
      	break;
      }
      if(cart[0]==3){
        MM_hist[cart[0]][cart[1]][cart[2]]->SetXTitle("MM^2 (GeV^2)");
        MM_hist[cart[0]][cart[1]][cart[2]]->SetYTitle("Counts");
      }else{
        MM_hist[cart[0]][cart[1]][cart[2]]->SetXTitle("MM (GeV)");
        MM_hist[cart[0]][cart[1]][cart[2]]->SetYTitle("Counts");
      }
      MM_hist[cart[0]][cart[1]][cart[2]]->Write();

      //TCanvas
      if(cart[2]==0){
      	c_MM1->cd(3*cart[0]+1+cart[1]);
      	MM_hist[cart[0]][cart[1]][cart[2]]->Draw();
      }

      if(cart[1]==0){
	      switch(cart[0]){
	      	case 0: c_MM2->cd(cart[2]+1);
	      		MM_hist[cart[0]][cart[1]][cart[2]]->Draw();
	      	break;
	      	case 1: c_MM3->cd(cart[2]+1);
	      		MM_hist[cart[0]][cart[1]][cart[2]]->Draw();
	      	break;
	      	case 2: c_MM4->cd(cart[2]+1);
	      		MM_hist[cart[0]][cart[1]][cart[2]]->Draw();
	      	break;
	      	case 3: c_MM5->cd(cart[2]+1);
	      		MM_hist[cart[0]][cart[1]][cart[2]]->Draw();
	      	break;
	      }
	  	}
    }
    c_MM1->SaveAs("MM Canvas all W.pdf");
    c_MM2->SaveAs("Proton MM W variance.pdf");
    c_MM3->SaveAs("Pip MM W Variance.pdf");
    c_MM4->SaveAs("Pim MM W Variance.pdf");
    c_MM5->SaveAs("Zero MM W variance.pdf");
}

void MakeHist_MM_Cross(){
	//Create Pointer for Histograms
	//Indexed: Sector, Species, Cut_Status
	

  	std::vector<long> space_dims(2);
  	space_dims[0] = 6; //{"p_pip", "p_pim", "p_zero", "pip_pim", "pip_zero", "pim_zero"}
    space_dims[1] = 30; //W binnings with 0 being no discrimination 

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	float bot, top; 

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish W range
      if(cart[1] == 0 ){
        sprintf(hname, "%s_MM_Cross",cross_top[cart[0]]); 
      }
      else{
        top = Wbin_start + (cart[1]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
        sprintf(hname, "%s_MM_Cross_WRange:%f-%f",cross_top[cart[0]],bot,top); 
      }
     //hisname = species[cart[1]] + "_fid_sec" + (cart[0]+1) + cut[cart[2]]; //Naming convention: species_type_of_plot_sector#_cut_type
      //histitle = hisname; //For Fiducial I can make them both the same thing. 
      MM_Cross_hist[cart[0]][cart[1]] = new TH2D( hname, hname, MMxres, MMxmin, MMxmax, MMxres, MMxmin, MMxmax);
  	}
}

void Fill_MM_Cross(int tol, double Wval, double MM_1, double MM_2){
	float bot, top;
	for(int i = 1; i < 30 ; i++){
    top = Wbin_start + (i * Wbin_res);
    bot = top - Wbin_res;
    //std::cout<<"Pre if-statment for i =" <<i <<std::endl;
    if(Wval > bot && Wval < top){
    	//std::cout<<"In if-statement for W = " <<Wval <<" and i = " <<i <<std::endl;
      MM_Cross_hist[tol][i]->Fill(MM_1,MM_2);
      //std::cout <<"We did it?" <<std::endl;
    }
  }
	MM_Cross_hist[tol][0]->Fill(MM_1,MM_2);//Filling for all the W 
}

void Write_MM_Cross(TFile *file){
	TDirectory * MM_Cross_plots = file->mkdir("MM_Cross_plots");
	MM_Cross_plots->cd();//{"p_pip", "p_pim", "p_zero", "pip_pim", "pip_zero", "pim_zero"}
	
	TDirectory * p_pip_MM_plots = MM_Cross_plots->mkdir("p_pip_MM_plots");
	TDirectory * p_pim_MM_plots = MM_Cross_plots->mkdir("p_pim_MM_plots");
	TDirectory * p_zero_MM_plots = MM_Cross_plots->mkdir("p_zero_MM_plots");
	TDirectory * pip_pim_MM_plots = MM_Cross_plots->mkdir("pip_pim_MM_plots");
	TDirectory * pip_zero_MM_plots = MM_Cross_plots->mkdir("pip_zero_MM_plots");
	TDirectory * pim_zero_MM_plots = MM_Cross_plots->mkdir("pim_zero_MM_plots");
	

  	std::vector<long> space_dims(2);
  	space_dims[0] = 6; //{"p_pip", "p_pim", "p_zero", "pip_pim", "pip_zero", "pim_zero"}
    space_dims[1] = 30; //W binnings with 0 being no discrimination 

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	//std::cout<<"Here?" <<std::endl;
  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish which directory to write

      switch(cart[0]){
      	case 0: p_pip_MM_plots->cd();
      	break;
      	case 1: p_pim_MM_plots->cd();
      	break;
      	case 2: p_zero_MM_plots->cd();
      	break;
      	case 3: pip_pim_MM_plots->cd();
      	break;
      	case 4: pip_zero_MM_plots->cd();
      	break;
      	case 5: pim_zero_MM_plots->cd();
      	break;
      }
  		//std::cout<<cart[0] <<" " <<cart[1] <<std::endl;
      MM_Cross_hist[cart[0]][cart[1]]->SetXTitle("MM (GeV)");
      MM_Cross_hist[cart[0]][cart[1]]->SetYTitle("MM (GeV");
      MM_Cross_hist[cart[0]][cart[1]]->Write();
    }
}


#endif