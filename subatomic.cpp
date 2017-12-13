#include "headers.h" //Contains all the header files I need
#include "event_pro.h"
#include "hist_project.h"



using namespace std; //A standard space to be in for a c++ program
int main(int argc, char** argv){ //Main function that will return an integer. argc/v are for command line inputs
    std::cout<< "You have " <<argc <<" arguments" <<std::endl;
    

    //Set input and output files
    //The argv[i] cannot be called directly, so their values need to be assigned to variables in the program
    if(argc == 4){
        for(int w = 0; w < argc ; w++){ //Loop over inputs to confirm intention 
            std::cout<< arguments[w] <<": " <<argv[w] <<endl; //arguments array found in constants.h
        }
        std::cout<< "Start argv assignment: ";
        comp = argv[1]; //variables.h
        file_num = std::atoi(argv[2]); //variables.h
        output_name = argv[3]; //variables.h
        std::cout<<"Complete" <<std::endl;
    }
    else{
        if( argc == 3){//No file number input
            for(int w = 0; w < argc ; w++){ //Loop over inputs to confirm intention 
                naming_var = w;
                if(w == 2){//Skip over the number of files
                    naming_var++;
                }
                    std::cout<< arguments[naming_var] <<": " <<argv[w] <<endl; //arguments array found in constants.h
            }
            std::cout<<"Start argv assignment: ";
            comp = argv[1]; //variables.h
            file_num = -1; //Just read in all files;
            output_name = argv[2];
            std::cout<<"Complete" <<std::endl;
        }
        else{
            std::cout<< "You have not properly put in commandline inputs" <<std::endl;
            std::cout<<"Remember you need ./analysis, input, number of files, output" <<std::endl;
            std::cout<<"Rerun this program. None of this will work now" <<std::endl;
            std::exit(1);
        }
    }

    //Work with loading in files
    std::cout<<"Create Output File: ";
    TFile *output = Name_File(output_name); //read_in_files.h
    std::cout<<"Complete" <<std::endl <<"Load root files: ";
    TChain data("h10"); //Create TChain to be used. TTrees are h10
    if(comp == "one"){ //Desktop computer in office
        loadChain(&data, "/home/mclauchlinc/Desktop/analysis/nick_convert_e16.txt", file_num);//read_in_data.h
        work++; //variables.h
        which = 1; //denote which data set //variables.h
    }
    if(comp == "two"){  //Mac Data set
        loadChain(&data, "e16_10_18_17_ntple.txt",file_num);//read_in_files.h;
        work++;//variables.h
        which = 2; //denote which set //variables.h
    }
    if(work == 1){ //Did the function loadChain run without halting everything?
        std::cout<<"Complete" <<std::endl;
    }
    else{
        std::cout<<"Error" <<std::endl;
	std::exit(1);
    }

    //Outputs on what was input
    events = data.GetEntries(); //TTree.h //variables.h
    std::cout<<"You have read in data from " <<local[which] <<std::endl;
    std::cout<<"Events loaded: " <<events <<std::endl;

    //Set Branches
    std::cout<< "Setting Branches: ";
    SetBranches(&data);//read_in_data.h
    std::cout<< "Complete" <<std::endl;

    //Make Histograms
    std::cout<< "Making Histograms: ";
    MakeHist();//histograms.h
    MakeHist_MM_p();
    MakeHist_WQ2_p();
    std::cout<<"Complete" <<std::endl;

    int y_Dp_p = 0;
    int y_Dp_pip = 0;

    int num_Dpp = 0;
    int num_Dz = 0;

    double MM0_p;
    double MM1_p;
    double MM1_pi;
    double MM1_pi_pp;
    double MM1_pi_z;

    double W_p;
    double Q2_p;

    TLorentzVector k_pip, k_pim, k_p, k_e;


    for(int i = 0; i< events ; i++)
    {
        //Update on the progress
       // cout<<"got into the loop?" <<endl;
        progress = (int) 100.0*(((double)i+1.0)/(double)events);
        cout <<"Progess Percent " <<progress <<"\r" << std::flush;

       p_pass = false;
       pip_pass = false;
       pim_pass = false;
       zero_pass = false;

        //Get info for event i
        data.GetEntry(i);
        Reassign(); //Converts to C++ data types variables.h

        Fill_eid(p[0], q[0], cx[0], cy[0], cz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], stat[0], etot[0], id[0]);
        //cout << "did electron things about to enter for loop" <<endl;
        //Missing mass when no particles are observed
        if(eid(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], 4)){
            //cout<<endl <<"Running MM1_b" <<endl;
            MM0_p = MM1_b(p[0],cx[0],cy[0],cz[0],me);

            k_e = Make_4Vector(0.0,0.0,0.0,0.0,0.0);
            k_p = Make_4Vector(0.0,0.0,0.0,0.0,0.0);
            k_pip = Make_4Vector(0.0,0.0,0.0,0.0,0.0);
            k_pim = Make_4Vector(0.0,0.0,0.0,0.0,0.0);
            
            //std::cout<<endl<< "Running WP" <<endl;
            W_p = WP(0,p[0],cx[0],cy[0],cz[0]);

            Q2_p = Qsquared(0,p[0],cx[0],cy[0],cz[0]);

            //std::cout<< endl<<"Difference "<<(W_p - MM0_p) <<endl <<endl;

            Fill_MM_p(1,0,0,W_p);//Dp p pre
            Fill_MM_p(1,1,0,W_p);//Dp pip pre
            
            //PRE for WQ2
            for(int o = 0; o <3 ; o++){
                for(int u = 0; u<2; u++){
                    Fill_WQ2_p(o,u,0,W_p,Q2_p);
                }
            }
        
            
            for(int j = 1; j<gpart ; j++){
                Fill_Hadron(q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1], p[0], sc_t[sc[0]-1], sc_r[sc[0]-1], id[j]);
                //Missing Mass
                    //Missing Mass one measured
                MM1_pi = MM2_b(p[0],cx[0],cy[0],cz[0],me, p[j], cx[j], cy[j], cz[j],mpi);//Both 1 observed things are pions
                MM1_p = MM2_b(p[0],cx[0],cy[0],cz[0],me, p[j], cx[j], cy[j], cz[j],mp);//For observed proton
                if(is_pim( q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1], p[0], sc_r[sc[0]-1], sc_t[sc[0]-1])){
                    Fill_MM_p(0,0,0,MM1_pi);//D++ pim observed pre
                }
                if(is_pip( q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1], p[0], sc_r[sc[0]-1], sc_t[sc[0]-1])){
                    Fill_MM_p(2,0,0,MM1_pi);//D0 pip observed pre
                }


                //D++ pim
                if(isDpp_pim_other(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1])){
                    Fill_MM_p(0,0,1,MM1_pi);//Dp p cut
                    Fill_WQ2_p(0,0,1,W_p,Q2_p);
                    //Cut for Delta
                    if(MM_D_direct(MM1_pi)){
                        Fill_MM_p(0,0,2,MM1_pi);
                        Fill_WQ2_p(0,0,2,W_p,Q2_p);
                    }
                    else{
                        Fill_MM_p(0,0,3,MM1_pi);
                        Fill_WQ2_p(0,0,3,W_p,Q2_p);
                    }
                }

                //D+ p
                if(isDp_p_other(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1])){
                    //y_Dp_p++;
                    Fill_MM_p(1,0,1,MM1_p);//The precut for pi0 ID
                    Fill_WQ2_p(1,0,1,W_p,Q2_p);
                    //Cut for pi0
                    if(MM_piz_direct(MM1_p)){
                        Fill_MM_p(1,0,2,MM1_p);//Filling the cut on the pi0
                        Fill_WQ2_p(1,0,2,W_p,Q2_p);
                        Fill_MM_p(1,0,4,MM0_p);//Pre for Delta ID
                        Fill_WQ2_p(1,0,4,W_p,Q2_p);
                        if(MM_D_direct(MM0_p)){
                            y_Dp_p++;
                            Fill_MM_p(1,0,5,MM0_p); //Cut for Delta ID
                            Fill_WQ2_p(1,0,5,W_p,Q2_p);
                        }
                        else{
                            Fill_MM_p(1,0,6,MM0_p);//Anti cut for Delta id
                            Fill_WQ2_p(1,0,6,W_p,Q2_p);
                        }
                    }
                    else{
                        Fill_MM_p(1,0,3,MM1_p);//Anti cut for Pi0 id
                        Fill_WQ2_p(1,0,3,W_p,Q2_p);
                    }
                }

                //D+ pip
                if(isDp_pip_other(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1])){
                    //y_Dp_p++;
                    Fill_MM_p(1,1,1,MM1_pi);//The precut for n ID
                    Fill_WQ2_p(1,1,1,W_p,Q2_p);
                    //Cut for neutron
                    if(MM_n_direct(MM1_pi)){
                        Fill_MM_p(1,1,2,MM1_pi);//Filling the cut on the n
                        Fill_WQ2_p(1,1,2,W_p,Q2_p);
                        Fill_MM_p(1,1,4,MM0_p);//Pre for Delta ID
                        Fill_WQ2_p(1,1,4,W_p,Q2_p);
                        if(MM_D_direct(MM0_p)){
                            y_Dp_pip++;
                            Fill_MM_p(1,1,5,MM0_p); //Cut for Delta ID
                            Fill_WQ2_p(1,1,5,W_p,Q2_p);
                        }
                        else{
                            Fill_MM_p(1,1,6,MM0_p);//Anti cut for Delta id
                            Fill_WQ2_p(1,1,6,W_p,Q2_p);
                        }
                    }
                    else{
                        Fill_MM_p(1,1,3,MM1_pi);//Anti cut for n id
                        Fill_WQ2_p(1,1,3,W_p,Q2_p);
                    }
                }

                //D0 pip
                if(isDz_pip_other(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1])){
                    Fill_MM_p(2,0,1,MM1_pi);//D0 Delta cut
                }

                for(int k = 1; k<gpart ; k++){
                    //Missing Mass for pion calculation
                    MM_pi_val = MM_3_com(p[0],p[j],p[k],cx[0],cx[j],cx[k],cy[0],cy[j],cy[k],cz[0],cz[j],cz[k],me,mp,mpi);
                    //Proton missing mass topology
                    if(other_p_miss(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], j, k)){
                          MM_p_val = MM_3_com(p[0],p[j],p[k],cx[0],cx[j],cx[k],cy[0],cy[j],cy[k],cz[0],cz[j],cz[k],me,mpi,mpi);
                        Fill_MM(0,0,MM_p_val);
                        //Proton Missing Cut
                        if(MM_p2(MM_p_val)){
                            Fill_MM(0,1,MM_p_val);
                            p_pass = true;
                            Fill_WQ2_ES(0,p[0],cx[0],cy[0],cz[0]);
                            k_pim = Make_4Vector(p[k],cx[k],cy[k],cz[k],mpi);
                            k_pip = Make_4Vector(p[j],cx[j],cy[j],cz[j],mpi);
                            k_e = Make_4Vector(p[0],cx[0],cy[0],cz[0],me);
                            k_p = k_mu_e16 + p_mu - k_e - k_pim - k_pip;
                        }
                         //Proton Missing Anti
                        else{
                            Fill_MM(0,2,MM_p_val);
                        }
                    }
                    //Pi+ missing mass topology
                    if(other_pip_miss(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], j, k)){
                        Fill_MM(1,0,MM_pi_val);
                        //Pi+ Missing Cut
                        if(MM_pi2(MM_pi_val)){
                            Fill_MM(1,1,MM_pi_val);
                            pip_pass = true;
                            Fill_WQ2_ES(1,p[0],cx[0],cy[0],cz[0]);
                            if( p_pass){
                                k_p = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                            }
                            else{
                                k_pim = Make_4Vector(p[k],cx[k],cy[k],cz[k],mpi);
                                k_p = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                                k_e = Make_4Vector(p[0],cx[0],cy[0],cz[0],me);
                                k_pip = k_mu_e16 + p_mu - k_e - k_pim - k_pim;
                            }
                        }                
                        //Pi+ Missing Anti
                        else{
                            Fill_MM(1,2,MM_pi_val);
                        }
                    }

                    //Pi- missing mass topology
                    if(other_pim_miss(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], j, k)){
                         Fill_MM(2,0,MM_pi_val);
                        //Pi- Missing Cut
                        if(MM_pi2(MM_pi_val)){
                            Fill_MM(2,1,MM_pi_val);
                            pim_pass = true;
                            Fill_WQ2_ES(2,p[0],cx[0],cy[0],cz[0]);
                        
                            if( p_pass){
                                if(!pip_pass){
                                    k_p = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                                }
                            }
                            else{
                                if(pip_pass){
                                    k_pip = Make_4Vector(p[k],cx[k],cy[k],cz[k],mpi);
                                }
                                else{
                                k_pip = Make_4Vector(p[k],cx[k],cy[k],cz[k],mpi);
                                k_p = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                                k_e = Make_4Vector(p[0],cx[0],cy[0],cz[0],me);
                                k_pim = k_mu_e16 + p_mu - k_e - k_pim - k_pim;
                                }
                            }
                        }
                        //Pi- Missing Anti
                        else{
                            Fill_MM(2,2,MM_pi_val);
                        }
                    }

                    for(int l = 0; l < gpart; l++){
                        //Full Topology Pre
                        MM_full = MM_4_com(p[0],p[j],p[k],p[l],cx[0],cx[j],cx[k],cx[l],cy[0],cy[j],cy[k],cy[l],cz[0],cz[j],cz[k],cz[l],me,mp,mpi,mpi);
            
                        if(other_zero_miss(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], q[l], p[l], cx[l], cy[l], cz[l], dc[l], sc[l], stat[l], dc_stat[dc[l]-1], sc_t[sc[l]-1], sc_r[sc[l]-1], j, k, l)){
                            Fill_MM(3,0,MM_full);
                            if(MM_all2(MM_full)){
                                //Full Topology cut
                                Fill_MM(3,1,MM_full);
                                zero_pass = true;
                                Fill_WQ2_ES(3,p[0],cx[0],cy[0],cz[0]);
                                if(pip_pass && !p_pass && !pim_pass){
                                    k_pip = Make_4Vector(p[k],cx[k],cy[k],cz[k],mpi);
                                }
                                if(p_pass && !pim_pass && !pip_pass){
                                    k_p = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                                }
                                if(pim_pass && !p_pass && !pip_pass){
                                    k_pim = Make_4Vector(p[l],cx[l],cy[l],cz[l],mpi);
                                }
                            }
                            else{
                                //Full topology anti 
                                Fill_MM(3,2,MM_4_com(p[0],p[j],p[k],p[l],cx[0],cx[j],cx[k],cx[l],cy[0],cy[j],cy[k],cy[l],cz[0],cz[j],cz[k],cz[l],me,mp,mpi,mpi));
                            }
                        }
                    }
                }
                if(top_cross(zero_pass,pim_pass,pip_pass,p_pass)){
                    Fill_WQ2_ES(4,p[0],cx[0],cy[0],cz[0]);
                }
                    
            }
            
        }
        if(zero_pass || pim_pass || pip_pass || p_pass){
            MM1_pi_pp = MM_2(k_e,k_pim);
            MM1_pi_z = MM_2(k_e,k_pip);
            Fill_MM_p(0,1,4,MM1_pi_pp);
            Fill_WQ2_p(0,1,4,W_p,Q2_p);
            Fill_MM_p(2,1,4,MM1_pi_z);
            Fill_WQ2_p(2,1,4,W_p,Q2_p);
            if(MM_D_direct(MM1_pi_z)){
                Fill_MM_p(2,1,5,MM1_pi_z);
                Fill_WQ2_p(2,1,5,W_p,Q2_p);
                num_Dz++;
            }
            else{
                Fill_MM_p(2,1,6,MM1_pi_z);
                Fill_WQ2_p(2,1,6,W_p,Q2_p);
            }
            if(MM_D_direct(MM1_pi_pp)){
                Fill_MM_p(0,1,5,MM1_pi_pp);
                Fill_WQ2_p(0,1,5,W_p,Q2_p);
                num_Dpp++;
            }
            else{
                Fill_MM_p(0,1,6,MM1_pi_pp);
                Fill_WQ2_p(0,1,6,W_p,Q2_p);
            }
        }

    }

    cout<<endl << "proton: " <<y_Dp_pip <<endl <<"pip: " <<y_Dp_p <<endl;

    cout<<endl <<"Delta ++: " <<num_Dpp <<endl <<"Delta 0: " <<num_Dz <<endl;

    std::cout<<"Adjusted Delta 0: " <<(3.0/2.0)*(float)num_Dz <<endl;
    std::cout<<"Ratio of ++/0: " <<((float)num_Dpp/(float)num_Dz)*(2.0/3.0) <<endl;
    std::cout<<"Ratio of n/p for D+: " <<(float)y_Dp_pip/(float)y_Dp_p <<endl;
    std::cout<<"Ratio of +/0: " <<(2.0/3.0)*((float)y_Dp_p + (float)y_Dp_pip)/((float)num_Dz) <<endl;
    std::cout<<"Ratio of ++/+" <<(float)num_Dpp/((float)y_Dp_p + (float)y_Dp_pip) <<endl;

    std::cout<<"\nWrite: ";
    output->Write();
    std::cout<<"Complete \nClose: " <<std::endl;
    output->Close();
    std::cout<<"Complete" <<std::endl;

	return 0;
}
