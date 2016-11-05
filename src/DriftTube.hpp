#ifndef DRIFT_TUBE_HPP_
#define DRIFT_TUBE_HPP_

#include <iostream>
#include <string>

#include "Device.hpp"



using namespace std;

class DriftTube : public Device
{
friend unsigned int test_driftTube(bool verbose);

public:

	DriftTube(const string& nomenclature, double width, double height, double length);

	virtual
	~DriftTube();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const DriftTube& driftTube);

	void
	transport(Ion& ion);

	void
	reset(void);
	
	string
	mirkoMixString(void) const;
	
private:
	
};

#endif /* DRIFT_TUBE_HPP_ */
