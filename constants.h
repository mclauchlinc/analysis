#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "TMath.h"
#include "four_vector.h"
#include "headers.h"

const double c_special = 29.9792458; //speed of light in cm/ns
const double c_convert = 10000000; //Convert c_special to m/s

//Beam energies in GeV
const double energy_e16 = 5.759;
//3_14 was 5.754, but led to bad results: updated to 5.759 after reading Paremuzyan's thesis 
//Check 4.794 GeV for e16
const double energy_e1f = 5.499;

//Masses of relevant particles
const	double me = 0.0005109989; //mass of electron in GeV
const	double mp = 0.93828;	//Mass of proton in GeV
const	double mpi = 0.1395;	//Mass of pion in GeV

//Initial Four Vectors

TLorentzVector k_mu_e16 = Make_4Vector(energy_e16,0.0,0.0,1.0,me);
TLorentzVector k_mu_e1f = Make_4Vector(energy_e1f,0.0,0.0,1.0,me);
TLorentzVector p_mu = Make_4Vector(0.0,0.0,0.0,0.0,mp);

//Particle ID Numbers
//anti particles are negative
const 	int PROTON = 2212;
const	int ELECTRON = 11;
const	int PION = 211;
const	int PION_0 = 111;

// Beam spot from Arjun's Fortran vertex_e1f.f
const double x_beam = 0.090;
const double y_beam = -0.345;

//These vertext cut constants are from Arjun's cuts.h in elast_lite
const Float_t VX_ZMAX = -22.25; //Empirically-determined target upstream edge z-position in cm, for E1F
const Float_t VX_ZMIN = -27.75; //Empirically-determined target downstream edge z-position in cm, for E1F
const Float_t VX_DZ = 1.6; //Vertex resolution in cm, for E1F

//Fiducial cut Parameters. electron's have an e and hadrons have an h
//These were gotten from Arjun's cut_fid_e1f.f
const double c1e = 12.0;
const double c2e = 18.5;
const double c3e = 0.25;
const double c4e = 15.0;
const double factor_e = 0.416667;
const double p_shift_e = 0.14;
const double a0xh[6] = {24.0,24.0,23.0,23.5,24.5,24.5};
const double a0mh[6] = {25.0,26.0,26.0,25.5,27.0,26.0};
const double a1xh[6] = {0.22,0.23,0.20,0.20,0.22,0.22};
const double a1mh[6] = {0.22,0.22,0.22,0.22,0.16,0.16};
const double a2xh[6] = {8.0,8.0,8.0,8.0,8.0,8.0};
const double a2mh[6] = {8.0,8.0,8.0,8.0,8.0,8.0};
const double a3xh[6] = {1.0,1.0,1.0,1.0,1.0,1.0};
const double a3mh[6] = {1.0,1.0,1.0,1.0,1.0,1.0};

//Missing Mass cut parameters
/*
//None determined yet (just place holders for now)
const double pim_center = 0.1395;
const double pim_sig = 0.02; 
const double pip_center = 0.1395;
const double pip_sig = 0.02;
const double p_center = 0.93828;
const double p_sig = 0.02;
*/
//Arjun's ranges for each Missing mass cut
//proton min: 0.652  max: 0.912
//pion min: 0.050  max: 0.270
//Convert to the formalism I'll use, but will adjust later
const double pim_center = 0.164369;//These are all determined through fitting of b_wig fitting.h
const double pim_sig = 0.0862474;
const double pip_center = 0.157301;
const double pip_sig = 0.0752388;
const double p_center = 0.946847;
const double p_sig = 0.0420984;
const double pim_center2 = 0.022;
const double pim_sig2 = 0.022;
const double pip_center2 = 0.022;
const double pip_sig2 = 0.022;
const double p_center2 = 0.89;
const double p_sig2 = 0.05;


//For Project
const double MM_n_center = 0.944;
const double MM_n_sigma = 0.07;
const double MM_piz_center = 0.140;
const double MM_piz_sigma = 0.1;
const double MM_D_center = 1.232;
const double MM_D_sigma = 0.08;

//My Own MM cut parameters
const double MM_zero_center = 0.0;
const double MM_zero_sigma = 0.02;
const double MM_zero_center2 = 0.0;
const double MM_zero_sigma2 = 0.004;

//Delta T cut parameters
/*
//Currently cannot find Arjun's so they are just guesses of flat numbers. Will adjust when I can 8/4/16
const double DT_PROTON_L = -0.6;
const double DT_PROTON_H = 0.6;
const double DT_PI_L = -0.6;
const double DT_PI_H = 0.6;
*/
//Arjun's cut parameters: 3rd order polynomial
const double DTL[4] = {-0.778903, 0.027350, 0.047947, -0.009641};
const double DTH[4] = {0.758057, -0.147383, 0.034343, -0.002367};

//attempt to remove slice of electrons from Pi- delta t
const double dt_e_sig = 0.05;
const double dt_e_A = 20.0;
const double dt_e_a = 8.55;
const double dt_e_b = 0.31;


//Kinematic Cuts
// Margin of error allowed for kinematic fitting 
const double px_dev = 0.02;
const double py_dev = 0.02;
const double pz_dev = 0.02;

