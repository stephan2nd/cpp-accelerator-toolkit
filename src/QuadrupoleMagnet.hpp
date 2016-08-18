#ifndef QUADRUPOLE_MAGNET_HPP_
#define QUADRUPOLE_MAGNET_HPP_

#include <iostream>
#include <string>

#include "Device.hpp"



using namespace std;

class QuadrupoleMagnet : public Device
{
friend unsigned int test_quadrupoleMagnet(bool verbose);

public:

	QuadrupoleMagnet(const string& name, double width, double height, double length, double strength);
	
	QuadrupoleMagnet(const string& name, double width, double height, double length, double min_strength, double max_strength);	

	virtual
	~QuadrupoleMagnet();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const QuadrupoleMagnet& quadrupoleMagnet);

	void
	transport(Ion& ion);
	
	void
	reset(void);
	
	virtual int
	settingSize(void) { return 1; };

	void 
	setMinStrength(double min_strength);
	
	void
	setMaxStrength(double max_strength);
	
	void
	setStrength(double strength);
	
	void
	setNormValue(double norm_strength);
	
private:
	
	double m_strength;
	
	double m_min_strength;
	
	double m_max_strength;	
};

#endif /* QUADRUPOLE_MAGNET_HPP_ */
