#include "MacroParticle.hpp"

#include <sstream>



MacroParticle::MacroParticle()
{ }



MacroParticle::~MacroParticle()
{ }



string
MacroParticle::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "nof_particles = " << m_nof_particles 
	   << ")";
	return ss.str();
}
	


string
MacroParticle::toLine(void) const
{
	return "MacroParticle";
}
	


ostream&
operator<<(ostream& os, const MacroParticle& macroParticle)
{
	return os << macroParticle.toLine();
}









