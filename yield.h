#ifndef YIELD_H
#define YIELD_H

//Produce yields for the various binning options

#include "variables.h"
#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
#include "debugger.h"
#include "TCanvas.h"
#include "TGraph.h"

TGraph* g_yield_Q2Wbin[9][6][30];//{Place on canvas}{Q2 binning},{W binning}
//13 for MM 0.6 start at 1.1
//10 for angles starting at 10 for alpha with bins of 40 sep and 9 for theta with bins of 18

int MM2bins = 13;
int thbins = 10;
int albins = 10;

TCanvas* c_yield_Q2Wbin[6][30];//{Q2 binning},{W binning}(3x3)

const double cW = 4800;
const double cH = 4800;

bool Qbinning_check(double Q2){
	if(Q2 >= 2.0 && Q2 <= 5.0){
		return true;
	}else{
		return false;
	}
}

bool Wbinning_check(double W){
	if(W >= 1.4 && W <= 2.125){
		return true;
	}else{
		return false;
	}
}

bool MMbinning_check(int s, double MM){
	double n, x;
	n = YM_start[s];
	x = YM_start[s] + 13*YM_res[s];
	if(MM >= n && MM <= x){
		return true;
	}else{
		return false;
	}
}

int Q2binning(double Q2){
	bool pass =false;
	int i = -1;
	for(int j = 0; j < 7; j++){
		if(Q2 <= Q2bin_start + i*Q2bin_res && Q2 >= Q2bin_start + (j-1)*Q2bin_res){
			i = j;
		}
	}
	return i;
}

int Wbinning(double W){
	bool pass =false;
	int j = -1;
	for(int i = 0; i < 31; i++){
		if(W <= Wbin_start + i*Wbin_res && W >= Wbin_start + (i-1)*Wbin_res){
			j = i;
		}
	}
	return j;
}

int MM_stuff_binning(int s, double MM){
	//std::cout<<std::endl <<"The MM: " <<MM <<" and the bin is: ";
	int i = -1;
	for(int j = 0; j < MM2bins; j++){
		if(MM <= YM_start[s] + j*YM_res[s] && MM >= YM_start[s] + (j-1)*YM_res[s]){
			i = j;
		}
	}
	std::cout<<i <<std::endl;
	return i;
}

int theta_binning(double th){
	//std::cout<<std::endl <<"The theta: " <<th <<" and the bin is: ";
	int i = -1;
	for(int j = 0; j < thbins; j++){
		if(th <= Yth_start + j*Yth_res && th >= Yth_start + (j-1)*Yth_res){
			i = j;
		}
	}
	std::cout<<i <<std::endl;
	return i;
}

int alpha_binning(double a){
	//std::cout<<std::endl <<"The alpha: " <<a <<" and the bin is: ";
	int i = -1;
	for(int j = 0; j < albins; j++){
		if(a <= Yal_start + j*Yal_res && a >= Yal_start + (j-1)*Yal_res){
			i = j;
		}
	}
	std::cout<<i <<std::endl;
	return i;
}

double MM_bincenter(int s,int i){
	return YM_start[s] + i*YM_res[s]; 
}

double th_bincenter(int i){
	return Yth_start + i*Yth_res; 
}

double al_bincenter(int i){
	return Yal_start + i*Yal_res; 
}

