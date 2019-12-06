//CityStack.h
//author: Levon Gevorgyan

#ifndef CITYSTACK_H_
#define CITYSTACK_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct StackNode {
	vector<string> cities; 	//all current cities in path
	int cost;				//current cost in this path
	int time;				//current time in this path

	~StackNode();
	StackNode();
	StackNode(StackNode *other);
	void addCity(string name, int cost, int time);
	bool isUntouched(string name);

	friend class PathFinder;
};

class CityStack {
	vector<StackNode*> nodes;
	bool criteria; 		//0 = time, 1 = cost

	~CityStack();
	CityStack();
	CityStack(bool criteria);
	void push(StackNode *node);
	StackNode* pop();
	StackNode* peek();

	friend class PathFinder;
};

#endif
