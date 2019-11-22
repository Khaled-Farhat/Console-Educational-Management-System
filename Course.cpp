// Member-function definition for class Course.
#include "Course.h"
#include <string>
#include <vector>
#include <tuple>

using namespace std;

// constructor takes course's code and professor's username
Course::Course(const string& courseCode, const string& username)
	: code(courseCode), professor(username) {}

// return course code
const std::string& Course::getCode() const { return code; }

// return assignments count
int Course::getAssignmentsCount() const { return assignments.size(); }

// takes student's username, add student to course's students list
void Course::addStudent(const string& studentUsername) {
	courseStudents.push_back(studentUsername);
}

// takes student's username  and assignment index
// returns true if student has submitted a solution; false otherwise
bool Course::isStudentSumbittedSolution(const string& studentUsername, int assignmentIndex) const {
	return assignments[assignmentIndex - 1].isStudentSumbittedSolution(studentUsername);
}

// takes student's username and assignment index; returns true if student solution has been graded; false otherwise
bool Course::isStudentSolutionGraded(const string& studentUsername, int assignmentIndex) const {
	return assignments[assignmentIndex - 1].isStudentSolutionGraded(studentUsername);
}

// takes student's username and assignment index; returns student grade in the assignment
int Course::getStudentGradeInAssignment(const string& studentUsername, int assignmentIndex) const {
	return assignments[assignmentIndex - 1].getStudentGrade(studentUsername);
}

// takes assignment index; return‘ assignment's max grade
int Course::getAssignmentMaxGrade(int assignmentIndex) const {
	return assignments[assignmentIndex - 1].getMaxGrade();
}

// takes student's username; remove student account from students list in the course
void Course::removeStudentFromCourse(const string& studentUsername) {
	for (size_t i{ 0 }; i < courseStudents.size(); ++i) {
		if (courseStudents[i] == studentUsername) {
			courseStudents.erase(courseStudents.begin() + i);
			break;
		}
	}

	for (size_t i{ 0 }; i < assignments.size(); ++i) {
		assignments[i].removeStudentSolution(studentUsername);
	}
}

// takes student's username and assignment's index and the answer
void Course::submitAssignmentSolution(const string& studentUsername, int assignmentIndex, const string& answer) {
	assignments[assignmentIndex - 1].submitSolution(studentUsername, answer);
}

// takes assignment question; add assignment to course
void Course::addAssignment(const string& question) {
	assignments.push_back(Assignment(question));
}

// takes assignment index; return solution as vector of tuples of form (is graded, grade, student username)
vector<tuple<bool, int, const string>> Course::getAssignmentSolutionsInfo(int assignmentIndex) const {
	return assignments[assignmentIndex - 1].getSolutionsInfo();
}

// takes assignment index; returns submitted solutions count
int Course::getAssignmentSolutionsCount(int assignmentIndex) const {
	return assignments[assignmentIndex - 1].getSolutionsCount();
}

// takes assignment index and solution index; returns solution's answer
const string& Course::getSolutionAnswer(int assignmentIndex, int solutionIndex) const {
	return assignments[assignmentIndex - 1].getSolutionAnswer(solutionIndex);
}

// takes assignment index, solution index and grade; set solution grade
void Course::gradeSolution(int assignmentIndex, int solutionIndex, int grade) {
	assignments[assignmentIndex - 1].gradeSolution(solutionIndex, grade);
}

// takes Teacher Assistant username; to allow Teacher Assistant to manage course (add assignments and grade students solutions)
// returns true if success; false otherwise (if there is no Teacher Assistant with that username)
void Course::addTAToCourse(const string& taUsername) {
	teacherAssistants.push_back(taUsername);
}

// return the total grade of the course
int Course::getMaxGrade() const {
	int assignmentsCount = getAssignmentsCount();
	int maxGrade{ 0 };

	for (int i{ 0 }; i < assignmentsCount; ++i) {
		maxGrade += assignments[i].getMaxGrade();
	}

	return maxGrade;
}

// takes student's username; returns the student's total grade in the course
int Course::getStudentTotalGrade(const string& studentUsername) const {
	int assignmentsCount = getAssignmentsCount();
	int studentGrade{ 0 };

	for (int i{ 0 }; i < assignmentsCount; ++i) {
		studentGrade += assignments[i].getStudentGrade(studentUsername);
	}

	return studentGrade;
}

// takes assignment's index; returns assignment's question
const string& Course::getAssignmentQuestion(int assignmentIndex) const {
	return assignments[assignmentIndex - 1].getQuestion();
}
