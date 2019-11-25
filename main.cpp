#include "Driver.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {
	Driver database;
	database.start();
	while(database.isRunning()){
		database.displayMenu();
	}
	

};
