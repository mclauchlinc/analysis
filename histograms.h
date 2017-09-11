#ifndef HISTOGRAMS_H
#define HISTOGRAMS_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"

//Declare all title pointers and plots first
char  htitle[100]; //The name on the graph itself (can have spaces)
char  hname[100]; //The name shown in the TBrowser (should have no spaces)
TH2D* fid_hist[6][4][5]; //Sector, species, cut
TH2D* WQ2_hist[9]; //look in constants.h for the 9 different parameters
TH2D* SF_hist[5]; //cuts 
TH2D* dt_hist[3][5]; //delta t, cuts
TH1D* dt_vertex[3]; //The hadron vertex distribution for each different particle 
TH1I* sc_plot;
TH1D* MM_hist[4][3];//Particle, cut


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
  std::cout<<space_dims <<" out of loop" <<std::endl;
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





void MakeHist_fid(){
	//Create Pointer for Histograms
	//Indexed: Sector, Species, Cut_Status
	

  	std::vector<long> space_dims(3);
  	space_dims[0] = 6; //Six sectors
  	space_dims[1] = 4; //electron, proton, pi+, pi-
  	space_dims[2] = 5; //No cut, cut, anti-cut, all cuts, bank

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	
  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
		  sprintf(hname, "%s_fid_sec%d_%s",species[cart[1]],cart[0]+1,norm_cut[cart[2]]); 
     //hisname = species[cart[1]] + "_fid_sec" + (cart[0]+1) + cut[cart[2]]; //Naming convention: species_type_of_plot_sector#_cut_type
      //histitle = hisname; //For Fiducial I can make them both the same thing. 
      fid_hist[cart[0]][cart[1]][cart[2]] = new TH2D( hname, hname, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
    }
}

void Fill_fid(int type, int level, double cx, double cy, double cz)
{
	double phi = phi_center(cx, cy); //fiducial.h
	double theta = get_theta(cz);  //fiducial.h
	int sec = get_sector(cx, cy);  //fiducial.h
  int sidx = sec-1;
	//Level {0,1,2,3} -> {no cut, cut, anti-cut, all cuts}
  //Type {0,1,2,3} -> {e, p, pip, pim}
  if(type == 1){
   // std::cout<<"PROTON FID" ;
  }
  if(type == 2 || type == 3){
  //  std::cout<<"PION FID" ;
  }
	fid_hist[sidx][type][level]->Fill(phi, theta);
}


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

//Fill_dt(0,0,p, p0, sc_r, sc_r0, sc_t, sc_t0);
void Fill_dt(int s, int cut, int sc, double p, double p0, double d, double d0, double t, double t0){
  /*
  for species: {p,pip,pim} -> {0,1,2}
  cut: {pre, cut, anti, pid, bank} -> {0,1,2,3,4}
  */
  if(sc != 0){
    double mass = 10000;
    int q = 0;
    if(s == 0){
      mass = mp;
     // std::cout<< " Proton dt! " ;
    }
    if(s == 1 || s == 2){
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

/*
species missing {0,1,2,3} -> {proton, pip, pim, zero}
cut {0,1,2} -> {pre, cut, anti} 
*/
void Fill_MM(int species, int cut, double mm){
  MM_hist[species][cut] ->Fill(mm);
}


void MakeHist(){
  MakeHist_fid();
  MakeHist_WQ2();
  MakeHist_SF();
  MakeHist_dt();
  MakeHist_dt_vert();
  MakeHist_sc();
  MakeHist_MM();
}


#endif