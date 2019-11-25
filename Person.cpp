#include "Person.h"

using namespace std;

//constructor
Person::Person(){
	id = 0;
	name = "name";
	level = "level";
}
//destructor
Person::~Person(){
}

int Person::getID(){
	return id;
}

string Person::getName(){
	return name;
}

string Person::getLevel(){
	return level;
}
