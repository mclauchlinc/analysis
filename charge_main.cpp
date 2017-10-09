//#include "headers.h" //Contains all the header files I need
//#include "Hist_Charge.h"

#include <iostream>     //Allow in and out standard functions
#include "TROOT.h"      //Allow access to all root libraries 
#include "TTree.h"  //Allows access to R00t Trees
#include "TFile.h"  //Allows reading and writing R00t files
#include "TChain.h" //Allows creating chains and reading in multiple R00t Files
#include "TH2.h"    //2D histograms
#include "TH1.h"    //1D histograms
#include "TMath.h"  //Use of Math and the like
#include "TString.h"    //Use of strings
#include "CartesianGenerator.hh" 
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
//#include "read_in_data.h"



const double c_special = 29.9792458; //speed of light in cm/ns
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
const   int PROTON = 2212;
const   int ELECTRON = 11;
const   int PION = 211;
const   int PION_0 = 111;
//Masses of relevant particles
const   double me = 0.0005109989; //mass of electron in GeV
const   double mp = 0.93828;    //Mass of proton in GeV
const   double mpi = 0.1395;    //Mass of pion in GeV
const double DTL[4] = {-0.778903, 0.027350, 0.047947, -0.009641};
const double DTH[4] = {0.758057, -0.147383, 0.034343, -0.002367};
const char * species[] = {"e","p","pip","pim","all"};
const char * eid_cut[] = {"pre","eid1","eid2","eid3","eid4","sanity","efid","sf","bank"};
const char * norm_cut[] = {"pre", "cut", "anti", "pid", "bank"};
const char * char_cut[] = {"pre","cut","anti","combo","pid","bank"};
const char * charge[] = {"pos","neg"};
//Delta_t
const int DTxres = 300;
const int DTyres = 200;
const double DTxmin = 0.0;
const double DTymin = -4.0;
const double DTxmax = 7.0;
const double DTymax = 4.0;

std::vector<std::string> read_file_list(std::string path) //Choose a vector of strings. Vector because adding things onto the end works fine. Also don't know how to use a list
{
    std::ifstream infile(path.c_str()); // in file stream
    std::vector<std::string> result;
    std::string line;

    while(getline(infile,line)) { //getline sees if there is a line available
        result.push_back(line);//Gets the current line
    }
    return result;
}


//Create a data chain for a given data set
//Optional number of files to load
void loadChain(TChain* c, std::string file, int max=-1)
{
    std::vector<std::string> filelist = read_file_list(file);//read_file_list(file); //creates a vector of file names
    //If not specified will take in all the files in the text file
    int test = filelist.size();
    if(max > test)
    {
        std::cout<< "You tried to add too many files. This has been corrected" <<std::endl <<"Remember that you may only add " <<test <<" files" <<std::endl;
    }
    if(max == -1 || max > test) {//In case one tries to add too many files
        max = filelist.size();
    }
    //If specified then it will take in that number of files 
    for(int i = 0; i < max; i++) {
        c->AddFile(filelist[i].c_str());
    }
}

double vert_e(double d, double t)
{
    return t -( d/c_special);
}

double vert_p(double p, double d, double t, double m)
{
    return t-((d/c_special)*sqrt(1.0 + m*m/(p*p)));//is there supposed to be a + here? yeah 9/25
}

double delta_t( double p, double p0, double d, double d0, double t, double t0, double m )
{
    double vertex_e = vert_e(d0, t0);
    double vertex_p = vert_p(p, d, t, m);
    return vertex_e - vertex_p;
}

TH2D* fid_hist_q[6][5][2]; //Sector, cut, pos/neg
TH2D* dt_hist_q[5][2];
char  htitle[100]; //The name on the graph itself (can have spaces)
char  hname[100]; //The name shown in the TBrowser (should have no spaces)
/*
void MakeHist_fidp_q(){
  std::vector<long> space_dims(3);
  space_dims[0] =6;//sectors
  space_dims[1] = 6; //no cut, cut, anti, cross, pid, bank
  space_dims[2] = 2; //positive, negative

  CartesianGenerator cart(space_dims);

  while(cart.GetNextCombination()){
    sprintf(hname,"p_fid_sec%d_%s_%s",cart[0]+1,char_cut[cart[1]],charge[cart[2]]);
    fid_hist_q[cart[0]][cart[1]][cart[2]] = new TH2D( hname, hname, FIDxres, FIDxmin, FIDxmax, FIDyres, FIDymin, FIDymax);
  }
}
*/
bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

