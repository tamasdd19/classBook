#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string.h>
#include "button.h"
#include "input.h"
#include "databaseStuff.h"
#include "menus.h"

// #define DEBUG 0
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

// The main page you see when you open up the app, this function returns the user
LoginData* loginPage(sqlite3 *db, sf::RenderWindow& window, sf::Font& font, std::vector<Button*>& buttonsToDraw);

int main()
{
    // Back End stuff setups
    sqlite3* db;
    int rc = sqlite3_open("database.db", &db);
    if(rc != SQLITE_OK)
    {
        std::cout << "Could not open up the data base!\n";
        return 0;
    }
    std::vector<Button*> buttonsToDraw;

    // Front End stuff setups
    sf::RenderWindow window(sf::VideoMode(1280, 720), "ClassBook", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("src/arial.ttf");

    LoginData* userData = loginPage(db, window, font, buttonsToDraw);

    if(!window.isOpen()) // So it doensn't crash if you close the window in the login page
    {
        sqlite3_close(db);
        return 0;
    }

    if(userData->isAdmin) // Admin side
    {
        adminPage::mainPage(window, font, db);
        sqlite3_close(db);
        return 0;
    }

    std::vector<Button*> userDataInfo = userDataInfoButtons(window, userData->user, font); // Loads the userDataInfo with the buttons that shows basic info about the user, in the first menu

    if(userData->isStudent) // Student side
    {
        std::vector<Button*> gradeButtons = studentGradesButtons(window, userData->student, font, db);

        studentPage::mainPage(db, window, font, buttonsToDraw, userDataInfo, gradeButtons, userData->student);   
    }
    else // Professor side
    {
        std::vector<Button*> gradeBookButtons = profCoursesButtons(window, userData->professor, font, db);

        profPage::mainPage(db, window, font, buttonsToDraw, userDataInfo, gradeBookButtons, userData->professor);
    }

    sqlite3_close(db);
    return 0;
}

LoginData* loginPage(sqlite3 *db, sf::RenderWindow& window, sf::Font& font, std::vector<Button*>& buttonsToDraw)
{
    sf::Texture texture;
    if(!texture.loadFromFile("img/login-page-background.jpg"))
    {
        std::cout << "Image not loaded";
    }
    sf::Sprite background(texture);

    LoginData* userData = new LoginData;
    Student* student;
    Professor* professor;
    sf::Event event;
    bool keyPressed = false;
    bool studentPage = false;
    bool professorPage = false;

    Button* title = new Button(&Button::setCenter, window.getSize(), sf::Vector2f(300.f, 100.f), "ClassBook!", font, 40);
    Button* errorLoginBtn = new Button(&Button::setCenter, window.getSize(), sf::Vector2f(200.f, 50.f), "Invalid data!", font);
    Button* userRect = new Button(&Button::setCenter, window.getSize(), sf::Vector2f(200.f, 50.f), "Username", font);
    TextInput* textInput = new TextInput(&Button::setCenter, window.getSize(), sf::Vector2f(300.f, 50.f), font);
    Button* passRect = new Button(&Button::setCenter, window.getSize(), sf::Vector2f(200.f, 50.f), "Password", font);
    TextInput* passInput = new TextInput(&Button::setCenter, window.getSize(), sf::Vector2f(300.f, 50.f), font);

    textInput->setFillColor(sf::Color(255, 255, 255, 200));
    textInput->setOutlineColor(sf::Color(0, 0, 0, 50));

    passInput->setFillColor(sf::Color(255, 255, 255, 200));
    passInput->setOutlineColor(sf::Color(0, 0, 0, 50));
    passInput->setIsPassword(true);

    title->setFillColor(sf::Color(255, 255, 255, 20));
    title->setOutlineThickness(0);
    title->setTextColor(sf::Color(0, 0, 0, 250));

    errorLoginBtn->setFillColor(sf::Color::Red);
    errorLoginBtn->setOutlineColor(sf::Color::Red);

    userRect->setFillColor(sf::Color(255,255,255,150));
    userRect->setOutlineColor(sf::Color(0, 0, 0, 50));

    passRect->setFillColor(sf::Color(255,255,255,150));
    passRect->setOutlineColor(sf::Color(0, 0, 0, 50));

    buttonsToDraw.push_back(title);
    buttonsToDraw.push_back(userRect);
    buttonsToDraw.push_back(textInput);
    buttonsToDraw.push_back(passRect);
    buttonsToDraw.push_back(passInput);

    textInput->setSelected(true);

    textInput->getText(); // for whatever reason if I don't to this, on my pc it will show the null char in the input box

    while (window.isOpen())  
    {
        textInput->handleEvent(event, window, keyPressed);
        passInput->handleEvent(event, window, keyPressed);
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Return)
                    {
                        if(textInput->isSelected() && passInput->getText().empty() && textInput->getText().size()>1)
                        {
                            textInput->setSelected(false);
                            passInput->setSelected(true);
                        }
                        else
                        {
                            if(passInput->isSelected())
                                passInput->setSelected(false);
                            if(textInput->isSelected())
                                textInput->setSelected(false);
                            std::string user = textInput->getText();
                            std::string pass = passInput->getText();
                                                            

                            textInput->clearText();
                            passInput->clearText();

                            userData->name = NAME_DEBUG;//user;
                            userData->password = PASSWORD_DEBUG;//pass;
                                                                        
                            const char* selectQuery = "SELECT * FROM users;";
                            int rc = sqlite3_exec(db, selectQuery, callbackFunction, userData, 0);
                            if(rc != SQLITE_OK)
                            {
                                std::cout << "Error trying to connect!\n";
                                return nullptr;
                            }
                            else if(!userData->found || userData->user == nullptr)
                            {
                                buttonsToDraw.push_back(errorLoginBtn);
                                break;
                            }

                            std::string titleText = "Welcome, ";

                            if(userData->isStudent)
                            {
                                userData->student = static_cast<Student*>(userData->user);
                                titleText += userData->user->getFirstName() + " " + userData->user->getLastName();
                                // For the student, it shows it's first and last name
                            }
                            else if(userData->user->getUsername() == "admin")
                            {
                                userData->isAdmin = true;
                                return userData;
                            }
                            else
                            {
                                userData->professor = static_cast<Professor*>(userData->user);
                                titleText += "Prof. " + userData->user->getLastName();
                                // For the prof. it shows Prof. and its last Name
                            }

                            Button::resetButtonHeight();

                            title = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, titleText, font, 50);
                            title->setFillColor(sf::Color(0, 0, 0, 125));
                            title->setOutlineThickness(0);
                            title->setTextColor(sf::Color(255, 255, 255));
                            if(title->getPosition().x < 0) // Checks if the title is bigger than the screen itself 
                            {                // and only shows the username, in case of someone with a very long name
                                titleText = "Welcome, " + userData->user->getUsername();
                                title->setText(titleText, false);
                                title->setPositionCenter(window.getSize());
                            }
                            title->setSideToSide(window.getSize());
                            buttonsToDraw.clear();
                            buttonsToDraw.push_back(title);
                            if(userData->isStudent)
                            {
                                std::vector<std::string> menuOptions = {"Student's Data", "Grades", "Exit"};
                                addButtonOptions(buttonsToDraw, {300.f, 100.f}, menuOptions, window.getSize(), font, 100.f);
                            }
                            else
                            {
                                title->setFillColor(sf::Color(0, 0, 0, 150));
                                std::vector<std::string> menuOptions = {"Professor's Data", "GradeBook", "Exit"};
                                addButtonOptions(buttonsToDraw, {300.f, 100.f}, menuOptions, window.getSize(), font, 100.f);
                            }
                            return userData;
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                        return nullptr;
                    }
                    break;
                default:
                    break;
            }
        }

        textInput->update();
        passInput->update();

        window.clear();
        window.draw(background);
        for(auto& i : buttonsToDraw)
            i->draw(window);
        window.display();
    }
    return userData;
}