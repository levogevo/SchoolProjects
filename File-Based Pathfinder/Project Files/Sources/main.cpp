//main.cpp
//author: Levon Gevorgyan

#include "../Headers/FlightPlanner.h"

int main(int argc, char *argv[]) {
	if (argc != 4) {
		cerr << "Error: wrong number of arguments, need 3";
		exit(1);
	} else {
		string flights = argv[1];	//Flight(s) data file
		string paths = argv[2];		//Path(s) data file
		string output = argv[3];	//Output file

		FlightPlanner fly;
		fly.planFlight(flights, paths, output);
	}
}
