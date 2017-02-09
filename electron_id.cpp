#include "TROOT.h"      //Allow access to all root libraries 
#include <iostream> 	//
#include "read_in_data.h" //Functions to create TChains
#include "constants.h"  //All the various constants that will be used throughout the analysis
#include "TTree.h"	//
#include "TFile.h"	//
#include "TChain.h"	//
#include "TH2.h"	//
#include "TH1.h"	//
#include "TMath.h"	//
#include "TString.h"	//
#include <stdio.h>	//
#include "electron_ec.h"	//
#include "fiducial.h"   //Functions to do fiducial cuts 
#include "eid.h" 
#include "physics.h"

using namespace std;
int main(){

	 //Load in Files
    cout << "Loading Files: ";
    TChain::TChain data("h10");
    e16_num = -1;
    loadChain(&data,"e16_data.txt",e16_num);