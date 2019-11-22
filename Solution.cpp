// Member-function definition for class Solution.
#include "Solution.h"
#include <string>

using namespace std;

// constructor takes student's username and soluiton answer
Solution::Solution(const string& username, const string& solutionAnswer)
	: studentUsername(username), answer(solutionAnswer), grade(0), isGraded(false) {}

// takes student's username; returns 1 if the solution is submitted by that student
bool Solution::isStudentSolution(const string& username) const {
	if (username == studentUsername) {
		return true;
	}
	else {
		return false;
	}
}

// return solution's answer
const string& Solution::getAnswer() const { return answer; }

// set solution's grade
void Solution::setGrade(int solutionGrade) {
	grade = solutionGrade;
	isGraded = true;
}

// return solution grade
int Solution::getGrade() const { return grade; }

// return true if the solution was graded by a professor or teacher assistant; returns false otherwise
bool Solution::isSolutionGraded() const {
	if (isGraded == true) {
		return true;
	}
	else {
		return false;
	}
}

// return the username of the student who has submitted the solution
const string& Solution::getStudentUsername() const { return studentUsername; }
