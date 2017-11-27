#ifndef FITTING_H
#define FITTING_H


#include "TH1.h"
#include "TF1.h"
#include "headers.h"
#include "TMath.h"



void fit_b_wig(TH1D* hist, double lowb, double upb, double m0, double gamma0, double max, double &par1, double &par2, double &par3, double &err1, double &err2, double &err3){
	double* pointer[4];
	TF1 *b_wig = new TF1("b_wig","[2]*(2*sqrt(2)*[0]*[1]*sqrt([0]*[0]*([0]*[0]+[1]*[1])))/(TMath::Pi()*((x-[0]*[0])*(x-[0]*[0])+[0]*[0]*[1]*[1])*sqrt([0]*[0]+sqrt([0]*[0]*([0]*[0]+[1]*[1]))))",lowb,upb);
	b_wig->SetParameters(0,m0);
	b_wig->SetParameters(1,gamma0);
	b_wig->SetParameters(2,max);
	hist->Fit(b_wig);
	par1 = b_wig->GetParameter(0);
	par2 = b_wig->GetParameter(1);
	par3 = b_wig->GetParameter(2);
	err1 = b_wig->GetParError(0);
	err2 = b_wig->GetParError(1);
	err3 = b_wig->GetParError(2);
}

void fit_gaus(TH1D* hist, double lowb, double upb, double m0, double gamma0, double max, double &par1, double &par2, double &par3, double &err1, double &err2, double &err3){
	double* pointer[4];
	TF1 *b_wig = new TF1("b_wig","[2]*TMath::Exp(-(x-[0])*(x-[0])/(2*[1]*[1]))",lowb,upb);
	b_wig->SetParameters(0,m0);
	b_wig->SetParameters(1,gamma0);
	b_wig->SetParameters(2,max);
	hist->Fit(b_wig);
	par1 = b_wig->GetParameter(0);
	par2 = b_wig->GetParameter(1);
	par3 = b_wig->GetParameter(2);
	err1 = b_wig->GetParError(0);
	err2 = b_wig->GetParError(1);
	err3 = b_wig->GetParError(2);
}

#endif