#ifndef HISTOGRAMS_H
#define HISTOGRAMS_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"
//various histogram types
#include "fiducial histograms.h"
#include "W Q2 histograms.h"
#include "delta_t histograms.h"
#include "sf histograms.h"
#include "MM histograms.h"
#include "COM histograms.h"
#include "cross section histograms.h"



//Declare all title pointers and plots first
//char  htitle[100]; //The name on the graph itself (can have spaces)
//char  hname[100]; //The name shown in the TBrowser (should have no spaces)
//TH2D* fid_hist[6][4][5]; //Sector, species, cut, pos/neg
//TH2D* WQ2_hist[9]; //look in constants.h for the 9 different parameters
TH2D* SF_hist[5]; //cuts 
TH2D* dt_hist[3][5]; //delta t, cuts, pos/neg
TH1D* dt_vertex[3]; //The hadron vertex distribution for each different particle 
TH1I* sc_plot;
TH1D* MM_hist[4][3];//Particle, cut
//TH2D* WQ2_hist_ES[5];//Topology
TH2D* MM_Cross[6];//Topology Crosses
TH1D* alpha_hist[3];//Topology
TH1D* MM_hist_par[3];//toplolgy
TH1D* theta_hist_par[3];//topology
TH1D* alpha_hist_bin[3][6][7];//topology, W binning, Q2 binnng
TH1D* theta_hist_bin[3][6][7];//topology, W binning, Q2 binnng
TH1D* MM_hist_bin[3][6][7];//topology, W binning, Q2 binnng

TH1D* MM_pim_M[2][10];// MM for the pi minus missing with changes in mass ID for proton and pi+ {W var, M var}
TH1D* MM_hist_pim_m[2];//Total MM with variation in mass for proton/pi+
//W Variance
TH1D* MM_W[3][10];//Discovering the W dependence of the strange peak in the Pim MM //2/7 changed order of index. See if fixes filling issue
//TH2D* fid_hist_W[6][4][5][10]; //Sector, species, cut, pos/neg, W binning
TH2D* dt_hist_W[3][5][10]; //delta t, cuts, pos/neg, W binning
TH2D* SF_hist_W[5][10]; //cuts 

/*
//Conversion from string to char *
char* Str2CharS( std::string str){
  char * write = new char[str.size()+1]; //Creates a char* with the proper dimensions for the string
  std::copy(str.begin(),str.end(),write); //Copies the string over into the char array that is the char*
  return write; 
}
*/


/* Gary stuff
#include "CartesianGenerator.hh"
//Sector, species, cut_status
  TH2D* fid_hist[6][4][4];

  std::vector<long> space_dims(3);
  space_dims[0] = 6;
  space_dims[1] = 4;
  space_dims[2] = 4;

  CartesianGenerator cartgen(space_dims);
  //in the loop
  while(cartgen.GetNextCombination()) {
	sprintf(hname, "%s_fid_sec%d_%s",species[cart[1]],cart[0]+1,cut[cart[2]]);
    sprintf(htitle, "%s_fid_sec%d_%s",species[cart[1]],cart[0]+1,cut[cart[2]]);
    fid_hist[cart[0]][cart[1]][cart[2]] = new TH2D(hname, htitle, FIDxres, FIDxmin, FIDxmin, FIDyres, FIDymin, FIDymax);
  }
*/

//W vs. Q^2
/*
Cut Types: 
*/

void MakeHist_WQ2(){
  //Create Pointer for Histograms
  /*Indexed: Cut_Status
    - Pre = no cut
    - Cut = EID Cut
    - Anti-Cut = !EID
    - All = All cuts
  */
  int space_dims = 9;//The cuts in constants.h
  //std::cout<<space_dims <<" out of loop" <<std::endl;
  for(int w = 0; (w < 9); w++){ 
    sprintf(hname,"W_Q2_%s",eid_cut[w]); //constants.h and otherwise writing the specific cut to the right plot
    WQ2_hist[w] = new TH2D( hname, hname, WQxres, WQxmin, WQxmax, WQyres, WQymin, WQymax); // constants.h
  }
}

