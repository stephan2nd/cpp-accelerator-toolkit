#ifndef MIRKO_Interface_HPP_
#define MIRKO_Interface_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "Device.hpp"



using namespace std;

class MirkoInterface
{
public:

	MirkoInterface();

	virtual
	~MirkoInterface();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const MirkoInterface& mirkoInterface);

	void 
	readMixFile(const string& filename);

	void 
	parseDeviceFromMixFileLine(const string& line);

	void 
	addDevice(const string& name, int vcode, int type, int sub, double arg1, double arg2, double arg3, double arg4);

	vector<Device*> 
	getDevices() const;

private:

	vector<Device*> m_devices;
};

#endif /* MIRKO_Interface_HPP_ */
