#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string.h>
#include "button.h"
#include "input.h"
#include "databaseStuff.h"
#include "menus.h"


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
    std::vector<Button*> buttonsToDraw;

    // Front End stuff setups
    sf::RenderWindow window(sf::VideoMode(1280, 720), "ClassBook", sf::Style::Titlebar | sf::Style::Close);

    sf::Font font;
    font.loadFromFile("src/arial.ttf");

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

    Button* btn = nullptr;
    Button* backBtn = nullptr;

    window.setFramerateLimit(60);

    LoginData* userData = loginPage(db, window, font, buttonsToDraw);

    if(userData->isAdmin) // Admin side
    {
        adminPage(window, font, db);
        return 0;
    }

    std::vector<Button*> userDataInfo = userDataInfoButtons(window, userData->user, font);


    if(userData->isStudent) // Student side
    {
        std::vector<Button*> gradeButtons;

        gradeButtons = studentGradesButtons(window, userData->student, font, db);

        studentPage::mainPage(db, window, font, backgroundStudent, buttonsToDraw, userDataInfo, gradeButtons, userData->student);   
    }
    else // Professor side
    {
        std::vector<Button*> gradeBookButtons;

        gradeBookButtons = profCoursesButtons(window, userData->professor, font, db);

        profPage::mainPage(db, window, font, backgroundProfessor, buttonsToDraw, userDataInfo, gradeBookButtons, userData->professor);
    }

/*

        else if(studentPage)  
        {
            
            
        }
        else if(professorPage)
        {
            
            
            else if(menus[2]) // Professor's GradeBook
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
                            break;
                        case sf::Event::KeyPressed:
                            if(event.key.code == sf::Keyboard::Escape)
                            {
                                menus[2] = false;
                                menus[0] = true;
                            }
                            break;
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
    */
    sqlite3_close(db);
    return 0;
}
