#ifndef VARIABLES_H
#define VARIABLES_H

  //Input Variables from Commandline
    std::string comp; //Variable for choosing which data set will be used
    char* output_name;//Variable for the output file name. This is reassigned through input parameters
    int file_num = -1;//The initial assignment for the number of files in the program. -1 equates to all of them
    int work = 0;//Variable notified to let the program know that a proper file was attempted to be loaded
    int which = 0;//Variable which is assigned based on which file set is loaded so the user can be notified
    int naming_var = 0; //Variable used in switiching the index for outputs in the beginning. Used when inputing 3 inputs rather than 4

  

    //Data parameters
    int events;//The variable for the total number of events
    int progress;//The Variable for the percentage of events looped through
    double MM_p_val; //The variable for the value of the Missing Mass Squared for proton missing topology
    double MM_pi_val;//The variable for the value of the Missing Mass Squared for pion missing topology
    double MM_pi2_val;//For testing proper particle ID
    double MM_pi3_val;//For testing proper particle ID
    double MM_pip_pass;
    double MM_pim_pass;
    double MM_p_pass;
    double MM_full;//The variable for the value of the Missing Mass Squared for the full topology
    double MM_full_pass;
    bool p_pass; 
    bool pip_pass;
    bool pim_pass;
    bool zero_pass;
    bool p_pre;
    bool pip_pre;
    bool pim_pre;
    bool zero_pre;
    double alph;
    double event_W;
    double event_Q2;
    double theta_event;
    double theta_p_pip;
    double theta_p_pim;
    double theta_pip_pim;
    double MM_p_pip;
    double MM_p_pim;
    double MM_pip_pim;
    double MM_event;

    TLorentzVector ele_mu;
    TLorentzVector pro_mu;
    TLorentzVector pip_mu;
    TLorentzVector pim_mu;
    //TLorentzVector pro2_mu;//Misidentified as a proton switch to pi+
    //TLorentzVector pip2_mu;//Misidentified as a pi+ switch to proton

    //Fitting parameters
    double parameters[6];//First three are parameters with the latter three as their errors

    Int_t gpart; //The number of particles registered in a given event
    Char_t q_b[100]; //The charge of each given particle
    Float_t sc_t_b[100]; //The time taken for a particle to travel through as found by the sc
    Float_t sc_r_b[100]; //The distance taken by a particle through the detector as found by the sc
    UChar_t sc_b[100]; //The index used to navigate any sc banks
    Float_t p_b[100]; //The momentum of given particles calculated from the curavture through the dc //AH HA!!! The old file had this as an int, but the good files have this as a UChar
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
    Short_t id_b[100];

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
    int id[100];//The id assigned to it automatically through the standard parameters

    //Int_t gpart; //The number of particles registered in a given event
    //Need to reassign the individual pieces of the array rather than entire arrays at once 7/31/17
    void Reassign(){
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
            id[i] = (int) id_b[i];//The id assigned to it automatically through the standard parameters
        }
    }

    //Histogram naming variables
    char  htitle[100]; //The name on the graph itself (can have spaces)
    char  hname[100]; //The name shown in the TBrowser (should have no spaces)


    //Form Directories
    //TDirectory 
    




#endif