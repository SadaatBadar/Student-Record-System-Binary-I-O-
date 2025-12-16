#include <iostream>
#include <fstream>
#include <cstring> // Required for string manipulation if needed
using namespace std;

// UPGRADE 1: Fixed-size arrays for Binary Compatibility
struct Student {
    int rollNo;
    char name[50];
    char fatherName[50];
    char mobile[15];
    char dob[15];
    char address[100];
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

/* ---------- File Handling (BINARY UPGRADE) ---------- */

void saveToFile() {
    // Open in Binary Mode
    ofstream outFile("student_records.dat", ios::binary); 
    if (!outFile) {
        cout << "Error saving data!\n";
        return;
    }

    // Write the entire array from memory to disk in one go (or loop)
    // Looping ensures we only write valid students
    for (int i = 0; i < totalStudents; i++) {
        outFile.write(reinterpret_cast<char*>(&students[i]), sizeof(Student));
    }
    outFile.close();
}

void loadFromFile() {
    ifstream inFile("student_records.dat", ios::binary);
    if (!inFile)
        return;

    totalStudents = 0;
    Student temp;
    
    // Read raw bytes directly into the temp struct
    while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(Student))) {
        if(totalStudents < 50) {
            students[totalStudents] = temp;
            totalStudents++;
        }
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
    cin.ignore(); // Clear buffer

    // UPGRADE 3: Safe Input for Char Arrays
    cout << "Name: ";
    cin.getline(students[totalStudents].name, 50);

    cout << "Father's Name: ";
    cin.getline(students[totalStudents].fatherName, 50);

    cout << "Mobile (10 digits): ";
    cin.getline(students[totalStudents].mobile, 15);

    cout << "Date of Birth (DD/MM/YYYY): ";
    cin.getline(students[totalStudents].dob, 15);

    cout << "Address: ";
    cin.getline(students[totalStudents].address, 100);

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
            // Using cin.getline for safety here too
            cout << "New Name: ";
            cin.getline(students[i].name, 50);

            cout << "New Father's Name: ";
            cin.getline(students[i].fatherName, 50);

            cout << "New Mobile: ";
            cin.getline(students[i].mobile, 15);

            cout << "New DOB: ";
            cin.getline(students[i].dob, 15);

            cout << "New Address: ";
            cin.getline(students[i].address, 100);

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
    loadFromFile(); // Auto-load binary data on start
    int choice;

    do {
        cout << "\n===== High-Performance Student System =====\n";
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
