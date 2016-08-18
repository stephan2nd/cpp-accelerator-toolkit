#include "IonSource.hpp"

#include <sstream>
#include <cmath>
#include <random>
#include <chrono>



IonSource::IonSource() :
	m_mass_number(12),
	m_proton_number(6),
	m_charge(2),
	m_energy(1000),
	m_mu_x(0.),
	m_sigma_x(0.02),
	m_mu_dx(0.005),
	m_sigma_dx(0.01),
	m_mu_y(0.),
	m_sigma_y(0.02),
	m_mu_dy(0.),
	m_sigma_dy(0.01),
	m_mu_dl(0.),
	m_sigma_dl(0.01),
	m_mu_dp(0.),
	m_sigma_dp(0.01),
	m_first_device(NULL)
{ }




IonSource::IonSource(unsigned int mass_number, unsigned int proton_number, int charge, double energy,
	                 double mu_x, double sigma_x, double mu_dx, double sigma_dx, 
	                 double mu_y, double sigma_y, double mu_dy, double sigma_dy, 
	                 double mu_dl, double sigma_dl, double mu_dp, double sigma_dp) :
	m_mass_number(mass_number),
	m_proton_number(proton_number),
	m_charge(charge),
	m_energy(energy),
	m_mu_x(mu_x),
	m_sigma_x(sigma_x),
	m_mu_dx(mu_dx),
	m_sigma_dx(sigma_dx),
	m_mu_y(mu_y),
	m_sigma_y(sigma_y),
	m_mu_dy(mu_dy),
	m_sigma_dy(sigma_dy),
	m_mu_dl(mu_dl),
	m_sigma_dl(sigma_dl),
	m_mu_dp(mu_dp),
	m_sigma_dp(sigma_dp),
	m_first_device(NULL)
{ }



IonSource::~IonSource()
{ }



string
IonSource::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine();
	return ss.str();
}
	


string
IonSource::toLine(void) const
{
	stringstream ss;
	Ion ion(m_mass_number, m_proton_number, m_charge,m_energy);
	ss << ion << "Source";
	return ss.str();
}
	


ostream&
operator<<(ostream& os, const IonSource& ionSource)
{
	return os << ionSource.toLine();
}



void
IonSource::appendDevice(Device* device)
{
	if( m_first_device==NULL ){
		m_first_device=device;
	} else {
		m_first_device->appendDevice(device);
	}
}


	
void
IonSource::run(unsigned int nof_ions)
{
	default_random_engine rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
	
	normal_distribution<double> xdist(m_mu_x,m_sigma_x);
	normal_distribution<double> dxdist(m_mu_dx,m_sigma_dx);
	normal_distribution<double> ydist(m_mu_y,m_sigma_y);
	normal_distribution<double> dydist(m_mu_dy,m_sigma_dy);
	normal_distribution<double> dldist(m_mu_dl,m_sigma_dl);
	normal_distribution<double> dpdist(m_mu_dp,m_sigma_dp);	

	for( unsigned int i=0; i<nof_ions; i++ ){
		Ion ion(m_mass_number, m_proton_number, m_charge, m_energy,
		        xdist(rnd),dxdist(rnd),ydist(rnd),dydist(rnd),dldist(rnd),dpdist(rnd));
		        
		m_first_device->transport(ion);
	}
}





