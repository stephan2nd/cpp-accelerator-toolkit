#ifndef SLIT_HPP_
#define SLIT_HPP_

#include <iostream>
#include <string>
#include <atomic>

#include "Device.hpp"



using namespace std;

class Slit : public Device
{
friend unsigned int test_slit(bool verbose);

public:

	Slit(const string& name, double pos_left, double pos_right , double pos_bottom, double pos_top);

	virtual
	~Slit();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const Slit& slit);

	virtual void
	transport(Ion& ion);
		
	virtual void
	reset(void);
	
private:

	double m_pos_left;
	
	double m_pos_right;
	
	double m_pos_top;
	
	double m_pos_bottom;

	atomic<unsigned int> m_count_left;
	
	atomic<unsigned int> m_count_right;
	
	atomic<unsigned int> m_count_top;
	
	atomic<unsigned int> m_count_bottom;
};

#endif /* SLIT_HPP_ */
