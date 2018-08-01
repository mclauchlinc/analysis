#ifndef FIDUCIAL_HISTOGRAMS_H
#define FIDUCIAL_HISTOGRAMS_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"
#include "directories.h"
#include "TCanvas.h"
#include "main_phd.h"//This has the Name_File function for some reason

//name the histograms being created
TH2D* fid_hist[6][4][5][30]; //Sector, species, cut, W binning

TCanvas * c_fid[5][6];//{0,1,2,3} -> {Species variance and cuts [4x5], 4 Species W var [6x5]}, Sectors
double fidw = 9600;
double fidh = 4800;

//cname is in variables.h


void MakeHist_fid(){
	//Create Pointer for Histograms
	//Indexed: Sector, Species, Cut_Status
	

  	std::vector<long> space_dims(4);
  	space_dims[0] = 6; //Six sectors
  	space_dims[1] = 4; //electron, proton, pi+, pi-
  	space_dims[2] = 5; //No cut, cut, anti-cut, all cuts, bank
    space_dims[3] = 30; //W binnings with 0 being no discrimination 

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

 for(int i = 1; i < 30 ; i++){
    top = Wbin_start + (i * Wbin_res);
    bot = top - Wbin_res;
    if(Wval > bot && Wval < top){
      fid_hist[sidx][type][level][i]->Fill(phi, theta);
    }
  }
	fid_hist[sidx][type][level][0]->Fill(phi, theta);//Filling for all the W 
}

//Name canvasas
void NS_Fid_C(int b1, int b2, TCanvas* can){
  //char c_f_n = "Fid_$species_Sec$sector.pdf";//Naming of the pdf files for the canvases
  sprintf(cname2,"Fid_%s_Sec%d.pdf",fid_can[b1],b2+1);
  /*replace(c_f_n,"$sector","");//Sector naming in there
  switch(b2){
    case 0:replace(c_f_n,"$sector","1");//Sector naming in there
    break;
    case 1:replace(c_f_n,"$sector","2");//Sector naming in there
    break;
    case 2:replace(c_f_n,"$sector","3");//Sector naming in there
    break;
    case 3:replace(c_f_n,"$sector","4");//Sector naming in there
    break;
    case 4:replace(c_f_n,"$sector","5");//Sector naming in there
    break;
    case 5:replace(c_f_n,"$sector","6");//Sector naming in there
    break;
  }
  if(b1==0){//All W
    replace(c_f_n,"$species","cuts");
  }else{
    switch(b1){
      case 0:replace(c_f_n,"$species","e");
      break;
      case 1:replace(c_f_n,"$species","p");
      break;
      case 2:replace(c_f_n,"$species","pip");
      break;
      case 3:replace(c_f_n,"$species","pim");
      break;
    }
  }*/
  can->SaveAs(cname2);
}

void Draw_fid(int cart0, int cart1, int cart2, int cart3, TH2D * cfid){
  //std::string c_fid_name = "cf$num$mun";//name inside of the TCanvas thing need to all be different
  //std::string c_f_n = "Fid_$species_Sec$sector.pdf"//Naming of the pdf files for the canvases

  //TCanvas naming and dividing
  

  //Naming of pdfs
  

  //Assingn to proper ones
  //All W assignment
  if(cart3==0){//This is all c_fid[0][s] and the first cell in W spreads
        //std::string c_f_n = "Fid_$species_Sec$sector.pdf"//Naming of the pdf files for the canvases
        c_fid[0][cart0]->cd(5*cart1+1+cart2);
        cfid->Draw("colz");
        /*switch(cart1){
          
        }*/

      //Total W bins in the W variance plots
      if(cart2==0){
        c_fid[cart1+1][cart0]->cd(1);
        cfid->Draw("colz");
      }
  }else{
    if(cart2==0){//pre cut
      //std::string c_f_n = "Fid_$species_Sec$sector.pdf"//Naming of the pdf files for the canvases
      c_fid[cart1+1][cart0]->cd(cart3+1);
      cfid->Draw("colz");
    }
  }
//W Variance
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
    space_dims[3] = 30; //W binnings with 0 being no discrimination 

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	float bot, top; 

    for(int e=0; e<5 ; e++){
      for(int s = 0; s<6; s++){
        sprintf(cname1,"c_fid%d%d",e,s);
        //replace(c_fid_name,"$num",e);//Number dude
        //replace(c_fid_name,"$mun",s+1);//Sector
        c_fid[e][s] = new TCanvas(cname1,cname2,fidw,fidh);
        if(e==0){
          c_fid[e][s]->Divide(5,4);
        }
        else{
          c_fid[e][s]->Divide(6,5);
        }
      }
    } 

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
    
      Draw_fid(cart[0],cart[1],cart[2],cart[3],fid_hist[cart[0]][cart[1]][cart[2]][cart[3]]);

      

    }

    
    for(int r = 0; r < 5; r++){
      for(int t = 0; t<6; t++){
        NS_Fid_C(r,t,c_fid[r][t]);
      }
    }
    
    

}



#endif