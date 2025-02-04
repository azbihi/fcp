#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// Constants
const int MAX_STUDENTS = 100;
const int MAX_COURSES = 10;

// Structs
struct Course {
    string name;
    int units;
    float grade;
};

struct Student {
    string firstName;
    string lastName;
    string studentId;
    string major;
    Course courses[MAX_COURSES];
    int courseCount;
    float gpa;
};

// Global Variables
Student students[MAX_STUDENTS];
int studentCount = 0;

// Helper Functions
bool isValidGrade(float grade) {
    return grade >= 0 && grade <= 20;
}

bool isUniqueId(const string& id) {
    for (int i = 0; i < studentCount; i++) {
        if (id == students[i].studentId) {
            return false;
        }
    }
    return true;
}

bool isUniqueId2(const string& id, int j) { //Handling edition in student data
    for (int i = 0; i < studentCount; i++) {
        if (i == j) {
            continue;
        }
        if (id == students[i].studentId) {
            return false;
        }
    }
    return true;
}

bool isValidStudentId(const string& id) {
    return id.length() == 8 && all_of(id.begin(), id.end(), ::isdigit) && isUniqueId(id);
}

bool isValidStudentId2(const string& id, const int j) {
    return id.length() == 8 && all_of(id.begin(), id.end(), ::isdigit) && isUniqueId2(id, j);
}

bool allAreDigits(const string& str) { // handling non-digit inputs
    return all_of(str.begin(), str.end(), ::isdigit);
}

void calculateGPA(Student& student) {
    float totalPoints = 0;
    int totalUnits = 0;

    for (int i = 0; i < student.courseCount; ++i) {
        totalPoints += (student.courses[i].grade) * (student.courses[i].units);
        totalUnits += student.courses[i].units;
    }
    student.gpa = totalPoints > 0 ? totalPoints / totalUnits : 0;
}

// Core Functions
void addStudent() { 
    if (studentCount >= MAX_STUDENTS) {
        cout << "\nCannot add more students. Maximum capacity reached.\n";
        return;
    }

    Student student;
    cout << "\n=== New Student Registration ===\n";
    
    do {
        cout << "First Name: ";
        getline(cin, student.firstName);
    } while (student.firstName.empty());

    do {
        cout << "Last Name: ";
        getline(cin, student.lastName);
    } while (student.lastName.empty());

    do {
        cout << "Student ID (8 digits): ";
        cin >> student.studentId;
    } while (!isValidStudentId(student.studentId));
    cin.ignore();

    do {
        cout << "Major: ";
        getline(cin, student.major);
    } while (student.major.empty());

    student.courseCount = 0;
    student.gpa = 0.0;

    students[studentCount++] = student;
    cout << "\nStudent successfully registered.\n";
}

void addCourseToStudent() {
    string studentId;
    cout << "\n=== Add Course to Student ===\n";
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
        cin.ignore();
        return;
    }

    Student& student = students[studentIndex];

    if (student.courseCount >= MAX_COURSES) {
        cout << "\nCannot add more courses. Maximum capacity reached.\n";
        cin.ignore();
        return;
    }

    Course course;
    cout << "Course Name: ";
    cin.ignore();
    getline(cin, course.name);
    
    string input;
    do {
    jump:
        cout << "Number of Units (1-4): ";
        getline(cin, input);
        if (!allAreDigits(input)) {
            cout << "Please enter a valid number\n";
            goto jump;
        }
        course.units = stoi(input);
    } while (course.units < 1 || course.units > 4);

    do {
    jump1:
        cout << "Grade (0-20): ";
        getline(cin, input);
        if (!allAreDigits(input)) {
            cout << "Please enter a valid number\n";
            goto jump1;
        }
        course.grade = stof(input);
    } while (!isValidGrade(course.grade));

    student.courses[student.courseCount++] = course;
    calculateGPA(student);

    cout << "\nCourse successfully added.\n";
}

