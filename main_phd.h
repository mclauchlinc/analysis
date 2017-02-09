#ifndef MAIN_PHD_H_GUARD
#define MAIN__PHD_H_GUARD
#include <TFile.h>
#include "TH1.h"


TFile *Name_File(std::string a_file_name)
{
	return new TFile(a_file_name.c_str(),"RECREATE");
}

#endif