#ifndef VARIABLES_H
#define VARIABLES_H


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

    Int_t gpart; //The number of particles registered in a given event
    Char_t q[100]; //The charge of each given particle
    Float_t sc_t[100]; //The time taken for a particle to travel through as found by the sc
    Float_t sc_r[100]; //The distance taken by a particle through the detector as found by the sc
    UChar_t sc[100]; //The index used to navigate any sc banks
    Float_t p[100]; //The momentum of given particles calculated from the curavture through the dc
    Float_t cx[100]; //The Cosine projection of the particle's intitial trajectory in x-axis the lab frame
    Float_t cy[100]; //The Cosine projection of the particle's intitial trajectory in y-axis the lab frame
    Float_t cz[100]; //The Cosine projection of the particle's intitial trajectory in z-axis the lab frame
    Char_t stat[100]; //Shows how statistically sound the particular particle is 
    UChar_t dc_stat[100]; //Shows how statistically sound the particular event is using data from the dc
    Float_t vx[100]; //Vertex of interaction measured in cm in x-axis in lab frame
    Float_t vy[100]; //Vertex of interaction measured in cm in y-axis in lab frame
    Float_t vz[100]; //Vertex of interaction measured in cm in z-axis in lab frame
    UChar_t dc[100]; // The index used to navigate any dc banks
    UChar_t cc[100]; // The index used to navigate any sc banks
    UChar_t ec[100]; //The index used to navigate any ec banks
    Float_t etot[100]; //The total final energy of the particle deposited in the detector
    Int_t id[100];


#endif