// Member-function definition for class TAsDatabase
#include "TAsDatabase.h"
#include "TeacherAssistant.h"
#include <string>

using namespace std;

// returns true if TeacherAssistant authentic
bool TAsDatabase::authenticateTA(const string& taUsername, const string& password) {
	if (isTA(taUsername) == false) { // invalid username
		return false;
	}

	TeacherAssistant* teacherAssistant = getTA(taUsername);

	if (teacherAssistant->validatePassword(password) == true) {
		return true;
	}
	else { // invalid password
		return false;
	}
}

// takes account's username; return true if it is a TeacherAssistant
bool TAsDatabase::isTA(const string& taUsername) {
	TeacherAssistant* teacherAssistantPtr = getTA(taUsername);

	if (teacherAssistantPtr == nullptr) {
		return false;
	}
	else {
		return true;
	}
}

// takes username and password; create a new TeacherAssistant account
void TAsDatabase::createTAAccount(const string& username, const string& password) {
	teacherAssistants.push_back(TeacherAssistant(username, password));
}

// return pointer to TeacherAssistant object; returns null pointer if not found
TeacherAssistant* TAsDatabase::getTA(const string& username) {
	for (size_t i{ 0 }; i < teacherAssistants.size(); ++i) {
		if (teacherAssistants[i].getUsername() == username) {
			return &teacherAssistants[i];
		}
	}

	return nullptr;
}
