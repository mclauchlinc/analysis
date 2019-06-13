#ifndef CORRECTIONS_H
#define CORRECTIONS_H

#include "constants.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1.h"
#include "headers.h"
#include <cmath>
#include "TGraph.h"
#include "CartesianGenerator.hh"
#include "variables.h"
#include <iostream>
#include <vector>
#include "fitting.h"

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

//Electron angle corrections
    double eac1_pars[num_theta_e_bins][num_phi_e_bins][6][8];//{theta}{phi}{sector}{parameters and errors}//For the angular electron momentum corrections step 1
    double eac2_x[num_theta_e_bins][num_phi_e_bins][6];//{theta},{phi}{sector}
    double eac2_y[num_theta_e_bins][num_phi_e_bins][6];//{theta}{phi}{sector}
    double eac2_pars[num_theta_e_bins][6][10];//{theta}{sector}{A,B,C,D,E + errors}
    double eac3_pars[5][6][6];//{A,B,C,D,E}{sector}{alpha,beta,gamma + errors}

TH1D* eac_1[num_theta_e_bins][num_phi_e_bins][6]; //These are the yield plots for given phi_e and theta_e bins {theta_e}{phi_e}{sector}
TCanvas * c_eac_1[num_theta_e_bins][6];//{theta binning, sector} The phi binning is inside of the canvas
TGraph* eac_2[num_theta_e_bins][6]; //Determining phi_e dependence of fit parameters {theta_e}{sector}
TGraph* eac_3[4][6];//{A,B,C,D}{sector}
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
		sprintf(hname, "angle_corr_1|theta_e:%f-%f|phi_e:%f-%f|sec:%d",bot_t,top_t,bot_p,top_p,cart[2]+1);
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

TCanvas* c_eac_2[6]; //Sector

double phi_bin_center(int phi_bin){
	return phi_e_low+phi_bin*interval(phi_e_hig,phi_e_low,num_phi_e_bins);
}

double array_zero_bye(double array[]){

}

void Graph_eac2(double eac2_x1[num_theta_e_bins][num_phi_e_bins][6], double eac2_y1[num_theta_e_bins][num_phi_e_bins][6], TFile *file){
	
	//std::vector <long> 
	double x2[num_theta_e_bins][6][num_phi_e_bins], y2[num_theta_e_bins][6][num_phi_e_bins];//Making the x and y's for the various plots
	//I'm probably already going to have problems I think where I'm not actually utilizing the full space for phi_e binning given my quality restriction, but we'll see
	int temp_phi_idx;
	//Make the new TDirectory, TCanvases, and TGraphs
	TDirectory* eac2_plots = file->mkdir("eac2_plots");
	eac2_plots->cd();

	int can_rows = round((TMath::Sqrt(num_theta_e_bins)));//Just make squares for now
	double top, bot;

	for(int s = 0; s < 6; s++){//Sector binning loop
		sprintf(cname1,"eac2_sec:%d",s+1);
		c_eac_2[s] = new TCanvas(cname1,cname1,canw,canh);
		c_eac_2[s]->Divide(can_rows,can_rows);
		for(int y = 0; y<num_theta_e_bins; y++){//theta binning loop
			bot = theta_e_low +(interval(theta_e_hig,theta_e_low,num_theta_e_bins)*((double)y-0.5));
			top = theta_e_low +(interval(theta_e_hig,theta_e_low,num_theta_e_bins)*((double)y+0.5));
			temp_phi_idx = num_phi_e_bins;//Reset before the u loop
			for(int u = 0; u<num_phi_e_bins;u++){//phi binning loop
				//if(eac2_y1[y][u][s] != 0){//Getting those zeros out which come from
					x2[y][s][u] = eac2_x1[y][u][s];
					std::cout<<std::endl <<"x2 for sector" <<s+1 <<" and theta bin " <<y <<" is:" <<x2[u] <<std::endl;
					y2[y][s][u] = eac2_y1[y][u][s];
					std::cout <<"y2 for sector" <<s+1 <<" and theta bin " <<y <<" is:" <<y2[u] <<std::endl;
					
				//}
			}
			eac_2[y][s] = new TGraph(num_phi_e_bins,x2[y][s],y2[y][s]);//Create new TGraph for given theta range and sector
			sprintf(hname,"eac2_sec%d_theta:%f-%f",s+1,bot,top);
			eac_2[y][s]->SetMarkerColor(9);
      		eac_2[y][s]->SetMarkerStyle(20);
		    eac_2[y][s]->SetMarkerSize(1);
		    eac_2[y][s]->SetTitle(hname);
		    eac_2[y][s]->GetYaxis()->SetTitle("Change in Theta (deg)");
		    eac_2[y][s]->GetXaxis()->SetTitle("Phi (deg)");
			c_eac_2[s]->cd(y+1);//Find right place in the canvas
			eac_2[y][s]->Draw("AP");//Place the plot there
		}
		c_eac_2[s]->SaveAs(cname1);
		c_eac_2[s]->Write();
	}
}

