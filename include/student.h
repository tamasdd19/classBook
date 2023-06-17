#pragma once

#include <vector>
#include <string>
#include "user.h"
#include "major.h"
#include "course.h"

class Student : public User, public Major
{
public:
    Student(const std::string& name, const Major&);
    Student(const std::string& name);
    Student();
    void setCourses(const std::vector<StudentCourse*>&);
    void addCourse(StudentCourse&);
    // for the major stuff there are those setters
private:
    std::vector<StudentCourse*> m_courses;
};