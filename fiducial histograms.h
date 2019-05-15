#ifndef FIDUCIAL_HISTOGRAMS_H
#define FIDUCIAL_HISTOGRAMS_H

#include "variables.h"
#include "constants.h"
#include "fiducial.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"
#include "directories.h"
#include "TCanvas.h"
#include "main_phd.h"//This has the Name_File function for some reason

//name the histograms being created
TH2D* fid_hist[6][4][5][30]; //Sector, species, cut, W binning
TH2D* fid_hist_pdep[6][4][1][30][12]; //Sector, species, cut, W binning, p binning

TCanvas * c_fid[5][6];//{0,1,2,3} -> {Species variance and cuts [4x5], 4 Species W var [6x5]}, Sectors
double fidw = 9600;
double fidh = 4800;

TCanvas * c_fid_pdep[4][6][13];// Species, Sector, Momentum

//cname is in variables.h
double degree = 180.0*TMath::Pi();


double hfid_m(double *x, double *par){
  float xx = x[0];
  double f = par[0]-(TMath::Log(1.0-((-xx+par[1])/par[2]))/par[3]);
  //double f = 20.0 + par[0]*xx +par[1]+par[2]+par[3];
  //std::cout<<std::endl <<"par0: " <<par[0] <<" par1: " <<par[1] <<" par2: " <<par[2] <<" par3: " <<par[3];
  return f;
}

double hfid_x(double *x, double *par){
  float xx = x[0];
  double f = par[0]-((TMath::Log(1.0-((xx-par[1])/par[2])))/par[3]);
  //std::cout<<std::endl <<"par0: " <<par[0] <<" par1: " <<par[1] <<" par2: " <<par[2] <<" par3: " <<par[3];
  //std::cout<<std::endl <<"hfid_x: phi value_" <<xx <<" and function value_" <<f;
  return f;
}
//[0]-(TMath::Log(1.0-((x-[1])/[2]))/[3]) max
//[0]-(TMath::Log(1.0-((-x+[1])/[2]))/[3]) min

TF1 *h_fid_max = new TF1("h_fid_max",hfid_x,-27,25.5,4);
TF1 *h_fid_min = new TF1("h_fid_min",hfid_m,-25,25,4);


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


//Hahahaha
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

