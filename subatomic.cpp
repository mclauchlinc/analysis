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

    double MM0_p;
    double MM1_p;
    double MM1_pi;

    double W_p;
    double Q2_p;

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
            MM0_p = MM1_b(p[0],cx[0],cy[0],cz[0],me);
            

            W_p = WP(0,p[0],cx[0],cy[0],cz[0]);
            Q2_p = Qsquared(0,p[0],cx[0],cy[0],cz[0]);

            std::cout<< endl<<"Difference "<<(W_p - MM0_p) <<endl <<endl;

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
                    Fill_MM_p(0,0,0,MM1_p);//D++ pim observed pre
                }
                if(is_pim( q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1], p[0], sc_r[sc[0]-1], sc_t[sc[0]-1])){
                    Fill_MM_p(2,0,0,MM1_p);//D0 pip observed pre
                }


                //D++ pim
                if(isDpp_pim_other(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1])){
                    Fill_MM_p(0,0,1,MM0_p);//Dp p cut
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
                    Fill_MM_p(2,0,1,MM0_p);//Dp p cut
                }
                
            }
            
        }

    }

    cout<<endl << "proton: " <<y_Dp_pip <<endl <<"pip: " <<y_Dp_p <<endl;

    std::cout<<"\nWrite: ";
    output->Write();
    std::cout<<"Complete \nClose: " <<std::endl;
    output->Close();
    std::cout<<"Complete" <<std::endl;

	return 0;
}
