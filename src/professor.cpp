#include "professor.h"

Professor::Professor()
    : User()
{
    
}

Professor::Professor(const std::string& name)
    : User(name)
{
    
}

void Professor::setCourses(const std::vector<Course*>& courses)
{
    m_courses = courses;
}

std::vector<Course*> Professor::getCourses() const
{
    return m_courses;
}

