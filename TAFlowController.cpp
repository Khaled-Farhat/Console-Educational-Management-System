// Memeber-function definition for class TAFlowController which represents Teacher Assistant Flow Controller
#include "TAFlowController.h"
#include "Database.h"
#include <string>
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;


// enumeration constants represent main menu options
enum class TAMainMenuOption { LIST = 1, VIEW, LOGOUT};

// enumeration constants represent view course menu options
enum class TAViewCourseMenuOption { ADD = 1, LIST, VIEW, BACK };

// enumeration constants represent view assignment menu options
enum class ViewAssignmentMenuOption { LIST = 1, VIEW, BACK };

// enumeration constants represent view solution menu options
enum class ViewSolutionMenuOption { GRADE = 1, BACK };

// constructor takes reference to database and take current account's username
TAFlowController::TAFlowController(Database& theDatabase, const string& username)
	: FlowController(theDatabase, username) {}

// start TAFlowController
// overrides FlowController pure virtual function
void TAFlowController::run() {
	bool userExited = false; // whether user has logged out
	const vector<string> TAMainMenu{ "List courses", "View course", "Log out" };

	while (userExited == false) {
		// loop while user has not exited
		displayMenu(TAMainMenu);
		int choice = inputInteger(1, 3); // input integer in range [1 - 3]
		TAMainMenuOption option = static_cast<TAMainMenuOption>(choice);

		switch (option) {
			case TAMainMenuOption::LIST: // list course
				listCoursesCodes();
				break;

			case TAMainMenuOption::VIEW: { // view course
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

			case TAMainMenuOption::LOGOUT: // log out
				userExited = true;
				break;
		}
	}
}

// get solution index
int TAFlowController::getSolutionIndex() const { return solutionIndex; }

// set solution index
void TAFlowController::setSolutionIndex(int index) { solutionIndex = index; }

// manage view course menu
// overrides FlowController pure virtual function
void TAFlowController::viewCourse() {
	bool userExited = false; // whether use has choosed back
	const vector<string> viewCourseMenu{ "Add assignment", "List assignments","View assignment", "back" };

	while (userExited == false) {
		displayMenu(viewCourseMenu);
		int choice = inputInteger(1, 4); // input integer in range [1 - 4]
		TAViewCourseMenuOption option = static_cast<TAViewCourseMenuOption>(choice);

		switch (option) {
			case TAViewCourseMenuOption::ADD: // add assignment
				addAssignment();
				break;

			case TAViewCourseMenuOption::LIST: // list assignments
				listCourseAssignments();
				break;

			case TAViewCourseMenuOption::VIEW: { // view assignment
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

			case TAViewCourseMenuOption::BACK: // back to TA main menu
				userExited = true;
				break;
		}
	}
}

// manage add assignment menu
void TAFlowController::addAssignment() {
	string courseCode = getCourseCode();
	Database& database = getDatabase(); // reference to database
	string assignmentQuestion;

	cout << "\nEnter assignment question (max 30 character): ";
	cin >> assignmentQuestion;

	database.addAssignmentToCourse(courseCode, assignmentQuestion);
	cout << "\nAssignment created successfully.";
}

// manage view assignment menu
void TAFlowController::viewAssignment() {
	bool userExited = false;
	vector<string> viewAssignmentMenu{ "List solutions", "View solution", "Back" };

	while (userExited == false) {
		displayMenu(viewAssignmentMenu);
		int choice = inputInteger(1, 3); // input integer in range [1 - 3]
		ViewAssignmentMenuOption option = static_cast<ViewAssignmentMenuOption>(choice);
		
		switch (option) {
		case ViewAssignmentMenuOption::LIST: // list solutions
			listAssignmentSolutions();
			break;

		case ViewAssignmentMenuOption::VIEW: { // view solution
			int choosedSolutionIndex{ -1 };

			try {
				choosedSolutionIndex = inputSolutionSelection();
			}
			catch (const exception& ex) {
				break;
			}

			setSolutionIndex(choosedSolutionIndex);
			viewSolution();
			break;
		}

		case ViewAssignmentMenuOption::BACK: // back to view course menu
			userExited = true;
			break;
		}
	}
}

// list assignment's solutions;
// return false if there are no solutions; true otherwise
bool TAFlowController::listAssignmentSolutions() const {
	Database& database = getDatabase(); // reference to database
	string courseCode = getCourseCode();
	int assignmentIndex = getAssignmentIndex();
	int assignmentMaxGrade = database.getAssignmentMaxGrade(courseCode, assignmentIndex);

	// get solutions info as vector of tuples of form (is graded, grade, student username)
	vector<tuple<bool, int, const string>> solutionsInfo = database.getAssignmentSolutionsInfo(courseCode, assignmentIndex);

	if (solutionsInfo.size() == 0) {
		cout << "\nAssignment has no submitted solutions yet.";
		return false;
	}
	else {
		for (size_t i{ 0 }; i < solutionsInfo.size(); ++i) {
			cout << "\n" << i + 1 << " - " << get<2>(solutionsInfo[i]) << " - "; // student username
			
			bool isGraded = get<0>(solutionsInfo[i]);

			if (isGraded == true) {
				cout << get<1>(solutionsInfo[i]); // output grade
			}
			else { // not graded
				cout << "NA";
			}

			cout << " / " << assignmentMaxGrade;
		}

		return true;
	}
}

// calls listAssignmentSolution; input solution selection and return it
// throw exception if assignment does not have any submitted solution
int TAFlowController::inputSolutionSelection() {
	if (listAssignmentSolutions() == true) {
		Database& database = getDatabase(); // reference to database
		string courseCode = getCourseCode();
		int assignmetnIndex = getAssignmentIndex();
		int solutionsCount = database.getAssignmentSolutionsCount(courseCode, assignmetnIndex);
		cout << "\nEnter integer in range [1 - " << solutionsCount << "]: ";
		int selection = inputInteger(1, solutionsCount);
		return selection;
	}
	else {
		throw exception("\nAssignment has no submitted solutions yet.");
	}
}

// manage view solution menu
void TAFlowController::viewSolution() {
	Database& database = getDatabase();
	string courseCode = getCourseCode();
	int assignmentIndex = getAssignmentIndex();
	string solutionAnswer = database.getSolutionAnswer(courseCode, assignmentIndex, solutionIndex);

	cout << "\nStudent solution: " << solutionAnswer;

	const vector<string> viewSolutionMenu{ "Grade solution", "Back" };

	displayMenu(viewSolutionMenu);
	int choice = inputInteger(1, 2); // input integer in range [1 - 2]
	ViewSolutionMenuOption option = static_cast<ViewSolutionMenuOption>(choice);

	switch (option) {
		case ViewSolutionMenuOption::GRADE:
			gradeSolution();
			break;

		case ViewSolutionMenuOption::BACK:
			break;
	}
}

// allows Teacher Assistant to grade solutions
void TAFlowController::gradeSolution() {
	Database& database = getDatabase(); // reference to database
	const string courseCode = getCourseCode();
	int assignmentIndex = getAssignmentIndex();
	int assignmentMaxGrade = database.getAssignmentMaxGrade(courseCode, assignmentIndex);

	cout << "\nEnter grade in range [0 - " << assignmentMaxGrade << "]: ";
	
	int grade = inputInteger(1, assignmentMaxGrade);
	database.gradeSolution(courseCode, assignmentIndex, solutionIndex, grade);

	cout << "\nSolution graded successfully to " << grade << '.';
}

void TAFlowController::displayAssignmentInfo() const {
	int assignmentIndex = getAssignmentIndex();
	cout << "\nAssignment - " << assignmentIndex;
}
