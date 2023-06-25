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
    Student();
    // Getters
    int getMajorId() const;
    Major* getMajor() const;
    // Setters
    void setMajor(Major*);
private:
    int m_majorId;
    Major* m_major;
};