void Fill_WQ2(int set, int cut, double p, double cx, double cy, double cz){
  double W, Q2;
  //Set refers to the data set, due to them having different beam energies: 1->e16 and 2->e1f
  W = WP(set, p, cx, cy, cz); // physics.h  
  Q2 = Qsquared(set , p, cx, cy, cz); // physics.h
  // Cut: {0,1,2,3} -> {pre,cut,anti,all}
  WQ2_hist[cut]->Fill(W,Q2);
}

//Fiducial
/*int fid_num = 6;
int fid_types = 4;
int fid_tot = 24;
TH2D * e_fid_hist[24];
TH2D * p_fid_hist[24];
TH2D * pip_fid_hist[24];
TH2D * pim_fid_hist[24];
*/



//Fiducial
/*

void MakeHist_fid(){
	//Create Pointer for Histograms
	//Indexed: Sector, Species, Cut_Status
	

  	std::vector<long> space_dims(3);
  	space_dims[0] = 6; //Six sectors
  	space_dims[1] = 4; //electron, proton, pi+, pi-
  	space_dims[2] = 5; //No cut, cut, anti-cut, all cuts, bank
    space_dims[3] = 11; //W binnings with 0 being no discrimination 

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	float bot, top; 

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish W range
      if(cart[3] == 0 ){
        bot = 0.0; 
        top = 5.0;
      }
      else{
        top = Wbin_start + (cart[3]*Wbin_res);//constant.h
        bot = top - Wbin_res; //constants.h
      }
		  sprintf(hname, "%s_fid_sec%d_%s_WRange:%f-%f",species[cart[1]],cart[0]+1,norm_cut[cart[2]],bot,top); 
     //hisname = species[cart[1]] + "_fid_sec" + (cart[0]+1) + cut[cart[2]]; //Naming convention: species_type_of_plot_sector#_cut_type
      //histitle = hisname; //For Fiducial I can make them both the same thing. 
      fid_hist[cart[0]][cart[1]][cart[2]][cart[3]] = new TH2D( hname, hname, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
    }
}

//Make each individual particle's fiducial plots
//electron
void MakeHist_fide(){
  std::vector<long> space_dims(2);
  space_dims[0] =6;//sectors
  space_dims[1] = 5; //no cut, cut, anti, all, bank

  CartesianGenerator cart(space_dims);

  while(cart.GetNextCombination()){
    sprintf(hname,"e_fid_sec%d_%s",cart[0]+1,norm_cut[cart[1]]);
    fid_hist[0][cart[0]][cart[1]] = new TH2D( hname, hname, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
  }
}

//proton
void MakeHist_fidp(){
  std::vector<long> space_dims(2);
  space_dims[0] =6;//sectors
  space_dims[1] = 5; //no cut, cut, anti, all, bank

  CartesianGenerator cart(space_dims);

  while(cart.GetNextCombination()){
    sprintf(hname,"p_fid_sec%d_%s",cart[0]+1,norm_cut[cart[1]]);
    fid_hist[1][cart[0]][cart[1]] = new TH2D( hname, hname, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
  }
}

//pi+
void MakeHist_fidpip(){
  std::vector<long> space_dims(2);
  space_dims[0] =6;//sectors
  space_dims[1] = 5; //no cut, cut, anti, all, bank

  CartesianGenerator cart(space_dims);

  while(cart.GetNextCombination()){
    sprintf(hname,"pip_fid_sec%d_%s",cart[0]+1,norm_cut[cart[1]]);
    fid_hist[2][cart[0]][cart[1]] = new TH2D( hname, hname, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
  }
}

//Pi-
void MakeHist_fidpim(){
  std::vector<long> space_dims(2);
  space_dims[0] =6;//sectors
  space_dims[1] = 5; //no cut, cut, anti, all, bank

  CartesianGenerator cart(space_dims);

  while(cart.GetNextCombination()){
    sprintf(hname,"pim_fid_sec%d_%s",cart[0]+1,norm_cut[cart[1]]);
    fid_hist[3][cart[0]][cart[1]] = new TH2D( hname, hname, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
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
 for(int i = 1; i < 11 ; i++){
    top = Wbin_start + (i * Wbin_res);
    bot = top - Wbin_res;
    if(W > bot && W < top){
      fid_hist[sidx][type][level][i]->Fill(phi, theta);
    }
  }
	fid_hist[sidx][type][level][0]->Fill(phi, theta);//Filling for all the W 
}
*/


