#ifndef BEAMLINE_HPP_
#define BEAMLINE_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <algorithm>

#include "IonSource.hpp"
#include "Device.hpp"



using namespace std;

class Accelerator
{
friend unsigned int test_accelerator(bool verbose);

public:

	Accelerator();

	virtual
	~Accelerator();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const Accelerator& accelerator);
	
	void
	appendDevice(Device* device);
	
	Device*
	getDeviceByName(const string& name);
	
	void
	startSimulation(unsigned int nof_ions, bool threaded=true, unsigned int nof_threads=max((unsigned int)1,thread::hardware_concurrency()));
	
	void
	setNormValues(vector<double> values);
	
	int
	settingSize(void);

private:

	IonSource m_ion_source;
	
	vector<Device*> m_devices;
};

#endif /* BEAMLINE_HPP_ */