void editCourse() {
    string studentId;
    cout << "\n=== Edit Course ===\n";
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
        cin.ignore();
        return;
    }

    Student& student = students[studentIndex];
    int z = 0;
    for (z; z < student.courseCount; z++) {
        cout << z + 1 << ". " << student.courses[z].name << endl;
    }
    if (z == 0) {
        cout << "There isn't course to edit " << endl
             << string(50, '*') << endl;
        cin.ignore();
        return;
    } else {
    jump2:
        cout << "Course num : ";
        string choose;
        cin.ignore();
        getline(cin, choose);
        if (!allAreDigits(choose)) {
            cout << "Please enter a valid number\n";
            goto jump2;
        }
        int courseIndex = stoi(choose) - 1;
        if (courseIndex < 0 || courseIndex >= student.courseCount) {
            cout << "Invalid course number!\n";
            return;
        }

        Course& course = student.courses[courseIndex];
        cout << "Course Name (" << course.name << "): ";
        getline(cin, course.name);

        string input;
        do {
        jump3:
            cout << "Number of Units (1-4) (" << course.units << "): ";
            getline(cin, input);
            if (!allAreDigits(input)) {
                cout << "Please enter a valid number\n";
                goto jump3;
            }
            if (!input.empty()) {
                course.units = stoi(input);
            }
        } while (course.units < 1 || course.units > 4);

        do {
        jump4:
            cout << "Grade (0-20) (" << course.grade << "): ";
            getline(cin, input);
            if (!allAreDigits(input)) {
                cout << "Please enter a valid number\n";
                goto jump4;
            }
            if (!input.empty()) {
                course.grade = stof(input);
            }
        } while (!isValidGrade(course.grade));

        calculateGPA(student);
        cout << "\nCourse successfully updated.\n";
    }
}

void listStudents(const string& majorFilter = "") {
    cout << "\n=== Student List ===\n";

    int indices[MAX_STUDENTS];
    int count = 0;
    
    for (int i = 0; i < studentCount; ++i) {
        if (majorFilter.empty() || students[i].major == majorFilter) {
            indices[count++] = i;
        }
    }

    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (students[indices[j]].gpa < students[indices[j + 1]].gpa) {
                swap(indices[j], indices[j + 1]);
            }
        }
    }

    cout << setw(30) << "Full Name"
         << setw(15) << "Student ID"
         << setw(20) << "Major"
         << setw(10) << "GPA" << endl;
    cout << string(75, '-') << endl;

    for (int i = 0; i < count; ++i) {
        int idx = indices[i];
        cout << setw(30) << (students[idx].firstName + " " + students[idx].lastName)
             << setw(15) << students[idx].studentId
             << setw(20) << students[idx].major
             << setw(10) << fixed << setprecision(2) << students[idx].gpa << endl;
    }
}

void printTranscript() {
    string studentId;
    cout << "\n=== Generate Transcript ===\n"
         << "Student ID: ";
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
        cin.ignore();
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
    cin.ignore();
}

void editStudent() {
    string studentId;
    cout << "\n=== Edit Student ===\n";
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
        cin.ignore();
        return;
    }

    Student& student = students[studentIndex];
    string draftId, firstName, lastName, major;

    do {
        cout << "Student ID (8 digits) (" << student.studentId << "): ";
        cin.ignore();
        getline(cin, draftId);
        if (draftId.empty()) {
            draftId = student.studentId;
            break;
        }
    } while (!isValidStudentId2(draftId, studentIndex));

    cout << "First Name (" << student.firstName << ") :";
    getline(cin, firstName);
    if (!firstName.empty()) {
        student.firstName = firstName;
    }
    cout << "Last Name (" << student.lastName << ") : ";
    getline(cin, lastName);
    if (!lastName.empty()) {
        student.lastName = lastName;
    }
    cout << "Major (" << student.major << ") : ";
    getline(cin, major);
    if (!major.empty()) {
        student.major = major;
    }

    if (!draftId.empty()) {
        student.studentId = draftId;
    }

    cout << "\nStudent successfully updated.\n";
}

void deleteStudent() {
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
        cin.ignore();
        return;
    }

    for (int i = studentIndex; i < studentCount - 1; ++i) {
        students[i] = students[i + 1];
    }

    studentCount--;
    cout << "\nStudent successfully deleted.\n";
    cin.ignore();
}

int main() {
    string choice;

    while (true) {
        cout << "\n=== Student Management System ===\n";
        cout << "1. Add New Student\n";
        cout << "2. Add Course to Student\n";
        cout << "3. List All Students\n";
        cout << "4. List all students by major\n";
        cout << "5. Generate Transcript\n";
        cout << "6. Edit student data\n";
        cout << "7. Edit course\n";
        cout << "8. Delete student\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        getline(cin, choice);

        if (choice == "1") {
            addStudent();
        } else if (choice == "2") {
            addCourseToStudent();
        } else if (choice == "3") {
            listStudents();
        } else if (choice == "4") {
            string major;
            cout << "Enter major to filter: ";
            getline(cin, major);
            listStudents(major);
        } else if (choice == "5") {
            printTranscript();
        } else if (choice == "6") {
            editStudent();
        } else if (choice == "7") {
            editCourse();
        } else if (choice == "8") {
            deleteStudent();
        } else if (choice == "9") {
            cout << "Program terminated.\n";
            return 0;
        } else {
            cout << "Invalid option!\n";
        }
    }
    return 0;
}
