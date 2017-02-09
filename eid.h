#ifndef EID_H
#define EID_H

#include "constants.h"
#include "sanity_cuts.h"
#include "vertex.h"
#include "fiducial.h"
#include "electron_ec.h"

/*
Identifies electrons
Sanity cuts: dc, cc, ec, sc, stat, dc_stat, q
Vertex Cuts: vz (eventually p, vx, vy)
Fiducial Cuts: p, cx, cy, cz
Min Energy in EC cuts: 
Sampling Fraction Cut: 
 */
bool eid( Float_t p, Char_t q, Float_t cx, Float_t cy, Float_t cz, Float_t vx, Float_t vy, Float_t vz, UChar_t dc, UChar_t cc, UChar_t ec, UChar_t sc, UChar_t dc_stat, Float_t etot, Char_t stat, int level)
{
	bool is_electron = kFALSE;
	bool sane_elec = kFALSE;
	bool vertex = kFALSE;
	bool fiducial_cut = kFALSE;
	bool min_energy_cut = kFALSE;
	bool sf_cut = kFALSE;
	//int dc_index = dc-1;
	sane_elec = sanity_electron( dc, cc, ec, sc, stat, dc_stat, q );
	vertex = vertex_cut(vz); //For now this has no vertex correction as the function makes no sense. 
	fiducial_cut = fid_e( p, cx, cy, cz);
	min_energy_cut = min_ec(etot); 
	sf_cut = sf_e( p , etot, cx, cy);
	if(level >= 1)
	{
		if(dc>0 && cc>0 && sc>0 && q==-1)
		{
			if(level == 1)
			{
				is_electron = kTRUE;
			}
			if(level >= 2)
			{
				if(sane_elec == kTRUE)
				{
					if(level == 2)
					{
						is_electron = kTRUE;
					}
					if(level == 3)
					{
						if(fiducial_cut == kTRUE)
						{
							if(min_energy_cut == kTRUE)
							{
								if(sf_cut == kTRUE)
								{
									is_electron = kTRUE;
								}
							}
						}
					}
				}	
			}
		}
	}

	return is_electron;
}

#endif /* EID_H */