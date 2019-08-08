#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct user{
	string username = "", password = "";

	user(string my_username="", string my_password=""){
		username = my_username;
		password = my_password;
	}

	bool operator == (const user &compared_user){
		return ( username == compared_user.username  &&
				 password == compared_user.password );
	}
};

struct account{
	string type = "";
	user account_data;

	account(string my_username, string my_password, string my_type){
		user my_login_data(my_username, my_password);
		account_data = my_login_data;
		type = my_type;
	}

	account(user my_login_data, string my_type){
		account_data = my_login_data;
		type = my_type;
	}

	bool operator == (const user &compared_user){
		return (account_data == compared_user);
	}
};

struct solution{
	string student_name = "", answer = "";
	int grade = -1, course_index = -1, assignment_index = -1, student_pos = -1;
	bool viewed = 0;

	solution(string my_name, string my_answer, int my_course_index, int my_assignment_index, int my_student_pos){
		student_name = my_name;
		answer = my_answer;
		course_index = my_course_index;
		assignment_index = my_assignment_index;
		student_pos = my_student_pos;
		viewed = 0;
		grade = 0;
	}

	void print_grade_report();

	void print_name();
	void print_grade();
	void print_answer();
	
	void print_solution();
	
	void set_grade(int new_grade);
	void prompt_grade();
	void doctor_view_solution();
};

struct assignment{
	string question = "";
	int course_index = -1, total_solutions = 0, instructor_id = -1;
	vector<solution> all_solutions;

	assignment(int my_insrtuctor_id, string my_question, int my_course_index){
		question = my_question;
		course_index = my_course_index;
		total_solutions = 0;
		all_solutions.clear();
	}

	void doctor_view_assignment();
	void show_grades_report();
	void list_solutions();
	void view_solution();
	int is_submitted(int student_id);
	void print_question();
	void add_solution(solution new_solution);
};

struct student{
	string name = "", password = "";
	int id = -1, my_courses_number = 0, pos = -1;
	vector<int> my_courses_index;

	student(string my_name, string my_password, int my_id, int my_pos){
		name = my_name;
		password = my_password;
		id = my_id;
		pos = my_pos;
		my_courses_number = 0;
	}

	void main_page();

	void suggest_course();
	void register_in_course(int course_id);
	bool is_register_in_course(int course_id);

	void delete_course(int course_index);

	void list_courses();
	void view_course();
	void grades_report();

	bool authenticate(user &entered);
};

struct course{
	string name = "", code = "", instructor = "";
	int id = -1, total_assignments = 0, instructor_id = -1, total_students = 0;
	vector<assignment> all_assignments;
	vector<int> students_id;
	
	course(string my_name, string my_code, string my_instructor, int my_index, int my_instructor_id){
		name = my_name;
		code = my_code;
		instructor = my_instructor;
		id = my_index;
		total_assignments = 0;
		instructor_id = my_instructor_id;
	}

	void add_assignment();
	void doctor_view_course();
	void doctor_list_assignments();
	void doctor_view_assignment();

	void print_course();

	void print_course_name();
	void print_course_code();
	void print_instructor_name();
	void print_course_name_code();

	void student_view_course(int student_pos);
	void student_list_my_assignments(int student_id);
	void submit_solution(int student_pos);
	void print_report(int student_id);

	void add_student(int student_id);
	void unregister(int student_id);
	void delete_submitted_solutions(int student_id);
	void delete_student(int student_id);
};

struct doctor{
	string name = "", password = "";
	int id = -1, my_courses_number = 0, pos = -1;
	vector<int> my_courses_index;

	doctor(string my_name, string my_password, int my_id, int my_pos){
		name = my_name;
		password = my_password;
		id = my_id;
		pos = my_pos;
		my_courses_number = 0;
		my_courses_index.clear();
	}

	void main_page();

	void add_course();

	void list_courses();
	void view_courses();
	
	bool authenticate(user &entered);
};

struct all_data{
	int total_users = 0,
		total_doctors = 0,
		total_students = 0,
		total_courses = 0;
	vector<doctor> all_doctors;
	vector<student> all_students;
	vector<course> all_courses;

