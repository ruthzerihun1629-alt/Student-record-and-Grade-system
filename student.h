#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>

using namespace std;

struct Student {

    int id;
    string name;

    vector<float> marks;

    float total;
    float average;
    float gpa;

    char grade;

    int attendance;

    bool passed;
};

#endif