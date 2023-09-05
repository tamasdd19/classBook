#include "faculty.h"

Faculty::Faculty()
{

}

Faculty::Faculty(const std::string& name)
    : m_facultyName(name)
{

}

Faculty::Faculty(int id, const std::string& name)
    : m_ID(id), m_facultyName(name)
{
    
}

Faculty::Faculty(const std::string& name, const std::vector<Major*>& majors)
    : m_facultyName(name), m_majors(majors)
{
    // m_majors = majors;  /// not sure wether or not this will work, I shall see in the future
}

Faculty::Faculty(const std::vector<Major*>& majors)
    : m_majors(majors)
{

}

void Faculty::setName(const std::string& name)
{
    m_facultyName = name;
}

void Faculty::addMajor(Major& major)
{
    m_majors.push_back(&major);
}

void Faculty::setMajors(const std::vector<Major*>& majors)
{
    m_majors = majors;
}

void Faculty::setId(int id)
{
    m_ID = id;
}

int Faculty::getId() const
{
    return m_ID;
}

std::string Faculty::getName() const
{
    return m_facultyName;
}