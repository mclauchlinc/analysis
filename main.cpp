#include "headers.h" //Contains all the header files I need


using namespace std; //A standard space to be in for a c++ program
int main(int argc, char** argv){ //Main function that will return an integer. argc/v are for command line inputs
    std::cout<< "You have " <<argc <<" arguments" <<std::endl;
    

    //cout<<endl <<"This is a test for modulus" <<endl; 
    //cout<<"(4.25%0.5)= " <<(4.25%0.5) <<endl; 
    //cout<<"3%0.5= " <<3%0.5 <<endl;
    //cout<<

    int plate_separation = 0; 
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
            std::cout<<"Rerun this program. None of this will work now" <<std::endl;//\\\][[9\]]
        }
    }

    //Work with loading in files
    std::cout<<"Create Output File: ";
    TFile *output = Name_File(output_name); //read_in_files.h
    //output = Name_File(output_name);
    std::cout<<"Complete" <<std::endl <<"Load root files: ";
    TChain data("h10"); //Create TChain to be used. TTrees are h10
    TChain data_IN("h10");//Creat TChains for half wave plate configurations
    TChain data_OUT("h10");
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
        loadChain(&data, "e16_10_18_17_ntple.txt",file_num);//read_in_files.h;
        work++;//variables.h
        which = 2; //denote which set //variables.h
    }
    if(comp == "three"){  //Mac Data set
        cout<<endl<<"three?" <<endl;
        loadChain(&data, "Nick_skim_e16.txt",file_num);//read_in_files.h;
        work++;//variables.h
        which = 3; //denote which set //variables.h
    }
    if(comp == "three+"){
        cout<<endl<<"Three with Plate Separation" <<endl;
        loadChain(&data_IN,"NickSkim_e16_PlateIN.txt",file_num);
        loadChain(&data_OUT,"NickSkim_e16_PlateOUT.txt",file_num);
        work++; //variables.h
        which = 3; //denote which set
        plate_separation = 1; 
    }
    if(work == 1){ //Did the function loadChain run without halting everything?
        std::cout<<"Complete" <<std::endl;
    }
    else{
        std::cout<<"Error" <<std::endl;
    }

    if(plate_separation == 0){
        //Outputs on what was input
        events = data.GetEntries(); //TTree.h //variables.h
        std::cout<<"You have read in data from " <<local[which] <<std::endl;
        std::cout<<"Events loaded: " <<events <<std::endl;

        //Set Branches
        std::cout<< "Setting Branches: ";
        SetBranches(&data,which);//read_in_data.h
        std::cout<< "Complete" <<std::endl;
    }
    else{
        //Outputs on what was input
        eventsIN = data_IN.GetEntries(); //TTree.h //variables.h
        std::cout<<"You have read in data from " <<"Nick Skim Plate IN" <<std::endl;
        std::cout<<"Events loaded: " <<eventsIN <<std::endl;

        eventsOUT = data_OUT.GetEntries(); //TTree.h //variables.h
        std::cout<<"You have read in data from " <<"Nick Skim Plate OUT" <<std::endl;
        std::cout<<"Events loaded: " <<eventsOUT <<std::endl;

        //Set Branches
        std::cout<< "Setting Branches: ";
        SetBranches(&data_IN,which);//read_in_data.h
        SetBranches(&data_OUT,which);//read_in_data.h
        std::cout<< "Complete" <<std::endl;

    }
    
    //MakeDirectories(output);

    //Make Histograms
    std::cout<< "Making Histograms: ";
    MakeHist();//histograms.h
    MakeHist_fid_pdep();//Make momentum dependent fiducial histograms 4/17/19
    MakeHist_eac_corr1();//First step in electron angle correction
    //MakeHist_fid();//fiducial histograms.h
    std::cout<<"Complete" <<std::endl;

    std::cout<<"did it work?" <<endl;

    //For W variance in plots
    double W_var; 
    double Q2_var;

    int pos_h; 
    int neg_h;
    int pos_h_E;
    int neg_h_E;

    double theta_e;
    double cz_corr; 
    double theta_p;

    int s1l=50;
    int s2l=1050;
    int s3l=2050;
    int s1h=50;
    int s2h=1050;
    int s3h=2050;

    int looped; 
    int p_loop;
    int pip_loop;
    int pim_loop;
    int p_miss_loop;
    int pip_miss_loop;
    int pim_miss_loop;
    int zero_miss_loop;

    TLorentzVector p_mu_event;

    for(int plate = 0; plate < plate_separation+1 ; plate++){//If the half wave plate is relevant to what is happening this will help separate the two
        if(plate_separation = 1){
            switch(plate){
                case 0: events = eventsIN;
                        plate_stat = 1;
                        cout<<endl;
                break;
                case 1: events = eventsOUT;
                        plate_stat = -1;
                        cout<<endl;
                break;
            }
        }else{
            plate_stat = 0;
        }

        for(int i = 0; i< events ; i++)//Start of actual event loop 
        {

            //cout<<"Q_l says: " <<q_l_c <<" For event# " <<i <<endl;
            p_mu_event = p_mu;
            looped = 0; 
            p_loop = 0;
            pip_loop = 0;
            pim_loop = 0;

            p_miss_loop = 0;
            pim_miss_loop = 0;
            pip_miss_loop = 0;
            zero_miss_loop = 0;

            //Update on the progress
            // cout<<"got into the loop?" <<endl;
            progress = (int) 100.0*(((double)i+1.0)/(double)events);
            cout <<"Progess Percent " <<progress;
            if(plate_separation == 1){
            cout<<"|| " <<plates[plate];
            } 
            cout<<"\r";

           p_pass = false;
           pip_pass = false;
           pim_pass = false;
           zero_pass = false;
           p_pre = false;
           pip_pre = false;
           pim_pre = false;
           zero_pre = false;       

            //Get info for event i
            if(plate_separation == 1){
                switch(plate){
                    case 0: data_IN.GetEntry(i);
                    break;
                    case 1: data_OUT.GetEntry(i);
                    break;
                }
            }
            else{
                data.GetEntry(i);
            }
            if(which != 3){//Data types are different for data location 3
                Reassign(); //Converts to C++ data types variables.h
            }else{
                Reassign3();//
            }
            //cout<<endl <<"event class: " <<evntclas2 <<endl;
            e_helicity = event_helicity(evntclas2,plate_stat); //Assign Helicity to the event
            //cout<<"event helicity: " <<e_helicity <<endl;
            W_var = WP(0,p[0],cx[0],cy[0],cz[0]);
            Q2_var = Qsquared(0,p[0],cx[0],cy[0],cz[0]);
            if(e_helicity == -1){
                neg_h += 1;
            }
            if(e_helicity == 1){
                pos_h +=1;
            }
            //counts = counts +1;
            //Electron angle correction
            if(eid(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], cc_segm[cc[0]-1], nphe[cc[0]-1], cc_sect[cc[0]-1],1)){//eid.h
                if(W_var < 1.05 && W_var > 0.7){//Look at just elastic peak
                    theta_p = get_theta(cz[1]);
                    if(theta_p > 35){
                        //cout<<endl <<theta_p <<endl;
                        Fill_eac_corr1(energy_e16,theta_p,cx[0],cy[0],cz[0]);
                    }
                }
            }
            //Assign_Ele(&ele_ints, &ele_dob, p[0], q[0], cx[0], cy[0], cz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], stat[0], etot[0], cc_sect[cc[0]-1], cc_segm[cc[0]-1], nphe[cc[0]-1]);
            //Limit W and Q2 to be in the regime we actually care about for the analysis
            if(W_var > WminAna && W_var < WmaxAna && Q2_var > Q2minAna && Q2_var < Q2maxAna){
                Fill_MinCC(cc_sect[cc[0]-1],nphe[cc[0]-1],cc_segm[cc[0]-1],0);
                Fill_eid(W_var,p[0], q[0], cx[0], cy[0], cz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], stat[0], etot[0], id[0], cc_segm[cc[0]-1], nphe[cc[0]-1], cc_sect[cc[0]-1]);//partitions.h
                if(eid(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], cc_segm[cc[0]-1], nphe[cc[0]-1], cc_sect[cc[0]-1],5)){//eid.h
                    for(int j = 1; j<gpart ; j++){//Hadron/Proton loop
                        Fill_Hadron(q[j], W_var, p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1], p[0], sc_t[sc[0]-1], sc_r[sc[0]-1], cc[j], ec[j], etot[j], vx[j], vy[j], vz[j], id[j]);//partitions.h
                        //Missing Mass
                        for(int k = 1; k<gpart ; k++){//Pip Loop
                            for(int l = 0; l < gpart; l++){//Pim Loop
                                //Missing Mass for pion calculation
                                MM_pi_val = MM_3_com(p[0],p[j],p[l],cx[0],cx[j],cx[l],cy[0],cy[j],cy[l],cz[0],cz[j],cz[l],me,mp,mpi);//Looking for pi+ with proton and  pim
                                MM_pi2_val = MM_3_com(p[0],p[j],p[k],cx[0],cx[j],cx[k],cy[0],cy[j],cy[k],cz[0],cz[j],cz[k],me,mp,mpi);//Looking for pim with proton and pip
                                MM_pi3_val = MM_3_com(p[0],p[j],p[k],cx[0],cx[j],cx[k],cy[0],cy[j],cy[k],cz[0],cz[j],cz[k],me,mpi,mpi);
                                //Proton missing mass topology Brackets work
                                if(other_p_miss(cc_segm[cc[0]-1], cc_sect[cc[0]-1], nphe[cc[0]-1],p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1],  q[l], p[l], cx[l], cy[l], cz[l], dc[l], sc[l], stat[l], dc_stat[dc[l]-1], sc_t[sc[l]-1], sc_r[sc[l]-1], cc[l], ec[l], etot[l], vx[l], vy[l], vz[l], k, l)){
                                      //cout<<endl <<"other p miss pass" <<endl;
                                      MM_p_val = MM_3_com(p[0],p[k],p[l],cx[0],cx[k],cx[l],cy[0],cy[k],cy[l],cz[0],cz[k],cz[l],me,mpi,mpi);
                                      MM_p_pass = MM_p_val;
                                      p_pre = true;
                                    Fill_MM(0,0,W_var,MM_p_val);
                                    //Proton Missing Cut
                                    if(MM_p2(MM_p_val) && p_miss_loop ==0){
                                        pip_loop++;
                                        pim_loop++;
                                        p_miss_loop++;

                                        Fill_MM(0,1,W_var,MM_p_val);
                                        p_pass = true;
                                        Fill_WQ2(0,5,1,p[0],cx[0],cy[0],cz[0]);
                                        ele_mu = Make_4Vector(p[0],cx[0],cy[0],cz[0],me);
                                        pip_mu = Make_4Vector(p[k],cx[k],cy[k],cz[k],mpi);
                                        pim_mu = Make_4Vector(p[l],cx[l],cy[l],cz[l],mpi);
                                        pro_mu = k_mu_e16 + p_mu - ele_mu - pro_mu - pim_mu;
                                        if(pip_loop == 1){
                                            Fill_dt(W_var,1,7,sc[k],p[k], p[0], sc_r[sc[k]-1], sc_r[sc[0]-1], sc_t[sc[k]-1], sc_t[sc[0]-1]);
                                        }
                                        if(pim_loop == 1){
                                            Fill_dt(W_var,2,7,sc[l],p[l], p[0], sc_r[sc[l]-1], sc_r[sc[0]-1], sc_t[sc[l]-1], sc_t[sc[0]-1]);
                                        }
                                    }
                                     //Proton Missing Anti
                                    else{
                                        Fill_MM(0,2,W_var,MM_p_val);
                                    }
                                }
                                //Pi+ missing mass topology bracket work
                                if(other_pip_miss(cc_segm[cc[0]-1], cc_sect[cc[0]-1], nphe[cc[0]-1],p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[l], p[l], cx[l], cy[l], cz[l], dc[l], sc[l], stat[l], dc_stat[dc[l]-1], sc_t[sc[l]-1], sc_r[sc[l]-1], cc[l], ec[l], etot[l], vx[l], vy[l], vz[l], j, l)){
                                   // cout<<endl <<"other pip miss pass" <<endl;
                                    Fill_MM(1,0,W_var,MM_pi_val);
                                    pip_pre = true;
                                    MM_pip_pass = MM_pi_val;
                                    //Pi+ Missing Cut
                                    if(MM_pi2(MM_pi_val) && pip_miss_loop == 0){
                                        Fill_MM(1,1,W_var,MM_pi_val);
                                        pip_miss_loop++;
                                        looped++;
                                        p_loop++;
                                        pim_loop++;
                                        pip_pass = true;
                                        Fill_WQ2(0,5,2,p[0],cx[0],cy[0],cz[0]);
                                        if(pim_loop == 1){
                                            Fill_dt(W_var,2,7,sc[l],p[l], p[0], sc_r[sc[l]-1], sc_r[sc[0]-1], sc_t[sc[l]-1], sc_t[sc[0]-1]);
                                        }
                                        if(p_loop == 1){
                                            Fill_dt(W_var,0,7,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                                        }
                                            if(p_pass){
                                                pro_mu = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                                            }
                                            else{
                                                ele_mu = Make_4Vector(p[0],cx[0],cy[0],cz[0],me);
                                                pro_mu = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                                                pim_mu = Make_4Vector(p[l],cx[l],cy[l],cz[l],mpi);
                                                pip_mu = k_mu_e16 + p_mu - ele_mu - pro_mu - pim_mu;
                                            }
                                    }                
                                    //Pi+ Missing Anti
                                    else{
                                        Fill_MM(1,2,W_var,MM_pi_val);
                                    }
                                }
                                //Pi- missing mass topology bracket work
                                if(other_pim_miss(cc_segm[cc[0]-1], cc_sect[cc[0]-1], nphe[cc[0]-1],p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], j, k)){
                                     Fill_MM(2,0,W_var,MM_pi_val);
                                     Fill_dt_MM( MM_pi_val, W_var, 0, 1, 2, sc[j], p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                                     Fill_dt_MM( MM_pi_val, W_var, 1, 1, 2, sc[k], p[k], p[0], sc_r[sc[k]-1], sc_r[sc[0]-1], sc_t[sc[k]-1], sc_t[sc[0]-1]);
                                     pim_pre = true;
                                     MM_pim_pass = MM_pi2_val;
                                    //Pi- Missing Cut
                                    if(MM_pi2(MM_pi2_val) && pim_miss_loop == 0 ){
                                        Fill_MM(2,1,W_var,MM_pi2_val);
                                        pim_miss_loop++;
                                        pim_pass = true;
                                        looped++;
                                        p_loop++;
                                        pip_loop++;
                                        Fill_WQ2(0,5,2,p[0],cx[0],cy[0],cz[0]);
                                        if(pip_loop == 1){
                                            Fill_dt(W_var,1,7,sc[k],p[k], p[0], sc_r[sc[k]-1], sc_r[sc[0]-1], sc_t[sc[k]-1], sc_t[sc[0]-1]);
                                        }
                                        if(p_loop == 1){
                                            Fill_dt(W_var,0,7,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                                        }
                                        if(p_pass && !pip_pass){
                                            pro_mu = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                                        }
                                        if(pip_pass && !p_pass){
                                            pip_mu = Make_4Vector(p[k], cx[k],cy[k], cz[k], mpi);
                                        }
                                        if(!p_pass && !pip_pass){
                                            ele_mu = Make_4Vector(p[0],cx[0],cy[0],cz[0],me);
                                            pro_mu = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                                            pip_mu = Make_4Vector(p[k],cx[k],cy[k],cz[k],mpi);
                                            pim_mu = k_mu_e16 + p_mu - ele_mu - pro_mu - pim_mu;
                                        }
                                    }
                                    //Pi- Missing Anti
                                    else{
                                        Fill_MM(2,2,W_var,MM_pi_val);
                                    }
                                }
                                //Full Topology Pre
                                MM_full = MM_4_com(p[0],p[j],p[k],p[l],cx[0],cx[j],cx[k],cx[l],cy[0],cy[j],cy[k],cy[l],cz[0],cz[j],cz[k],cz[l],me,mp,mpi,mpi);
                                if(other_zero_miss(cc_segm[cc[0]-1], cc_sect[cc[0]-1], nphe[cc[0]-1],p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], q[l], p[l], cx[l], cy[l], cz[l], dc[l], sc[l], stat[l], dc_stat[dc[l]-1], sc_t[sc[l]-1], sc_r[sc[l]-1], cc[l], ec[l], etot[l], vx[l], vy[l], vz[l], j, k, l)){
                                    Fill_MM(3,0,W_var,MM_full);
                                    MM_full_pass = MM_full;
                                    zero_pre = true;
                                    if(MM_all2(MM_full) && zero_miss_loop == 0){
                                        //Full Topology cut
                                        Fill_MM(3,1,W_var,MM_full);
                                        zero_pass = true;
                                        Fill_WQ2(0,5,3,p[0],cx[0],cy[0],cz[0]);
                                        zero_miss_loop++;
                                        p_loop++;
                                        pip_loop++;
                                        pim_loop++;
                                        looped++;
                                        if(pip_loop == 1){
                                            Fill_dt(W_var,1,7,sc[k],p[k], p[0], sc_r[sc[k]-1], sc_r[sc[0]-1], sc_t[sc[k]-1], sc_t[sc[0]-1]);
                                        }
                                        if(p_loop == 1){
                                            Fill_dt(W_var,0,7,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                                        }
                                        if(pim_loop == 1){
                                            Fill_dt(W_var,2,7,sc[l],p[l], p[0], sc_r[sc[l]-1], sc_r[sc[0]-1], sc_t[sc[l]-1], sc_t[sc[0]-1]);
                                        }
                                        if(p_pass && !pip_pass && !pim_pass){
                                            pro_mu = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                                        }
                                        if(pip_pass && !p_pass && !pim_pass){
                                            pip_mu = Make_4Vector(p[k], cx[k],cy[k], cz[k], mpi);
                                        }
                                        if(!pip_pass && !p_pass && pim_pass){
                                            pim_mu = Make_4Vector(p[l], cx[l],cy[l], cz[l], mpi);
                                        }
                                        if(!p_pass && !pip_pass && !pim_pass){
                                            ele_mu = Make_4Vector(p[0],cx[0],cy[0],cz[0],me);
                                            pro_mu = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                                            pip_mu = Make_4Vector(p[k],cx[k],cy[k],cz[k],mpi);
                                            pim_mu = Make_4Vector(p[l],cx[l],cy[l],cz[l],mpi);
                                        }
                                        //Fill_dt(W_var,0,7,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                                        //Fill_dt(W_var,1,7,sc[k],p[k], p[0], sc_r[sc[k]-1], sc_r[sc[0]-1], sc_t[sc[k]-1], sc_t[sc[0]-1]);
                                        //Fill_dt(W_var,2,7,sc[l],p[l], p[0], sc_r[sc[l]-1], sc_r[sc[0]-1], sc_t[sc[l]-1], sc_t[sc[0]-1]);
                                    }
                                }//if other_zero_miss   
                                /*if(!p_pass && !pim_pass && zero_pass){
                                    Fill_dt(W_var,1,7,sc[k],p[k], p[0], sc_r[sc[k]-1], sc_r[sc[0]-1], sc_t[sc[k]-1], sc_t[sc[0]-1]);
                                }
                                if(!p_pass && !pip_pass && zero_pass){
                                    Fill_dt(W_var,2,7,sc[l],p[l], p[0], sc_r[sc[l]-1], sc_r[sc[0]-1], sc_t[sc[l]-1], sc_t[sc[0]-1]);
                                }
                                if(!pip_pass && !pim_pass && zero_pass){
                                    Fill_dt(W_var,0,7,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                                }*/
                            }//l loop 
                        }//k loop ends
                        //Cross MM plots
                        if(top_cross(zero_pass,pim_pass,pip_pass,p_pass)){
                            Fill_WQ2(0,5,5,p[0],cx[0],cy[0],cz[0]);
                        }
                        if(zero_pre && pim_pre){
                           // cout<< endl <<"boop1" <<endl;
                            Fill_MM_Cross(5, W_var, MM_pim_pass,MM_full_pass);
                        }
                        if(zero_pre && pip_pre){
                           // cout<< endl <<"boop2" <<endl;
                            Fill_MM_Cross(4, W_var, MM_pip_pass,MM_full_pass);
                        }
                        if(zero_pre && p_pre){
                            //cout<< endl <<"boop3" <<endl;
                            Fill_MM_Cross(2, W_var, MM_p_pass,MM_full_pass);
                        }
                        if(p_pre && pim_pre){
                           // cout<< endl <<"boop4" <<endl;
                            Fill_MM_Cross(1, W_var, MM_p_pass,MM_pim_pass);
                        }
                        if(p_pre && pip_pre){
                            //cout<< endl <<"boop5" <<endl;
                            Fill_MM_Cross(0, W_var, MM_p_pass,MM_pip_pass);
                        }
                        if(pip_pre && pim_pre){
                            //cout<< endl <<"boop6" <<endl;
                            Fill_MM_Cross(3, W_var,MM_pip_pass,MM_pim_pass);//
                        }
                    }//j loop ends
                }//eid if statement ends
            }
            
            //This is the complete event selection. Now do things with the four vectors 
            if(p_pass || pip_pass || pim_pass || zero_pass){
                if(e_helicity == -1){
                    neg_h_E =+1;     
                }
                if(e_helicity == 1){
                    pos_h_E +=1; 
                }
                event_W = WP(0,p[0],cx[0],cy[0],cz[0]);
                event_Q2 = Qsquared(0,p[0],cx[0],cy[0],cz[0]);
                MM_p_pip = MM_2(pro_mu,pip_mu);
                MM_p_pim = MM_2(pro_mu,pim_mu);
                MM_pip_pim = MM_2(pip_mu,pim_mu);
                //Convert to COM frame
                    //First do with respect to gamma/proton COM frame
                COM_gp(0,ele_mu,pro_mu,pip_mu,pim_mu,p_mu_event);
                //Extract scattering angle in center of mass now that
                theta_p_pip = theta_com((pim_mu));
                theta_p_pim = theta_com((pip_mu));
                theta_pip_pim = theta_com((pro_mu));
                if(Qbinning_check(event_Q2) && Wbinning_check(event_W)){//yield.h
                    //cout<<" __ and we passed the check";
                    Qbin_now = Q2binning(event_Q2);
                    Wbin_now = Wbinning(event_W);
                    //Top Row of MM
                    if(MMbinning_check(0,MM_p_pip)){//yield.h
                        y[0][Qbin_now][Wbin_now][MM_stuff_binning(0,MM_p_pip)][0][0][3] += 1;
                        y[0][Qbin_now][Wbin_now][MM_stuff_binning(0,MM_p_pip)][0][0][e_helicity+1] += 1;
                        y[0][Qbin_now][Wbin_now][MM_stuff_binning(0,MM_p_pip)][0][0][4] += e_helicity;
                    }
                    if(MMbinning_check(1,MM_p_pim)){//yield.h
                        y[1][Qbin_now][Wbin_now][MM_stuff_binning(1,MM_p_pim)][0][0][3] += 1;
                        y[1][Qbin_now][Wbin_now][MM_stuff_binning(1,MM_p_pim)][0][0][e_helicity+1] += 1;
                        y[1][Qbin_now][Wbin_now][MM_stuff_binning(1,MM_p_pim)][0][0][4] += e_helicity;
                    }
                    if(MMbinning_check(2,MM_pip_pim)){//yield.h
                        y[2][Qbin_now][Wbin_now][MM_stuff_binning(2,MM_pip_pim)][0][0][3] += 1;
                        y[2][Qbin_now][Wbin_now][MM_stuff_binning(2,MM_pip_pim)][0][0][e_helicity+1] += 1;
                        y[2][Qbin_now][Wbin_now][MM_stuff_binning(2,MM_pip_pim)][0][0][4] += e_helicity;
                    }
                    //Second row
                    y[3][Qbin_now][Wbin_now][0][theta_binning(theta_p_pip)][0][3] += 1;
                    y[4][Qbin_now][Wbin_now][0][theta_binning(theta_p_pim)][0][3] += 1;
                    y[5][Qbin_now][Wbin_now][0][theta_binning(theta_pip_pim)][0][3] += 1;
                    y[3][Qbin_now][Wbin_now][0][theta_binning(theta_p_pip)][0][e_helicity+1] += 1;
                    y[4][Qbin_now][Wbin_now][0][theta_binning(theta_p_pim)][0][e_helicity+1] += 1;
                    y[5][Qbin_now][Wbin_now][0][theta_binning(theta_pip_pim)][0][e_helicity+1] += 1;
                    y[3][Qbin_now][Wbin_now][0][theta_binning(theta_p_pip)][0][4] += e_helicity;
                    y[4][Qbin_now][Wbin_now][0][theta_binning(theta_p_pim)][0][4] += e_helicity;
                    y[5][Qbin_now][Wbin_now][0][theta_binning(theta_pip_pim)][0][4] += e_helicity;
                    //Third Row
                    //cout<<endl <<"Alpha angles" <<endl <<"[p',pip][p,pim]: " <<alpha(0,p_mu_event,pro_mu,pip_mu,pim_mu);
                    //cout <<endl <<"[pip,pim][p',p]: " <<alpha(1,p_mu_event,pro_mu,pip_mu,pim_mu);
                    //cout <<endl <<"[p',pim][p,pip]: " <<alpha(2,p_mu_event,pro_mu,pip_mu,pim_mu);
                    y[6][Qbin_now][Wbin_now][0][0][alpha_binning(alpha(0,p_mu_event,pro_mu,pip_mu,pim_mu))][3] +=1;
                    //cout<<endl <<"alpha 0: " <<alpha(0,p_mu_event,pro_mu,pip_mu,pim_mu) <<" binning: " <<alpha_binning(alpha(0,p_mu_event,pro_mu,pip_mu,pim_mu));
                    y[7][Qbin_now][Wbin_now][0][0][alpha_binning(alpha(1,p_mu_event,pro_mu,pip_mu,pim_mu))][3] +=1;
                    y[8][Qbin_now][Wbin_now][0][0][alpha_binning(alpha(2,p_mu_event,pro_mu,pip_mu,pim_mu))][3] +=1;
                    //cout<<endl <<"alpha 1: " <<alpha(1,p_mu_event,pro_mu,pip_mu,pim_mu) <<" binning: " <<alpha_binning(alpha(1,p_mu_event,pro_mu,pip_mu,pim_mu));
                    //cout<<endl <<"alpha 2: " <<alpha(2,p_mu_event,pro_mu,pip_mu,pim_mu) <<" binning: " <<alpha_binning(alpha(2,p_mu_event,pro_mu,pip_mu,pim_mu)) <<endl;
                    y[6][Qbin_now][Wbin_now][0][0][alpha_binning(alpha(0,p_mu_event,pro_mu,pip_mu,pim_mu))][e_helicity+1] +=1;
                    //cout<<endl <<"alpha 0: " <<alpha(0,p_mu_event,pro_mu,pip_mu,pim_mu) <<" binning: " <<alpha_binning(alpha(0,p_mu_event,pro_mu,pip_mu,pim_mu));
                    y[7][Qbin_now][Wbin_now][0][0][alpha_binning(alpha(1,p_mu_event,pro_mu,pip_mu,pim_mu))][e_helicity+1] +=1;
                    y[8][Qbin_now][Wbin_now][0][0][alpha_binning(alpha(2,p_mu_event,pro_mu,pip_mu,pim_mu))][e_helicity+1] +=1;
                    y[6][Qbin_now][Wbin_now][0][0][alpha_binning(alpha(0,p_mu_event,pro_mu,pip_mu,pim_mu))][4] += e_helicity;
                    //cout<<endl <<"alpha 0: " <<alpha(0,p_mu_event,pro_mu,pip_mu,pim_mu) <<" binning: " <<alpha_binning(alpha(0,p_mu_event,pro_mu,pip_mu,pim_mu));
                    y[7][Qbin_now][Wbin_now][0][0][alpha_binning(alpha(1,p_mu_event,pro_mu,pip_mu,pim_mu))][4] += e_helicity;
                    y[8][Qbin_now][Wbin_now][0][0][alpha_binning(alpha(2,p_mu_event,pro_mu,pip_mu,pim_mu))][4] += e_helicity;

                }
                /*
                for(int r = 0; r<3 ; r++){
                    //cout<< endl <<"alpha plot?";
                    alph = alpha(r,ele_mu,pro_mu,pip_mu,pim_mu);//physics.h
                    switch (r){
                    case 0: 
                    MM_event = MM_p_pip;
                    theta_event = theta_p_pip;
                    break;
                    case 1:
                    MM_event = MM_p_pim;
                    theta_event = theta_p_pim;
                    break;
                    case 2:
                    MM_event = MM_pip_pim;
                    theta_event = theta_pip_pim;
                    break;
                    }

                    //cout<< endl <<alph <<endl;
                    //Fill_Alpha(r,alph);
                    //Fill_MM_par(r,MM_event);
                    //Fill_theta_par(r,theta_event);
                    

                    //Q2 Bins
                    /*for(int u = 0; u< 16 ; u++ ){
                        if(event_Q2 < (Q2min+(u*(Q2res/2))) && event_Q2 > (Q2min-(u*(Q2res/2)))){
                            //W bins
                            for(int e = 0; e < 8 ; e++){
                                //W Binning
                                if(event_W < (Wmin+(e*(Wres/2))) && event_W > (Wmin-(e*(Wres/2)))){
                                    Fill_Alpha_bin(r,e,u,alph);
                                    Fill_MM_bin(r,e,u,MM_event);
                                    Fill_theta_bin(r,e,u,theta_event);
                                }
                            }
                        }
                    }//****
                }
            }*/ //}

            }
        }

        //Now for the graphing o stuff
        //Assign x's for 3x3 Plots 
        for(int h = 0; h<5; h++){//Over all the different Helicity bins
            for(int qq = 0; qq<6; qq++){
                for(int ww = 0; ww<30; ww++){ //W Qsquared binning
                    for(int spice = 0; spice <3; spice++){ //Particle Binning
                        //cout<<endl <<"x for MM binning " <<qq <<" " <<ww;
                        for(int rage = 0; rage < 13; rage++){ //
                            x[spice][qq][ww][rage][0][0][h]=MM_bincenter(spice,rage);//yield.h
                            xc_y[spice][qq][ww][rage][0][0][h] = y[spice][qq][ww][rage][0][0][h]*(1.0/L_e16)*cm2_to_mbarn;//Create a differential cross section
                            //cout<<endl <<"MM bin: " <<rage <<" is: "<<x[spice][qq][ww][rage][0][0] <<endl;
                        }
                        //cout<<endl <<"x for theta binning " <<qq <<" " <<ww;
                        for(int against = 0; against < 10; against++){
                            x[spice+3][qq][ww][0][against][0][h]=th_bincenter(against);//yield.h
                            x[spice+6][qq][ww][0][0][against][h]=al_bincenter(against);//yield.h
                           // cout<<endl <<"theta bin: " <<against <<" is: "<<x[spice+3][qq][ww][0][against][0] <<endl;
                            //cout<<endl <<"alpha bin: " <<against <<" is: "<<x[spice+6][qq][ww][0][0][against] <<endl;
                            xc_y[spice+6][qq][ww][0][0][against][h] = y[spice+6][qq][ww][0][0][against][h]*(1.0/L_e16)*cm2_to_mbarn;
                            xc_y[spice+6][qq][ww][0][against][0][h] = y[spice+6][qq][ww][0][against][0][h]*(1.0/L_e16)*cm2_to_mbarn;
                        }
                    }

                }
            }
        }
    }
    cout<<endl <<"pre graph" <<endl;
    //Graph_yield1(x,y,output);//yield.h//commented out 5/28/19
    cout<<endl <<"  post graph";    

    cout<<endl <<"positive helicity events: " <<pos_h <<endl <<"negative helicity events: " <<neg_h;
    cout<<endl <<"positive helicity events for channel : " <<pos_h <<endl <<"negative helicity events for channel: " <<neg_h;
    
    //momentum correction fitting
    //Angle step 1
    for(int th_e = 0; th_e < num_theta_e_bins ; th_e++){
        for(int ph_e = 0; ph_e < num_phi_e_bins; ph_e++){
            for(int secto = 0; secto < 6 ; secto++){
                fit_gaus_const(eac_1[th_e][ph_e][secto],-0.2,0.2,-0.05,0.02,5.0,0.1,eac1_pars[th_e][ph_e][secto][0],eac1_pars[th_e][ph_e][secto][1],eac1_pars[th_e][ph_e][secto][2],eac1_pars[th_e][ph_e][secto][3],eac1_pars[th_e][ph_e][secto][4],eac1_pars[th_e][ph_e][secto][5],eac1_pars[th_e][ph_e][secto][6],eac1_pars[th_e][ph_e][secto][7]);
            }
        }
    }
    //fit_gaus_const(eac_1[])


    /*
    //Fitting
    fit_b_wig_mult(MM_hist[0][0], 5, 0.9,0.97,p_center,p_sig,100.0,parameters[0],parameters[1],parameters[2],parameters[3],parameters[4],parameters[5]);
    cout<<endl <<"Proton Mass: " <<parameters[0] <<" error: " <<parameters[3];
    cout<<endl <<"Proton Gamma: " <<parameters[1] <<" error: " <<parameters[4];
    fit_b_wig_mult(MM_hist[1][0], 5, 0.109,0.187,pip_center,pip_sig,100.0,parameters[0],parameters[1],parameters[2],parameters[3],parameters[4],parameters[5]);
    cout<<endl <<"Pi+ Mass: " <<parameters[0] <<" error: " <<parameters[3];
    cout<<endl <<"Pi+ Gamma: " <<parameters[1] <<" error: " <<parameters[4];
    fit_b_wig_mult(MM_hist[2][0], 5, 0.093,0.190,pip_center,pip_sig,100.0,parameters[0],parameters[1],parameters[2],parameters[3],parameters[4],parameters[5]);
    cout<<endl <<"Pi- Mass: " <<parameters[0] <<" error: " <<parameters[3];
    cout<<endl <<"Pi- Gamma: " <<parameters[1] <<" error: " <<parameters[4];
    fit_b_wig_mult(MM_hist[3][0], 5, -0.05,0.05,pip_center,pip_sig,100.0,parameters[0],parameters[1],parameters[2],parameters[3],parameters[4],parameters[5]);
    cout<<endl <<"Zero Mass: " <<parameters[0] <<" error: " <<parameters[3];
    cout<<endl <<"Zero Gamma: " <<parameters[1] <<" error: " <<parameters[4];
    */
    //MM_hist[1][0].Fit("gaus");

    //Fitting Min CC Plots
    //TH1D* hist,int t, double lowb, double upb, double m0, double gamma0, double max, double &par1, double &par2, double &par3, double &err1, double &err2, double &err3, double m02, double gamma02, double max2, double &par12, double &par22, double &par32, double &err12, double &err22, double &err32
   /* for(int seggie = 0; seggie <18; seggie++){
        for(int se = 0; se <6; se++){
        //Sector //Segment //Cuts {none,sf,e fiducial,both} //left,coincident,right,all
        fit_gaus_mult(cc_min_hist[se][seggie][3][3],1,80.0,200.0,100.0,100.0,2000.0,parameters[0],parameters[1],parameters[2],parameters[3],parameters[4],parameters[5]);
        //fit_gaus_mult_2(cc_min_hist[se][seggie][3][3],1,3.0,200.0,100.0,100.0,2000.0,parameters[0],parameters[1],parameters[2],parameters[3],parameters[4],parameters[5],10.0,20.0,6000.0,parameters2[0],parameters2[1],parameters2[2],parameters2[3],parameters2[4],parameters2[5]);
            for(int par=0; par <3; par++){
                //cout<<"Par" <<par <<": " <<parameters[0] <<" Error" <<par <<": " <<parameters[par+3] <<endl;
                //cout<<"Parp" <<par <<": " <<parameters2[0] <<" Errorp" <<par <<": " <<parameters2[par+3] <<endl;
            }
        }
    }*/
    
    std::cout<<"\nWrite: ";

    //output->Write();
    /*
    Write_fid(output);
    Write_WQ2(output);
    Write_sf(output);
    Write_dt(output);
    Write_MM(output);*/
    //Write_MM_Cross(output);//commented out 4/17/19
    //Write_dt_MM(output);
    //Write_dt_pe(output);//commented out 4/17/19
    //Write_MinCC(output);//commented out 4/17/19
   // Write_fid_pdep(output); commented out 5/28/19
    Write_eac1(output);
    

    std::cout<<"Complete \nClose: ";
    output->Close();
    std::cout<<"Complete" <<std::endl;

	return 0;
}
