// CoursesDatabase class definition.
#ifndef COURSESDATABASE_H
#define COURSESDATABASE_H

#include "Course.h"
#include <string>
#include <vector>

class CoursesDatabase {
public:
	int getAssignmentsCount(const std::string&); // takes coruse's code; return assignments count in that course
	std::vector<std::string> getAllCoursesCodes() const; // all get courses codes
	void addStudentToCourse(const std::string&, const std::string&); // add student to course's students list, takes student's username and coruse's code
	bool isStudentSubmittedSolution(const std::string&, const std::string&, int); // takes student's username, course's code and assignment index
																						// return true if student has submitted a solution; false otherwise
	bool isStudentSolutionGraded(const std::string&, const std::string&, int); // takes student's username, course's code and assignment index
																			   // return true if student solution has been graded; false otherwise																			  // returns true if the student has submitted solution to the assignment
	int getStudentGradeInAssignment(const std::string&, const std::string&, int); // takes student's username, course's code and assignment index
																				  // return student grade in the assignment
	int getAssignmentMaxGrade(const std::string&, int); // takes course's code and assignment index; return assignment's max grade
	void removeStudentFromCourse(const std::string&, const std::string&); // takes student's username and course's code; remove student account from students list in the course
	void submitAssignmentSolution(const std::string&, const std::string&, int, const std::string&); // takes student's username and course's code, assignment's index and the answer
	void addAssignmentToCourse(const std::string&, const std::string&); // takes course code and assignment question; add assignment to that course
	std::vector<std::tuple<bool, int, const std::string>> getAssignmentSolutionsInfo(const std::string&, int); // takes course code and assignment index
																											   // return solution as vector of tuples of form
																											   // ( is graded, grade, student username)
	int getAssignmentSolutionsCount(const std::string&, int); // takes course's code and assignment index; returns submitted solutions count
	const std::string& getSolutionAnswer(const std::string&, int, int); // takes course's code, assignment index and solution index; returns solution's answer
	void gradeSolution(const std::string&, int, int, int); // takes course's code, assignment index, solution index and grade; set solution grade
	bool createCourse(const std::string&, const std::string&); // takes course code and professor username and create a new course with that code
															   // returns true if success; false otherwise (there is another course with that code)
	void addTAToCourse(const std::string&, const std::string&); // takes course code and Teacher Assistant username; to allow Teacher Assistant to manage course
																// (add assignments and grade students solutions)
																// returns true if success; false otherwise (if there is no Teacher Assistant with that username)
	int getCourseMaxGrade(const std::string&); // takes course's code; returns the total grade of the course
	int getStudentTotalGrade(const std::string&, const std::string&); // takes student's username and course's code; returns the total grade of the student in course
	const std::string& getAssignmentQuestion(const std::string&, int); // takes coruse's index and assignment's index; returns assignment's question

private:
	std::vector<Course> courses;

	bool isValidCourseName(const std::string&); // takes course's code; returns true if there is no course with that code; false otherwise
	Course* getCourse(const std::string&); // takes course's code; returns pointer to course object; returns null pointer if not found
};

#endif