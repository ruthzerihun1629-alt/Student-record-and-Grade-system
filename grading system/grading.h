#ifndef GRADING_H
#define GRADING_H

#include "student.h"

float calculateTotal(vector<float> marks);

float calculateAverage(float total);

float calculateGPA(float average);

char calculateGrade(float average);

bool isPassed(float average);

#endif