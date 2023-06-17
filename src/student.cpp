#include "student.h"

Student::Student()
    : User()
{

}

Student::Student(const std::string& name)
    : User(name)
{
    
}

Student::Student(const std::string& name, const Major& major)
    : User(name)
{
    this->setMajorName(major.getMajorName());
    this->setMajorYear(major.getMajorYear());
}

void Student::addCourse(StudentCourse& course)
{
    m_courses.push_back(&course);
}

void Student::setCourses(const std::vector<StudentCourse*>& courses)
{
    m_courses = courses;
}