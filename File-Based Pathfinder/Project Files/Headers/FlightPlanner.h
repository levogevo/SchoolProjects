//FlightPlanner.h
//author: Levon Gevorgyan

#ifndef FLIGHTPLANNER_H_
#define FLIGHTPLANNER_H_

#include "../Headers/PathFinder.h"

class FlightPlanner {
private:
public:
	~FlightPlanner();
	FlightPlanner();
	void planFlight(string flights, string paths, string output);
	void print();
};

#endif
