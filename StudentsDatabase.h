// StudentsDatabase class definition.
#ifndef STUDENTSDATABASE_H
#define STUDENTSDATABASE_H

#include "Account.h"
#include "Student.h"
#include "Course.h"
#include <string>
#include <vector>

class StudentsDatabase {
public:
	bool autheticateStudent(const std::string&, const std::string&); // returns true if account authentic
	bool isStudent(const std::string&); // takes account's username; return true if it is a student
	void createStudentAccount(const std::string&, const std::string&); // takes username and password; create a new student account
	void addCourseToStudent(const std::string&, const std::string&); // takes student user name and course's code; add course to student's courses list
	Student* getStudent(const std::string&); // return pointer to student object
	void removeCourseFromStudent(const std::string&, const std::string&); // takes student's username and course's code; remove the course from the student's courses list

private:
	std::vector<Student> students;
};

#endif
