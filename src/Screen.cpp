#include "Screen.hpp"

#include <sstream>
#include <fstream>
#include <cmath>



Screen::Screen(const string& name, double width, double height, unsigned int dots_per_meter) :
	Device("Screen", name, width, height, 0),
	m_dots_per_meter(dots_per_meter),
	m_pixel(ceil(dots_per_meter * dots_per_meter * width * height)),
	m_missed(0),
	m_counts(0)
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
	   << "missed = " << m_missed << ", "
	   << "counts = " << m_counts 
	   << ") {\n";
	
	unsigned int cells_hor = m_dots_per_meter * m_width;
	unsigned int cells_ver = m_dots_per_meter * m_height;
	
	unsigned int x_factor = cells_hor / 50;	
	unsigned int y_factor = cells_hor / 25;	
	
/*	for( unsigned int y=0; y<cells_ver; y+=y_factor ){
		ss << indention << "\t|";
		for( unsigned int x=0; x<cells_hor; x+=x_factor ){
			unsigned int sum = 0;
			for( unsigned int i=0; i<y_factor; i++ ){
				for( unsigned int j=0; j<x_factor; j++ ){			
					sum += m_pixel[cells_hor * (y + i) + (x + j)];
				}
			}
			ss << asciiRepresentation(sum, x_factor, y_factor);
		}
		ss << "|\n";
	}*/
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
	if( !m_ignore ){
		fillHistogram(ion.x(),ion.y());
	}
	
	if( m_next != NULL ){
		m_next->transport(ion);
	}
}


	
void
Screen::reset(void)
{ 
	fill(m_pixel.begin(), m_pixel.end(), 0);
	m_missed = 0;
	m_counts = 0;
}



void
Screen::exportHistogram(const string& filename) const
{
	ofstream outfile;
	outfile.open(filename, ios::out | ios::trunc );
	
	unsigned int dots_hor = m_dots_per_meter * m_width;
	unsigned int dots_ver = m_dots_per_meter * m_height;
	unsigned int x = 0;
	unsigned int y = 0;
	
	outfile << "hist2d" << "\n";
	outfile << dots_hor << "\n";
	outfile << dots_ver << "\n";	
	
	for( auto it = m_pixel.begin(); it<m_pixel.end(); it++ ){
		outfile << x << "," << y << "," << *it << "\n";
		x++;
		if( x == dots_hor ){ 
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



void
Screen::fillHistogram(double x, double y)
{
	double half_width  = 0.5 * m_width;
	double half_height = 0.5 * m_height;
	unsigned int dots_hor = m_dots_per_meter * m_width;
	unsigned int dots_ver = m_dots_per_meter * m_height;
		
	if ( x < half_width and
		 x > -half_width and
		 y < half_height and
		 y > -half_height){
		
		unsigned int x_ = round((x * m_dots_per_meter) + 0.5 * dots_hor);
		unsigned int y_ = round((y * m_dots_per_meter) + 0.5 * dots_ver);		
			
		unsigned int pos = dots_hor * y_ + x_;
		
		if( pos < m_pixel.size() ){
			m_pixel.at(pos) += 1;
			m_counts ++;
		}
	} else {
		m_missed += 1;
	}	
}



string
Screen::asciiRepresentation(unsigned int number, unsigned int x_factor, unsigned int y_factor) const
{	
	double p = double(number) / double(0.5 * x_factor * y_factor * maxPixelValue());
	
	if( p > 0.9 ){
		return "M";
	} else if( p > 0.8 ){
		return "X";
	} else if( p > 0.7 ){
		return "Z";
	} else if( p > 0.5 ){
		return "%";		
	} else if( p > 0.3 ){
		return "+";
	} else if( p > 0.1 ){
		return ":";
	} else if( p > 0.05 ){
		return "´";		
	} else {
		return " ";
	}
}



unsigned int
Screen::maxPixelValue(void) const
{
	unsigned int max = 0;

	for( auto it = m_pixel.begin(); it<m_pixel.end(); it++ ){
		if( max < *it ){ max = *it;	} 
	}
	
	return max;
}




