#include "Driver.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <stdio.h>
#include <string>

using namespace std;

//constructor
Driver::Driver(){
	running = true;
	numIDs = 500000; // the amount of alocated numbers for each type of person
	rollback = new GenStack<Undo>(5); //Change the number to change length of history
}
//destructor
Driver::~Driver(){
	save();
}

bool Driver::isRunning(){
	return running;
}
void Driver::start(){
	ifstream fact("facultyTable.txt");
	if(fact.is_open()){
		masterFaculty.Deserialize(fact);
		ifstream stut("studentTable.txt");
		if(stut.is_open()){
			masterStudents.Deserialize(stut);
		}
		stut.close();
	}
	fact.close();
	fixAdvisory();
}

void Driver::exit(){
	running = false;
}

void Driver::save(){
	ofstream fact;
	fact.open("facultyTable.txt");
	masterFaculty.Serialize(fact);
	fact.close();
	ofstream stut;
	stut.open("studentTable.txt");
	masterStudents.Serialize(stut);
	stut.close();

	std::cout << "File Saved." << '\n';
}

void Driver::displayMenu(){
	std::cout << "School Database:" << '\n';
	std::cout << "1)   Print All Students" << '\n';
	std::cout << "2)   Print All Faculty" << '\n';
	std::cout << "3)   Find Student" << '\n';
	std::cout << "4)   Find Faculty" << '\n';
	std::cout << "5)   Find Students Advisor" << '\n';
	std::cout << "6)   Find Faculty's Advisees" << '\n';
	std::cout << "7)   Add Student" << '\n';
	std::cout << "8)   Remove Student" << '\n';
	std::cout << "9)   Add Faculty" << '\n';
	std::cout << "10)  Remove Faculty" << '\n';
	std::cout << "11)  Change Advisor" << '\n';
	std::cout << "12)  Remove Advisee" << '\n';
	std::cout << "13)  Change Major" << '\n';
	std::cout << "14)  Rollback (Undo)" << '\n';
	std::cout << "15)  Save Database" << '\n';
	std::cout << "16)  Exit" << '\n';

	std::cout << "What would you like to do? " << flush;
	int choice;
	std::cin >> choice;

	if(choice == 1){
		printAllStudents();
	}else if(choice == 2){
		printAllFaculty();
	}else if(choice == 3){
		printStudent(askStudentID());
	}else if(choice == 4){
		printStudent(askFacultyID());
	}else if(choice == 5){
		printAdvisor(askStudentID());
	}else if(choice == 6){
		printAdvisees(askFacultyID());
	}else if(choice == 7){ //
		addStudent();
	}else if(choice == 8){
		removeStudent(askStudentID());
	}else if(choice == 9){
		addFaculty();
	}else if(choice == 10){
		removeFaculty(askFacultyID());
	}else if(choice == 11){
		changeAdvisor(askStudentID());
	}else if(choice == 12){
		removeAdvisee(askFacultyID());
	}else if(choice == 13){
		changeMajor(askStudentID());
	}else if(choice == 14){
		Rollback();
	}else if(choice == 15){
		save();
	}else if(choice == 16){
		exit();
	}else{
		std::cout << "NOT A VALID OPTION!" << '\n';
		std::cout << "Please pick from this list (1-14):" << '\n';
		displayMenu();
	}

}

int Driver::askStudentID(){
	std::cin.ignore();

	if(masterStudents.isEmpty()){
		std::cout << "ERROR: There are no students, Create one first." << '\n';
		return -1;
	}else{
		std::cout << "Enter Student ID Number: " << '\n';
		int idNum;
		std::cin >> idNum;

		if(idNum == -1){
			return -1;
		}else if(idNum == -2){
			masterStudents.PrintTree();
			return askStudentID();;
		}else if(masterStudents.find(idNum)){
			return idNum;
		}else{
			std::cout << "ERROR: Not a Valid Student ID!" << '\n';
			std::cout << "  - Enter -1 to go to the Menu." << '\n';
			std::cout << "  - Enter -2 to Print a list of all the current students." << '\n';
			return askStudentID();
		}
	}
}
int Driver::askFacultyID(){
	std::cin.ignore();

	if(masterFaculty.isEmpty()){
		std::cout << "ERROR: There are no Faculty, Create one first." << '\n';
		return -1;
	}else{
		std::cout << "Enter Faculty ID Number: " << '\n';
		int idNum;
		std::cin >> idNum;

		if(idNum == -1){
			return -1;
		}else if(idNum == -2){
			masterFaculty.PrintTree();
			return askFacultyID();
		}else if(masterFaculty.find(idNum)){
			return idNum;
		}else{
			std::cout << "ERROR: Not a Valid Faculty ID!" << '\n';
			std::cout << "  - Enter -1 to go back to the Menu." << '\n';
			std::cout << "  - Enter -2 to Print a list of all the current faculty." << '\n';
			return askFacultyID();
		}
	}
}

