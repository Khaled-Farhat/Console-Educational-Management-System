// Member-function definition for abstract class FlowController
#include "FlowController.h"
#include "Database.h"
#include "Assignment.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <exception>

using namespace std;

// constructor takes reference to data base and takes account's username
FlowController::FlowController(Database& theDatabase, const std::string& accountUsername)
	: database(theDatabase), username(accountUsername) {}

// return username
const string& FlowController::getUsername() const { return username; }

// return current course code
const string& FlowController::getCourseCode() const { return courseCode; }

// return reference to database
Database& FlowController::getDatabase() const { return database; }

// return assignment index
int FlowController::getAssignmentIndex() const { return assignmentIndex; }

// set course code
void FlowController::setCourseCode(const string& code) { courseCode = code; }

// set assignment index
void FlowController::setAssignmentIndex(int index) { assignmentIndex = index; }

// utility function to input integer
int FlowController::inputInteger(int low, int high) {
	int integer = 0;

	while (1) {
		string input;
		getline(cin, input);

		if (input.size() == 0) {
			continue;
		}

		bool validInput = true;

		for (size_t i{ 0 }; i < input.size(); ++i) {
			if (!isdigit(input[i])) {
				validInput = 0;
				break;
			}
		}

		if (input.size() > 9) {
			validInput = 0;
		}

		if (validInput) {
			integer = stoi(input);

			if (integer < low || integer > high) {
				validInput = false;
			}
		}

		if (validInput) {
			break;
		}
		else {
			cout << "Invalid input. Enter integer in range [" << low << " - " << high << "]: ";
		}
	}

	return integer;
}

// takes size; input a string with size less than or equal that size; returns the string
string FlowController::inputString(size_t stringSize) {
	string inputString;

	while (1) {
		string input;
		getline(cin, input);

		if (input.size() == 0) {
			continue;
		}

		bool validInput = true;

		for (size_t i{ 0 }; i < input.size(); ++i) {
			if (input[i] == ' ') {
				validInput = 0;
			}
		}

		if (input.size() > stringSize) {
			validInput = 0;
		}

		if (validInput) {
			inputString = input;
			break;
		}
		else {
			cout << "Invalid input. Enter a string with no spaces and size less than "
				<< stringSize << ": ";
		}
	}

	return inputString;
}

// utility function to display a menu
void FlowController::displayMenu(const vector<string>& menu) const {
	cout << "\n";
	for (size_t i{ 0 }; i < menu.size(); ++i) {
		cout << "\n" << i + 1 << " - " << menu[i];
	}

	cout << "\nMake a choice: ";
}

// call the database to get course's assignments list
// return false if there are no assignments; true otherwise
bool FlowController::listCourseAssignments() {
	int assignmentsCount = database.getAssignmentsCount(courseCode);

	if (assignmentsCount == 0) {
		cout << "\nCourse " << courseCode << " has no assignments";
		return false;
	}
	else {
		for (int i{ 0 }; i < assignmentsCount; ++i) {
			setAssignmentIndex(i + 1);
			displayAssignmentInfo();
		}

		return true;
	}
}

// call the database to get current account's courses codes
// return false if there are no courses; true otherwise
bool FlowController::listCoursesCodes() const {
	const vector<string> coursesCodes = database.getCoursesCodes(username);

	if (coursesCodes.size() == 0) {
		cout << "\nYou don't have any courses.";
		return false;
	}
	else {
		for (size_t i{ 0 }; i < coursesCodes.size(); ++i) {
			cout << "\n" << i + 1 << " - " << coursesCodes[i];
		}

		return true;
	}
}

// list course's assignments; input assignment number
// throw exception if course does not have any assignment
int FlowController::inputAssignmentSelection() {
	if (listCourseAssignments() == true) {
		int assignmentsCount = database.getAssignmentsCount(courseCode);
		cout << "\nEnter integer in range [1 - " << assignmentsCount << "]: ";
		int selection = inputInteger(1, assignmentsCount); // input integer in range [1 - assignmentsCount]
		return selection;
	}
	else {
		throw std::runtime_error("\nThis course does not have any assignments.");
	}
}

// list account's courses codes; input course number
// throw exception if user does not have any courses
std::string FlowController::inputCourseSelection() {
	if (listCoursesCodes() == true) {
		int coursesCount = database.getCoursesCount(username);
		cout << "\nEnter integer in range [1 - " << coursesCount << "]: ";
		int selection = inputInteger(1, coursesCount); // input integer in range [1 - coursesCount]
		vector<string> coursesList = database.getCoursesCodes(username);
		string courseCodeSelection = coursesList[selection - 1];
		return courseCodeSelection;
	}
	else {
		throw std::runtime_error("\nYou don't have any courses.");
	}
}
