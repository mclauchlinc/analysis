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

	//Load in Files
    cout << "Loading Files: ";
    TChain data("h10"); //Create a TChain
   	loadChain(&data, "/home/mclauchlinc/Desktop/e16/nick.txt", -1); //Located in read_in_data.h
    cout<< "Done" <<std::endl;  //Just to let me know

    //Number of events check
    int events;
    events = data.GetEntries();
    cout <<"There are "<< events <<" events loaded" <<endl;

  
    SetBranches(&data); // Located in read_in_data.h
    
    MakeHist();
 
    //Progress
    int progress;

    for(int i = 0; i< 10 ; i++)
    {
        //Update on the progress
        progress = (int) 100.0*(((double)i+1.0)/(double)events);
        cout <<"Progess Percent " <<progress <<"\r";

        //Get info for event i
        data.GetEntry(i);

        //Electron ID
            //EID Precut
    	Fill_fid( 0 , 0, cx[0], cy[0], cz[0]); //histograms.h
        Fill_WQ2( 0, 0, p[0], cx[0], cy[0], cz[0]); //histograms.h
            //EID Cut and Anti-Cut
        if(eid( p[0], q[0], cx[0], cy[0], cz[0], vx[0], vy[0], vz[0], dc[0], cc[0], ec[0], sc[0], dc_stat[dc[0]-1], etot[0], stat[0], 3)){   //eid.h
            Fill_fid( 0, 1, cx[0], cy[0], cz[0]);    //histograms.h
            Fill_WQ2( 0, 1, p[0], cx[0], cy[0], cz[0]); //histograms.h
        }else{
            Fill_fid( 0, 2, cx[0], cy[0], cz[0]);    //histograms.h
            Fill_WQ2( 0, 2, p[0], cx[0], cy[0], cz[0]); // histograms.h
        }
        //cout<< i+1 <<endl;
    }

    //Fid_Write(); //Located in make_files.h

    output->Write();
    output->Close();

	return 0;
}
