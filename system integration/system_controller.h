#ifndef SYSTEM_CONTROLLER_H
#define SYSTEM_CONTROLLER_H

#include "student.h"

void runSystem();

void mainMenu();

void addStudent(vector<Student>& students);

bool isDuplicateID(vector<Student>& students, int id);

#endif