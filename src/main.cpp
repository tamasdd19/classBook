#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>
#include <string.h>
#include "button.h"
#include "input.h"
#include "databaseStuff.h"


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
    Button errorLoginBtn(&Button::setCenter, window.getSize(), sf::Vector2f(200.f, 50.f), "Date incorecte!", font);
    Button userRect(&Button::setCenter, window.getSize(), sf::Vector2f(200.f, 50.f), "Username", font);
    TextInput textInput(&Button::setCenter, window.getSize(), sf::Vector2f(300.f, 50.f), font);
    Button passRect(&Button::setCenter, window.getSize(), sf::Vector2f(200.f, 50.f), "Password", font);
    TextInput passInput(&Button::setCenter, window.getSize(), sf::Vector2f(300.f, 50.f), font);

    // textInput.setOutlineThickness(0);
    textInput.setFillColor(sf::Color(255, 255, 255, 200));
    textInput.setOutlineColor(sf::Color(0, 0, 0, 50));

    // passInput.setOutlineThickness(0);
    passInput.setFillColor(sf::Color(255, 255, 255, 200));
    passInput.setOutlineColor(sf::Color(0, 0, 0, 50));
    passInput.setIsPassword(true);

    title->setFillColor(sf::Color(255, 255, 255, 20));
    title->setOutlineThickness(0);
    title->setTextColor(sf::Color(0, 0, 0, 250));

    errorLoginBtn.setFillColor(sf::Color::Red);
    errorLoginBtn.setOutlineColor(sf::Color::Red);

    userRect.setFillColor(sf::Color(255,255,255,150));
    // userRect.setOutlineThickness(0);
    userRect.setOutlineColor(sf::Color(0, 0, 0, 50));

    passRect.setFillColor(sf::Color(255,255,255,150));
    // passRect.setOutlineThickness(0);
    passRect.setOutlineColor(sf::Color(0, 0, 0, 50));

    std::vector<Button*> buttonsToDraw;
    buttonsToDraw.push_back(title);
    buttonsToDraw.push_back(&userRect);
    buttonsToDraw.push_back(&textInput);
    buttonsToDraw.push_back(&passRect);
    buttonsToDraw.push_back(&passInput);

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

    window.setFramerateLimit(60);
    textInput.setSelected(true);

    while (window.isOpen())
    {
        sf::Event event;
        if(loginPage)
        {
            textInput.handleEvent(event, window, keyPressed);
            passInput.handleEvent(event, window, keyPressed);
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
                            if(textInput.getSelected() && passInput.getText().empty() && textInput.getText().size()>1)
                            {
                                textInput.setSelected(false);
                                passInput.setSelected(true);
                            }
                            else
                            {
                                if(passInput.getSelected())
                                    passInput.setSelected(false);
                                if(textInput.getSelected())
                                    textInput.setSelected(false);
                                std::string user = textInput.getText();
                                std::string pass = passInput.getText();
                                
                                textInput.clearText();
                                passInput.clearText();

                                userData.name = user;
                                userData.password = pass;

                                const char* selectQuery = "SELECT * FROM users;";
                                rc = sqlite3_exec(db, selectQuery, callbackFunction, &userData, 0);
                                if(rc != SQLITE_OK)
                                {
                                    std::cout << "Error trying to connect!\n";
                                    return 0;
                                }
                                else if(!userData.gasit || userData.user == nullptr)
                                {
                                    buttonsToDraw.push_back(&errorLoginBtn);
                                    break;
                                }
                                if(userData.student)
                                {
                                    student = static_cast<Student*>(userData.user);
                                    Date* test = student->getDateOfBirth();
                                    std::cout << "Day: " << test->getDay() << "\nMonth: " << test->getMonth() << "\nYear: " << test->getYear() << "\n";
                                    studentPage = true;
                                }
                                else
                                {
                                    professor = static_cast<Professor*>(userData.user);
                                    professorPage = true;
                                }
                                std::string titleText = "Welcome, ";
                                titleText += user;
                                loginPage = false;      
                                sf::Vector2f position = title->getPosition();                          
                                delete title;
                                Button::resetButtonHeight();
                                title = new Button(position, titleText, font, 50);
                                title->setFillColor(sf::Color(0, 0, 0, 80));
                                title->setOutlineThickness(0);
                                title->setTextColor(sf::Color(255, 255, 255));
                                title->setPositionCenter(window.getSize());
                                
                                buttonsToDraw.clear();
                                buttonsToDraw.push_back(title);
                                Button* btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "", font, 28);
                                btn->setFillColor(sf::Color(255, 255, 255, 200));
                                btn->setOutlineThickness(0);
                                delete btn;
                                if(studentPage)
                                {
                                    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "Student's Data", font, 28);
                                    btn->setFillColor(sf::Color(255, 255, 255, 200));
                                    btn->setOutlineThickness(0);
                                    buttonsToDraw.push_back(btn);
                                    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "Courses", font, 28);
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
                                    title->setFillColor(sf::Color(0, 0, 0, 200));
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
                            }

                        }
                        break;
                    default:
                        break;
                }
            }

            textInput.update();
            passInput.update();

            window.clear();
            window.draw(background);
            for(auto& i : buttonsToDraw)
                i->draw(window);
            window.display();
        }
        else if(studentPage) // Mai trebuie sa centrez text-ul de la titlu din student page si professor page, 
        {               // o sa trebuiasca sa vad cum sa maresc chenarul mare astfel incat sa acopere tot text-ul
            while(window.pollEvent(event)) // si raman de facut meniurile mai departe, la student si la profesor
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
                            if(buttonsToDraw[1]->isMouseOver(window)) // Student's data
                            {
                                
                            }
                            if(buttonsToDraw[2]->isMouseOver(window)) // Courses
                            {

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
        else if(professorPage)
        {
            while(window.pollEvent(event))
            {
                auto iter = buttonsToDraw.begin();

                switch(event.type)
                {
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
                            if(buttonsToDraw[1]->isMouseOver(window)) // Professor's Data
                            {
                                
                            }
                            if(buttonsToDraw[2]->isMouseOver(window)) // GradeBook, to give grades and stuff
                            {

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
            window.draw(backgroundProfessor);
            for(auto& i : buttonsToDraw)
                i->draw(window);
            window.display();
        }
    }
    sqlite3_close(db);
    return 0;
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