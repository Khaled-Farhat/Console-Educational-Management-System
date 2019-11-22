// Member-function definition for class StudentsDatabase.
#include "StudentsDatabase.h"
#include "Account.h"
#include "Student.h"
#include <string>

using namespace std;

// returns true if account authentic
bool StudentsDatabase::autheticateStudent(const string& studentUsername, const string& password) {
	if (isStudent(studentUsername) == false) { // invalid username
		return false;
	}

	Student* student = getStudent(studentUsername);

	if (student->validatePassword(password) == true) {
		return true;
	}
	else { // invalid password
		return false;
	}
}

// takes account's username; return true if it is a student
bool StudentsDatabase::isStudent(const string& username) {
	Student* student = getStudent(username);

	if (student == nullptr) {
		return false;
	}
	else {
		return true;
	}
}

// takes username and password; create a new student account
void StudentsDatabase::createStudentAccount(const string& studentUsername, const string& password) {
	students.push_back(Student(studentUsername, password));
}

// takes student user name and course's code; add course to student's courses list
void StudentsDatabase::addCourseToStudent(const string& studentUsername, const string& courseCode) {
	Student* student = getStudent(studentUsername);
	student->addCourse(courseCode);
}

// return pointer to student object; return null pointer if not found
Student* StudentsDatabase::getStudent(const string& studentUsername) {
	for (size_t i{ 0 }; i < students.size(); ++i) {
		if (students[i].getUsername() == studentUsername) {
			return &students[i];
		}
	}

	// if we reach here then the student account was not found
	return nullptr;
}

// takes student's username and course's code; remove the course from the student's courses list
void StudentsDatabase::removeCourseFromStudent(const string& studentUsername, const string& courseCode) {
	Student* student = getStudent(studentUsername);
	student->removeCourse(courseCode);
}
