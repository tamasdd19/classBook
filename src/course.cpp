#include "course.h"

Course::Course()
{
    
}

Course::Course(int id, const std::string& name, int majorId)
    : m_Id(id), m_name(name), m_majorId(majorId)
{

}

//Getters

std::string Course::getName() const
{
    return m_name;
}

int Course::getId() const
{
    return m_Id;
}

int Course::getMajorId() const
{
    return m_majorId;
}

//Setters
void Course::setId(int id)
{
    m_Id = id;
}
void Course::setMajorId(int id)
{
    m_majorId = id;
}
void Course::setName(const std::string& name)
{
    m_name = name;
}