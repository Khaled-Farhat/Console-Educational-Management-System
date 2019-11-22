#include "EducationalManagmenetSystem.h"
#include "Database.h"

using namespace std;

int main() {
	Database systemDatabase;
	EducationalManagementSystem EMS(systemDatabase);
	EMS.run();

	return 0;
}
