#ifndef ION_SOURCE_HPP_
#define ION_SOURCE_HPP_

#include <iostream>
#include <string>

#include "Device.hpp"



using namespace std;

class IonSource
{
friend unsigned int test_ionSource(bool verbose);

public:

	IonSource();

	IonSource(unsigned int mass_number, unsigned int proton_number, int charge, double energy,
	          double mu_x, double sigma_x, double mu_dx, double sigma_dx, 
	          double mu_y, double sigma_y, double mu_dy, double sigma_dy, 
	          double mu_dl, double sigma_dl, double mu_dp, double sigma_dp);

	virtual
	~IonSource();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const IonSource& ionSource);
	
	IonSource&
	operator=(const IonSource& ion_source);

	void
	appendDevice(Device* device);
	
	void
	run(unsigned int nof_ions);
	
private:

	unsigned int m_mass_number;
	
	unsigned int m_proton_number;
	
	int m_charge;
	
	double m_energy;

	double m_mu_x;
	
	double m_sigma_x;
	
	double m_mu_dx;
	
	double m_sigma_dx;

	double m_mu_y;
	
	double m_sigma_y;
	
	double m_mu_dy;
	
	double m_sigma_dy;
	
	double m_mu_dl;
	
	double m_sigma_dl;
	
	double m_mu_dp;
	
	double m_sigma_dp;

	Device* m_first_device;
};

#endif /* ION_SOURCE_HPP_ */
