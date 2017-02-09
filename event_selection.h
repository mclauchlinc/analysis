#ifndef EVENT_SELECTION_H
#define EVENT_SELECTION_H

#include "constants.h"
#include "hid.h"
#include "TVector3.h"
#include <TLorentzVector.h>

//Determine if multiple ids assigned to a single particle
//These are the only particles I'm IDing so if it is something else it comes in as zero
bool clean_id ( bool electron, bool proton, bool pi_plus, bool pi_minus)
{
	bool clean = kFALSE;
	if((int)electron +(int)proton +(int)pi_plus +(int)pi_minus<=1)
	{
		clean = kTRUE;
	}
	return clean;
}

/*
//Determine if kinematically clean
//Only need to do when all particles are present 
//A momentum correction is all the more necessary after these
bool clean_kin 
*/

//Give proper particle ID number to the particle id varaible array you made
int give_id( bool electron, bool proton, bool pi_plus, bool pi_minus)
{
	//Check that the id is clean
	int id = 0;
	bool is_clean = clean_id(electron, proton, pi_plus, pi_minus);
	if( is_clean == kTRUE)
	{
		if( electron == kTRUE)
		{
			id = ELECTRON;
		}
		if( proton == kTRUE)
		{
			id = PROTON;
		}
		if( pi_plus == kTRUE)
		{
			id = PION;
		}
		if( pi_minus == kTRUE)
		{
			id = -PION;
		}
	}
	return id;
}

//Determine if there were only clean id's in an event
//Not sure how this is useful, probably won't use. 
bool clean_event (Int_t gpart, int real_id[24])
{
	bool clean_event = kFALSE;
	int mult = 1;
	for( int a=0;a<gpart;a++)
	{
		mult = mult * real_id[a];
	}
	if( mult != 0)
	{
		clean_event = kTRUE;
	}
	return clean_event;
}

//

/*
1) Identify particles
2) Choose Topology
3) Pi-Missing mass
3.1
/*



//pi- Missing Mass
if(real_id[0]==ELECTRON)
{
	int pidx = -1;
	int pipidx = -1;
	int event = 0;
	for(int k=1; k<gpart; k++)
	{
		if(is_proton(k) == kTRUE)
		{
			for(int l = 1; l<gpart; l++)
			{
				if(is_pip(l) == kTRUE && l!=k)
				{
					if(missing_mass(k,l) > (pim_center-3*pim_sigma) && missing_mass(k,l) < (pim_center+3*pim_sigma))
					{
						event++;
						pidx = k;
						pipidx = l;
					}
				}
			}
		}
	}
	if(event == 1)
	{
		//Event found
	}
}

*/


//proton, pi_plus measured
// Looks for 
/* Takes in 
personal id: real_id
bank momentum: p
bank: gpart
bank cosines: cx, cy, cz
Energy of beam
*/
bool pi_m_miss (int real_id[24], Float_t p[23], Int_t gpart, bool clean_id, Float_t cx[23], Float_t cy[23], Float_t cz[23], double Energy)
{
	bool pi_mi_found = kFALSE;
	int number_pi_mi = 0;
	TLorentzVector p_mu_prime, pi_mu_prime, k_mu_prime, k_mu(0.0,0.0,Energy,Energy),p_mu(0.0,0.0,0.0,mp),q_mu;
	TVector3 p_mu3_prime, pi_mu3_prime, k_mu_prime3;
	double missing_mass;
	
	//Need to recalculate four momentum of virtual exchange photon
	if(real_id[0]==ELECTRON)
	{
		k_mu_prime3.SetXYZ(p[0]*cx[0],p[0]*cy[0],p[0]*cz[0]);
		k_mu_prime.SetVectM(k_mu_prime3,me);
		q_mu = (k_mu - k_mu_prime);

		//Loop over particles twice to find a set of proton and pi_plus
		for(int w=0;w<gpart;w++)
		{
			for(int r=0;r<gpart;r++)
			{
				if( real_id[w]==PROTON && real_id[r]==PION)
				{
					p_mu3_prime.SetXYZ(p[w]*cx[w],p[w]*cy[w],p[w]*cz[w]);
					pi_mu3_prime.SetXYZ(p[r]*cx[r],p[r]*cy[r],p[r]*cz[r]);
					p_mu_prime.SetVectM(p_mu3_prime,mp);
					pi_mu_prime.SetVectM(pi_mu3_prime,mpi);
					missing_mass = (q_mu + p_mu - p_mu_prime - pi_mu_prime).Mag2();
					if(missing_mass>=(pim_center - 3*pim_sig) && missing_mass<=(pim_center - 3*pim_sig))
					{
						number_pi_mi++;
					}
				}
			}
		}	
	}	
	//Looking for just a single pi_minus paired with a proton, pi_plus
	if(number_pi_mi ==1)
	{
		pi_mi_found = kTRUE;
	}
	return pi_mi_found;
}