TFile *Name_File(std::string a_file_name)
{
    std::string file_name = "$name.root";
    replace(file_name, "$name", a_file_name);
    return new TFile(file_name.c_str(),"RECREATE");
}

void MakeHist_dtp_q(){
  std::vector<long> space_dims(2);
  space_dims[0] = 6;//pre, cut, anti, pid, bank
  space_dims[1] = 2; //Pos/neg

  CartesianGenerator cart(space_dims);
  while(cart.GetNextCombination()){
    sprintf(hname,"p_delta_t_%s_%s",char_cut[cart[0]],charge[cart[1]]);
    dt_hist_q[cart[0]][cart[1]] = new TH2D( hname, hname, DTxres, DTxmin, DTxmax, DTyres, DTymin, DTymax);
  }
}

//Fill_dt(0,0,p, p0, sc_r, sc_r0, sc_t, sc_t0);
void Fill_dt_q(int q, int cut, int sc, double p, double p0, double d, double d0, double t, double t0){
  /*
  for species: {p,pip,pim} -> {0,1,2}
  cut: {pre, cut, anti, combo, pid, bank} -> {0,1,2,3,4,5}
  */double mass = mp;
    int ch ;
  if(sc != 0){
    double dt = delta_t(p, p0, d, d0, t, t0, mass );
    if( q == 1){
        ch = 0;
        dt_hist_q[cut][ch] -> Fill(p,dt);
    }
    if( q == -1){
        ch = 1;
        dt_hist_q[cut][ch] -> Fill(p,dt);
    }    
  }
}

//Proton Formulae from Arjun
double dt_p_low(double p){
    return DTL[0]+DTL[1]*p+DTL[2]*p*p+DTL[3]*p*p*p;
}

double dt_p_high(double p){
    return DTH[0]+DTH[1]*p+DTH[2]*p*p+DTH[3]*p*p*p;
}

bool delta_t_proton(double p0, double p, double d0, double d, double t0, double t) //Note: d and t need the sc_index 
{
    bool isproton = kFALSE;
    double dt = delta_t( p, p0, d, d0, t, t0, mp );
    if(dt>dt_p_low(p) && dt<dt_p_high(p) )
    {
        isproton = kTRUE;
    }
    return isproton;
}

/*
void Fill_fid_q(int q, int level, double cx, double cy, double cz)
{
    double phi = phi_center(cx, cy); //fiducial.h
    double theta = get_theta(cz);  //fiducial.h
    int sec = get_sector(cx, cy);  //fiducial.h
  int sidx = sec-1;
    int duck; 
    //Level {0,1,2,3} -> {no cut, cut, anti-cut, all cuts}
  //Type {0,1,2,3} -> {e, p, pip, pim}
  if(q == 1){
   // std::cout<<"PROTON FID" ;
    duck = 0;

    fid_hist_q[sidx][level][duck]->Fill(phi, theta);
  }
  if(q == -1){
  //  std::cout<<"PION FID" ;
    duck = 1;

    fid_hist_q[sidx][level][duck]->Fill(phi, theta);
  }
}
*/


