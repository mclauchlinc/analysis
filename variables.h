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

    //Int_t gpart; //The number of particles registered in a given event
    //Need to reassign the individual pieces of the array rather than entire arrays at once 7/31/17
    void Reasign(){
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
    }

    //Form Directories
    // TDirectory 
    

   //The distance taken by a particle through the detector as found by the sc
    /*int sc[100] = (int) sc_b; //The index used to navigate any sc banks
    double p[100] = (double) p_b; //The momentum of given particles calculated from the curavture through the dc
    double cx[100] = (double) cx_b; //The Cosine projection of the particle's intitial trajectory in x-axis the lab frame
    double cy[100] = (double) cy_b; //The Cosine projection of the particle's intitial trajectory in y-axis the lab frame
    double cz[100] = (double) cz_b; //The Cosine projection of the particle's intitial trajectory in z-axis the lab frame
    int stat[100] = (int) stat_b; //Shows how statistically sound the particular particle is 
    int dc_stat[100] = (int) dc_stat_b; //Shows how statistically sound the particular event is using data from the dc
    double vx[100] = (double) vx_b; //Vertex of interaction measured in cm in x-axis in lab frame
    double vy[100] = (double) vy_b; //Vertex of interaction measured in cm in y-axis in lab frame
    double vz[100] = (double) vz_b; //Vertex of interaction measured in cm in z-axis in lab frame
    int dc[100] = (int) dc_b; // The index used to navigate any dc banks
    int cc[100] = (int) cc_b; // The index used to navigate any sc banks
    int ec[100] = (int) ec_b; //The index used to navigate any ec banks
    double etot[100] = (double) etot_b; //The total final energy of the particle deposited in the detector
    int id[100] = (int) id_b;
    */


#endif
