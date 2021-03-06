#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <atomic>

#include "Device.hpp"



using namespace std;

class Screen : public Device
{
friend unsigned int test_screen(bool verbose);

public:

	Screen(const string& name, double width, double height, unsigned int dots_per_meter = 1000);

	virtual
	~Screen();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const Screen& screen);

	void
	transport(Ion& ion);	
	
	void
	reset(void);
	
	void
	exportHistogram(const string& filename) const;
	
	void 
	exportHistogram(void) const;
	
private:
	
	void
	fillHistogram(double x, double y);
	
	string
	asciiRepresentation(unsigned int number, unsigned int x_factor, unsigned int y_factor) const;
	
	unsigned int
	maxPixelValue(void) const;
	
	unsigned int m_dots_per_meter;

	vector<atomic<unsigned int>> m_pixel;
	
	atomic<unsigned int> m_missed;
	
	atomic<unsigned int> m_counts;		
};

#endif /* SCREEN_HPP_ */
