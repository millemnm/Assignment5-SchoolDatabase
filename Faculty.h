#ifndef FACULTY
#define FACULTY

#include "Person.h"
#include "DList.h"

class Faculty : public Person
{
public:
	Faculty();
	Faculty(int idNum, string named, string leveled, string dep);
	~Faculty();

	string getDepartment();
	void setDepartment(string dep);

	void addAdvisee(int idNum);
	int removeAdvisee(); //remove the first Advisee and return their ID
	bool removeAdvisee(int idNum); //remove advisee by ID
	DList<int>* returnAdvisees(); //returns the list of advisee id's
	int getAdvisee(int index);
	int numAdvisees(); //returns the number of advisees
	bool hasAdvisee(int idNum);

	void print();
	void printAll();
	void printAdviseeIDs();

	void deserialize(istream &in);

	//Serialize:
	friend ostream & operator << (ostream &out, const Faculty &f1){
		out << f1.id << '\n' << f1.name << '\n' << f1.level << '\n' << f1.department << '\n';
		return out;
	}
	// //Deserialize:
	// friend istream & operator >> (istream &in, const Faculty &f1){
	// 	in >> f1.id;
	// 	in >> f1.name;
	// 	in >> f1.level;
	// 	in >> f1.department;
	// 	return in;
	// }

	//Operator Overloading:
	bool operator == (Faculty &f1){
		return (id == f1.id);
	}
	bool operator < (Faculty &f1){
		return (id < f1.id);
	}
	bool operator > (Faculty &f1){
		return (id > f1.id);
	}
	bool operator != (Faculty &f1){
		return (id != f1.id);
	}
	bool operator <= (Faculty &f1){
		return (id <= f1.id);
	}
	bool operator >= (Faculty &f1){
		return (id >= f1.id);
	}
	//Operator Overload for Integers
	bool operator == (int f1){
		return (id == f1);
	}
	bool operator < (int f1){
		return (id < f1);
	}
	bool operator > (int f1){
		return (id > f1);
	}
	bool operator != (int f1){
		return (id != f1);
	}
	bool operator <= (int f1){
		return (id <= f1);
	}
	bool operator >= (int f1){
		return (id >= f1);
	}

private:
	string department;
	DList<int> *advisees;

};
#endif
