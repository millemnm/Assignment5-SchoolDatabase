#ifndef DRIVER
#define DRIVER

#include "Student.h"
#include "Faculty.h"
#include "BSTree.h"
#include "DList.h"
#include "GenStack.h"
#include "Undo.h"

class Driver
{
public:
	Driver();
	~Driver();

	bool isRunning();
	void start();
	void displayMenu();

	void printAllStudents(); // Print all the students and their info
	void printAllFaculty(); // Print all the faculty and their info
	void printStudent(int idNum); // find and print student from id
	void printFaculty(int idNum); // find and print faculty from id
	void printAdvisor(int idNum); // from student id print advisor info
	void printAdvisees(int idNum); // from facultys ID print all advisees info

	void addStudent(); // add a student and ask for all important info
	void addFaculty(); // add a faculty and ask for all important info

	void removeStudent(int idNum); // ask for id and delete them from the tree and advisor
	void removeFaculty(int idNum); // ask for id and delete them from the tree redipursing advisees

	void changeAdvisor(int idNum); // ask for student id and select a new advisor
	void removeAdvisee(int idNum); // remove advisee from advisor

	void changeMajor(int idNum);

	void Rollback(); // undo
	void exit(); // save everything to a file and end the program
	void save();
	void fixAdvisory();

private:
	BSTree<Student> masterStudents;
	BSTree<Faculty> masterFaculty;

	GenStack<Undo> *rollback; //the rollback stack

	int askStudentID();
	int askFacultyID();

	bool running;
	int numIDs; // Number of Id's there can possibly be (needs to be more than total)

};

#endif
