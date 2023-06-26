#include "user.h"

User::User()
{

}

User::User(const std::string& name)
    : User()
{
    m_username = name;
}

// Getters
std::string User::getUsername() const
{
    return m_username;
}

int User::getID() const
{
    return m_ID;
}

std::string User::getFirstName() const
{
    return m_firstName;
}
std::string User::getLastName() const
{
    return m_lastName;
}
std::string User::getCountryOrigin() const
{
    return m_countryOrigin;
}
bool User::getSex() const
{
    return m_sexM;
}
Date* User::getDateOfBirth() const
{
    return m_DoB;
}

//Setters
void User::setUsername(const std::string& name)
{
    m_username = name;
}

void User::setId(int id)
{
    m_ID = id;
}

void User::setFirstName(const std::string& name)
{
    m_firstName = name;
}
void User::setLastName(const std::string& name)
{
    m_lastName = name;
}
void User::setCountryOrigin(const std::string& country)
{
    m_countryOrigin = country;
}
void User::setSex(bool sexM)
{
    m_sexM = sexM;
}

void User::setDateOfBirth(int day, int month, int year)
{
    if (m_DoB != nullptr)
        delete m_DoB;
    m_DoB = new Date(day, month, year);
}




// Date part

Date::Date()
{

}

Date::Date(int day, int month, int year)
    : m_day(day), m_month(month), m_year(year)
{

}

// Getters
int Date::getDay() const
{
    return m_day;
}

int Date::getMonth() const
{
    return m_month;
}

int Date::getYear() const
{
    return m_year;
}

// Setters
void Date::setDay(int day)
{
    m_day = day;
}

void Date::setMonth(int month)
{
    m_month = month;
}

void Date::setYear(int year)
{
    m_year = year;
}