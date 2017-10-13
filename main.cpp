#include "headers.h" //Contains all the header files I need



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
        }
    }

    //Work with loading in files
    std::cout<<"Create Output File: ";
    TFile *output = Name_File(output_name); //read_in_files.h
    std::cout<<"Complete" <<std::endl <<"Load root files: ";
    TChain data("h10"); //Create TChain to be used. TTrees are h10
    /*
    if(comp == zero){//work on the farm
        loadChain(&data,"",file_num);//read_in-data.h
        work++;//variables.h
        which = 0;//denote which set //variables.h
    }
    */
    if(comp == "one"){ //Desktop computer in office
        loadChain(&data, "/home/mclauchlinc/Desktop/analysis/nick_convert_e16.txt", file_num);//read_in_data.h
        work++; //variables.h
        which = 1; //denote which data set //variables.h
    }
    if(comp == "two"){  //Mac Data set
        loadChain(&data, "e16_75.txt",file_num);//read_in_files.h;
        work++;//variables.h
        which = 2; //denote which set //variables.h
    }
    if(work == 1){ //Did the function loadChain run without halting everything?
        std::cout<<"Complete" <<std::endl;
    }
    else{
        std::cout<<"Error" <<std::endl;
    }

    //Outputs on what was input
    events = data.GetEntries(); //TTree.h //variables.h
    std::cout<<"You are reading data in from " <<local[which] <<std::endl;
    std::cout<<"Events loaded: " <<events <<std::endl;

    //Set Branches
    std::cout<< "Setting Branches: ";
    SetBranches(&data);//read_in_data.h
    std::cout<< "Complete" <<std::endl;

    //Make Histograms
    std::cout<< "Making Histograms: ";
    MakeHist();//histograms.h
    std::cout<<"Complete" <<std::endl;

    for(int i = 0; i< events ; i++)
    {
        //Update on the progress
       // cout<<"got into the loop?" <<endl;
        progress = (int) 100.0*(((double)i+1.0)/(double)events);
       cout <<"Progess Percent " <<progress <<"\r";

       p_pass = false;
       pip_pass = false;
       pim_pass = false;
       zero_pass = false;

        //Get info for event i
        data.GetEntry(i);
        Reassign(); //Converts to C++ data types variables.h

        Fill_eid(p[0], q[0], cx[0], cy[0], cz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], stat[0], etot[0], id[0]);
        //cout << "did electron things about to enter for loop" <<endl;
        for(int j = 1; j<gpart ; j++){
            Fill_Hadron(q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1], p[0], sc_t[sc[0]-1], sc_r[sc[0]-1], id[j]);
            //Missing Mass
                //Missing Mass 1 missing
            for(int k = 1; k<gpart ; k++){
                //Missing Mass pre
                MM_pi_val = MM_3_com(p[0],p[j],p[k],cx[0],cx[j],cx[k],cy[0],cy[j],cy[k],cz[0],cz[j],cz[k],me,mp,mpi);
                //Proton missing mass topology
                if(other_p_miss(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], j, k)){
                      MM_p_val = MM_3_com(p[0],p[j],p[k],cx[0],cx[j],cx[k],cy[0],cy[j],cy[k],cz[0],cz[j],cz[k],me,mpi,mpi);
                    Fill_MM(0,0,MM_p_val);
                    //Proton Missing Cut
                    if(MM_p2(MM_p_val)){
                        Fill_MM(0,1,MM_p_val);
                        p_pass = true;
                       // Fill_WQ2_ES(0,p[0],cx[0],cy[0],cz[0]);
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
                    //Fill_WQ2_ES(1,p[0],cx[0],cy[0],cz[0]);
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
                        //Fill_WQ2_ES(2,p[0],cx[0],cy[0],cz[0]);
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
                            //Fill_WQ2_ES(3,p[0],cx[0],cy[0],cz[0]);
                        }
                        else{
                            //Full topology anti 
                            Fill_MM(3,2,MM_4_com(p[0],p[j],p[k],p[l],cx[0],cx[j],cx[k],cx[l],cy[0],cy[j],cy[k],cy[l],cz[0],cz[j],cz[k],cz[l],me,mp,mpi,mpi));
                        }
                    }
                }
            }
            if(top_cross(zero_pass,pim_pass,pip_pass,p_pass)){
               // Fill_WQ2_ES(4,p[0],cx[0],cy[0],cz[0]);
            }
        }
        //cout<<endl;
    }

    std::cout<<"\nWrite: ";
    output->Write();
    std::cout<<"Complete \nClose: " <<std::endl;
    output->Close();
    std::cout<<"Complete" <<std::endl;

	return 0;
}
