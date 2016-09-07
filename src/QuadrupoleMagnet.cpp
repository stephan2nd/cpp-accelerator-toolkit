#include "QuadrupoleMagnet.hpp"

#include <sstream>
#include <cmath>



QuadrupoleMagnet::QuadrupoleMagnet(const string& name, double width, double height, double length, double strength) :
	Device("QuadrupoleMagnet", name, width, height, length),
	m_strength(strength)
{ }



QuadrupoleMagnet::QuadrupoleMagnet(const string& name, double width, double height, double length, double min_strength, double max_strength) :
	Device("QuadrupoleMagnet", name, width, height, length),
	m_strength(0),
	m_min_strength(min_strength),
	m_max_strength(max_strength)
{ }



QuadrupoleMagnet::~QuadrupoleMagnet()
{ }



string
QuadrupoleMagnet::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "width = " << m_width << " m, "
	   << "height = " << m_height << " m, "
	   << "length = " << m_length << " m, "
	   << "strength = " << m_strength << " 1/m^2, "
	   << "mirko_strength = " << (m_strength/abs(m_strength))*sqrt(abs(m_strength))/1000. << " 1/mm"
	   << ")";
	return ss.str();
}
	


string
QuadrupoleMagnet::toLine(void) const
{
	return m_name==""?"QuadrupoleMagnet":m_name;
}
	


ostream&
operator<<(ostream& os, const QuadrupoleMagnet& quadrupoleMagnet)
{
	return os << quadrupoleMagnet.toLine();
}



void
QuadrupoleMagnet::transport(Ion& ion)
{
	double sqrts = sqrt(abs(m_strength));
	double omega = m_length * sqrts;		
	double cosomega  = cos(omega);
	double coshomega = cosh(omega);
	double sinomega  = sin(omega);
	double sinhomega = sinh(omega);
	
	if( m_strength<0 ){
		double x = cosomega*ion.x() + (sinomega/sqrts)*ion.dx();
		double dx = -sinomega*sqrts*ion.x() + cosomega*ion.dx();
		double y = coshomega*ion.y() + (sinhomega/sqrts)*ion.dy();
		double dy = sinhomega*sqrts*ion.y() + coshomega*ion.dy();
		ion.setX( x );
		ion.setDx( dx );
		ion.setY( y );
		ion.setDy( dy );
	} else if( m_strength>0 ){
		double x = coshomega*ion.x() + (sinhomega/sqrts)*ion.dx();
		double dx = sinhomega*sqrts*ion.x() + coshomega*ion.dx();
		double y = cosomega*ion.y() + (sinomega/sqrts)*ion.dy();
		double dy = -sinomega*sqrts*ion.y() + cosomega*ion.dy();
		ion.setX( x );
		ion.setDx( dx );
		ion.setY( y );
		ion.setDy( dy );
	} else {
		ion.setX( ion.x() + m_length * ion.dx() );
		ion.setY( ion.y() + m_length * ion.dy() );	
	}
	
	if( not isParticleLost(ion) ){
		if( m_next != NULL ){
			m_next->transport(ion);
		}
	}
}


	
void
QuadrupoleMagnet::reset(void)
{ }



string
QuadrupoleMagnet::mirkoMakroString(void) const
{
	stringstream ss;
	ss << "kele, \'" << m_name << "\', 5, " <<  (m_strength/abs(m_strength))*sqrt(abs(m_strength))/1000. << ", *\n";
	return ss.str();
}



void 
QuadrupoleMagnet::setMinStrength(double min_strength)
{
	m_min_strength = min_strength;
}


	
void
QuadrupoleMagnet::setMaxStrength(double max_strength)
{
	m_max_strength = max_strength;
}
	
	
	
void
QuadrupoleMagnet::setStrength(double strength)
{
	m_strength = strength;
}
	
	
	
void
QuadrupoleMagnet::setNormValue(double norm_strength)
{
	m_strength = m_min_strength + norm_strength * (m_max_strength - m_min_strength);
}




