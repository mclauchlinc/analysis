#include "constants.h"

#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TH2.h"
#include "TH1.h"
#include "TMath.h"
#include "TString.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "delta_t_id.h"

/*
double delta_t( Float_t p, Float_t p0, Float_t d, Float_t d0, Float_t t, Float_t t0, double m )
{
	double vertex_e = (double)t0-(double)d0/c_special;
	double vertex_p = (double)t-((double)d/c_special)*sqrt(1.0 + m*m/((double)p*(double)p));
	return vertex_e - vertex_p;
}

int sc_index(int index, UChar_t sc[23])
{
 	int scidx = (int)sc[index]-1;
 	return scidx;
}

bool delta_t_proton(int idx, Float_t p[23], Float_t d[23], Float_t t[23], UChar_t sc[23])
{
	bool isproton = kFALSE;
	int sidx = sc_index(idx, sc);
	double dt = delta_t(p[idx],p[0],d[sidx],d[sc_index(0,sc)],t[sidx],t[sc_index(0,sc)],mp);
	if(dt>(DTL[0]+DTL[1]*p[idx]+DTL[2]*p[idx]*p[idx]+DTL[3]*p[idx]*p[idx]*p[idx]) && dt<(DTH[0]+DTH[1]*p[idx]+DTH[2]*p[idx]*p[idx]+DTH[3]*p[idx]*p[idx]*p[idx]) )
	{
		isproton = kTRUE;
	}
	return isproton;
}

bool delta_t_pion(int idx, Float_t p[23], Float_t d[23], Float_t t[23], UChar_t sc[23])
{
	bool ispion = kFALSE;
	int sidx = sc_index(idx, sc);
	double dt = delta_t(p[idx],p[0],d[sidx],d[sc_index(0,sc)],t[sidx],t[sc_index(0,sc)],mpi);
	if(dt>(DTL[0]+DTL[1]*p[idx]+DTL[2]*p[idx]*p[idx]+DTL[3]*p[idx]*p[idx]*p[idx]) && dt<(DTH[0]+DTH[1]*p[idx]+DTH[2]*p[idx]*p[idx]+DTH[3]*p[idx]*p[idx]*p[idx]) )
	{
		ispion = kTRUE;
	}
	return ispion;
}
*/