/*
void Fid_Write()
{
	//Sector
	for(int sec = 0; sec<6; sec++){
		//Species
		for(int spe = 0; spe < 4; spe++){
			//cut
			for(int c = 0; c < 4; c++){
				fid_hist[sec][spe][c]->SetYTitle("#theta");
    			fid_hist[sec][spe][c]->SetXTitle("#phi");
    			fid_hist[sec][spe][c]->Write();
			}
		}
	}
}
*/


void MakeHist_SF(){
  //Create Pointer for Histograms
  /*Indexed: Cut_Status
    - Pre = no cut
    - Cut = EID Cut
    - Anti-Cut = !EID
    - All = All cuts
  */

  int space_dims = 5;//pre, cut, anti, pid, bank

  for(int w = 0; w<space_dims ; w++){
    sprintf(hname,"sf_%s",norm_cut[w]); 
    SF_hist[w] = new TH2D( hname, hname, SFxres, SFxmin, SFxmax, SFyres, SFymin, SFymax); // constants.h
  }
}

void Fill_sf(int level, double etot, double p){
  double sf_thing = sf(etot,p);
  // Cut: {0,1,2,3} -> {pre,cut,anti,all}
  SF_hist[level]->Fill(p,sf_thing);
}

//Delta t
/*
species: {p, pip, pim}  3
cut: {pre, cut, anti, pid, bank}  5
*/

void MakeHist_dt(){
  std::vector<long> space_dims(2);
    space_dims[0] = 3; //species
    space_dims[1] = 5; //cut

    CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    
    //in the loop
    while(cart.GetNextCombination()) {//CartesianGenerator.hh
      sprintf(hname, "%s_delta_t_%s",species[cart[0]+1],norm_cut[cart[1]]);  
      dt_hist[cart[0]][cart[1]] = new TH2D( hname, hname, DTxres, DTxmin, DTxmax, DTyres, DTymin, DTymax);
    }
}

//delta t plots for individual hadrons
//proton
void MakeHist_dtp(){
  for(int i=0;i<5;i++){
    sprintf(hname,"p_delta_t_%s",norm_cut[i]);
    dt_hist[0][i] = new TH2D( hname, hname, DTxres, DTxmin, DTxmax, DTyres, DTymin, DTymax);
  }
}

//pi+
void MakeHist_dtpip(){
  for(int i=0;i<5;i++){
    sprintf(hname,"pip_delta_t_%s",norm_cut[i]);
    dt_hist[1][i] = new TH2D( hname, hname, DTxres, DTxmin, DTxmax, DTyres, DTymin, DTymax);
  }
}
//pi-
void MakeHist_dtpim(){
  for(int i=0;i<5;i++){
    sprintf(hname,"pim_delta_t_%s",norm_cut[i]);
    dt_hist[2][i] = new TH2D( hname, hname, DTxres, DTxmin, DTxmax, DTyres, DTymin, DTymax);
  }
}

//Fill_dt(0,0,p, p0, sc_r, sc_r0, sc_t, sc_t0);
void Fill_dt(int s, int cut, int sc, double p, double p0, double d, double d0, double t, double t0){
  /*
  for species: {p,pip,pim} -> {0,1,2}
  cut: {pre, cut, anti, pid, bank} -> {0,1,2,3,4}
  */
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
    dt_hist[s][cut] -> Fill(p,dt);
  }
}

void MakeHist_dt_vert(){
  for(int w = 0; w<3; w++){
    sprintf(hname,"%s_dt_vertex", species[w+1]);
    dt_vertex[w] = new TH1D(hname, hname, DTyres, DTymin, DTymax);
  }
}

