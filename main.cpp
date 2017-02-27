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

	TFile *output = Name_File(output_name);


	//Load in Files
    cout << "Loading Files: ";
    TChain data("h10");
   	loadChain(&data, "/home/mclauchlinc/Desktop/e16/nick.txt", -1);
    cout<< "Done" <<std::endl;

    //Number of events check
    int events;
    events = data.GetEntries();
    cout <<"There are "<< events <<" events loaded" <<endl;

    SetBranches(&data);

    MakeHist_fid();

    for(int i = 0; i< 10 ; i++)
    {
    	data.GetEntry(i);
    	cout <<"Momentum is " <<p[1] <<endl;
    	Fill_fid("e", 1, cx[0], cy[0], cz[0]);
    }
    for(int i = 0; i<4; i++){
        cout <<"Species: " <<species[i] <<endl;
        cout << "Cut type: " <<cut[i] <<endl;
    }

    Fid_Write();


    gpart = 2;
    cout<< "gpart is " <<gpart <<endl;

	return 0;
}
