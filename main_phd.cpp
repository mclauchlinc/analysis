#include "TROOT.h"      //Allow access to all root libraries 
#include <iostream>     //Allow in and out standard functions
#include "main_phd.h"   //Standard functions for top down analysis
//#include "TStopwatch.h" //Function to show how long this takes
#include "read_in_data.h" //Functions to create TChains
#include "constants.h"  //All the various constants that will be used throughout the analysis
#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TH2.h"
#include "TH1.h"
#include "TMath.h"
#include "TString.h"
#include <stdio.h>
#include "electron_ec.h" // electron ec and sf cut functions
#include "delta_t_id.h" //The library for delta_t functions and delta_t id functions
#include "fiducial.h"   //Functions to do fiducial cuts 
#include "eid.h"    //All functions used for electron identification 
//#include "hid.h"    //All function used for hadron identification. This contains other libraries as well
#include "physics.h"
#include <map> 

using namespace std;
int main(){
    //Start Stopwatch to see how long it will take
    //TStopwatch *Watch = new TStopwatch;
   // Watch->Start();
    
    //Determine What will be loaded in
    char use_e16 = 'n';
    char use_e1f = 'n';
    char mac = 'n';
    char office = 'n';
    char farm = 'n';
    cout<< "Will you load in e16? (y or n): ";
    cin >> use_e16;
    /*cout<< "Will you load in e1f? (y or n): ";
    cin >> use_e1f;*/
    cout<< "Is this on your mac? (y or n): "; //Need to specify where this is being done because the data will be located in different places on each comp
    cin >> mac;
    if(mac == 'n')
    {
        cout<< "Is this on your office computer? (y or n): ";
        cin >> office;
        if(office == 'n')
        {
          cout << "Are you working on the farm? (y or n): ";
          cin >> farm;
           if( farm == 'y')
           {
            cout<< "What are you doing then? You don't know how to work on the farm yet" <<std::endl;
           } 
           if( farm == 'n')
           {
            cout<< "So you're just working nowhere...?" <<std::endl;
           }
        }
    } 

    //Load in Files
    cout << "Loading Files: ";
    TChain data("h10");

    if(mac == 'y') 
    {
        if(use_e16 == 'y')
        {
            int e16_num = -1; 
            cout << "How many files would you like to add? (if all say -1): "; //Can load in any number of files up to 
            cin >> e16_num;
            loadChain(&data,"/home/mclauchlinc/Desktop/e16/nick.txt",e16_num);
            //data.AddFile("/Users/cmc/Desktop/arjun.root");
        }
    }

    if(office == 'y')
    {
        if(use_e16 == 'y')
        {
            int e16_num = -1;
            cout << "How many files would you like to add? (if all say -1): "; //Can load in any number of files up to 
            cin >> e16_num;
            loadChain(&data,"/home/mclauchlinc/Desktop/e16/nick.txt",e16_num);
        }
    }
    cout<< "Done" <<std::endl;

    //Create Output File(s?)
    string file_name; 
    cout << "Name your Output File (end in .root):  ";
    cin >> file_name;
    cout<< "Creating File: ";
    TFile *output = Name_File(file_name); //Using this function to name a file 
    cout << "Done" <<std::endl;

    //Choose analysis
    //electron ID
    int eid_level = 1;
    char eid_plots;
    char electron_fid_plots;
    //Fiducial 
    char fiducial_plots;
    char proton_fid_plots;
    char pip_fid_plots;
    char pim_fid_plots;
    //Delta T
    char delta_t_plots;
    char proton_delta_t_plots;
    char pip_delta_t_plots;
    char pim_delta_t_plots;
    //Sample Fraction
    char sf_plots;
    //Energy Fraction
    char ec_plots;
    //Missing Mass
    char mm_plots;
    char pip_mm_plots;
    char pim_mm_plots;
    char proton_mm_plots;
    //Electron 
    cout<< "How deep do you want to do an eid (1, 2, 3): "; 
    /*1 is charge, first particle,
    2 is stat and dc_stat added
    3 are fiducial cuts, ec cuts, sf cuts */ 
    cin >> eid_level;
    if(eid_level >= 1)
    {
        cout<< "Do you want to have W Q2 plots? (y or n): " ;
        cin >> eid_plots; 
    }
    if(eid_level == 3)
    {
        cout<< "Electron Energy Minimum plot? (y or n): ";
        cin >> ec_plots;
        cout<< "Electron Sampling Fraction plots? (y or n): ";
        cin >> sf_plots;
        cout<< "Electron Fiducial plots? (y or n): ";
        cin >> electron_fid_plots;
    }
    //Fiducial
    cout << "Do you want to plot things involving hadronic fiducial cuts? (y or n): ";
    cin >> fiducial_plots;
    if(fiducial_plots == 'y')
    {
        cout<< "Proton Fiducial plots? (y or n): ";
        cin >> proton_fid_plots;
        cout<< "PiP Fiducial plots? (y or n): ";
        cin >> pip_fid_plots;
        cout<< "Pim Fiducial plots? (y or n): ";
        cin >> pim_fid_plots;
    }
    //Delta T
    cout<< "Do you want to plot things involving delta_t? (y or n): ";
    cin >> delta_t_plots;
    if(delta_t_plots == 'y')
    {
        cout<< "Proton Delta t plots? (y or n): ";
        cin >> proton_delta_t_plots;
        cout<< "PiP Delta t plots? (y or n): ";
        cin >> pip_delta_t_plots;
        cout<< "Pim Delta t plots? (y or n): ";
        cin >> pim_delta_t_plots;
    }
    //Missing Mass
    cout<< "Will you be working with missing masses? (y or n): ";
    cin >> mm_plots;
    if(mm_plots =='y')
    {
        cout<< "Will you want proton missing mass plots? (y or n): ";
        cin >> proton_mm_plots;
        cout<< "Will you want pi+ missing mass plots? (y or n): ";
        cin >> pip_mm_plots;
        cout<< "Will you want pi- missing mass plots? (y or n): ";
        cin >> pim_mm_plots;
    }




    //Define Root Variables
    cout<< "Creating Root Variables: ";
    Int_t gpart; //The number of particles registered in a given event
    Char_t q[23]; //The charge of each given particle
    Float_t sc_t[23]; //The time taken for a particle to travel through as found by the sc
    Float_t sc_r[23]; //The distance taken by a particle through the detector as found by the sc
    UChar_t sc[23]; //The index used to navigate any sc banks
    Float_t p[23]; //The momentum of given particles calculated from the curavture through the dc
    Float_t cx[23]; //The Cosine projection of the particle's intitial trajectory in x-axis the lab frame
    Float_t cy[23]; //The Cosine projection of the particle's intitial trajectory in y-axis the lab frame
    Float_t cz[23]; //The Cosine projection of the particle's intitial trajectory in z-axis the lab frame
    Char_t stat[23]; //Shows how statistically sound the particular particle is 
    UChar_t dc_stat[20]; //Shows how statistically sound the particular event is using data from the dc
    Float_t vx[23]; //Vertex of interaction measured in cm in x-axis in lab frame
    Float_t vy[23]; //Vertex of interaction measured in cm in y-axis in lab frame
    Float_t vz[23]; //Vertex of interaction measured in cm in z-axis in lab frame
    UChar_t dc[23]; // The index used to navigate any dc banks
    UChar_t cc[23]; // The index used to navigate any sc banks
    UChar_t ec[23]; //The index used to navigate any ec banks
    Float_t etot[22]; //The total final energy of the particle deposited in the detector


    cout<< "Done" <<std::endl;


    //Define in Program Variables
    cout<< "Defining Program Variables: ";
    double W;
    double Q2;
    //Electron ID
    bool is_e = kFALSE;

    //Hadron ID
    bool is_h = kFALSE;
    //Proton ID
    bool is_p = kFALSE;

    //Pi+ ID
    bool is_pip = kFALSE;

    //Pi- ID
    bool is_pim = kFALSE;

    //Observables
    double delta_t; 
    double theta_lab;
    double phi_lab;
    double phi_c;
    double sf;

    //Event Selection




    cout<< "Done" <<std::endl;


    //Define Progress
    cout<< "Define Progress: ";
    int progress;

    cout<< "Done" <<std::endl;




    //Set up Branch Addresses
    cout<< "Setting Branch Addresses: ";
    data.SetBranchAddress("q",&q);
    data.SetBranchAddress("gpart",&gpart);
    data.SetBranchAddress("sc_t",&sc_t);
    data.SetBranchAddress("sc_r",&sc_r);
    data.SetBranchAddress("sc",&sc);
    data.SetBranchAddress("p",&p);
    data.SetBranchAddress("cx",&cx);
    data.SetBranchAddress("cy",&cy);
    data.SetBranchAddress("cz",&cz);
    data.SetBranchAddress("stat",&stat);
    data.SetBranchAddress("dc_stat",&dc_stat);
    data.SetBranchAddress("vx",&vx);
    data.SetBranchAddress("vy",&vy);
    data.SetBranchAddress("vz",&vz);
    data.SetBranchAddress("dc",&dc);
    data.SetBranchAddress("cc",&cc);
    data.SetBranchAddress("ec",&ec);
    data.SetBranchAddress("etot",&etot);
    cout<< "Done" <<std::endl;


    //Get The Number of Events
    int events = data.GetEntries();
    cout<< "The number of events loaded are: " <<events <<std::endl;


    map<string, TH2F*> two_plot;
    map<string, TH1F*> one_plot;
    //Creates map of pointers so the pointers exist outside of the loop as far as C++ is concerned


    //Create Plots
    cout<< "Creating Plots: " <<endl;
    //if(eid_level >=1)
    //{
        //if(eid_plots == 'y')
        //{
            //plots["plot1"] = new TH2F("WvQ2_Pre","W vs. Q2 pre_eid_cut",500,-0.01,3.99,500,-0.01,8.99);
            two_plot["plot1"] = new TH2F("WvQ2_Pre","W vs. Q2 pre_eid_cut",500,-0.01,3.99,500,-0.01,8.99);
            two_plot["plot2"] = new TH2F("WvQ2_Post","W vs. Q2 post_eid_cut",500,-0.01,3.99,500,-0.01,8.99);
            two_plot["plot3"] = new TH2F("WvQ2_Anti","W vs. Q2 anti_eid_cut",500,-0.01,3.99,500,-0.01,8.99);
            cout<< "W Q2 plots made" <<endl;
        //}
        //if(eid_level ==3 && sf_plots == 'y')
        //{
            two_plot["sf1"] = new TH2F("sf_pre","Sample Fraction Pre Cut",100,0.0,6.0,100,0.0,1.0);
            two_plot["sf2"] = new TH2F("sf_cut","Sample Fraction Post Cut",100,0.0,6.0,100,0.0,1.0);
            two_plot["sf3"] = new TH2F("sf_anti","Sample Fraction Anit Cut",100,0.0,6.0,100,0.0,1.0);
            two_plot["sf4"] = new TH2F("sf_all","Sample Fraction All Cuts",100,0.0,6.0,100,0.0,1.0);
            cout<< "Sampling Fraction plots made" <<endl;
       // }
        //if(eid_level == 3 && e)
        
   // }
    //if(fiducial_plots = 'y')
   // {
        //if(eid_level ==3 && electron_fid_plots == 'y')
       // {
            two_plot["e_fid1"] = new TH2F("e_fid1_pre","Sector 1 Pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid2"] = new TH2F("e_fid2_pre","Sector 2 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid3"] = new TH2F("e_fid3_pre","Sector 3 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid4"] = new TH2F("e_fid4_pre","Sector 4 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid5"] = new TH2F("e_fid5_pre","Sector 5 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid6"] = new TH2F("e_fid6_pre","Sector 6 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid7"] = new TH2F("e_fid1_post","Sector 1 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid8"] = new TH2F("e_fid2_post","Sector 2 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid9"] = new TH2F("e_fid3_post","Sector 3 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid10"] = new TH2F("e_fid4_post","Sector 4 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid11"] = new TH2F("e_fid5_post","Sector 5 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid12"] = new TH2F("e_fid6_post","Sector 6 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid13"] = new TH2F("e_fid1_anti","Sector 1 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid14"] = new TH2F("e_fid2_anti","Sector 2 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid15"] = new TH2F("e_fid3_anti","Sector 3 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid16"] = new TH2F("e_fid4_anti","Sector 4 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid17"] = new TH2F("e_fid5_anti","Sector 5 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid18"] = new TH2F("e_fid6_anti","Sector 6 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid19"] = new TH2F("e_fid1_all","Sector 1 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid20"] = new TH2F("e_fid2_all","Sector 2 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid21"] = new TH2F("e_fid3_all","Sector 3 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid22"] = new TH2F("e_fid4_all","Sector 4 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid23"] = new TH2F("e_fid5_all","Sector 5 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["e_fid24"] = new TH2F("e_fid6_all","Sector 6 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            cout<< "Electron Fiducial plots made" <<endl;
        //}
        if(proton_fid_plots == 'y')
        { 
            two_plot["p_fid1"] = new TH2F("p_fid1_pre","Sector 1 Pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid2"] = new TH2F("p_fid2_pre","Sector 2 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid3"] = new TH2F("p_fid3_pre","Sector 3 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid4"] = new TH2F("p_fid4_pre","Sector 4 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid5"] = new TH2F("p_fid5_pre","Sector 5 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid6"] = new TH2F("p_fid6_pre","Sector 6 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid7"] = new TH2F("p_fid1_post","Sector 1 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid8"] = new TH2F("p_fid2_post","Sector 2 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid9"] = new TH2F("p_fid3_post","Sector 3 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid10"] = new TH2F("p_fid4_post","Sector 4 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid11"] = new TH2F("p_fid5_post","Sector 5 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid12"] = new TH2F("p_fid6_post","Sector 6 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid13"] = new TH2F("p_fid1_anti","Sector 1 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid14"] = new TH2F("p_fid2_anti","Sector 2 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid15"] = new TH2F("p_fid3_anti","Sector 3 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid16"] = new TH2F("p_fid4_anti","Sector 4 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid17"] = new TH2F("p_fid5_anti","Sector 5 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid18"] = new TH2F("p_fid6_anti","Sector 6 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid19"] = new TH2F("p_fid1_all","Sector 1 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid20"] = new TH2F("p_fid2_all","Sector 2 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid21"] = new TH2F("p_fid3_all","Sector 3 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid22"] = new TH2F("p_fid4_all","Sector 4 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid23"] = new TH2F("p_fid5_all","Sector 5 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["p_fid24"] = new TH2F("p_fid6_all","Sector 6 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            cout<< "Proton Fiducial plots made" <<endl;
        }
        if(pip_fid_plots == 'y')
        {
            two_plot["pip_fid1"] = new TH2F("pip_fid1_pre","Sector 1 Pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid2"] = new TH2F("pip_fid2_pre","Sector 2 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid3"] = new TH2F("pip_fid3_pre","Sector 3 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid4"] = new TH2F("pip_fid4_pre","Sector 4 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid5"] = new TH2F("pip_fid5_pre","Sector 5 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid6"] = new TH2F("pip_fid6_pre","Sector 6 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid7"] = new TH2F("pip_fid1_post","Sector 1 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid8"] = new TH2F("pip_fid2_post","Sector 2 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid9"] = new TH2F("pip_fid3_post","Sector 3 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid10"] = new TH2F("pip_fid4_post","Sector 4 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid11"] = new TH2F("pip_fid5_post","Sector 5 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid12"] = new TH2F("pip_fid6_post","Sector 6 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid13"] = new TH2F("pip_fid1_anti","Sector 1 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid14"] = new TH2F("pip_fid2_anti","Sector 2 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid15"] = new TH2F("pip_fid3_anti","Sector 3 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid16"] = new TH2F("pip_fid4_anti","Sector 4 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid17"] = new TH2F("pip_fid5_anti","Sector 5 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid18"] = new TH2F("pip_fid6_anti","Sector 6 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid19"] = new TH2F("pip_fid1_all","Sector 1 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid20"] = new TH2F("pip_fid2_all","Sector 2 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid21"] = new TH2F("pip_fid3_all","Sector 3 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid22"] = new TH2F("pip_fid4_all","Sector 4 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid23"] = new TH2F("pip_fid5_all","Sector 5 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pip_fid24"] = new TH2F("pip_fid6_all","Sector 6 all cuts", 200,-30.0,30.0,200,0.0,180.0);
            cout<< "Pi+ Fiducial plots made" <<endl;
        }
        if(pim_fid_plots == 'y')
        {
            two_plot["pim_fid1"] = new TH2F("pim_fid1_pre","Sector 1 Pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid2"] = new TH2F("pim_fid2_pre","Sector 2 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid3"] = new TH2F("pim_fid3_pre","Sector 3 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid4"] = new TH2F("pim_fid4_pre","Sector 4 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid5"] = new TH2F("pim_fid5_pre","Sector 5 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid6"] = new TH2F("pim_fid6_pre","Sector 6 pre", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid7"] = new TH2F("pim_fid1_post","Sector 1 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid8"] = new TH2F("pim_fid2_post","Sector 2 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid9"] = new TH2F("pim_fid3_post","Sector 3 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid10"] = new TH2F("pim_fid4_post","Sector 4 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid11"] = new TH2F("pim_fid5_post","Sector 5 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid12"] = new TH2F("pim_fid6_post","Sector 6 post", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid13"] = new TH2F("pim_fid1_anti","Sector 1 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid14"] = new TH2F("pim_fid2_anti","Sector 2 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid15"] = new TH2F("pim_fid3_anti","Sector 3 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid16"] = new TH2F("pim_fid4_anti","Sector 4 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid17"] = new TH2F("pim_fid5_anti","Sector 5 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid18"] = new TH2F("pim_fid6_anti","Sector 6 anti-cut", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid19"] = new TH2F("pim_fid1_all","Sector 1 all cuts applied", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid20"] = new TH2F("pim_fid2_all","Sector 2 all cuts applied", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid21"] = new TH2F("pim_fid3_all","Sector 3 all cuts applied", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid22"] = new TH2F("pim_fid4_all","Sector 4 all cuts applied", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid23"] = new TH2F("pim_fid5_all","Sector 5 all cuts applied", 200,-30.0,30.0,200,0.0,180.0);
            two_plot["pim_fid24"] = new TH2F("pim_fid6_all","Sector 6 all cuts applied", 200,-30.0,30.0,200,0.0,180.0);
            cout<< "Pi- Fiducial plots made" <<endl;
        }
    //}
    if(delta_t_plots == 'y')
    {
        if(proton_delta_t_plots == 'y')
        {
            two_plot["p_delta_t1"] = new TH2F("delta_t_proton1","Delta_t Assume Proton Mass",300,0.0,7.0,200,-4.0,4.0);
            two_plot["p_delta_t2"] = new TH2F("delta_t_proton2","Delta_t Assume Proton Mass_cut",300,0.0,7.0,200,-4.0,4.0);
            two_plot["p_delta_t3"] = new TH2F("delta_t_proton3","Delta_t Assume Proton Mass_anticut",300,0.0,7.0,200,-4.0,4.0);
            cout<< "Proton Delta t plots made" <<endl;
        }
        if(pip_delta_t_plots == 'y')
        {
            two_plot["pip_delta_t1"] = new TH2F("delta_t_pip1","Delta_t Assume Pi+ Mass",300,0.0,7.0,200,-4.0,4.0);
            two_plot["pip_delta_t2"] = new TH2F("delta_t_pip2","Delta_t Assume Pi+ Mass_cut",300,0.0,7.0,200,-4.0,4.0);
            two_plot["pip_delta_t3"] = new TH2F("delta_t_pip3","Delta_t Assume Pi+ Mass_anticut",300,0.0,7.0,200,-4.0,4.0);
            cout<< "Pi+ Delta t plots made" <<endl;
        }
        if(pim_delta_t_plots == 'y')
        {
            two_plot["pim_delta_t1"] = new TH2F("delta_t_pim1","Delta_t Assume Pi- Mass",300,0.0,7.0,200,-4.0,4.0);
            two_plot["pim_delta_t2"] = new TH2F("delta_t_pim2","Delta_t Assume Pi- Mass_cut",300,0.0,7.0,200,-4.0,4.0);
            two_plot["pim_delta_t3"] = new TH2F("delta_t_pim3","Delta_t Assume Pi- Mass_anticut",300,0.0,7.0,200,-4.0,4.0);
            cout<< "Pi- Delta t plots made" <<endl;
        }

    }


    cout<< "Done" <<std::endl;


    
    //Begin The Loop
    cout<< "Begin Loop" <<std::endl;
    for( int i=0;i<events;i++)
    {
        data.GetEntry(i);
        progress = (int) 100.0*(((double)i+1.0)/(double)events);
        cout << progress <<"\r";
        //Avoid problems of gparts not being between 0 and 23
        if(gpart >=1 && gpart <= 23)
        {
            //W Q2
            //Note that the initial energy here depends on which run
            W = WP(energy_e16, p[0], cx[0], cy[0], cz[0]);
            Q2 = Qsquared(energy_e16, p[0], cx[0], cy[0], cz[0]);
            //cout<< "Beam energy is " <<energy_e16 <<endl; 
            //Get theta and phi for electron
            theta_lab = get_theta(cz[0]);
            phi_lab = get_phi(cx[0],cy[0]);
            phi_c = phi_center(cx[0],cy[0]);
            //Sampling Fraction
            sf = etot[0]/p[0]; 
            //Electron Identification
            is_e = eid(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], eid_level);
            if(eid_level >= 1 && eid_plots == 'y')
            {
                two_plot["plot1"]->Fill(W,Q2);
                if(is_e == kTRUE)//The Cut
                {
                    two_plot["plot2"]->Fill(W,Q2);
                }
                if(is_e ==kFALSE)//The anti cut
                {
                    two_plot["plot3"]->Fill(W,Q2);
                }
                //Will need to add stuff for level 2
                
                if( eid_level == 3) //ec, sf, and fiducial 
                {
                    //Electron Sampling Fraction Cuts
                    if(sf_plots == 'y')
                    {
                        //Pre
                        two_plot["sf1"]->Fill(p[0],sf);
                        //Post
                        if(sf_e(p[0],etot[0],cx[0],cy[0])==kTRUE)
                        {
                            two_plot["sf2"]->Fill(p[0],sf);
                        }
                        //Anti
                        if(sf_e(p[0],etot[0],cx[0],cy[0])==kFALSE)
                        {
                            two_plot["sf3"]->Fill(p[0],sf);
                        }
                        //All
                        if(is_e == kTRUE)
                        {
                            two_plot["sf4"]->Fill(p[0],sf);
                        }
                    }

                    //Electron Fiducial Cuts
                    if(electron_fid_plots == 'y')
                    {
                        //Pre Cut
                        if(get_sector(cx[0],cy[0]) == 1)
                        {
                            two_plot["e_fid1"]->Fill(phi_c, theta_lab);
                        }
                        if(get_sector(cx[0],cy[0]) == 2)
                        {
                            two_plot["e_fid2"]->Fill(phi_c, theta_lab);
                        }
                        if(get_sector(cx[0],cy[0]) == 3)
                        {
                            two_plot["e_fid3"]->Fill(phi_c, theta_lab);
                        }
                        if(get_sector(cx[0],cy[0]) == 4)
                        {
                            two_plot["e_fid4"]->Fill(phi_c, theta_lab);
                        }
                        if(get_sector(cx[0],cy[0]) == 5)
                        {
                            two_plot["e_fid5"]->Fill(phi_c, theta_lab);
                        }
                        if(get_sector(cx[0],cy[0]) == 6)
                        {
                            two_plot["e_fid6"]->Fill(phi_c, theta_lab);
                        }
                        // The Cut
                        if(is_e == kTRUE)
                        {
                            if(get_sector(cx[0],cy[0]) == 1)
                            {
                                two_plot["e_fid7"]->Fill(phi_c, theta_lab);
                            }
                            if(get_sector(cx[0],cy[0]) == 2)
                            {
                                two_plot["e_fid8"]->Fill(phi_c, theta_lab);
                            }
                            if(get_sector(cx[0],cy[0]) == 3)
                            {
                                two_plot["e_fid9"]->Fill(phi_c, theta_lab);
                            }
                            if(get_sector(cx[0],cy[0]) == 4)
                            {
                                two_plot["e_fid10"]->Fill(phi_c, theta_lab);
                            }
                            if(get_sector(cx[0],cy[0]) == 5)
                            {
                                two_plot["e_fid11"]->Fill(phi_c, theta_lab);
                            }
                            if(get_sector(cx[0],cy[0]) == 6)
                            {
                                two_plot["e_fid12"]->Fill(phi_c, theta_lab);
                            }
                        }
                        //The Anti Cut
                        if(is_e == kFALSE)
                        {
                            if(get_sector(cx[0],cy[0]) == 1)
                            {
                                two_plot["e_fid13"]->Fill(phi_c, theta_lab);
                            }
                            if(get_sector(cx[0],cy[0]) == 2)
                            {
                                two_plot["e_fid14"]->Fill(phi_c, theta_lab);
                            }
                            if(get_sector(cx[0],cy[0]) == 3)
                            {
                                two_plot["e_fid15"]->Fill(phi_c, theta_lab);
                            }
                            if(get_sector(cx[0],cy[0]) == 4)
                            {
                                two_plot["e_fid16"]->Fill(phi_c, theta_lab);
                            }
                            if(get_sector(cx[0],cy[0]) == 5)
                            {
                                two_plot["e_fid17"]->Fill(phi_c, theta_lab);
                            }
                            if(get_sector(cx[0],cy[0]) == 6)
                            {
                                two_plot["e_fid18"]->Fill(phi_c, theta_lab);
                            }
                        }
                    }
                }
            }
            /*
            //Begin the Event Loops
            if(is_e == kTRUE) //Only use events that have the first particle confirmed as an electron
            {
                for(int j=1;j<gpart;j++)//Loop through the particles
                {
                    scidx = sc_index(sc[j]); //Defining the sc index for things that use sc banks 
                    particle = particle_id();
                    theta_lab = get_theta(cz[j]);
                    //Fiducial Plots
                    if(fiducial_plots == "y")
                    {
                        if(proton_fid_plots == "y") //Proton Fiducial plots
                        {
                            //Precut
                            if(get_sector(cx[j],cy[j]) == 1)
                            {
                                //plots["p_fid1"]->Fill(phi_lab, theta_lab);
                                two_plot["p_fid1"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 2)
                            {
                                 two_plot["p_fid2"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 3)
                            {
                                two_plot["p_fid3"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 4)
                            {
                                two_plot["p_fid4"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 5)
                            {
                                two_plot["p_fid5"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 6)
                            {
                                two_plot["p_fid6"]->Fill(phi_lab, theta_lab);
                            }
       ***                     if(is_proton(   ) == kTRUE) //The Cut
                            {
                                if(get_sector(cx[j],cy[j]) == 1)
                                {
                                    two_plot["p_fid7"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 2)
                                {
                                    two_plot["p_fid8"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 3)
                                {
                                    two_plot["p_fid9"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 4)
                                {
                                    two_plot["p_fid10"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 5)
                                {
                                    two_plot["p_fid11"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 6)
                                {
                                    two_plot["p_fid12"]->Fill(phi_lab, theta_lab);
                                }
                            }
         ***                   if(is_proton(   ) == kFALSE) //The Anticut
                            {
                                if(get_sector(cx[j],cy[j]) == 1)
                                {
                                    two_plot["p_fid13"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 2)
                                {
                                    two_plot["p_fid14"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 3)
                                {
                                    two_plot["p_fid15"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 4)
                                {
                                    two_plot["p_fid16"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 5)
                                {
                                    two_plot["p_fid17"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 6)
                                {
                                    two_plot["p_fid18"]->Fill(phi_lab, theta_lab);
                                }
                            }
                        }
                        if(pip_fid_plots == "y") //Pi + Fiducial plots
                        {
                            //Precut
                            if(get_sector(cx[j],cy[j]) == 1)
                            {
                                two_plot["pip_fid1"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 2)
                            {
                                 two_plot["pip_fid2"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 3)
                            {
                                two_plot["pip_fid3"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 4)
                            {
                                two_plot["pip_fid4"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 5)
                            {
                                two_plot["pip_fid5"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 6)
                            {
                                two_plot["pip_fid6"]->Fill(phi_lab, theta_lab);
                            }
       ***                  if(is_pip(   ) == kTRUE) //The Cut
                            {
                                if(get_sector(cx[j],cy[j]) == 1)
                                {
                                    two_plot["pip_fid7"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 2)
                                {
                                    two_plot["pip_fid8"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 3)
                                {
                                    two_plot["pip_fid9"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 4)
                                {
                                    two_plot["pip_fid10"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 5)
                                {
                                    two_plot["pip_fid11"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 6)
                                {
                                    two_plot["pip_fid12"]->Fill(phi_lab, theta_lab);
                                }
                            }
         ***                if(is_pip(   ) == kFALSE) //The Anticut
                            {
                                if(get_sector(cx[j],cy[j]) == 1)
                                {
                                    two_plot["pip_fid13"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 2)
                                {
                                    two_plot["pip_fid14"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 3)
                                {
                                    two_plot["pip_fid15"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 4)
                                {
                                    two_plot["pip_fid16"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 5)
                                {
                                    two_plot["pip_fid17"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 6)
                                {
                                    two_plot["pip_fid18"]->Fill(phi_lab, theta_lab);
                                }
                            }
                        }
                        if(pim_fid_plots == "y") //Pi - Fiducial plots
                        {
                            //Precut
                            if(get_sector(cx[j],cy[j]) == 1)
                            {
                                two_plot["pim_fid1"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 2)
                            {
                                 two_plot["pim_fid2"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 3)
                            {
                                two_plot["pim_fid3"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 4)
                            {
                                two_plot["pim_fid4"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 5)
                            {
                                two_plot["pim_fid5"]->Fill(phi_lab, theta_lab);
                            }
                            if(get_sector(cx[j],cy[j]) == 6)
                            {
                                two_plot["pim_fid6"]->Fill(phi_lab, theta_lab);
                            }
       ***                  if(is_pim(   ) == kTRUE) //The Cut
                            {
                                if(get_sector(cx[j],cy[j]) == 1)
                                {
                                    two_plot["pim_fid7"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 2)
                                {
                                    two_plot["pim_fid8"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 3)
                                {
                                    two_plot["pim_fid9"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 4)
                                {
                                    two_plot["pim_fid10"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 5)
                                {
                                    two_plot["pim_fid11"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 6)
                                {
                                    two_plot["pim_fid12"]->Fill(phi_lab, theta_lab);
                                }
                            }
         ***                if(is_pim(   ) == kFALSE) //The Anticut
                            {
                                if(get_sector(cx[j],cy[j]) == 1)
                                {
                                    two_plot["pim_fid13"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 2)
                                {
                                    two_plot["pim_fid14"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 3)
                                {
                                    two_plot["pim_fid15"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 4)
                                {
                                    two_plot["pim_fid16"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 5)
                                {
                                    two_plot["pim_fid17"]->Fill(phi_lab, theta_lab);
                                }
                                if(get_sector(cx[j],cy[j]) == 6)
                                {
                                    two_plot["pim_fid18"]->Fill(phi_lab, theta_lab);
                                }
                            }
                        }
                    }
                    /*
                    //Delta T Plots
                    if(delta_t_plots == "y")
                    {
                        if(proton_delta_t_plots == "y")// Proton delta t plots
                        {
                            //Pre Cut
                            p_delta_t1->Fill(p[j],delta_t())
                            //Cut
                            //Anticut
                        }
                        if(pip_delta_t_plots == "y") // Pi+ Delta T Plots
                        {

                        }
                        if(pim_delta_t_plots == "y") //Pi - delta T plots
                        {

                        }
                    
                    }
                    
                }
            
            }
            */
        }
    }
    
    
    //Write to the file and close it
    output->Write();
    cout<<"written to file" <<std::endl;
    output->Close();
    cout<<"File Closed" <<std::endl;


    //Watch->Stop();
    //cout << "The program has taken " << Watch->RealTime() << "sec to complete" << std::endl;
    return 0;
}