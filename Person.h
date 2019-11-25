#ifndef PERSON
#define PERSON

#include <iostream>
#include <string>

using namespace std;

class Person{
public:
	Person();
	~Person();

	int getID();
	string getName();
	string getLevel();

	//Overload print operator
	friend ostream & operator << (ostream &out, Person &p1){
		out << p1.name << '\n';
		out << "   ID: " << p1.id << '\n';
		out << "   Level: " << p1.level << '\n';
		return out;
	}
	//Operator Overloading:
	bool operator == (Person &p1){
		return (id == p1.id);
	}
	bool operator < (Person &p1){
		return (id < p1.id);
	}
	bool operator > (Person &p1){
		return (id > p1.id);
	}
	bool operator != (Person &p1){
		return (id != p1.id);
	}
	bool operator <= (Person &p1){
		return (id <= p1.id);
	}
	bool operator >= (Person &p1){
		return (id >= p1.id);
	}

	//Operator Overload for Integers
	bool operator == (int p1){
		return (id == p1);
	}
	bool operator < (int p1){
		return (id < p1);
	}
	bool operator > (int p1){
		return (id > p1);
	}
	bool operator != (int p1){
		return (id != p1);
	}
	bool operator <= (int p1){
		return (id <= p1);
	}
	bool operator >= (int p1){
		return (id >= p1);
	}

protected:
	int id;
	string name;
	string level; //Current grade for student and Current job title for Faculty

};
#endif