//Let's try something new 4/19/19
/*

void MakeHist_fid_pdep(){
  //Create Pointer for Histograms
  //Indexed: Sector, Species, Cut_Status
  

    std::vector<long> space_dims(4);
    space_dims[0] = 6; //Six sectors
    space_dims[1] = 4; //electron, proton, pi+, pi-
    space_dims[2] = 12; //Momentum
    space_dims[3] = 30; //W binnings with 0 being no discrimination 

    CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    float bot, top, pbot, ptop; 

    //in the loop
    while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish W range
      pbot = cart[2]*0.5;
      ptop = pbot + 0.5;
      if(cart[3] == 0 ){
        sprintf(hname, "%s_fid_sec%d_p:%f-%f",species[cart[1]],cart[0]+1,pbot,ptop); 
      }
      else{
        top = Wbin_start + (cart[3]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
        sprintf(hname, "%s_fid_sec%d_p:%f-%f_WRange:%f-%f",species[cart[1]],cart[0]+1,pbot,ptop,bot,top); 
      }
     //hisname = species[cart[1]] + "_fid_sec" + (cart[0]+1) + cut[cart[2]]; //Naming convention: species_type_of_plot_sector#_cut_type
      //histitle = hisname; //For Fiducial I can make them both the same thing. 
      fid_hist_pdep[cart[0]][cart[1]][cart[2]][cart[3]] = new TH2D( hname, hname, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
    }
}

int get_pidx(double p){
  double boop = p/0.5;
  int pidx; 
  for(int i=0; i<12; i++){
    if(boop < (i+1)*0.5 && boop>(i*0.5)){
      pidx = i; 
    }
  }
  return pidx; 
}

void Fill_fid_pdep(int type, int level, double Wval, double cx, double cy, double cz, double p)
{
  float bot, top; 
  double phi = phi_center(cx, cy); //fiducial.h
  double theta = get_theta(cz);  //fiducial.h
  int sec = get_sector(cx, cy);  //fiducial.h
  int sidx = sec-1;
  int pidx = get_pidx(p);
  //std::cout<< std::endl <<"The Sector is: " <<sec <<std::endl;
  //Level {0,1,2,3} -> {no cut, cut, anti-cut, all cuts}
  //Type {0,1,2,3} -> {e, p, pip, pim}

 for(int i = 1; i < 30 ; i++){
    top = Wbin_start + (i * Wbin_res);
    bot = top - Wbin_res;
    if(Wval > bot && Wval < top){
      fid_hist_pdep[sidx][pidx][level][i]->Fill(phi, theta);
    }
  }
  fid_hist_pdep[sidx][pidx][level][0]->Fill(phi, theta);//Filling for all the W 
}

//Name canvasas
void NS_Fid_pdep_C(int b1, int b2, TCanvas* can){
  //char c_f_n = "Fid_$species_Sec$sector.pdf";//Naming of the pdf files for the canvases
  sprintf(cname2,"Fid_p:_Sec%d.pdf",(b1*0.5),(b1+1)*0.5,b2+1);
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
  }*/ /*
  can->SaveAs(cname2); return these to back
}
/*
void Draw_fid_pdep(int cart0, int cart1, int cart2, int cart3, TH2D * cfid_pdep){
  //std::string c_fid_name = "cf$num$mun";//name inside of the TCanvas thing need to all be different
  //std::string c_f_n = "Fid_$species_Sec$sector.pdf"//Naming of the pdf files for the canvases

  //TCanvas naming and dividing
  

  //Naming of pdfs
  
  //****Will probably need to fix this***?// 4/19/19
  //Assingn to proper ones
  //All W assignment
  if(cart3==0){//This is all c_fid[0][s] and the first cell in W spreads
        //std::string c_f_n = "Fid_$species_Sec$sector.pdf"//Naming of the pdf files for the canvases
        c_fid_pdep[0][cart0]->cd(5*cart1+1+cart2);
        cfid_pdep->Draw("colz");
        /*switch(cart1){
          
        }*/ /*

      //Total W bins in the W variance plots
      if(cart2==0){
        c_fid_pdep[cart1+1][cart0]->cd(1);
        cfid_pdep->Draw("colz");
      }
  }else{
    if(cart2==0){//pre cut
      //std::string c_f_n = "Fid_$species_Sec$sector.pdf"//Naming of the pdf files for the canvases
      c_fid_pdep[cart1+1][cart0]->cd(cart3+1);
      cfid_pdep->Draw("colz");
    }
  }
//W Variance
}


//Hahahaha
void Write_fid_pdep(TFile *file ){
  TDirectory * fid_pdep_plots = file->mkdir("fid_pdep_plots");
  fid_pdep_plots->cd();
  TDirectory * e_fid_pdep_plots = fid_pdep_plots->mkdir("e_fid_plots");
  TDirectory * p_fid_pdep_plots = fid_pdep_plots->mkdir("p_fid_plots");
  TDirectory * pip_fid_pdep_plots = fid_pdep_plots->mkdir("pip_fid_plots");
  TDirectory * pim_fid_pdep_plots = fid_pdep_plots->mkdir("pim_fid_plots");

  

    std::vector<long> space_dims(4);
    space_dims[0] = 6; //Six sectors
    space_dims[1] = 4; //electron, proton, pi+, pi-
    space_dims[2] = 12; //Momentum binning
    space_dims[3] = 30; //W binnings with 0 being no discrimination 

    CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    float bot, top; 

    for(int e=0; e<12 ; e++){
      for(int s = 0; s<6; s++){
        sprintf(cname1,"c_fid%d%d",e,s);
        //replace(c_fid_name,"$num",e);//Number dude
        //replace(c_fid_name,"$mun",s+1);//Sector
        c_fid_pdep[e][s] = new TCanvas(cname1,cname2,fidw,fidh);
        if(e==0){
          c_fid_pdep[e][s]->Divide(5,4);
        }
        else{
          c_fid_pdep[e][s]->Divide(6,5);
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
      }*/ /*
      //Establish directory to place in
      switch(cart[1]){
        case 0: e_fid_pdep_plots->cd();
        break;
        case 1: p_fid_pdep_plots->cd();
        break;
        case 2: pip_fid_pdep_plots->cd();
        break;
        case 3: pim_fid_pdep_plots->cd();
        break;
      }
      fid_hist_pdep[cart[0]][cart[1]][cart[2]][cart[3]]->SetXTitle("Theta (deg)");
      fid_hist_pdep[cart[0]][cart[1]][cart[2]][cart[3]]->SetYTitle("Phi (deg)");
      fid_hist_pdep[cart[0]][cart[1]][cart[2]][cart[3]]->Write();
    
      Draw_fid_pdep(cart[0],cart[1],cart[2],cart[3],fid_hist_pdep[cart[0]][cart[1]][cart[2]][cart[3]]);
    }
    for(int r = 0; r < 12; r++){
      for(int t = 0; t<6; t++){
        NS_Fid_pdep_C(r,t,c_fid[r][t]);
      }
    }
    
    

}

*/
//End



