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
         if (id == student[i].studentId)
         {
             return false ;
         }
     }
     return true;
 }
 //this function is checking length of string and being sure all of chars are digits
 bool isValidStudentId (const string& id) {
     return id.length() == 8 && all_of(id.begin(), id.end(), ::isdigit) && isUniqueId(&id);
// this func work is to calculate gpa
voig GPAclal (Student& student)
{
    float totalPoints = 0;
    int totalUnits = 0 ;

        for (int i = 0 ; i < student.courseCount; ++i )
        {
            totlalPoints += student.couses[i].grade * student.courses[i].units;
            totalUnits += student.course[i].units;
        }
        student.gpa = totalaPoints > 0 ? totalPoints / totalUnits : 0 ;
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
