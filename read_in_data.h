#ifndef READ_IN_DATA_H_GUARD
#define READ_IN_DATA_H_GUARD

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <TChain.h>
#include "variables.h"
#include "TTree.h"


//Creates a vector of file names from a source file labeled "path"
std::vector<std::string> read_file_list(std::string path) //Choose a vector of strings. Vector because adding things onto the end works fine. Also don't know how to use a list
{
	std::ifstream infile(path.c_str()); // in file stream
	std::vector<std::string> result;
	std::string line;

	while(getline(infile,line)) { //getline sees if there is a line available
		result.push_back(line);//Gets the current line
	}
	return result;
}

//Create a data chain for a given data set
//Optional number of files to load
void loadChain(TChain* c, std::string file, int max=-1)
{
	std::vector<std::string> filelist = read_file_list(file); //creates a vector of file names
	//If not specified will take in all the files in the text file
	int test = filelist.size();
	if(max > test)
	{
		std::cout<< "You tried to add too many files. This has been corrected" <<std::endl <<"Remember that you may only add " <<test <<" files" <<std::endl;
	}
	if(max == -1 || max > test) {//In case one tries to add too many files
		max = filelist.size();
	}
	//If specified then it will take in that number of files 
	for(int i = 0; i < max; i++) {
		c->AddFile(filelist[i].c_str());
	}
}

void SetBranches(TChain* c)
{
	c->SetBranchAddress("q",&q);
    c->SetBranchAddress("gpart",&gpart);
    c->SetBranchAddress("sc_t",&sc_t);
    c->SetBranchAddress("sc_r",&sc_r);
    c->SetBranchAddress("sc",&sc);
    c->SetBranchAddress("p",&p);
    c->SetBranchAddress("cx",&cx);
    c->SetBranchAddress("cy",&cy);
    c->SetBranchAddress("cz",&cz);
    c->SetBranchAddress("stat",&stat);
    c->SetBranchAddress("dc_stat",&dc_stat);
    c->SetBranchAddress("vx",&vx);
    c->SetBranchAddress("vy",&vy);
    c->SetBranchAddress("vz",&vz);
    c->SetBranchAddress("dc",&dc);
    c->SetBranchAddress("cc",&cc);
    c->SetBranchAddress("ec",&ec);
    c->SetBranchAddress("etot",&etot);
}



/*
TChain LoadData(char q, TChain* chain){
	if(q == 'd')
	{
		loadChain(&chain,"/home/mclauchlinc/Desktop/e16/nick.txt"); //This is specifically for the desktop
	}
	return data;
}
*/
#endif

/*
  TChain chain("h10");
  loadChain(&chain,"/some/path/files.txt");
  loadChain(&chain,"/some/path/files.txt",100);
*/