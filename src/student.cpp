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


// Student::Student(const std::string& name, const Major& major)
//     : User(name)
// {
//     this->setMajorName(major.getMajorName());
//     this->setMajorYear(major.getMajorYear());
// }

// void Student::addCourse(StudentCourse& course)
// {
//     m_courses.push_back(&course);
// }

// void Student::setCourses(const std::vector<StudentCourse*>& courses)
// {
//     m_courses = courses;
// }