#ifndef FITTING_H
#define FITTING_H


#include "TH1.h"
#include "TF1.h"
#include "headers.h"
#include "TMath.h"



void fit_b_wig2(TH1D* hist, double lowb, double upb, double m0, double gamma0, double max, double &par1, double &par2, double &par3, double &err1, double &err2, double &err3){
	//double* pointer[4];
	TF1 *b_wig = new TF1("b_wig","[2]*(2*sqrt(2)*[0]*[1]*sqrt([0]*[0]*([0]*[0]+[1]*[1])))/(TMath::Pi()*((x-[0]*[0])*(x-[0]*[0])+[0]*[0]*[1]*[1])*sqrt([0]*[0]+sqrt([0]*[0]*([0]*[0]+[1]*[1]))))",-0.2,1.2);
	b_wig->SetParameter(0,m0);
	b_wig->SetParameter(1,gamma0);
	b_wig->SetParameter(2,max);
	hist->Fit(b_wig,"Q+","",lowb,upb);//MQ+
	par1 = b_wig->GetParameter(0);
	par2 = b_wig->GetParameter(1);
	par3 = b_wig->GetParameter(2);
	err1 = b_wig->GetParError(0);
	err2 = b_wig->GetParError(1);
	err3 = b_wig->GetParError(2);
}

void fit_b_wig2_mult(TH1D* hist, int t, double lowb, double upb, double m0, double gamma0, double max, double &par1, double &par2, double &par3, double &err1, double &err2, double &err3){
	//double* pointer[4];
	int t1 = 0; 
	fit_b_wig2(hist, lowb, upb, m0, gamma0, max, par1, par2, par3, err1, err2, err3);
	if(t > 1){
		t1 = t-1; 
	}
	else{
		t = t;
	}
	for(int i = 0; i< t1; i++){
		fit_b_wig2(hist, lowb, upb, par1, par2, par3, par1, par2, par3, err1, err2, err3);
	}
}

void fit_b_wig(TH1D* hist, double lowb, double upb, double m0, double gamma0, double max, double &par1, double &par2, double &par3, double &err1, double &err2, double &err3){
	//double* pointer[4];
	TF1 *b_wig = new TF1("b_wig","[2]*(2*sqrt(2)*[0]*[1]*sqrt([0]*[0]*([0]*[0]+[1]*[1])))/(TMath::Pi()*((x*x-[0]*[0])*(x*x-[0]*[0])+[0]*[0]*[1]*[1])*sqrt([0]*[0]+sqrt([0]*[0]*([0]*[0]+[1]*[1]))))",-0.2,1.2);
	b_wig->SetParameter(0,m0);
	b_wig->SetParameter(1,gamma0);
	b_wig->SetParameter(2,max);
	hist->Fit(b_wig,"Q+","",lowb,upb);
	par1 = b_wig->GetParameter(0);
	par2 = b_wig->GetParameter(1);
	par3 = b_wig->GetParameter(2);
	err1 = b_wig->GetParError(0);
	err2 = b_wig->GetParError(1);
	err3 = b_wig->GetParError(2);
}

void fit_b_wig_mult(TH1D* hist, int t, double lowb, double upb, double m0, double gamma0, double max, double &par1, double &par2, double &par3, double &err1, double &err2, double &err3){
	//double* pointer[4];
	int t1 = 0; 
	fit_b_wig(hist, lowb, upb, m0, gamma0, max, par1, par2, par3, err1, err2, err3);
	if(t > 1){
		t1 = t -1; 
	}
	else{
		t1 = t;
	}
	for(int i = 0; i< t1; i++){
		fit_b_wig(hist, lowb, upb, par1, par2, par3, par1, par2, par3, err1, err2, err3);
	}
}

void fit_gaus(TH1D* hist, double lowb, double upb, double m0, double gamma0, double max, double &par1, double &par2, double &par3, double &err1, double &err2, double &err3){
	double* pointer[4];
	TF1 *b_wig = new TF1("b_wig","[2]*TMath::Exp(-(x-[0])*(x-[0])/(2*[1]*[1]))",lowb,upb);
	b_wig->SetParameter(0,m0);
	b_wig->SetParameter(1,gamma0);
	b_wig->SetParameter(2,max);
	hist->Fit(b_wig,"Q+","",lowb,upb);
	par1 = b_wig->GetParameter(0);
	par2 = b_wig->GetParameter(1);
	par3 = b_wig->GetParameter(2);
	err1 = b_wig->GetParError(0);
	err2 = b_wig->GetParError(1);
	err3 = b_wig->GetParError(2);
}

