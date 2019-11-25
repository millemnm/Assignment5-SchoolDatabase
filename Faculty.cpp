#include "Faculty.h"

//constructor
Faculty::Faculty(){
	department = "department";
	advisees = new DList<int>();
}
//Overloaded constructor
Faculty::Faculty(int idNum, string named, string leveled, string dep){
	id = idNum;
	name = named;
	level = leveled;
	department = dep;
	advisees = new DList<int>();
}
//destructor
Faculty::~Faculty(){

}

string Faculty::getDepartment(){
	return department;
}

void Faculty::setDepartment(string dep){
	department = dep;
}

void Faculty::addAdvisee(int idNum){
	advisees->addBack(idNum);
}

int Faculty::removeAdvisee(){
	return advisees->removeHead();
}

bool Faculty::removeAdvisee(int idNum){
	return advisees->remove(idNum);
}

DList<int> *Faculty::returnAdvisees(){
	return advisees;
}

int Faculty::getAdvisee(int index){
	return advisees->getIndex(index);
}

int Faculty::numAdvisees(){
	return advisees->getSize();
}

bool Faculty::hasAdvisee(int idNum){
	for(int i = 0; i < advisees->getSize(); ++i){
		if(advisees->getIndex(i) == idNum){
			return true;
		}
	}
	return false;
}

void Faculty::print(){
	std::cout << name << '\n';
	std::cout << "   ID: " << id << '\n';
	std::cout << "   Title: " << level << '\n';
	std::cout << "   Department: " << department << '\n';
	std::cout << "   Advisory Size:  " << advisees->getSize() << '\n';
}
void Faculty::printAdviseeIDs(){
	std::cout << "Advisee ID's: " << '\n';
	advisees->print();
}
void Faculty::printAll(){
	print();
	printAdviseeIDs();
}

void Faculty::deserialize(istream &in){
	string line;
	getline(in, line); //ID number
	id = stoi(line);
	getline(in, line); //Name
	name = line;
	getline(in, line); //Job Title
	level = line;
	getline(in, line); //Department
	department = line;
}
