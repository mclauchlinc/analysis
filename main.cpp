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
   	loadChain(&data, "/home/mclauchlinc/Desktop/e16/nick.txt", -1); //Located in read_in_data.h
    cout<< "Done" <<std::endl;  //Just to let me know
    cout<<"2" <<endl;
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

    for(int i = 0; i< events ; i++)
    {
        //Update on the progress
        progress = (int) 100.0*(((double)i+1.0)/(double)events);
       cout <<"Progess Percent " <<progress <<"\r";

        //Get info for event i
        data.GetEntry(i);
        
        //Fill histograms for eid 
        Fill_eid(p[0], q[0], cx[0], cy[0], cz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], stat[0], etot[0], id[0]);
    }

    //Fid_Write(); //Located in make_files.h

    output->Write();
    std::cout<<"\n \n \nwrite" <<std::endl;
    output->Close();
    std::cout<<"close" <<std::endl;

	return 0;
}
