#include "DriftTube.hpp"

#include <sstream>



DriftTube::DriftTube(const string& name, double width, double height, double length) :
	Device("DriftTube", name, width, height, length)
{ }



DriftTube::~DriftTube()
{ }



string
DriftTube::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "width = " << m_width << " m, "
	   << "height = " << m_height << " m, "
	   << "length = " << m_length << " m" 
	   << ")";
	return ss.str();
}
	


string
DriftTube::toLine(void) const
{
	return m_name==""?"Drifttube":m_name;
}
	


ostream&
operator<<(ostream& os, const DriftTube& driftTube)
{
	return os << driftTube.toLine();
}



void
DriftTube::transport(Ion& ion)
{
	ion.setX( ion.x() + m_length * ion.dx() );
	ion.setY( ion.y() + m_length * ion.dy() );	
	
	if( not isParticleLost(ion) ){
		if( m_next != NULL ){
			m_next->transport(ion);
		}
	}
}


	
void
DriftTube::reset(void)
{ }







