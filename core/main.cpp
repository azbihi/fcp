#include <iostream>
#include <algorithm>
using namespace std;

//Constants
//intruducing a couple of const Variables for size of array
const int MAX_STUDENTS = 100 ;
const int MAX_COURSES = 10 ;
 //Structs
 // intruducing a couple of structs to keeping our students data
 struct Course
 {
     string name;
     int units;
     float grade;
 };

 struct Student
 {
     string firstName;
     string lastName;
     string studentId;
     string major;
     Course courses[MAX_COURSES];
     int courseCount;
     float gpa;
 };
 //Global Variables
 Student students[MAX_STUDENTS];
 int studentCount = 0;
 // Helper Functions
 // func will validate grade
 bool gradeCheck(float grade) {
     return grade >= 0 && grade <= 20;
 }
 bool isUniqueId (const string& id)
 {
     for (int i = 0 ; i < studentCount ; i++)
     {
         if (id == students[i].studentId)
         {
             return false ;
         }
     }
     return true;
 }
 //this function is checking length of string and being sure all of chars are digits
 bool isValidStudentId (const string& id) {
     return id.length() == 8 && all_of(id.begin(), id.end(), ::isdigit) && isUniqueId(id);
     }
// this func work is to calculate gpa
void GPAclal (Student& student)
{
    float totalPoints = 0;
    int totalUnits = 0 ;

        for (int i = 0 ; i < student.courseCount; ++i )
        {
            totalPoints += (student.courses[i].grade) * (student.courses[i].units);
            totalUnits += student.courses[i].units;
        }
        student.gpa = totalPoints > 0 ? totalPoints / totalUnits : 0 ;
}
// Core Functions
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "\nCannot add more students. Maximum capacity reached.\n";
        return;
    }

    Student student;
    cout << "\n=== New Student Registration ===\n";
    cout << "First Name: ";
    cin >> student.firstName;
    cout << "Last Name: ";
    cin >> student.lastName;

    do {
        cout << "Student ID (8 digits): ";
        cin >> student.studentId;
    } while (!isValidStudentId(student.studentId));

    cout << "Major: ";
    cin >> student.major;

    student.courseCount = 0;
    student.gpa = 0.0;

    students[studentCount++] = student;
    cout << "\nStudent successfully registered.\n";
}
// Core Functions

void deleteSrudnet()
{
    string studentId;
    cout << "\n=== Delete Student ===\n";
    cout << "Student ID: ";
    cin >> studentId;

    int studentIndex = -1;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].studentId == studentId) {
            studentIndex = i;
            break;
        }
    }

    if (studentIndex == -1) {
        cout << "Student not found!\n";
        return;
    }

    for (int i = studentIndex; i < studentCount - 1; ++i) {
        students[i] = students[i + 1];
    }

    studentCount--;
    cout << "\nStudent successfully deleted.\n";
}
void addStudent()
{
//checking for count of students limit
    if (studentCount >= MAX_STUDENTS) {
        cout << "\nCannot add more students. Maximum capacity reached.\n";
        return;
    }

//making a temp Variable
    Student student;
    // entering data
    cout << "\n=== New Student Registration ===\n";
    cout << "First Name: ";
    cin >> student.firstName;
    cout << "Last Name: ";
    cin >> student.lastName;
// cheking student id
    do {
        cout << "Student ID (8 digits): ";
        cin >> student.studentId;
    } while (!isValidStudentId(student.studentId));

    cout << "Major: ";
    cin >> student.major;

    student.courseCount = 0;
    student.gpa = 0.0;
//We puting temp data into the main variable.
    students[studentCount++] = student;
    cout << "\nStudent successfully registered.\n";
}

 int main()
 {
//defining int for chosing operation
     int choice;
// main menu of project
     while (true) {
         cout << "\n=== Student Management System ===\n";
         cout << "1. Add New Student\n";
         cout << "2. Delete Student\n";
         cout << "3. Add Course to Student\n";
         cout << "4. List All Students\n";
         cout << "5. List Students by Major\n";
         cout << "6. Generate Transcript\n";
         cout << "7. Exit\n";
         cout << "Enter your choice: ";
         cin >> choice;
}
 }
