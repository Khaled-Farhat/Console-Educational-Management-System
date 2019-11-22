// Member-function definition for class EducationalManagementSystem
#include "EducationalManagmenetSystem.h"
#include "Database.h"
#include "FlowController.h"
#include "StudentFlowController.h"
#include "TAFlowController.h"
#include "ProfessorFlowController.h"
#include <iostream>
#include <string>
#include <cctype>
#include <memory>

using namespace std;

// enumeration constants represent main menu options
enum class MainMenuOption{LOGIN = 1, SIGNUP, EXIT};

// constructor
EducationalManagementSystem::EducationalManagementSystem(Database& theDatabase)
	: database(theDatabase) {}

// start the Educational Management System
void EducationalManagementSystem::run() {
	bool userExited = false; // whether user has exited or not

	cout << "Designed and implemented by Khaled Farhat - github.com/Khaled-Farhat/\n";

	while (userExited == false) {
		// loop while user has not exited
		displayMainMenu();

		int choice;
		choice = inputInteger(1, 3); // input integer in range [1 - 3]

		MainMenuOption option = static_cast<MainMenuOption>(choice);

		switch (option) {
			case MainMenuOption::LOGIN:
				login();
				break;

			case MainMenuOption::SIGNUP:
				signup();
				break;

			case MainMenuOption::EXIT:
				cout << "\nThank you for using Educational Management System";
				cin.ignore();
				userExited = true;
				break;
		}
	}
}

// show main menu options
void EducationalManagementSystem::displayMainMenu() const {
	cout << "\nWelcome to the Educational Management System"
		<< "\n1 - Login"
		<< "\n2 - Signup"
		<< "\n3 - Exit"
		<< "\nMake a choice: ";
}

// perform login
void EducationalManagementSystem::login() {
	string username;
	string password;

	// input username
	cout << "\nEnter your username: ";
	username = inputString(8);

	// input password
	cout << "Enter your account password: ";
	password = inputString(8);

	// set userAutheticated state to true if user is authenticated;
	// false otherwise
	userAuthenticated = database.authenticateUser(username, password);

	if (userAuthenticated == true) {
		// set account type; start the flow controller
		currentUsername = username;
		accountType = database.getAccountType(username);
		runFlowController();
	}
	else {
		cout << "\nInvalid username or password.\n";
	}
}

// perform sign up
void EducationalManagementSystem::signup() {
	int accountTypeChoice;
	string username;
	string password;

	// input account's type
	cout << "\nEnter account type: "
		<< "\n1 - Student"
		<< "\n2 - Teacher Assistant"
		<< "\n3 - Professor"
		<< "\nMake a choice: ";
	accountTypeChoice = inputInteger(1, 3);

	// input username and check that it is valid
	while (1) {
		cout << "\nEnter username (max 8 characters, without spaces): ";
		username = inputString(8);

		if (database.isValidUsername(username) == true) {
			break;
		}
		else {
			cout << "\nThis user name is used before.";
		}
	}

	// input password
	cout << "Enter your account password (max 8 characters, without spaces): ";
	password = inputString(8);

	AccountType accountType = static_cast<AccountType>(accountTypeChoice);

	// call database to create new account
	switch (accountType) {
		case AccountType::STUDENT:
			database.createStudentAccount(username, password);
			break;

		case AccountType::TA:
			database.createTAAccount(username, password);
			break;

		case AccountType::Professor:
			database.createProfessorAccount(username, password);
			break;
	}

	cout << "\nSuccessfully created account " << username << "\n";
}

// start the flow controller
void EducationalManagementSystem::runFlowController() {
	unique_ptr<FlowController> FlowControllerPtr = createFlowController();

	// start the FlowController using polymorphic behavior
	FlowControllerPtr->run();
}

// private utility function to input integer
int EducationalManagementSystem::inputInteger(int low, int high) {
	int integer = 0;

	while (1) {
		string input;
		getline(cin, input);

		if (input.size() == 0) {
			continue;
		}

		bool validInput = true;

		for (size_t i{ 0 }; i < input.size(); ++i) {
			if (isdigit(input[i]) == false) {
				validInput = 0;
				break;
			}
		}

		if (input.size() > 9) {
			validInput = 0;
		}

		if (validInput) {
			integer = stoi(input);

			if (integer < low || integer > high) {
				validInput = false;
			}
		}

		if (validInput) {
			break;
		}
		else {
			cout << "Invalid input. Enter integer in range [" << low << " - " << high << "]: ";
		}
	}

	return integer;
}

// private utility function to input a string
string EducationalManagementSystem::inputString(size_t stringSize) {
	string inputString;

	while (1) {
		string input;
		getline(cin, input);

		if (input.size() == 0) {
			continue;
		}

		bool validInput = true;

		for (size_t i{ 0 }; i < input.size(); ++i) {
			if (input[i] == ' ') {
				validInput = 0;
			}
		}

		if (input.size() > stringSize) {
			validInput = 0;
		}

		if (validInput) {
			inputString = input;
			break;
		}
		else {
			cout << "Invalid input. Enter a string with no spaces and size less than "
				<< stringSize << ": ";
		}
	}

	return inputString;
}

unique_ptr<FlowController> EducationalManagementSystem::createFlowController() {
	unique_ptr<FlowController> tempPtr = nullptr;

	switch (accountType) {
		case AccountType::STUDENT:
			tempPtr = make_unique<StudentFlowController>(database, currentUsername);
			break;

		case AccountType::TA:
			tempPtr = make_unique<TAFlowController>(database, currentUsername);
			break;

		case AccountType::Professor:
			tempPtr = make_unique<ProfessorFlowController>(database, currentUsername);
			break;
	}

	return tempPtr;
}
