#ifndef HIST_CHARGE_H
#define HIST_CHARGE_H

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"
#include "fiducial.h"

TH2D* fid_hist_q[6][5][2]; //Sector, cut, pos/neg
TH2D* dt_hist_q[5][2];

void MakeHist_fidp_q(){
  std::vector<long> space_dims(3);
  space_dims[0] =6;//sectors
  space_dims[1] = 6; //no cut, cut, anti, cross, pid, bank
  space_dims[2] = 2; //positive, negative

  CartesianGenerator cart(space_dims);

  while(cart.GetNextCombination()){
    sprintf(hname,"p_fid_sec%d_%s_%s",cart[0]+1,char_cut[cart[1]],charge[cart[2]]);
    fid_hist_q[cart[0]][cart[1]][cart[2]] = new TH2D( hname, hname, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
  }
}

void MakeHist_dtp_q(){
  std::vector<long> space_dims(2);
  space_dims[0] = 6;//pre, cut, anti, pid, bank
  space_dims[1] = 2; //Pos/neg

  CartesianGenerator cart(space_dims);
  while(cart.GetNextCombination()){
    sprintf(hname,"p_delta_t_%s_%s",char_cut[cart[0]],charge[cart[1]]);
    dt_hist_q[cart[0]][cart[1]] = new TH2D( hname, hname, DTxres, DTxmin, DTxmax, DTyres, DTymin, DTymax);
  }
}

//Fill_dt(0,0,p, p0, sc_r, sc_r0, sc_t, sc_t0);
void Fill_dt_q(int q, int cut, int sc, double p, double p0, double d, double d0, double t, double t0){
  /*
  for species: {p,pip,pim} -> {0,1,2}
  cut: {pre, cut, anti, combo, pid, bank} -> {0,1,2,3,4,5}
  */double mass = mp;
	int ch ;
  if(sc != 0){
  	double dt = delta_t(p, p0, d, d0, t, t0, mass );
    if( q == 1){
    	ch = 0;
    	dt_hist_q[cut][ch] -> Fill(p,dt);
    }
    if( q == -1){
    	ch = 1;
    	dt_hist_q[cut][ch] -> Fill(p,dt);
    }    
  }
}
void Fill_fid_q(int q, int level, double cx, double cy, double cz)
{
	double phi = phi_center(cx, cy); //fiducial.h
	double theta = get_theta(cz);  //fiducial.h
	int sec = get_sector(cx, cy);  //fiducial.h
  int sidx = sec-1;
	int duck; 
	//Level {0,1,2,3} -> {no cut, cut, anti-cut, all cuts}
  //Type {0,1,2,3} -> {e, p, pip, pim}
  if(q == 1){
   // std::cout<<"PROTON FID" ;
  	duck = 0;

	fid_hist_q[sidx][level][duck]->Fill(phi, theta);
  }
  if(q == -1){
  //  std::cout<<"PION FID" ;
  	duck = 1;

	fid_hist_q[sidx][level][duck]->Fill(phi, theta);
  }
}

#endif