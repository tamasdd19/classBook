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
private:
    std::vector<ProfessorCourse*> m_courses;
};