//TF1 *eac2_fit = new TF1()

void Graph_eac2_2(double eac2_x1[num_theta_e_bins][num_phi_e_bins][6], double eac2_y1[num_theta_e_bins][num_phi_e_bins][6], TFile *file){
	
	std::vector <double>  x2, y2;//Making the x and y's for the various plots
	//I'm probably already going to have problems I think where I'm not actually utilizing the full space for phi_e binning given my quality restriction, but we'll see
	int temp_phi_idx;
	//Make the new TDirectory, TCanvases, and TGraphs
	TDirectory* eac2_plots = file->mkdir("eac2_plots");
	eac2_plots->cd();

	int r,q; 

	int can_rows = round((TMath::Sqrt(num_theta_e_bins)));
	//int can_col = //Just make squares for now. These depend on bins 
	double top, bot;

	double xr[num_theta_e_bins][6][2];//To give the highest and lowest value for Phi to use as our fit bounds 
	//std::cout<<std::endl <<"here1" <<std::endl;

	for(int s = 0; s < 6; s++){//Sector binning loop
		//std::cout <<"here2" <<std::endl;
		sprintf(cname1,"eac2_sec:%d",s+1);
		c_eac_2[s] = new TCanvas(cname1,cname1,canw,canh);
		c_eac_2[s]->Divide(can_rows,can_rows);
		for(int y = 0; y<num_theta_e_bins; y++){//theta binning loop
			//std::cout <<"here3" <<std::endl;
			bot = theta_e_low +(interval(theta_e_hig,theta_e_low,num_theta_e_bins)*((double)y-0.5));
			top = theta_e_low +(interval(theta_e_hig,theta_e_low,num_theta_e_bins)*((double)y+0.5));
			temp_phi_idx = num_phi_e_bins;//Reset before the u loop
			q = 0; 
			for(int u = 0; u<num_phi_e_bins;u++){//phi binning loop
				//std::cout <<"here4" <<std::endl;
				if(eac2_y1[y][u][s] != 0 && eac2_y1[y][u][s] <= 0.2 && eac2_y1[y][u][s] >= -0.2){//Getting those zeros out which come from
					//std::cout<<std::endl <<std::endl <<"eac2_x for sector" <<s+1 <<" and theta bin " <<y <<" and phi bin: " <<u <<" is:" <<(double)eac2_x1[y][u][s] <<std::endl;
					//std::cout<<"eac2_y for sector" <<s+1 <<" and theta bin " <<y <<" and phi bin: " <<u <<" is:" <<(double)eac2_y1[y][u][s];
					x2.push_back(eac2_x1[y][u][s]);
					//std::cout<<std::endl <<"x2 for sector" <<s+1 <<" and theta bin " <<y <<" and phi bin: " <<u <<" is:" <<x2[q] <<std::endl;
					y2.push_back(eac2_y1[y][u][s]);
					//std::cout <<"y2 for sector" <<s+1 <<" and theta bin " <<y <<" and phi bin: " <<u <<" is:" <<y2[q] <<std::endl;	
					q++;
				}
			}
			//std::cout <<"here5" <<std::endl;
			if(int(y2.size())>0){
				eac_2[y][s] = new TGraph(int(y2.size()),&x2[0],&y2[0]);//Create new TGraph for given theta range and sector
				xr[y][s][0] = x2[0];//Assign x fit lower bound
				xr[y][s][1] = x2[int(x2.size())-1];//x fit upper bound
				sprintf(hname,"eac2_sec%d_theta:%f-%f",s+1,bot,top);
				eac_2[y][s]->SetMarkerColor(9);
	      		eac_2[y][s]->SetMarkerStyle(20);
			    eac_2[y][s]->SetMarkerSize(1);
			    eac_2[y][s]->SetTitle(hname);
			    eac_2[y][s]->GetYaxis()->SetTitle("Change in Theta (deg)");
			    eac_2[y][s]->GetXaxis()->SetTitle("Phi (deg)");
				c_eac_2[s]->cd(y+1);//Find right place in the canvas
				eac_2[y][s]->Draw("AP");//Place the plot there
			}else{//For the fitting step later
				xr[y][s][0]=-100;
				xr[y][s][1]=-100;
			}
			x2.clear();
			y2.clear();
		}
		//std::cout <<"here6" <<std::endl;
		

		//Some fun fitting!
		for(int i = 0; i<num_theta_e_bins; i++){
			//std::cout <<"here7" <<std::endl;
			if(xr[i][s][1]!=-100){//If there are no good friends in a particular theta/sector bin then the upper and lower bounds for the fit are not properly defined. Therefore we must exclude said events
				fit_eac2(eac_2[i][s],xr[i][s][0],xr[i][s][1],0.0,0.0,0.0,0.0,0.0,eac2_pars,i,s);//fitting.h
				//std::cout <<"here8" <<std::endl;
			}
		}
		c_eac_2[s]->SaveAs(cname1);
		c_eac_2[s]->Write();
	}
}

