// TAFlowController definition; represents Teacher Assistant Flow Controller.
#ifndef TAFLOW_H
#define TAFLOW_H

#include "FlowController.h"
#include <string>

class TAFlowController : public FlowController {
public:
	TAFlowController(Database&, const std::string&); // constructor
	virtual ~TAFlowController() {} // virtual destructor
	virtual void run() override; // start TAFlowController

protected:
	int getSolutionIndex() const; // get solution index
	void setSolutionIndex(int); // set solution index
	void addAssignment(); // manage add assignment menu
	void viewAssignment(); // manage view assignment menu

private:
	int solutionIndex; // temporary selected solution's index in assignment solutions

	virtual void viewCourse() override; // manage view course menu
	bool listAssignmentSolutions() const; // list assignment's solutions
	int inputSolutionSelection(); // calls listAssignmentSolutions; input solution selection and return it
	void viewSolution(); // manage view solution menu
	void gradeSolution(); // allows Teacher Assistant to grade solutions
	virtual void displayAssignmentInfo() const override; // display assignment Info
};

#endif