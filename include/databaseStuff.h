#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "professor.h"
#include "student.h"
#include "course.h"
#include "sql/sqlite3.h"

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


int callbackFunction(void* data, int argc, char** argv, char** columnNames);
int getMajor(void* data, int argc, char** argv, char** columnNames);
int setMajorCourses(void* data, int argc, char** argv, char** columnNames);
int getGrades(void* data, int argc, char** argv, char** columnNames);
int getProfessorCourses(void* data, int argc, char** argv, char** columnNames);