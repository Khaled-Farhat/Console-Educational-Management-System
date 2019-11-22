// Assignment class definition.
#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "Solution.h"
#include <string>
#include <vector>
#include <tuple>

class Assignment {
public:
	Assignment(const std::string&); // constructor takes assignment question
	bool isStudentSumbittedSolution(const std::string&) const; // takes student's username; returns true if the student has submitted a solution
	bool isStudentSolutionGraded(const std::string&) const; // takes student's username; returns true if student solution has been graded; false otherwise
	int getStudentGrade(const std::string&) const; // takes student's username; returns student grade in the assignment
	int getMaxGrade() const; // return max grade of the assignment
	void submitSolution(const std::string&, const std::string&); // takes student's username and the answer
	std::vector<std::tuple<bool, int, const std::string>> getSolutionsInfo() const; // returns solution as vector of tuples of form (is graded, grade, student username)
	int getSolutionsCount() const; // returns submitted solutions count
	const std::string& getSolutionAnswer(int) const; // takes solution index; returns solution's answer
	void gradeSolution(int, int); // takes solution index and grade; set solution grade
	const std::string& getQuestion() const; // return assignment's question
	void removeStudentSolution(const std::string&); // takes student's username; remove student's submitted solution

private:
	std::string question;
	int maxGrade;
	std::vector<Solution> solutions;
};

#endif