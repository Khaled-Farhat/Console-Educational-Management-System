// Professor class definition.
#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "TeacherAssistant.h"
#include <string>

class Professor : public TeacherAssistant {
public:
	// constructor takes username and password; and calls the constructor of class TeacherAssistant
	Professor(const std::string&, const std::string&);
};

#endif