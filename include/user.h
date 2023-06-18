#pragma once

#include <iostream>
#include <string>

class User
{
public:
    User(const std::string& name);
    User();
    // Getters
    std::string getName() const;
    std::string getPassword() const;
    int getID() const;
    // Setters
    void setName(const std::string&);
    void setPassword(const std::string&);
    void setId(int);
private:
    int m_ID;
    std::string m_name;
    std::string m_password;
};
