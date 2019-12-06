//PathFinder.h
//author: Levon Gevorgyan

#include "../Headers/CityStack.h"
#include "../Headers/CityList.h"

#ifndef PATHFINDER_H_
#define PATHFINDER_H_

class PathFinder {
private:
	vector<CityStack*> stack;
	CityList *list;

	void findPaths(string end, CityStack *stack);
public:
	~PathFinder();
	PathFinder();
	PathFinder(CityList *list);
	void findPaths(string pathsFile);
	void printToFile(string outputFile);
};

#endif