//Seen pi plus and minus
bool proton_miss (int real_id[24], Float_t p[23], Int_t gpart, bool clean_id, Float_t cx[23], Float_t cy[23], Float_t cz[23], double Energy)
{
	bool proton_found = kFALSE;
	int number_proton = 0;
	TLorentzVector p_mu_prime, pi_mu_prime, k_mu_prime, k_mu(0.0,0.0,Energy,Energy),p_mu(0.0,0.0,0.0,mp),q_mu;
	TVector3 p_mu3_prime, pi_mu3_prime, k_mu_prime3;
	double missing_mass;
	
	//Need to recalculate four momentum of virtual exchange photon
	if(real_id[0]==ELECTRON)
	{
		k_mu_prime3.SetXYZ(p[0]*cx[0],p[0]*cy[0],p[0]*cz[0]);
		k_mu_prime.SetVectM(k_mu_prime3,me);
		q_mu = (k_mu - k_mu_prime);

		//Loop over particles twice to find a set of pi_minus and pi_plus
		for(int w=0;w<gpart;w++)
		{
			for(int r=0;r<gpart;r++)
			{
				if( real_id[w]==PION && real_id[r]==-PION)
				{
					p_mu3_prime.SetXYZ(p[w]*cx[w],p[w]*cy[w],p[w]*cz[w]);
					pi_mu3_prime.SetXYZ(p[r]*cx[r],p[r]*cy[r],p[r]*cz[r]);
					p_mu_prime.SetVectM(p_mu3_prime,mpi);
					pi_mu_prime.SetVectM(pi_mu3_prime,mpi);
					missing_mass = (q_mu + p_mu - p_mu_prime - pi_mu_prime).Mag2();
					if(missing_mass>=(p_center - 3*p_sig) && missing_mass<=(p_center - 3*p_sig))
					{
						number_proton++;
					}
				}
			}
		}	
	}	
	//Looking for just a single proton paired with a pi minus, pi_plus
	if(number_proton ==1)
	{
		proton_found = kTRUE;
	}
	return proton_found;
}

//Seen proton and pi minus: missing mass on pi plus
bool pi_p_miss (int real_id[24], Float_t p[23], Int_t gpart, bool clean_id, Float_t cx[23], Float_t cy[23], Float_t cz[23], double Energy)
{
	bool pi_p_found = kFALSE;
	int number_pi_p = 0;
	TLorentzVector p_mu_prime, pi_mu_prime, k_mu_prime, k_mu(0.0,0.0,Energy,Energy),p_mu(0.0,0.0,0.0,mp),q_mu;
	TVector3 p_mu3_prime, pi_mu3_prime, k_mu_prime3;
	double missing_mass;
	
	//Need to recalculate four momentum of virtual exchange photon
	if(real_id[0]==ELECTRON)
	{
		k_mu_prime3.SetXYZ(p[0]*cx[0],p[0]*cy[0],p[0]*cz[0]);
		k_mu_prime.SetVectM(k_mu_prime3,me);
		q_mu = (k_mu - k_mu_prime);

		//Loop over particles twice to find a set of proton and pi_minus
		for( int w=0;w<gpart;w++)
		{
			for( int r=0;r<gpart;r++)
			{
				if( real_id[w]==PROTON && real_id[r]==-PION)
				{
					p_mu3_prime.SetXYZ(p[w]*cx[w],p[w]*cy[w],p[w]*cz[w]);
					pi_mu3_prime.SetXYZ(p[r]*cx[r],p[r]*cy[r],p[r]*cz[r]);
					p_mu_prime.SetVectM(p_mu3_prime,mp);
					pi_mu_prime.SetVectM(pi_mu3_prime,mpi);
					missing_mass = (q_mu + p_mu - p_mu_prime - pi_mu_prime).Mag2();
					if(missing_mass>=(pip_center - 3*pip_sig) && missing_mass<=(pip_center - 3*pip_sig))
					{
						number_pi_p++;
					}
				}
			}
		}	
	}	
	//Looking for just a single pi_minus paired with a proton, pi_minus
	if(number_pi_p ==1)
	{
		pi_p_found = kTRUE;
	}
	return pi_p_found;
}

//This just says whether or not all target particles are in the event
bool all_present(int real_id[24], Int_t gpart)
{
	bool all_present = kFALSE;
	for(int i=0;i<gpart;i++)
	{
		for(int j=0;j<gpart;j++)
		{
			for(int k=0;k<gpart;k++)
			{
				if( real_id[i]==PROTON && real_id[j]==PION && real_id[k]==-PION)
				{
					all_present = kTRUE;
				}
			}
		}
	}
	return all_present;
}

//To see if an event satisfies any of the four topologies
bool topology_cross ( bool all_present, bool pi_mi_miss, bool pi_p_miss, bool proton_miss)
{
	bool cross = kFALSE;
	if( ((int)all_present + (int)pi_mi_miss +(int)pi_p_miss +(int)proton_miss)>=1)
	{
		cross = kTRUE;
	}
	return cross;
}

//Actual event selection
//Will cross reference through diffrent topologies to make sure that events are not double, or triple counted
/*
Says whether or not the event fits within
- Taret Particles
- Kinematic Agreement
- no momentum corrections yet
*/
//bool event_selection()

#endif /* EVENT_SELECTION_H */