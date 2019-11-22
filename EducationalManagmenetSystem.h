// EducationalManagementSystem class definition.
#ifndef EDUCATOINALMS_H
#define EDUCATIONALMS_H

#include "Database.h"
#include "FlowController.h"
#include <string>
#include <memory>

class EducationalManagementSystem {
public:
	EducationalManagementSystem(Database&); // constructor
	void run(); // start the Educational Management System

private:
	Database& database;
	std::string currentUsername;
	bool userAuthenticated; // whether user authenticated or not
	AccountType accountType;

	void displayMainMenu() const;
	void login();
	void signup();
	void runFlowController();
	std::unique_ptr<FlowController> createFlowController();

	// private utility functions
	int inputInteger(int, int); // input integer in range [low - high]; check that it is valid integer; returns it
	std::string inputString(size_t); // takes size; input a string with size less than or equal that size; returns the string
};

#endif
