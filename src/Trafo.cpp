#include "Trafo.hpp"

#include <sstream>



Trafo::Trafo(const string& name) :
	Device(name, 0, 0, 0),
	m_counts(0)
{ }



Trafo::~Trafo()
{ }



string
Trafo::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "counts = " << m_counts
	   << ")";
	return ss.str();
}
	


string
Trafo::toLine(void) const
{
	return m_name==""?"Trafo":m_name;
}
	


ostream&
operator<<(ostream& os, const Trafo& trafo)
{
	return os << trafo.toLine();
}



void
Trafo::transport(Ion& ion)
{
	m_counts++;
	if( m_next != NULL ){
		m_next->transport(ion);
	}
}


	
void
Trafo::reset(void)
{ 
	m_counts = 0;
}



double 
Trafo::getCounts(void)
{
	return m_counts;
}



