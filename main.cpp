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
    TChain data("h10");
   	loadChain(&data, "/home/mclauchlinc/Desktop/e16/nick.txt", -1); //Located in read_in_data.h
    cout<< "Done" <<std::endl;

    //Number of events check
    int events;
    events = data.GetEntries();
    cout <<"There are "<< events <<" events loaded" <<endl;

    cout << 1 <<endl;
    SetBranches(&data); // Located in read_in_data.h
    cout<< 2 <<endl;
    MakeHist_fid(); // Located in histograms.h
    cout<< 3 <<endl;
    //Progress
    int progress;
    cout << 4 <<endl;
    for(int i = 0; i< 10 ; i++)
    {
    	cout<< "event " << i <<endl;
        //Update on the progress
        //progress = (int) 100.0*(((double)i+1.0)/(double)events);
        //cout<<"Progess Percent " <<progress <<"\r";

        //Get info for event i
        data.GetEntry(i);

        //Electron ID
    	Fill_fid(0 , 0, cx[0], cy[0], cz[0]); //histograms.h
    }

    //Fid_Write(); //Located in make_files.h

    output->Write();
    output->Close();

	return 0;
}
