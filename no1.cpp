/*PLEASE READ:
Firstly, make a students.json AND all_students.json files, 
in the SAME directory as you have this code stored right now.
Secondly, You have to exit the code when done with it, by pressing
"3". This exits while loop at the end of the code.
Thirdly, Enjoy and make improvements!!!*/


#include<iostream>
#include<map>
#include <fstream>  // Include this for file operations
#include<string>
#include "json.hpp" // Include the nlohmann/json library
#include <limits.h>  // Required for PATH_MAX or FILENAME_MAX
#include <direct.h>  // For _getcwd on Windows
#define getcwd _getcwd


using json = nlohmann::json;
using namespace std;

// Holds student details
struct Student
{

	int batch_year;
	string roll_no;
	string department;
	string class_room_no;
};

//Global Map To Hold Student data (key = name , value = struct)
map<string, Student> students_data;



// Function to save student data to JSON file
void save_student_to_json(const Student &student)
{
    // Create a JSON object for the new student
    json students_json;
    students_json["batch_year"] = student.batch_year;
    students_json["department"] = student.department;
    students_json["roll_no"] = student.roll_no;
    students_json["class_room_no"] = student.class_room_no;
	
	//Read existing files,if they exist
	json all_students;
	ifstream infile ("students.json");	
		if (infile.is_open()){
			cout << "Reading from students.json";
			infile >> all_students;
			infile.close(); 
		}else {
			cout << "No file found, starting fresh.\n";
        	// If the file doesn't exist or can't be opened, create a new empty JSON array
        	all_students = json::array();
    	}

	// Add the new students to the list
	all_students.push_back(students_json);

    // Save the updated student list back to the file
    ofstream outfile("students.json");
    if (outfile.is_open()) {
		cout << "Saving To students.json\n";
		cout << all_students.dump(4) << endl; //Display the students saved
        outfile << all_students.dump(4);  // Save the JSON object to file
        outfile.close();
		cout<<"Data Saved succesfully to students.json\n";
    } else {
        cout << "Error opening file to save student data.\n";
    }
}

//Fuction to load and display all students from json file
void load_students_from_json()
{
	ifstream infile("students.json");
	if (infile.is_open())
	{
		json all_students;
		infile >> all_students; // Loads data from json file
		infile.close();

		// To check for any students stored in the file
		if (all_students.is_array() && !all_students.empty()) 
		{
			//Iterate and display student's information the json file
			for (const auto &students_json : all_students)
			{
				cout << "Batch Year: " << students_json["batch_year"] << endl;
                cout << "Department: " << students_json["department"] << endl;
                cout << "Roll Number: " << students_json["roll_no"] << endl;
                cout << "Class Room No: " << students_json["class_room_no"] << endl;
                cout << "----------------------\n";
			}
		} else {
			cout<< " No student data was found in file.\n ";
		}
	} else {
		cout << " Unable to open students.json for reading\n ";
	}

}

//Fuction to add a student
void add_student() {
    string name;
    cout << "Enter student's name: ";
    getline(cin, name);

    // Create a new Student structure
    Student New_Student;

    cout << "Enter student's batch year: ";
    cin >> New_Student.batch_year;
    cin.ignore();

    cout << "Enter student's department: ";
    getline(cin, New_Student.department);

    cout << "Enter student's roll number: ";
    getline(cin, New_Student.roll_no);

    cout << "Enter student's classroom number: ";
    getline(cin, New_Student.class_room_no);

    // Create a JSON object for the new student
    json new_student_json;
    new_student_json["name"] = name;
    new_student_json["batch_year"] = New_Student.batch_year;
    new_student_json["department"] = New_Student.department;
    new_student_json["roll_no"] = New_Student.roll_no;
    new_student_json["class_room_no"] = New_Student.class_room_no;

    // Load existing students from students.json
    json all_students;
    ifstream infile("students.json");
    if (infile.is_open()) {
        infile >> all_students;
        infile.close();
    }

    // Add the new student to the list
    all_students.push_back(new_student_json);

    // Save all students (including the new one) back to students.json
    ofstream outfile("students.json");
    if (outfile.is_open()) {
        outfile << all_students.dump(4);  // Save in pretty format
        outfile.close();
        cout << "Student was added successfully!\n";
    } else {
        cout << "Error: Unable to open students.json for writing.\n";
    }
}


//Get student info
void get_student_info() {
    string name;
    cout << "Enter the student's name: ";
    getline(cin, name);

    // Open and read from the students.json file
    ifstream infile("students.json");
    if (infile.is_open()) {
        json all_students;
        infile >> all_students;  // Load the JSON data from the file
        infile.close();

        bool student_found = false;

        // Iterate through the JSON array to find the student by name
        for (const auto &student_json : all_students) {
            if (student_json["name"] == name) {
                cout << "Student Name: " << student_json["name"] << endl;
                cout << "Batch Year: " << student_json["batch_year"] << endl;
                cout << "Roll Number: " << student_json["roll_number"] << endl;
                cout << "Department: " << student_json["department"] << endl;
                cout << "Class Room No: " << student_json["class_room_no"] << endl;
                cout << "----------------------\n";
                student_found = true;
                break;  // Stop searching once the student is found
            }
        }

        if (!student_found) {
            cout << "No record found for " << name << ".\n";
        }
    } else {
        cout << "Error: Unable to open students.json for reading.\n";
    }
}

//Main function to search or add student info.
int main(){
    char buffer[FILENAME_MAX];  // Create a buffer to store the directory path
    if (getcwd(buffer, FILENAME_MAX)) {  // Get current working directory
        string current_working_dir(buffer);
        cout << "Current working directory: " << current_working_dir << endl;
    } else {
        cout << "Error retrieving current working directory.\n";
    }	
	int choise;

	while (true){
		cout<<"\n Menu: \n";
	    cout << "1. Add a student\n";
        cout << "2. Get student info\n";
        cout << "3. Exit\n";
        cout << "Choose an option (1/2/3): ";
		cin>> choise;
		cin.ignore();//to ignore anything else in the input.

		switch (choise){
		case 1:
			add_student();
			break;
		case 2:
			get_student_info();
			break;
		case 3:
			cout<<"Bye have a great time";
			return 0;	
			
		default:
			cout<< "Invalid input, try again\n";
		}
	}	
}