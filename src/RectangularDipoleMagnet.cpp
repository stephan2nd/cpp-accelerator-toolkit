#include "RectangularDipoleMagnet.hpp"

#include <sstream>
#include <cmath>



RectangularDipoleMagnet::RectangularDipoleMagnet(const string& name, double width, double height, double length, double angle) :
	Device("RectangularDipoleMagnet", name, width, height, length),
	m_angle(angle)
{ }



RectangularDipoleMagnet::~RectangularDipoleMagnet()
{ }



string
RectangularDipoleMagnet::toString(unsigned int indent) const
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
RectangularDipoleMagnet::toLine(void) const
{
	return m_name==""?"RectangularDipoleMagnet":m_name;
}
	


ostream&
operator<<(ostream& os, const RectangularDipoleMagnet& rectangularDipoleMagnet)
{
	return os << rectangularDipoleMagnet.toLine();
}



void
RectangularDipoleMagnet::transport(Ion& ion)
{
	if( m_angle != 0 ){
		
		double r        = m_length/m_angle;
		double cosangle = cos(m_angle);
		double sinangle = sin(m_angle);
		double tanangle = tan(0.5 * m_angle);
		
		// pole face
		ion.setDx( tanangle * ion.x() / r + ion.dx() );
		ion.setDy( -tanangle * ion.y() / r + ion.dy() );		
		
		// dipole
		double x = cosangle*ion.x() + r*sinangle*ion.dx() + r*(1.-cosangle)*ion.dp();
		double dx = -(1/r)*sinangle*ion.x() +  cosangle*ion.dx() + sinangle*ion.dp();
		double y = ion.y()+m_length*ion.dy();
		double dl = -sinangle*ion.x() - r*(1.-cosangle)*ion.dx() - r*(m_length-r*sinangle)*ion.dp();	
		ion.setX( x );			
		ion.setDx( dx );	
		ion.setY( y );
		ion.setDl( dl );

		// pole face
		ion.setDx( tanangle * ion.x() / r + ion.dx() );
		ion.setDy( -tanangle * ion.y() / r + ion.dy() );
		
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
RectangularDipoleMagnet::reset(void)
{ }





