//============================================================================
// Name        : bM_02.cpp
// Author      : Francesco Forcher
// Version     : 1.1
// Description : Hello World in C++, Ansi-style
//============================================================================

//... include header files ...

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "BraggStatistic.h"
#include "dbg_macro.h"
#include "Event.h"

//... declare functions to read and dump events ...
const Event* read(std::ifstream& file);
void dump(const Event& ev);

int main(int argc, char* argv[]) {
	using namespace std;

	// open input file
	//Read file name, see DBG macro
	DBG(std::string filename = "./bragg_events.txt";
		, std::string filename = argv[1];)

	//Try to open the file and check the stream.
	ifstream ifs(filename);
	if (!ifs) {
		cerr << "[ERROR] File not opened";
		return -1;
	}

	// create count objects
	BraggStatistic background(3000, 5000);
	BraggStatistic africium(6000, 6499);
	BraggStatistic asium(6500, 6799);
	BraggStatistic australium(6800, 7200);

	// loop over events
	const Event* ev;
	while ((ev = read(ifs))) {
		//Evergy condition are mutually exclusive
		background.add(*ev);
		africium.add(*ev);
		asium.add(*ev);
		australium.add(*ev);

		// using a shared_ptr would have been preferable, because then we would not have needed
		// to explicitly delete ev everytime;
		delete ev;
	}

	// compute results
	background.compute();
	africium.compute();
	asium.compute();
	australium.compute();

	// print results
	cout << "1) background  2) africium  3) asium  4) australium" << endl;
	cout << "1) MeanEnergy RMS 2) MeanEnergy RMS 3) "
			"MeanEnergy RMS 4) MeanEnergy RMS" << endl;
	for (unsigned i = 0; i < Event::minSize(); ++i) {
		printf("%4f %4f ", background.eMean()[i], background.eRMS()[i]);
		printf("%4f %4f ", africium.eMean()[i], africium.eRMS()[i]);
		printf("%4f %4f ", asium.eMean()[i], asium.eRMS()[i]);
		printf("%4f %4f ", australium.eMean()[i], australium.eRMS()[i]);
		//cout << endl;
		cout << endl;
	}
	// print number of selected events
	cout << endl << endl;
	cout << "Number of events:" << endl;
	cout << "background: " << background.nEvents() << endl;
	cout << "africium: " << africium.nEvents() << endl;
	cout << "asium: " << asium.nEvents() << endl;
	cout << "australium: " << australium.nEvents() << endl;


	return 0;
}

