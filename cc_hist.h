#ifndef CC_HIST_H
#define CC_HIST_H

#include "constants.h"
#include "headers.h"
#include "CartesianGenerator.hh"
/*
cc_part
cc_sect
cc_hit
cc_segm
*/

TH1D* cc_min_hist[6][18][5][4];//Sector //Segment //Cuts {none,sf,e fiducial,both} //left,coincident,right,all

void MakeHist_MinCC(){
	//Create Pointer for Histograms
	//Indexed: Sector, Species, Cut_Status
	

  	std::vector<long> space_dims(4);
  	space_dims[0] = 6; //sector
  	space_dims[1] = 18; //Segment
  	space_dims[2] = 5; //Cuts
  	space_dims[3] = 4; //left, coincidence, right, all

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh
    	sprintf(hname, "%s_Min_CC_%s_Sector:%d_Seg:%d",cc_pos[cart[3]],cc_cuts[cart[2]],cart[0]+1,cart[1]+1); 
  
     //hisname = species[cart[1]] + "_fid_sec" + (cart[0]+1) + cut[cart[2]]; //Naming convention: species_type_of_plot_sector#_cut_type
      //histitle = hisname; //For Fiducial I can make them both the same thing. 
      cc_min_hist[cart[0]][cart[1]][cart[2]][cart[3]]= new TH1D( hname, hname, MinCCres, MinCCmin, MinCCmax);
    }
}

//Getting the proper segment number out from cc_segm
int cc_segment(int cc_segm){
	int seg = -1;

	if(cc_segm > 0 && cc_segm <200){
		seg = ((cc_segm)/10)-1;
		//std::cout<<"cc_seg: " <<cc_segm <<" -> " <<seg <<"             " <<std::endl;
	}
	if(cc_segm > 1000 && cc_segm <1200){
		seg = ((cc_segm-1000)/10)-1;
		//std::cout<<"cc_seg: " <<cc_segm <<" -> " <<seg<<"             " <<std::endl;
	}
	if(cc_segm > 2000 && cc_segm <2200){
		seg = ((cc_segm-2000)/10)-1;
		//std::cout<<"cc_seg: " <<cc_segm <<" -> " <<seg<<"             " <<std::endl;
	}
	return seg;
}

//Defining left, right, or coincidence hits in the CC
int cc_lrc(int cc_segm){
	int po = -1;
	if(cc_segm > 0 && cc_segm <200){
		po = 0;//left
	}
	if(cc_segm > 1000 && cc_segm <1200){
		po = 1;//coincident
	}
	if(cc_segm > 2000 && cc_segm <2200){
		po = 2;//right
	}
	
	return po;
}

void Fill_MinCC( int cc_sector, int nphe, int cc_segm, int cut){
	int segment = cc_segment(cc_segm);
	int lrc = cc_lrc(cc_segm);
	
	//Avoid seg 
	//std::cout<<"Filling?" <<std::endl;
	if(lrc!=-1){
	//	std::cout<<"Now filling:" <<std::endl;
		//std::cout<<std::endl <<"cc_segm = " <<cc_segm <<"|lrc = " <<lrc <<"| seg = " <<segment <<std::endl;
		//std::cout<<std::endl <<"nphe: " <<nphe  <<std::endl;
		cc_min_hist[cc_sector-1][segment][cut][lrc]->Fill(nphe);//Filling for all the W 
		cc_min_hist[cc_sector-1][segment][cut][3]->Fill(nphe);//Filling for all the W 
	//	std::cout<<"Filled" <<std::endl;
	}
}

void Write_MinCC(TFile *file){
	//std::cout<<"boop" <<std::endl;
	TDirectory * Min_CC_plots = file->mkdir("Min_CC_plots");
	Min_CC_plots->cd();

	TDirectory * Min_CC_1 = Min_CC_plots->mkdir("Min_CC_1");
	TDirectory * Min_CC_2 = Min_CC_plots->mkdir("Min_CC_2");
	TDirectory * Min_CC_3 = Min_CC_plots->mkdir("Min_CC_3");
	TDirectory * Min_CC_4 = Min_CC_plots->mkdir("Min_CC_4");
	TDirectory * Min_CC_5 = Min_CC_plots->mkdir("Min_CC_5");
	TDirectory * Min_CC_6 = Min_CC_plots->mkdir("Min_CC_6");
	//std::cout<<"doop" <<std::endl;

  	std::vector<long> space_dims(4);
  	space_dims[0] = 6; //Sectors
  	space_dims[1] = 18; //Sector
  	space_dims[2] = 5;//Cuts
  	space_dims[3] =4;//left, coinc, right, all

  	CartesianGenerator cart(space_dims); //Look in CartesianGenerator.hh

  	//in the loop
  	while(cart.GetNextCombination()) {//CartesianGenerator.hh

  		switch(cart[0]){
      	case 0: Min_CC_1->cd();
      	break;
      	case 1: Min_CC_2->cd();
      	break;
      	case 2: Min_CC_3->cd();
      	break;
      	case 3: Min_CC_4->cd();
      	break;
      	case 4: Min_CC_5->cd();
      	break;
      	case 5: Min_CC_6->cd();
      	break;
      }
      cc_min_hist[cart[0]][cart[1]][cart[2]][cart[3]]->SetXTitle("nphe");
      cc_min_hist[cart[0]][cart[1]][cart[2]][cart[3]]->SetYTitle("Counts");
      cc_min_hist[cart[0]][cart[1]][cart[2]][cart[3]]->Write();
    }
}


#endif