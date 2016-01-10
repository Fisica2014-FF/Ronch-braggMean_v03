#include <iostream>
#include <fstream>

#include "../Event.h"

const Event* read(std::ifstream& file) {

	Event* ev;
	int event_ID;
	// try to read input file
	if (file >> event_ID)
		ev = new Event(event_ID);
	else
		return nullptr;

	// read number of points
	unsigned numpoints;
	file >> numpoints;

	// read and store energy loss
	int energy_loss;
	for (unsigned i = 0; i < numpoints; ++i) {
		file >> energy_loss;
		ev->add(energy_loss);
	}

	return ev;

}

