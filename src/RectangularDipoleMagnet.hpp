#ifndef RECTANGULAR_DIPOLE_MAGNET_HPP_
#define RECTANGULAR_DIPOLE_MAGNET_HPP_

#include <iostream>
#include <string>

#include "Device.hpp"



using namespace std;

class RectangularDipoleMagnet : public Device
{
friend unsigned int test_rectangularDipoleMagnet(bool verbose);

public:

	RectangularDipoleMagnet(const string& name, double width, double height, double length, double angle);

	virtual
	~RectangularDipoleMagnet();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const RectangularDipoleMagnet& rectangularDipoleMagnet);

private:

	double m_angle;
};

#endif /* RECTANGULAR_DIPOLE_MAGNET_HPP_ */
