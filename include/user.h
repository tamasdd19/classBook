#pragma once

#include <iostream>
#include <string>
#include <vector>


class Date;

class User
{
public:
    User(const std::string& name);
    User();
    // Getters
    std::string getUsername() const;
    int getID() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getCountryOrigin() const;
    bool isMale() const; 
    Date* getDateOfBirth() const; 
    // Setters
    void setUsername(const std::string&);
    void setId(int);
    void setFirstName(const std::string&);
    void setLastName(const std::string&);
    void setCountryOrigin(const std::string&);
    void setMale(bool);
    void setDateOfBirth(int, int, int); // I'm gonna read the date of birth from the users table, which is a char** and I'm gonna convert in the function
private:
    int m_ID = -1;
    std::string m_username, m_firstName, m_lastName, m_countryOrigin;
    bool m_male = 1; // 1 = M; 0 = F
    Date* m_DoB = nullptr; // date of birth
};

class Date
{
public:
    Date();
    Date(int, int, int);
    // Getters
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    std::string getString() const;
    // Setters
    void setDay(int);
    void setMonth(int);
    void setYear(int);
private:
    int m_day = -1, m_month = -1, m_year = -1;
};