void Fill_dt_vert(int s, double p, double d,double t ){
  int mass = 10000;
  int q = 0;
  if(s == 0){
    mass = mp;
  }
  if(s == 1 || s == 2){
    mass = PION;
  }
  if(s >2 || s < 0){
    std::cout << "you fucked up, friend" <<std::endl;
  }
  double vertex = vert_p(p,d,t, mass );
  dt_vertex[s] -> Fill(vertex);
}

void MakeHist_sc(){
  sprintf(hname,"sc");
  sc_plot = new TH1I(hname,hname, 10,-0.5,9.5);
}

void Fill_sc(int sc){
  if(DEBUG){

  }
  sc_plot -> Fill(sc);
}

//Makes all Missing mass plots
void MakeHist_MM(){
  std::vector<long> space_dims(2);
    space_dims[0] = 4; //species
    space_dims[1] = 3; //cut

  CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    
  //in the loop
  while(cart.GetNextCombination()) {//CartesianGenerator.hh
    sprintf(hname, "%s_MM_%s",species[cart[0]+1],norm_cut[cart[1]]);  
    MM_hist[cart[0]][cart[1]] = new TH1D( hname, hname, MMxres, MMxmin, MMxmax);
  }   
}

//Makes Missing Mass Plots for just Proton Missing
void MakeHist_MMp(){
  for(int i=0;i<3;i++){
    sprintf(hname,"p_MM_%s",norm_cut[i]);
    MM_hist[0][i] = new TH1D( hname, hname, MMxres, MMxmin, MMxmax);
  }
}

//Makes Missing Mass Plot for just Pi+ Missing
void MakeHist_MMpip(){
  for(int i=0;i<3;i++){
    sprintf(hname,"pip_MM_%s",norm_cut[i]);
    MM_hist[1][i] = new TH1D( hname, hname, MMxres, MMxmin, MMxmax);
  }
}

//Makes Missing Mass Plot for just Pi- Missing
void MakeHist_MMpim(){
  for(int i=0;i<3;i++){
    sprintf(hname,"pim_MM_%s",norm_cut[i]);
    MM_hist[2][i] = new TH1D( hname, hname, MMxres, MMxmin, MMxmax);
  }
}

/*
species missing {0,1,2,3} -> {proton, pip, pim, zero}
cut {0,1,2} -> {pre, cut, anti} 
*/
void Fill_MM(int species, int cut, double mm){
  MM_hist[species][cut] ->Fill(mm);
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
}*/

void MakeHist_MM_Cross(){
   //Create Pointer for Histograms

  int space_dims = 6;//The cuts in constants.h;
  for(int w = 0; (w < space_dims); w++){ 
    sprintf(hname,"MM_cross_%s",cross_top[w]); //constants.h and otherwise writing the specific cut to the right plot
    MM_Cross[w] = new TH2D( hname, hname, MMxres, MMxmin, MMxmax, MMxres, MMxmin, MMxmax); // constants.h
  }
}

void Fill_MM_Cross(int top, double MM1, double MM2){
  MM_Cross[top]->Fill(MM1,MM2);
}

void MakeHist_Alpha(){
  for(int w = 0; (w < 3); w++){ 
    sprintf(hname,"Alpha_%s",alpha_stuff[w]); //constants.h and otherwise writing the specific cut to the right plot
    alpha_hist[w] = new TH1D( hname, hname, alphaxres, alphaxmin, alphaxmax); // constants.h
  }
}

void Fill_Alpha(int set, double a){
  alpha_hist[set]->Fill(a);
}

void MakeHist_MM_par(){
  for(int w = 0; (w < 3); w++){ 
    sprintf(hname,"MM_hist_%s",alpha_stuff[w]); //constants.h and otherwise writing the specific cut to the right plot
    MM_hist_par[w] = new TH1D( hname, hname, MMxres, MMxmin, MMxmax); // constants.h
  }
}

