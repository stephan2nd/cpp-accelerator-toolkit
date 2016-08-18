#include "Dummy.hpp"

#include <sstream>



Dummy::Dummy()
{ }



Dummy::~Dummy()
{ }



string
Dummy::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "nomenclature = " << m_nomenclature << ", "
	   << "width = " << m_width << " m, "
	   << "height = " << m_height << " m, "
	   << "length = " << m_length << " m" 
	   << ")";
	return ss.str();
}
	


string
Dummy::toLine(void) const
{
	return m_nomenclature==""?"Dummy":m_nomenclature;
}
	


ostream&
operator<<(ostream& os, const Dummy& dummy)
{
	return os << dummy.toLine();
}









