
#ifndef PARTICLE_ID_H
#define PARTICLE_ID_H

#include "physics.h"
#include "eid.h"
#include "hid.h"
#include "event_selection.h"

int particle_id( int idx, Float_t p, Char_t q[23], Float_t cx[23], Float_t cy[23], Float_t cz[23], Float_t vx[23], Float_t vy[23], Float_t vz[23], UChar_t dc[23], UChar_t cc[23], UChar_t ec[23], UChar_t sc[23], UChar_t dc_stat[23], Float_t etot[23], Char_t stat[23])
{
	int particle = 0;
	int ids = 0;
	bool electron, proton, pi_plus, pi_minus;
	//Electron id
	if(idx == 0)
	{
		electron = eid(Float_t p[23], Char_t q[23], Float_t cx[23], Float_t cy[23], Float_t cz[23], Float_t vx[23], Float_t vy[23], Float_t vz[23], UChar_t dc[23], UChar_t cc[23], UChar_t ec[23], UChar_t sc[23], UChar_t dc_stat[23], Float_t etot[23], Char_t stat[23])
	}
	//Hadron ID
	if(idx >= 1)
	{
		proton = is_proton( q,  p,  beta,  cx,  cy,  cz,  dc,  sc,  stat,  dc_stat,  sc_t, sc_r);
		pi_plus = is_pip();
		pi_minus = is_pim();
	}
	particle = give_id(electron, proton, pi_plus, pi_minus);
	return particle;
}


#endif /* PARTICLE_ID_H */