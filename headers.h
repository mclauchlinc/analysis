#ifndef HEADERS_H
#define HEADERS_H

#include "TROOT.h"      //Allow access to all root libraries 
#include <iostream>     //Allow in and out standard functions
#include "TDirectory.h"	//Allows for use of Directories 
#include "main_phd.h"   //Standard functions for top down analysis
//#include "TStopwatch.h" //Function to show how long this takes
#include "TLorentzVector.h"	//Allows use of Lorentz 4-Vectors 
#include "read_in_data.h" //Functions to create TChains
#include "constants.h"  //All the various constants that will be used throughout the analysis
#include "TTree.h"	//Allows access to R00t Trees
#include "TFile.h"	//Allows reading and writing R00t files
#include "TChain.h"	//Allows creating chains and reading in multiple R00t Files
#include "TH2.h"	//2D histograms
#include "TH1.h"	//1D histograms
#include "TMath.h"	//Use of Math and the like
#include "TString.h"	//Use of strings
#include <stdio.h>	//Standard input outout. Allows for printed statements
#include "electron_ec.h" // electron ec and sf cut functions
#include "delta_t_id.h" //The library for delta_t functions and delta_t id functions
#include "fiducial.h"   //Functions to do fiducial cuts 
#include "eid.h"    //All functions used for electron identification 
//#include "hid.h"    //All function used for hadron identification. This contains other libraries as well
#include "physics.h"	//Fun physics functions that will be used. 
#include "variables.h" // Initialize all variables that will be used
#include "histograms.h"//Functions to make and write histograms 
//#include "cuts.h"
#include "CartesianGenerator.hh" //Allows loops over species, cut_status, and other things. finds the combinations thereof
#include "make_files.h"
#include "partitions.h" //Functions that fill the plots relevant to specific things: eid, hid, etc. 
#include "debugger.h"
#include "event_selection.h"//slecting events 

#endif