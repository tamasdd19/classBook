#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "major.h"

class Faculty
{
public:
    Faculty(const std::string&);
    Faculty(const std::string&, const std::vector<Major*>&);
    Faculty(const std::vector<Major*>&);
    Faculty();
    void addMajor(Major&);
    void setName(const std::string&);
    void setMajors(const std::vector<Major*>&);
protected:
    std::string m_facultyName;
private:
    std::vector<Major*> m_majors;
};