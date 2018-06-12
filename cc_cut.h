#ifndef CC_CUT_H
#define CC_CUT_H

//#include "constants.h"
//#include "variables.h"
#include "headers.h"
#include "cc_hist.h"
#include "CartesianGenerator.hh"

bool min_cc(int cc_segm, int cc_sect, int nphe){
	bool pass = false;
	int seg = cc_segment(cc_segm);
	int sect = cc_sect -1;
	if(sect >= 0 && seg >= 0){
		if(nphe > MinCC_Cut[sect][cc_segm]){
			pass = true;
		}
	}
	return pass; 
}


#endif