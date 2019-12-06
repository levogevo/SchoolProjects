//CityList.cpp is a list of CityNodes
//a CityNode includes the home city and all adjacent cities next to home
//CityNode also includes the required cost and time to reach an adjacent city
//CityNode also points to a potential next CityNode
//author: Levon Gevorgyan

#include "../Headers/CityList.h"

//CityNode
CityNode::~CityNode() {

}
CityNode::CityNode() {
	cityName = "";
	nextCity = NULL;
}
CityNode::CityNode(string name) {
	cityName = name;
	nextCity = NULL;
}
void CityNode::addCity(string name, int cost, int time) {
	cities.push_back(name);
	this->cost.push_back(cost);
	this->time.push_back(time);
}
void CityNode::setNext(string name) {
	nextCity = new CityNode(name);
}

//CityList
CityList::~CityList() {

}
CityList::CityList() {
	head = NULL;
}
void CityList::makeList(string flights) {
	ifstream flightsFile;
	string line;

	//opening flights file
	flightsFile.open(flights);
	//only read the given n number of lines
	getline(flightsFile, line);
	int lines = stoi(line);
	for (int i = lines; i > 0; i--) {
		getline(flightsFile, line);
		//have access to one line
		replace(line.begin(), line.end(), '|', ' ');
		vector<string> oneLine;
		stringstream ss(line);
		string temp;

		while (ss >> temp)
			oneLine.push_back(temp);
		//oneLine now has each line separated by the pipe ('|')

		//check if city exists, if it does add the new city to it
		//if city does not exist, add it to the end (nextCity)
		string cityName = oneLine.at(0);
		string cityTo = oneLine.at(1);
		int cost = stoi(oneLine.at(2));
		int time = stoi(oneLine.at(3));
		if (head == NULL) {
			//if CityList is empty
			head = new CityNode(cityName);
			head->addCity(cityTo, cost, time);
			head->setNext(cityTo);
			head->nextCity->addCity(cityName, cost, time);
		} else {
			//if CityList already contains cities
			CityNode *node = head;
			//trying to find city that either matches cityName
			//or is the end of CityList
			while (node->cityName != cityName && node->nextCity != NULL) {
				node = node->nextCity;
			}

			//if the node's name matches the new cityName,
			//we add a city to its list of cities
			//else we did not find the city and make a new city
			if (node->cityName == cityName) {
				node->addCity(cityTo, cost, time);
			} else {
				node->nextCity = new CityNode(cityName);
				node->nextCity->addCity(cityTo, cost, time);
			}

			node = head;
			//trying to find city that either matches cityTo
			//or is the end of CityList
			while (node->cityName != cityTo && node->nextCity != NULL) {
				node = node->nextCity;
			}

			//if the node's name matches the new cityName,
			//we add a city to its list of cities
			//else we did not find the city and make a new city
			if (node->cityName == cityTo) {
				node->addCity(cityName, cost, time);
			} else {
				node->nextCity = new CityNode(cityTo);
				node->nextCity->addCity(cityName, cost, time);
			}
		}
	}
	flightsFile.close();
	//done adding all possible paths to cityList
}
void CityList::print() {
	CityNode *node = head;
	while (node != NULL) {
		cout << "From " << node->cityName << endl;
		int numCities = node->cities.size();

		for (int i = 0; i < numCities; i++) {
			string cityTo = node->cities.at(i);
			int cost = node->cost.at(i);
			int time = node->time.at(i);
			cout << "\tto " << cityTo << ": $" << cost << ", " << time
					<< " minutes" << endl;
		}

		node = node->nextCity;
	}
}
