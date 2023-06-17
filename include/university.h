#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "faculty.h"

class University
{
public:
    University();
private:
    std::string m_name;
    std::vector<Faculty*> faculties;
};