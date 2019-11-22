// Member-function definition for class StudentFlowController
#include "StudentFlowController.h"
#include "FlowController.h"
#include "Database.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <tuple>

using namespace std;

// enumeration constants represent student main menu options
enum class StudentMainMenuOption { ENROLL = 1, LIST, VIEW, REPORT, LOGOUT };

// enumeration constants represent Enroll in course menu options
enum class EnrollInCourseMenuOption { ENROLL = 1, BACK };

// enumeration constants represent View course menu options
enum class StudentViewCourseMenuOption { LIST = 1, UNENROLL, BACK };

// enumeration constants represent View assignment menu options
enum class ViewAssignmentMenuOption { SUBMIT = 1, BACK };

// constructor takes reference to database and takes account's username
StudentFlowController::StudentFlowController(Database& theDatabase, const std::string& accountUsername)
	: FlowController(theDatabase, accountUsername) {}

// start StudentFlowController
// overrides FlowController pure virtual function
void StudentFlowController::run() {
	bool userExited = false; // whether user has logged out
	const vector<string> studentMainMenu{ "Enroll in course", "List courses",
		"View Course", "Show grades report", "Log out" };

	while (userExited == false) {
		// loop while user has not exited
		displayMenu(studentMainMenu);
		int choice = inputInteger(1, 5);
		StudentMainMenuOption option = static_cast<StudentMainMenuOption>(choice);

		switch (option) {
			case StudentMainMenuOption::ENROLL: // enroll in course
				enrollInCourse();
				break;

			case StudentMainMenuOption::LIST: // list courses
				listCoursesCodes();
				break;

			case StudentMainMenuOption::VIEW: { // view course
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

			case StudentMainMenuOption::REPORT: // get grades report
				gradesReport();
				break;

			case StudentMainMenuOption::LOGOUT: // log out
				userExited = true;
				break;
		}
	}
}

// enroll in course
void StudentFlowController::enrollInCourse() {
	Database& database = getDatabase(); // get reference to database
	string username = getUsername();
	vector<string> coursesList = database.getComplementCoursesCodes(username);

	if (coursesList.size() == 0) {
		cout << "\nThere are no more courses to enroll in.";
		return;
	}
	else {
		for (size_t i{ 0 }; i < coursesList.size(); ++i) {
			cout << "\n" << i + 1 << " - " << coursesList[i];
		}
	}

	vector<string> menu{"Enroll in course", "Back"};
	displayMenu(menu);
	int choice = inputInteger(1, 2);
	EnrollInCourseMenuOption option = static_cast<EnrollInCourseMenuOption>(choice);

	switch (option) {
		case EnrollInCourseMenuOption::ENROLL: {
			cout << "\nWhich ith course would you like to enroll in?"
				<< "Input Integer in range [1 - " << coursesList.size() << "]: ";
			int choice = inputInteger(1, coursesList.size());
			string courseCode = coursesList[choice - 1];

			database.enrollInCourse(username, courseCode);
			cout << "\nSuccessfully enrolled in  course " << courseCode;
			break;
		}

		case EnrollInCourseMenuOption::BACK:
			break;
	}
}

// manage view course menu
// overrides FlowController pure virtual function
void StudentFlowController::viewCourse() {
	vector<string> ViewCourseMenu{ "List course's assignments", "Unenroll from course", "Back" };
	bool userExtied = false; // whether user has choose back

	while (userExtied == false) {
		// loop while user has not choose back
		displayMenu(ViewCourseMenu);
		int choice = inputInteger(1, 3);
		StudentViewCourseMenuOption option = static_cast<StudentViewCourseMenuOption>(choice);

		switch (option) {
		case StudentViewCourseMenuOption::LIST: { // list course's assignments
			int assignmentIndex{ -1 };

			try {
				assignmentIndex = inputAssignmentSelection();
			}
			catch (const exception& ex) {
				cout << ex.what();
				break;
			}

			setAssignmentIndex(assignmentIndex);
			viewAssignment();
			break;
		}

		case StudentViewCourseMenuOption::UNENROLL: { // unenroll from course
			string username = getUsername();
			string courseCode = getCourseCode();
			Database& database = getDatabase();
			database.unenrollFromCourse(username, courseCode);
			userExtied = true;
			break;
		}
		case StudentViewCourseMenuOption::BACK: // back to student main menu
			userExtied = true;
			break;
		}
	}
}

// call data base to get student grade in assignment and display assignment information
// overrides FlowController pure virtual function
void StudentFlowController::displayAssignmentInfo() const {
	Database& database = getDatabase();
	string username = getUsername();
	string courseCode = getCourseCode();
	int assignmentIndex = getAssignmentIndex();
	bool submitted = database.isStudentSubmittedSolution(username, courseCode, assignmentIndex);

	cout << "\nAssignment " << assignmentIndex;

	if (submitted) {
		cout << " - submitted - ";
		bool graded = database.isStudentSolutionGraded(username, courseCode, assignmentIndex);

		if (graded) {
			int grade = database.getStudentGradeInAssignment(username, courseCode, assignmentIndex);
			cout << grade;
		}
		else {
			cout << "NA";
		}

		int assignmentMaxGrade = database.getAssignmentMaxGrade(courseCode, assignmentIndex);
		cout << " / " << assignmentMaxGrade;
	}
	else {
		cout << " - NOT submitted";
	}
}

// manage assignment view
// overrides FlowController pure virtual function
void StudentFlowController::viewAssignment() {
	vector<string> viewAssignmentMenu{ "Submit solution to assignment", "Back" };

	displayMenu(viewAssignmentMenu);
	int choice = inputInteger(1, 2);
	ViewAssignmentMenuOption option = static_cast<ViewAssignmentMenuOption>(choice);

	switch (option) {
		case ViewAssignmentMenuOption::SUBMIT: {
			submitAssignmentSolution();
			break;
		}

		case ViewAssignmentMenuOption::BACK:
			break;
	}
}

// manage submit solution
void StudentFlowController::submitAssignmentSolution() {
	Database& database = getDatabase();
	string username = getUsername();
	string courseCode = getCourseCode();
	int assignmentIndex = getAssignmentIndex();

	cout << "Assignment Question: " << database.getAssignmentQuetion(courseCode, assignmentIndex);
	cout << "Enter the answer (max 40 characters): ";
	string answer = inputString(40);

	database.submitAssignmentSolution(username, courseCode, assignmentIndex, answer);
	cout << "\nSolution submitted successfully";
}

// calls the database to get student's grades report
void StudentFlowController::gradesReport() const {
	Database& database = getDatabase();
	string username = getUsername();
	int coursesCount = database.getCoursesCount(username);

	if (coursesCount == 0) {
		cout << "\nYou do not have any courses.";
		return;
	}

	vector<tuple<string, int, int>> report = database.getStudentGradesReport(username);

	for (size_t i{ 0 }; i < report.size(); ++i) {
		cout << "\n" << get<0>(report[i]) << " - " << get<1>(report[i]) << " / " << get<2>(report[i]);
	}
}
