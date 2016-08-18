#include "ProfileGrid.hpp"

#include <sstream>
#include <cmath>



ProfileGrid::ProfileGrid(const string& name, double width, double height, unsigned int  nof_wires) :
	Device(name, width, height, 0),
	m_wires_hor(nof_wires),
	m_wires_ver(nof_wires)
{ }



ProfileGrid::~ProfileGrid()
{ }



string
ProfileGrid::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "width = " << m_width << " m, "
	   << "height = " << m_height << " m, "
	   << ") {\n";

	ss << indention << "\t";
	for( unsigned int x=0; x<m_wires_hor.size(); x++ ){
		ss << m_wires_hor[x] << " ";
	}	   
	ss << "\n";
	
	ss << indention << "\t";
	for( unsigned int y=0; y<m_wires_ver.size(); y++ ){
		ss << m_wires_ver[y] << " ";
	}	   
	ss << "\n";
	
	ss << indention << "}";	   	   
	return ss.str();
}
	


string
ProfileGrid::toLine(void) const
{
	return m_name==""?"ProfileGrid":m_name;
}
	


ostream&
operator<<(ostream& os, const ProfileGrid& profileGrid)
{
	return os << profileGrid.toLine();
}



void
ProfileGrid::transport(Ion& ion)
{
	fillHistograms(ion.x(),ion.y());
	if( m_next != NULL ){
		m_next->transport(ion);
	}
}


	
void
ProfileGrid::reset(void)
{ 
	fill(m_wires_hor.begin(), m_wires_hor.end(), 0);
	fill(m_wires_ver.begin(), m_wires_ver.end(), 0);
}



void
ProfileGrid::fillHistograms(double x, double y)
{
	double half_width  = 0.5 * m_width;
	double half_height = 0.5 * m_height;	
	unsigned int cells_hor = m_wires_hor.size();
	unsigned int cells_ver = m_wires_ver.size();
				
	if( x < half_width and x > -half_width ){
		unsigned int pos = floor((x*cells_hor/m_width) + 0.5*cells_hor);		
		m_wires_hor[pos] += 1;
	}

	if ( y < half_height and y > -half_height ){
		unsigned int pos = floor((y*cells_ver/m_height) + 0.5*cells_ver);		
		m_wires_ver[pos] += 1;
	}
}








