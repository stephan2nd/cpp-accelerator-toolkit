#include "Ion.hpp"

#include <sstream>



Ion::Ion() :
	m_mass_number(12),
	m_proton_number(6),
	m_charge(2),
	m_energy(1000),
	m_x(0),
	m_dx(0),
	m_y(0),
	m_dy(0),
	m_dl(0),
	m_dp(0)
{ }



Ion::Ion(unsigned int mass_number, unsigned int proton_number, int charge, double energy, double x, double dx, double y, double dy, double dl, double dp) :
	m_mass_number(mass_number),
	m_proton_number(proton_number),
	m_charge(charge),
	m_energy(energy),
	m_x(x),
	m_dx(dx),
	m_y(y),
	m_dy(dy),
	m_dl(dl),
	m_dp(dp)
{ }



Ion::Ion(const Ion& ion) :
	m_mass_number(ion.m_mass_number),
	m_proton_number(ion.m_proton_number),
	m_charge(ion.m_charge),
	m_energy(ion.m_energy),
	m_x(ion.m_x),
	m_dx(ion.m_dx),
	m_y(ion.m_y),
	m_dy(ion.m_dy),
	m_dl(ion.m_dl),
	m_dp(ion.m_dp)
{ }



Ion::~Ion()
{ }



string
Ion::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "E = "  << m_energy << " eV, "
	   << "x = "  << m_x  << " m, "
	   << "dx = " << m_dx << " rad, "
	   << "y = "  << m_y  << " m, "
	   << "dy = " << m_dy << " rad, "
	   << "dl = " << m_dl << " m, "
	   << "dp = " << m_dp 
	   << ")";
	return ss.str();
}
	


string
Ion::toLine(void) const
{
	string symbol[117] = {"e", "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na",
	                      "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti",
	                      "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", 
	                      "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru",
	                      "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs",
	                      "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy",
	                      "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir",
	                      "Pt", "Au", "Hg", "TI", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra",
	                      "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es",
	                      "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds",
	                      "Rg", "Cn", "Uut", "Fl", "Uup", "Lv"};

	stringstream ss;

	if (m_mass_number!=0){
		ss << m_mass_number;
	}	
	
	if (m_proton_number>117){ 
		ss << "??";
	} else {
		ss << symbol[m_proton_number];
	}
	
	if (m_charge>0){
		ss << "+" << m_charge;
	} else if (m_charge<0){
		ss << m_charge;
	}

	return ss.str();
}
	


Ion&
Ion::operator=(const Ion& ion)
{
	m_mass_number   = ion.m_mass_number;
	m_proton_number = ion.m_proton_number;
	m_charge        = ion.m_charge;
	m_energy        = ion.m_energy;
	m_x             = ion.m_x;
	m_dx            = ion.m_dx;
	m_y             = ion.m_y;
	m_dy            = ion.m_dy;
	m_dl            = ion.m_dl;
	m_dp            = ion.m_dp;
	return *this;
}



ostream&
operator<<(ostream& os, const Ion& ion)
{
	return os << ion.toLine();
}









