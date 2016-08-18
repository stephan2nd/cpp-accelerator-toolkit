#include "Slit.hpp"

#include <sstream>



Slit::Slit(const string& name, double pos_left, double pos_right , double pos_bottom, double pos_top) :
	Device(name, 0, 0, 0),
	m_pos_left(pos_left),	
	m_pos_right(pos_right),	
	m_pos_top(pos_top),
	m_pos_bottom(pos_bottom),
	m_count_left(0),
	m_count_right(0),
	m_count_top(0),
	m_count_bottom(0)
{ 
	if( pos_left >= pos_right || pos_bottom >= pos_top ){
		cout << "Error in " << __FILE__ << " line " << __LINE__ << ": slit is closed"<< endl;
		exit(0);	
	}
}



Slit::~Slit()
{ }



string
Slit::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "pos_left = " << m_pos_left << " m, "
	   << "pos_right = " << m_pos_right << " m, "
	   << "pos_top = " << m_pos_top << " m, "
	   << "pos_bottom = " << m_pos_bottom << " m, "
	   << ") {\n"
	   
	   << indention << "\t"
	   << "count_left = " << m_count_left << ", "
	   << "count_right = " << m_count_right << ", "
	   << "count_top = " << m_count_top << ", "
	   << "count_bottom = " << m_count_bottom
	   << "\n"
	   << indention << "}";	   
	return ss.str();
}
	


string
Slit::toLine(void) const
{
	return m_name==""?"Slit":m_name;
}
	


ostream&
operator<<(ostream& os, const Slit& slit)
{
	return os << slit.toLine();
}



void
Slit::transport(Ion& ion)
{
	if( ion.x() < m_pos_left ){
		m_count_left   += 1;
	} else if( ion.x() > m_pos_right ){
		m_count_right  += 1;
	} else if( ion.y() > m_pos_top ){
		m_count_top    += 1;
	} else if( ion.y() < m_pos_bottom ){
		m_count_bottom += 1;
	} else if( m_next != NULL ){
		m_next->transport(ion);
	}
}


	
void
Slit::reset(void)
{ 
	m_count_left   = 0;
	m_count_right  = 0;
	m_count_top    = 0;
	m_count_bottom = 0;
}





