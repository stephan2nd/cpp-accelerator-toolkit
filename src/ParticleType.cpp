#include "ParticleType.hpp"

#include <sstream>



ParticleType::ParticleType(unsigned int neutron_number, unsigned int proton_number, unsigned int electron_number) :
	m_neutron_number(neutron_number),
	m_proton_number(proton_number),
	m_electron_number(electron_number)
{ }



ParticleType::~ParticleType()
{ }



string
ParticleType::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "neutron_number = " << m_neutron_number << ", "
	   << "proton_number = " << m_proton_number << " , "
	   << "electron_number = " << m_electron_number 
	   << ")";
	return ss.str();
}
	


string
ParticleType::toLine(void) const
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

	if (mass_number()!=0){
		ss << mass_number();
	}	
	
	if (m_proton_number>117){ 
		ss << "??";
	} else {
		ss << symbol[m_proton_number];
	}
	
	if (charge_number()>0){
		ss << "+" << charge_number();
	} else if (charge_number()<0){
		ss << charge_number();
	}

	return ss.str();
}
	


ostream&
operator<<(ostream& os, const ParticleType& particleType)
{
	return os << particleType.toLine();
}









