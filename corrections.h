#ifndef CORRECTIONS_H
#define CORRECTIONS_H

#include "constants.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1.h"
#include "headers.h"
#include <cmath>

//This library contains the various functions working to correct varying aspects of the data



//Electron Angle Corrections (EAC)

const int num_theta_e_bins = 14;
const int num_phi_e_bins = 41;
const double phi_e_low = -25.0; 
const double phi_e_hig = 25.0;
const double theta_e_low = 13.0;
const double theta_e_hig = 26.0; 

const double eac_1_min = -0.2;
const double eac_1_max = 0.2;
const double eac_1_res = 200;

TH1D* eac_1[num_theta_e_bins][num_phi_e_bins][6]; //These are the yield plots for given phi_e and theta_e bins {theta_e}{phi_e}{sector}
TCanvas * c_eac_1[num_theta_e_bins][6];//{theta binning, sector} The phi binning is inside of the canvas
TH1D* eac_2[num_theta_e_bins][6]; //Determining phi_e dependence of fit parameters {theta_e}{sector}
TH1D* eac_3[4][6];//{A,B,C,D}{sector}
//Theta binning is 1 degree from 13 to 26 degrees => 14 bins
//Phi binning is 1.25 degree from -25 to 25 => 41 bins

double canw = 9600;
double canh = 8200;


//Detailed in K. Park's Thesis
bool elast_cut(double We){ //Isolate the elastic peak 
	bool pass = false; 
	if(We > 0.7 && We < 1.05){
		pass = true;
	}
	return pass;
}

//The change in polar angle for the electron
double theta_ecalc(double Energy, double theta_p){
	//std::cout<<std::endl <<"Tan theta_p: " <<TMath::Tan(theta_p);
	//std::cout<<std::endl <<"Shift in theta_e: " <<2*TMath::ATan(mp/((Energy + mp)*TMath::Tan(theta_p))) <<std::endl;
	return 2*TMath::ATan(mp/((Energy + mp)*TMath::Tan(theta_p*TMath::Pi()/180.0)))*180.0/TMath::Pi();
}

double delta_etheta(double energy, double theta_p, double theta_meas){
	return theta_ecalc(energy,theta_p) - theta_meas;
}

//Binning for theta_e and phi_e
double interval(double high, double low, int steps){//create equal steps for a high and a low value with steps number of steps
	//std::cout<<std::endl <<"high: " <<high <<std::endl <<"low: " <<low <<std::endl <<"steps: " <<steps <<std::endl <<"interval: " <<(high - low)/((double)steps-1.0) <<std::endl; 
	return (high - low)/((double)steps-1.0);
}

bool theta_e_bin_check(double theta_e){//Determines if theta_e can be properly binned
	bool pass = false;
	//std::cout<<std::endl <<"the theta interval: " <<interval(theta_e_hig,theta_e_low,num_theta_e_bins) <<std::endl;
	if(theta_e >= theta_e_low-(interval(theta_e_hig,theta_e_low,num_theta_e_bins)/2.0) && theta_e <= theta_e_hig+(interval(theta_e_hig,theta_e_low,num_theta_e_bins)/2.0)){
		pass = true;
	}
	return pass; 
} 

bool phi_e_bin_check(double phi_e){//determines if phi_e can be properly binnned
	bool pass = false; 
	//std::cout<<std::endl <<"the phi interval: " <<interval(phi_e_hig,phi_e_low,num_phi_e_bins) <<std::endl;
	if(phi_e >= phi_e_low-(interval(phi_e_hig,phi_e_low,num_phi_e_bins)/2.0) && phi_e <= phi_e_hig+(interval(phi_e_hig,phi_e_low,num_phi_e_bins)/2.0)){
		pass = true;
	}
	return pass; 
}

int theta_e_bin(double theta_e){//Get the proper bin for the given theta
	return floor(((theta_e - theta_e_low+(interval(theta_e_hig,theta_e_low,num_theta_e_bins)/2.0))/interval(theta_e_hig,theta_e_low,num_theta_e_bins)));
}

int phi_e_bin(double phi_e){//Get the proper bin for the given phi
	return floor(((phi_e - phi_e_low+(interval(phi_e_hig,phi_e_low,num_phi_e_bins)/2.0))/interval(phi_e_hig,phi_e_low,num_phi_e_bins)));
}

//Make and fill first yield plots for electron angule corrections
void MakeHist_eac_corr1(){
	std::vector<long> space_dims(3);
	space_dims[0] = num_theta_e_bins;
	space_dims[1] = num_phi_e_bins;
	space_dims[2] = 6; //sectors

	CartesianGenerator cart(space_dims);
	float bot_p, top_p, bot_t, top_t;

	while(cart.GetNextCombination()){
		bot_p = phi_e_low + (double) (interval(phi_e_hig,phi_e_low,num_phi_e_bins)*(cart[1]-0.5));
		top_p = phi_e_low + (double) (interval(phi_e_hig,phi_e_low,num_phi_e_bins)*(cart[1]+0.5));
		bot_t = theta_e_low + (double) (interval(theta_e_hig,theta_e_low,num_theta_e_bins)*(cart[0]-0.5));
		top_t = theta_e_low + (double) (interval(theta_e_hig,theta_e_low,num_theta_e_bins)*(cart[0]+0.5));
		sprintf(hname, "angle_corr_1|theta_e:%f-%f|phi_e:%f_%f|sec:%d",bot_t,top_t,bot_p,top_p,cart[2]+1);
		eac_1[cart[0]][cart[1]][cart[2]] = new TH1D(hname, hname, eac_1_res, eac_1_min, eac_1_max);
	}
}

