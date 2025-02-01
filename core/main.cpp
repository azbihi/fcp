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
 bool isValidGrade(float grade) {
     return grade >= 0 && grade <= 20;
 }
 bool isUniqueId (const string& id) //check ID uniqueness 
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
 bool isUniqueId2 (const string& id ,int j) //check ID uniqueness 
 {
     for (int i = 0 ; i < studentCount ; i++)
     {   if ( i == j) {continue;}
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
bool isValidStudentId2 (const string& id , const int j) {
     return id.length() == 8 && all_of(id.begin(), id.end(), ::isdigit) && isUniqueId2(id, j);
     }
// this func work is to calculate gpa
void calculateGPA (Student& student)
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
    cin.ignore();  // Add this to clear buffer
    cout << "First Name: ";
    getline(cin, student.firstName);
    cout << "Last Name: ";
    getline(cin, student.lastName);
// cheking student id
    do {
        cout << "Student ID (8 digits): ";
        getline(cin, student.studentId);
    } while (!isValidStudentId(student.studentId));

    cout << "Major: ";
    getline(cin, student.major);

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
// function to add a transcript to each students data set
void printTranscript() {
    string studentId;
    cout << "\n=== Generate Transcript ===\n";
    cin.ignore();
    cout << "Student ID: ";
    getline(cin, studentId);

    int studentIndex = -1;
    for (int i = 0; i < studentCount; ++i) { //finding the student id
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

    cout << "\n" << string(50, '*') << endl;
    cout << "Academic Transcript" << endl;
    cout << string(50, '*') << endl;
    cout << "Full Name: " << student.firstName << " " << student.lastName << endl;
    cout << "Student ID: " << student.studentId << endl;
    cout << "Major: " << student.major << endl;
    cout << "Overall GPA: " << fixed << setprecision(2) << student.gpa << endl;
    cout << string(50, '-') << endl;

    cout << setw(30) << "Course Name"
         << setw(15) << "Units"
         << setw(10) << "Grade" << endl;
    cout << string(55, '-') << endl;

    for (int i = 0; i < student.courseCount; ++i) {
        cout << setw(30) << student.courses[i].name
             << setw(15) << student.courses[i].units
             << setw(10) << student.courses[i].grade << endl;
    }

    cout << string(50, '*') << endl;
}

void editStudent()
 {
     string studentId;
     cout << "\n=== Edit Student ===\n";
     cin.ignore();
     cout << "Student ID: ";
     getline(cin, studentId);

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

     Student& student = students[studentIndex];
     cout << "Student ID (" << student.studentId << "): ";
        do {
            getline(cin, student.studentId);
        } while (!isValidStudentId(student.studentId));
     cout << "First Name (" << student.firstName << "): ";
     getline(cin, student.firstName);
     cout << "Last Name (" << student.lastName << "): ";
     getline(cin, student.lastName);
     cout << "Major (" << student.major << "): ";
     getline(cin, student.major);

     cout << "\nStudent successfully updated.\n";
 }

 void deleteStudent()
{
    string studentId;
    cout << "\n=== Delete Student ===\n";
    cin.ignore();
    cout << "Student ID: ";
    getline(cin, studentId);

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

 int main()
 {
//defining int for chosing operation
     int choice;

     while (true) {
         cout << "\n=== Student Management System ===\n";
         cout << "1. Add New Student\n";
         cout << "2. Add Course to Student\n";
         cout << "3. List All Students\n";
         cout << "4. List all students by major\n";
         cout << "5. Generate Transcript\n";
         cout << "6. Edit student data\n";
         cout << "7. Delete student\n";
         cout << "8. Exit\n";
         cout << "Enter your choice: ";
         cin >> choice;
      
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                addCourseToStudent();
                break;
            case 3:
                listStudents();
                break;
            case 4: {
                string major;
                cin.ignore();
                cout << "Enter major to filter: ";
                getline(cin, major);
                listStudents(major);
                break;
            }
            case 5:
                printTranscript();
                break;
            case 6:
                editStudent();
                break;
            case 7: 
                deleteStudent();
                break;
            case 8:
                cout << "Program terminated.\n";
                return 0;
            default:
                cout << "Invalid option!\n";
        }
      
}
  return 0;
}
