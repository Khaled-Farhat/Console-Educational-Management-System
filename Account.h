// Account class definition.
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Course.h"
#include <string>
#include <vector>

class Account {
public:
	Account(const std::string&, const std::string&); // constructor initializes username and password

	bool validatePassword(const std::string&) const; // returns true if the password is correct; false otherwise
	const std::vector<std::string> getCoursesCodes() const; // return vector of courses codes
	int getCoursesCount() const; // return the number of courses that account's has

	void addCourse(const std::string&); // add course to account's courses vector
	void removeCourse(const std::string&); // remove course from account's courses
	const std::string& getUsername() const;

private:
	std::string username;
	std::string password;
	std::vector<std::string> courses;
};

#endif