void Fill_MM_par(int set, double a){
  MM_hist_par[set]->Fill(a);
}

void MakeHist_theta_par(){
  for(int w = 0; (w < 3); w++){ 
    sprintf(hname,"theta_%s",alpha_stuff[w]); //constants.h and otherwise writing the specific cut to the right plot
    theta_hist_par[w] = new TH1D( hname, hname, FIDyres, FIDymin, FIDymax); // constants.h
  }
}

void Fill_theta_par(int set, double theta){
  theta_hist_par[set]->Fill(theta);
}

void MakeHist_Alpha_bin(){
  std::vector<long> space_dims(3);
    space_dims[0] = 16; //Q2 binning
    space_dims[1] = 8; //W binning
    space_dims[2] = 3;//topology

  CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  double berp = Wmin;
  double merp = Q2min;
  double upW; 
  double downW;
  double upQ;
  double downQ;
  //in the loop
  while(cart.GetNextCombination()) {//CartesianGenerator.hh
     berp = Wmin + cart[1]*Wres;
    merp = Q2min + cart[0]*Q2res;
    downW = berp - (Wres/2);
    upW = berp + (Wres/2);
    upQ = merp + (Q2res/2);
    downQ = merp - (Q2res/2);
    sprintf(hname, "Alpha_%s_W:%f-%f_Q2:%f-%f",alpha_stuff[cart[2]],downW,upW,downQ,upQ);  
    alpha_hist_bin[cart[2]][cart[1]][cart[0]] = new TH1D( hname, hname, alphaxres, alphaxmin, alphaxmax);
  }   
}

void Fill_Alpha_bin(int top, int Wbin, int Q2bin, double alpha){
  alpha_hist_bin[top][Wbin][Q2bin] -> Fill(alpha);
}

void MakeHist_MM_bin(){
  std::vector<long> space_dims(3);
    space_dims[0] = 16; //Q2 binning
    space_dims[1] = 8; //W binning
    space_dims[2] = 3;//topology

  CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  double berp = Wmin;
  double merp = Q2min;
  double upW; 
  double downW;
  double upQ;
  double downQ;
  //in the loop
  while(cart.GetNextCombination()) {//CartesianGenerator.hh
    berp = Wmin + cart[1]*Wres;
    merp = Q2min + cart[0]*Q2res;
    downW = berp - (Wres/2);
    upW = berp + (Wres/2);
    upQ = merp + (Q2res/2);
    downQ = merp - (Q2res/2);
    sprintf(hname, "MM_%s_W:%f-%f_Q2:%f-%f",alpha_stuff[cart[2]],downW,upW,downQ,upQ);  
    MM_hist_bin[cart[2]][cart[1]][cart[0]] = new TH1D( hname, hname, MMxres, MMxmin, MMxmax);
  }   
}

void Fill_MM_bin(int top, int Wbin, int Q2bin, double MM){
  MM_hist_bin[top][Wbin][Q2bin] -> Fill(MM);
}

void MakeHist_theta_bin(){
  std::vector<long> space_dims(3);
    space_dims[0] = 16; //Q2 binning
    space_dims[1] = 8; //W binning
    space_dims[2] = 3;//topology

  CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  double berp = Wmin;
  double merp = Q2min;
  double upW; 
  double downW;
  double upQ;
  double downQ;
  //in the loop
  while(cart.GetNextCombination()) {//CartesianGenerator.hh
    berp = Wmin + cart[1]*Wres;
    merp = Q2min + cart[0]*Q2res;
    downW = berp - (Wres/2);
    upW = berp + (Wres/2);
    upQ = merp + (Q2res/2);
    downQ = merp - (Q2res/2);
    sprintf(hname, "theta_%s_W:%f-%f_Q2:%f-%f",alpha_stuff[cart[2]],downW,upW,downQ,upQ);  
    theta_hist_bin[cart[2]][cart[1]][cart[0]] = new TH1D( hname, hname, FIDyres, FIDymin, FIDymax);
    
    //std::cout<< std::endl <<downW <<" " <<upW <<std::endl;
    //std::cout<< std::endl <<downQ <<" " <<upQ <<std::endl;
  }   
}

