#include "MirkoInterface.hpp"
#include "DriftTube.hpp"
#include "QuadrupoleMagnet.hpp"
#include "Screen.hpp"
#include "HKick.hpp"
#include "VKick.hpp"
#include "RectangularDipoleMagnet.hpp"

#include <sstream>
#include <fstream>
#include <cmath>



MirkoInterface::MirkoInterface() :
	m_devices()
{ }



MirkoInterface::~MirkoInterface()
{ }



string
MirkoInterface::toString(unsigned int indent) const
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
MirkoInterface::toLine(void) const
{
	return "MirkoInterface";
}
	


ostream&
operator<<(ostream& os, const MirkoInterface& mirkoInterface)
{
	return os << mirkoInterface.toLine();
}



void 
MirkoInterface::readMixFile(const string& filename)
{
	const unsigned int STATE_UNKNOWN = 0;
	const unsigned int STATE_DEVICES = 1;

	unsigned int state = STATE_UNKNOWN;

	ifstream file(filename);
	string line;

	while( std::getline(file, line) )
	{
		if( line.substr(0, 1) == "!" ){
			;
		} else if( line.substr(0, 1) == "$" ){
			if( line.substr(0, 9) == "$ELEMENTE" ){
				state = STATE_DEVICES;
			} else {
				state = STATE_UNKNOWN;
			}
		} else if( state == STATE_DEVICES ){
			
			parseDeviceFromMixFileLine(line);
		}
	} 
}



void 
MirkoInterface::parseDeviceFromMixFileLine(const string& line)
{
	string name = line.substr(3,16);
	int vcode = 0;
	int type = 0;
	int sub = 1;
	double arg1 = 0.0;
	double arg2= 0.0;
	double arg3 = 0.0;
	double arg4 = 0.0;
	
	try{
		vcode = stoi(line.substr(19,4));
	} catch( exception& e){
		vcode = 0;
	}

	try{
		type = stoi(line.substr(23,4));
	} catch( exception& e){
		type = 0;
		cout << __FILE__ << " line " << __LINE__ << ": cannot parse type \"" << line.substr(23,4) << "\" to int, " << e.what() << endl;
	}		

	try{
		sub = stoi(line.substr(27,4));
	} catch( exception& e){
		sub = 1;
	}	

	try{	
		arg1 = stod(line.substr(31,17));
	} catch( exception& e){
		arg1 = 0.0;
	}		

	try{	
		arg2 = stod(line.substr(48,17));
	} catch( exception& e){
		arg2 = 0.0;
	}	

	try{
		arg3 = stod(line.substr(65,12));
	} catch( exception& e){
		arg3 = 0.0;
	}	

	try{
		arg4 = stod(line.substr(77,12));
	} catch( exception& e){
		arg4 = 0.0;
	}	
	
	addDevice(name, vcode, type, sub, arg1, arg2, arg3, arg4);
}



void
MirkoInterface::addDevice(const string& name, int vcode, int type, int sub, double arg1, double arg2, double arg3, double arg4)
{
	switch (type){
		case 2:
			m_devices.push_back( new DriftTube(name, 0.2, 0.2, arg1) );
            break;
		case 3:
			m_devices.push_back( new QuadrupoleMagnet(name, arg3, arg4, arg1, 1000000*arg2*arg2) );
            break;
		case 5:
			m_devices.push_back( new RectangularDipoleMagnet(name, arg3, arg4, arg2 * M_PI * arg1/180., M_PI * arg1/180.) );
            break;						
		case 21:
			m_devices.push_back( new HKick(name, arg1) );
			break;
		case 22:
			m_devices.push_back( new VKick(name, arg1) );
			break;
		case 29:
			m_devices.push_back( new Screen(name, 0.2, 0.2) );
			break;
		case 30:
			break;
		default:
            cout << "MirkoInterface, unkown device type " << type << ". skipped!" << endl;
	}
}


vector<Device*> 
MirkoInterface::getDevices() const
{
	return m_devices;
}

