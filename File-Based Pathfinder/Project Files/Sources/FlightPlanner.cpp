//FlightPlanner.cpp is an overarching managing class for CityStack, CityList, and PathFinder
//author: Levon Gevorgyan

#include "../Headers/FlightPlanner.h"

FlightPlanner::~FlightPlanner() {

}
FlightPlanner::FlightPlanner() {

}
void FlightPlanner::planFlight(string flightsFile, string pathsFile,
		string outputFile) {
	ifstream flightsFileFile;
	ofstream outputFileFile;
	string line;

	CityList cities;
	cities.makeList(flightsFile);

	PathFinder paths(&cities);
	paths.findPaths(pathsFile);
	paths.printToFile(outputFile);
}
void FlightPlanner::print() {

}
