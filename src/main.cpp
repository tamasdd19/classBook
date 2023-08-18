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


int main()
{
    // Back End stuff setups
    Student* student = nullptr;
    Professor* professor = nullptr;
    sqlite3* db;
    int rc = sqlite3_open("database.db", &db);
    if(rc != SQLITE_OK)
    {
        std::cout << "Could not open up the data base!\n";
        return 0;
    }
    MyData userData;

    // Front End stuff setups
    sf::RenderWindow window(sf::VideoMode(1280, 720), "ClassBook", sf::Style::Titlebar | sf::Style::Close);

    sf::Font font;
    font.loadFromFile("src/arial.ttf");
    
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

    std::vector<Button*> buttonsToDraw;
    buttonsToDraw.push_back(title);
    buttonsToDraw.push_back(userRect);
    buttonsToDraw.push_back(textInput);
    buttonsToDraw.push_back(passRect);
    buttonsToDraw.push_back(passInput);

    sf::Texture texture;
    if(!texture.loadFromFile("img/login-page-background.jpg"))
    {
        std::cout << "Image not loaded";
    }

    sf::Sprite background(texture);
    sf::Texture texture2;
    if(!texture2.loadFromFile("img/student-page-background.jpg"))
    {
        std::cout << "Image not loaded";
    }
    sf::Sprite backgroundStudent(texture2);
    sf::Texture texture3;
    if(!texture3.loadFromFile("img/professor-page-background.jpg"))
    {
        std::cout << "Image not loaded";
    }
    sf::Sprite backgroundProfessor(texture3);
    sf::Texture texture4;
    if(!texture4.loadFromFile("img/admin-page-background.jpg"))
    {
        std::cout << "Image not loaded";
    }
    sf::Sprite adminBackground(texture4);
    bool loginPage = true;
    bool studentPage = false;
    bool professorPage = false;
    bool keyPressed = false;
    bool menus[3] = {false, false, false}; // main menu, first and second menu in studentPage or professorPage

    std::vector<Button*> menu1Buttons;
    std::vector<Button*> menu2Buttons;
    Button* btn = nullptr;
    Button* backBtn = nullptr;

    window.setFramerateLimit(60);
    textInput->setSelected(true);

    textInput->getText(); // for whatever reason if I don't to this, on my pc it will show the null char in the input box

    while (window.isOpen())
    {
        sf::Event event;
        if(loginPage)
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
                            if(textInput->getSelected() && passInput->getText().empty() && textInput->getText().size()>1)
                            {
                                textInput->setSelected(false);
                                passInput->setSelected(true);
                            }
                            else
                            {
                                if(passInput->getSelected())
                                    passInput->setSelected(false);
                                if(textInput->getSelected())
                                    textInput->setSelected(false);
                                std::string user = textInput->getText();
                                std::string pass = passInput->getText();
                                
                                textInput->clearText();
                                passInput->clearText();

                                userData.name = NAME_DEBUG;//user;
                                userData.password = PASSWORD_DEBUG;//pass;

                                const char* selectQuery = "SELECT * FROM users;";
                                rc = sqlite3_exec(db, selectQuery, callbackFunction, &userData, 0);
                                if(rc != SQLITE_OK)
                                {
                                    std::cout << "Error trying to connect!\n";
                                    return 0;
                                }
                                else if(!userData.gasit || userData.user == nullptr)
                                {
                                    buttonsToDraw.push_back(errorLoginBtn);
                                    break;
                                }
                                if(userData.student)
                                {
                                    student = static_cast<Student*>(userData.user);
                                    studentPage = true;
                                }
                                else if(userData.user->getUsername() == "admin")
                                {
                                    adminPage(window, adminBackground, font, db);
                                }
                                else
                                {
                                    professor = static_cast<Professor*>(userData.user);
                                    professorPage = true;
                                }
                                std::string titleText = "Welcome, ";
                                if(studentPage) // For the student, it shows it's first and last name
                                    titleText += userData.user->getFirstName() + " " + userData.user->getLastName();
                                else // For the prof. it shows Prof. and it's last name Name
                                    titleText += "Prof. " + userData.user->getLastName();
                                loginPage = false;      
                                Button::resetButtonHeight();
                                title = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, titleText, font, 50);
                                title->setFillColor(sf::Color(0, 0, 0, 125));
                                title->setOutlineThickness(0);
                                title->setTextColor(sf::Color(255, 255, 255));
                                if(title->getPosition().x < 0) // Checks if the title is bigger than the screen itself 
                                {                // and only shows the username, in case of someone with a very long name
                                    titleText = "Welcome, " + userData.user->getUsername();
                                    title->setText(titleText, false);
                                    title->setPositionCenter(window.getSize());
                                }
                                title->setSideToSide(window.getSize());
                                buttonsToDraw.clear();
                                buttonsToDraw.push_back(title);
                                if(studentPage)
                                {
                                    std::vector<std::string> menuOptions = {"Student's Data", "Grades", "Exit"};
                                    addButtonOptions(buttonsToDraw, {300.f, 100.f}, menuOptions, window.getSize(), font, 100.f);
                                }
                                else if(professorPage)
                                {
                                    title->setFillColor(sf::Color(0, 0, 0, 150));
                                    std::vector<std::string> menuOptions = {"Professor's Data", "GradeBook", "Exit"};
                                    addButtonOptions(buttonsToDraw, {300.f, 100.f}, menuOptions, window.getSize(), font, 100.f);
                                }
                                menus[0] = true;
                            }

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
        else if(studentPage)  
        {
            if(menus[0]) // Student's main menu  
            {    
                while(window.pollEvent(event)) 
                {
                    auto iter = buttonsToDraw.begin();

                    switch(event.type)
                    {
                        default:
                            break;
                        case sf::Event::Closed:
                            window.close();
                            break;

                        case sf::Event::MouseMoved:
                            ++iter;

                            for (; iter != buttonsToDraw.end(); ++iter)
                            {
                                auto& i = *iter;
                                
                                if (i->isMouseOver(window)) 
                                {
                                    i->setOutlineThickness(3.f);
                                    i->setOutlineColor(sf::Color::Black);
                                    i->setFillColor(sf::Color(255, 255, 255, 250));
                                }
                                else
                                {
                                    i->setOutlineThickness(0);
                                    i->setFillColor(sf::Color(255, 255, 255, 200));
                                }
                            }
                            break;
                        case sf::Event::MouseButtonPressed:
                            if (event.mouseButton.button == sf::Mouse::Left)
                            {
                                if(backBtn == nullptr)
                                {
                                    sf::Vector2f btnPosition;
                                    backBtn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "Back", font, 28);
                                    backBtn->setFillColor(sf::Color(255, 255, 255, 200));
                                    backBtn->setOutlineThickness(0);
                                    btnPosition = backBtn->getPosition();
                                    btnPosition.y += 75.f;
                                    backBtn->setPosition(btnPosition);
                                }
                                if(buttonsToDraw[1]->isMouseOver(window)) // Student's data
                                {
                                    menus[1] = true;
                                    menus[0] = false;
                                    
                                    if(menu1Buttons.empty())
                                    {
                                        menu1Buttons.push_back(buttonsToDraw[0]);

                                        menu1Buttons.push_back(backBtn);

                                        Button::resetButtonHeight();

                                        menu1Options(menu1Buttons, window, student, font);

                                    }
                                    break;
                                }
                                else if(buttonsToDraw[2]->isMouseOver(window)) // Grades
                                {
                                    menus[2] = true;
                                    menus[0] = false;

                                    if(menu2Buttons.empty())
                                    {
                                        menu2Buttons.push_back(backBtn);

                                        Button::resetButtonHeight();

                                        menu2Student(menu2Buttons, window, student, font, db);
                                    }
                                }
                                if(buttonsToDraw[3]->isMouseOver(window)) // Exit
                                {
                                    window.close();
                                }
                            }
                            break;
                    }
                }
                window.clear();
                window.draw(backgroundStudent);
                for(auto& i : buttonsToDraw)
                    i->draw(window);
                window.display();
            }
            else if(menus[1]) // Student's data
            {
                while(window.pollEvent(event)) 
                {
                    switch(event.type)
                    {
                        default:
                            break;
                        case sf::Event::Closed:
                            window.close();
                            break;
                        case sf::Event::MouseMoved:
                            if (menu1Buttons[1]->isMouseOver(window)) 
                            {
                                menu1Buttons[1]->setOutlineThickness(3.f);
                                menu1Buttons[1]->setOutlineColor(sf::Color::Black);
                                menu1Buttons[1]->setFillColor(sf::Color(255, 255, 255, 250));
                            }
                            else
                            {
                                menu1Buttons[1]->setOutlineThickness(0);
                                menu1Buttons[1]->setFillColor(sf::Color(255, 255, 255, 200));
                            }
                            break;
                        case sf::Event::MouseButtonPressed:
                            if(event.mouseButton.button == sf::Mouse::Left)
                            {
                                if(menu1Buttons[1]->isMouseOver(window))
                                {
                                    menus[1] = false;
                                    menus[0] = true;
                                }
                            }
                    }
                }
                window.clear();
                window.draw(backgroundStudent);
                for(auto& i : menu1Buttons)
                    i->draw(window);
                window.display();
            }
            else if(menus[2]) // Student's grades
            {
                while(window.pollEvent(event))
                {
                    switch(event.type)
                    {
                        default:
                            break;
                        case sf::Event::Closed:
                            window.close();
                            break;
                            case sf::Event::MouseMoved:
                            if (menu2Buttons[0]->isMouseOver(window)) 
                            {
                                menu2Buttons[0]->setOutlineThickness(3.f);
                                menu2Buttons[0]->setOutlineColor(sf::Color::Black);
                                menu2Buttons[0]->setFillColor(sf::Color(255, 255, 255, 250));
                            }
                            else
                            {
                                menu2Buttons[0]->setOutlineThickness(0);
                                menu2Buttons[0]->setFillColor(sf::Color(255, 255, 255, 200));
                            }
                            break;
                            case sf::Event::MouseButtonPressed:
                            if(event.mouseButton.button == sf::Mouse::Left)
                            {
                                if(menu2Buttons[0]->isMouseOver(window))
                                {
                                    menus[2] = false;
                                    menus[0] = true;
                                }
                            }
                    }
                }
                window.clear();
                window.draw(backgroundStudent);
                for(auto& i : menu2Buttons)
                    i->draw(window);
                window.display();
            }
        }
        else if(professorPage)
        {
            if (menus[0]) // Professor's main menu
            {
                while (window.pollEvent(event)) 
                {
                    auto iter = buttonsToDraw.begin();

                    switch(event.type)
                    {
                        default:
                            break;
                        case sf::Event::Closed:
                            window.close();
                            break;
                        case sf::Event::MouseMoved:
                            ++iter;

                            for (; iter != buttonsToDraw.end(); ++iter)
                            {
                                auto& i = *iter;
                                
                                if (i->isMouseOver(window)) 
                                {
                                    i->setOutlineThickness(3.f);
                                    i->setOutlineColor(sf::Color::Black);
                                    i->setFillColor(sf::Color(255, 255, 255, 250));
                                }
                                else
                                {
                                    i->setOutlineThickness(0);
                                    i->setFillColor(sf::Color(255, 255, 255, 200));
                                }
                            }
                            break;
                        case sf::Event::MouseButtonPressed:
                            if (event.mouseButton.button == sf::Mouse::Left) 
                            {
                                if(backBtn == nullptr)
                                {
                                    sf::Vector2f btnPosition;
                                    backBtn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "Back", font, 28);
                                    backBtn->setFillColor(sf::Color(255, 255, 255, 200));
                                    backBtn->setOutlineThickness(0);
                                    btnPosition = backBtn->getPosition();
                                    btnPosition.y += 75.f;
                                    backBtn->setPosition(btnPosition);
                                }
                                if (buttonsToDraw[1]->isMouseOver(window))  // Professor's Data
                                {
                                    menus[1] = true;
                                    menus[0] = false;
                                        
                                    if (menu1Buttons.empty()) 
                                    {
                                        sf::Vector2f btnPosition;
                                        menu1Buttons.push_back(buttonsToDraw[0]);
                                        
                                        menu1Buttons.push_back(backBtn);

                                        Button::resetButtonHeight();

                                        menu1Options(menu1Buttons, window, professor, font);
                                    }
                                    break;
                                }
                                else if (buttonsToDraw[2]->isMouseOver(window))  // GradeBook, to give grades and stuff
                                { 
                                    menus[2] = true;
                                    menus[0] = false;

                                    if(menu2Buttons.empty())
                                    {
                                        sf::Vector2f btnPosition;
                                        menu2Buttons.push_back(buttonsToDraw[0]);
                                        
                                        menu2Buttons.push_back(backBtn);

                                        Button::resetButtonHeight();

                                        menu2Professor(menu2Buttons, window, professor, font, db);
                                    }

                                    break;
                                }
                                else if (buttonsToDraw[3]->isMouseOver(window))  // Exit
                                { 
                                    window.close();
                                }
                            }
                            break;
                    }
                }

                window.clear();
                window.draw(backgroundProfessor);
                for (auto& i : buttonsToDraw)
                    i->draw(window);
                window.display();
            } 
            else if (menus[1]) // Professor's Data
            {
                while(window.pollEvent(event)) 
                {
                    switch(event.type)
                    {
                        default:
                            break;
                        case sf::Event::Closed:
                            window.close();
                            break;
                        case sf::Event::MouseMoved:
                            if (menu1Buttons[1]->isMouseOver(window)) 
                            {
                                menu1Buttons[1]->setOutlineThickness(3.f);
                                menu1Buttons[1]->setOutlineColor(sf::Color::Black);
                                menu1Buttons[1]->setFillColor(sf::Color(255, 255, 255, 250));
                            }
                            else
                            {
                                menu1Buttons[1]->setOutlineThickness(0);
                                menu1Buttons[1]->setFillColor(sf::Color(255, 255, 255, 200));
                            }
                            break;
                        case sf::Event::MouseButtonPressed:
                            if(event.mouseButton.button == sf::Mouse::Left)
                            {
                                if(menu1Buttons[1]->isMouseOver(window))
                                {
                                    menus[1] = false;
                                    menus[0] = true;
                                }
                            }
                            break;
                    }
                }
                window.clear();
                window.draw(backgroundProfessor);
                for(auto& i : menu1Buttons)
                    i->draw(window);
                window.display();
            }
            else if(menus[2]) // rest of the code for the gradeBook goes here!
            {
                while(window.pollEvent(event))
                {
                    auto iter = menu2Buttons.begin();
                    switch(event.type)
                    {
                        default:
                            break;
                        case sf::Event::Closed:
                            window.close();
                            break;
                        case sf::Event::MouseMoved:
                            ++iter;

                            for (; iter != menu2Buttons.end(); ++iter)
                            {
                                auto& i = *iter;
                                
                                if (i->isMouseOver(window)) 
                                {
                                    i->setOutlineThickness(3.f);
                                    i->setOutlineColor(sf::Color::Black);
                                    i->setFillColor(sf::Color(255, 255, 255, 250));
                                }
                                else
                                {
                                    i->setOutlineThickness(0);
                                    i->setFillColor(sf::Color(255, 255, 255, 200));
                                }
                            }
                            break;
                        case sf::Event::MouseButtonPressed:
                            if(event.mouseButton.button == sf::Mouse::Left)
                            {
                                if(menu2Buttons[1]->isMouseOver(window))
                                {
                                    menus[2] = false;
                                    menus[0] = true;
                                }
                                else
                                {
                                    for(int i = 2; i<menu2Buttons.size(); i++)
                                    {
                                        if(menu2Buttons[i]->isMouseOver(window))
                                        {
                                            courseMenu(professor->getCourses()[i-2], backBtn, window, backgroundProfessor, professor, font, db);
                                        }
                                    }
                                }
                            }
                    }
                }
                window.clear();
                window.draw(backgroundProfessor);
                for(auto& i : menu2Buttons)
                    i->draw(window);
                window.display();
            }
        }
        
    }
    sqlite3_close(db);
    return 0;
}