//MM
void Graph_yield1(double x[9][6][30][13][10][10], double y[9][6][30][13][10][10]){
	std::vector<long> space_dims(3);
  	space_dims[0] = 9;
  	space_dims[1] = 6; //Q2 binning
  	space_dims[2] = 30; //W binning

  	double x1[13], y1[13];
  	double x2[10], y2[10];
  	double x3[10], y3[10];

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	float Qbot, Qtop, Wbot, Wtop; 
  	//std::cout<<std::endl <<"1";
  	for(int i = 0; i < 6; i++){
  		for(int j = 0; j <30; j++){
  			sprintf(cname1,"yield_Q2bin:%d_Wbin:%d",i,j);
  			c_yield_Q2Wbin[i][j] = new TCanvas(cname1,cname1,cW,cH);
  			c_yield_Q2Wbin[i][j]->Divide(3,3);
  		}
  	}
  	//std::cout<<std::endl <<"2" <<std::endl;

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish Q2 range
  		Qtop = Q2bin_start + ((cart[1]+1)*Q2bin_res);
  		Qbot = Qtop - Q2bin_res;
  		//std::cout<<std::endl <<"0.1: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2]<<std::endl;
      //Establish W range in titles
      if(cart[1] == 0 ){//All W
      	//std::cout<<std::endl <<"1.1: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2]<<std::endl;
        sprintf(hname, "%s_Q2:%f-%f_All_W",yield_n[cart[0]],Qbot,Qtop); 
       // std::cout<<std::endl <<"1.2: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2]<<std::endl;
      }
      else{
      	//std::cout<<std::endl <<"2.1: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2]<<std::endl;
        Wtop = Wbin_start + (cart[2]*Wbin_res);//constant.h
        Wbot = Wtop - Wbin_res; //constants.h
        sprintf(hname, "%s_Q2:%f-%f_W:%f-%f",yield_n[cart[0]],Qbot,Qtop,Wbot,Wtop); 
       // std::cout<<std::endl <<"2.2: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2]<<std::endl;
      }
     //hisname = species[cart[1]] + "_fid_sec" + (cart[0]+1) + cut[cart[2]]; //Naming convention: species_type_of_plot_sector#_cut_type
      //histitle = hisname; //For Fiducial I can make them both the same thing. 
      //std::cout<<std::endl <<"boop ba doop?" <<std::endl;
      if(cart[0]<3){
      	//std::cout<<std::endl <<"boop?" <<std::endl;
      	for(int go = 0; go < 13; go++){
      		//std::cout<<std::endl <<"3.1.1: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
      		x1[go]=x[cart[0]][cart[1]][cart[2]][go][0][0];
      		y1[go]=y[cart[0]][cart[1]][cart[2]][go][0][0];
      		//std::cout<<std::endl <<"MM "<<"x: "<<x1[go] <<" y: " <<y1[go];
      		//std::cout<<std::endl <<"MM "<<"x: "<<x[cart[0]][cart[1]][cart[2]][go][0][0] <<" y: " <<y[cart[0]][cart[1]][cart[2]][go][0][0];
      		
      		//std::cout<<std::endl <<"3.1.2: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
      	}
      	//std::cout<<std::endl <<"3.1: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
      	g_yield_Q2Wbin[cart[0]][cart[1]][cart[2]] = new TGraph(13,x1,y1);
      	//std::cout<<std::endl <<"3.2: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
      }
      if(3<= cart[0] && cart[0]<6){
      	//std::cout<<std::endl <<"ba?" <<std::endl;
      	for(int ho = 0; ho < 10; ho++){
      		//	std::cout<<std::endl <<"4.1.1: "  <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
      		x2[ho]=x[cart[0]][cart[1]][cart[2]][0][ho][0];
      		y2[ho]=y[cart[0]][cart[1]][cart[2]][0][ho][0];
      		//std::cout<<std::endl <<"theta "<<"x: "<<x2[ho] <<" y: " <<y2[ho];
      		//std::cout<<std::endl <<"theta "<<"x: "<<x[cart[0]][cart[1]][cart[2]][0][ho][0] <<" y: " <<y[cart[0]][cart[1]][cart[2]][0][ho][0];
      		//std::cout<<std::endl <<"4.1.2: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
      	}
      	g_yield_Q2Wbin[cart[0]][cart[1]][cart[2]] = new TGraph(10,x2,y2);
      ///	std::cout<<std::endl <<"4.2: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
      }
      if(6<= cart[0] && cart[0]<9){
      	//std::cout<<std::endl <<"doop?" <<std::endl;
      	for(int jo = 0; jo < 10; jo++){
      		//std::cout<<std::endl <<"5.1.1: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
      		x3[jo]=x[cart[0]][cart[1]][cart[2]][0][0][jo];
      		y3[jo]=y[cart[0]][cart[1]][cart[2]][0][0][jo];
      		//std::cout<<std::endl <<"alpha "<<"x: "<<x3[jo] <<" y: " <<y3[jo];
      		//std::cout<<std::endl <<"alpha "<<"x: "<<x[cart[0]][cart[1]][cart[2]][0][0][jo] <<" y: " <<y[cart[0]][cart[1]][cart[2]][0][0][jo];
      		//std::cout<<std::endl <<"5.1.2: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
      	}
      	g_yield_Q2Wbin[cart[0]][cart[1]][cart[2]] = new TGraph(10,x3,y3);
      	//std::cout<<std::endl <<"5.2: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
      }
      g_yield_Q2Wbin[cart[0]][cart[1]][cart[2]]->SetMarkerColor(2);
      g_yield_Q2Wbin[cart[0]][cart[1]][cart[2]]->SetLineColorAlpha(kBlue,0.0);
      g_yield_Q2Wbin[cart[0]][cart[1]][cart[2]]->SetMarkerStyle(21);
      g_yield_Q2Wbin[cart[0]][cart[1]][cart[2]]->SetMarkerSize(4);
      g_yield_Q2Wbin[cart[0]][cart[1]][cart[2]]->SetTitle(hname);
      g_yield_Q2Wbin[cart[0]][cart[1]][cart[2]]->GetYaxis()->SetTitle("Raw Yield");
      g_yield_Q2Wbin[cart[0]][cart[1]][cart[2]]->GetXaxis()->SetTitle(yield_n[cart[0]]);

      //assign to TCanvas 
     // std::cout<<std::endl <<"6.1: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
      c_yield_Q2Wbin[cart[1]][cart[2]]->cd(cart[0]+1);
      //std::cout<<std::endl <<"6.2: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
      g_yield_Q2Wbin[cart[0]][cart[1]][cart[2]]->Draw();
      //std::cout<<std::endl <<"6.3: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
    }
    //std::cout<<std::endl <<"3";
    for(int i = 0; i < 6; i++){
  		for(int j = 0; j <30; j++){
  			//std::cout<<std::endl <<"7.1: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
  			Qtop = Q2bin_start + ((i+1)*Q2bin_res);
  			Qbot = Qtop - Q2bin_res;
  			Wtop = Wbin_start + (j*Wbin_res);//constant.h
        	Wbot = Wtop - Wbin_res; //constants.h
        	//std::cout<<std::endl <<"7.2: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
  			sprintf(cname2,"Yield Q2:%f-%f W:%f-%f.pdf",Qbot,Qtop,Wbot,Wtop);
  			//std::cout<<std::endl <<"7.3: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
  			c_yield_Q2Wbin[i][j]->SaveAs(cname2);
  			//std::cout<<std::endl <<"7.4: " <<cart[0] <<" " <<cart[1] <<" " <<cart[2] <<std::endl;
  		}
  	}
  	//std::cout<<std::endl <<"4";

}