//Look into Momentum Dependence for Fiducial Plots
//Momentum Slices: Up to 6 GeV with 0.5 GeV slices 
void MakeHist_fid_pdep(){
  //Create Pointer for Histograms
  //Indexed: Sector, Species, Cut_Status
  float ptop, pbot; 
  

    std::vector<long> space_dims(5);
    space_dims[0] = 6; //Six sectors
    space_dims[1] = 4; //electron, proton, pi+, pi-
    space_dims[2] = 1; //No cut, cut, anti-cut, all cuts, bank //Changed to 1 5/6/19
    space_dims[3] = 30; //W binnings with 0 being no discrimination 
    space_dims[4] = 12; //momentum binning

    CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    float bot, top; 

    //in the loop
    while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish W range
        ptop = 0.5*(cart[4]+1.0);
        pbot = 0.5*(cart[4]);
        if(cart[3] == 0 ){
          sprintf(hname, "%s_pfid_sec%d_p:%f-%f_all_W",species[cart[1]],cart[0]+1,pbot,ptop); 
        }
        else{
          top = Wbin_start + (cart[3]*Wbin_res);//constant.h
          bot = top - Wbin_res; //constants.h
          sprintf(hname, "%s_fid_sec%d_%s_prange%f-%f_WRange%f-%f",species[cart[1]],cart[0]+1,norm_cut[cart[2]],pbot,ptop,bot,top); 
        }
      fid_hist_pdep[cart[0]][cart[1]][cart[2]][cart[3]][cart[4]] = new TH2D( hname, hname, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
      //std::cout<<std::endl <<hname ;
    }

}

int get_pidx(double p){
  double boop = p/0.5;
  int pidx =-1; 
  for(int i=0; i<12; i++){
    if(boop < (i+1) && boop> i){
      pidx = i; 
    }
  }
  if(pidx == -1){
    pidx = 11; 
  }
  //std::cout<<std::endl <<"p: " <<p <<" || p/0.5: " <<boop <<" || pidx = " <<pidx <<std::endl; 
  return pidx; 
}

void Fill_fid_pdep(int type, int level, double Wval, double cx, double cy, double cz, double p)
{
  float bot, top; 
  double phi = phi_center(cx, cy); //fiducial.h
  double theta = get_theta(cz);  //fiducial.h
  int sec = get_sector(cx, cy);  //fiducial.h
  int sidx = sec-1;
  int pidx; 
  //std::cout<< std::endl <<"The Sector is: " <<sec <<std::endl;
  //Level {0,1,2,3} -> {no cut, cut, anti-cut, all cuts}
  //Type {0,1,2,3} -> {e, p, pip, pim}
  pidx = get_pidx(p);

 for(int i = 1; i < 30 ; i++){
    top = Wbin_start + (i * Wbin_res);
    bot = top - Wbin_res;
    if(Wval > bot && Wval < top){
      fid_hist_pdep[sidx][type][level][i][pidx]->Fill(phi, theta);
    }
  }
  fid_hist_pdep[sidx][type][level][0][pidx]->Fill(phi, theta);//Filling for all the W 
}