void Driver::printAllStudents(){
	masterStudents.PrintTree();
}
void Driver::printAllFaculty(){
	masterFaculty.PrintTree();
}

void Driver::printStudent(int idNum){
	if(idNum != -1){
		masterStudents.search(idNum).print();
	}
}
void Driver::printFaculty(int idNum){
	if(idNum != -1){
		Faculty curr = masterFaculty.search(idNum);
		curr.print();
		std::cout << "Advisees: ";
		int advSize = curr.numAdvisees();
		for(int i = 0; i < advSize; ++i){
			Student stu = masterStudents.search(curr.getAdvisee(i));
			std::cout << stu.getName() << " (" << stu.getID() << "), ";
		}
	}
}

void Driver::printAdvisor(int idNum){
	if(idNum != -1){
		printFaculty(masterStudents.search(idNum).getAdvisorID());
	}
}
void Driver::printAdvisees(int idNum){
	if(idNum != -1){
		Faculty curr = masterFaculty.search(idNum);
		int advSize = curr.numAdvisees();
		for(int i = 0; i < advSize; ++i){
			printStudent(curr.getAdvisee(i));
		}
	}
}

void Driver::addStudent(){
	if(!masterFaculty.isEmpty()){
		// Get Random Number from (numIds -> (numIds+numIds-1)) for ID
		int randID = rand() % numIDs + numIDs;
		while(masterStudents.find(randID)){
			randID = rand() % numIDs + numIDs;
		}

		// Get Name
		std::cout << "What is the new students name? " << flush;
		cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
		string named;
		getline(cin, named);

		// Get Year
		std::cout << "What is " << named << "'s Year? " << flush;
		string year;
		getline(cin, year);

		// Get Major
		std::cout << "What is " << named << "'s Major? " << flush;
		string major;
		getline(cin, major);

		// Get GPA
		std::cout << "What is " << named << "'s GPA? " << flush;
		string gpas;
		getline(cin, gpas);
		double gpa = stod(gpas);

		// Get Advisor
		std::cout << "Who is " << named << "'s Advisor? " << flush;
		int adv = askFacultyID();

		masterFaculty.search(adv).addAdvisee(randID);
		Student newStu = Student(randID, named, year, major, gpa, adv);
		masterStudents.insert(newStu);
		std::cout << "Succesfully Created New Student!" << '\n';
		newStu.print();

		rollback->push(Undo(1, randID));
	}else{
		std::cout << "ERROR: Please add at least one faculty member before you add a student." << '\n';
	}

}
void Driver::addFaculty(){
	// Get Random Number from (0 -> numIds-1)) for ID
	int randID = rand() % numIDs;
	while(masterFaculty.find(randID)){
		randID = rand() % numIDs;
	}

	// Get Name
	std::cout << "What is the new Faculty Member's Name? " << flush;
	cin.clear();
	std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string named;
	getline(cin, named);

	// Get Job Title
	std::cout << "What is " << named << "'s Job Title? " << flush;
	string title;
	getline(cin, title);

	// Get Department
	std::cout << "What is " << named << "'s Department? " << flush;
	string department;
	getline(cin, department);

	Faculty newFac = Faculty(randID, named, title, department);
	masterFaculty.insert(newFac);
	std::cout << "Succesfully Created New Faculty!" << '\n';
	newFac.print();

	rollback->push(Undo(2, randID));
}

