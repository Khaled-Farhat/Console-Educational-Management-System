// Member-function definition for class Account
#include "Account.h"
#include "Course.h"
#include <string>
#include <vector>

using namespace std;

// constructor takes uesrname and password
Account::Account(const string& accountUsername, const string& accountPassword)
	: username(accountUsername), password(accountPassword) {}

// return username
const string& Account::getUsername() const { return username; }

// return true if the password is valid
bool Account::validatePassword(const string& pass) const {
	if (pass == password) {
		return true;
	}
	else {
		return false;
	}
}

// return courses code
const vector<string> Account::getCoursesCodes() const {
	return courses;
}

// return courses count
int Account::getCoursesCount() const {
	return courses.size();
}

// add course's to account's courses list
void Account::addCourse(const string& course) {
	courses.push_back(course);
}

// takes course's code; remove courses from courses list
void Account::removeCourse(const string& course) {
	for (size_t i{ 0 }; i < courses.size(); ++i) {
		if (course == courses[i]) {
			courses.erase(courses.begin() + i);
			break;
		}
	}
}