using namespace std;
int main()
{
	int file_num = 0;
	cout<< "Files Loading:";
	//Enter Data (this is e1f data)
	TChain chain("h10");
	//chain.AddFile("/home/mclauchlinc/Desktop/data/data_e1f_pass2_v1/root_37685_pass1.a04.root"); 	file_num++;
	//chain.AddFile("/home/mclauchlinc/Desktop/data/data_e1f_pass2_v1/root_37687_pass1.a20.root");	file_num++;
	/*chain.AddFile("/home/mclauchlinc/Desktop/data/data_e1f_pass2_v1/root_37688_pass1.a18.root");	file_num++;
	//chain.AddFile("/home/mclauchlinc/Desktop/data/data_e1f_pass2_v1/root_37690_pass1.a06.root");	file_num++;
	//chain.AddFile("/home/mclauchlinc/Desktop/data/data_e1f_pass2_v1/root_37690_pass1.a15.root");	file_num++;
	//chain.AddFile("/home/mclauchlinc/Desktop/data/data_e1f_pass2_v1/root_37692_pass1.a04.root");	file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e1f_pass2_v1/root_37693_pass1.a11.root");	file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e1f_pass2_v1/root_37694_pass1.a06.root");	file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e1f_pass2_v1/root_37698_pass1.a02.root");	file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e1f_pass2_v1/root_37698_pass1.a14.root");	file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e1f_pass2_v1/root_37747_pass1.a05.root");	file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e1f_pass2_v1/root_37805_pass1.a18.root");	file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e1f_pass2_v1/root_37806_pass1.a03.root");	file_num++;
	*/
	/*
	//This is e16 data
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30540_pass1.a13.root"); file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30540_pass1.a14.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30540_pass1.a15.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30540_pass1.a16.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30570_pass1.a03.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30570_pass1.a08.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30570_pass1.a09.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30570_pass1.a22.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30570_pass1.a23.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30570_pass1.a24.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30583_pass1.a00.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30583_pass1.a01.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30583_pass1.a02.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30583_pass1.a03.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30583_pass1.a04.root");file_num++;
	chain.AddFile("/home/mclauchlinc/Desktop/data/data_e16/ntp_30583_pass1.a05.root");file_num++;
	*/

	//Actual e16 Data
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a00.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a01.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a02.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a03.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a04.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a05.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a06.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a07.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a08.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a09.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a10.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a11.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a12.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a13.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a14.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a15.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a16.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a17.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a18.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a19.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a20.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a21.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a22.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a23.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a24.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a25.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a26.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a27.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a28.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a29.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a30.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a31.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a32.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a33.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a34.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30540_pass1.a35.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a00.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a01.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a02.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a03.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a04.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a05.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a06.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a07.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a08.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a09.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a10.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a11.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a12.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a13.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a14.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a15.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30541_pass1.a16.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a00.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a01.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a02.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a03.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a04.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a05.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a06.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a07.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a08.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a09.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a10.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a11.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a12.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a13.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a14.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a15.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a16.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a17.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a18.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a19.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a20.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a21.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a22.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30542_pass1.a23.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30543_pass1.a00.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30563_pass1.a00.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30568_pass1.a00.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30568_pass1.a01.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30568_pass1.a02.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30568_pass1.a03.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30570_pass1.a00.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30570_pass1.a01.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30570_pass1.a02.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30570_pass1.a03.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30570_pass1.a04.00.root");file_num++;
	chain.AddFile("/Users/cmc/Desktop/phd/data/e16/ntp_30570_pass1.a05.00.root");file_num++;
		
	cout<<" Loaded" <<endl;

	cout<<"There are " <<file_num <<" Files loaded" <<endl;

	cout<<"Creating File: ";
	//Open the Output File 
	TFile output("delta_t_cut.root","RECREATE","delta_t_cut");

	cout<<"File Created" <<endl;

	cout<<"Defining Root Variables: ";

	//Define Root Variables
	Float_t sc_t[23];
	Float_t sc_r[23];
	UChar_t sc[23];
	Char_t q[23];
	Int_t gpart;
	Float_t p[23];
	cout<<"Done" <<endl;

	cout<<"Defining Program Variables: ";
	//Define delta_t variables
	double dt_p;
	double dt_pip;
	double dt_pim;

	double p_v;
	double pip_v;

	int sidx;
	int eidx;

	//Define Progress number
	int progress;

	cout<<"Done" <<endl;


	cout<<"Setting Branch Addresses: ";
	//Set Branch Address
	chain.SetBranchAddress("sc_t",&sc_t);
	chain.SetBranchAddress("sc_r",&sc_r);
	chain.SetBranchAddress("sc",&sc);
	chain.SetBranchAddress("p",&p);
	//chain.SetBranchAddress("q",&q);
	chain.SetBranchAddress("gpart",&gpart);

	cout<<"Done" <<endl;

	//Get the number of events
	int events = chain.GetEntries();
	cout<<"number of events: " <<events <<endl;

	cout<<"Plot Skeletons: ";
	//Create Plots
	TH2F *plot1 = new TH2F("delta_t_proton","Delta_t Assume Proton Mass",300,0.0,7.0,200,-4.0,4.0);
	TH2F *plot2 = new TH2F("delta_t_proton_cut","Delta_t Assume Proton Mass using function",300,0.0,7.0,200,-4.0,4.0);
	TH2F *plot3 = new TH2F("delta_t_pion+","Delta_t Assume Pion+ Mass",300,0.0,7.0,200,-4.0,4.0);
	TH2F *plot4 = new TH2F("delta_t_pion-","Delta_t Assume Pion- Mass",300,0.0,7.0,200,-4.0,4.0);
	TH2F *plot5 = new TH2F("delta_t_pip_cut","Delta_t Assume pi plus cut ",300,0.0,7.0,300,-4.0,4.0);
	TH2F *plot6 = new TH2F("delta_t_pim_cut","Delta_t Assume pi Minus cut",300,0.0,7.0,300,-4.0,4.0);
	

	cout<<"Made" <<endl;

	cout<<"Looping Through Events" <<endl;
	//Loop through events
	for(int i=0;i<events;i++)
	{
		chain.GetEntry(i);
		progress = (int) 100.0*(((double)i+1.0)/(double)events);
		//cout<<"Current Entry " <<i <<"\r";
		//Electron Vertex Time
		//cut_beta_e = 1.0/sqrt(1+me*me/(p[0]*p[0]));
		//Strange error with attempting to have lengths of 1060000000 or so. I am confused. 
		if(gpart<=23)
		{
			for(int j=1;j<gpart;j++)
			{
				sidx = sc_index(j, sc);

				p_v = vert_p(p[j],sc_r[sidx],sc_t[sidx],mp);
				pip_v = vert_p(p[j],sc_r[sidx],sc_t[sidx],mp);

				cout<<"Proton Vertex: " <<p_v <<" and Pion Vertex: " <<pip_v <<endl;
				
				if((int)q[j]==1)
				{
					dt_p = delta_t(p[j],p[0],sc_r[sidx],sc_r[sc_index(0,sc)],sc_t[sidx],sc_t[sc_index(0,sc)],mp);
					dt_pip = delta_t(p[j],p[0],sc_r[sidx],sc_r[sc_index(0,sc)],sc_t[sidx],sc_t[sc_index(0,sc)],mpi);

					plot1->Fill(p[j],dt_p);
					plot3->Fill(p[j],dt_pip);
					if( delta_t_proton(j, p, sc_r, sc_t, sc) == kTRUE)
					{
						plot2->Fill(p[j],dt_p);
					}
					if( delta_t_pion(j, p, sc_r, sc_t, sc)== kTRUE)
					{
						plot5->Fill(p[j],dt_pip);
					}
				}
				if((int)q[j]==-1)
				{
					dt_pim = delta_t(p[j],p[0],sc_r[sidx],sc_r[sc_index(0,sc)],sc_t[sidx],sc_t[sc_index(0,sc)],mpi);
					plot4->Fill(p[j],dt_pim);
					if( delta_t_pion(j, p, sc_r, sc_t, sc) == kTRUE)
					{
						plot6->Fill(p[j],dt_pim);
					}
				}
			}
		}
		cout<<"Progess Percent " <<progress <<"\r";
	}
	cout<<endl;
	cout<<"Loop Complete" <<endl;
	//Write to the file and close it
	output.Write();
	cout<<"written to file" <<endl;
	output.Close();
	cout<<"File Closed" <<endl;
	return 0;
}