#include "Device.hpp"

#include <sstream>
#include <cmath>



Device::Device(const string& class_name, const string& name, double width, double height, double length, int shape) :
	m_class_name(class_name),
	m_name(name),
	m_width(width),
	m_height(height),
	m_left_width(0.5 * width),
	m_right_width(0.5 * width),
	m_upper_width(0.5 * height),
	m_lower_width(0.5 * height),	
	m_length(length),
	m_shape(shape),
	m_ignore(false),
	m_previous(NULL),
	m_next(NULL)
{ }



Device::Device(const string& class_name, const string& name, double left_width, double right_width, double upper_width, double lower_width, double length, int shape) :
	m_class_name(class_name),
	m_name(name),
	m_width(left_width + right_width),
	m_height(upper_width + lower_width),
	m_left_width(left_width),
	m_right_width(right_width),
	m_upper_width(upper_width),
	m_lower_width(lower_width),
	m_length(length),
	m_shape(shape),
	m_ignore(false),
	m_previous(NULL),
	m_next(NULL)
{ }



Device::~Device()
{ }
	


ostream&
operator<<(ostream& os, const Device& device)
{
	return os << device.toLine();
}



void
Device::appendDevice(Device* device)
{
	if( m_next==NULL ){
		m_next=device;
		device->setPreviousDevice(this);
	} else {
		m_next->appendDevice(device);
	}
}



bool
Device::isParticleLost(const Ion& ion) const 
{	
	if( m_shape == SHAPE_ELLIPSE ){
		return (4*pow(ion.x(),2)/pow(m_width,2) + 4*pow(ion.y(),2)/pow(m_height,2)) > 1;
	} else if( m_shape == SHAPE_RECT ){
		return (ion.x() < -m_left_width) || (ion.x() > m_right_width) || (ion.y() < -m_lower_width) || (ion.y() > m_upper_width);
	} else {
		 cout << "Error in " << __FILE__ << " line " << __LINE__ << " shape type " << m_shape << " unknown" << endl;
		 exit(0);
	}
}



string
Device::mirkoMakroString(void) const
{
	return "";
}



