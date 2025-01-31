#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
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
 int studentCount = 0; //counting the number for students
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

void addCourseToStudent() {
    string studentId;
    cout << "\n=== Add Course to Student ===\n";
    cout << "Student ID: ";
    cin >> studentId;

    int studentIndex = -1; // searching for the ID
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

    Student& student = students[studentIndex];

    if (student.courseCount >= MAX_COURSES) {
        cout << "\nCannot add more courses. Maximum capacity reached.\n";
        return;
    }

    Course course;
    cout << "Course Name: ";
    cin.ignore();
    getline(cin, course.name);
    cout << "Number of Units: ";
    cin >> course.units;

    do {
        cout << "Grade (0-20): ";
        cin >> course.grade;
    } while (!isValidGrade(course.grade));

    student.courses[student.courseCount++] = course;
    calculateGPA(student);

    cout << "\nCourse successfully added.\n";
}

void listStudents(const string& majorFilter = "") { //listing sturdents by major
    cout << "\n=== Student List ===\n";

    cout << setw(30) << "Full Name"
         << setw(15) << "Student ID"
         << setw(20) << "Major"
         << setw(10) << "GPA" << endl;
    cout << string(75, '-') << endl;

    for (int i = 0; i < studentCount; ++i) {
        if (!majorFilter.empty() && students[i].major != majorFilter) {
            continue;
        }

        cout << setw(30) << (students[i].firstName + " " + students[i].lastName)
             << setw(15) << students[i].studentId
             << setw(20) << students[i].major
             << setw(10) << fixed << setprecision(2) << students[i].gpa << endl;
    }
}


 int main()
 {
//defining int for chosing operation
     int choice;
// main menu of project
     while (true) {
         cout << "\n=== Student Management System ===\n";
         cout << "1. Add New Student\n";
         cout << "2. Add Course to Student\n";
         cout << "3. List All Students\n";
         cout << "4. List Students by Major\n";
         cout << "5. Generate Transcript\n";
         cout << "6. Exit\n";
         cout << "Enter your choice: ";
         cin >> choice;
}
 }
