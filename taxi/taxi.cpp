#include<iostream>
#include<cstring>
#include<vector>
#include<unordered_set>
#include<string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include<string>

using namespace std;


// Function Declaration
void loginmenu();
void sethire(int index);
void viewhires(int index);
void update_user(int index);
void update_driver(int index);
void usermenu(int index);
void drivermenu(int index);
void user_register();
void driver_register();
void set_availability(int index);
void set_location(int index);
void userlogin();
void driverlogin();
void create_files();
void load_files();
void manage_login();
void update_files();
void manage_mast(int index);
void RPFD();
void replace_element(vector<string>& vect, int index, string newstr);
vector<string> split(const string& str, const string& delim);

//Global Variable Definition
vector<vector<string>> User, Driver, Active, Records;
int run = 0;

// Function Definitions

void loginmenu() {           // Login screen
	int choice;
	cout << " \n";
	cout << "\t\t******** TourMate ************* " << endl;
	cout << "\t\t| 1. User Login               | " << endl;
	cout << "\t\t| 2. Driver Login             | " << endl; // login screen
	cout << "\t\t| 3. Manage Login              | " << endl;
	cout << "\t\t| 4. New User Registration    | " << endl;
	cout << "\t\t| 5. New Driver Registration  | " << endl;
	cout << "\t\t| 6. Save and Exit            | " << endl;
	cout << "\t\t******************************* " << endl;
	cout << " " << endl;
	cout << "Please enter your choice(1/2/3/4)\n" << ">> ";
label1:
	cin >> choice;
	cin.ignore();
	switch (choice)
	{
	case 1:
		userlogin();                      // mewa passe edit karanna
		break;
	case 2:
		driverlogin();
		break;
	case 3:
		manage_login();
		break;
	case 4:
		user_register();
		break;
	case 5:
		driver_register();
		break;
	case 6:
		run = 1;
		break;
	default:
		cout << "Please enter a number from 1 to 4\n" << ">>";
		cin.clear();
		cin.sync();
		goto label1;

	}
}
void manage_login()
{
	char passward[2] = "2"; //This variable is used to store the login password
	char s[2];//Get the entered password, which is used to verify whether the password and login password are the same 
	int n = 3;      //Limit the number of input errors to 3
	cout << "Please enter the login password: ";
	cin >> s;
	int i = 0;
	if (!strcmp(s, passward)) { //若密码正确
		cout << "Congratulations on your successful login!!! One moment please......\n\n";
		system("pause");
		manage_mast(i);
	}
	else {
		cout << "Waring!!!The password is entered incorrectly. Please exit the system and try again\n";
		system("pause");
		
	}
	
}
void sethire(int index) {
	int n = 0;
	int choice;
	string location;
	for (int i = 0; i < Driver.size(); i++) {
		if (Driver[i][8] == "yes") {
			n++;
			cout << n << ". ";
			for (int j = 2; j < Driver[i].size() - 1; j++) {
				cout << Driver[i][j] << " ";
			}
			cout << endl;
		}
	}
	if (n == 0) {
		cout << "Sorry, No Vehicles are Available at the moment" << endl;
		usermenu(index);
	}
	cout << "Enter the driver Number to set a hire. Or enter 0 to exit : " << endl;
	cin >> choice;
	cin.clear();
	cin.sync();
	if (choice == 0 || choice > n) {
		usermenu(index);
	}
	cout << "Enter the location: " << endl;
	getline(cin, location);
	n = 0;
	for (int i = 0; i < Driver.size(); i++) {
		if (Driver[i][8] == "yes") {
			n++;
			if (n == choice) {
				vector<string> hire = { Driver[i][0],User[index][0],User[index][4],location };
				Active.push_back(hire);
				cout << "Hire set successfully" << endl;
			}
		}
	}


}
void hires(int  index) {

	int choice;
	float distance;
	int rate;
	float cost;
	int n = 0;
	for (int i = 0; i < Active.size(); i++) {
		if (Active[i][0] == Driver[index][0]) {
			cout << i + 1 << ". ";
			n++;
			for (int j = 1; j < Active[i].size(); j++) {
				cout << Active[i][j] << " ";
			}
			cout << endl;
		}
	}
	if (n == 0) {
		cout << endl;
		cout << "Sorry, there are no hires available at the moment";
		drivermenu(index);
	}
	else {
		cout << "\nEnter a hire number to accept, or press 0 to exit: ";
		cin >> choice;
		cin.ignore();
		if (choice <= n && choice != 0) {
			n = 0;
			for (int i = 0; i < Active.size(); i++) {
				if (Active[i][0] == Driver[index][0]) {
					n++;
					if (choice == n) {
						cout << "Enter the distance in  km: ";
						cin >> distance;
						cin.ignore();
						cin.clear();
						cin.sync();
						rate = stoi(Driver[index][7]);
						cost = rate * distance;
						string costs = to_string(cost);
						cout << "Thre trip cost is :" << cost << endl;
						cout << "Order Complete. " << endl;
						system("pause");
						int p = 0;
						for (int k=0;  k < Records.size(); k++) {
							if (Records[k][0] == Driver[index][0]) {
								Records[k].push_back(costs);
								p = 1;
								break;
							}
						}
						update_files();
						if (p == 0) {
							Records.push_back({ Driver[index][0],costs });
						}
						Active.erase(Active.begin() + n - 1);
					top9:
						string k;
						cout << "Press B to go back or press E to Exit " << endl;
						cin >> k;
						cin.ignore();
						if (k == "B") {
							drivermenu(index);
						}
						else if (k == "E") {
							loginmenu();
						}
						else {
							cout << "Invalid Input" << endl;
							goto top9;
						}
						break;
					}

					cout << endl;
				}

			}
		}
	}
}
void update_user(int index) {

	system("cls");
	cout << "-- User Modification--\n" << endl;
	cout << "1. Username: " << endl;
	cout << "2. password: " << endl;
	cout << "3. Name: " << endl;
	cout << "4. Telephone Number" << endl;
	cout << "5. NIC " << endl;
	cout << "6. Exit : \n" << endl;

	int choice = 0;
	string input;
	cout << "Enter the number of the item that needs to be changed: " << endl;
	cin >> choice;
	cin.ignore();

	if (choice == 1) {
	top4:
		cout << "Enter New Username :" << endl;
		getline(cin, input);
		for (auto i = User.begin(); i != User.end(); i++) {
			vector<string> k = *i;
			if (k[0] == input) {
				cout << "Username already exist. Please try another username" << endl;
				goto top4;
			}
		}
		replace_element(User[index], 0, input);
	}
	else if (choice == 2) {
		cout << "Enter New Password :" << endl;
		getline(cin, input);
		replace_element(User[index], 1, input);
	}
	else if (choice == 3) {
		cout << "Enter New Name :" << endl;
		getline(cin, input);
		replace_element(User[index], 2, input);
	}
	else if (choice == 4) {
		cout << "Enter New Telephone Number :" << endl;
		getline(cin, input);
		replace_element(User[index], 3, input);
	}
	else if (choice == 5) {
		cout << "Enter New NIC :" << endl;
		getline(cin, input);
		replace_element(User[index], 4, input);
	}
	else if (choice == 6) {
		usermenu(index);
	}
	else {
		cout << "Invalid Input" << endl;
		update_user(index);
	}
	update_files();
	cout << "\n--User Modification successful.-- " << endl;
	system("pause");
	system("cls");
}
void update_driver(int index) {

	system("cls");
	cout << "--Driver Modification--\n" << endl;
	cout << "1.Username: " << endl;
	cout << "2.Password: " << endl;
	cout << "3.Name: " << endl;
	cout << "4.Telephone Number: " << endl;
	cout << "5.Model and the brand of your vehicle: " << endl;
	cout << "6.Number plate code: " << endl;
	cout << "7.Location: " << endl;
	cout << "8.Car: " << endl;
	cout << "9.Rate per Kilometer: " << endl;
	cout << "0.Exit:\n " << endl;

	int choice = 0;
	string input;
	cout << "Enter the number of the item that needs to be changed: " << endl;
	cin >> choice;
	cin.ignore();
	if (choice == 1) {
	top8:
		cout << "Enter New Username :" << endl;
		getline(cin, input);
		for (auto i = Driver.begin(); i != Driver.end(); i++) {
			vector<string> k = *i;
			if (k[0] == input) {
				cout << "Username already exist. Please try another username" << endl;
				goto top8;
			}
		}
		replace_element(Driver[index], 0, input);
	}
	else if (choice == 2) {
		cout << "Enter New Password :" << endl;
		getline(cin, input);
		replace_element(Driver[index], 1, input);
	}
	else if (choice == 3) {
		cout << "Enter New Name :" << endl;
		getline(cin, input);
		replace_element(Driver[index], 2, input);
	}
	else if (choice == 4) {
		cout << "Enter New Telephone Number :" << endl;
		getline(cin, input);
		replace_element(Driver[index], 3, input);
	}
	else if (choice == 5) {
		cout << "Enter New Model and Brand :" << endl;
		getline(cin, input);
		replace_element(Driver[index], 6, input);
	}
	else if (choice == 6) {
		cout << "Enter New Number plate :" << endl;
		getline(cin, input);
		replace_element(Driver[index], 4, input);
	}
	else if (choice == 7) {
		cout << "Enter New Location :" << endl;
		getline(cin, input);
		replace_element(Driver[index], 8, input);
	}
	else if (choice == 8) {
		cout << "Enter New Car :" << endl;
		getline(cin, input);
		replace_element(Driver[index], 5, input);
	}
	else if (choice == 9) {
		cout << "Enter New Rate:" << endl;
		getline(cin, input);
		replace_element(Driver[index], 7, input);
	}
	else if (choice == 0) {
		cout << "Enter New Password :" << endl;
		drivermenu(index);
	}
	else {
		cout << "Invalid Input" << endl;
		update_driver(index);
	}

	cout << "\n--Driver Modification successful.--" << endl;
	system("pause");
	system("cls");
}
void usermenu(int index) {   // User menu
	int choice;                                                        // usermenu , drivermenu wenama screen ekakata ganna thiyenawan hodai
	cout << " \n";
	cout << "\t\t************TourMate ********************** " << endl;
	cout << "\t\t| 1. View Available Vehicles              | " << endl;
	cout << "\t\t| 2. Update Personal Information          | " << endl;     // login screen
	cout << "\t\t| 3. Help                                 | " << endl;
	cout << "\t\t| 4. Contact us                           | " << endl;
	cout << "\t\t| 5. About us                             | " << endl;
	cout << "\t\t******************************************* " << endl;
	cout << " " << endl;
	cout << "Please enter your choice(1/2/3/4/5)\n";
label3:
	cout << ">> ";
	cin >> choice;
	system("cls");
	switch (choice)
	{
	case 1:
		sethire(index);
		break;
	case 2:
		update_user(index);
		break;
	case 3:
		//help();
		break;                            //  help /contact/about us notepad ekaka save karala methana pennana thiyenawanam hodai
	case 4:
		//contactus();
		break;
	case 5:
		//aboutus();
		break;
	default:
		cout << "Please enter a number from 1 to 5";
		cin.clear();
		cin.sync();
		goto label3;
	}
	cin.ignore();
}
void manage_mast(int index) {
	int mast;
	cout << " \n";
	cout << "\t\t******** TourMate ************* " << endl;
	cout << "\t\t| 1.      New User Registration         | " << endl;
	cout << "\t\t| 2.      New Driver Registration       | " << endl; // login screen
	cout << "\t\t| 3.      update_user                   | " << endl;
	cout << "\t\t| 4.      update_driver                 | " << endl;
	cout << "\t\t| 5.      Reward or Punishment for Drive| " << endl;
	cout << "\t\t| 6.      Save and Exit                 | " << endl;
	cout << "\t\t******************************* " << endl;
	cout << " " << endl;
	cout << "Please enter your choice(1/2/3/4)\n" << ">> ";
label1:
	cin >> mast;
	cin.ignore();
	switch (mast)
	{
	case 1:
		user_register();                      // mewa passe edit karanna
		break;
	case 2:
		driver_register();
		break;
	case 3:
		update_user(index);;
		break;
	case 4:
		update_driver(index);
		break;
	case 5:
		RPFD();
		break;
	case 6:
		run = 1;
		break;
	default:
		cout << "Please enter a number from 1 to 4\n" << ">>";
		cin.clear();
		cin.sync();
		goto label1;

	}
}
void drivermenu(int index) { // Driver menu
	int choice;                                                        // usermenu , drivermenu wenama screen ekakata ganna thiyenawan hodai
	cout << " \n";
	cout << "\t\t************TourMate ********************** " << endl;
	cout << "\t\t| 1. View Available Hires                 | " << endl;
	cout << "\t\t| 2. Set Availability                     | " << endl;     // login screen
	cout << "\t\t| 3. Set Location                         | " << endl;
	cout << "\t\t| 4. Update Personal Info                 | " << endl;
	cout << "\t\t| 5. Payment Details                      | " << endl;
	cout << "\t\t| 6. Payments                             | " << endl;
	cout << "\t\t| 7. Help                                 | " << endl;
	cout << "\t\t| 8. Contact us                           | " << endl;
	cout << "\t\t| 9. About us                             | " << endl;
	cout << "\t\t******************************************* " << endl;
	cout << " " << endl;
	cout << "Please enter your choice(1/2/3/4/5)\n";
	cout << ">> ";
	cin >> choice;
	cin.ignore();
	switch (choice)
	{
	case 1:
		hires(index);                      // mewa passe edit karanna
		break;
	case 2:
		set_availability(index);
		break;
	case 3:
		set_location(index);
		break;
	case 4:
		update_driver(index);
		break;                            //  help /contact/about us notepad ekaka save karala methana pennana thiyenawanam hodai
	case 5:
		//payment details;
		break;
	case 6:
		for (int i=0; i < Records.size(); i++) {
			if (Records[i][0] == Driver[index][0]) {
				for (int j = 1; j < Records[i].size(); j++) {
					cout << Records[i][j] << " " << endl;
				}
			}
		}
		break;
	case 7:
		//help
		break;
	case 8:
		//contact us();
		break;
	case 9:
		//aboutus();
		break;
	default:
		cout << "Please enter a number from 1 to 8";
		cin.ignore();
		drivermenu(index);
	}
}
void user_register() {       // Function for user Registraion
	system("cls");

	cout << "--New User Registration--\n" << endl;
	string regUser, regPass, regName, regTP, regNIC, ru, rp, uname, up;

top1:
	cout << "Enter Username: ";
	getline(cin, regUser);

	for (auto i = User.begin(); i != User.end(); i++) {
		vector<string> k = *i;
		if (k[0] == regUser) {
			cout << "Username already exist. Please try another username" << endl;
			goto top1;
		}
	}

	cout << "Enter password: ";
	getline(cin, regPass);
	cout << "Enter your Name: ";
	getline(cin, regName);
	cout << "Telephone Number: ";
	getline(cin, regTP);
	cout << "Enter NIC: ";
	getline(cin, regNIC);

	User.push_back({ regUser,regPass,regName,regTP,regNIC });
	update_files();
	cout << "\n--User Registration successful.-- " << endl;
	system("pause");
	system("cls");
}
void driver_register() {     // Function for driver registration
	system("cls");

	cout << "--New Driver Registration--\n" << endl;
	string regDriver, regPass, regName, regTP, regMnB, Car, regNumPlate, regRate, regLocation, availability;

top2:
	cout << "Enter Username: ";
	getline(cin, regDriver);

	for (auto i = Driver.begin(); i != Driver.end(); i++) {
		vector<string> k = *i;
		if (k[0] == regDriver) {
			cout << "Username already exist. Please try another username" << endl;
			goto top2;
		}
	}
	cout << "Enter password: ";
	getline(cin, regPass);
	cout << "Enter your Name: ";
	getline(cin, regName);
	cout << "Telephone Number: ";
	getline(cin, regTP);
	cout << "Enter the model and the brand of your vehicle: ";
	getline(cin, regMnB);
	cout << "Enter the model and the brand of your vehicle: ";
	getline(cin, Car);
	cout << "Enter the number plate code: ";
	getline(cin, regNumPlate);
	cout << "Enter the Location: ";
	getline(cin, regLocation);
	cout << "Enter the Rate per Kilometer: ";
	getline(cin, regRate);
	cout << "Enter your availability(Yes/No): ";
label4:
	getline(cin, availability);
	if (availability == "YES" || availability == "Yes" || availability == "yes") {
		availability = "yes";
	}
	else if (availability == "NO" || availability == "No" || availability == "no") {
		availability = "no";
	}
	else {
		cout << "Invalid Input. Please Enter Yes or No" << endl;
		goto label4;
	}

	Driver.push_back({ regDriver,regPass,regName,regTP,regMnB,Car,regNumPlate,regLocation,regRate,availability });
	update_files();
	cout << "\n--Driver Registration successful.--" << endl;
	system("pause");
	system("cls");
}
void set_availability(int index) {   // Function to set the availability of a driver
	cout << "Are you available? (Yes/No): ";
label5:
	string availability;
	getline(cin, availability);
	if (availability == "YES" || availability == "Yes" || availability == "yes") {
		availability = "yes";
	}
	else if (availability == "NO" || availability == "No" || availability == "no") {
		availability = "no";
	}
	else {
		cout << "Invalid Input. Please Enter Yes or No" << endl;
		goto label5;
	}
	replace_element(Driver[index], 8, availability);
	update_files();
}
void set_location(int index) {
	cout << "Enter your Location: ";
label6:
	string location;
	getline(cin, location);
	replace_element(Driver[index], 6, location);
	update_files();
}
void userlogin() {           // User Login function
	int count = 0;
	string username, password;  // methana coma dapu eka code optimazation wala danna
	cout << "Enter Username: ";
	getline(cin, username);
	cout << "Enter Password: ";
	getline(cin, password);
	int i;
	for (i=0; i < User.size(); i++) {
		if (User[i][0] == username && User[i][1] == password) {
			count = 1;
			break;
		}
	}

	if (count == 1) {
		system("cls");
		cout << "Hello " << username << "\n <LOGIN SUCCESSFUL> \n";
		usermenu(i);
	}
	else
	{
		cout << "<LOGIN FAILED> Please check your Username and Password and try again\n";
		system("pause");
		system("cls");
		loginmenu();
	}
} 
void driverlogin() {         // Driver Login Function

	int count = 0;
	string username, password;  // methana coma dapu eka code optimazation wala danna
	cout << "Enter Username: ";
	getline(cin, username);
	cout << "Enter Password: ";
	getline(cin, password);
	int i;
	for (i=0; i < Driver.size(); i++) {
		if (Driver[i][0] == username && Driver[i][1] == password) {
			count = 1;
			break;
		}
	}

	if (count == 1) {
		system("cls");
		cout << "Hello " << username << "\n <LOGIN SUCCESSFUL> \n";
		drivermenu(i);
	}
	else
	{
		system("cls");
		cout << "<LOGIN FAILED> Please check your Username and Password and try again\n";
		system("pause");
		system("cls");
		loginmenu();
	}
}
void RPFD() {
	int choice;
	cout << " \n";
	cout << "\t\t******** TourMate ************* " << endl;
	cout << "\t\t| 1. User Login               | " << endl;
	cout << "\t\t| 2. Driver Login             | " << endl; // login screen
	cout << "\t\t| 3. Manage Login              | " << endl;
	cout << "\t\t| 4. New User Registration    | " << endl;
	cout << "\t\t| 5. New Driver Registration  | " << endl;
	cout << "\t\t| 6. Save and Exit            | " << endl;
	cout << "\t\t******************************* " << endl;
	cout << " " << endl;
	cout << "Please enter your choice(1/2/3/4)\n" << ">> ";
label1:
	cin >> choice;
	cin.ignore();
	switch (choice)
	{
	case 1:
		userlogin();                      // mewa passe edit karanna
		break;
	case 2:
		driverlogin();
		break;
	case 3:
		manage_login();
		break;
	case 4:
		user_register();
		break;
	case 5:
		driver_register();
		break;
	case 6:
		run = 1;
		break;
	default:
		cout << "Please enter a number from 1 to 4\n" << ">>";
		cin.clear();
		cin.sync();
		goto label1;

	}
}
void create_files() {        // Creates the required files if the files does not exist.
	fstream file;
	file.open("driver.txt");
	if (!file) {
		cout << "driver.txt File not detected. Creating new file..." << endl;
		file.open("driver.txt", ios::out); // creates a file if the file does not exixt
	}
	file.close();
	file.open("user.txt");
	if (!file) {
		cout << "user.txt File not detected. Creating new file..." << endl;
		file.open("user.txt", ios::out); // creates a file if the file does not exixt
	}
	file.close();
	file.open("active.txt");
	if (!file) {
		cout << "active.txt File not detected. Creating new file..." << endl;
		file.open("active.txt", ios::out); // creates a file if the file does not exixt
	}
	file.close();
	file.open("records.txt");
	if (!file) {
		cout << "records.txt File not detected. Creating new file..." << endl;
		file.open("records.txt", ios::out); // creates a file if the file does not exixt
	}
	file.close();
}
void load_files() {          // Load the files to global Vectors User and Driver
	User.clear();
	Driver.clear();
	Active.clear();
	Records.clear();
	ifstream user_file;
	user_file.open("user.txt", ios::in);
	string line;
	while (getline(user_file, line)) {
		User.push_back(split(line, "~"));
	}
	user_file.close();

	ifstream driver_file;
	driver_file.open("driver.txt", ios::in);
	while (getline(driver_file, line)) {
		Driver.push_back(split(line, "~"));
	}
	driver_file.close();

	ifstream active_file;
	active_file.open("active.txt", ios::in);
	while (getline(active_file, line)) {
		Active.push_back(split(line, "~"));
	}
	active_file.close();

	ifstream records_file;
	records_file.open("records.txt", ios::in);
	while (getline(records_file, line)) {
		Records.push_back(split(line, "~"));
	}
	records_file.close();
}
void update_files() {        // Function to update the files with current details
	ofstream user_file;
	user_file.open("user.txt", ofstream::out | ofstream::trunc);
	for (int i = 0; i < User.size(); i++) {
		for (int j = 0; j < User[i].size(); j++) {
			user_file << User[i][j] << "~";
		}
		user_file << endl;
	}
	user_file.close();
	ofstream driver_file;
	driver_file.open("driver.txt", ofstream::out | ofstream::trunc);
	for (auto i = Driver.begin(); i != Driver.end(); ++i) {
		vector<string> temp1 = *i;
		for (auto j = temp1.begin(); j != temp1.end(); ++j) {
			string temp2 = *j;
			driver_file << temp2 << "~";
		}
		driver_file << endl;
	}
	driver_file.close();
	ofstream active_file;
	active_file.open("active.txt", ofstream::out | ofstream::trunc);
	for (int i = 0; i < Active.size(); i++) {
		for (int j = 0; j < Active[i].size(); j++) {
			active_file << Active[i][j] << "~";
		}
		active_file << endl;
	}
	active_file.close();
	ofstream records_file;
	records_file.open("records.txt", ofstream::out | ofstream::trunc);
	for (int i = 0; i < Records.size(); i++) {
		for (int j = 0; j < Records[i].size(); j++) {
			records_file << Records[i][j] << "~";
		}
		records_file << endl;
	}
	records_file.close();
}
void replace_element(vector<string>& vect, int index, string newstr) {       //Replace the element with index i of a string vector with a given new string
	vect[index] = newstr;
}

vector<string> split(const string& str, const string& delim) {   // This function splits a string with a given delimeter
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}


// Main Function
int main() {
	create_files(); //creates the required files if the files does not exist.

	while (true) {
		load_files();
		loginmenu();
		update_files();
		if (run == 1) {
			break;
		}
	}
	return(0);
}