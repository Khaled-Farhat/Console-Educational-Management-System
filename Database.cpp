// Memeber-function definitions for class Database
#include "Database.h"
#include "CoursesDatabase.h"
#include "ProfessorsDatabase.h"
#include "TAsDatabase.h"
#include "StudentsDatabase.h"
#include "Account.h"
#include "Professor.h"
#include "TeacherAssistant.h"
#include "Student.h"
#include <string>
#include <algorithm>

using namespace std;

// authenticate user
// return 0 if not authenticated
// return 1 if authenticated
bool Database::authenticateUser(const std::string& username, const std::string& password) {
	if (studentsDatabase.autheticateStudent(username, password) == true) {
		return true;
	}
	else if (taDatabase.authenticateTA(username, password) == true) {
		return true;
	}
	else if (professorsDatabase.authenticateProfessor(username, password) == true) {
		return true;
	}
	else {
		return false;
	}
}

// return account type
AccountType Database::getAccountType(const string& username) {
	if (studentsDatabase.isStudent(username) == true) {
		return AccountType::STUDENT;
	}
	else if (taDatabase.isTA(username) == true) {
		return AccountType::TA;
	}
	else if (professorsDatabase.isProfessor(username) == true) {
		return AccountType::Professor;
	}
}

// create a new student account
void Database::createStudentAccount(const string& username, const string& password) {
	studentsDatabase.createStudentAccount(username, password);
	Student* studentPtr = studentsDatabase.getStudent(username);
	accounts.push_back(studentPtr);
}

// create a new Teacher Assistant account
void Database::createTAAccount(const string& username, const string& password) {
	taDatabase.createTAAccount(username, password);
	TeacherAssistant* teacherAssistantPtr = taDatabase.getTA(username);
	accounts.push_back(teacherAssistantPtr);
}

// create a new professor account
void Database::createProfessorAccount(const string& username, const string& password) {
	professorsDatabase.createProfessorAccount(username, password);
	Professor* professorPtr = professorsDatabase.getProfessor(username);
	accounts.push_back(professorPtr);
}

// takes username; return true if there is no user with that username; false otherwise
bool Database::isValidUsername(const string& username) {
	if (studentsDatabase.isStudent(username) == true) {
		return false;
	}
	else if (taDatabase.isTA(username) == true) {
		return false;
	}
	else if (professorsDatabase.isProfessor(username) == true) {
		return false;
	}

	return true;
}

// takes account's username; return list of courses codes
const vector<string> Database::getCoursesCodes(const string& username) {
	Account* account = getAccount(username);
	return account->getCoursesCodes();
}

// takes username; return courses count
int Database::getCoursesCount(const string& username) {
	Account* account = getAccount(username);
	return account->getCoursesCount();
}

// takes course's code; return assignments count
int Database::getAssignmentsCount(const string& courseCode) {
	return coursesDatabase.getAssignmentsCount(courseCode);
}

// takes account's username;
// return courses codes that user has not enrolled in it
const vector<string> Database::getComplementCoursesCodes(const string& username) {
	vector<string> allCourses = coursesDatabase.getAllCoursesCodes();
	vector<string> userCourses = getCoursesCodes(username);
	vector<string> complementCourses;

	sort(allCourses.begin(), allCourses.end());
	sort(userCourses.begin(), userCourses.end());

	size_t indexInUserCourses = 0;
	
	for (size_t i{ 0 }; i < allCourses.size(); ++i) {
		if ((indexInUserCourses < userCourses.size()) && (allCourses[i] == userCourses[i])) {
			++indexInUserCourses;
		}
		else {
			complementCourses.push_back(allCourses[i]);
		}
	}

	return complementCourses;
}

// student enrolls in course: add course to student's account and add that student to course's students
void Database::enrollInCourse(const string& studentUsername, const string& courseCode) {
	studentsDatabase.addCourseToStudent(studentUsername, courseCode);
	coursesDatabase.addStudentToCourse(studentUsername, courseCode);
}

// takes student's username, course's code and assignment index
// return true if student has submitted a solution; false otherwise
bool Database::isStudentSubmittedSolution(const string& studentUsername, const string& courseCode, int assignmentIndex) {
	return coursesDatabase.isStudentSubmittedSolution(studentUsername, courseCode, assignmentIndex);
}

// takes student's username, course's code and assignment index
// return true if student solution has been graded; false otherwise
bool Database::isStudentSolutionGraded(const string& studentUsername, const string& courseCode, int assignmentIndex) {
	return coursesDatabase.isStudentSolutionGraded(studentUsername, courseCode, assignmentIndex);
}

// takes student's username, course's code and assignment index
// return student grade in the assignment
int Database::getStudentGradeInAssignment(const string& studentUsername, const string& courseCode, int assignmentIndex) {
	return coursesDatabase.getStudentGradeInAssignment(studentUsername, courseCode, assignmentIndex);
}

