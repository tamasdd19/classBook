#pragma once

#include <iostream>
#include <string>
#include <vector>

class Course
{
public:
    Course();
    Course(int, const std::string&, int);
    // Getters
    std::string getName() const;
    int getId() const;
    std::vector<int> getStudents() const;
    std::vector<int> getProfessors() const;
    // Setters
    void setId(int);
    void setMajorId(int);
    void setName(const std::string&);
protected:
    int m_Id, m_majorId;
    std::string m_name;
    std::vector<int> m_professors; // professors id
    std::vector<int> m_students;   // student    ids
};

class StudentCourse : public Course // student's side of the course, with the added grades and stuff
{
public:
    StudentCourse(const Course&);
 private:
    std::vector<int> m_grades;
};

class ProfessorCourse : public Course // professors side of the course, with the ability to add grades and stuff
{
public:
    ProfessorCourse(const Course&);
    void giveGrade(const int&);
    void printProf();
private:
};