/*******************************************************************************
* Name          : student.cpp
* Author        : Ben Rose
* Date          : February 2, 2019
* Description   : An organized way of viewing student data.
* Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
* Version		: 2.0
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

// Initialize the Student class
class Student {

	/*
	 * List of public methods:
	 * full_name() const: outputs a string with the full name
	 * id() const: outputs CWID number, which is an integer
	 * gpa() const: outputs the student's gpa, of type float
	 * print_info() const: prints student's information.
	 *
	 * print_info() should print in the format (GPA has two decimal places):
	 * Bob Smith, GPA: 3.50, ID: 20146
	 */

public:

	// Constructor
	Student(string first_, string last_, float gpa_, int id_) : first_{first_}, last_{last_}, gpa_{gpa_}, id_{id_} { }

	// Full Name function, returns a string
	string full_name() const {
		return first_ + " " + last_;
	}

	// Prints ID
	int id() const {
		return id_;

	}

	// Prints GPA to the nearest 2 decimal places
	// Used setprecision here, make sure it works
	float gpa() const {
		return gpa_;
	}

	// Prints all Student information
	void print_info() const {
		cout << full_name() << ", " << "GPA: " << fixed << setprecision(2) << gpa() << ", " << "ID: " << id() << endl;
	}



	/*
	 * Private members:
	 * first_: a name of type String
	 * last_: a name of type String
	 * gpa_: a value of type float
	 * id_: a number of type int
	 */

private:

		// Member variables.
		// First and Last are declared on separate lines for the sake of organization.
		string first_, last_;
		float gpa_;
		int id_;

};

/**
	* Takes a vector of Student objects, and returns a new vector
	* with all Students whose GPA is < 1.0.
	*/
	vector<Student> find_failing_students(const vector<Student> &students) {
	    vector<Student> failing_students;
	    for (const auto &student : students) { // For each student in students
	    	if (student.gpa() < 1) {
	    		failing_students.push_back(student);
	    	}
	    }
	    // Iterates through the students vector, appending each student whose gpa is
	    // less than 1.0 to the failing_students vector.
	    return failing_students;
	}

	/**
	* Takes a vector of Student objects and prints them to the screen.
	*/
	void print_students(const vector<Student> &students) {
	  // Iterates through the students vector, calling print_info() for each student.
		for (const auto &student : students) {
			student.print_info();
		}
	}

	/**
	* Allows the user to enter information for multiple students, then
	* find those students whose GPA is below 1.0 and prints them to the
	* screen.
	*/
	int main() {
	    string first_name, last_name;
	    float gpa;
	    int id;
	    char repeat;
	    vector<Student> students;
	    do {
		   cout << "Enter student's first name: ";
		   cin >> first_name;
		   cout << "Enter student's last name: ";
		   cin >> last_name;
		   gpa = -1;
		   while (gpa < 0 || gpa > 4) {
			   cout << "Enter student's GPA (0.0-4.0): ";
			   cin >> gpa;
		   }
		   cout << "Enter student's ID: ";
		   cin >> id;
		   students.push_back(Student(first_name, last_name, gpa, id));
		   cout << "Add another student to database (Y/N)? ";
		   cin >> repeat;
	   } while (repeat == 'Y' || repeat == 'y');
		cout << endl << "All students:" << endl;
		print_students(students);

		cout << endl << "Failing students:";
		if (find_failing_students(students).empty()) { // If there are no students failing
			cout << " None" << endl; // Print a space and the word "None"
			return 0;
		}
		cout << endl;
		print_students(find_failing_students(students)); // Else, call the print students function
		return 0;
	}
