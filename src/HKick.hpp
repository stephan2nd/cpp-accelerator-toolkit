#ifndef H_KICK_HPP_
#define H_KICK_HPP_

#include <iostream>
#include <string>

#include "Device.hpp"



using namespace std;

class HKick : public Device
{
friend unsigned int test_hKick(bool verbose);

public:

	HKick(const string& name, double angle);
	
	HKick(const string& name, double min_angle, double max_angle);

	virtual
	~HKick();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const HKick& hKick);

	virtual void
	transport(Ion& ion);
		
	virtual void
	reset(void);
	
	virtual int
	settingSize(void) { return 1; };
	
	void 
	setMinAngle(double min_angle);
	
	void
	setMaxAngle(double max_angle);
	
	void
	setAngle(double angle);
	
	void
	setNormValue(double norm_angle);
	
private:

	double m_angle;
	
	double m_min_angle;
	
	double m_max_angle;
};

#endif /* H_KICK_HPP_ */
