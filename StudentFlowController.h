// StudentFlow controller class definion.
#ifndef STUDENTFLOW_H
#define	STUDENTFLOW_H

#include "FlowController.h"
#include "Database.h"
#include <string>

class StudentFlowController : public FlowController {
public:
	StudentFlowController(Database&, const std::string&); // constructor

	virtual void run() override; // start StudentFlowController

private:
	void enrollInCourse(); // enroll in course
	virtual void viewCourse() override; // manage view course menu
	virtual void viewAssignment() override; // mangage view assignment
	virtual void displayAssignmentInfo() const override; // display assignment info
	void submitAssignmentSolution(); // manage submit solution
	void gradesReport() const; // calls the database to get student's grades report
};

#endif