#include "major.h"

Major::Major()
{

}

Major::Major(const std::string& name)
    : m_majorName(name)
{

}
Major::Major(int id, const std::string& name, int year)
    : m_majorId(id), m_majorName(name), m_majorYear(year)
{

}

Major::Major(const std::string& name, int year, const std::vector<Course*>& courses)
    : m_majorName(name), m_majorYear(year), m_courses(courses)
{

}

// Getters
std::string Major::getName() const
{
    return m_majorName;
}

int Major::getYear() const
{
    return m_majorYear;
}

std::vector<Course*> Major::getCourses() const
{
    return m_courses;
}

// Setters
void Major::setName(const std::string& name)
{
    m_majorName = name;
}

void Major::setYear(int year)
{
    m_majorYear = year;
}

void Major::setCourses(const std::vector<Course*>& courses)
{
    m_courses = courses;
}
int Major::getId() const
{
    return m_majorId;
}

int Major::getFacultyId() const
{
    return m_facultyId;
}

void Major::setId(int id)
{
    m_majorId = id;
}
void Major::setFacultyId(int id)
{
    m_facultyId = id;
}