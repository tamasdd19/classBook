#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <sql/sqlite3.h>
#include <openssl/aes.h>
#include "professor.h"
#include "student.h"
#include "course.h"
#include "faculty.h"
#include "major.h"

struct LoginData
{
    std::string name, password;
    bool found = false;
    User* user = nullptr;
    Student* student = nullptr;
    Professor* professor = nullptr;
    bool isStudent = false;
    bool isAdmin = false;
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
int getAllFaculties(void* data, int argc, char** argv, char** columnNames);
// Encryption stuff
std::string encryptPassword(const std::string& password, const std::string& key);
std::string decryptPassword(const std::string& encrypted, const std::string& key);