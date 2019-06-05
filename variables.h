#ifndef VARIABLES_H
#define VARIABLES_H

  //Input Variables from Commandline
    std::string comp; //Variable for choosing which data set will be used
    char* output_name;//Variable for the output file name. This is reassigned through input parameters
    int file_num = -1;//The initial assignment for the number of files in the program. -1 equates to all of them
    int work = 0;//Variable notified to let the program know that a proper file was attempted to be loaded
    int which = 0;//Variable which is assigned based on which file set is loaded so the user can be notified
    int naming_var = 0; //Variable used in switiching the index for outputs in the beginning. Used when inputing 3 inputs rather than 4

    int ele_ints[10];
    int pro_ints[5];
    int pip_ints[5];
    int pim_ints[7];
    int had_ints[7];

    int q_las;


    double ele_dob[5];
    double pro_dob[9];
    double pip_dob[9];
    double pim_dob[13];
    double had_dob[13];

    /*
    //bool eid_5(double p, int q, double cx, double cy, double cz, int dc, int cc, int ec, int sc, int dc_stat, int stat, double etot, int cc_sect, int cc_segm, int nphe)
    void Assign_Elec(int *elecints[10], double *eledobs[5], double p, int q, double cx, double cy, double cz, int dc, int cc, int ec, int sc, int dc_stat, int stat, double etot, int cc_sect, int cc_segm, int nphe){
        ele_ints[0] =  q;
        ele_ints[1] = dc;
        ele_ints[2] = cc;
        ele_ints[3] = ec;
        ele_ints[4] = sc;
        ele_ints[5] = stat;
        ele_ints[6] = dc_stat;
        ele_ints[7] = cc_sect;
        ele_ints[8] = cc_segm;
        ele_ints[9] = nphe;
        ele_dob[0] = p;
        ele_dob[1] = cx;
        ele_dob[2] = cy;
        ele_dob[3] = cz;
        ele_dob[4] = etot;
    }

    void Assign_Pro(int *pro_ints[10], double *pro_dob[9], int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_r0, double sc_t0){
        pro_ints[0] = q;
        pro_ints[1] = dc;
        pro_ints[2] = sc;
        pro_ints[3] = stat;
        pro_ints[4] = dc_stat;
        pro_dob[0] = p;
        pro_dob[1] = cx;
        pro_dob[2] = cy;
        pro_dob[3] = cz;
        pro_dob[4] = sc_t;
        pro_dob[5] = sc_r;
        pro_dob[6] = sc_t0;
        pro_dob[7] = sc_r0;
        pro_dob[8] = p0; 
    }

    void Assign_Pip(int &pip_ints[10], double &pip_dob[9], int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_r0, double sc_t0){
        pip_ints[0] = q;
        pip_ints[1] = dc;
        pip_ints[2] = sc;
        pip_ints[3] = stat;
        pip_ints[4] = dc_stat;
        pip_dob[0] = p;
        pip_dob[1] = cx;
        pip_dob[2] = cy;
        pip_dob[3] = cz;
        pip_dob[4] = sc_t;
        pip_dob[5] = sc_r;
        pip_dob[6] = sc_t0;
        pip_dob[7] = sc_r0;
        pip_dob[8] = p0; 
    }

    void Assign_Pim(int *pip_ints[10], double *pip_dob[9], int q, double p, double cx, double cy, double cz, int dc, int sc, int stat, int dc_stat, double sc_t, double sc_r, double p0, double sc_r0, double sc_t0, double cc, double ec, double etot, double vx, double vy, double vz){
        pim_ints[0] = q;
        pim_ints[1] = dc;
        pim_ints[2] = sc;
        pim_ints[3] = stat;
        pim_ints[4] = dc_stat;
        pim_ints[5] = cc;
        pim_ints[6] = ec;
        pim_dob[0] = p;
        pim_dob[1] = cx;
        pim_dob[2] = cy;
        pim_dob[3] = cz;
        pim_dob[4] = sc_t;
        pim_dob[5] = sc_r;
        pim_dob[6] = sc_t0;
        pim_dob[7] = sc_r0;
        pim_dob[8] = p0; 
        pim_dob[9] = etot;
        pim_dob[10] = vx;
        pim_dob[11] = vy;
        pim_dob[12] = vz; 
    }*/

    int counts = 0;

    //Data parameters
    int events;//The variable for the total number of events
    int eventsIN;
    int eventsOUT;
    int progress;//The Variable for the percentage of events looped through
    double MM_p_val; //The variable for the value of the Missing Mass Squared for proton missing topology
    double MM_pi_val;//The variable for the value of the Missing Mass Squared for pion missing topology
    double MM_pi2_val;//For testing proper particle ID
    double MM_pi3_val;//For testing proper particle ID
    double MM_pip_pass;//passed pip MM ID for event selection
    double MM_pim_pass; //passed pim MM ID for event selection
    double MM_p_pass;
    double MM_full;//The variable for the value of the Missing Mass Squared for the full topology
    double MM_full_pass;//Passed all observed event
    bool p_pass; //proton ID passed
    bool pip_pass;//pip ID passed
    bool pim_pass;//pim ID passed
    bool zero_pass;//
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
    int e_helicity; //Helicity of the electron beam for an event (+ = 1, - = -1, unknonwn = 0)
    int plate_stat; //status of the half wave plate: whether in or out (1 = in, -1 = out, 0 = not stated)

    TLorentzVector ele_mu;//Four vector for scattered election
    TLorentzVector pro_mu;//Four vector for scattered proton
    TLorentzVector pip_mu;//Four Vector for scattered pi+
    TLorentzVector pim_mu;//Four Vector for scattered pi-
    //TLorentzVector pro2_mu;//Misidentified as a proton switch to pi+
    //TLorentzVector pip2_mu;//Misidentified as a pi+ switch to proton

    //Fitting parameters
    double parameters[6];//First three are parameters with the latter three as their errors
    double parameters2[6];//Parameters for a second layer of fits if multiple gaussians are being fit simultaneously

    //Electron angle corrections
    double eac1_pars[14][41][6][8];//{theta}{phi}{sector}{parameters and errors}//For the angular electron momentum corrections step 1
    double eac2_x[14][6];//{theta}{sector}
    double eac2_pars[14][6][5];//{theta}{sector}{A,B,C,D,E}

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
    UChar_t cc_hit_b[100];
    Int_t cc_part_b;
    UChar_t cc_sect_b[100];
    Int_t cc_segm_b[100];
    UShort_t nphe_b[100];
    Float_t q_l_b;
    Int_t evntclas2;

    //int gpart; //The nmcer of particles registered in a given event
    int q_c[100]; //The charge of each given particle
    float sc_t_c[100]; //The time taken for a particle to travel throgh as fond cy the sc
    float sc_r_c[100]; //The distance taken cy a particle throgh the detector as fond cy the sc
    int sc_c[100]; //The index sed to navigate any sc canks
    float p_c[100]; //The momentm of given particles calclated from the cravtre throgh the dc //AH HA!!! The old file had this as an int, ct the good files have this as a Char
    float cx_c[100]; //The Cosine projection of the particle's intitial trajectory in x-axis the lac frame
    float cy_c[100]; //The Cosine projection of the particle's intitial trajectory in y-axis the lac frame
    float cz_c[100]; //The Cosine projection of the particle's intitial trajectory in z-axis the lac frame
    int stat_c[100]; //Shows how statistically sond the particlar particle is 
    int dc_stat_c[100]; //Shows how statistically sond the particlar event is sing data from the dc
    float vx_c[100]; //Vertex of interaction measred in cm in x-axis in lac frame
    float vy_c[100]; //Vertex of interaction measred in cm in y-axis in lac frame
    float vz_c[100]; //Vertex of interaction measred in cm in z-axis in lac frame
    int dc_c[100]; // The index sed to navigate any dc canks
    int cc_c[100]; // The index sed to navigate any sc canks
    int ec_c[100]; //The index sed to navigate any ec canks
    float etot_c[100]; //The total final energy of the particle deposited in the detector
    int id_c[100];
    int cc_hit_c[100];
    int cc_part_c;
    int cc_sect_c[100];
    int cc_segm_c[100];
    int nphe_c[100];
    float q_l_c;
    int evntclas2_c; 
    //int evntclas_c;


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
    int cc_hit[100];//*CHECK* the number of registred photo electrons created?
    int cc_part;//*CHECK* the number of particles registred in the CC for a particular event
    int cc_sect[100]; //The sector a particle was registered in
    int cc_segm[100];//The segment the CC hit was registered in 
    int nphe[100];//number of photo-electrons
    float q_l; //Charge accumulated for individual runs on the Faraday Cup 
    //int evntclas2; //The helicity state of the event, but needs 1/2 wave plate info for consistent definition 

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
            cc_hit[i] = (int) cc_hit_b[i];
            cc_part = (int) cc_part_b;
            cc_segm[i] = (int) cc_segm_b[i];
            cc_sect[i] = (int) cc_sect_b[i];
            nphe[i] = (int) nphe_b[i];
            q_l = (float) q_l_b;
            //evntclas2 = (int) evntclas2_b;
       }
    }

    void Reassign3(){
            for(int i = 0; i <100; i++){
            q[i] = (int) q_c[i];// = (int) q_c; //The charge of each given particle
            sc_t[i] = (double) sc_t_c[i];// = (doucle) sc_t_c; //The time taken for a particle to travel through as found cy the sc
            sc_r[i] = (double) sc_r_c[i]; //= (doucle) sc_r_c; //The distance taken cy a particle through the detector as found cy the sc
            sc[i] = (int) sc_c[i]; //The index used to navigate any sc canks
            p[i] = (double) p_c[i]; //The momentum of given particles calculated from the curavture through the dc
            cx[i] = (double) cx_c[i]; //The Cosine projection of the particle's intitial trajectory in x-axis the lac frame
            cy[i] = (double) cy_c[i]; //The Cosine projection of the particle's intitial trajectory in y-axis the lac frame
            cz[i] = (double) cz_c[i]; //The Cosine projection of the particle's intitial trajectory in z-axis the lac frame
            stat[i] = (int) stat_c[i]; //Shows how statistically sound the particular particle is 
            dc_stat[i] = (int) dc_stat_c[i]; //Shows how statistically sound the particular event is using data from the dc
            vx[i] = (double) vx_c[i]; //Vertex of interaction measured in cm in x-axis in lac frame
            vy[i] = (double) vy_c[i]; //Vertex of interaction measured in cm in y-axis in lac frame
            vz[i] = (double) vz_c[i]; //Vertex of interaction measured in cm in z-axis in lac frame
            dc[i] = (int) dc_c[i]; // The index used to navigate any dc canks
            cc[i] = (int) cc_c[i]; // The index used to navigate any sc canks
            ec[i] = (int) ec_c[i]; //The index used to navigate any ec canks
            etot[i] = (double) etot_c[i]; //The total final energy of the particle deposited in the detector
            id[i] = (int) id_c[i];//The id assigned to it automatically through the standard parameters
            cc_hit[i] = (int) cc_hit_c[i];
            cc_part = (int) cc_part_c;
            cc_segm[i] = (int) cc_segm_c[i];
            cc_sect[i] = (int) cc_sect_c[i];
            nphe[i] = (int) nphe_c[i];
            //q_l = (int) q_l_c;
            //evntclas2 = (int) evntclas2_c; 
       }
    }

    //Histogram naming variables
    char  htitle[100]; //The name on the graph itself (can have spaces)
    char  hname[100]; //The name shown in the TBrowser (should have no spaces)

    char cname1[100];
    char cname2[100];

    int Qbin_now; 
    int Wbin_now; 

    TLorentzVector p_mu_event;
    //Form Directories
    //TDirectory 
    
    //For fun TGraphs for yields
    double x[9][6][30][13][10][10][5];//Single Diff xc, Q2, W, MM binning, theta binning, alpha binning, helicity
    double y[9][6][30][13][10][10][5];//Single Diff xc, Q2, W, MM binning, theta binning, alpha binning, helicity

    //Differential Cross Section Values
    double xc_x[9][6][30][13][10][10][5];//{Single Diff xc, Q2, W, MM binning, Theta binning, Alpha binning,helicity}
    double xc_y[9][6][30][13][10][10][5];//{Single Diff xc, Q2, W, MM binning, Theta binning, Alpha binning,helicity}
    //{Helicity binning is 0 = - 1 = ?? 2 = +, 3 = sum of all, 4 = + minus -}
    




#endif