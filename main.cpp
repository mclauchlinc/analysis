#include "headers.h" //Contains all the header files I need



using namespace std;
int main(int argc, char** argv)
{
	cout<< "You have " << argc << " arguments: " <<endl;
	for( int i = 0; i < argc; i++)
	{
		cout << argv[i] <<endl;
	}

	//Set input and output files
	char* input = argv[1];
	char* output_name = argv[2];

	TFile *output = Name_File(output_name); //read_in_data.h
    cout<<"1" <<endl;

	//Load in Files
    cout << "Loading Files: ";
    TChain data("h10"); //Create a TChain
    //if(argv[1] == "o"){
   	//    loadChain(&data, "/home/mclauchlinc/Desktop/e16/nick.txt", -1); //Located in read_in_data.h
    
    //}
    //if(argv[1] == "t"){
    loadChain(&data, "mac_set_1.txt",-1);
    /*}
    else{
        cout<< "You did it wrong and loaded no data" <<endl;
    }
    */
    cout<< "Done" <<std::endl;  //Just to let me know
    cout<<"2" <<endl;

    //Create Subdirectories
    //char dirname[50];
    /*
    TDirectory *pid = output->mkdir("particle_id");
    TDirectory *e_id = pid->mkdir("eid");
    TDirectory *h_id = pid->mkdir("hid");
    TDirectory *p_id = h_id->mkdir("proton_id");
    TDirectory *pip_id = h_id->mkdir("pip_id");
    TDirectory *pim_id = h_id->mkdir("pim_id");
    TDirectory *W_Q2 = output->mkdir("W_Q2 Plots");
    //for( y=0; y<3; y++){ //Hadronic article
      //  sprintf(dirname,"%s_delta_t",species[i+1]);
        //TDir
    //}
   //TDirectory *delta = 
    */

    //Number of events check
    int events;
    events = data.GetEntries();
    cout <<"There are "<< events <<" events loaded" <<endl;

    cout<<"3" <<endl;
    SetBranches(&data); // Located in read_in_data.h
    
    //MakeHist();
    MakeHist();
    
    cout<<"4" <<endl;
    //Progress
    int progress;

    /*
    W_Q2->cd();
    MakeHist_WQ2();

    pid->cd();

    e_id->cd();
    MakeHist_e();

    p_id->cd();
    MakeHist_p();

    pip_id->cd();
    MakeHist_pip();

    pim_id->cd();
    MakeHist_pim();
    */

    cout<< "made histograms?" <<endl;

    for(int i = 0; i< events ; i++)
    {
        //Update on the progress
       // cout<<"got into the loop?" <<endl;
        progress = (int) 100.0*(((double)i+1.0)/(double)events);
       cout <<"Progess Percent " <<progress <<"\r";

        //Get info for event i
        data.GetEntry(i);
        Reasign();

        /*Debug
        if(i == 100000){
            for( int o = 0; o <gpart ; o++){
                cout<<endl <<"for i = "<<o <<" Sc is : " <<sc[o] <<endl;
            }
        }
        *///End Debug
        
        /*
        //cout<< "Id: " <<id_b[0] << " " <<id[0] <<endl;
        for(int h = 0; h<gpart; h++){
            Fill_sc((int)sc[h]);
        }
        */
        //Fill histograms for eid 
        //e_id->cd();
        //cout<<"about to do electron things" <<endl;
        Fill_eid(p[0], q[0], cx[0], cy[0], cz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], stat[0], etot[0], id[0]);
        //cout << "did electron things about to enter for loop" <<endl;
        for(int j = 1; j<gpart ; j++){
            Fill_Hadron(q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1], p[0], sc_t[sc[0]-1], sc_r[sc[0]-1], id[j]);
            //Missing Mass
                //Missing Mass 1 missing
            
            for(int k = 0; k<gpart ; k++){
                //Missing Mass pre
                MM_p_val = MM_3_com(p[0],p[j],p[k],cx[0],cx[j],cx[k],cy[0],cy[j],cy[k],cz[0],cz[j],cz[k],me,mpi,mpi);
                MM_pi_val = MM_3_com(p[0],p[j],p[k],cx[0],cx[j],cx[k],cy[0],cy[j],cy[k],cz[0],cz[j],cz[k],me,mp,mpi);

                Fill_MM(0,0,MM_p_val);
                Fill_MM(1,0,MM_pi_val);
                Fill_MM(2,0,MM_pi_val);


                if(other_p_miss(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], j, k)){
                    //Proton Missing Cut
                    Fill_MM(0,1,MM_p_val);
                }
                else{
                    //Proton Missing Anti
                    Fill_MM(0,2,MM_p_val);
                }
                if(other_pip_miss(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], j, k)){
                    //Pi+ Missing Cut
                    Fill_MM(1,1,MM_pi_val);
                }
                else{
                    //Pi+ Missing Anti
                    Fill_MM(1,2,MM_pi_val);
                }
                if(other_pim_miss(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], j, k)){
                    //Pi- Missing Cut
                    Fill_MM(2,1,MM_pi_val);
                }
                else{
                    //Pi- Missing Anti
                    Fill_MM(2,2,MM_pi_val);
                }
                for(int l = 0; l < gpart; l++){
                    //Full Topology PRe
                    MM_full = MM_4_com(p[0],p[j],p[k],p[l],cx[0],cx[j],cx[k],cx[l],cy[0],cy[j],cy[k],cy[l],cz[0],cz[j],cz[k],cz[l],me,mp,mpi,mpi);
                    Fill_MM(3,0,MM_full);
                    if(zero_miss(p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], sc_r[sc[0]-1], sc_t[sc[0]-1],  q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[dc[j]-1], sc_t[sc[j]-1], sc_r[sc[j]-1],  q[k], p[k], cx[k], cy[k], cz[k], dc[k], sc[k], stat[k], dc_stat[dc[k]-1], sc_t[sc[k]-1], sc_r[sc[k]-1], q[l], p[l], cx[l], cy[l], cz[l], dc[l], sc[l], stat[l], dc_stat[dc[l]-1], sc_t[sc[l]-1], sc_r[sc[l]-1], j, k, l)){
                        //Full Topology cut
                        Fill_MM(3,1,MM_full);
                    }
                    else{
                        //Full topology anti 
                        Fill_MM(3,2,MM_4_com(p[0],p[j],p[k],p[l],cx[0],cx[j],cx[k],cx[l],cy[0],cy[j],cy[k],cy[l],cz[0],cz[j],cz[k],cz[l],me,mp,mpi,mpi));
                    }
                }
            }
        }
        //cout<<endl;
    }

    //Fid_Write(); //Located in make_files.h

    output->Write();
    std::cout<<"\n \n \nwrite" <<std::endl;
    output->Close();
    std::cout<<"close" <<std::endl;

	return 0;
}
