#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>
#include <string.h>
#include "button.h"
#include "input.h"
#include "databaseStuff.h"

#define NAME_DEBUG "Prof2"
#define PASSWORD_DEBUG "test"

void menu1Options(std::vector<Button*>& menu1Buttons, sf::RenderWindow& window, User* user, sf::Font& font);
void menu2Student(std::vector<Button*>& menu2Buttons, sf::RenderWindow& window, Student* student, sf::Font& font, sqlite3* db);
void menu2Professor(std::vector<Button*>& menu2Buttons, sf::RenderWindow& window, Professor* professor, sf::Font& font, sqlite3* db);

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
    Button* errorLoginBtn = new Button(&Button::setCenter, window.getSize(), sf::Vector2f(200.f, 50.f), "Date incorecte!", font);
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
                                else
                                {
                                    professor = static_cast<Professor*>(userData.user);
                                    professorPage = true;
                                }
                                std::string titleText = "Welcome, ";
                                if(studentPage)
                                    titleText += userData.user->getFirstName() + " " + userData.user->getLastName();
                                else
                                    titleText += "Prof. " + userData.user->getFirstName();
                                loginPage = false;      
                                sf::Vector2f position = title->getPosition();                          
                                delete title;
                                Button::resetButtonHeight();
                                title = new Button(position, titleText, font, 50, {60.f, 60.f}, true);
                                title->setFillColor(sf::Color(0, 0, 0, 80));
                                title->setOutlineThickness(0);
                                title->setTextColor(sf::Color(255, 255, 255));
                                title->setPositionCenter(window.getSize());
                                if(title->getPosition().x < 0)
                                {
                                    titleText = "Welcome, " + userData.user->getUsername();
                                    title->setText(titleText);
                                    title->setPositionCenter(window.getSize());
                                }
                                title->setSideToSide(window.getSize());
                                buttonsToDraw.clear();
                                buttonsToDraw.push_back(title);
                                btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "", font, 28);
                                btn->setFillColor(sf::Color(255, 255, 255, 200));
                                btn->setOutlineThickness(0);
                                delete btn;
                                if(studentPage)
                                {
                                    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "Student's Data", font, 28);
                                    btn->setFillColor(sf::Color(255, 255, 255, 200));
                                    btn->setOutlineThickness(0);
                                    buttonsToDraw.push_back(btn);
                                    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "Grades", font, 28);
                                    btn->setFillColor(sf::Color(255, 255, 255, 200));
                                    btn->setOutlineThickness(0);
                                    buttonsToDraw.push_back(btn);
                                    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "Exit", font, 28);
                                    btn->setFillColor(sf::Color(255, 255, 255, 200));
                                    btn->setOutlineThickness(0);
                                    buttonsToDraw.push_back(btn);
                                }
                                else if(professorPage)
                                {
                                    title->setFillColor(sf::Color(0, 0, 0, 150));
                                    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "Professors's Data", font, 28);
                                    btn->setFillColor(sf::Color(255, 255, 255, 200));
                                    btn->setOutlineThickness(0);
                                    buttonsToDraw.push_back(btn);
                                    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "GradeBook", font, 28);
                                    btn->setFillColor(sf::Color(255, 255, 255, 200));
                                    btn->setOutlineThickness(0);
                                    buttonsToDraw.push_back(btn);
                                    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "Exit", font, 28);
                                    btn->setFillColor(sf::Color(255, 255, 255, 200));
                                    btn->setOutlineThickness(0);
                                    buttonsToDraw.push_back(btn);
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
                                    btnPosition.y -= 50.f;
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
                                    btnPosition.y -= 50.f;
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

