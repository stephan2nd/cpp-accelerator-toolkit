#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>

#include "Accelerator.hpp"
#include "Ion.hpp"
#include "IonSource.hpp"
#include "DriftTube.hpp"
#include "QuadrupoleMagnet.hpp"
#include "DipoleMagnet.hpp"
#include "Trafo.hpp"
#include "Screen.hpp"
#include "ProfileGrid.hpp"
#include "Slit.hpp"
#include "HKick.hpp"



using namespace std;



unsigned int testIfTrue(bool b, string description)
{
	if(b){
		cout << "\033[1;32mTest OK\033[0m\t\t" << description << endl;
		return 0;
	} else {
		cout << "\033[1;31mTest FAILED\033[0m\t" << description << endl;
		return 1;
	}
}



template<typename T, typename U>
unsigned int testIfEqual(T a, U b, string description)
{
	if(a==b){
		cout << "\033[1;32mTest OK\033[0m\t\t" << description << " -> " << a << " == " << b << endl;
		return 0;
	} else {
		cout << "\033[1;31mTest FAILED\033[0m\t" << description << " -> " << a << " != " << b<< endl;
		return 1;
	}
}



template<typename T, typename U>
unsigned int testIfNotEqual(T a, U b, string description)
{
	if(!(a==b)){
		cout << "\033[1;32mTest OK\033[0m\t\t" << description << " -> " << a << " != " << b << endl;
		return 0;
	} else {
		cout << "\033[1;31mTest FAILED\033[0m\t" << description << " -> " << a << " == " << b<< endl;
		return 1;
	}
}



template<typename T, typename U, typename V>
unsigned int testIfEqual(T a, U b, V diff, string description)
{
	if(abs(a-b)<diff){
		cout << "\033[1;32mTest OK\033[0m\t\t" << description << " -> " << a << " = " << b << endl;
		return 0;
	} else {
		cout << "\033[1;31mTest FAILED\033[0m\t" << description << " -> " << a << " != " << b<< endl;
		return 1;
	}
}



unsigned int test_ion(bool verbose)
{
	cout << "\033[1;36mRun Test: test_ion\033[0m" << endl;

	unsigned int failcount = 0;


	Ion ion;
	Ion uranium(238,92,28);
	Ion electron(0,0,-1);
	Ion proton(1,1,1);
	DriftTube* tube = new DriftTube("",0.4,0.2,2.0);
	DriftTube* tube2 = new DriftTube("",0.4,0.2,0.5);	
	QuadrupoleMagnet* qm1 = new QuadrupoleMagnet("DQ1",0.4,0.2,0.5,-0.5);
	QuadrupoleMagnet* qm2 = new QuadrupoleMagnet("DQ2",0.4,0.2,0.5,0.3);	
	Trafo* dt1 = new Trafo("DT1");
	Trafo* dt2 = new Trafo("DT2");	
	DipoleMagnet* dm = new DipoleMagnet("DM",0.4,0.2,1.0,1.0);
	Screen* sc1 = new Screen("Sc1",0.2,0.2,100);
	Screen* sc2 = new Screen("Sc2",0.2,0.2,100);	
	ProfileGrid* pg1 = new ProfileGrid("Pg1",0.2,0.2,20);
	Slit* slit = new Slit("",-0.02,0.02,-0.02,0.02);
	HKick* hk = new HKick("",-0.04);
	
	Accelerator acc;
	acc.appendDevice(dt1);
	acc.appendDevice(pg1);
	acc.appendDevice(sc1);	
	acc.appendDevice(tube);
	acc.appendDevice(qm1);
	acc.appendDevice(slit);
	acc.appendDevice(hk);	
	acc.appendDevice(tube2);	
	acc.appendDevice(qm2);
	acc.appendDevice(dm);	
	acc.appendDevice(dt2);
	acc.appendDevice(sc2);
		
	//acc.startSimulation(8000000,true,thread::hardware_concurrency());
	acc.startSimulation(800000,true);	
	
	if(verbose){
		cout << ion << endl;
		cout << uranium << endl;
		cout << electron << endl;
		cout << proton << endl;		
		cout << ion.toString() << endl;
		cout << tube->toString() << endl;
		cout << acc.toString() << endl;		
	}	
	
	return failcount;
}



/** ##################################################################################*/



unsigned int test_mirko(bool verbose)
{
	cout << "\033[1;36mRun Test: test_mirko\033[0m" << endl;

	unsigned int failcount = 0;

	Accelerator acc;
	acc.appendDevicesFromMirkoFile("mirko_test_file.mix");
	if(verbose){ cout << "m3all.mix loaded" << endl; }
	
	if(verbose){


		cout << acc.toString() << endl;		
	}	
	
	return failcount;
}



/** ##################################################################################*/



void test(bool verbose)
{
	unsigned int failcount = 0;

	failcount+=test_ion(verbose);
	failcount+=test_mirko(verbose);

	if(failcount==0){
		cout << "\033[1;32mAll tests passed!\033[0m\t\t" << endl;
	} else {
		cout << "\033[1;31m" << failcount << " tests failed\033[0m\t\t" << endl;
	}
}



/** ##################################################################################*/

int main(int argc, char* argv[])
{
	clock_t begin = clock();
	time_t start, finish; 
	time(&start); 
	
	if( argc > 1 && string(argv[1]) == string("-v")){
		test(true);
	} else {
		test(false);
	}

	time(&finish); 
	float diff = (((float)clock()-(float)begin)/CLOCKS_PER_SEC);
	cout << "CPU-time: " << diff << " s" << endl;	
	cout << "runtime: " << difftime(finish,start) << " s" << endl;
//	cout << "multi core efficiency: " << 100*(thread::hardware_concurrency()*difftime(finish,start))/diff << "%" << endl;
	
}