double theta_bin_center(int theta_bin){
	return theta_e_low+theta_bin*interval(theta_e_hig,theta_e_low,num_theta_e_bins);
}

TCanvas * c_eac_3[6];

void Graph_eac3(double pars[num_theta_e_bins][6][10], TFile *file){
	std::vector<double> x3, y3;
	double xr[5][6][2];//Give upper and lower bounds for given plots 

	TDirectory *eac3_plots = file->mkdir("eac3_plots");
	eac3_plots->cd();

	for(int s = 0; s<6; s++){//Sector Loop
		//Make the Canvas
		sprintf(cname1,"eac3_sector:%d",s+1);
		c_eac_3[s] = new TCanvas(cname1,cname1,canh,canw);
		c_eac_3[s]->Divide(5,1);//Just the four plots for the A,B,C,D in a given sector
		for(int a = 0; a<5; a++){//A,B,C,D loop
			for(int t = 0; t<num_theta_e_bins; t++){//Theta loop
				if((pars[t][s][a]/pars[t][s][a+5]) <= 0.01 && pars[t][s][a+5]!=0){
					y3.push_back(pars[t][s][a]);
					x3.push_back(theta_bin_center(t));
				}
			}
			if(int(y3.size())>0){//To make sure we have any points to put in the plot
				eac_3[a][s] = new TGraph(int(y3.size()),&x3[0],&y3[0]);//Create new TGraph for given theta range and sector
				xr[a][s][0] = x3[0];//Assign x fit lower bound
				xr[a][s][1] = x3[int(x3.size())-1];//x fit upper bound
				sprintf(hname,"eac3_sec%d_Var_%s",s+1,eac3_word1[a]);
				eac_3[a][s]->SetMarkerColor(9);
	      		eac_3[a][s]->SetMarkerStyle(20);
			    eac_3[a][s]->SetMarkerSize(1);
			    eac_3[a][s]->SetTitle(hname);
			    eac_3[a][s]->GetYaxis()->SetTitle("Value of Constant");
			    eac_3[a][s]->GetXaxis()->SetTitle("Theta (deg)");
				c_eac_3[s]->cd(a+1);//Find right place in the canvas
				eac_3[a][s]->Draw("AP");//Place the plot there
			}else{
				xr[a][s][0] = -100;
				xr[a][s][1] = -100; 
			}
			x3.clear();
			y3.clear();
		}
		for(int b = 0;b<5; b++){
			if(xr[b][s][0]!=-100){
				fit_eac3(eac_3[b][s],xr[b][s][0],xr[b][s][1],0.0,0.0,0.0,eac3_pars,b,s);
			}
		}
		c_eac_3[s]->SaveAs(cname1);
		c_eac_3[s]->Write();
	}
}


#endif