void menu1Options(std::vector<Button*>& menu1Buttons, sf::RenderWindow& window, User* user, sf::Font& font)
{
    std::string btnText;
    Button* btn;
    sf::Vector2f btnPosition;
    btnText = "First Name: " + user->getFirstName();
    btn = new Button(&Button::setCenter, window.getSize(), {400.f, 50.f}, btnText, font, 28);
    btnPosition = btn->getPosition();
    btnPosition.y += 200.f;
    btn->setTextColor(sf::Color(0, 0, 0, 255));
    if (btn->isTextOutOfBounds()) 
    {
        delete btn;
        btn = new Button(btnPosition, btnText, font, 28, {30.f, 30.f}, false);
        btn->setPositionCenter(window.getSize());
    } 
    else 
    {
        btn->setPosition(btnPosition);
    }
    btn->setOutlineThickness(0);
    btn->setFillColor(sf::Color(255, 255, 255, 200));
    menu1Buttons.push_back(btn);

    btnText = "Last Name: " + user->getLastName();
    btn = new Button(&Button::setCenter, window.getSize(), {400.f, 50.f}, btnText, font, 28);
    btnPosition = btn->getPosition();
    btnPosition.y += 200.f;
    if (btn->isTextOutOfBounds()) 
    {
        delete btn;
        btn = new Button(btnPosition, btnText, font, 28, {30.f, 30.f}, false);
        btn->setPositionCenter(window.getSize());
    } 
    else
    {
        btn->setPosition(btnPosition);
    }
    btn->setOutlineThickness(0);
    btn->setFillColor(sf::Color(255, 255, 255, 200));
    menu1Buttons.push_back(btn);

    btnText = "Date of Birth: " + user->getDateOfBirth()->getString();
    btn = new Button(&Button::setCenter, window.getSize(), {400.f, 50.f}, btnText, font, 28);
    btnPosition = btn->getPosition();
    btnPosition.y += 200.f;
    btn->setPosition(btnPosition);
    btn->setOutlineThickness(0);
    btn->setFillColor(sf::Color(255, 255, 255, 200));
    menu1Buttons.push_back(btn);

    btnText = "Country of Origin: " + user->getCountryOrigin();
    btn = new Button(&Button::setCenter, window.getSize(), {400.f, 50.f}, btnText, font, 28);
    btnPosition = btn->getPosition();
    btnPosition.y += 200.f;
    if (btn->isTextOutOfBounds()) 
    {
        btn->setTextInBounds({30.f, 30.f});
    } 
    else 
    {
        btn->setPosition(btnPosition);
    }
    btn->setOutlineThickness(0);
    btn->setFillColor(sf::Color(255, 255, 255, 200));
    menu1Buttons.push_back(btn);

    btnText = "Gender: ";
    if (user->isMale())
        btnText += "Male";
    else
        btnText += "Female";
    btn = new Button(&Button::setCenter, window.getSize(), {400.f, 50.f}, btnText, font, 28);
    btnPosition = btn->getPosition();
    btnPosition.y += 200.f;
    btn->setPosition(btnPosition);
    btn->setOutlineThickness(0);
    btn->setFillColor(sf::Color(255, 255, 255, 200));
    menu1Buttons.push_back(btn);
}

void menu2Student(std::vector<Button*>& menu2Buttons, sf::RenderWindow& window, Student* student, sf::Font& font, sqlite3* db)
{
    // Initializez the major with all the respective courses for the student
    Major* major = new Major;
    Button* btn;
    int rc;
    std::string selectQuery;
    sf::Vector2f btnPosition;
    std::vector<float> grades;
    selectQuery = "SELECT * FROM major WHERE id = ";
    selectQuery += std::to_string(student->getMajorId());
    selectQuery += ";";
    
    rc = sqlite3_exec(db, selectQuery.c_str(), getMajor, major, 0); // GetMajor gets de id and name of the major
    
    if(rc != SQLITE_OK)
    {
        std::cout << "Error trying to get the major for the student" << std::endl;
        return ;
    }

    selectQuery.replace(14, 5, "courses");
    selectQuery.replace(selectQuery.find("id"), 2, "majorId");
    MyData2 data2;
    data2.id = major->getId();
    rc = sqlite3_exec(db, selectQuery.c_str(), setMajorCourses, &data2, 0); // setMajorCourses sets the major courses up
    if(rc != SQLITE_OK)
    {
        std::cout << "Erorr trying to collect the courses for the student" << std::endl;
        return ;
    }
    major->setCourses(data2.courses);
    student->setMajor(major);

    // Once the major courses are set up we can begin building up the menu for the student page nr 2
    std::string btnText = student->getFirstName() + " " + student->getLastName() + "'s grades"; 
    Button::resetButtonHeight();
    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 105.f}, btnText, font, 50);
    btn->setPositionCenter(window.getSize());
    btn->setSideToSide(window.getSize());
    btn->setFillColor(sf::Color(0, 0, 0, 80));
    btn->setOutlineThickness(0);
    btn->setTextColor(sf::Color(255, 255, 255));
    btn->setPositionCenter(window.getSize());
    
    menu2Buttons.push_back(btn);

    for(auto& i : student->getMajor()->getCourses())
    {
        float grade = -1.f;
        std::string showGrade;
        selectQuery = "SELECT * FROM grades WHERE courseId = " + std::to_string(i->getId()) + " AND studentID = " + std::to_string(student->getID()) + ";";
        rc = sqlite3_exec(db, selectQuery.c_str(), getGrades, &grade, 0);
        if(rc != SQLITE_OK)
        {
            std::cout << "Error trying to get grades\n";
            return ;
        }
        showGrade = std::to_string(grade);
        if(grade == -1.f)
        {
            showGrade = "not assigned";
        }
        else if(grade == 10.000f)
        {
            showGrade = showGrade.substr(0, 2);
        }
        else
        {
            showGrade = showGrade.substr(0, 4);
        }
        btnText = i->getName() + ": " + showGrade;
        btn = new Button(&Button::setCenter, window.getSize(), {400.f, 50.f}, btnText, font, 28);
        btnPosition = btn->getPosition();
        btn->setPosition(btnPosition);
        btn->setOutlineThickness(0);
        btn->setFillColor(sf::Color(255, 255, 255, 200));
        if(btn->isTextOutOfBounds())
        {
            btn->setTextInBounds({20.f, 20.f});
        }
        menu2Buttons.push_back(btn);
    }
}

