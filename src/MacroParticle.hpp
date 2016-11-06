#ifndef MACRO_PARTICLE_HPP_
#define MACRO_PARTICLE_HPP_

#include <iostream>
#include <string>



using namespace std;

class MacroParticle
{
friend unsigned int test_macroParticle(bool verbose);

public:

	MacroParticle();

	virtual
	~MacroParticle();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const MacroParticle& macroParticle);

private:

	unsigned int m_nof_particles;

	unsigned int m_mass_number;
	
	unsigned int m_proton_number;
	
	int m_charge_per_particle;
	
	double m_energy;

	double m_x;
	
	double m_dx;
	
	double m_y;
	
	double m_dy;
	
	double m_z; // oder phase
	
	double m_dz; // oder dW
};

#endif /* MACRO_PARTICLE_HPP_ */
