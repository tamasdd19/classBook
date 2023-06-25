#include "student.h"

Student::Student()
    : User()
{

}

Student::Student(const std::string& name, int majorId)
    : User(name), m_majorId(majorId)
{
    
}

int Student::getMajorId() const
{
    return m_majorId;
}

void Student::setMajor(Major* major)
{
    m_major = major;
}

Major* Student::getMajor() const
{
    return m_major;
}