void Draw_fid_pdep(int cart0, int cart1, int cart2, int cart3, int cart4, TH2D * cfid_pdep){
  //std::string c_fid_name = "cf$num$mun";//name inside of the TCanvas thing need to all be different
  //std::string c_f_n = "Fid_$species_Sec$sector.pdf"//Naming of the pdf files for the canvases

  //TCanvas naming and dividing
  //cart0-> Sector binning 6
  //cart1-> Species binning 4
  //cart2-> Cut binning 5
  //cart3-> W binning 30
  //cart4-> Momentum binning 12
  //Canvas binning [5][6][12] sized (6x5) {species, sector, momentum}
  //    [species][sector][momentum]
  //Naming of pdfs
  

  //Assingn to proper ones
  //All W assignment
  if(cart3==0){//This is not looking at W Dependence
      c_fid_pdep[cart1][cart0][cart4+1]->cd(1); //For the first plot in W dependence
      cfid_pdep->Draw("colz");
      if(cart1!=0){
        //switch(cart0){
          //case 0: 
           //h_fid_min->SetParameters(-1.0);
            //h_fid_max->SetParameters(1.0);
            //std::cout<<std::endl <<"We are in sector: " <<cart0+1 <<" With min parameters: " <<a0mh[cart0] <<" " <<a1mh[cart0] <<" " <<a2mh[cart0] <<" " <<a3mh[cart0];
            h_fid_min->SetParameters(a2mh[cart0],a3mh[cart0],a0mh[cart0],a1mh[cart0]);
            h_fid_min->Draw("same");
            h_fid_max->SetParameters(a2xh[cart0],a3xh[cart0],a0xh[cart0],a1xh[cart0]);
            h_fid_max->Draw("same");
          /*break;
          case 1:
            h_fid_min_s2->Draw("same");
            h_fid_max_s2->Draw("same");
          break;
          case 2:
            h_fid_min_s3->Draw("same");
            h_fid_max_s3->Draw("same");
          break;
          case 3:
            h_fid_min_s4->Draw("same");
            h_fid_max_s4->Draw("same");
          break;
          case 4:
            h_fid_min_s5->Draw("same");
            h_fid_max_s5->Draw("same");
          break;
          case 5:
            h_fid_min_s6->Draw("same");
            h_fid_max_s6->Draw("same");
          break;*/

        //}
    }

      c_fid_pdep[cart1][cart0][0]->cd(cart4+1); //Particle and sector p dependence
      cfid_pdep->Draw("colz");
      if(cart1!=0){
        //switch(cart0){
          //case 0: 
          //h_fid_min->SetParameters(-1.0);
           // h_fid_max->SetParameters(1.0);
            h_fid_min->SetParameters(a2mh[cart0],a3mh[cart0],a0mh[cart0],a1mh[cart0]);
            h_fid_min->Draw("same");
            h_fid_max->SetParameters(a2xh[cart0],a3xh[cart0],a0xh[cart0],a1xh[cart0]);
            h_fid_max->Draw("same");
          /*break;
          case 1:
            h_fid_min_s2->Draw("same");
            h_fid_max_s2->Draw("same");
          break;
          case 2:
            h_fid_min_s3->Draw("same");
            h_fid_max_s3->Draw("same");
          break;
          case 3:
            h_fid_min_s4->Draw("same");
            h_fid_max_s4->Draw("same");
          break;
          case 4:
            h_fid_min_s5->Draw("same");
            h_fid_max_s5->Draw("same");
          break;
          case 5:
            h_fid_min_s6->Draw("same");
            h_fid_max_s6->Draw("same");
          break;*/

        //}
      }
      
      

  }//Total W bins in the W variance plots
  else{
    c_fid_pdep[cart1][cart0][cart4+1]->cd(cart3+1);
    cfid_pdep->Draw("colz");
    if(cart1!=0){
        //switch(cart0){
          //case 0: 
          //h_fid_min->SetParameters(-1.0);
           // h_fid_max->SetParameters(1.0);
            h_fid_min->SetParameters(a2mh[cart0],a3mh[cart0],a0mh[cart0],a1mh[cart0]);
            h_fid_min->Draw("same");
            h_fid_max->SetParameters(a2xh[cart0],a3xh[cart0],a0xh[cart0],a1xh[cart0]);
            h_fid_max->Draw("same");
          /*break;
          case 1:
            h_fid_min_s2->Draw("same");
            h_fid_max_s2->Draw("same");
          break;
          case 2:
            h_fid_min_s3->Draw("same");
            h_fid_max_s3->Draw("same");
          break;
          case 3:
            h_fid_min_s4->Draw("same");
            h_fid_max_s4->Draw("same");
          break;
          case 4:
            h_fid_min_s5->Draw("same");
            h_fid_max_s5->Draw("same");
          break;
          case 5:
            h_fid_min_s6->Draw("same");
            h_fid_max_s6->Draw("same");
          break;*/

        //}
    }
  }  
}



