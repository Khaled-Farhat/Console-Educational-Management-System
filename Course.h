// Course class definition.
#ifndef COURSE_H
#define COURSE_H

#include "Assignment.h"
#include <string>
#include <vector>

class Course {
public:
	Course(const std::string&, const std::string&); // constructor takes course's code and professor's username
	const std::string& getCode() const; // return course code
	int getAssignmentsCount() const; // return assignments count
	void addStudent(const std::string&); // takes student's username, add student to course's students list
	bool isStudentSumbittedSolution(const std::string&, int) const; // takes student's username  and assignment index
																	// returns true if student has submitted a solution; false otherwise
	bool isStudentSolutionGraded(const std::string&, int) const; // takes student's username and assignment index
																 // return true if student solution has been graded; false otherwise
	int getStudentGradeInAssignment(const std::string&, int) const; // takes student's username and assignment index
																	// return student grade in the assignment
	int getAssignmentMaxGrade(int) const; // takes assignment index; return assignment's max grade
	void removeStudentFromCourse(const std::string&); // takes student's username; remove student account from students list in the course
	void submitAssignmentSolution(const std::string&, int, const std::string&); // takes student's username and assignment's index and the answer
	void addAssignment(const std::string&); // takes assignment question; add assignment to course
	std::vector<std::tuple<bool, int, const std::string>> getAssignmentSolutionsInfo(int) const; // takes assignment index;
																								 // return solution as vector of tuples of form;
																								 // (is graded, grade, student username)
	int getAssignmentSolutionsCount(int) const; // takes assignment index; returns submitted solutions count
	const std::string& getSolutionAnswer(int, int) const; // takes assignment index and solution index; returns solution's answer
	void gradeSolution(int, int, int); // takes assignment index, solution index and grade; set solution grade

	void addTAToCourse(const std::string&); // takes Teacher Assistant username; to allow Teacher Assistant to manage course (add assignments and grade students solutions)
											// returns true if success; false otherwise (if there is no Teacher Assistant with that username)
	int getMaxGrade() const; // return the total grade of the course
	int getStudentTotalGrade(const std::string&) const; // takes student's username; returns the student's total grade in the course
	const std::string& getAssignmentQuestion(int) const; // takes assignment's index; returns assignment's question

private:
	std::string code;
	std::string professor;
	std::vector<std::string> courseStudents;
	std::vector<std::string> teacherAssistants;
	std::vector<Assignment> assignments;
};

#endif