void Fill_theta_bin(int top, int Wbin, int Q2bin, double theta){
  theta_hist_bin[top][Wbin][Q2bin] -> Fill(theta);
}

void MakeHist_MM_Wvar(){
  double number = 1.0; 
  int t = 0; 
  for(int w = 0; (w < 3); w++){ 
    number = 1.0;
    for(int r = 0; r<10 ; r++){
      t = w +1; 
      sprintf(hname,"MM_%s_Wvar_%f-%f",species[t],number,(number+0.2)); //constants.h and otherwise writing the specific cut to the right plot
      MM_W[w][r] = new TH1D( hname, hname, MMxres, MMxmin, MMxmax); // constants.h
      number = number + 0.2; 
    }
  }
}

//p -> {0,1,2} -> {proton, pip, pim}
void Fill_MM_Wvar(int set, int p, double MM){
  MM_W[p][set]->Fill(MM);
}

void Fill_MM_Wall(int p, double W, double MM){
  double bot, top, res, start;
  bot = 1.0;
  res = 0.2;
  for(int i = 0; i < 10 ; i++){
    top = bot + res;
    if(W > bot && W < top){
      Fill_MM_Wvar(i,p,MM);
    }
    bot = bot + res; ; 
  }




  /*if(W > 1.0 && W < 1.2){
      Fill_MM_Wvar(0, p, MM);
   }
   if(W > 1.2 && W < 1.4){
      Fill_MM_Wvar(1, p, MM);
   }
   if(W > 1.4 && W < 1.6){
      Fill_MM_Wvar(2, p, MM);
   }
   if(W > 1.6 && W < 1.8){
      Fill_MM_Wvar(3, p, MM); 
   }
   if(W > 1.8 && W < 2.0){
      Fill_MM_Wvar(4, p, MM);
   }
   if(W > 2.0 && W < 2.2){
      Fill_MM_Wvar(5, p, MM);
   }
   if(W > 2.2 && W < 2.4){
      Fill_MM_Wvar(6, p, MM);
   }
   if(W > 2.4 && W < 2.6){
      Fill_MM_Wvar(7, p, MM);
   }
   if(W > 2.6 && W < 2.8){
      Fill_MM_Wvar(8, p, MM);
   }
   if(W > 2.8 && W < 3.0){
      Fill_MM_Wvar(9, p, MM);
   }*/
}

void WriteHist_MM_Wvar(){
  TDirectory * MM_W_var_stuff = output -> mkdir("MM_W_var_stuff");
  MM_W_var_stuff->cd();
  double number = 1.0; 
  int t = 0; 
  for(int w = 0; (w < 3); w++){ 
    number = 1.0;
    for(int r = 0; r<10 ; r++){
      MM_W[w][r]->SetXTitle("MM (GeV)");
      MM_W[w][r]->SetYTitle("Counts");
      MM_W[w][r]->Write();
    }
  }
}

//Let's look at different replacements for four vectors
void MakeHist_MMpim_Mvar(){
  double number = 1.0; 
  for(int w = 0; (w < 10); w++){ 
    for( int e = 0; e < 2; e++){
      sprintf(hname,"MM_PIM_Mvar_%s_%f-%f",mvar[e],number,(number+0.2)); //constants.h and otherwise writing the specific cut to the right plot
      MM_pim_M[e][w] = new TH1D( hname, hname, MMxres, MMxmin, MMxmax); // constants.h
    }
    number = number + 0.2;
  }
}

void Fill_MMpim_Mvar(int set, int m, double MM){
  //m-> {switch, 2pi}
  MM_pim_M[m][set]->Fill(MM);
}

