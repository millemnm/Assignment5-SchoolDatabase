#include "Undo.h"


//default constructor
Undo::Undo(){
	operation = 0;
	idNum = 0;
}
//Overloaded constructor for either add
Undo::Undo(int op, int id){
	operation = op; // Should only be 1 or 2
	idNum = id;
}
//Overloaded constructor for deleting a student
Undo::Undo(Student stu){
	operation = 3;
	idNum = stu.getID();
	student = stu;
}
//Overloaded constructor for deleting a student
Undo::Undo(Faculty fac){
	operation = 4;
	idNum = fac.getID();
	faculty = fac;
}
//destructor
Undo::~Undo(){
}

int Undo::getOp(){
	return operation;
}

int Undo::getID(){
	return idNum;
}

Student Undo::getStu(){
	return student;
}

Faculty Undo::getFac(){
	return faculty;
}
