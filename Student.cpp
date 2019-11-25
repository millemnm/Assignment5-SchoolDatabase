#include "Student.h"

//constructor
Student::Student(){
	major = "majoring";
	gpa = 0;
	advisorID = 0;
}
//Overloaded constructor
Student::Student(int idNum, string named, string leveled, string majoring, double gpas, int advisor){
	id = idNum;
	name = named;
	level = leveled;
	major = majoring;
	gpa = gpas;
	advisorID = advisor;
}
//destructor
Student::~Student(){
}

string Student::getMajor(){
	return major;
}

double Student::getGPA(){
	return gpa;
}

int Student::getAdvisorID(){
	return advisorID;
}

void Student::setMajor(string majoring){
	major = majoring;
}

void Student::setAdvisorID(int idNum){
	advisorID = idNum;
}

void Student::print(){
	std::cout << name << '\n';
	std::cout << "   ID: " << id << '\n';
	std::cout << "   Year: " << level << '\n';
	std::cout << "   Major: " << major << '\n';
	std::cout << "   GPA: " << gpa << '\n';
	std::cout << "   Advisor ID: " << advisorID << '\n';
}

void Student::deserialize(istream &in){
	string line;
	getline(in, line); //ID number
	id = stoi(line);
	getline(in, line); //Name
	name = line;
	getline(in, line); //Year
	level = line;
	getline(in, line); //Major
	major = line;
	getline(in, line); //GPA
	gpa = stod(line);
	getline(in, line); //Advisor ID
	advisorID = stoi(line);
}
