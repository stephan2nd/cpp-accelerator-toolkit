#include "DipoleMagnet.hpp"

#include <sstream>
#include <cmath>


DipoleMagnet::DipoleMagnet(const string& name, double width, double height, double length, double angle) :
	Device("DipoleMagnet", name, width, height, length),
	m_angle(angle)
{ }



DipoleMagnet::~DipoleMagnet()
{ }



string
DipoleMagnet::toString(unsigned int indent) const
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
	   << "angle = " << m_angle  
	   << ")";
	return ss.str();
}
	


string
DipoleMagnet::toLine(void) const
{
	return m_name==""?"DipoleMagnet":m_name;
}
	


ostream&
operator<<(ostream& os, const DipoleMagnet& dipoleMagnet)
{
	return os << dipoleMagnet.toLine();
}




void
DipoleMagnet::transport(Ion& ion)
{
	if( m_angle != 0 ){
		
		double r        = m_length/m_angle;
		double cosangle = cos(m_angle);
		double sinangle = sin(m_angle);
			
		double x = cosangle*ion.x() + r*sinangle*ion.dx() + r*(1.-cosangle)*ion.dp();
		double dx = -(1/r)*sinangle*ion.x() +  cosangle*ion.dx() + sinangle*ion.dp();
		double y = ion.y()+m_length*ion.dy();
		double dl = -sinangle*ion.x() - r*(1.-cosangle)*ion.dx() - r*(m_length-r*sinangle)*ion.dp();	
		ion.setX( x );			
		ion.setDx( dx );	
		ion.setY( y );
		ion.setDl( dl );

	} else {
		ion.setX( ion.x()+m_length * ion.dx() );
		ion.setY( ion.y()+m_length * ion.dy() );	
	}
	
	if( not isParticleLost(ion) ){
		if( m_next != NULL ){
			m_next->transport(ion);
		}
	}
}


	
void
DipoleMagnet::reset(void)
{ }