void Fill_eac_corr1(double energy, double theta_p, double cx, double cy, double cz){
	//std::cout<<std::endl <<"energy: " <<energy <<" || theta_p: " <<theta_p <<" || cz: " <<cz <<std::endl;
	double phi = phi_center(cx,cy);
	int sec = get_sector(cx,cy);
	double theta = get_theta(cz);
	int tidx;
	int pidx;
	double delta_th_e; 
	
	if(phi_e_bin_check(phi) && theta_e_bin_check(theta)){
		tidx = theta_e_bin(theta);
		pidx = phi_e_bin(phi);
		//std::cout<<"theta: " <<theta <<" || tidx: " <<tidx <<" || pidx: " <<pidx <<std::endl;
		delta_th_e = delta_etheta(energy,theta_p,theta);
		//std::cout<<std::endl <<"here is delta theta " <<delta_th_e <<std::endl;
		eac_1[tidx][pidx][sec-1]->Fill(delta_th_e);
	}
}

/*void NS_eac_corr1(int tidx, int sidx, TCanvas* can){ //Naming those canvasas. The canvasas go by sector and Theta range and contain a range of phi's 
	float bot, top;
	bot = theta_e_low + (double) (interval(theta_e_hig,theta_e_low,num_theta_e_bins)*((double)tidx-1.0));
	top = theta_e_low + (double) (interval(theta_e_hig,theta_e_low,num_theta_e_bins)*((double)tidx-1.0));
	sprintf(cname2, "Electron Theta Correction Plots 1| Sector:%d|Theta:%f-%f",sidx+1,bot,top);
	can->SaveAs(cname2);
}*/

void Draw_eac_corr1(int cart0, int cart1, int cart2, TH1D * eac1){//Note that eac1 is not a constructed plot, but will be filled with the proper plot when the time comes
	c_eac_1[cart0][cart2] -> cd(cart1+1);
	eac1->Draw();
}

void Write_eac1(TFile *file){
	TDirectory * eac1_plots = file->mkdir("eac1_plots");
	eac1_plots->cd();
	TDirectory *  eac1_sec1 = eac1_plots->mkdir("eac1_sector1_plots");
	TDirectory *  eac1_sec2 = eac1_plots->mkdir("eac1_sector2_plots");
	TDirectory *  eac1_sec3 = eac1_plots->mkdir("eac1_sector3_plots");
	TDirectory *  eac1_sec4 = eac1_plots->mkdir("eac1_sector4_plots");
	TDirectory *  eac1_sec5 = eac1_plots->mkdir("eac1_sector5_plots");
	TDirectory *  eac1_sec6 = eac1_plots->mkdir("eac1_sector6_plots");
	
	std::vector<long> space_dims(3);
	space_dims[0] = num_theta_e_bins;
	space_dims[1] = num_phi_e_bins;
	space_dims[2] = 6; 
	//std::cout<<"is it here? 1" <<std::endl;
	CartesianGenerator cart(space_dims);
	float bot,top;

	for(int m = 0; m<num_theta_e_bins; m++){
		for(int n = 0; n<6; n++){
			bot = theta_e_low + (interval(theta_e_hig,theta_e_low,num_theta_e_bins)*((double)m-0.5));
			top = theta_e_low + (interval(theta_e_hig,theta_e_low,num_theta_e_bins)*((double)m+0.5));
			sprintf(cname1, "Electron Theta Correction Plots 1| Sector:%d|Theta:%f-%f",n+1,bot,top);
			c_eac_1[m][n] = new TCanvas(cname1,cname1,canw,canh);
			c_eac_1[m][n]->Divide(7,6);
		}
	}

	//std::cout<<"is it in here?" <<std::endl;
	while(cart.GetNextCombination()){
		
		eac_1[cart[0]][cart[1]][cart[2]]->SetXTitle("Change in Theta_e (deg)");
		eac_1[cart[0]][cart[1]][cart[2]]->SetXTitle("Yield");
		Draw_eac_corr1(cart[0],cart[1],cart[2],eac_1[cart[0]][cart[1]][cart[2]]);
	}

	
	//std::cout<<"is it out here?" <<std::endl;
	for(int j = 0; j<num_theta_e_bins; j++){
		for(int u = 0; u<6; u++){
			//NS_eac_corr1(j,u,c_eac_1[j][u]);
			switch(u){
				case 0: eac1_sec1->cd();
				break;
				case 1: eac1_sec2->cd();
				break;
				case 2: eac1_sec3->cd();
				break;
				case 3: eac1_sec4->cd();
				break;
				case 4: eac1_sec5->cd();
				break;
				case 5: eac1_sec6->cd();
				break;
			}
			bot = theta_e_low +(interval(theta_e_hig,theta_e_low,num_theta_e_bins)*((double)j-0.5));
			top = theta_e_low +(interval(theta_e_hig,theta_e_low,num_theta_e_bins)*((double)j+0.5));
			sprintf(cname2, "Electron Theta Correction Plots 1| Sector:%d|Theta:%f-%f",u+1,bot,top);
			c_eac_1[j][u]->SaveAs(cname2);
			c_eac_1[j][u]->Write();
		}
	}
	
}

//EAC Plots 2
//These are going to be actual graphs!! :O



#endif