void Fill_MMpim_Mall(int m, double W, double MM){
  if(W > 1.0 && W < 1.2){
      Fill_MMpim_Mvar(0, m, MM);
   }
   if(W > 1.2 && W < 1.4){
      Fill_MMpim_Mvar(1, m, MM);
   }
   if(W > 1.4 && W < 1.6){
      Fill_MMpim_Mvar(2, m, MM);
   }
   if(W > 1.6 && W < 1.8){
      Fill_MMpim_Mvar(3, m, MM); 
   }
   if(W > 1.8 && W < 2.0){
      Fill_MMpim_Mvar(4, m, MM);
   }
   if(W > 2.0 && W < 2.2){
      Fill_MMpim_Mvar(5, m, MM);
   }
   if(W > 2.2 && W < 2.4){
      Fill_MMpim_Mvar(6, m, MM);
   }
   if(W > 2.4 && W < 2.6){
      Fill_MMpim_Mvar(7, m, MM);
   }
   if(W > 2.6 && W < 2.8){
      Fill_MMpim_Mvar(8, m, MM);
   }
   if(W > 2.8 && W < 3.0){
      Fill_MMpim_Mvar(9, m, MM);
   }
}


//MM_hist_pim_m
//Makes Missing Mass Plot for just Pi- Missing
void MakeHist_MMpimM(){
  for(int i=0;i<2;i++){
    sprintf(hname,"pim_MM_%s_pre",mvar[i]);
    MM_hist_pim_m[i] = new TH1D( hname, hname, MMxres, MMxmin, MMxmax);
  }
}

/*
species missing {0,1,2,3} -> {proton, pip, pim, zero}
cut {0,1,2} -> {pre, cut, anti} 
*/
void Fill_MMpimM( int cut, double mm){
  MM_hist_pim_m[cut] ->Fill(mm);
}


TH2D* fid_hist_W[6][4][5][10]; //Sector, species, cut, pos/neg, W binning
TH2D* dt_hist_W[3][5][10]; //delta t, cuts, pos/neg, W binning
TH2D* SF_hist_W[5][10]; //cuts 
//W variance of Fiducial
Void MakeHist_fid_W(){
  //Create Pointer for Histograms
  //Indexed: Sector, Species, Cut_Status

    std::vector<long> space_dims(3);
    space_dims[0] = 6; //Six sectors
    space_dims[1] = 4; //electron, proton, pi+, pi-
    space_dims[2] = 5; //No cut, cut, anti-cut, all cuts, bank
    space_dims[3] = 10; //W binning

    CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
    
    //in the loop
    while(cart.GetNextCombination()) {//CartesianGenerator.hh
      sprintf(hname, "%s_fid_sec%d_%s",species[cart[1]],cart[0]+1,norm_cut[cart[2]]); 
     //hisname = species[cart[1]] + "_fid_sec" + (cart[0]+1) + cut[cart[2]]; //Naming convention: species_type_of_plot_sector#_cut_type
      //histitle = hisname; //For Fiducial I can make them both the same thing. 
      fid_hist[cart[0]][cart[1]][cart[2]] = new TH2D( hname, hname, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
    }
}





//Combined Functions

void MakeHist(){
  //MakeHist_fid();
  MakeHist_WQ2();
  MakeHist_SF();
  MakeHist_dt();
  //MakeHist_dt_vert();
  //MakeHist_sc();
  MakeHist_MM();
  MakeHist_WQ2_ES();
  MakeHist_MM_Cross();
  MakeHist_Alpha();
  MakeHist_MM_par();
  MakeHist_theta_par();
  //MakeHist_Alpha_bin();
  //MakeHist_MM_bin();
 // MakeHist_theta_bin();
  MakeHist_MM_Wvar();
  //MakeHist_MMpim_Mvar();
  //MakeHist_MMpimM();
}

void MakeHist_p(){
  MakeHist_dtp();
  MakeHist_fidp();
  MakeHist_MMp();
}

void MakeHist_e(){
  MakeHist_fide();
  MakeHist_SF();
}

void MakeHist_pip(){
  MakeHist_dtpip();
  MakeHist_fidpip();
  MakeHist_MMpip();
}
void MakeHist_pim(){
  MakeHist_dtpim();
  MakeHist_fidpim();
  MakeHist_MMpim();
}


#endif