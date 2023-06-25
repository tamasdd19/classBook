#include "course.h"

Course::Course()
{
    
}

Course::Course(int id, const std::string& name, int majorId)
    : m_Id(id), m_name(name), m_majorId(majorId)
{

}

std::string Course::getName() const
{
    return m_name;
}

int Course::getId() const
{
    return m_Id;
}


// StudentCourse::StudentCourse(const Course& course)
// {
//     m_name = course.getName();
//     m_ID = course.getID();
//     m_professors = course.getProfessors();
// }

// ProfessorCourse::ProfessorCourse(const Course& course)
// {
//     m_name = course.getName();
//     m_ID = course.getID();
//     m_students = course.getStudents();
// }