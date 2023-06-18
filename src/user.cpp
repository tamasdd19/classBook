#include "user.h"

User::User()
{

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

void User::setId(int id)
{
    m_ID = id;
}