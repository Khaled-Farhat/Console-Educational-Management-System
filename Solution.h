// Solution class definition.
#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>

class Solution {
public:
	Solution(const std::string&, const std::string&); // constructor takes student's username and solution answer
	bool isStudentSolution(const std::string&) const; // takes student's username; returns 1 if the solution is submitted by that student
	const std::string& getAnswer() const; // return solution's answer
	void setGrade(int); // set solution's grade
	int getGrade() const; // return solution grade
	bool isSolutionGraded() const; // return true if the solution was graded by a professor or teacher assistant; returns false otherwise
	const std::string& getStudentUsername() const; // return the username of the student who has submitted the solution

private:
	std::string studentUsername;
	std::string answer;
	int grade;
	bool isGraded;
};

#endif