// takes course's code and assignment index; return assignment's max grade
int Database::getAssignmentMaxGrade(const string& courseCode, int assignmentIndex) {
	return coursesDatabase.getAssignmentMaxGrade(courseCode, assignmentIndex);
}

// takes student username and course code
// remove the course from student's courses list; remove the student from the course's students list
void Database::unenrollFromCourse(const string& studentUsername, const string& courseCode) {
	studentsDatabase.removeCourseFromStudent(studentUsername, courseCode);
	coursesDatabase.removeStudentFromCourse(studentUsername, courseCode);
}

// submit assignment solution
// takes student's username and course's code, assignment's index and the answer
void Database::submitAssignmentSolution(const string& studentUsername, const string& courseCode,
	int assignmentIndex, const string&answer) {
	coursesDatabase.submitAssignmentSolution(studentUsername, courseCode, assignmentIndex, answer);
}

// takes student's username; returns grades report as vector of tuple of form (course code, student grade, max grade)
vector<tuple<string, int, int>> Database::getStudentGradesReport(const string& studentUsername) {
	Account* accountPtr = getAccount(studentUsername);
	vector<string> accountCourses = accountPtr->getCoursesCodes();
	vector<tuple<string, int, int>> gradesReport;

	for (size_t i{ 0 }; i < accountCourses.size(); ++i) {
		int studentGrade = coursesDatabase.getStudentTotalGrade(studentUsername, accountCourses[i]);
		int courseMaxGrade = coursesDatabase.getCourseMaxGrade(accountCourses[i]);

		gradesReport.push_back(make_tuple(accountCourses[i], studentGrade, courseMaxGrade));
	}

	return gradesReport;
}

// takes course code and assignment question; add assignment to that course
void Database::addAssignmentToCourse(const string& courseCode, const string& question) {
	coursesDatabase.addAssignmentToCourse(courseCode, question);
}

// takes course code and assignment index; return solution as vector of tuples of form ( is graded, grade, student username)
vector<tuple<bool, int, const string>> Database::getAssignmentSolutionsInfo(const string& courseCode, int assignmentIndex) {
	return coursesDatabase.getAssignmentSolutionsInfo(courseCode, assignmentIndex);
}

// takes course's code and assignment index; returns submitted solutions count
int Database::getAssignmentSolutionsCount(const string& courseCode, int assignmentIndex) {
	return coursesDatabase.getAssignmentSolutionsCount(courseCode, assignmentIndex);
}

// takes course's code, assignment index and solution index; returns solution's answer
const string& Database::getSolutionAnswer(const string& courseCode, int assignmentIndex, int solutionIndex) {
	return coursesDatabase.getSolutionAnswer(courseCode, assignmentIndex, solutionIndex);
}

// takes course's code, assignment index, solution index and grade; set solution grade
void Database::gradeSolution(const std::string& courseCode, int assignmentIndex, int solutionIndex, int grade) {
	coursesDatabase.gradeSolution(courseCode, assignmentIndex, solutionIndex, grade);
}

// takes course code and professor username and create a new course with that code
// returns true if success; false otherwise (there is another course with that code)
bool Database::createCourse(const string& courseCode, const string& professorUsername) {
	bool status = coursesDatabase.createCourse(courseCode, professorUsername);

	if (status == false) { // there is another course with that code
		return false;
	}
	else { // course was created successfully
		Professor* professorPtr = professorsDatabase.getProfessor(professorUsername);
		professorPtr->addCourse(courseCode);
		return true;
	}
}

// takes coruse's index and assignment's index; returns assignment's question
const string& Database::getAssignmentQuetion(const string& courseCode, int assignmentIndex) {
	return coursesDatabase.getAssignmentQuestion(courseCode, assignmentIndex);
}

// takes course code and Teacher Assistant username; to allow Teacher Assistant to manage course (add assignments and grade students solutions)
// returns true if success; false otherwise (if there is no Teacher Assistant with that username)
bool Database::addTAToCourse(const string& courseCode, const string& usernameTA) {
	bool status = taDatabase.isTA(usernameTA);

	if (status == false) { // there is no Teacher Assistant with that usrname
		return false;
	}
	else { // the username Teacher Assistant
		coursesDatabase.addTAToCourse(courseCode, usernameTA);
		TeacherAssistant* teacherAssistantPtr = taDatabase.getTA(usernameTA);
		teacherAssistantPtr->addCourse(courseCode);
		return true;
	}
}

// return pointer to account object
Account* Database::getAccount(const string& username) const {
	for (size_t i{ 0 }; i < accounts.size(); ++i) {
		if (accounts[i]->getUsername() == username) {
			return accounts[i];
		}
	}

	return nullptr;
}
