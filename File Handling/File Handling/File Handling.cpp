#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Maximum number of students
const int MAX_STUDENTS = 100;

// Structure to hold student information
struct Student {
    int id;
    string name;
};

// Global array to hold student records
Student students[MAX_STUDENTS];
int numStudents = 0; // Current number of students

// Function prototypes
void insertStudent();
void deleteStudent();
void updateStudent();
void searchStudent();
void displayStudents();
void saveStudents();
void loadStudents();

int main() {
    loadStudents(); // Load existing student records from file

    int choice;
    do {
        cout << "\n===== Student Record Management =====" << endl;
        cout << "1. Insert a Student" << endl;
        cout << "2. Delete a Student" << endl;
        cout << "3. Update Student Name" << endl;
        cout << "4. Search for a Student" << endl;
        cout << "5. Display All Students" << endl;
        cout << "6. Save Student Records to File" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            insertStudent();
            break;
        case 2:
            deleteStudent();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            searchStudent();
            break;
        case 5:
            displayStudents();
            break;
        case 6:
            saveStudents();
            break;
        case 7:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 7." << endl;
            break;
        }
    } while (choice != 7);

    return 0;
}

// Function to insert a new student record
void insertStudent() {
    if (numStudents >= MAX_STUDENTS) {
        cout << "Maximum number of students reached. Cannot insert more." << endl;
        return;
    }

    int id;
    string name;
    cout << "Enter student ID: ";
    cin >> id;

    // Check if ID already exists
    for (int i = 0; i < numStudents; ++i) {
        if (students[i].id == id) {
            cout << "Student with ID " << id << " already exists. Please enter a different ID." << endl;
            return;
        }
    }

    cout << "Enter student name: ";
    cin.ignore(); // Ignore newline character left in the input buffer
    getline(cin, name);

    students[numStudents].id = id;
    students[numStudents].name = name;
    numStudents++;

    cout << "Student inserted successfully." << endl;
}

// Function to delete a student record by ID
void deleteStudent() {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < numStudents; ++i) {
        if (students[i].id == id) {
            // Shift remaining elements left
            for (int j = i; j < numStudents - 1; ++j) {
                students[j] = students[j + 1];
            }
            numStudents--;
            found = true;
            cout << "Student deleted successfully." << endl;
            break;
        }
    }

    if (!found) {
        cout << "Student with ID " << id << " not found." << endl;
    }
}

// Function to update a student's name by ID
void updateStudent() {
    int id;
    cout << "Enter student ID to update: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < numStudents; ++i) {
        if (students[i].id == id) {
            cout << "Enter new name: ";
            cin.ignore(); // Ignore newline character left in the input buffer
            getline(cin, students[i].name);
            found = true;
            cout << "Student updated successfully." << endl;
            break;
        }
    }

    if (!found) {
        cout << "Student with ID " << id << " not found." << endl;
    }
}

// Function to search for a student by ID
void searchStudent() {
    int id;
    cout << "Enter student ID to search: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < numStudents; ++i) {
        if (students[i].id == id) {
            cout << "Student found: ID = " << students[i].id << ", Name = " << students[i].name << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student with ID " << id << " not found." << endl;
    }
}

// Function to display all students
void displayStudents() {
    if (numStudents == 0) {
        cout << "No students to display." << endl;
        return;
    }

    cout << "Student Records:" << endl;
    cout << setw(5) << "ID" << setw(20) << "Name" << endl;
    for (int i = 0; i < numStudents; ++i) {
        cout << setw(5) << students[i].id << setw(20) << students[i].name << endl;
    }
}

// Function to save student records to file
void saveStudents() {
    ofstream outFile("students.txt");

    if (!outFile) {
        cerr << "Unable to open file students.txt" << endl;
        return;
    }

    for (int i = 0; i < numStudents; ++i) {
        outFile << students[i].id << "," << students[i].name << endl;
    }

    outFile.close();
    cout << "Student records saved to students.txt." << endl;
}

// Function to load student records from file
void loadStudents() {
    ifstream inFile("students.txt");
    numStudents = 0; // Reset number of students

    if (!inFile) {
        cerr << "Unable to open file students.txt" << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;

        getline(ss, token, ',');
        students[numStudents].id = stoi(token);

        getline(ss, students[numStudents].name);
        numStudents++;
    }

    inFile.close();
    cout << "Student records loaded from students.txt." << endl;
}
