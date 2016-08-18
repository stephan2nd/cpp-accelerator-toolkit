#ifndef TRAFO_HPP_
#define TRAFO_HPP_

#include <iostream>
#include <string>

#include "Device.hpp"

using namespace std;

class Trafo : public Device
{
friend unsigned int test_trafo(bool verbose);

public:

	Trafo(const string& name);

	virtual
	~Trafo();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const Trafo& trafo);

	void
	transport(Ion& ion);
	
	void
	reset(void);
	
	double 
	getCounts(void);
	
private:

	atomic<unsigned int> m_counts;	
};

#endif /* TRAFO_HPP_ */