	all_data(){
		total_users = 0;
		total_doctors = 0;
		total_students = 0;
		all_doctors.clear();
		all_students.clear();
		all_courses.clear();
	}

	void home_page();
	void login();
	void signup();
	int find_student(user entered);
	int find_doctor(user entered);
	void add_user(account new_user);
	int add_course(course new_course);
	void print_students();
	void print_doctors();
	bool no_space(string s);
	string get_string();
}; all_data data;



void all_data::home_page(){

	int choice = 0;
	cout << "Please make a choice:\n"
		<< "\t1 - Login\n"
		<< "\t2 - Sign up\n"
		<< "\t3 - Shutdown system\n"
		<< "\tChoice: ";
	cin >> choice;
	cout << "\n\n";

	while (choice < 1 || choice > 3){
		cout << "Error. You should enter a number in range [1 - 3]: ";
		cin >> choice;
	}

	switch (choice){
		case 1 :
			login();
			return;

		case 2 :
			signup();
			home_page();
			return;

		case 3 :
			exit(0);
			return;
	}

	home_page();
}

void all_data::login(){

	string user_name = "", password = "";

	cout << "Enter your user name and your password\n";

	cout << "username: ";
	user_name = get_string();


	cout << "password: ";
	password = get_string();

	cout << "\n\n";

	user entered(user_name, password);

	int student_index = find_student(entered);

	if (student_index != -1){
		cout << "Successfully logged in. Welcome " << all_students[student_index].name << "\n\n\n";
		all_students[student_index].main_page();
	}

	else{

		int doctor_index = find_doctor(entered);

		if (doctor_index != -1){
			cout << "Successfully logged in. Welcome Prof. " << all_doctors[doctor_index].name << "\n\n\n";
			all_doctors[doctor_index].main_page();
		}

		else{
			cout << "Incorrect user name or password. Returning to home page..\n\n\n";
			home_page();
			return;
		}
	}
}

void all_data::signup(){

	string username, password;
	int choice;

	cout << "Enter your user name: ";
	username = get_string();

	cout << "Enter your password: ";
	password = get_string();

	string type;
	cout << "Enter account type\n"
		<< "\t1 - professor\n"
		<< "\t2 - student\n"
		<< "\tEnter Choice: ";

	while (1){
		cin >> choice;

		if (choice == 1){
			type = "doctor";
			break;
		}

		else if (choice == 2){
			type = "student";
			break;
		}

		cout << "Error. Enter a number in range [1 - 2]: ";
	}

	cout << "\n\n";
	

	// check if user name available
	user entered(username, password);

	int is_student = find_student(entered),
		is_doctor = find_doctor(entered);

	if (is_student != -1 || is_doctor != -1){
		cout << "this user name is exist\n";
		signup();
		return;
	}

	account new_user(entered, type);
	add_user(new_user);

	cout << "Successfully registered, you can login with your entered username and password\n\n\n";
}

int all_data::find_student(user entered){

	for (int i = 0; i < total_students; i++)
		if (all_students[i].authenticate(entered))
			return i;

	return -1;
}

int all_data::find_doctor(user entered){

	for (int i = 0; i < total_doctors; i++)
		if (all_doctors[i].authenticate(entered))
			return i;

	return -1;
}

void all_data::add_user(account new_user){

	if (new_user.type == "doctor"){
		doctor new_doctor(new_user.account_data.username, new_user.account_data.password, total_users++, total_doctors++);
		all_doctors.push_back(new_doctor);
	}

	else if (new_user.type == "student"){
		student new_student(new_user.account_data.username, new_user.account_data.password, total_users++, total_students++);
		all_students.push_back(new_student);
	}
}

int all_data::add_course(course new_course){

	all_courses.push_back(new_course);

	return total_courses++;
}

void all_data::print_students(){

	cout << "List of all students:\n";

	for (int i = 0; i < total_students; i++)
		cout << "Student " << all_students[i].name << "\tid: " << all_students[i].id << "\n";

	cout << "\n\n";
}

void all_data::print_doctors(){

	cout << "List of all doctors:\n";

	for (int i = 0; i < total_doctors; i++)
		cout << "Dr. " << all_doctors[i].name << "\tid: " << all_doctors[i].id << "\n";

	cout << "\n\n";
}

