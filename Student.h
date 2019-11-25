#ifndef STUDENT
#define STUDENT

#include "Person.h"
#include <iostream>
#include <string>

class Student : public Person
{
public:
	Student();
	Student(int idNum);
	Student(int idNum, string named, string leveled, string majoring, double gpas, int advisor);
	~Student();

	string getMajor();
	double getGPA();
	int getAdvisorID();


	void setMajor(string majoring);
	void setAdvisorID(int idNum);

	void print();

	void deserialize(istream &in);
	//Serialize:
	friend ostream & operator << (ostream &out, const Student &s1){
		out << s1.id << '\n' << s1.name << '\n' << s1.level << '\n' << s1.major << '\n' << s1.gpa << '\n' << s1.advisorID << '\n';
		return out;
	}
	// //Deserialize:
	// friend istream & operator >> (istream &in, const Student &s1){
	// 	string save;
	// 	in >> save;
	// 	s1.id = stoi(save);
	//
	// 	in >> s1.name;
	//
	// 	in >> s1.level;
	//
	// 	in >> s1.major;
	//
	// 	save = "";
	// 	in >> save;
	// 	s1.gpa = stod(save);
	//
	// 	save = "";
	// 	in >> save;
	// 	s1.advisorID = stoi(save);
	//
	// 	return in;
	// }

	//Operator Overloading:
	bool operator == (Student &s1){
		return (id == s1.id);
	}
	bool operator < (Student &s1){
		return (id < s1.id);
	}
	bool operator > (Student &s1){
		return (id > s1.id);
	}
	bool operator != (Student &s1){
		return (id != s1.id);
	}
	bool operator <= (Student &s1){
		return (id <= s1.id);
	}
	bool operator >= (Student &s1){
		return (id >= s1.id);
	}
	//Operator Overload for Integers
	bool operator == (int s1){
		return (id == s1);
	}
	bool operator < (int s1){
		return (id < s1);
	}
	bool operator > (int s1){
		return (id > s1);
	}
	bool operator != (int s1){
		return (id != s1);
	}
	bool operator <= (int s1){
		return (id <= s1);
	}
	bool operator >= (int s1){
		return (id >= s1);
	}

private:
	string major;
	double gpa;
	int advisorID;

};
#endif
