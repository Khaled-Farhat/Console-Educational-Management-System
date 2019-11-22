// TADatabase class definition; represents Teacher Assistants database
#ifndef TASDATABASE_H
#define TASDATABASE_H

#include "TeacherAssistant.h"
#include <string>

class TAsDatabase {
public:
	bool authenticateTA(const std::string&, const std::string&); // returns true if TA authentucae
	bool isTA(const std::string&); // takes account's username; return true if it is a Teacher Assistant
	void createTAAccount(const std::string&, const std::string&); // takes username and password; create a new TA account
	TeacherAssistant* getTA(const std::string&); // returns pointer to TeacherAssistant object; returns null pointer if not found

private:
	std::vector<TeacherAssistant> teacherAssistants;
};

#endif