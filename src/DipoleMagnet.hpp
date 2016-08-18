#ifndef DIPOLE_MAGNET_HPP_
#define DIPOLE_MAGNET_HPP_

#include <iostream>
#include <string>

#include "Device.hpp"



using namespace std;

class DipoleMagnet : public Device
{
friend unsigned int test_dipole_magnet(bool verbose);

public:

	DipoleMagnet(const string& name, double width, double height, double length, double angle);

	virtual
	~DipoleMagnet();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const DipoleMagnet& dipoleMagnet);

	void
	transport(Ion& ion);
	
	void
	reset(void);

private:

	double m_angle;
};

#endif /* DIPOLE_MAGNET_HPP_ */
