#include "Accelerator.hpp"

#include <sstream>



Accelerator::Accelerator() :
	m_ion_source(),
	m_devices()
{ }



Accelerator::~Accelerator()
{ }



string
Accelerator::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " {\n";
	for( auto it_device=m_devices.begin(); it_device<m_devices.end(); it_device++ ){
		ss << indention << (*it_device)->toString(indent+1) << "\n";
	}	
	ss << indention << "}";
	return ss.str();
}
	


string
Accelerator::toLine(void) const
{
	stringstream ss;
	ss << "Accelerator ( ion_source = " << m_ion_source.toString() << " )";
	return ss.str();
}
	


ostream&
operator<<(ostream& os, const Accelerator& accelerator)
{
	return os << accelerator.toLine();
}


	
void
Accelerator::appendDevice(Device* device)
{
	m_devices.push_back(device);
	m_ion_source.appendDevice(device);
}



Device*
Accelerator::getDeviceByName(const string& name)
{
	for( auto it=m_devices.begin(); it<m_devices.end(); it++ ){
		if( name == (*it)->getName() ){
			return *it;
		}
	}
	return NULL;
}


	
void
Accelerator::startSimulation(unsigned int nof_ions, bool threaded, unsigned int nof_threads)
{
	if (threaded){
		//cout << "start simulation with " << nof_ions << " ions in " << nof_threads << " threads" << endl;
	} else {
		//cout << "start simulation with " << nof_ions << " ions in 1 thread" << endl;
	}
	
	
	for( auto it_device=m_devices.begin(); it_device<m_devices.end(); it_device++ ){
		(*it_device)->reset();
	}
	
	if( threaded ){
	
		unsigned int ions_per_core = nof_ions/nof_threads;
		
		thread* threadlist = new thread[nof_threads];
		
		for( unsigned int i=0; i<nof_threads; i++ ){
			try{
				threadlist[i] = thread(&IonSource::run, m_ion_source, ions_per_core);
			} catch(...) {
				cout << "Error in " << __FILE__ << " line " << __LINE__ << " thread limit exceeded with " << nof_threads << " threads" << endl;
				exit(0);
			}
		}
		
		for( unsigned int i=0; i<nof_threads; i++ ){ 
			threadlist[i].join();
		}

		delete[] threadlist;	
	} else {
		m_ion_source.run(nof_ions);
	}	
}



void
Accelerator::setNormValues(vector<double> values)
{
	int i = 0;
	for( auto it=m_devices.begin(); it<m_devices.end(); it++ ){
		if( (*it)->settingSize() == 1 ){
			(*it)->setNormValue(values.at(i));
			i++;
		}
	}
}



int
Accelerator::settingSize(void)
{
	int settingSize = 0;
	for( auto it=m_devices.begin(); it<m_devices.end(); it++ ){
		settingSize += (*it)->settingSize();
	}
	return settingSize;
}







