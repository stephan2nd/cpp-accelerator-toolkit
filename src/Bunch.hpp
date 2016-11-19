#ifndef BUNCH_HPP_
#define BUNCH_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "Device.hpp"
#include "MacroParticle.hpp"



using namespace std;

class Bunch
{
friend unsigned int test_bunch(bool verbose);

public:

	Bunch(unsigned int nof_macro_particles, unsigned int bunch_current, double rf_frequency);

	virtual
	~Bunch();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const Bunch& bunch);

private:

	vector<MacroParticle> m_makro_particles;
};

#endif /* BUNCH_HPP_ */
