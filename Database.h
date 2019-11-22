// Database class definition
#ifndef DATABASE_H
#define DATABASE_H

#include "StudentsDatabase.h"
#include "CoursesDatabase.h"
#include "TAsDatabase.h"
#include "ProfessorsDatabase.h"
#include "Assignment.h"
#include <vector>
#include <string>
#include <tuple>

// enumeration constants represent account types
enum class AccountType { STUDENT = 1, TA, Professor };

class Database {
public:
	bool authenticateUser(const std::string&, const std::string&); // returns true if account authentic
	AccountType getAccountType(const std::string&); // return account type
	void createStudentAccount(const std::string&, const std::string&); // create a new Student account
	void createTAAccount(const std::string&, const std::string&); // create a new TeacherAssistant account
	void createProfessorAccount(const std::string&, const std::string&); // create a new Professor account
	bool isValidUsername(const std::string&); // return true if can create account with defined username
	const std::vector<std::string> getCoursesCodes(const std::string&); // takes account's username; return list of courses codes
	// const std::vector<Assignment>& getCourseAssignments(const std::string&) const; // takes course's code; returns course's assignments
	int getCoursesCount(const std::string&); // takes account's username; return account's courses count
	int getAssignmentsCount(const std::string&); // takes course's code; return assignments count 
	const std::vector<std::string> getComplementCoursesCodes(const std::string&); // takes account's username;
																							  // return courses codes that user has not enrolled in it
	void enrollInCourse(const std::string&, const std::string&); // takes student's username and course's code; enroll student in course
	bool isStudentSubmittedSolution(const std::string&, const std::string&, int); // takes student's username, course's code and assignment index
																						// return true if student has submitted a solution; false otherwise
	bool isStudentSolutionGraded(const std::string&, const std::string&, int); // takes student's username, course's code and assignment index
																					 // return true if student solution has been graded; false otherwise
	int getStudentGradeInAssignment(const std::string&, const std::string&, int); // takes student's username, course's code and assignment index
																						// return student grade in the assignment
	int getAssignmentMaxGrade(const std::string&, int); // takes course's code and assignment index; return assignment's max grade
	void unenrollFromCourse(const std::string&, const std::string&); // takes student username and course code
	void submitAssignmentSolution(const std::string&, const std::string&, int, const std::string&); // takes student's username and course's code, assignment's index and the answer
	std::vector<std::tuple<std::string, int, int>> getStudentGradesReport(const std::string&); // takes student's username; returns grades report as
																							   // vector of tuple of form (course code, student grade, max grade)
	void addAssignmentToCourse(const std::string&, const std::string&); // takes course code and assignment question; add assignment to that course
	std::vector<std::tuple<bool, int, const std::string>> getAssignmentSolutionsInfo(const std::string&, int); // takes course code and assignment index
																												     // return solution as vector of tuples of form
																												     // ( is graded, grade, student username)
	int getAssignmentSolutionsCount(const std::string&, int); // takes course's code and assignment index; returns submitted solutions count
	const std::string& getSolutionAnswer(const std::string&, int, int); // takes course's code, assignment index and solution index; returns solution's answer
	void gradeSolution(const std::string&, int, int, int); // takes course's code, assignment index, solution index and grade; set solution grade
	bool createCourse(const std::string&, const std::string&); // takes course code and professor username and create a new course with that code
															   // returns true if success; false otherwise (there is another course with that code)
	bool addTAToCourse(const std::string&, const std::string&); // takes course code and Teacher Assistant username; to allow Teacher Assistant to manage course
																// (add assignments and grade students solutions)
																// returns true if success; false otherwise (if there is no Teacher Assistant with that username)
	const std::string& getAssignmentQuetion(const std::string&, int); // takes coruse's index and assignment's index; returns assignment's question

private:
	CoursesDatabase coursesDatabase;
	StudentsDatabase studentsDatabase;
	TAsDatabase taDatabase;
	ProfessorsDatabase professorsDatabase;
	std::vector<Account*> accounts;

	Account* getAccount(const std::string&) const; // return pointer to account object
};

#endif