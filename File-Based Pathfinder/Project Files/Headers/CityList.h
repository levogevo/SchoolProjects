//CityList.h
//author: Levon Gevorgyan

#ifndef CITYLIST_H_
#define CITYLIST_H_

#include "../Headers/CityStack.h"

struct CityNode {
	string cityName;		//the name of this city
	vector<string> cities; 	//all connected cities
	vector<int> cost; 		//the cost to fly to a given city
	vector<int> time; 		//the time (minutes) to fly to a given city
	CityNode *nextCity;		//the next city

	~CityNode();
	CityNode();
	CityNode(string name);
	void addCity(string name, int cost, int time);
	void setNext(string name);

	friend class CityList;
	friend class PathFinder;
};

class CityList {
private:
	CityNode *head;
public:
	~CityList();
	CityList();
	void makeList(string flights);
	void print();

	friend class PathFinder;
};

#endif
