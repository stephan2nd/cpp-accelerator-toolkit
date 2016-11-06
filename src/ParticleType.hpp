#ifndef PARTICLE_TYPE_HPP_
#define PARTICLE_TYPE_HPP_

#include <iostream>
#include <string>

#include "Device.hpp"
#include "physics.h"



using namespace std;

class ParticleType
{
friend unsigned int test_particleType(bool verbose);

public:

	ParticleType(unsigned int neutron_number, unsigned int proton_number, unsigned int electron_number);

	virtual
	~ParticleType();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const ParticleType& particleType);
	
	inline unsigned int 
	mass_number(void) const { return m_neutron_number + m_proton_number; }
	
	inline int
	charge_number(void) const { return m_proton_number - m_electron_number; }
	
	inline double 
	charge(void) const { return physics::elementary_charge_in_coulombs * charge_number(); }

private:

	unsigned int m_neutron_number;
	
	unsigned int m_proton_number;
	
	unsigned int m_electron_number;
};

#endif /* PARTICLE_TYPE_HPP_ */
