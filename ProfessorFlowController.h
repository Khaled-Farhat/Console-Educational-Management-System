// ProfessorFlowController definition.
#ifndef PROFESSORFLOW_H
#define PROFESSORFLOW_H

#include "TAFlowController.h"
#include "Database.h"
#include <string>

class ProfessorFlowController : public TAFlowController {
public:
	ProfessorFlowController(Database&, const std::string&);
	virtual void run() override; // start ProfessorFlowController

private:
	virtual void viewCourse() override; // manage view course menu
	void createCourse(); // create course
	void addTAToCourse(); // add Teacher Assistant to course
};

#endif