/*
//Theta
void Graph_yield2(int n, double x[10], double y[10]){
	std::vector<long> space_dims(3);
  	space_dims[0] = 3
  	space_dims[1] = 6; //Q2 binning
  	space_dims[2] = 30; //W binning

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	float Qbot, Qtop, Wbot, Wtop; 

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish Q2 range
  		Qtop = Q2bin_start + ((cart[1]+1)*Q2bin_res);
  		Qbot = Qtop - Q2bin_res

      //Establish W range in titles
      if(cart[1] == 0 ){//All W
        sprintf(hname, "%s_Q2:%f-%f_All_W",yield_n[cart[0]+3],Qbot,Qtop); 
      }
      else{
        Wtop = Wbin_start + (cart[2]*Wbin_res);//constant.h
        Wbot = Wtop - Wbin_res; //constants.h
        sprintf(hname, "%s_Q2:%f-%f_W:%f-%f",yield_n[cart[0]+3],Qbot,Qtop,Wbot,Wtop); 
      }
     //hisname = species[cart[1]] + "_fid_sec" + (cart[0]+1) + cut[cart[2]]; //Naming convention: species_type_of_plot_sector#_cut_type
      //histitle = hisname; //For Fiducial I can make them both the same thing. 
      c_yield_Q2Wbin[cart[0]+3][cart[1]][cart[2]] = new TGraph(n,x,y);
      c_yield_Q2Wbin[cart[0]+3][cart[1]][cart[2]]->SetMarkerColor(4);
      c_yield_Q2Wbin[cart[0]+3][cart[1]][cart[2]]->SetMarkerStyle(21);
      c_yield_Q2Wbin[cart[0]+3][cart[1]][cart[2]]->SetTitle(hname);
      c_yield_Q2Wbin[cart[0]+3][cart[1]][cart[2]]->GetYaxis()->SetTitle("Raw Yield");
      c_yield_Q2Wbin[cart[0]+3][cart[1]][cart[2]]->GetXaxis()->SetTitle(yield_n[cart[0]+3]);
    }
}

//Alphas
void Graph_yield3(int n, double x[10], double y[10]){
	std::vector<long> space_dims(3);
  	space_dims[0] = 3
  	space_dims[1] = 6; //Q2 binning
  	space_dims[2] = 30; //W binning

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh
  	float Qbot, Qtop, Wbot, Wtop; 

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
      //Establish Q2 range
  		Qtop = Q2bin_start + ((cart[1]+1)*Q2bin_res);
  		Qbot = Qtop - Q2bin_res

      //Establish W range in titles
      if(cart[1] == 0 ){//All W
        sprintf(hname, "%s_Q2:%f-%f_All_W",yield_n[cart[0]+6],Qbot,Qtop); 
      }
      else{
        Wtop = Wbin_start + (cart[2]*Wbin_res);//constant.h
        Wbot = Wtop - Wbin_res; //constants.h
        sprintf(hname, "%s_Q2:%f-%f_W:%f-%f",yield_n[cart[0]+6],Qbot,Qtop,Wbot,Wtop); 
      }
     //hisname = species[cart[1]] + "_fid_sec" + (cart[0]+1) + cut[cart[2]]; //Naming convention: species_type_of_plot_sector#_cut_type
      //histitle = hisname; //For Fiducial I can make them both the same thing. 
      c_yield_Q2Wbin[cart[0]+6][cart[1]][cart[2]] = new TGraph(n,x,y);
      c_yield_Q2Wbin[cart[0]+6][cart[1]][cart[2]]->SetMarkerColor(4);
      c_yield_Q2Wbin[cart[0]+6][cart[1]][cart[2]]->SetMarkerStyle(21);
      c_yield_Q2Wbin[cart[0]+6][cart[1]][cart[2]]->SetTitle(hname);
      c_yield_Q2Wbin[cart[0]+6][cart[1]][cart[2]]->GetYaxis()->SetTitle("Raw Yield");
      c_yield_Q2Wbin[cart[0]+6][cart[1]][cart[2]]->GetXaxis()->SetTitle(yield_n[cart[0]+6]);
    }
}
*/


#endif