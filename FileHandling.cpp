#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "common.h"
#include <iostream>
#include <fstream>

using namespace std;

// ==================================================
// SAFE BINARY STRUCTS (IMPORTANT FIX)
// ==================================================

struct StudentBinary
{
    int id;
    char name[50];
    char department[30];
    float marks[MAX_SUBJECTS];
    char username[30];
    char password[30];
    char grade;
    float attendance;
};

struct TeacherBinary
{
    char username[30];
    char password[30];
    char department[30];
};

class FileHandler
{
private:

    // TEXT FILES
    const string studentFile = "students.txt";
    const string teacherFile = "teachers.txt";

    const string studentBackup = "students_backup.txt";
    const string teacherBackup = "teachers_backup.txt";

    // BINARY FILES
    const string studentBinaryFile = "students.dat";
    const string teacherBinaryFile = "teachers.dat";

public:

    // ==================================================
    // TEXT SAVE STUDENTS
    // ==================================================

    void saveStudentsText()
    {
        ofstream out(studentFile);
        out << students.size() << endl;

        for (auto &s : students)
        {
            out << s.id << endl;
            out << s.name << endl;
            out << s.department << endl;

            for (int i = 0; i < MAX_SUBJECTS; i++)
                out << s.marks[i] << " ";
            out << endl;

            for (int i = 0; i < MAX_SUBJECTS; i++)
                out << s.subjects[i] << endl;

            for (int i = 0; i < MAX_SUBJECTS; i++)
                out << s.examDate[i] << endl;

            out << s.grade << endl;
            out << s.attendance << endl;

            out << s.username << endl;
            out << s.password << endl;
        }

        out.close();
        backupData();
    }

    // ==================================================
    // TEXT LOAD STUDENTS
    // ==================================================

    void loadStudentsText()
    {
        ifstream in(studentFile);

        if (!in) return;

        int count;
        in >> count;
        in.ignore();

        students.clear();

        for (int i = 0; i < count; i++)
        {
            Student s;

            in >> s.id;
            in.ignore();

            getline(in, s.name);
            getline(in, s.department);

            for (int j = 0; j < MAX_SUBJECTS; j++)
                in >> s.marks[j];

            in.ignore();

            for (int j = 0; j < MAX_SUBJECTS; j++)
                getline(in, s.subjects[j]);

            for (int j = 0; j < MAX_SUBJECTS; j++)
                getline(in, s.examDate[j]);

            in >> s.grade;
            in >> s.attendance;
            in.ignore();

            getline(in, s.username);
            getline(in, s.password);

            students.push_back(s);
        }

        in.close();
    }

    // ==================================================
    // TEXT DELETE STUDENT
    // ==================================================

    void deleteStudentText(int id)
    {
        for (auto it = students.begin(); it != students.end(); ++it)
        {
            if (it->id == id)
            {
                students.erase(it);
                saveStudentsText();
                return;
            }
        }
    }

    // ==================================================
    // TEXT SAVE TEACHERS
    // ==================================================

    void saveTeachersText()
    {
        ofstream out(teacherFile);
        out << teachers.size() << endl;

        for (auto &t : teachers)
        {
            out << t.username << endl;
            out << t.password << endl;
            out << t.department << endl;
        }

        out.close();
        backupData();
    }

    // ==================================================
    // TEXT LOAD TEACHERS
    // ==================================================

    void loadTeachersText()
    {
        ifstream in(teacherFile);

        if (!in) return;

        int count;
        in >> count;
        in.ignore();

        teachers.clear();

        for (int i = 0; i < count; i++)
        {
            Teacher t;

            getline(in, t.username);
            getline(in, t.password);
            getline(in, t.department);

            teachers.push_back(t);
        }

        in.close();
    }

    // ==================================================
    // TEXT DELETE TEACHER
    // ==================================================

    void deleteTeacherText(string username)
    {
        for (auto it = teachers.begin(); it != teachers.end(); ++it)
        {
            if (it->username == username)
            {
                teachers.erase(it);
                saveTeachersText();
                return;
            }
        }
    }

    // ==================================================
    // ================= BINARY SECTION =================
    // ==================================================

    // CONVERT STUDENT → BINARY STRUCT
    StudentBinary toBinary(const Student &s)
    {
        StudentBinary b;

        b.id = s.id;
        b.grade = s.grade;
        b.attendance = s.attendance;

        strncpy(b.name, s.name.c_str(), sizeof(b.name));
        strncpy(b.department, s.department.c_str(), sizeof(b.department));
        strncpy(b.username, s.username.c_str(), sizeof(b.username));
        strncpy(b.password, s.password.c_str(), sizeof(b.password));

        for (int i = 0; i < MAX_SUBJECTS; i++)
            b.marks[i] = s.marks[i];

        return b;
    }

    // ==================================================
    // BINARY SAVE STUDENTS
    // ==================================================

    void saveStudentsBinary()
    {
        ofstream out(studentBinaryFile, ios::binary);

        for (auto &s : students)
        {
            StudentBinary b = toBinary(s);
            out.write((char*)&b, sizeof(b));
        }

        out.close();
    }

    // ==================================================
    // BINARY LOAD STUDENTS
    // ==================================================

    void loadStudentsBinary()
    {
        ifstream in(studentBinaryFile, ios::binary);

        if (!in) return;

        students.clear();

        StudentBinary b;

        while (in.read((char*)&b, sizeof(b)))
        {
            Student s;

            s.id = b.id;
            s.grade = b.grade;
            s.attendance = b.attendance;

            s.name = b.name;
            s.department = b.department;
            s.username = b.username;
            s.password = b.password;

            for (int i = 0; i < MAX_SUBJECTS; i++)
                s.marks[i] = b.marks[i];

            students.push_back(s);
        }

        in.close();
    }

    // ==================================================
    // BINARY DELETE STUDENT
    // ==================================================

    void deleteStudentBinary(int id)
    {
        ifstream in(studentBinaryFile, ios::binary);

        vector<StudentBinary> temp;
        StudentBinary b;

        while (in.read((char*)&b, sizeof(b)))
        {
            if (b.id != id)
                temp.push_back(b);
        }

        in.close();

        ofstream out(studentBinaryFile, ios::binary | ios::trunc);

        for (auto &x : temp)
            out.write((char*)&x, sizeof(x));

        out.close();
    }

    // ==================================================
    // BACKUP (TEXT ONLY)
    // ==================================================

    void backupData()
    {
        ifstream s(studentFile);
        ofstream sb(studentBackup);

        if (s && sb)
            sb << s.rdbuf();

        ifstream t(teacherFile);
        ofstream tb(teacherBackup);

        if (t && tb)
            tb << t.rdbuf();
    }

    // ==================================================
    // RESTORE BACKUP
    // ==================================================

    void restoreBackup()
    {
        ifstream sb(studentBackup);
        ofstream s(studentFile);

        if (sb && s)
            s << sb.rdbuf();

        ifstream tb(teacherBackup);
        ofstream t(teacherFile);

        if (tb && t)
            t << tb.rdbuf();
    }
};

#endif