string all_data::get_string(){
	
	string s = "";

	while (1){
		getline(cin, s);

		if (no_space(s))		break;
		else					cout << "Error. don't type spaces. Re enter your text: ";
	}

	return s;
}

bool all_data::no_space(string s){

	for (int i = 0; i < s.size(); i++)
		if (!isalnum(s[i]))
			return 0;

	return 1;
}



void student::main_page(){

	int choice = 0;
	cout << "Please make a choice:\n"
		<< "\t1 - Register in Course\n"
		<< "\t2 - List My Courses\n"
		<< "\t3 - View Course\n"
		<< "\t4 - Grades Report\n"
		<< "\t5 - Log out\n"
		<< "\tEnter Choice: ";
	cin >> choice;
	cout << "\n\n";

	while (choice < 1 || choice > 5){
		cout << "Error. You should enter a number in range [1 - 5]: ";
		cin >> choice;
	}

	switch (choice){
		case 1 :
			suggest_course();
			break;

		case 2 :
			list_courses();
			cout << "\n";
			break;

		case 3 :
			view_course();
			break;

		case 4 :
			grades_report();
			break;

		case 5 :
			cout << "Successfully logged out\n\n\n";
			data.home_page();
			return;
	}

	main_page();
}

void student::suggest_course(){

	int cnt = 0;
	vector<int> store_index;

	for (int i = 0; i < data.total_courses; i++)
		if (!is_register_in_course(i)){
		cout << ++cnt << " - ";
		data.all_courses[i].print_course_name();

		cout << " - ";
		data.all_courses[i].print_course_code();

		cout << " - ";
		data.all_courses[i].print_instructor_name();

		cout << "\n";
		store_index.push_back(i);
		}

	if ((int)store_index.size() == 0){
		cout << "There are no courses else to register.\n\n\n";
		return;
	}

	int index;
	cout << "\nWhich ith [1 - " << cnt << "] to register? ";

	while (1){
		cin >> index;

		if (index >= 1 && index <= cnt)
			break;

		else
			cout << "Error. Enter a number in range [1 - " << cnt << "]: ";
	}
	index--;

	register_in_course(store_index[index]);

	cout << "\n\nSuccessfully registered in course " << data.all_courses[store_index[index]].name << "\n\n";
}

void student::register_in_course(int course_id){

	data.all_courses[course_id].add_student(id);
	data.total_courses++;

	my_courses_index.push_back(course_id);
	my_courses_number++;
}

bool student::is_register_in_course(int course_id){

	for (int i = 0; i < my_courses_number; i++)
		if (my_courses_index[i] == course_id)
			return 1;

	return 0;
}

void student::delete_course(int course_id){

	for (int i = 0; i < my_courses_number; i++)
		if (my_courses_index[i] == course_id){
			my_courses_index.erase(my_courses_index.begin() + i);
			break;
		}

	my_courses_number--;
}

void student::list_courses(){

	cout << "I have " << my_courses_number << " courses.:\n";

	for (int i = 0; i < my_courses_number; i++){
		cout << "\t";
		data.all_courses[my_courses_index[i]].print_course();
	}

	cout << "\n";
}

void student::view_course(){

	if (my_courses_number == 0){
		cout << "I have 0 courses.\n\n";
		main_page();
		return;
	}

	list_courses();

	int index;
	cout << "Which ith [1 - " << my_courses_number << "] to view? ";
	while (1){
		cin >> index;

		if (index >= 1 && index <= my_courses_number)
			break;

		else
			cout << "Error. Enter a number in range [1 - " << my_courses_number << "]: ";
	}
	index--;

	int index_in_data = my_courses_index[index];
	cout << "\n\n";

	data.all_courses[index_in_data].student_view_course(pos);
}

void student::grades_report(){
	
	if (!my_courses_number){
		cout << "I have 0 courses. Returning to student main page\n\n";
		return;
	}

	for (int i = 0; i < my_courses_number; i++){
		course &select = data.all_courses[my_courses_index[i]];
		select.print_report(pos);
	}
}

