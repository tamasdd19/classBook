#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sql/sqlite3.h>
#include "button.h"
#include "user.h"
#include "professor.h"
#include "student.h"
#include "databaseStuff.h"
#include "input.h"

#define DEBUG 0
// #define ADMIN 0

#ifdef DEBUG
#define NAME_DEBUG "Student1" 
#define PASSWORD_DEBUG "test" 
#else
#ifdef ADMIN
#define NAME_DEBUG "admin" 
#define PASSWORD_DEBUG "admin" 
#else
#define NAME_DEBUG user // user for input from keyboard
#define PASSWORD_DEBUG pass // pass for input from keyboard
#endif
#endif

// The main page you see when you open up the app
LoginData* loginPage(sqlite3 *db, sf::RenderWindow& window, sf::Font& font, std::vector<Button*>& buttonsToDraw);

namespace studentPage
{
    void mainPage(sqlite3* db, sf::RenderWindow& window, sf::Font& font, sf::Sprite& background, std::vector<Button*>& buttonsToDraw,std::vector<Button*>& dataButtons, std::vector<Button*>& gradeButtons, Student* student);
    void dataPage(sf::RenderWindow& window, std::vector<Button*>& dataButtons, sf::Sprite& background);
    void gradesPage(sf::RenderWindow& window, std::vector<Button*>& gradesButtons, sf::Sprite& background);
}

namespace profPage
{
    void mainPage(sqlite3* db, sf::RenderWindow& window, sf::Font& font, sf::Sprite& background, std::vector<Button*>& buttonsToDraw, std::vector<Button*>& dataButtons, std::vector<Button*>& gradeBookButtons, Professor* prof);
    void dataPage(sf::RenderWindow& window, std::vector<Button*>& dataButtons, sf::Sprite& background);
    void gradesPage();
}

// It transforms the textToAdd parameter into buttons and it adds them to the existing buttons parameter
void addButtonOptions(std::vector<Button*>& buttons, const sf::Vector2f& btnSize, std::vector<std::string>& textToAdd, const sf::Vector2u& windowSize, sf::Font& font, float buttonsDistance);
// Updates menu1Buttons with all the data the user has, student or professor, it will show the first name, last name, dob, country of origin and gender
std::vector<Button*> userDataInfoButtons(sf::RenderWindow& window, User* user, sf::Font& font);
// Updates de studentGradesButtons vector with all the courses the student is attending and all the grades the student gathered at every course.
// If there is not a grade assigned, it will say not assigned
std::vector<Button*> studentGradesButtons(sf::RenderWindow& window, Student* student, sf::Font& font, sqlite3* db);
// Updates the profCoursesButtons vector with all the courses the professor is teaching
std::vector<Button*> profCoursesButtons(sf::RenderWindow& window, Professor* professor, sf::Font& font, sqlite3* db);

// namespace profGradeBook
// {
    // On the Professor's side, after the prof has selected a course, a menu is created with all the students attending that course, so the prof. can give any student attending a grade
    void courseMenu(Course* course, Button* backBtn, sf::RenderWindow& window, sf::Sprite& background, Professor* professor, sf::Font& font, sqlite3* db);
    // The menu where the professor can add grades to the student
    void courseStudentMenu(Course* course, Student* student, Button** otherButtons, sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db);
// }

// Admin side of the app
// The main page
void adminPage(sf::RenderWindow& window, sf::Font& font, sqlite3* db);
// Admin's pages
void adminUserPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
void adminFacultiesPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
void adminCoursesPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
void adminMajorsPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);

namespace adminAdd 
{
    // The menus that appear when you try to add data within the admin menu
    void userPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, Button* titleBtn);
    void facultyPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
    void coursePage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
    void majorPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
}

namespace adminModify 
{
    // The menus that appear when you try to modify data within the admin menu
    void userPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, Button* titleBtn);
    void facultyPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
    void coursePage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
    void majorPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
}

namespace adminDelete 
{
    // The menus that appear when you try to delete data within the admin menu
    void userPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
    void facultyPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
    void coursePage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
    void majorPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
}