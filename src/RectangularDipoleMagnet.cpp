#include "RectangularDipoleMagnet.hpp"

#include <sstream>



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









