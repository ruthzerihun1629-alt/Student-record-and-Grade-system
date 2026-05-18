#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "common.h"
#include <iostream>
#include <fstream>

using namespace std;

class FileHandler
{
private:

    const string studentFile = "students.txt";
    const string teacherFile = "teachers.txt";

    const string studentBackup = "students_backup.txt";
    const string teacherBackup = "teachers_backup.txt";

public:

    // ==================================================
    // 1. SAVE STUDENT DATA
    // ==================================================

    void saveStudentsToFile(Student students[], int count)
    {
        ofstream outFile(studentFile);

        if (!outFile)
        {
            cerr << "Error opening student file!" << endl;
            return;
        }

        outFile << count << endl;

        for (int i = 0; i < count; i++)
        {
            outFile << students[i].id << endl;
            outFile << students[i].name << endl;

            for (int j = 0; j < 6; j++)
            {
                outFile << students[i].marks[j] << " ";
            }

            outFile << endl;

            for (int j = 0; j < 6; j++)
            {
                outFile << students[i].subject[j] << endl;
            }

            for (int j = 0; j < 6; j++)
            {
                outFile << students[i].examDate[j] << endl;
            }

            outFile << students[i].grade << endl;
            outFile << students[i].attendance << endl;

            outFile << students[i].username << endl;
            outFile << students[i].password << endl;
        }

        outFile.close();

        cout << "Student data saved successfully." << endl;

        backupData();
    }

    // ==================================================
    // 2. LOAD STUDENT DATA
    // ==================================================

    void loadStudentsFromFile(Student students[], int &count)
    {
        ifstream inFile(studentFile);

        if (!inFile)
        {
            cout << "No student file found." << endl;
            count = 0;
            return;
        }

        inFile >> count;
        inFile.ignore();

        for (int i = 0; i < count; i++)
        {
            inFile >> students[i].id;
            inFile.ignore();

            getline(inFile, students[i].name);

            for (int j = 0; j < 6; j++)
            {
                inFile >> students[i].marks[j];
            }

            inFile.ignore();

            for (int j = 0; j < 6; j++)
            {
                getline(inFile, students[i].subject[j]);
            }

            for (int j = 0; j < 6; j++)
            {
                getline(inFile, students[i].examDate[j]);
            }

            inFile >> students[i].grade;
            inFile >> students[i].attendance;

            inFile.ignore();

            getline(inFile, students[i].username);
            getline(inFile, students[i].password);
        }

        inFile.close();

        cout << "Student data loaded successfully." << endl;
    }

    // ==================================================
    // 3. SAVE TEACHER DATA
    // ==================================================

    void saveTeachersToFile(Teacher teachers[], int count)
    {
        ofstream outFile(teacherFile);

        if (!outFile)
        {
            cerr << "Error opening teacher file!" << endl;
            return;
        }

        outFile << count << endl;

        for (int i = 0; i < count; i++)
        {
            outFile << teachers[i].username << endl;
            outFile << teachers[i].password << endl;
        }

        outFile.close();

        cout << "Teacher data saved successfully." << endl;

        backupData();
    }

    // ==================================================
    // 4. LOAD TEACHER DATA
    // ==================================================

    void loadTeachersFromFile(Teacher teachers[], int &count)
    {
        ifstream inFile(teacherFile);

        if (!inFile)
        {
            cout << "No teacher file found." << endl;
            count = 0;
            return;
        }

        inFile >> count;
        inFile.ignore();

        for (int i = 0; i < count; i++)
        {
            getline(inFile, teachers[i].username);
            getline(inFile, teachers[i].password);
        }

        inFile.close();

        cout << "Teacher data loaded successfully." << endl;
    }

    // ==================================================
    // 5. BACKUP SYSTEM
    // ==================================================

    void backupData()
    {
        // ---------- Student Backup ----------

        ifstream srcStudent(studentFile);
        ofstream dstStudent(studentBackup);

        if (srcStudent && dstStudent)
        {
            dstStudent << srcStudent.rdbuf();
        }

        srcStudent.close();
        dstStudent.close();

        // ---------- Teacher Backup ----------

        ifstream srcTeacher(teacherFile);
        ofstream dstTeacher(teacherBackup);

        if (srcTeacher && dstTeacher)
        {
            dstTeacher << srcTeacher.rdbuf();
        }

        srcTeacher.close();
        dstTeacher.close();

        cout << "Backup completed successfully." << endl;
    }

    // ==================================================
    // 6. RESTORE BACKUP
    // ==================================================

    void restoreBackup()
    {
        // ---------- Restore Students ----------

        ifstream backupStudent(studentBackup);
        ofstream restoreStudent(studentFile);

        if (backupStudent && restoreStudent)
        {
            restoreStudent << backupStudent.rdbuf();
        }

        backupStudent.close();
        restoreStudent.close();

        // ---------- Restore Teachers ----------

        ifstream backupTeacher(teacherBackup);
        ofstream restoreTeacher(teacherFile);

        if (backupTeacher && restoreTeacher)
        {
            restoreTeacher << backupTeacher.rdbuf();
        }

        backupTeacher.close();
        restoreTeacher.close();

        cout << "Backup restored successfully." << endl;
    }
};

#endif
