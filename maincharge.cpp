#include "headers.h" //Contains all the header files I need
#include "Hist_Charge.h"


using namespace std;
int main(int argc, char** argv)
{
	cout<< "You have " << argc << " arguments: " <<endl;
	for( int i = 0; i < argc; i++)
	{
		cout << argv[i] <<endl;
	}

	//Set input and output files
	std::string comp = argv[1];
    //int file_num = argv[2];
	char* output_name = argv[2];

    int file_num = 6;

	TFile *output = Name_File(output_name); //read_in_data.h
    cout<<"1" <<endl;

	//Load in Files
    cout << "Loading Files: ";
    TChain data("h10"); //Create a TChain

    int work = 0;
    if(comp == "one"){
   	    loadChain(&data, "/home/mclauchlinc/Desktop/e16/nick.txt", file_num); //Located in read_in_data.h
        work ++;
    }
    if(comp == "two"){
        loadChain(&data, "mac_set_1.txt",file_num);
        work ++;
    }
    if(comp == "three"){
        loadChain(&data,"question_data.txt",file_num);
        work ++;
    }
    if(comp == "four"){
        loadChain(&data,"old_e1f_data.txt",16);
        work ++;
    }
    if(work =0){
        cout<< "You did it wrong and loaded no data" <<endl;
    }
    
    cout<< "Done" <<std::endl;  //Just to let me know
    cout<<"2" <<endl;

    //Number of events check
    int events;
    events = data.GetEntries();
    cout <<"There are "<< events <<" events loaded" <<endl;

    cout<<"3" <<endl;
    SetBranches(&data); // Located in read_in_data.h
    
    //MakeHist();
    //MakeHist();
    MakeHist_dtp_q();
    //MakeHist_dtpip();
    MakeHist_fidp_q();
    //MakeHist_fidpip();
    
    cout<<"4" <<endl;
    //Progress
    int progress;

    int q_m[100];

    cout<< "made histograms?" <<endl;

    for(int i = 0; i< events ; i++)
    {
        //Update on the progress
       // cout<<"got into the loop?" <<endl;
        //cout<< "one " <<endl;
        progress = (int) 100.0*(((double)i+1.0)/(double)events);
       cout <<"Progess Percent " <<progress <<"\r";
       //cout<< "two " <<endl;
        //Get info for event i
        data.GetEntry(i);
        Reasign(); //Converts to C++ data types variables.h
       // cout<< "three" <<endl;
        int duck = 0;

        //Fill_eid(p[0], q[0], cx[0], cy[0], cz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], stat[0], etot[0], id[0]);
        //cout << "did electron things about to enter for loop" <<endl;
        for(int j = 1; j<gpart ; j++){
           //hid_sanity(dc[j], sc[j], stat[j], dc_stat[j]){
                //Pre
                Fill_fid_q(q[j],0,cx[j],cy[j],cz[j]);
                Fill_dt_q(q[j],0,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                /*
                //Delta T
                if(delta_t_proton(p[0], p[j], sc_r[sc[0]-1], sc_r[sc[j]-1], sc_t[sc[0]-1], sc_t[sc[j]-1])){
                    duck ++;
                    Fill_dt_q(q[j],1,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                }
                else{
                    Fill_dt_q(q[j],2,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                }
                //Fiducial
                if(fid_h(p[j], cx[j], cy[j], cz[j])){
                    Fill_fid_q(q[j],1,cx[j],cy[j],cz[j]);
                    duck ++;
                }
                else{
                    Fill_fid_q(q[j],2,cx[j],cy[j],cz[j]);
                }
                //Full ID
                //if(fid_h(p[j],cx[j],cy[j],cz[j]) && delta_t_proton(p[0], p[j], sc_r[sc[0]-1], sc_r[sc[j]-1], sc_t[sc[0]-1], sc_t[sc[j]-1])){
                if(duck == 2){
                    Fill_dt_q(q[j],3,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                    Fill_fid_q(q[j],3,cx[j],cy[j],cz[j]);
                }
               
                if(id[j] == PROTON){
                    Fill_dt_q(q[j],5,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                    Fill_fid_q(q[j],5,cx[j],cy[j],cz[j]);
                }
             if(is_proton(q[j], p[j], cx[j], cy[j], cz[j], dc[j], sc[j], stat[j], dc_stat[j], sc_t[sc[j]-1], sc_r[sc[j]-1], p[0],sc_r[sc[0]-1], sc_t[sc[0]-1])){
                    Fill_dt_q(q[j],4,sc[j],p[j], p[0], sc_r[sc[j]-1], sc_r[sc[0]-1], sc_t[sc[j]-1], sc_t[sc[0]-1]);
                    Fill_fid_q(q[j],4,cx[j],cy[j],cz[j]);
                }
                */
            
        }
    }

    output->Write();
    std::cout<<"\n \n \nwrite" <<std::endl;
    output->Close();
    std::cout<<"close" <<std::endl;

	return 0;
}
