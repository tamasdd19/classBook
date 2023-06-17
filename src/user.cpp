#include "user.h"

int User::userNumbers = 0;

User::User()
{
    m_ID = userNumbers;
    userNumbers++;
}

User::User(const std::string& name)
    : User()
{
    m_name = name;
}

// Getters
std::string User::getName() const
{
    return m_name;
}

std::string User::getPassword() const
{
    return m_password;
}

int User::getID() const
{
    return m_ID;
}

//Setters
void User::setName(const std::string& name)
{
    m_name = name;
}

void User::setPassword(const std::string& password)
{
    m_password = password;
}