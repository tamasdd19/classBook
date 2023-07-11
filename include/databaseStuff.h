#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <sql/sqlite3.h>
#include "professor.h"
#include "student.h"
#include "course.h"

struct MyData
{
    std::string name, password;
    bool gasit = false;
    User* user = nullptr;
    bool student = false;
};

struct MyData2
{
    std::vector<Course*> courses;
    int id;
};

struct MyData3
{
    bool check = false;
    float grade = 0.0f;
};


int callbackFunction(void* data, int argc, char** argv, char** columnNames);
int getMajor(void* data, int argc, char** argv, char** columnNames);
int setMajorCourses(void* data, int argc, char** argv, char** columnNames);
int getGrades(void* data, int argc, char** argv, char** columnNames);
int getProfessorCourses(void* data, int argc, char** argv, char** columnNames);
int getStudents(void* data, int argc, char** argv, char** columnNames);
int checkIfGradeExists(void* data, int argc, char** argv, char** columnNames);