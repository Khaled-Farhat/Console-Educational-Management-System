// Member-function definition for class CoursesDatabase.
#include "CoursesDatabase.h"
#include "Course.h"
#include <string>
#include <vector>
#include <tuple>

using namespace std;

// return number of assignments in a course
int CoursesDatabase::getAssignmentsCount(const string& courseCode) {
	Course* coursePtr = getCourse(courseCode);
	return coursePtr->getAssignmentsCount();
}

// return vector of all courses codes
vector<string> CoursesDatabase::getAllCoursesCodes() const {
	vector<string> coursesCodes;

	for (size_t i{ 0 }; i < courses.size(); ++i) {
		coursesCodes.push_back(courses[i].getCode());
	}

	return coursesCodes;
}

// add student to course's students list, takes a pointer to student object and takes coruse's code
void CoursesDatabase::addStudentToCourse(const string& studentUsername, const string& courseCode) {
	Course* coursePtr = getCourse(courseCode);
	coursePtr->addStudent(studentUsername);
}

// takes student's username, course's code and assignment index
// return true if student has submitted a solution; false otherwise
bool CoursesDatabase::isStudentSubmittedSolution(const string& studentUsername, const string& courseCode, int assignmentIndex) {
	Course* coursePtr = getCourse(courseCode);
	return coursePtr->isStudentSumbittedSolution(studentUsername, assignmentIndex);
}

// takes student's username, course's code and assignment index
// return true if student solution has been graded; false otherwise
bool CoursesDatabase::isStudentSolutionGraded(const string& studentUsername, const string& courseCode, int assignmentIndex) {
	Course* coursePtr = getCourse(courseCode);
	return coursePtr->isStudentSolutionGraded(studentUsername, assignmentIndex);
}

// takes student's username, course's code and assignment index
// return student grade in the assignment
int CoursesDatabase::getStudentGradeInAssignment(const string& studentUsername, const string& courseCode, int assignmentIndex) {
	Course* coursePtr = getCourse(courseCode);
	return coursePtr->getStudentGradeInAssignment(studentUsername, assignmentIndex);
}

// takes course's code and assignment index; return assignment's max grade
int CoursesDatabase::getAssignmentMaxGrade(const string& courseCode, int assignmentIndex) {
	Course* coursePtr = getCourse(courseCode);
	return coursePtr->getAssignmentMaxGrade(assignmentIndex);
}

// takes student's username and course's code; remove student account from students list in the course
void CoursesDatabase::removeStudentFromCourse(const string& studentUsername, const string& courseCode) {
	Course* coursePtr = getCourse(courseCode);
	coursePtr->removeStudentFromCourse(studentUsername);
}

// takes student's username and course's code, assignment's index and the answer
void CoursesDatabase::submitAssignmentSolution(const string& studentUsername, const string& courseCode, int assignmentIndex, const string& answer) {
	Course* coursePtr = getCourse(courseCode);
	coursePtr->submitAssignmentSolution(studentUsername, assignmentIndex, answer);
}

// takes course code and assignment question; add assignment to that course
void CoursesDatabase::addAssignmentToCourse(const std::string& courseCode, const std::string& question) {
	Course* coursePtr = getCourse(courseCode);
	coursePtr->addAssignment(question);
}

// takes course code and assignment index; return solution as vector of tuples of form ( is graded, grade, student username)
vector<tuple<bool, int, const string>> CoursesDatabase::getAssignmentSolutionsInfo(const string& courseCode, int assignmentIndex) {
	Course* coursePtr = getCourse(courseCode);
	return coursePtr->getAssignmentSolutionsInfo(assignmentIndex);
}

// takes course's code and assignment index; returns submitted solutions count
int CoursesDatabase::getAssignmentSolutionsCount(const std::string& courseCode, int assignmentIndex) {
	Course* coursePtr = getCourse(courseCode);
	return coursePtr->getAssignmentSolutionsCount(assignmentIndex);
}

// takes course's code, assignment index and solution index; returns solution's answer
const string& CoursesDatabase::getSolutionAnswer(const string& courseCode, int assignmentIndex, int solutionIndex) {
	Course* coursePtr = getCourse(courseCode);
	return coursePtr->getSolutionAnswer(assignmentIndex, solutionIndex);
}

// takes course's code, assignment index, solution index and grade; set solution grade
void CoursesDatabase::gradeSolution(const string& courseCode, int assignmentIndex, int solutionIndex, int grade) {
	Course* coursePtr = getCourse(courseCode);
	coursePtr->gradeSolution(assignmentIndex, solutionIndex, grade);
}

// takes course code and professor username and create a new course with that code
// returns true if success; false otherwise (there is another course with that code)
bool CoursesDatabase::createCourse(const string& courseCode, const string& professorUsername) {
	bool isValid = isValidCourseName(courseCode);

	if (isValid == true) {
		courses.push_back(Course(courseCode, professorUsername));
		return true;
	}
	else {
		return false;
	}
}

// takes course code and Teacher Assistant username; to allow Teacher Assistant to manage course (add assignments and grade students solutions)
// returns true if success; false otherwise (if there is no Teacher Assistant with that username)
void CoursesDatabase::addTAToCourse(const string& courseCode, const string& taUsername) {
	Course* coursePtr = getCourse(courseCode);
	coursePtr->addTAToCourse(taUsername);
}

// takes course's code; returns true if there is no course with that code; false otherwise
bool CoursesDatabase::isValidCourseName(const string& courseCode) {
	Course* coursePtr = getCourse(courseCode);

	if (coursePtr == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

// takes course's code; returns pointer to course object; returns null pointer if not found
Course* CoursesDatabase::getCourse(const string& courseCode) {
	for (size_t i{ 0 }; i < courses.size(); ++i) {
		if (courses[i].getCode() == courseCode) {
			return &courses[i];
		}
	}

	// we reach here if the course was not found
	return nullptr;
}

// takes coruse's index and assignment's index; returns assignment's question
const string& CoursesDatabase::getAssignmentQuestion(const string& courseCode, int assignmentIndex) {
	Course* coursePtr = getCourse(courseCode);
	return coursePtr->getAssignmentQuestion(assignmentIndex);
}

// takes course's code; returns the total grade of the course
int CoursesDatabase::getCourseMaxGrade(const string& courseCode) {
	Course* coursePtr = getCourse(courseCode);
	return coursePtr->getMaxGrade();
}

// takes student's username and course's code; returns the total grade of the student in course
int CoursesDatabase::getStudentTotalGrade(const string& studentUsername, const string& courseCode) {
	Course* coursePtr = getCourse(courseCode);
	return coursePtr->getStudentTotalGrade(studentUsername);
}
