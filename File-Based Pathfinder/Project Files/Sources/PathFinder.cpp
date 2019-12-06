//PathFinder.cpp takes a CityList and finds all possible files dictated by pathsFile
//these paths are added to CityStack
//author: Levon Gevorgyan

#include "../Headers/PathFinder.h"

PathFinder::~PathFinder() {

}
PathFinder::PathFinder() {
	list = NULL;
}
PathFinder::PathFinder(CityList *list) {
	this->list = list;
}
void PathFinder::findPaths(string paths) {
	ifstream pathsFile;
	string line;

	//opening flights file
	pathsFile.open(paths);
	//only read the given n number of lines
	getline(pathsFile, line);
	int lines = stoi(line);
	for (int i = lines; i > 0; i--) {
		getline(pathsFile, line);
		//have access to one line
		replace(line.begin(), line.end(), '|', ' ');
		vector<string> oneLine;
		stringstream ss(line);
		string temp;

		while (ss >> temp)
			oneLine.push_back(temp);
		//oneLine now has each line separated by the pipe ('|')

		//make a new stack per path necessary to find
		//make the stack have one starting node that contains the first city
		string start = oneLine.at(0);
		string end = oneLine.at(1);
		bool criteria = (oneLine.at(2) == "T") ? 0 : 1;
		CityStack *newStack = new CityStack(criteria);
		StackNode *startCity = new StackNode;
		startCity->addCity(start, 0, 0);
		newStack->push(startCity);
		stack.push_back(newStack);

		findPaths(end, newStack);
	}

	/*
	 * node, destination, stack*
	 * pop node off of stack
	 * if node = destination
	 * 		push back
	 * else for each place adjacent to node
	 *
	 *  if place is not in node already
	 *		 push node + place onto stack
	 * else do nothing since node does not lead to destination
	 *
	 */
}
void PathFinder::findPaths(string destination, CityStack *stack) {
	StackNode *stackNode;
	//only pop if stack has something to pop
	if (stack->nodes.size() > 0)
		stackNode = stack->pop();
	else
		return;
	if (stackNode->cities.back() == destination) {
		//this node has successfully found destination
		//check if stack needs any other processing
		if (stack->nodes.size() > 0) {
			findPaths(destination, stack);
		}
		//push completed node back onto stack
		stack->push(stackNode);
	} else {
		CityNode *listNode = list->head;
		//trying to find the listNode that matches the current stackNode city
		//so we can iterate through the listNode's adjacent cities
		while (listNode->cityName != stackNode->cities.back()
				&& listNode->nextCity != NULL) {
			listNode = listNode->nextCity;
		}
		//we found the listNode that matches the stackNode city
		if (listNode->cityName == stackNode->cities.back()) {
			//iterate through all adjacent cities that are not in stack already
			int size = listNode->cities.size();
			for (int i = 0; i < size; i++) {
				//if the adjacent city has not been visited already by stackNode
				string newCity = listNode->cities.at(i);
				if (stackNode->isUntouched(newCity)) {
					//make new stackNode and add the untouched city to it
					StackNode *newNode = new StackNode(stackNode);
					int cost = listNode->cost.at(i);
					int time = listNode->time.at(i);
					newNode->addCity(newCity, cost, time);
					//add this stackNode to stack
					stack->push(newNode);

					//continue processing stack
					findPaths(destination, stack);
				}
			}
		}
		//did not find the city and it is not there
		else
			return;
	}

}
void PathFinder::printToFile(string outputFile) {
	ofstream output;
	output.open(outputFile);

	int numStacks = stack.size();
	for (int i = 0; i < numStacks; i++) {
		int stackSize = stack.at(i)->nodes.size();
		//get the first node in a given stack
		StackNode *firstNode = stack.at(i)->nodes.at(0);
		//get the start and end city, and criteria
		string start = firstNode->cities.at(0);
		string end = firstNode->cities.at(firstNode->cities.size() - 1);
		string criteria = (stack.at(i)->criteria) ? "Cost" : "Time";

		output << "Flight " << i + 1 << ": " << start << ", " << end << " ("
				<< criteria << ")" << endl;

		//if there are more than 3 paths, only print 3
		if (stackSize > 3) {
			stackSize = 3;
		}

		//sort by time
		if (criteria == "Time") {
			for (int j = 0; j < stackSize; j++) {
				int minInd = 0;
				int minTime = stack.at(i)->nodes.at(minInd)->time;

				for (long long unsigned int k = 0;
						k < stack.at(i)->nodes.size(); k++) {
					if (stack.at(i)->nodes.at(k)->time < minTime) {
						minInd = k;
						minTime = stack.at(i)->nodes.at(minInd)->time;
					}
				}
				StackNode *minNode = stack.at(i)->nodes.at(minInd);
				stack.at(i)->nodes.erase(stack.at(i)->nodes.begin() + minInd);

				int numNodes = minNode->cities.size();
				output << "Path " << j + 1 << ": " << minNode->cities.at(0);
				for (int k = 1; k < numNodes; k++) {
					output << " -> " << minNode->cities.at(k);
				}
				output << ". Time: " << minNode->time;
				output << " Cost: " << minNode->cost << ".00";
				output << endl;
			}
			output << endl;
		}
		//sort by cost
		else {
			for (int j = 0; j < stackSize; j++) {
				int minInd = 0;
				int minCost = stack.at(i)->nodes.at(minInd)->cost;

				for (long long unsigned int k = 0;
						k < stack.at(i)->nodes.size(); k++) {
					if (stack.at(i)->nodes.at(k)->cost < minCost) {
						minInd = k;
						minCost = stack.at(i)->nodes.at(minInd)->cost;
					}
				}
				StackNode *minNode = stack.at(i)->nodes.at(minInd);
				stack.at(i)->nodes.erase(stack.at(i)->nodes.begin() + minInd);

				int numNodes = minNode->cities.size();
				output << "Path " << j + 1 << ": " << minNode->cities.at(0);
				for (int k = 1; k < numNodes; k++) {
					output << " -> " << minNode->cities.at(k);
				}
				output << ". Time: " << minNode->time;
				output << " Cost: " << minNode->cost << ".00";
				output << endl;
			}
			output << endl;
		}
	}
	output.close();
}

