#ifndef UNDO
#define UNDO

#include "BSTree.h"
#include "Student.h"
#include "Faculty.h"

// *OPERATION KEY* :
// 1 - Add Student (data = idNum)
// 2 - Add Faculty (data = idNum)
// 3 - Delete Student (data = student)
// 4 - Delete Faculty (data = faculty)

class Undo{
public:
	Undo();
	Undo(int op, int idNum);
	Undo(Student stu);
	Undo(Faculty fac);
	~Undo();

	int getOp();
	int getID();
	Student getStu();
	Faculty getFac();


private:
	int operation;
	int idNum;
	Student student;
	Faculty faculty;
};

#endif