bool student::authenticate(user &entered){

	return (name == entered.username  &&
			password == entered.password);
}



void doctor::main_page(){

	int choice = 0;
	cout << "Please make a choice:\n"
		<< "\t1 - List Courses\n"
		<< "\t2 - Create course\n"
		<< "\t3 - View Course\n"
		<< "\t4 - Log out\n"
		<< "\tEnter Choice: ";
	cin >> choice;
	cout << "\n\n";

	while (choice < 1 || choice > 4){
		cout << "Error. You should enter a number in range [1 - 4]: ";
		cin >> choice;
	}

	switch (choice){
		case 1 :
			list_courses();
			cout << "\n";
			break;

		case 2 :
			add_course();
			break;

		case 3 :
			view_courses();
			break;

		case 4 :
			cout << "Successfully logged out\n\n\n";
			data.home_page();
			return;
	}

	main_page();
}

void doctor::add_course(){

	string course_name;
	cout << "Enter course name: ";
	course_name = data.get_string();

	string course_code;
	cout << "Enter course code: ";
	course_code = data.get_string();

	course new_course(course_name, course_code, name, data.total_courses, id);
	int index = data.total_courses;
	data.add_course(new_course);

	my_courses_index.push_back(index);
	my_courses_number++;

	cout << "\n\nCourse created successfully.\n\n\n";
}

void doctor::list_courses(){

	if (my_courses_number == 0){
		cout << "I have 0 courses.\n\n";
		main_page();
		return;
	}

	cout << "I have " << my_courses_number << " courses:\n";

	for (int i = 0; i < my_courses_number; i++){
		cout << i + 1 << ") ";
		data.all_courses[my_courses_index[i]].print_course_name_code();
	}

	cout << "\n";
}

void doctor::view_courses(){

	if (my_courses_number == 0){
		cout << "I have 0 courses. No courses to view.\n\n";
		main_page();
		return;
	}

	list_courses();

	int index;
	cout << "Which ith [1 - " << my_courses_number << "] to view? ";
	while (1){
		cin >> index;

		if (index >= 1 && index <= my_courses_number)
			break;

		else
			cout << "Error. Enter a number in range [1 - " << my_courses_number << "]: ";
	}
	index--;

	int index_in_data = my_courses_index[index];
	cout << "\n";

	data.all_courses[index_in_data].doctor_view_course();
}

bool doctor::authenticate(user &entered){

	return (name == entered.username  &&
		password == entered.password);
}



void course::print_course(){

	cout << "Course: " << name << " - Code: " << code << "\n";
}

void course::add_assignment(){

	string question;
	cout << "Enter the question: ";
	question = data.get_string();

	assignment new_task(instructor_id, question, id);
	all_assignments.push_back(new_task);

	total_assignments++;
	cout << "Assignment created successfully.\n\n\n";
}

void course::doctor_list_assignments(){

	print_course();

	cout << "Course has " << total_assignments << " Assignments\n";
	for (int i = 0; i < total_assignments; i++)
		cout << "\tAssignment (" << i + 1 << ") - Task: " << all_assignments[i].question << "\n";

	cout << "\n";
}

void course::doctor_view_course(){

	print_course_name_code();

	int choice = 0;
	cout << "Please make a choice:\n"
		<< "\t1 - List Assignments\n"
		<< "\t2 - Create Assignment\n"
		<< "\t3 - View Assignment\n"
		<< "\t4 - Back\n"
		<< "\tEnter Choice: ";
	cin >> choice;
	cout << "\n\n";

	while (choice < 1 || choice > 4){
		cout << "Error. You should enter a number in range [1- 4]: ";
		cin >> choice;
	}

	switch (choice){
		case 1:
			doctor_list_assignments();
			break;

		case 2:
			add_assignment();
			break;

		case 3 :
			doctor_view_assignment();
			break;

		case 4:
			data.all_doctors[instructor_id].main_page();
			return;
	}

	doctor_view_course();
}