//Electron EC cut parameters
//currently from Arjun and not verified
//High and Low functions are third order polynomials separtated by sector
const Float_t p_min_e16 = 0.70; //in GeV
const Float_t ec_min_e16 = 0.06; //in GeV 
const double sf_high_e16[6][4] = {
		{0.380401, -0.019463, 0.004609, -0.000359},
		{0.428533, -0.047554, 0.016350, -0.001938},
		{0.420563, -0.064622, 0.025420, -0.003105},
		{0.411866, -0.062074, 0.022444, -0.002734},
		{0.383041, -0.020678, 0.007576, -0.000897},
		{0.394516, -0.023219, 0.010402, -0.001431}
		};
const double sf_low_e16[6][4] = {
		{0.141603, 0.063643, -0.012677, 0.000918},
		{0.149598, 0.053507, -0.007504, 0.000323},
		{0.172657, 0.038093, -0.002066, -0.000355},
		{0.149623, 0.060981, -0.012957, 0.001054},
		{0.099589, 0.102036, -0.028452, 0.002751},
		{0.117104, 0.097765, -0.023769, 0.002149}
		};
const Float_t p_min_e1f = 0.64;
const Float_t ec_min_e1f_exp[6] = {0.058,0.064,0.060,0.056,0.058,0.056}; 
const Float_t ec_min_e1f_sim[6] = {0.063,0.063,0.063,0.063,0.063,0.063}; 

//Plot Formation Constants
//W Q2
const int WQxres = 300;
const int WQyres = 300;
const double WQxmin = -0.01;
const double WQymin = -0.01;
const double WQxmax = 3.99;
const double WQymax = 8.99;
//For Topology Selection
const int WQ2xres = 20;
const int WQ2yres = 20;

//Electron Sampling Fraction
const int SFxres = 100;
const int SFyres = 100;
const double SFxmin = 0.0;
const double SFymin = 0.0;
const double SFxmax = 6.0;
const double SFymax = 1.0;
//Minimum Electron Energy
const int MEExres = 100;
const int MEEyres = 100;
const double MEExmin = 0.0;
const double MEEymin = 0.0;
const double MEExmax = 6.0;
const double MEEymax = 1.0;
//Fiducial Cuts
const int FIDxres = 200;
const int FIDyres = 200;
const double FIDxmin = -30.0;
const double FIDymin = 0.0;
const double FIDxmax = 30.0;
const double FIDymax = 180.0;
//Delta_t
const int DTxres = 300;
const int DTyres = 200;
const double DTxmin = 0.0;
const double DTymin = -4.0;
const double DTxmax = 7.0;
const double DTymax = 4.0;
//Missing Mass
const int MMxres = 1500;
const double MMxmin = -0.2;
const double MMxmax = 3.0;
//Alpha
const int alphaxres = 100;
const double alphaxmin = 0.0;
const double alphaxmax = 3.2;
//Binning
const double Wmin = 1;
const double Wres = 0.5;
const double Wmax = 3;
const double Q2min = 1.5;
const double Q2max = 5.0;
const double Q2res = 0.5;

//Project
const int p_MMxres = 400;
const double p_MMxmin = -0.2;
const double p_MMxmax = 8.0;

//binning
const Wbin_res = 0.2;//The width of a W bin
const Wbin_start = 1.0;//The starting of W bins



const char * species[] = {"e","p","pip","pim","all"};
const char * eid_cut[] = {"pre","eid1","eid2","eid3","eid4","sanity","efid","sf","bank"};
const char * norm_cut[] = {"pre", "cut", "anti", "pid", "bank"};
const char * char_cut[] = {"pre","cut","anti","combo","pid","bank"};
const char * charge[] = {"pos","neg"};
const char * arguments[] = {"program", "input file","number of files", "output file"};//4
const char* local[] = {"the farm", "the desktop", "the mac"};//3
const char* topologies[] = {"proton_miss", "Pip_miss", "Pim_miss","All","Combined"};//5 //Used for differentiation between the various topolgies
const char* cross_top[] = {"p_pip", "p_pim", "p_zero", "pip_pim", "pip_zero", "pim_zero"};//For the cross plots of missing mass
const char* alpha_stuff[] = {"p_pip","p_pim", "pip_pim"};
const char* mvar[] = {"switch","2pi"};

//project
const char* p_deltas[] = {"Dpp","Dp","D0"};
const char* p_top[] = {"pim_meas","pim_miss","p_meas","pip_meas","pip_meas","pim_miss"};
const char* p_cuts[] = {"PRE","par_pre","par_cut","par_anti","D_pre","D_cut","D_anti"};
/*
Types of Cuts
	Electron ID
		0 Sanity
		1 Fiducial
		2 Sampling Fraction
		3 Min Energy
		4 Vertex
		5 CC
		6 Built in Particle ID
	Hadron ID
		7 Santiy
		8 Fiducial
		9 Delta T
		10 Built in Particle ID
	Event Selection
		11 Full Topology
		12 MM Proton
		13 MM Pip
		14 MM Pim
*/
//const std::string cut_type[] = {"e_san", "e_fid", "e_sf_", "e_min", "e_vtx", "e_cc_", "e_PID", "h_san", "h_fid", "h_d_t", "h_PID", "fulltp", "mm_pr", "mmpip", "mmpim"};

#endif /* CONSTANTS_H */