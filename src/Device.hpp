#ifndef Device_HPP_
#define Device_HPP_

#include <iostream>
#include <string>

#include "Ion.hpp"



using namespace std;

class Device
{
public:

	static const int SHAPE_ELLIPSE = 1;
	static const int SHAPE_RECT    = 2;

	Device(const string& class_name, const string& name, double width, double height, double length = 0., int shape = SHAPE_ELLIPSE);
	
	Device(const string& class_name, const string& name, double left_width, double right_width, double upper_width, double lower_width, double length = 0., int shape = SHAPE_ELLIPSE);

	virtual
	~Device();

	virtual string
	toString(unsigned int indent=0) const = 0; 
	
	virtual string
	toLine(void) const = 0;
	
	friend ostream&
	operator<<(ostream& os, const Device& device);

	void
	appendDevice(Device* device);
	
	bool
	isParticleLost(const Ion& ion) const ;	
	
	virtual void
	transport(Ion& ion) = 0;
		
	virtual void
	reset(void) = 0;
	
	virtual int
	settingSize(void) { return 0; };

	virtual string
	mirkoMakroString(void) const;
	
	virtual void setNormValue(double norm_value) { };
	
	inline void setPreviousDevice(Device* device) { m_previous = device; }	
	
	inline Device* getNextDevice(void) { return m_next; }
	
	inline string getName(void) { return m_name; }
	
	inline void setIgnore(bool ignore) { m_ignore = ignore; }
	
	inline string getClassName(void) { return m_class_name; }

protected:

	string m_class_name;

	string m_name;

	double m_width;

	double m_height;
	
	double m_left_width;
	
	double m_right_width;
	
	double m_upper_width;
	
	double m_lower_width;
	
	double m_length;
	
	int m_shape;
	
	bool m_ignore;
	
	Device* m_previous;
	
	Device* m_next;
	
};

#endif /* Device_HPP_ */