void NS_Fid_pdep_C(int b1, int b2, int b3, TCanvas* can){
  //char c_f_n = "Fid_$species_Sec$sector.pdf";//Naming of the pdf files for the canvases
  if(b3==0){
    sprintf(cname2,"pFid_%s_Sec%d.pdf",fid_can[b1+1],b2+1);
  }
  else{
    sprintf(cname2,"pFid_%s_Sec%d_p%d.pdf",fid_can[b1+1],b2+1,b3);
  }
  can->SaveAs(cname2);

}

void Write_fid_pdep(TFile *file ){
  //TDirectory * fid_plot = output -> mkdir("fid_plot");
  TDirectory * fid_pdep_plots = file->mkdir("fid_pdep_plots");
  fid_pdep_plots->cd();
  TDirectory * e_fid_pdep_plots = fid_pdep_plots->mkdir("e_fid_pdep_plots");
  TDirectory * p_fid_pdep_plots = fid_pdep_plots->mkdir("p_fid_pdep_plots");
  TDirectory * pip_fid_pdep_plots = fid_pdep_plots->mkdir("pip_fid_pdep_plots");
  TDirectory * pim_fid_pdep_plots = fid_pdep_plots->mkdir("pim_fid_pdep_plots");


    std::vector<long> space_dims(5);
    space_dims[0] = 6; //Six sectors
    space_dims[1] = 4; //electron, proton, pi+, pi-
    space_dims[2] = 1; //No cut, cut, anti-cut, all cuts, bank //changed to 1 5/6/19
    space_dims[3] = 30; //W binnings with 0 being no discrimination 
    space_dims[4] = 12; //It's 13 here

    CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    float bot, top; 

    for(int e=0; e<4 ; e++){//particle Loop
      for(int s = 0; s<6; s++){//Sector Loop
        for(int o = 0; o<13; o++){//Momentum Loop
          sprintf(cname1,"c_fid_pdep%d%d%d",e,s,o);
          //replace(c_fid_name,"$num",e);//Number dude
          //replace(c_fid_name,"$mun",s+1);//Sector
          c_fid_pdep[e][s][o] = new TCanvas(cname1,cname2,fidw,fidh);
          if(o==0){
            c_fid_pdep[e][s][o]->Divide(4,3);
          }
          else{
            c_fid_pdep[e][s][o]->Divide(6,5);
          }
        }
      }
    } 

    //in the loop
    while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish directory to place in
      switch(cart[1]){
        case 0: e_fid_pdep_plots->cd();
        break;
        case 1: p_fid_pdep_plots->cd();
        break;
        case 2: pip_fid_pdep_plots->cd();
        break;
        case 3: pim_fid_pdep_plots->cd();
        break;
      }
      fid_hist_pdep[cart[0]][cart[1]][cart[2]][cart[3]][cart[4]]->SetXTitle("Phi (deg)");
      fid_hist_pdep[cart[0]][cart[1]][cart[2]][cart[3]][cart[4]]->SetYTitle("Theta (deg)");
      //std::cout<<hname; 
      fid_hist_pdep[cart[0]][cart[1]][cart[2]][cart[3]][cart[4]]->Write();
      
      //std::cout <<std::endl  <<"Did we get this far? " <<cart[0] <<" " <<cart[1] << " " <<cart[2] << " " <<cart[3] << " " <<cart[4] <<std::endl;

      Draw_fid_pdep(cart[0],cart[1],cart[2],cart[3],cart[4],fid_hist_pdep[cart[0]][cart[1]][cart[2]][cart[3]][cart[4]]);
    }

    
    for(int r = 0; r < 4; r++){
      for(int t = 0; t<6; t++){
        for(int u = 0; u<13; u++){
          NS_Fid_pdep_C(r,t,u,c_fid_pdep[r][t][u]);
        }
      }
    }
    
    

}

#endif