void course::doctor_view_assignment(){
	doctor_list_assignments();
	
	int index;
	cout << "Which ith [1 - " << total_assignments << "] to view? ";
	while (1){
		cin >> index;

		if (index >= 1 && index <= total_assignments)
			break;

		else
			cout << "Error. Enter a number in range [1 - " << total_assignments << "]: ";
	}
	index--;
	cout << "\n";

	all_assignments[index].doctor_view_assignment();
}

void course::print_course_name(){
	cout << "Course: " << name;
}

void course::print_course_code(){
	cout << "Code: " << code;
}

void course::print_course_name_code(){
	print_course_name();
	cout << " - ";

	print_course_code();
	cout << "\n";
}

void course::print_instructor_name(){
	cout << "Taught by Prof: " << instructor;
}

void course::add_student(int student_id){
	students_id.push_back(student_id);
	total_students++;
}

void course::student_view_course(int student_pos){
	print_course_name();
	cout << " - ";
	print_course_code();
	cout << "\n";

	student_list_my_assignments(student_pos);

	int choice = 0;
	cout << "Please make a choice:\n"
		<< "\t1 - Submit assignment solution\n"		/// done
		<< "\t2 - Unregister from course\n"			/// done
		<< "\t3 - Back\n"							/// done
		<< "\tEnter Choice: ";
	cin >> choice;
	cout << "\n\n";

	while (choice < 1 || choice > 3){
		cout << "Error. You should enter a number in range [1 - 3]: ";
		cin >> choice;
	}

	switch (choice){
		case 1 :
			submit_solution(student_pos);
			break;

		case 2 :
			unregister(student_pos);
			data.all_students[student_pos].main_page();
			return;

		case 3 :
			data.all_students[student_pos].main_page();
			return;
	}

	student_view_course(student_pos);
}

void course::student_list_my_assignments(int student_id){
	for (int i = 0; i < total_assignments; i++){
		cout << "Assignment " << i + 1 << " ";

		int my_solution_index = all_assignments[i].is_submitted(student_id);

		if (my_solution_index == -1)
			cout << "NOT submitted - NA/10\n";
		
		else{
			cout << "submitted - ";

			if (all_assignments[i].all_solutions[my_solution_index].viewed)
				cout << all_assignments[i].all_solutions[my_solution_index].grade << "/10\n";

			else
				cout << "NA/10\n";
		}
	}
}

void course::submit_solution(int student_pos){
	int choosed_index;
	cout << "Which ith [1 - " << total_assignments << "] to submit? ";

	while (1){
		cin >> choosed_index;

		if (choosed_index >= 1 && choosed_index <= total_assignments)
			break;

		else
			cout << "Error. Enter a number in range [1 - " << total_assignments << "]: ";
	}
	choosed_index--;
	cout << "\n";

	all_assignments[choosed_index].print_question();

	string your_solution;
	cout << "Enter you solution (no spaces): ";
	your_solution = data.get_string();

	solution new_solution(data.all_students[student_pos].name, your_solution, id, choosed_index, student_pos);

	all_assignments[id].add_solution(new_solution);

	cout << "Solution submitted successfully\n\n";
}

void assignment::add_solution(solution new_solution){
	all_solutions.push_back(new_solution);
	total_solutions++;
}

void course::unregister(int student_id){
	delete_submitted_solutions(student_id);
	data.all_students[student_id].delete_course(id);
	delete_student(student_id);
}

void course::delete_submitted_solutions(int student_id){
	for (int i = 0; i < total_assignments; i++){
		assignment &select = all_assignments[i];

		int index = select.is_submitted(student_id);
		if (index != -1){
			select.total_solutions--;
			select.all_solutions.erase(select.all_solutions.begin() + index);
		}
	}
}

void course::print_report(int student_pos){
	
	int max_grade = 0,
		my_grade = 0,
		submits_number = 0;

	for (int i = 0; i < total_assignments; i++){

		assignment &select = all_assignments[i];

		int is_sent = select.is_submitted(student_pos);

		if (is_sent != -1){
			submits_number++;
			max_grade += 10;

			int given_grade = select.all_solutions[is_sent].grade;

			if (given_grade != -1)
				my_grade += given_grade;
		}
	}

	print_course_name();
	cout << " - ";

	print_course_code();
	cout << " - ";

	cout << "Total submitted " << submits_number << " assignments - Grade: " << my_grade << '/' << max_grade << "\n";
}

