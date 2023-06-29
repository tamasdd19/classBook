#pragma once

#include "course.h"
#include "user.h"
#include <string>
#include <vector>

class Professor : public User
{
public:
    Professor(const std::string& name);
    Professor();
    // Getters
    std::vector<Course*> getCourses() const;
    // Setters
    void setCourses(const std::vector<Course*>& courses);
private:
    std::vector<Course*> m_courses; // Every course has an Id_professor that shows which professor is teaching that course
};