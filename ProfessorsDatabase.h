// ProfessorsDatabase class definition.
#ifndef PROFESSORSDATABASE_H
#define PROFESSORSDATABASE_H

#include "Professor.h"
#include <vector>
#include <string>

class ProfessorsDatabase {
public:
	bool authenticateProfessor(const std::string&, const std::string&); // returns true if Professor authentic
	bool isProfessor(const std::string&); // takes account's username; return true if it is a professor
	void createProfessorAccount(const std::string&, const std::string&); // takes username and password; create a new professor account
	Professor* getProfessor(const std::string&); // return pointer to Professor object

private:
	std::vector<Professor> professors;
};

#endif