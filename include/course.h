#pragma once

#include <iostream>
#include <string>
#include <vector>

class Course
{
public:
    Course();
    Course(int id, const std::string& name, int majorId);
    // Getters
    std::string getName() const;
    int getId() const;
    // Setters
    void setId(int);
    void setMajorId(int);
    void setName(const std::string&);
protected:
    int m_Id, m_majorId;
    std::string m_name;
};