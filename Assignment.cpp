// Member-function definition for class Assignment
#include "Assignment.h"
#include "Solution.h"
#include <string>
#include <tuple>

using namespace std;

// constructor takes assignment question
Assignment::Assignment(const string& assignmentQuestion)
	: question(assignmentQuestion), maxGrade(10) {}

// takes student's username; returns true if the student has submitted a solution
bool Assignment::isStudentSumbittedSolution(const string& studentUsername) const {
	for (size_t i{ 0 }; i < solutions.size(); ++i) {
		if (solutions[i].isStudentSolution(studentUsername) == true) {
			return true;
		}
	}

	return false;
}

// takes student's username; returns true if student solution has been graded; false otherwise
bool Assignment::isStudentSolutionGraded(const string& studentUsername) const {
	for (size_t i{ 0 }; i < solutions.size(); ++i) {
		if ((solutions[i].isStudentSolution(studentUsername) == true) && (solutions[i].isSolutionGraded())) {
				return true;
		}
	}

	return false;
}

// takes student's username; returns student grade in the assignment
int Assignment::getStudentGrade(const string& studentUsername) const {
	for (size_t i{ 0 }; i < solutions.size(); ++i) {
		if (solutions[i].getStudentUsername() == studentUsername) {
			return solutions[i].getGrade();
		}
	}

	return 0;
}

// return max grade of the assignment
int Assignment::getMaxGrade() const { return maxGrade; }

// takes student's username and the answer
void Assignment::submitSolution(const string& studentUsername, const string& answer) {
	// remove student's previous submitted solution
	for (size_t i{ 0 }; i < solutions.size(); ++i) {
		if (solutions[i].getStudentUsername() == studentUsername) {
			solutions.erase(solutions.begin() + i);
		}
	}

	solutions.push_back(Solution(studentUsername, answer));
}

// returns solution as vector of tuples of form (is graded, grade, student username)
vector<tuple<bool, int, const string>> Assignment::getSolutionsInfo() const {
	vector<tuple<bool, int, const string>> solutionsInfo;

	for (size_t i{ 0 }; i < solutions.size(); ++i) {
		solutionsInfo.push_back(make_tuple(solutions[i].isSolutionGraded(),
										solutions[i].getGrade(),
										solutions[i].getStudentUsername()));
	}

	return solutionsInfo;
}

// returns submitted solutions count
int Assignment::getSolutionsCount() const {
	return solutions.size();
}

// takes solution index; returns solution's answer
const string& Assignment::getSolutionAnswer(int solutionIndex) const {
	return solutions[solutionIndex - 1].getAnswer();
}

// takes solution index and grade; set solution grade
void Assignment::gradeSolution(int solutionIndex, int grade) {
	solutions[solutionIndex - 1].setGrade(grade);
}

// returns assignment's question
const string& Assignment::getQuestion() const { return question; }

// takes student's username; remove student's submitted solution
void Assignment::removeStudentSolution(const string& studentUsername) {
	for (size_t i{ 0 }; i < solutions.size(); ++i) {
		if (solutions[i].getStudentUsername() == studentUsername) {
			solutions.erase(solutions.begin() + i);
		}
	}
}
