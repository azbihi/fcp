#include <iostream>
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
