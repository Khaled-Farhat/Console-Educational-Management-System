// Memeber-function definition for class Student
#include "Account.h"
#include "Student.h"
#include <string>

using namespace std;

Student::Student(const string& accountUsername, const string& accountPassword)
	: Account(accountUsername, accountPassword) {}
