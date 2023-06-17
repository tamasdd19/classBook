#include "major.h"

Major::Major()
{

}

Major::Major(const std::string& name)
    : m_majorName(name)
{

}
Major::Major(const std::string& name, int year)
    : m_majorName(name), m_majorYear(year)
{

}

Major::Major(const std::string& name, int year, const std::vector<Course*>& courses)
    : m_majorName(name), m_majorYear(year), m_courses(courses)
{

}

// Getters
std::string Major::getMajorName() const
{
    return m_majorName;
}

int Major::getMajorYear() const
{
    return m_majorYear;
}

// Setters
void Major::setMajorName(const std::string& name)
{
    m_majorName = name;
}

void Major::setMajorYear(int year)
{
    m_majorYear = year;
}

void Major::setMajorCourses(const std::vector<Course*>& courses)
{
    m_courses = courses;
}