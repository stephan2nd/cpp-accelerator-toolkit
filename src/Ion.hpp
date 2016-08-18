#ifndef ION_HPP_
#define ION_HPP_

#include <iostream>
#include <string>



using namespace std;

class Ion
{
friend unsigned int test_ion(bool verbose);

public:

	Ion();
	
	Ion(unsigned int mass_number, unsigned int proton_number, int charge, double energy=0, double x=0, double dx=0, double y=0, double dy=0, double dl=0, double dp=0);
	
	Ion(const Ion& ion);

	virtual
	~Ion();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	Ion&
	operator=(const Ion& ion);
	
	friend ostream&
	operator<<(ostream& os, const Ion& ion);

	inline double x() const { return m_x; }
	
	inline double dx() const { return m_dx; }	

	inline double y() const { return m_y; }	
	
	inline double dy() const { return m_dy; }	
	
	inline double dp() const { return m_dp; }
		
	inline void setX(double x) { m_x = x; }
	
	inline void setDx(double dx) { m_dx = dx; }	
	
	inline void setY(double y) { m_y = y; }	
	
	inline void setDy(double dy) { m_dy = dy; }	
	
	inline void setDl(double dl) { m_dl = dl; }

private:

	unsigned int m_mass_number;
	
	unsigned int m_proton_number;
	
	int m_charge;
	
	double m_energy;

	double m_x;
	
	double m_dx;
	
	double m_y;
	
	double m_dy;
	
	double m_dl;
	
	double m_dp;
};

#endif /* ION_HPP_ */