void menu2Professor(std::vector<Button*>& menu2Buttons, sf::RenderWindow& window, Professor* professor, sf::Font& font, sqlite3* db)
{
    // Set the Professor's courses up!
    std::vector<Course*> courses;
    std::string selectQuery = "SELECT * FROM courses WHERE professorId = " + std::to_string(professor->getID()) + ";";
    int rc = sqlite3_exec(db, selectQuery.c_str(), getProfessorCourses, &courses, 0);
    if(rc != SQLITE_OK)
    {
        std::cout << "Error trying to get professor's courses\n";
        return ;
    }
    professor->setCourses(courses);
    // Once the courses are set up we can build the buttons!
    for(auto& i : professor->getCourses())
    {
        Button* btn = new Button(&Button::setCenter, window.getSize(), {400.f, 50.f}, i->getName(), font, 28);
        sf::Vector2f btnPosition = btn->getPosition();
        btnPosition.y += 125.f;
        btn->setPosition(btnPosition);
        btn->setOutlineThickness(0);
        btn->setFillColor(sf::Color(255, 255, 255, 200));
        if(btn->isTextOutOfBounds())
        {
            btn->setTextInBounds({20.f, 20.f});
        }
        menu2Buttons.push_back(btn);
    }
}




/*


int main() 
{
    Student* student; // in case the user is a student, to be able tu use student functions
    Professor* professor;
    sqlite3* db;
    int rc = sqlite3_open("database.db", &db);

    if (rc == SQLITE_OK) 
    {
        // Login phase, a very primitive version of it, but it works kind of
        if (rc == SQLITE_OK) 
        {
            std::string name, password;
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
            std::cout << "Enter password: ";
            std::cin >> password;
            myData data;
            data.name = name;
            data.password = password;

            const char* selectQuery = "SELECT * FROM users;";
            rc = sqlite3_exec(db, selectQuery, callbackFunction, &data, 0);

            if (rc == SQLITE_OK) 
            {
                // Still have to do connection after I log in somehow, something to do for later
                if(login)
                {  
                    // Primitive version of being logged in, I can't to anything for now :((
                    Major* major = new Major;
                    student = static_cast<Student*>(user);
                    std::string selectQuery;
                    selectQuery = "SELECT * FROM major WHERE id = ";
                    selectQuery += std::to_string(student->getMajorId());
                    selectQuery += ";";
                    
                    rc = sqlite3_exec(db, selectQuery.c_str(), getMajor, major, 0); // GetMajor gets de id and name of the major
                    
                    selectQuery.replace(14, 5, "courses");
                    selectQuery.replace(selectQuery.find("id"), 2, "majorId");

                    MyData2 data2;
                    data2.id = major->getId();

                    rc = sqlite3_exec(db, selectQuery.c_str(), setMajorCourses, &data2, 0); // setMajorCourses sets the major courses up
                    if(rc == SQLITE_OK)
                    {
                        major->setCourses(data2.courses);

                        student->setMajor(major);

                        std::cout << student->getName() << " studiaza " << student->getMajor()->getName() << " si are urmatoarele cursuri: \n";
                        for(auto& i : student->getMajor()->getCourses())
                        {
                            std::cout << i->getName() << std::endl;
                        }
                    }
                }
                else if(!data.gasit)
                {
                    std::cout << name << " doesn't exist in the users database\n";
                }
            }
        }

        // Close the database
        sqlite3_close(db);
    }

    return 0;
}
*/