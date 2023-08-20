#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <sql/sqlite3.h>
#include "button.h"
#include "user.h"
#include "professor.h"
#include "student.h"
#include "databaseStuff.h"
#include "input.h"

namespace studentPage
{
    void mainPage(sqlite3* db, sf::RenderWindow& window, sf::Font& font, std::vector<Button*>& buttonsToDraw,std::vector<Button*>& dataButtons, std::vector<Button*>& gradeButtons, Student* student);
    void dataPage(sf::RenderWindow& window, std::vector<Button*>& dataButtons, sf::Sprite& background);
    void gradesPage(sf::RenderWindow& window, std::vector<Button*>& gradesButtons, sf::Sprite& background);
}

namespace profPage
{
    void mainPage(sqlite3* db, sf::RenderWindow& window, sf::Font& font, std::vector<Button*>& buttonsToDraw, std::vector<Button*>& dataButtons, std::vector<Button*>& gradeBookButtons, Professor* professor);
    void dataPage(sf::RenderWindow& window, std::vector<Button*>& dataButtons, sf::Sprite& background);
    void gradesPage(sf::RenderWindow& window, std::vector<Button*>& gradeBookButtons, sf::Sprite& background, Professor* professor, sf::Font& font, sqlite3* db);
}

// Admin side of the app
namespace adminPage
{
    void mainPage(sf::RenderWindow& window, sf::Font& font, sqlite3* db);
    void userPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
    void facultiesPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
    void coursesPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
    void majorsPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);

    namespace add 
    {
        // The menus that appear when you try to add data within the admin menu
        void userPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, Button* titleBtn);
        void facultyPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
        void coursePage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
        void majorPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
    }

    namespace modify 
    {
        // The menus that appear when you try to modify data within the admin menu
        void userPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, Button* titleBtn);
        void facultyPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
        void coursePage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
        void majorPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
    }

    namespace del 
    {
        // The menus that appear when you try to delete data within the admin menu
        void userPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
        void facultyPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
        void coursePage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
        void majorPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons);
    }
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
// On the Professor's side, after the prof has selected a course, a menu is created with all the students attending that course, so the prof. can give any student attending a grade
void courseStudentsList(Course* course, Button* backBtn, sf::RenderWindow& window, sf::Sprite& background, Professor* professor, sf::Font& font, sqlite3* db);
// The menu where the professor can add grades to the student
void giveGradeMenu(Course* course, Student* student, Button** otherButtons, sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db);
