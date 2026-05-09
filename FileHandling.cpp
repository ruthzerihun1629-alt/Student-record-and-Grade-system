#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// This structure must be consistent across all group members
struct Student {
    int id;
    char name[50]; // Use char array for binary safety
    float marks[5];
    float gpa;
};

class FileHandler {
private:
    const char* fileName = "students.dat";
    const char* backupName = "students_backup.dat";

public:
    // 1. Save student records to file
    void saveToFile(Student students[], int count) {
        ofstream outFile(fileName, ios::binary | ios::out | ios::trunc);

        if (!outFile) {
            cerr << "Error: Could not open file for writing!" << endl;
            return;
        }

        // Write the entire array of records at once
        outFile.write(reinterpret_cast<char*>(students), sizeof(Student) * count);

        outFile.close();
        cout << "Data saved successfully to " << fileName << endl;
        autoBackup();
    }

    // 2. Load student records from file
    // Returns the number of students loaded
    int loadFromFile(Student students[], int maxCapacity) {
        ifstream inFile(fileName, ios::binary | ios::in);

        if (!inFile) {
            cout << "No existing data file found." << endl;
            return 0;
        }

        int count = 0;
        // Read records one by one until end of file or max capacity is reached
        while (count < maxCapacity && inFile.read(reinterpret_cast<char*>(&students[count]), sizeof(Student))) {
            count++;
        }

        inFile.close();
        return count;
    }

    // 3. Backup student data automatically
    void autoBackup() {
        ifstream src(fileName, ios::binary);
        ofstream dst(backupName, ios::binary | ios::trunc);

        if (src && dst) {
            dst << src.rdbuf(); // Use rdbuf() for an efficient file copy
            src.close();
            dst.close();
        }
    }
};