using namespace std;
int main(int argc, char** argv)
{
	cout<< "You have " << argc << " arguments: " <<endl;
	for( int i = 0; i < argc; i++)
	{
		cout << argv[i] <<endl;
	}

	//Set input and output files
	std::string comp = argv[1];
    //int file_num = argv[2];
	char* output_name = argv[2];

    int file_num = -1;

	TFile *output = Name_File(output_name); //read_in_data.h
    cout<<"1" <<endl;

	//Load in Files
    cout << "Loading Files: ";
    TChain data("h10"); //Create a TChain

    int work = 0;
    if(comp == "one"){
   	    loadChain(&data, "nick_convert_e16.txt", file_num); //Located in main_phd.h
        work ++;
    }
    if(comp == "two"){
        loadChain(&data, "mac_set_1.txt",file_num);
        work ++;
    }
    if(comp == "three"){
        loadChain(&data,"question_data.txt",file_num);
        work ++;
    }
    if(comp == "four"){
        loadChain(&data,"old_e1f_data.txt",16);
        work ++;
    }
    if(comp == "five"){
        loadChain(&data, "e1d_files.txt",file_num);
        work ++;
    }
    if(work =0){
        cout<< "You are not using your loadChain function" <<endl;
    }
    
    cout<< "Done" <<std::endl;  //Just to let me know
    cout<<"2" <<endl;

    //Number of events check
    int events;
    events = data.GetEntries();
    cout <<"There are "<< events <<" events loaded" <<endl;

    
     Int_t gpart; //The number of particles registered in a given event
    Char_t q_b[100]; //The charge of each given particle
    Float_t sc_t_b[100]; //The time taken for a particle to travel through as found by the sc
    Float_t sc_r_b[100]; //The distance taken by a particle through the detector as found by the sc
    Int_t sc_b[100]; //The index used to navigate any sc banks
    Float_t p_b[100]; //The momentum of given particles calculated from the curavture through the dc
    Float_t cx_b[100]; //The Cosine projection of the particle's intitial trajectory in x-axis the lab frame
    Float_t cy_b[100]; //The Cosine projection of the particle's intitial trajectory in y-axis the lab frame
    Float_t cz_b[100]; //The Cosine projection of the particle's intitial trajectory in z-axis the lab frame
    Char_t stat_b[100]; //Shows how statistically sound the particular particle is 
    Int_t dc_stat_b[100]; //Shows how statistically sound the particular event is using data from the dc
    Float_t vx_b[100]; //Vertex of interaction measured in cm in x-axis in lab frame
    Float_t vy_b[100]; //Vertex of interaction measured in cm in y-axis in lab frame
    Float_t vz_b[100]; //Vertex of interaction measured in cm in z-axis in lab frame
    UChar_t dc_b[100]; // The index used to navigate any dc banks
    UChar_t cc_b[100]; // The index used to navigate any sc banks
    UChar_t ec_b[100]; //The index used to navigate any ec banks
    Float_t etot_b[100]; //The total final energy of the particle deposited in the detector
    Int_t id_b[100];


    cout<<"3" <<endl;
    //SetBranches(&data); // Located in read_in_data.h
    data.SetBranchAddress("q",&q_b);
    data.SetBranchAddress("gpart",&gpart);
    data.SetBranchAddress("sc_t",&sc_t_b);
    data.SetBranchAddress("sc_r",&sc_r_b);
    data.SetBranchAddress("sc",&sc_b);
    data.SetBranchAddress("p",&p_b);
    data.SetBranchAddress("cx",&cx_b);
    data.SetBranchAddress("cy",&cy_b);
    data.SetBranchAddress("cz",&cz_b);
    data.SetBranchAddress("stat",&stat_b);
    data.SetBranchAddress("dc_stat",&dc_stat_b);
    data.SetBranchAddress("vx",&vx_b);
    data.SetBranchAddress("vy",&vy_b);
    data.SetBranchAddress("vz",&vz_b);
    data.SetBranchAddress("dc",&dc_b);
    data.SetBranchAddress("cc",&cc_b);
    data.SetBranchAddress("ec",&ec_b);
    data.SetBranchAddress("etot",&etot_b);
    data.SetBranchAddress("id",&id_b);
    
    //MakeHist();
    //MakeHist();
    MakeHist_dtp_q();
    //MakeHist_dtpip();
   // MakeHist_fidp_q();
    //MakeHist_fidpip();
    
    cout<<"4" <<endl;
    //Progress
    int progress;

    int q_m[100];

    cout<< "made histograms?" <<endl;

        //Put the various variables into straight C++ data types
    int q[100] ;// = (int) q_b; //The charge of each given particle
    double sc_t[100] ;// = (double) sc_t_b; //The time taken for a particle to travel through as found by the sc
    double sc_r[100] ; //= (double) sc_r_b; //The distance taken by a particle through the detector as found by the sc
    int sc[100] ; //The index used to navigate any sc banks
    double p[100]; //The momentum of given particles calculated from the curavture through the dc
    double cx[100]; //The Cosine projection of the particle's intitial trajectory in x-axis the lab frame
    double cy[100] ; //The Cosine projection of the particle's intitial trajectory in y-axis the lab frame
    double cz[100] ; //The Cosine projection of the particle's intitial trajectory in z-axis the lab frame
    int stat[100] ; //Shows how statistically sound the particular particle is 
    int dc_stat[100]; //Shows how statistically sound the particular event is using data from the dc
    double vx[100] ; //Vertex of interaction measured in cm in x-axis in lab frame
    double vy[100] ; //Vertex of interaction measured in cm in y-axis in lab frame
    double vz[100] ; //Vertex of interaction measured in cm in z-axis in lab frame
    int dc[100] ; // The index used to navigate any dc banks
    int cc[100] ; // The index used to navigate any sc banks
    int ec[100]; //The index used to navigate any ec banks
    double etot[100]; //The total final energy of the particle deposited in the detector
    int id[100];


        for(int i = 0; i <100; i++){
            q[i] = (int) q_b[i];// = (int) q_b; //The charge of each given particle
            sc_t[i] = (double) sc_t_b[i];// = (double) sc_t_b; //The time taken for a particle to travel through as found by the sc
            sc_r[i] = (double) sc_r_b[i]; //= (double) sc_r_b; //The distance taken by a particle through the detector as found by the sc
            sc[i] = (int) sc_b[i]; //The index used to navigate any sc banks
            p[i] = (double) p_b[i]; //The momentum of given particles calculated from the curavture through the dc
            cx[i] = (double) cx_b[i]; //The Cosine projection of the particle's intitial trajectory in x-axis the lab frame
            cy[i] = (double) cy_b[i]; //The Cosine projection of the particle's intitial trajectory in y-axis the lab frame
            cz[i] = (double) cz_b[i]; //The Cosine projection of the particle's intitial trajectory in z-axis the lab frame
            stat[i] = (int) stat_b[i]; //Shows how statistically sound the particular particle is 
            dc_stat[i] = (int) dc_stat_b[i]; //Shows how statistically sound the particular event is using data from the dc
            vx[i] = (double) vx_b[i]; //Vertex of interaction measured in cm in x-axis in lab frame
            vy[i] = (double) vy_b[i]; //Vertex of interaction measured in cm in y-axis in lab frame
            vz[i] = (double) vz_b[i]; //Vertex of interaction measured in cm in z-axis in lab frame
            dc[i] = (int) dc_b[i]; // The index used to navigate any dc banks
            cc[i] = (int) cc_b[i]; // The index used to navigate any sc banks
            ec[i] = (int) ec_b[i]; //The index used to navigate any ec banks
            etot[i] = (double) etot_b[i]; //The total final energy of the particle deposited in the detector
            id[i] = (int) id_b[i];
        }

    for(int i = 0; i< events ; i++)
    {
        //Update on the progress
       // cout<<"got into the loop?" <<endl;
        //cout<< "one " <<endl;
        progress = (int) 100.0*(((double)i+1.0)/(double)events);
       cout <<"Progess Percent " <<progress <<"\r";
       //cout<< "two " <<endl;
        //Get info for event i
        data.GetEntry(i);
        //Reasign(); //Converts to C++ data types variables.h
        for(int i = 0; i <100; i++){
            q[i] = (int) q_b[i];// = (int) q_b; //The charge of each given particle
            sc_t[i] = (double) sc_t_b[i];// = (double) sc_t_b; //The time taken for a particle to travel through as found by the sc
            sc_r[i] = (double) sc_r_b[i]; //= (double) sc_r_b; //The distance taken by a particle through the detector as found by the sc
            sc[i] = (int) sc_b[i]; //The index used to navigate any sc banks
            p[i] = (double) p_b[i]; //The momentum of given particles calculated from the curavture through the dc
            cx[i] = (double) cx_b[i]; //The Cosine projection of the particle's intitial trajectory in x-axis the lab frame
            cy[i] = (double) cy_b[i]; //The Cosine projection of the particle's intitial trajectory in y-axis the lab frame
            cz[i] = (double) cz_b[i]; //The Cosine projection of the particle's intitial trajectory in z-axis the lab frame
            stat[i] = (int) stat_b[i]; //Shows how statistically sound the particular particle is 
            dc_stat[i] = (int) dc_stat_b[i]; //Shows how statistically sound the particular event is using data from the dc
            vx[i] = (double) vx_b[i]; //Vertex of interaction measured in cm in x-axis in lab frame
            vy[i] = (double) vy_b[i]; //Vertex of interaction measured in cm in y-axis in lab frame
            vz[i] = (double) vz_b[i]; //Vertex of interaction measured in cm in z-axis in lab frame
            dc[i] = (int) dc_b[i]; // The index used to navigate any dc banks
            cc[i] = (int) cc_b[i]; // The index used to navigate any sc banks
            ec[i] = (int) ec_b[i]; //The index used to navigate any ec banks
            etot[i] = (double) etot_b[i]; //The total final energy of the particle deposited in the detector
            id[i] = (int) id_b[i];
        }
       // cout<< "three" <<endl;
        int duck = 0;

        //Fill_eid(p[0], q[0], cx[0], cy[0], cz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], stat[0], etot[0], id[0]);
        //cout << "did electron things about to enter for loop" <<endl;
        for(int j = 1; j<gpart ; j++){
           //if(hid_sanity(dc[j], sc[j], stat[j], dc_stat[j])){
                //Pre
                //Fill_fid_q(q[j],0,cx[j],cy[j],cz[j]);
                cout<< "oen" <<endl;
                Fill_dt_q(q[j],0,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                
                /*
                //Delta T
                if(delta_t_proton(p[0], p[j], sc_r[sc[0]-1], sc_r[sc[j]-1], sc_t[sc[0]-1], sc_t[sc[j]-1])){
                    duck ++;
                    cout<< "tow" <<endl;
                    Fill_dt_q(q[j],1,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                }
                else{
                    cout<< "there" <<endl;
                    Fill_dt_q(q[j],2,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                }
                /*
                //Fiducial
                if(fid_h(p[j], cx[j], cy[j], cz[j])){
                    Fill_fid_q(q[j],1,cx[j],cy[j],cz[j]);
                    duck ++;
                }
                else{
                    Fill_fid_q(q[j],2,cx[j],cy[j],cz[j]);
                }
                //Full ID
                //if(fid_h(p[j],cx[j],cy[j],cz[j]) && delta_t_proton(p[0], p[j], sc_r[sc[0]-1], sc_r[sc[j]-1], sc_t[sc[0]-1], sc_t[sc[j]-1])){
                if(duck == 2){
                    Fill_dt_q(q[j],3,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                    Fill_fid_q(q[j],3,cx[j],cy[j],cz[j]);
                }
               
                if(id[j] == PROTON){
                    cout<< "fuor" <<endl;
                    Fill_dt_q(q[j],5,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                    //Fill_fid_q(q[j],5,cx[j],cy[j],cz[j]);
                }
                /*
             if(is_proton(q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[j], sc_t[sc[j]-1], sc_r[sc[j]-1], p[0],sc_r[sc[0]-1], sc_t[sc[0]-1])){
                    Fill_dt_q(q[j],4,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                    Fill_fid_q(q[j],4,cx[j],cy[j],cz[j]);
                }
                */
           // }
            
        }
    }

    output->Write();
    std::cout<<"\n \n \nwrite" <<std::endl;
    output->Close();
    std::cout<<"close" <<std::endl;

	return 0;
}
