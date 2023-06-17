#include "course.h"

Course::Course()
{
    
}

std::string Course::getName() const
{
    return m_courseName;
}

int Course::getID() const
{
    return m_ID;
}

std::vector<int> Course::getStudents() const
{
    return m_students;
}

std::vector<int> Course::getProfessors() const
{
    return m_professors;
}

StudentCourse::StudentCourse(const Course& course)
{
    m_courseName = course.getName();
    m_ID = course.getID();
    m_professors = course.getProfessors();
}

ProfessorCourse::ProfessorCourse(const Course& course)
{
    m_courseName = course.getName();
    m_ID = course.getID();
    m_students = course.getStudents();
}