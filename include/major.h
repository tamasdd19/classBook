#pragma once

//#include "faculty.h"
#include "course.h"
#include <vector>

class Major
{
public:
    Major(const std::string&);
    Major(int, const std::string&, int);
    Major(const std::string&, int, const std::vector<Course*>&);
    Major(int majorId, const std::string& majorName);
    Major();
    // Getters
    std::string getName() const;
    std::vector<Course*> getCourses() const;
    int getYear() const;
    int getId() const;
    int getFacultyId() const;
    // Setters
    void setName(const std::string&);
    void setYear(int);
    void setCourses(const std::vector<Course*>&);
    void setId(int);
    void setFacultyId(int);
private:
    std::vector<Course*> m_courses;
    std::string m_majorName;
    int m_majorId = -1, m_majorYear = -1, m_facultyId = -1;
};