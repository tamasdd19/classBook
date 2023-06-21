#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>
#include <string.h>
#include "button.h"
#include "input.h"
#include "professor.h"
#include "student.h"
#include "course.h"
#include "sql/sqlite3.h"

#define SLEEP_TIME 0

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "ClassBook", sf::Style::Titlebar | sf::Style::Close);

    sf::Font font;
    font.loadFromFile("src/arial.ttf");

    Button button(&Button::setCenter, window.getSize(), sf::Vector2f(300.f, 100.f), "ClassBook!", font, 35);
    Button button2(&Button::setLeft, window.getSize(), sf::Vector2f(200.f, 50.f), "buton2", font);
    Button button3(&Button::setLeft, window.getSize(), sf::Vector2f(200.f, 50.f), "buton3", font);
    TextInput textInput(&Button::setCenter, window.getSize(), sf::Vector2f(300.f, 50.f), font);
    TextInput passInput(&Button::setCenter, window.getSize(), sf::Vector2f(300.f, 50.f), font);



    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if(textInput.isMouseOver(window))
                        {   // this works, great! 
                            textInput.setSelected(true);
                            textInput.addCursor();
                        }
                        else
                        {
                            if(textInput.getSelected())
                            {
                                textInput.setSelected(false);
                                textInput.removeCursor();
                            }
                        }
                    }
                    break;
            case sf::Event::TextEntered:
                if (event.text.unicode < 128 && textInput.getSelected())
                {
                    if (event.text.unicode == '\b' && !textInput.getText().empty()) // Handle backspace
                    {
                        textInput.deleteCharacter();
                    }
                    else
                    {
                        textInput.appendCharacter(static_cast<char>(event.text.unicode));
                    }
                }
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Return)
                {
                    if(textInput.getSelected())
                    {
                        textInput.removeCursor();
                        textInput.setSelected(false);
                    }
                    std::cout << textInput.getText() << std::endl;
                    textInput.clearText();
                }
                break;
            default:
                break;
            }
        }

        textInput.update();

        window.clear();
        textInput.draw(window);
        passInput.draw(window);
        button.draw(window);
        window.display();
    }

    return 0;
}


/*
struct myData
{
    std::string name, password;
    bool gasit = false;
};

bool login = false;
User* user;

int callbackFunction(void* data, int argc, char** argv, char** columnNames) 
{
    myData* mydata = static_cast<myData*>(data);
    for (int i = 0; i < argc; i++) 
    {
        if(!strcmp(columnNames[i], "name"))
        {
            std::string checkName = argv[i];
            if(checkName == mydata->name)
            {
                mydata->gasit = true;
                std::string checkPass = argv[i+1];
                if(checkPass == mydata->password) // User has logged in
                {
                    if(std::stoi(argv[i+2]))
                    {
                        user = new Student(mydata->name, std::stoi(argv[i+3]));
                    }
                    else
                    {
                        user = new Professor(mydata->name);
                    }
                    user->setId(std::stoi(argv[i-1]));
                    std::cout << user->getName() << " has logged in!\n";
                    login = true;
                    break;
                }
                else
                {
                    std::cout << "Incorrect password!\n";
                    break;
                }
            }
        }
    }
    return 0;
}

int getMajor(void* data, int argc, char** argv, char** columnNames) 
{
    Major* major = static_cast<Major*>(data);
    major->setId(std::stoi(argv[0]));
    major->setName(argv[1]);
    std::cout << major->getName();
    major->setYear(std::stoi(argv[2]));
    major->setFacultyId(std::stoi(argv[3]));
    return 0;
}

struct MyData2
{
    std::vector<Course*> courses;
    int id;
};

int setMajorCourses(void* data, int argc, char** argv, char** columnNames) 
{
    MyData2* data2 = static_cast<MyData2*>(data);
    Course* course;
    course = new Course(std::stoi(argv[0]), argv[1], data2->id);
    data2->courses.push_back(course);
    return 0;
}

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