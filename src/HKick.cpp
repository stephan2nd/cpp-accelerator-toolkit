#include "HKick.hpp"

#include <sstream>



HKick::HKick(const string& name, double angle) :
	Device("HKick", name, 0, 0, 0),
	m_angle(angle)
{ }

	

HKick::HKick(const string& name, double min_angle, double max_angle) :
	Device("HKick", name, 0, 0, 0),
	m_angle(0),
	m_min_angle(min_angle),
	m_max_angle(max_angle)
{ }

	

HKick::~HKick()
{ }



string
HKick::toString(unsigned int indent) const
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
HKick::toLine(void) const
{
	return m_name==""?"HKick":m_name;
}
	


ostream&
operator<<(ostream& os, const HKick& hKick)
{
	return os << hKick.toLine();
}



void
HKick::transport(Ion& ion)
{
	ion.setDx( ion.dx() + m_angle );
	if( m_next != NULL ){
		m_next->transport(ion);
	}
}


	
void
HKick::reset(void)
{ }



void 
HKick::setMinAngle(double min_angle)
{
	m_min_angle = min_angle;
}


	
void
HKick::setMaxAngle(double max_angle)
{
	m_max_angle = max_angle;
}


	
void
HKick::setAngle(double angle)
{
	m_angle = angle;
}


	
void
HKick::setNormValue(double norm_angle)
{
	m_angle = m_min_angle + norm_angle * (m_max_angle - m_min_angle);
}














