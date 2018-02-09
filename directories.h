#ifndef DIRECTORIES_H
#define DIRECTORIES_H

#include "headers.h"
#include "TDirectory.h"

  //filefile
//TFile *file;

void MakeDirectories(TFile *file){

//TDirectory * WQ2_plots = file->mkdir("WQ2_plots");
//TDirectory * fid_plots = file->mkdir("fid_plots");
//TDirectory * delta_t_plots = file->mkdir("delta_t_plots");
//TDirectory * sf_plots = file->mkdir("sf_plots");
TDirectory * MM_plots = file->mkdir("MM_plots");
TDirectory * COM_plots = file->mkdir("COM_plots");
TDirectory * xs_h = file->mkdir("xs_h");

//Subdirectories
//TDirectory * e_WQ2_plots = WQ2_plots->mkdir("e_WQ2_plots");

}


#endif