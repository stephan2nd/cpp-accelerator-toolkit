#include "VKick.hpp"

#include <sstream>



VKick::VKick(const string& name, double angle) :
	Device("VKick", name, 0, 0, 0),
	m_angle(angle)
{ }

	

VKick::VKick(const string& name, double min_angle, double max_angle) :
	Device("VKick", name, 0, 0, 0),
	m_angle(0),
	m_min_angle(min_angle),
	m_max_angle(max_angle)
{ }

	

VKick::~VKick()
{ }



string
VKick::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "angle = " << m_angle << " rad" 
	   << ")";
	return ss.str();
}
	


string
VKick::toLine(void) const
{
	return m_name==""?"VKick":m_name;
}
	


ostream&
operator<<(ostream& os, const VKick& vKick)
{
	return os << vKick.toLine();
}



void
VKick::transport(Ion& ion)
{
	ion.setDy( ion.dy() + m_angle );
	if( m_next != NULL ){
		m_next->transport(ion);
	}
}


	
void
VKick::reset(void)
{ }



void 
VKick::setMinAngle(double min_angle)
{
	m_min_angle = min_angle;
}


	
void
VKick::setMaxAngle(double max_angle)
{
	m_max_angle = max_angle;
}


	
void
VKick::setAngle(double angle)
{
	m_angle = angle;
}


	
void
VKick::setNormValue(double norm_angle)
{
	m_angle = m_min_angle + norm_angle * (m_max_angle - m_min_angle);
}














