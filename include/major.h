#pragma once

//#include "faculty.h"
#include "course.h"
#include <vector>

class Major
{
public:
    Major(const std::string&);
    Major(const std::string&, int);
    Major(const std::string&, int, const std::vector<Course*>&);
    Major();
    // Getters
    std::string getMajorName() const;
    int getMajorYear() const;
    // Setters
    void setMajorName(const std::string&);
    void setMajorYear(int);
    void setMajorCourses(const std::vector<Course*>&);
private:
    std::vector<Course*> m_courses;
    std::string m_majorName;
    int m_majorYear;
};