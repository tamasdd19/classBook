#pragma once

#include <vector>
#include <string>
#include "user.h"
#include "major.h"
#include "course.h"

class Student : public User
{
public:
    Student(const std::string& name, int majorId);
    // Student(const std::string& name);
    Student();
    // void setCourses(const std::vector<StudentCourse*>&);
    // void addCourse(StudentCourse&);
    // for the major stuff there are those setters
    int getMajorId() const;
    Major* getMajor() const;
    void setMajor(Major*);
private:
    std::vector<StudentCourse*> m_courses;
    int m_majorId;
    Major* m_major;
};