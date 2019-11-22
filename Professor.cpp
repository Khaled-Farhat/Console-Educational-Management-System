// Mmeber-function definition for class Professor
#include "Professor.h"
#include "Account.h"
#include <string>

using namespace std;

Professor::Professor(const string& accountUsername, const string& accountPassword)
	: TeacherAssistant(accountUsername, accountPassword) {}
