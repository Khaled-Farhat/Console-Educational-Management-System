// Member-function definition for class TeacherAssistant
#include "TeacherAssistant.h"
#include "Account.h"
#include <string>

using namespace std;

// constructor takes username and encrypted password
TeacherAssistant::TeacherAssistant(const string& accountUsername, const string& accountPassword)
	: Account(accountUsername, accountPassword) {}
