// Member-function definition for class ProfessorFlowController.
#include "ProfessorFlowController.h"
#include "TAFlowController.h"
#include "Database.h"
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

// enumeration constants represent professor main menu options
enum class ProfessorMainMenuOption { CREATE = 1, LIST, VIEW, LOGOUT };

// enumeration constants represent View course menu options
enum class ProfessorViewCourseMenuOption { ADDTA = 1, ADDASSIGNMENT, LIST, VIEW, BACK };

// constructor takes reference to database; and takes professor username
ProfessorFlowController::ProfessorFlowController(Database& theDatabase, const string& username)
	: TAFlowController(theDatabase, username) {}

// start ProfessorFlowController
// overrides virtual function
void ProfessorFlowController::run() {
	bool userExited = false; // whether user has logged out
	const vector<string> TAMainMenu{ "Create course", "List courses", "View course", "Log out" };

	while (userExited == false) {
		// loop while user has not exited
		displayMenu(TAMainMenu);
		int choice = inputInteger(1, 3); // input integer in range [1 - 3]
		ProfessorMainMenuOption option = static_cast<ProfessorMainMenuOption>(choice);

		switch (option) {
			case ProfessorMainMenuOption::CREATE: // create course
				createCourse();
				break;

			case ProfessorMainMenuOption::LIST: // list course
				listCoursesCodes();
				break;

			case ProfessorMainMenuOption::VIEW: { // view course
				string courseCode;

				try {
					courseCode = inputCourseSelection();
				}
				catch (const exception& ex) {
					break;
				}

				setCourseCode(courseCode);
				viewCourse();
				break;
			}

			case ProfessorMainMenuOption::LOGOUT: // log out
				userExited = true;
				break;
			}
	}
}

// manage view course menu
// overrides virtual function
void ProfessorFlowController::viewCourse() {
	bool userExited = false; // whether use has choose back
	const vector<string> viewCourseMenu{ "Add teacher assistant to this course", "Add assignment", "List assignments","View assignment", "back" };

	while (userExited == false) {
		displayMenu(viewCourseMenu);
		int choice = inputInteger(1, 4); // input integer in range [1 - 5]
		ProfessorViewCourseMenuOption option = static_cast<ProfessorViewCourseMenuOption>(choice);

		switch (option) {
			case ProfessorViewCourseMenuOption::ADDTA: // add Teacher Assistant
				addTAToCourse();
				break;

			case ProfessorViewCourseMenuOption::ADDASSIGNMENT: // add assignment
				addAssignment();
				break;

			case ProfessorViewCourseMenuOption::LIST: // list assignments
				listCourseAssignments();
				break;

			case ProfessorViewCourseMenuOption::VIEW: { // view assignment
				int assignmentIndex{ -1 };

				try {
					assignmentIndex = inputAssignmentSelection();
				}
				catch (const exception& ex) {
					break;
				}

				setAssignmentIndex(assignmentIndex);
				viewAssignment();
				break;
			}

			case ProfessorViewCourseMenuOption::BACK: // back to TA main menu
				userExited = true;
				break;
			}
	}
}

// create course
void ProfessorFlowController::createCourse() {
	Database& database = getDatabase(); // reference to database
	string username = getUsername();
	string courseCode;

	cout << "\nEnter a unique course code (max 8 characters): ";
	courseCode = inputString(8);

	bool status = database.createCourse(courseCode, username);

	if (status == true) {
		cout << "\nCourse " << courseCode << " created successfully.";
	}
	else {
		cout << "\nCourse " << courseCode << " is already exist.";
	}
}

// add Teacher Assistant to course; this allows him to add assignments and grade students solutions
void ProfessorFlowController::addTAToCourse() {
	Database& database = getDatabase(); // reference to database
	string courseCode = getCourseCode();
	string TAUsername;

	cout << "\nEnter Teacher Assistant username: ";
	TAUsername = inputString(8);

	bool status = database.addTAToCourse(courseCode, TAUsername);

	if (status == true) {
		cout << "\nTeacher Assistant " << TAUsername << " successfully added to course " << courseCode << '.';
	}
	else {
		cout << "\nuser " << TAUsername << " is not a Teacher Assistant.";
	}
}