void Driver::removeStudent(int idNum){
	if(idNum != -1){
		Student deleted = masterStudents.remove(idNum);
		Faculty advisor = masterFaculty.search(deleted.getAdvisorID());

		advisor.removeAdvisee(idNum);

		std::cout << "Succesfully Removed: " << '\n';
		std::cout << deleted << '\n';
		rollback->push(Undo(deleted));
	}
}
void Driver::removeFaculty(int idNum){
	if(idNum != -1){
		Faculty deleted = masterFaculty.remove(idNum);
		int advSize = deleted.numAdvisees();
		for(int i = 0; i < advSize; ++i){
			changeAdvisor(deleted.getAdvisee(i));
		}
		std::cout << "Succesfully Removed: " << '\n';
		std::cout << deleted << '\n';
		rollback->push(Undo(deleted));
	}
}

void Driver::changeAdvisor(int idNum){
	if(idNum != -1){
		Student curr = masterStudents.search(idNum);
		masterFaculty.search(curr.getAdvisorID()).removeAdvisee(idNum);

		std::cout << "Pick a new Advisor. " << flush;
		int adv = askFacultyID();

		curr.setAdvisorID(adv);
		masterFaculty.search(adv).addAdvisee(idNum);
	}
}

void Driver::removeAdvisee(int idNum){
	if(idNum != -1){
		Faculty curr = masterFaculty.search(idNum);
		std::cout << "Choose an advisee to remove: " << '\n';
		printAdvisees(idNum);
		int adviseeID;
		std::cin >> adviseeID;

		while(!curr.removeAdvisee(adviseeID)){
			std::cout << "ERROR: Not an Advisee of the Faculty member! Enter a valid ID from above." << flush;
			std::cin >> adviseeID;
		}

		changeAdvisor(adviseeID);
	}
}

void Driver::Rollback(){
	if(rollback->isEmpty()){
		std::cout << "Rollback: EMPTY" << '\n';

	}else{
		Undo doing = rollback->pop();
		if(doing.getOp() == 1){ //Added Student (remove)
			Student deleted = masterStudents.remove(doing.getID());
			Faculty advisor = masterFaculty.search(deleted.getAdvisorID());
			advisor.removeAdvisee(doing.getID());
			std::cout << "RollBack: Add Student" << '\n';

		}else if(doing.getOp() == 2){ //Added Faculty (remove)
			masterFaculty.remove(doing.getID());
			std::cout << "RollBack: Add Faculty" << '\n';

		}else if(doing.getOp() == 3){ //Deleted Student (put back)
			Student curr = doing.getStu();
			int idNum = doing.getID();
			string name = curr.getName();
			string level = curr.getLevel();
			string major = curr.getMajor();
			double gpa = curr.getGPA();
			int advID = curr.getAdvisorID();

			masterFaculty.search(advID).addAdvisee(idNum);

			Student newStu = Student(idNum, name, level, major, gpa, advID);
			masterStudents.insert(newStu);
			std::cout << "Rollback: Delete Student" << '\n';

		}else if(doing.getOp() == 4){ //Deleted Faculty (put back)
			Faculty curr = doing.getFac();
			int idNum = doing.getID();
			string name = curr.getName();
			string level = curr.getLevel();
			string dep = curr.getDepartment();

			Faculty newFac = Faculty(idNum, name, level, dep);

			int advSize = curr.numAdvisees();
			for(int i = 0; i < advSize; ++i){
				Student advisee = masterStudents.search(curr.getAdvisee(i));
				int advID = advisee.getID();
				masterFaculty.search(advisee.getAdvisorID()).removeAdvisee(advID); //find old advisor and remove them from the advisory
				advisee.setAdvisorID(idNum);
				newFac.addAdvisee(advID);
			}

			masterFaculty.insert(newFac);
			std::cout << "Rollback: Delete Faculty" << '\n';
		}
	}
}

void Driver::changeMajor(int idNum){
	std::cout << "What is your new Major? " << flush;
	string major;
	getline(cin, major);

	masterStudents.search(idNum).setMajor(major);
	std::cout << "Succesfully Switched Majors!" << '\n';
}

void Driver::fixAdvisory(){
	BSTree<Student> studentSave = masterStudents;
	while(!studentSave.isEmpty()){
		int key = studentSave.findRoot();
		Student saved = studentSave.remove(key);
		masterFaculty.search(saved.getAdvisorID()).addAdvisee(key);
	}
}
