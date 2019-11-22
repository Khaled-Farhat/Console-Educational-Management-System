//TeacherAssistant class definition
#ifndef TEACHERASSISTANT_H
#define TEACHERASSISTANT_H

#include "Account.h"
#include <string>

class TeacherAssistant : public Account {
public:
	// constructor takes username and password; and calls the constructor of class Account
	TeacherAssistant(const std::string&, const std::string&);
	virtual ~TeacherAssistant() {} // virtual destructor
};

#endif