void course::delete_student(int student_id){
	for (int i = 0; i < total_students; i++)
		if (students_id[i] == student_id){
			students_id.erase(students_id.begin() + i);
			break;
		}

	total_students--;
}



void solution::print_name(){
	cout << "Student: " << student_name;
}

void solution::print_answer(){
	cout << "Solution: " << answer;
}

void solution::print_grade(){
	cout << "Grade: ";

	if (grade == -1)			cout << "NA";
	else						cout << grade;

	cout << "/10";
}

void solution::print_grade_report(){
	print_name();
	cout << " - ";
	print_grade();
	cout << "\n";
}

void solution::print_solution(){
	print_name();
	cout << " - ";
	print_answer();
	cout << "\n";
}

void solution::set_grade(int new_grade){
	grade = new_grade;
	viewed = 1;
}

void solution::prompt_grade(){
	int new_grade;
	cout << "Enter new grade: ";
	cin >> new_grade;

	while (new_grade < 0 || new_grade > 10){
		cout << "Error. Grade should be in range [1 - 10]. Enter grade: ";
		cin >> new_grade;
	}

	set_grade(new_grade);

	cout << "Grade set successfully to " << grade << "\n\n";
}

void solution::doctor_view_solution(){
	print_name();
	cout << " - ";
	print_answer();
	cout << " - ";
	print_grade();
	cout << "\n";

	int choice = 0;
	cout << "Please make a choice:\n"
		<< "\t1 - Set grade\n"
		<< "\t2 - back\n"
		<< "\tEnter Choice: ";
	cin >> choice;
	cout << "\n\n";

	while (choice < 1 || choice > 2){
		cout << "Error. You should enter a number in range [1 - 2]. Enter your choice: ";
		cin >> choice;
	}

	switch (choice){
		case  1 :
			prompt_grade();
			break;

		case 2 :
			data.all_courses[course_index].doctor_view_course();
			return;
	}

	doctor_view_solution();
}



void assignment::doctor_view_assignment(){
	int choice = 0;
	cout << "Please make a choice:\n"
		<< "\t1 - Show Grades Report\n"
		<< "\t2 - List Solutions\n"
		<< "\t3 - View Solution\n"
		<< "\t4 - Back\n"
		<< "\tEnter Choice: ";
	cin >> choice;
	cout << "\n\n";

	while (choice < 1 || choice > 4){
		cout << "Error. You should enter a number in range [1 - 4]. Enter your choice: ";
		cin >> choice;
	}

	switch (choice){
		case 1 :
			show_grades_report();
			break;

		case 2 :
			list_solutions();
			cout << "\n";
			break;

		case 3 :
			view_solution();
			break;

		case 4 :
			data.all_doctors[instructor_id].main_page();
			return;
	}

	doctor_view_assignment();
}

void assignment::show_grades_report(){
	for (int i = 0; i < total_solutions; i++)
		all_solutions[i].print_grade_report();

	cout << "\n";
}

void assignment::list_solutions(){
	for (int i = 0; i < total_solutions; i++){
		all_solutions[i].print_name();
		cout << " - ";

		all_solutions[i].print_answer();
		cout << "\n";
	}

	cout << "\n";
}

void assignment::view_solution(){
	list_solutions();

	int index;
	cout << "Which ith [1 - " << total_solutions << "] to view? ";
	while (1){
		cin >> index;

		if (index >= 1 && index <= total_solutions)
			break;

		else
			cout << "Error. Enter a number in range [1 - " << total_solutions << "]: ";
	}
	index--;
	cout << "\n\n";

	all_solutions[index].doctor_view_solution();
}

int assignment::is_submitted(int student_id){
	for (int i = 0; i < total_solutions; i++)
		if (all_solutions[i].student_pos == student_id)
			return i;

	return -1;
}

void assignment::print_question(){
	cout << "Question: " << question << "\n";
}


int main(){

	cout << "Educational Management System\n"
		 << "Small project to implement what I learnt in c++\n\n";
	
	data.home_page();

	return 0;
}
