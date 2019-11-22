// Student class definition
#ifndef STUDENT_H
#define STUDENT_H

#include "Account.h"
#include <string>

class Student : public Account {
public:
	// constructor takes username and password; and calls the constructor of class Account
	Student(const std::string&, const std::string&);
};

#endif