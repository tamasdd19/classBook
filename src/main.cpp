#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>
#include <string.h>
#include "button.h"
#include "input.h"
#include "databaseStuff.h"

#define DEBUG 0

#if DEBUG   
#define NAME_DEBUG "Student2" 
#define PASSWORD_DEBUG "test" 
#else
#define NAME_DEBUG user // user for input from keyboard
#define PASSWORD_DEBUG pass // pass for input from keyboard
#endif

void menu1Options(std::vector<Button*>& menu1Buttons, sf::RenderWindow& window, User* user, sf::Font& font);
void menu2Student(std::vector<Button*>& menu2Buttons, sf::RenderWindow& window, Student* student, sf::Font& font, sqlite3* db);
void menu2Professor(std::vector<Button*>& menu2Buttons, sf::RenderWindow& window, Professor* professor, sf::Font& font, sqlite3* db);
void courseMenu(Course* course, Button* backBtn, sf::RenderWindow& window, sf::Sprite& background, Professor* professor, sf::Font& font, sqlite3* db);
void courseStudentMenu(Course* course, Student* student, Button** otherButtons, sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db);

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

void courseMenu(Course* course, Button* backBtn, sf::RenderWindow& window, sf::Sprite& background, Professor* professor, sf::Font& font, sqlite3* db)
{
    bool courseWindowOpen = true;
    std::vector<Button*> buttons;
    Button* btn;
    sf::Event event;
    std::vector<Student*> students;
    Button** otherButtons = new Button*[2];
    std::string selectQuery = "SELECT * FROM users WHERE majorId = " + std::to_string(course->getMajorId()) + ";";
    int rc = sqlite3_exec(db, selectQuery.c_str(), getStudents, &students, 0);
    
    if(rc != SQLITE_OK)
    {
        std::cout << "Error getting the Students\n";
        return ;
    }

    Button::resetButtonHeight();

    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 105.f}, course->getName(), font, 50);
    btn->setSideToSide(window.getSize());
    btn->setFillColor(sf::Color(0, 0, 0, 150));
    btn->setTextColor(sf::Color(255, 255, 255));
    btn->setOutlineThickness(0);
    buttons.push_back(btn);
    buttons.push_back(backBtn);
    otherButtons[0] = btn;
    otherButtons[1] = backBtn;

    for(auto& i : students)
    {
        Button* btn = new Button(&Button::setCenter, window.getSize(), {400.f, 50.f}, i->getFirstName() + " " + i->getLastName(), font, 28);
        sf::Vector2f btnPosition = btn->getPosition();
        // btnPosition.y += 50.f;
        btn->setPosition(btnPosition);
        btn->setOutlineThickness(0);
        btn->setFillColor(sf::Color(255, 255, 255, 200));
        if(btn->isTextOutOfBounds())
        {
            btn->setTextInBounds({20.f, 20.f});
        }
        buttons.push_back(btn);
    }

    while(courseWindowOpen)
    {
        while(window.pollEvent(event))
        {
            auto iter = buttons.begin();
            switch(event.type)
            {
                case sf::Event::Closed:
                    courseWindowOpen = false;
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    ++ iter;
                    
                    for(; iter<buttons.end(); ++iter)
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
                        if(buttons[1]->isMouseOver(window))
                        {
                            courseWindowOpen = false;
                        }
                        else
                        {
                            for(int i=2; i<buttons.size(); i++)
                            {
                                if(buttons[i]->isMouseOver(window))
                                {
                                    courseStudentMenu(course, students[i-2], otherButtons, window, background, font, db);
                                    if(!window.isOpen())
                                    {
                                        courseWindowOpen = false;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    break;

            }
        }
        window.clear();
        window.draw(background);
        for(auto& i : buttons)
            i->draw(window);
        window.display();
    }
    for(auto& i : buttons)
    {
        if(i != backBtn)
            delete i;
    }
}

void courseStudentMenu(Course* course, Student* student, Button** otherButtons, sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db)
{
    bool courseStudentMenuOpen = true;
    Button* btn, *succesBtn, *errorBtn;
    sf::Event event;
    std::vector<Button*> buttons = {otherButtons[0]};
    bool keyPressed = false;
    Button::resetButtonHeight();

    btn = new Button(&Button::setCenter, window.getSize(), {400.f, 100.f}, student->getFirstName() + " " + student->getLastName(), font, 35);
    sf::Vector2f btnPos = btn->getPosition();
    btnPos.y += 130.f;
    btn->setPosition(btnPos);
    btn->setOutlineThickness(0);
    btn->setFillColor(sf::Color(255, 255, 255, 200));
    if(btn->isTextOutOfBounds())
    {
        btn->setTextInBounds({20.f, 20.f});
    }
    buttons.push_back(btn);
    btn = new Button(&Button::setCenter, window.getSize(), {200.f, 50.f}, "Enter grade", font, 30);
    btnPos = btn->getPosition();
    btnPos.y += 200.f;
    btn->setPosition(btnPos);
    btn->setOutlineThickness(0);
    btn->setFillColor(sf::Color(255, 255, 255, 225));
    buttons.push_back(btn);
    buttons.push_back(otherButtons[1]);

    TextInput textInput(&Button::setCenter, window.getSize(), {150.f, 50.f}, font, 35);
    textInput.setText("test");
    textInput.setFillColor(sf::Color(255, 255, 255, 200));
    textInput.setOutlineColor(sf::Color(0, 0, 0, 50));
    btnPos = textInput.getPosition();
    btnPos.y += 200.f;
    textInput.setPosition(btnPos);
    textInput.setSelected(true);
    // buttons.push_back(&textInput);

    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 50.f}, "Grade added!", font, 30);
    btn->setFillColor(sf::Color(0, 255, 0));
    btn->setTextColor(sf::Color(0, 0, 0));
    btn->setOutlineThickness(0);
    btnPos = btn->getPosition();
    btnPos.y -= 25.f;
    btn->setPosition(btnPos);
    succesBtn = btn;
    
    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 50.f}, "Error, invalid grade!", font, 30);
    btn->setFillColor(sf::Color(255, 0, 0));
    btn->setTextColor(sf::Color(0, 0, 0));
    btn->setOutlineThickness(0);
    btnPos = btn->getPosition();
    btnPos.y -= 100.f;
    btn->setPosition(btnPos);
    errorBtn = btn;

    while(courseStudentMenuOpen)
    {
        textInput.handleEvent(event, window, keyPressed);

        while(window.pollEvent(event))
        {
            auto iter = buttons.begin();
            switch(event.type)
            {
                default:
                    break;
                case sf::Event::Closed:
                    window.close();
                    courseStudentMenuOpen = false;
                    return ;
                    break;
                case sf::Event::MouseMoved:
                    if (buttons[3]->isMouseOver(window)) 
                    {
                        buttons[3]->setOutlineThickness(3.f);
                        buttons[3]->setOutlineColor(sf::Color::Black);
                        buttons[3]->setFillColor(sf::Color(255, 255, 255, 250));
                    }
                    else
                    {
                        buttons[3]->setOutlineThickness(0);
                        buttons[3]->setFillColor(sf::Color(255, 255, 255, 200));
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        if(buttons[3]->isMouseOver(window))
                        {
                            courseStudentMenuOpen = false;
                        }
                        else
                        {

                        }
                    }
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Return)
                    {
                        if(!textInput.getText().empty())
                        {
                            if(textInput.getSelected())
                                textInput.setSelected(false);
                            try 
                            {
                                float grade = std::stof(textInput.getText());
                                if(grade < 0.f || grade > 10.f)
                                {
                                    throw std::invalid_argument("Invalid grade");
                                }
                                bool check = false;
                                std::string query = "SELECT grade FROM grades WHERE courseId = " + std::to_string(course->getId()) + " AND studentId = " + std::to_string(student->getID()) + ";";
                                int rc = sqlite3_exec(db, query.c_str(), checkIfGradeExists, &check, 0);
                                if(rc != SQLITE_OK)
                                {
                                    std::cout << "Error trying to input the grade";
                                    return ;
                                }
                                if(check) // there is a grade already for that course and student
                                {
                                    std::string query = "UPDATE grades SET grade = " + std::to_string(grade) +
                                                        " WHERE courseId = " + std::to_string(course->getId()) +
                                                        " AND studentId = " + std::to_string(student->getID()) + ";";
                                    rc = sqlite3_exec(db, query.c_str(), 0, 0, 0);
                                    if (rc != SQLITE_OK) 
                                    {
                                        std::cout << "Error trying to update the grade\n";
                                        return;
                                    }
                                    // Grade updated with success
                                    buttons.push_back(succesBtn);
                                }
                                else // We have to insert the grade into the table
                                {
                                    query = "INSERT INTO grades (courseId, studentId, grade) VALUES (" + std::to_string(course->getId()) + ", " + std::to_string(student->getID()) + ", " + std::to_string(grade) + ");";
                                    rc = sqlite3_exec(db, query.c_str(), 0, 0, 0);
                                    if(rc != SQLITE_OK)
                                    {
                                        std::cout << "Error trying to insert the grade\n";
                                        return ;
                                    }
                                    // Grade inserted with success
                                    buttons.push_back(succesBtn);
                                }

                            } 
                            catch (const std::exception& e) 
                            {
                                buttons.push_back(errorBtn);
                            }
                            textInput.clearText();
                        }
                    }
            }
        }
        
        textInput.update();

        window.clear();
        window.draw(background);
        for(auto& i : buttons)
            i->draw(window);
        textInput.draw(window);
        window.display();
    }
}