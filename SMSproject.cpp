#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    string fatherName;
    string mobile;
    string dob;
    string address;
};

Student students[50];
int totalStudents = 0;

/* ---------- Utility Functions ---------- */

bool rollExists(int roll) {
    for (int i = 0; i < totalStudents; i++) {
        if (students[i].rollNo == roll)
            return true;
    }
    return false;
}

/* ---------- File Handling ---------- */

void saveToFile() {
    ofstream outFile("student_records.txt");
    if (!outFile) {
        cout << "Error saving data!\n";
        return;
    }

    for (int i = 0; i < totalStudents; i++) {
        outFile << students[i].rollNo << "\n"
                << students[i].name << "\n"
                << students[i].fatherName << "\n"
                << students[i].mobile << "\n"
                << students[i].dob << "\n"
                << students[i].address << "\n";
    }
    outFile.close();
}

void loadFromFile() {
    ifstream inFile("student_records.txt");
    if (!inFile)
        return;

    totalStudents = 0;
    while (inFile >> students[totalStudents].rollNo) {
        inFile.ignore();
        getline(inFile, students[totalStudents].name);
        getline(inFile, students[totalStudents].fatherName);
        getline(inFile, students[totalStudents].mobile);
        getline(inFile, students[totalStudents].dob);
        getline(inFile, students[totalStudents].address);
        totalStudents++;
    }
    inFile.close();
}

/* ---------- CRUD Operations ---------- */

void addStudent() {
    if (totalStudents >= 50) {
        cout << "Student limit reached!\n";
        return;
    }

    int roll;
    cout << "Enter Roll No: ";
    cin >> roll;

    if (rollExists(roll)) {
        cout << "Roll number already exists!\n";
        return;
    }

    students[totalStudents].rollNo = roll;
    cin.ignore();

    cout << "Name: ";
    getline(cin, students[totalStudents].name);

    cout << "Father's Name: ";
    getline(cin, students[totalStudents].fatherName);

    cout << "Mobile (10 digits): ";
    getline(cin, students[totalStudents].mobile);

    cout << "Date of Birth (DD/MM/YYYY): ";
    getline(cin, students[totalStudents].dob);

    cout << "Address: ";
    getline(cin, students[totalStudents].address);

    totalStudents++;
    saveToFile();
    cout << "Student added successfully!\n";
}

void displayStudent() {
    int roll;
    cout << "Enter Roll No: ";
    cin >> roll;

    for (int i = 0; i < totalStudents; i++) {
        if (students[i].rollNo == roll) {
            cout << "\nStudent Details\n";
            cout << "Roll No: " << students[i].rollNo << "\n";
            cout << "Name: " << students[i].name << "\n";
            cout << "Father: " << students[i].fatherName << "\n";
            cout << "Mobile: " << students[i].mobile << "\n";
            cout << "DOB: " << students[i].dob << "\n";
            cout << "Address: " << students[i].address << "\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

void displayAllStudents() {
    if (totalStudents == 0) {
        cout << "No records found.\n";
        return;
    }

    cout << "\n---- Student List ----\n";
    for (int i = 0; i < totalStudents; i++) {
        cout << "Roll: " << students[i].rollNo
             << " | Name: " << students[i].name
             << " | Mobile: " << students[i].mobile << "\n";
    }
}

void editStudent() {
    int roll;
    cout << "Enter Roll No to edit: ";
    cin >> roll;
    cin.ignore();

    for (int i = 0; i < totalStudents; i++) {
        if (students[i].rollNo == roll) {
            cout << "New Name: ";
            getline(cin, students[i].name);

            cout << "New Father's Name: ";
            getline(cin, students[i].fatherName);

            cout << "New Mobile: ";
            getline(cin, students[i].mobile);

            cout << "New DOB: ";
            getline(cin, students[i].dob);

            cout << "New Address: ";
            getline(cin, students[i].address);

            saveToFile();
            cout << "Student updated successfully!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

void deleteStudent() {
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    for (int i = 0; i < totalStudents; i++) {
        if (students[i].rollNo == roll) {
            for (int j = i; j < totalStudents - 1; j++) {
                students[j] = students[j + 1];
            }
            totalStudents--;
            saveToFile();
            cout << "Student deleted successfully!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

/* ---------- Main ---------- */

int main() {
    loadFromFile();
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student\n";
        cout << "3. Display All Students\n";
        cout << "4. Edit Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudent(); break;
            case 3: displayAllStudents(); break;
            case 4: editStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
