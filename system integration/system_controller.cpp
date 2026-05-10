#include "system_controller.h"

#include "grading.h"
#include "search_sort.h"
#include "reports.h"
#include "validation.h"
#include "file_manager.h"

void mainMenu() {

    cout << "\n===== STUDENT RECORD SYSTEM =====\n";

    cout << "1. Add Student\n";
    cout << "2. Search Student\n";
    cout << "3. Calculate GPA\n";
    cout << "4. Display Reports\n";
    cout << "5. Save File\n";
    cout << "6. Exit\n";
}

bool isDuplicateID(vector<Student>& students, int id) {

    for(Student s : students) {

        if(s.id == id)
            return true;
    }

    return false;
}

void addStudent(vector<Student>& students) {

    Student s;

    cout << "Enter ID: ";
    cin >> s.id;

    if(isDuplicateID(students, s.id)) {

        cout << "Duplicate ID!\n";
        return;
    }

    cout << "Enter Name: ";
    cin >> s.name;

    students.push_back(s);

    cout << "Student Added Successfully!\n";
}

void runSystem() {

    vector<Student> students;

    int choice;

    do {

        mainMenu();

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                addStudent(students);
                break;

            case 2:
                cout << "Search Module\n";
                break;

            case 3:
                cout << "Grading Module\n";
                break;

            case 4:
                cout << "Reports Module\n";
                break;

            case 5:
                saveToFile(students);
                break;

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while(choice != 6);
}