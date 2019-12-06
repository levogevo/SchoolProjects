//CityStack.cpp is a stack that holds StackNode
//each StackNode is a given pathway from one city to another
//a StackNode includes the cost and time for this given path
//author: Levon Gevorgyan

#include "../Headers/CityStack.h"

//StackNode
StackNode::~StackNode() {

}
StackNode::StackNode() {
	cost = 0;
	time = 0;
}
StackNode::StackNode(StackNode *other) {
	int size = other->cities.size();
	for (int i = 0; i < size; i++) {
		cities.push_back(other->cities.at(i));
	}
	cost = other->cost;
	time = other->time;
}
void StackNode::addCity(string name, int cost, int time) {
	cities.push_back(name);
	this->cost += cost;
	this->time += time;
}
bool StackNode::isUntouched(string name) {
	int size = cities.size();
	for (int i = 0; i < size; i++) {
		if (cities.at(i) == name) {
			return 0;
		}
	}
	return 1;
}

//CityStack
CityStack::~CityStack() {

}
CityStack::CityStack() {
	criteria = 0;
}
CityStack::CityStack(bool criteria) {
	this->criteria = criteria;
}
void CityStack::push(StackNode *node) {
	nodes.push_back(node);
}
StackNode* CityStack::pop() {
	StackNode *node = nodes.back();
	nodes.pop_back();
	return node;
}
StackNode* CityStack::peek() {
	return nodes.back();
}
