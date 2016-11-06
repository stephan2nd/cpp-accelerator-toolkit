#include "Bunch.hpp"

#include <sstream>



Bunch::Bunch(unsigned int nof_macro_particles, unsigned int bunch_current, double rf_frequency)
{ }



Bunch::~Bunch()
{ }



string
Bunch::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << ")";
	return ss.str();
}
	


string
Bunch::toLine(void) const
{
	return "Bunch";
}
	


ostream&
operator<<(ostream& os, const Bunch& bunch)
{
	return os << bunch.toLine();
}









