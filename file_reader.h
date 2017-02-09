#ifndef DELTA_T_CUTS_H
#define DELTA_T_CUTS_H

#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include <iostream>
#include <string>
#include <fstream>

TChain file_input(char d)
{	
	TChain chain("h10");
	string file_name;

	if(d == 'm')
	{
		ifstream filem("data_med.txt");
		if(filem.is_open())
		{
			
		}
	}
	else
	{
		cout<<"There is no File"
	}
	return 
}