void fit_gaus_mult(TH1D* hist, int t, double lowb, double upb, double m0, double gamma0, double max, double &par1, double &par2, double &par3, double &err1, double &err2, double &err3){
	//double* pointer[4];
	int t1 = 0;
	fit_gaus(hist, lowb, upb, m0, gamma0, max, par1, par2, par3, err1, err2, err3);
	for(int i = 0; i< t; i++){
		fit_gaus(hist, lowb, upb, par1, par2, par3, par1, par2, par3, err1, err2, err3);
	}
}

void fit_gaus_2(TH1D* hist, double lowb, double upb, double m0, double gamma0, double max, double &par1, double &par2, double &par3, double &err1, double &err2, double &err3, double m02, double gamma02, double max2, double &par12, double &par22, double &par32, double &err12, double &err22, double &err32){
	double* pointer[4];
	TF1 *b_wig = new TF1("b_wig","[2]*TMath::Exp(-(x-[0])*(x-[0])/(2*[1]*[1]))+[5]*TMath::Exp(-(x-[3])*(x-[3])/(2*[4]*[4]))",lowb,upb);
	b_wig->SetParameter(0,m0);
	b_wig->SetParameter(1,gamma0);
	b_wig->SetParameter(2,max);
	b_wig->SetParameter(3,m02);
	b_wig->SetParameter(4,gamma02);
	b_wig->SetParameter(5,max2);

	hist->Fit(b_wig,"Q+","",lowb,upb);
	par1 = b_wig->GetParameter(0);
	par2 = b_wig->GetParameter(1);
	par3 = b_wig->GetParameter(2);
	err1 = b_wig->GetParError(0);
	err2 = b_wig->GetParError(1);
	err3 = b_wig->GetParError(2);
	par12 = b_wig->GetParameter(3);
	par22 = b_wig->GetParameter(4);
	par32 = b_wig->GetParameter(5);
	err12 = b_wig->GetParError(3);
	err22 = b_wig->GetParError(4);
	err32 = b_wig->GetParError(5);
}

void fit_gaus_mult_2(TH1D* hist,int t, double lowb, double upb, double m0, double gamma0, double max, double &par1, double &par2, double &par3, double &err1, double &err2, double &err3, double m02, double gamma02, double max2, double &par12, double &par22, double &par32, double &err12, double &err22, double &err32 ){
	int t1 = 0;
	fit_gaus_2(hist, lowb, upb, m0, gamma0, max, par1, par2, par3, err1, err2, err3, m02, gamma02, max2, par12, par22, par32, err12, err22, err32);
	if(t <= 0){
		t = 1;
	}
	for(int i = 0; i< t; i++){
		fit_gaus_2(hist, lowb, upb, par1, par2, par3, par1, par2, par3, err1, err2, err3, par12, par22, par32, par12, par22, par32, err12, err22, err32);
	}
}

/*
void fit_MM(){
	fit_b_wig(MM_hist[0][0],0.8,1.0,p_center,p_sig,100.0,parameters[0],parameters[1],parameters[2],parameters[3],parameters[4],parameters[5]);
    cout<<"Proton Mass^2: " <<parameters[0] <<" error: " <<parameters[3];
    cout<<endl <<"Proton Gamma: " <<parameters[1] <<" error: " <<parameters[4];
    fit_b_wig(MM_hist[1][0],0.02,0.05,pip_center,pip_sig,100.0,parameters[0],parameters[1],parameters[2],parameters[3],parameters[4],parameters[5]);
    cout<<"Pi+ Mass^2: " <<parameters[0] <<" error: " <<parameters[3];
    cout<<endl <<"Pi+ Gamma: " <<parameters[1] <<" error: " <<parameters[4];
    fit_b_wig(MM_hist[2][0],-0.02,0.05,pip_center,pip_sig,100.0,parameters[0],parameters[1],parameters[2],parameters[3],parameters[4],parameters[5]);
    cout<<"Pi- Mass^2: " <<parameters[0] <<" error: " <<parameters[3];
    cout<<endl <<"Pi- Gamma: " <<parameters[1] <<" error: " <<parameters[4];
    fit_b_wig(MM_hist[3][0],-0.01,0.005,pip_center,pip_sig,100.0,parameters[0],parameters[1],parameters[2],parameters[3],parameters[4],parameters[5]);
    cout<<"Zero Mass^2: " <<parameters[0] <<" error: " <<parameters[3];
    cout<<endl <<"Zero Gamma: " <<parameters[1] <<" error: " <<parameters[4];
}*/

#endif