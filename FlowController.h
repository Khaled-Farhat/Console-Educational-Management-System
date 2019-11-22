// FlowController abstract class definition
#ifndef FLOWCONTROLLER_H
#define FLOWCONTROLLER_H

#include "Database.h"
#include "Assignment.h"
#include <string>
#include <vector>

class FlowController {
public:
	FlowController(Database&, const std::string&); // constructor initializes database and username
	virtual void run() = 0; // pure virtual function to start the flow controller
	virtual ~FlowController() {}; // virtual distructor

protected:
	const std::string& getUsername() const; // return username
	const std::string& getCourseCode() const; // return course code
	Database& getDatabase() const; // return reference to database
	int getAssignmentIndex() const; // get assignment index

	void setCourseCode(const std::string&); // set current course's code
	void setAssignmentIndex(int); // set current assignment index

	void displayMenu(const std::vector<std::string>&) const; // takes vector of string and output it
	int inputInteger(int, int); // input integer in range [low - high]; check that it is valid integer; returns it
	std::string inputString(size_t); // takes size; input a string with size less than or equal that size; returns the string

	bool listCourseAssignments(); // call the database to get course's assignments list
	bool listCoursesCodes() const; // call the database to get current account's courses codes

	std::string inputCourseSelection(); // list account's courses codes; input course number
									   // throw exception if user does not have any courses
	int inputAssignmentSelection(); // list course's assignments; input assignment number
									// throw exception if course does not have any assignments

private:
	Database& database; // reference to database
	std::string username; // current account username
	std::string courseCode; // temporary string for current course code
	int assignmentIndex; // temporary assignment index

	virtual void viewCourse() = 0; // pure virtual function to manage view course menu
	virtual void viewAssignment() = 0; // pure virtual function to manage view assignment menu
	virtual void displayAssignmentInfo() const = 0; // pure virtual function to display assignments info
};

#endif
