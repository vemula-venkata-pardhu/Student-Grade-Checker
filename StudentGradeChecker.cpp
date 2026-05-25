#include <iostream>
#include <string>
#include <unordered_map>
#include <iomanip>

using namespace std;

// Structure to store student details
struct Student {
    int rollNo;
    string name;
    float marks;
    char grade;
};

// Global Hash Table to store students
// Key: Roll Number (int), Value: Student details (Student struct)
unordered_map<int, Student> studentMap;

// Function Prototypes
char calculateGrade(float marks);
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();

int main() {
    int choice;
    
    // Menu-driven loop
    do {
        cout << "\n===== Student Grade Checker =====" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Delete Student" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        // Handle user choice
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);
    
    return 0;
}

// Function to calculate grade based on marks
char calculateGrade(float marks) {
    if (marks >= 90) {
        return 'A';
    } else if (marks >= 80) {
        return 'B';
    } else if (marks >= 70) {
        return 'C';
    } else if (marks >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

// Function to add a new student
void addStudent() {
    Student newStudent;
    
    cout << "\n--- Add New Student ---" << endl;
    cout << "Enter Roll Number: ";
    cin >> newStudent.rollNo;
    
    // Check if student already exists using find() method of unordered_map
    if (studentMap.find(newStudent.rollNo) != studentMap.end()) {
        cout << "Error: Student with this Roll Number already exists!" << endl;
        return;
    }
    
    cout << "Enter Name: ";
    cin.ignore(); // Clear input buffer before reading string with spaces
    getline(cin, newStudent.name);
    
    cout << "Enter Marks: ";
    cin >> newStudent.marks;
    
    // Validate marks
    if (newStudent.marks < 0 || newStudent.marks > 100) {
        cout << "Invalid marks! Enter between 0 and 100." << endl;
        return;
    }
    
    // Calculate grade automatically
    newStudent.grade = calculateGrade(newStudent.marks);
    
    // Insert into hash table
    studentMap[newStudent.rollNo] = newStudent;
    
    cout << "Student added successfully!" << endl;
}

// Function to display all students in a table format
// Also includes optional features: total students, average marks, and topper
void displayStudents() {
    // Check if map is empty
    if (studentMap.empty()) {
        cout << "\nNo students found in the system." << endl;
        return;
    }
    
    cout << "\n--- Student Records ---" << endl;
    cout << left << setw(15) << "Roll Number" 
         << setw(20) << "Name" 
         << setw(10) << "Marks" 
         << "Grade" << endl;
    cout << "----------------------------------------------------" << endl;
    
    float totalMarks = 0;
    float highestMarks = -1;
    string topperName = "";
    
    // Iterate through the hash table and print details
    for (auto const& pair : studentMap) {
        Student s = pair.second;
        cout << left << setw(15) << s.rollNo 
             << setw(20) << s.name 
             << setw(10) << s.marks 
             << s.grade << endl;
             
        // Calculations for optional features
        totalMarks += s.marks;
        if (s.marks > highestMarks) {
            highestMarks = s.marks;
            topperName = s.name;
        }
    }
    cout << "----------------------------------------------------" << endl;
    
    // Display extra simple statistics
    int totalStudents = studentMap.size();
    cout << "Total Students: " << totalStudents << endl;
    if (totalStudents > 0) {
        cout << fixed << setprecision(2);
        cout << "Average Marks: " << (totalMarks / totalStudents) << endl;
        cout << "Topper: " << topperName << " (" << highestMarks << " marks)" << endl;
    }
}

// Function to search for a student using roll number
void searchStudent() {
    int rollNo;
    cout << "\n--- Search Student ---" << endl;
    cout << "Enter Roll Number to search: ";
    cin >> rollNo;
    
    // Search in hash table
    if (studentMap.find(rollNo) != studentMap.end()) {
        Student s = studentMap[rollNo];
        cout << "\nStudent Found!" << endl;
        cout << "Roll Number: " << s.rollNo << endl;
        cout << "Name: " << s.name << endl;
        cout << "Marks: " << s.marks << endl;
        cout << "Grade: " << s.grade << endl;
    } else {
        cout << "Student not found!" << endl;
    }
}

// Function to delete a student record using roll number
void deleteStudent() {
    int rollNo;
    cout << "\n--- Delete Student ---" << endl;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNo;
    
    // Search and delete
    if (studentMap.find(rollNo) != studentMap.end()) {
        studentMap.erase(rollNo); // Remove from hash table
        cout << "Student record deleted successfully!" << endl;
    } else {
        cout << "Student not found! Deletion failed." << endl;
    }
}
