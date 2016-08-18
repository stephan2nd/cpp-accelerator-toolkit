#include "Screen.hpp"

#include <sstream>
#include <fstream>
#include <cmath>



Screen::Screen(const string& name, double width, double height, unsigned int dots_per_meter) :
	Device(name, width, height, 0),
	m_dots_per_meter(dots_per_meter),
	m_pixel(ceil(dots_per_meter*dots_per_meter*width*height)),
	m_missed(0)
{ }



Screen::~Screen()
{ }



string
Screen::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "width = " << m_width << " m, "
	   << "height = " << m_height << " m, "
	   << "dots_per_meter = " << m_dots_per_meter << ", "
	   << "missed = " << m_missed  
	   << ") {\n";
	
	unsigned int cells_hor = m_dots_per_meter * m_width;
	unsigned int cells_ver = m_dots_per_meter * m_height;
	
	for( unsigned int y=0; y<cells_ver; y++ ){
		ss << indention << "\t";
		for( unsigned int x=0; x<cells_hor; x++ ){
			ss << m_pixel[cells_hor * y + x] << " ";		
		}
		ss << "\n";
	}
	ss << indention << "}";	   
	return ss.str();
}
	


string
Screen::toLine(void) const
{
	return m_name==""?"Screen":m_name;
}
	


ostream&
operator<<(ostream& os, const Screen& screen)
{
	return os << screen.toLine();
}



void
Screen::transport(Ion& ion)
{
	fillHistogram(ion.x(),ion.y());
	if( m_next != NULL ){
		m_next->transport(ion);
	}
}


	
void
Screen::reset(void)
{ 
	fill(m_pixel.begin(), m_pixel.end(), 0);
	m_missed = 0;
}



void
Screen::exportHistogram(const string& filename) const
{
	ofstream outfile;
	outfile.open(filename, ios::out | ios::trunc );
	
	unsigned int cells_hor = m_dots_per_meter * m_width;
	unsigned int x = 0;
	unsigned int y = 0;
	outfile << cells_hor << "\n";
	for( auto it = m_pixel.begin(); it<m_pixel.end(); it++ ){
		outfile << x << "," << y << "," << *it << "\n";
		x++;
		if( x == cells_hor ){ 
			x = 0;
			y++;
		} 
	}	
	
	outfile.close();		
}



void 
Screen::exportHistogram(void) const
{
	exportHistogram(m_name + ".dat");
}



// @TODO optimize
void
Screen::fillHistogram(double x, double y)
{
	double half_width  = 0.5*m_width;
	double half_height = 0.5*m_height;
	unsigned int dots_hor = m_dots_per_meter * m_width;
	unsigned int dots_ver = m_dots_per_meter * m_height;
		
	if ( x < half_width and
		 x > -half_width and
		 y < half_height and
		 y > -half_height){
		
		double x_ = floor((x*m_dots_per_meter) + 0.5*dots_hor);
		double y_ = floor((y*m_dots_per_meter) + 0.5*dots_ver);			
		unsigned int pos = dots_hor * y_ + x_;
		
		m_pixel[pos] += 1;
	} else {
		m_missed += 1;
	}
}



