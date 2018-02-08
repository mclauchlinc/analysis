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
            std::cout<<"Rerun this program. None of this will work now" <<std::endl;//\\\][[9\]]
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
        loadChain(&data, "e16_10_18_17_ntple.txt",file_num);//read_in_files.h;
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
    std::cout<<"You have read in data from " <<local[which] <<std::endl;
    std::cout<<"Events loaded: " <<events <<std::endl;

    //Set Branches
    std::cout<< "Setting Branches: ";
    SetBranches(&data);//read_in_data.h
    std::cout<< "Complete" <<std::endl;

    //Make Histograms
    std::cout<< "Making Histograms: ";
    MakeHist();//histograms.h
    std::cout<<"Complete" <<std::endl;

    //For W variance in plots
    double W_var; 

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
       p_pre = false;
       pip_pre = false;
       pim_pre = false;
       zero_pre = false;       

        //Get info for event i
        data.GetEntry(i);
        Reassign(); //Converts to C++ data types variables.h



        Fill_eid(p[0], q[0], cx[0], cy[0], cz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], stat[0], etot[0], id[0]);
        //cout << "did electron things about to enter for loop" <<endl;
        for(int j = 1; j<gpart ; j++){
            // double p, int q, double cx, double cy, double cz, double vx, double vy, double vz, int dc, int cc, int ec, int sc, int dc_stat, double etot, int stat, int level
            if(eid(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], 4)){//added 12/19
                W_var = WP(0,p[0],cx[0],cy[0],cz[0]);
                Fill_Hadron(q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1], p[0], sc_t[sc[0]-1], sc_r[sc[0]-1], cc[j], ec[j], etot[j], vx[j], vy[j], vz[j], id[j]);
                //Missing Mass
                    //Missing Mass 1 missing
                for(int k = 1; k<gpart ; k++){
                    //Missing Mass for pion calculation
                    MM_pi_val = MM_3_com(p[0],p[j],p[k],cx[0],cx[j],cx[k],cy[0],cy[j],cy[k],cz[0],cz[j],cz[k],me,mp,mpi);
                    MM_pi2_val = MM_3_com(p[0],p[j],p[k],cx[0],cx[j],cx[k],cy[0],cy[j],cy[k],cz[0],cz[j],cz[k],me,mpi,mp);
                    MM_pi3_val = MM_3_com(p[0],p[j],p[k],cx[0],cx[j],cx[k],cy[0],cy[j],cy[k],cz[0],cz[j],cz[k],me,mpi,mpi);
                    //Proton missing mass topology
                    if(other_p_miss(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], cc[k], ec[k], etot[k], vx[k], vy[k], vz[k], j, k)){
                          MM_p_val = MM_3_com(p[0],p[j],p[k],cx[0],cx[j],cx[k],cy[0],cy[j],cy[k],cz[0],cz[j],cz[k],me,mpi,mpi);
                          MM_p_pass = MM_p_val;
                          p_pre = true;
                        Fill_MM(0,0,MM_p_val);
                        Fill_MM_Wall(0,W_var,MM_p_val);//*******
                        
                        //Proton Missing Cut
                        if(MM_p2(MM_p_val)){
                           // cout<< endl <<"p_pass";
                            Fill_MM(0,1,MM_p_val);
                            p_pass = true;
                            Fill_WQ2_ES(0,p[0],cx[0],cy[0],cz[0]);
                            ele_mu = Make_4Vector(p[0],cx[0],cy[0],cz[0],me);
                            pip_mu = Make_4Vector(p[j],cx[j],cy[j],cz[j],mpi);
                            pim_mu = Make_4Vector(p[k],cx[k],cy[k],cz[k],mpi);
                            pro_mu = k_mu_e16 + p_mu - ele_mu - pro_mu - pim_mu;
                        }
                         //Proton Missing Anti
                        else{
                            Fill_MM(0,2,MM_p_val);
                        }
                    }
                    //Pi+ missing mass topology
                    if(other_pip_miss(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], cc[k], ec[k], etot[k], vx[k], vy[k], vz[k], j, k)){
                        Fill_MM(1,0,MM_pi_val);
                        Fill_MM_Wall(1,W_var,MM_pi_val);//*********
                        pip_pre = true;
                        MM_pip_pass = MM_pi_val;
                        //Pi+ Missing Cut
                        if(MM_pi2(MM_pi_val)){
                        Fill_MM(1,1,MM_pi_val);
                        pip_pass = true;
                        Fill_WQ2_ES(1,p[0],cx[0],cy[0],cz[0]);
                            if(p_pass){
                                //cout<< endl<< "p_pass && pip_pass";
                                pro_mu = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                            }
                            else{
                                //cout<< endl <<"pip_pass";
                                ele_mu = Make_4Vector(p[0],cx[0],cy[0],cz[0],me);
                                pro_mu = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                                pim_mu = Make_4Vector(p[k],cx[k],cy[k],cz[k],mpi);
                                pip_mu = k_mu_e16 + p_mu - ele_mu - pro_mu - pim_mu;
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
                         
                         //W variance of the PIM MM plots
                         Fill_MM_Wall(2,W_var,MM_pi_val);//********
                         //Fill_MMpim_Mall(0,W_var,MM_pi2_val);
                         //Fill_MMpim_Mall(1,W_var,MM_pi3_val);
                         //Fill_MMpimM(0,MM_pi2_val);
                         //Fill_MMpimM(1,MM_pi3_val);

                         pim_pre = true;
                         MM_pim_pass = MM_pi_val;
                        //Pi- Missing Cut
                        if(MM_pi2(MM_pi_val)){
                            Fill_MM(2,1,MM_pi_val);
                            pim_pass = true;
                            Fill_WQ2_ES(2,p[0],cx[0],cy[0],cz[0]);
                            if(p_pass && !pip_pass){
                               // cout<<endl <<"p_pass && pim_pass";
                                pro_mu = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                            }
                            if(pip_pass && !p_pass){
                                //cout<<endl <<"pip_pass && pim_pass";
                                pip_mu = Make_4Vector(p[k], cx[k],cy[k], cz[k], mpi);
                            }
                            if(!p_pass && !pip_pass){
                               // cout<< endl <<"pim_pass";
                                ele_mu = Make_4Vector(p[0],cx[0],cy[0],cz[0],me);
                                pro_mu = Make_4Vector(p[j],cx[j],cy[j],cz[j],mp);
                                pip_mu = Make_4Vector(p[k],cx[k],cy[k],cz[k],mpi);
                                pim_mu = k_mu_e16 + p_mu - ele_mu - pro_mu - pim_mu;
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
                        if(other_zero_miss(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], q[l], p[l], cx[l], cy[l], cz[l], dc[l], sc[l], stat[l], dc_stat[dc[l]-1], sc_t[sc[l]-1], sc_r[sc[l]-1], cc[l], ec[l], etot[l], vx[l], vy[l], vz[l], j, k, l)){
                            Fill_MM(3,0,MM_full);
                            MM_full_pass = MM_full;
                            zero_pre = true;
                            if(MM_all2(MM_full)){
                                //Full Topology cut
                                Fill_MM(3,1,MM_full);
                                zero_pass = true;
                                Fill_WQ2_ES(3,p[0],cx[0],cy[0],cz[0]);
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
                if(zero_pre && pim_pre){
                   // cout<< endl <<"boop1" <<endl;
                    Fill_MM_Cross(5, MM_pim_pass,MM_full_pass);
                }
                if(zero_pre && pip_pre){
                   // cout<< endl <<"boop2" <<endl;
                    Fill_MM_Cross(4, MM_pip_pass,MM_full_pass);
                }
                if(zero_pre && p_pre){
                    //cout<< endl <<"boop3" <<endl;
                    Fill_MM_Cross(2, MM_p_pass,MM_full_pass);
                }
                if(p_pre && pim_pre){
                   // cout<< endl <<"boop4" <<endl;
                    Fill_MM_Cross(1, MM_p_pass,MM_pim_pass);
                }
                if(p_pre && pip_pre){
                    //cout<< endl <<"boop5" <<endl;
                    Fill_MM_Cross(0, MM_p_pass,MM_pip_pass);
                }
                if(pip_pre && pim_pre){
                    //cout<< endl <<"boop6" <<endl;
                    Fill_MM_Cross(3, MM_pip_pass,MM_pim_pass);//
                }
            }
        }
        //cout<<endl;
        //This is the complete event selection. Now do things with the four vectors 
        if(p_pass || pip_pass || pim_pass || zero_pass){
            event_W = WP(0,p[0],cx[0],cy[0],cz[0]);
            event_Q2 = Qsquared(0,p[0],cx[0],cy[0],cz[0]);
            MM_p_pip = MM_2(pro_mu,pip_mu);
            MM_p_pim = MM_2(pro_mu,pim_mu);
            MM_pip_pim = MM_2(pip_mu,pim_mu);
            //Convert to COM frame
                //First do with respect to gamma/proton COM frame
            COM_gp(0,ele_mu,pro_mu,pip_mu,pim_mu);
            theta_p_pip = theta_com((pro_mu+pip_mu));
            theta_p_pim = theta_com((pro_mu+pim_mu));
            theta_pip_pim = theta_com((pip_mu+pim_mu));
            for(int r = 0; r<3 ; r++){
                //cout<< endl <<"alpha plot?";
                alph = alpha(r,ele_mu,pro_mu,pip_mu,pim_mu);
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
                Fill_Alpha(r,alph);
                Fill_MM_par(r,MM_event);
                Fill_theta_par(r,theta_event);
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
                }*/
            }
        }
    }

    
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

    //MM_hist[1][0].Fit("gaus");

    std::cout<<"\nWrite: ";
    /*TDirectory * MM_W_var_stuff = output -> mkdir("MM_W_var_stuff");
    MM_W_var_stuff->cd();*/
    WriteHist_MM_Wvar();

    output->Write();
    std::cout<<"Complete \nClose: ";
    output->Close();
    std::cout<<"Complete" <<std::endl;

	return 0;
}
