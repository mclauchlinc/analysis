#ifndef MAIN_PHD_H_GUARD
#define MAIN__PHD_H_GUARD
#include <TFile.h>
#include "TH1.h"


bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

TFile *Name_File(std::string a_file_name)
{
	std::string file_name = "$name.root";
	replace(file_name, "$name", a_file_name);
	return new TFile(file_name.c_str(),"RECREATE");
}

#endif