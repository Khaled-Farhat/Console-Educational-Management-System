// Member-function definition for class ProfessorsDatabase
#include "ProfessorsDatabase.h"
#include "Professor.h"
#include <string>
#include <memory>

using namespace std;

// returns true if Professor authentic
bool ProfessorsDatabase::authenticateProfessor(const string& professorUsername, const string& password) {
	if (isProfessor(professorUsername) == false) { // invalid username
		return false;
	}

	Professor* professor = getProfessor(professorUsername);

	if (professor->validatePassword(password) == true) {
		return true;
	}
	else { // invalid password
		return false;
	}
}

// takes account's username; return true if it is a professor
bool ProfessorsDatabase::isProfessor(const string& professorUsername) {
	Professor* professor = getProfessor(professorUsername);

	if (professor == nullptr) {
		return false;
	}
	else {
		return true;
	}
}

// takes username and password; create a new professor account
void ProfessorsDatabase::createProfessorAccount(const string& username, const string& password) {
	professors.push_back(Professor(username, password));
}

// return pointer to Professor object
Professor* ProfessorsDatabase::getProfessor(const string& username) {
	for (size_t i{ 0 }; i < professors.size(); ++i) {
		if (professors[i].getUsername() == username) {
			return &professors[i];
		}
	}

	// not found
	return nullptr;
}
