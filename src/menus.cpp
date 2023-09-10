#include "menus.h"

namespace studentPage
{
    void mainPage(sqlite3* db, sf::RenderWindow& window, sf::Font& font, std::vector<Button*>& buttonsToDraw,std::vector<Button*>& dataButtons, std::vector<Button*>& gradeButtons, Student* student)
    {     
        sf::Event event;
        Button* backBtn = nullptr;
        
        sf::Texture texture;
        if(!texture.loadFromFile("img/student-page-background.jpg"))
        {
            std::cout << "Image not loaded";
        }
        sf::Sprite background(texture);

        while(window.isOpen())
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
                                backBtn->setPosition(btnPosition);
                                gradeButtons.push_back(backBtn);
                                dataButtons.push_back(buttonsToDraw[0]);
                                dataButtons.push_back(backBtn);
                            }
                            if(buttonsToDraw[1]->isMouseOver(window)) // Student's data
                            {
                                // Student data
                                dataPage(window, dataButtons, background);
                            }
                            else if(buttonsToDraw[2]->isMouseOver(window)) // Grades
                            {
                                // Student Grades
                                gradesPage(window, gradeButtons, background);
                            }
                            if(buttonsToDraw[3]->isMouseOver(window)) // Exit
                            {
                                window.close();
                            }
                        }
                        break;
                    case sf::Event::KeyPressed:
                        if(event.key.code == sf::Keyboard::Escape)
                        {
                            window.close();
                            return ;
                        }
                        break;
                }
            }
            window.clear();
            window.draw(background);

            for(auto& i : buttonsToDraw)
                i->draw(window);
            window.display();
        }
    }
    void dataPage(sf::RenderWindow& window, std::vector<Button*>& dataButtons, sf::Sprite& background)
    {
        sf::Event event;
        while(window.isOpen())
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
                        if (dataButtons[dataButtons.size()-1]->isMouseOver(window)) 
                        {
                            dataButtons[dataButtons.size()-1]->setOutlineThickness(3.f);
                            dataButtons[dataButtons.size()-1]->setOutlineColor(sf::Color::Black);
                            dataButtons[dataButtons.size()-1]->setFillColor(sf::Color(255, 255, 255, 250));
                        }
                        else
                        {
                            dataButtons[dataButtons.size()-1]->setOutlineThickness(0);
                            dataButtons[dataButtons.size()-1]->setFillColor(sf::Color(255, 255, 255, 200));
                        }
                        break;
                    case sf::Event::MouseButtonPressed:
                        if(event.mouseButton.button == sf::Mouse::Left)
                        {
                            if(dataButtons[dataButtons.size()-1]->isMouseOver(window))
                            {
                                // You pressed the back btn, go back
                                return ;
                            }
                        }
                        break;
                    case sf::Event::KeyPressed:
                        if(event.key.code == sf::Keyboard::Escape)
                        {
                            return ;
                        }
                        break;
                }
            }
            window.clear();
            window.draw(background);
            for(auto& i : dataButtons)
                i->draw(window);
            window.display();
        }
    }
    
    void gradesPage(sf::RenderWindow& window, std::vector<Button*>& gradesButtons, sf::Sprite& background)
    {
        sf::Event event;
        while(window.isOpen())
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
                        if (gradesButtons[gradesButtons.size()-1]->isMouseOver(window)) 
                        {
                            gradesButtons[gradesButtons.size()-1]->setOutlineThickness(3.f);
                            gradesButtons[gradesButtons.size()-1]->setOutlineColor(sf::Color::Black);
                            gradesButtons[gradesButtons.size()-1]->setFillColor(sf::Color(255, 255, 255, 250));
                        }
                        else
                        {
                            gradesButtons[gradesButtons.size()-1]->setOutlineThickness(0);
                            gradesButtons[gradesButtons.size()-1]->setFillColor(sf::Color(255, 255, 255, 200));
                        }
                        break;
                    case sf::Event::MouseButtonPressed:
                        if(event.mouseButton.button == sf::Mouse::Left)
                        {
                            if(gradesButtons[gradesButtons.size()-1]->isMouseOver(window))
                            {
                                return ;
                            }
                        }
                        break;
                    case sf::Event::KeyPressed:
                        if(event.key.code == sf::Keyboard::Escape)
                        {
                            return ;
                        }
                        break;
                }
            }
            window.clear();
            window.draw(background);
            for(auto& i : gradesButtons)
                i->draw(window);
            window.display();
        }
    }
}

namespace profPage
{
    void mainPage(sqlite3* db, sf::RenderWindow& window, sf::Font& font, std::vector<Button*>& buttonsToDraw, std::vector<Button*>& dataButtons, std::vector<Button*>& gradeBookButtons, Professor* professor)
    {
        sf::Event event;
        Button* backBtn = nullptr;

        sf::Texture texture;
        if(!texture.loadFromFile("img/professor-page-background.jpg"))
        {
            std::cout << "Image not loaded";
        }
         sf::Sprite background(texture);

        while(window.isOpen()) // Professor's main menu
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
                                btnPosition.y += 125.f;
                                backBtn->setPosition(btnPosition);
                                dataButtons.push_back(buttonsToDraw[0]);
                                dataButtons.push_back(backBtn);
                                gradeBookButtons.push_back(backBtn);
                                gradeBookButtons.push_back(buttonsToDraw[0]);
                            }
                            if (buttonsToDraw[1]->isMouseOver(window))  // Professor's Data
                            {
                                dataPage(window, dataButtons, background);
                                break;
                            }
                            else if (buttonsToDraw[2]->isMouseOver(window))  // GradeBook, to give grades and stuff
                            { 
                                gradesPage(window, gradeBookButtons, background, professor, font, db);
                                break;
                            }
                            else if (buttonsToDraw[3]->isMouseOver(window))  // Exit
                            { 
                                window.close();
                            }
                        }
                        break;
                    case sf::Event::KeyPressed:
                        if(event.key.code == sf::Keyboard::Escape)
                        {
                            window.close();
                            return ;
                        }
                        break;
                }
            }

            window.clear();
            window.draw(background);
            for (auto& i : buttonsToDraw)
                i->draw(window);
            window.display();
        } 
    }
    void dataPage(sf::RenderWindow& window, std::vector<Button*>& dataButtons, sf::Sprite& background)
    {
        sf::Event event;
        while(window.isOpen()) // Professor's Data
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
                        if (dataButtons[dataButtons.size()-1]->isMouseOver(window)) 
                        {
                            dataButtons[dataButtons.size()-1]->setOutlineThickness(3.f);
                            dataButtons[dataButtons.size()-1]->setOutlineColor(sf::Color::Black);
                            dataButtons[dataButtons.size()-1]->setFillColor(sf::Color(255, 255, 255, 250));
                        }
                        else
                        {
                            dataButtons[dataButtons.size()-1]->setOutlineThickness(0);
                            dataButtons[dataButtons.size()-1]->setFillColor(sf::Color(255, 255, 255, 200));
                        }
                        break;
                    case sf::Event::MouseButtonPressed:
                        if(event.mouseButton.button == sf::Mouse::Left)
                        {
                            if(dataButtons[dataButtons.size()-1]->isMouseOver(window))
                            {
                                return ;
                            }
                        }
                        break;
                    case sf::Event::KeyPressed:
                        if(event.key.code == sf::Keyboard::Escape)
                        {
                            return ;
                        }
                        break;
                }
            }
            window.clear();
            window.draw(background);
            for(auto& i : dataButtons)
                i->draw(window);
            window.display();
        }
    }
    void gradesPage(sf::RenderWindow& window, std::vector<Button*>& gradeBookButtons, sf::Sprite& background, Professor* professor, sf::Font& font, sqlite3* db)
    {
        sf::Event event;
        while(window.isOpen()) // Professor's GradeBook
        {
            while(window.pollEvent(event))
            {
                auto iter = gradeBookButtons.begin();
                switch(event.type)
                {
                    default:
                        break;
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::MouseMoved:

                        for (; iter != gradeBookButtons.end()-1; ++iter)
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
                            if(gradeBookButtons[gradeBookButtons.size()-2]->isMouseOver(window))
                            {
                                return ;
                            }
                            else
                            {
                                for(int i = 0; i<gradeBookButtons.size()-2; i++)
                                {
                                    if(gradeBookButtons[i]->isMouseOver(window))
                                    {
                                        courseStudentsList(professor->getCourses()[i], gradeBookButtons[gradeBookButtons.size()-2], window, background, professor, font, db);
                                    }
                                }
                            }
                        }
                        break;
                    case sf::Event::KeyPressed:
                        if(event.key.code == sf::Keyboard::Escape)
                        {
                            return ;
                        }
                        break;
                }
            }
            window.clear();
            window.draw(background);
            for(auto& i : gradeBookButtons)
                i->draw(window);
            window.display();
        }
    }
}

void addButtonOptions(std::vector<Button*>& buttons, const sf::Vector2f& btnSize, std::vector<std::string>& textToAdd, const sf::Vector2u& windowSize, sf::Font& font, float buttonsDistance)
{
    Button* btn;
    sf::Vector2f btnPos;
    for(auto& i : textToAdd)
    {
        btn = new Button(&Button::setCenter, windowSize, btnSize, i, font, 28);
        btn->setFillColor(sf::Color(255, 255, 255, 200));
        btn->setOutlineThickness(0);
        btnPos = btn->getPosition();
        btnPos.y += buttonsDistance;
        btn->setPosition(btnPos);
        buttons.push_back(btn);
    }
}

std::vector<Button*> userDataInfoButtons(sf::RenderWindow& window, User* user, sf::Font& font)
{
    std::string btnText;
    Button* btn;
    sf::Vector2f btnPosition;
    std::vector<Button*> menuButtons;

    Button::resetButtonHeight();

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
    menuButtons.push_back(btn);

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
    menuButtons.push_back(btn);

    btnText = "Date of Birth: " + user->getDateOfBirth()->getString();
    btn = new Button(&Button::setCenter, window.getSize(), {400.f, 50.f}, btnText, font, 28);
    btnPosition = btn->getPosition();
    btnPosition.y += 200.f;
    btn->setPosition(btnPosition);
    btn->setOutlineThickness(0);
    btn->setFillColor(sf::Color(255, 255, 255, 200));
    menuButtons.push_back(btn);

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
    menuButtons.push_back(btn);

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
    menuButtons.push_back(btn);

    return menuButtons;
}

std::vector<Button*> studentGradesButtons(sf::RenderWindow& window, Student* student, sf::Font& font, sqlite3* db)
{
    // Initializez the major with all the respective courses for the student
    Major* major = new Major;
    Button* btn;
    std::string selectQuery;
    sf::Vector2f btnPosition;
    std::vector<Button*> menuButtons;

    Button::resetButtonHeight;

    selectQuery = "SELECT * FROM major WHERE id = ";
    selectQuery += std::to_string(student->getMajorId());
    selectQuery += ";";
    
    int rc = sqlite3_exec(db, selectQuery.c_str(), getMajor, major, 0); // GetMajor gets de id and name of the major
    
    if(rc != SQLITE_OK)
    {
        std::cout << "Error trying to get the major for the student" << std::endl;
        return menuButtons;
    }

    selectQuery.replace(14, 5, "courses");
    selectQuery.replace(selectQuery.find("id"), 2, "majorId");
    MyData2 data2;
    data2.id = major->getId();
    rc = sqlite3_exec(db, selectQuery.c_str(), setMajorCourses, &data2, 0); // setMajorCourses sets the major courses up
    if(rc != SQLITE_OK)
    {
        std::cout << "Erorr trying to collect the courses for the student" << std::endl;
        return menuButtons;
    }
    major->setCourses(data2.courses);
    student->setMajor(major);

    // Once the major courses are set up we can begin building up the menu for the student page nr 2
    std::string btnText = student->getFirstName() + " " + student->getLastName() + "'s grades"; 
    Button::resetButtonHeight();
    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, btnText, font, 50);
    btn->setPositionCenter(window.getSize());
    btn->setSideToSide(window.getSize());
    btn->setFillColor(sf::Color(0, 0, 0, 125));
    btn->setOutlineThickness(0);
    btn->setTextColor(sf::Color(255, 255, 255));
    
    menuButtons.push_back(btn);

    for(auto& i : student->getMajor()->getCourses())
    {
        float grade = -1.f;
        std::string showGrade;
        selectQuery = "SELECT * FROM grades WHERE courseId = " + std::to_string(i->getId()) + " AND studentID = " + std::to_string(student->getID()) + ";";
        rc = sqlite3_exec(db, selectQuery.c_str(), getGrades, &grade, 0);
        if(rc != SQLITE_OK)
        {
            std::cout << "Error trying to get grades\n";
            return menuButtons;
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
        menuButtons.push_back(btn);
    }
    return menuButtons;
}

std::vector<Button*> profCoursesButtons(sf::RenderWindow& window, Professor* professor, sf::Font& font, sqlite3* db)
{
    // Set the Professor's courses up!
    std::vector<Course*> courses;
    std::vector<Button*> menuButtons;
    std::string selectQuery = "SELECT * FROM courses WHERE professorId = " + std::to_string(professor->getID()) + ";";
    int rc = sqlite3_exec(db, selectQuery.c_str(), getProfessorCourses, &courses, 0);
    if(rc != SQLITE_OK)
    {
        std::cout << "Error trying to get professor's courses\n";
        return menuButtons;
    }
    
    professor->setCourses(courses);

    Button::resetButtonHeight();
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
        menuButtons.push_back(btn);
    }
    return menuButtons;
}

// courseMenu
void courseStudentsList(Course* course, Button* backBtn, sf::RenderWindow& window, sf::Sprite& background, Professor* professor, sf::Font& font, sqlite3* db)
{
    // Loads up the users that attend the selected course by the professor, so the professor can give the student a grade
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

    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, course->getName(), font, 50);
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
                                    giveGradeMenu(course, students[i-2], otherButtons, window, background, font, db);
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
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape)
                    {
                        return ;
                    }

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

void giveGradeMenu(Course* course, Student* student, Button** otherButtons, sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db)
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
    textInput.setText("test", false);
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
                            if(textInput.isSelected())
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

namespace adminPage
{
    void mainPage(sf::RenderWindow& window, sf::Font& font, sqlite3* db)
    {
        std::vector<Button*> buttons;
        Button* btn;
        sf::Vector2f btnPos;
        sf::Event event;
        std::vector<std::string> options = {"Users", "Faculties", "Majors", "Courses", "Exit"};
        Button::resetButtonHeight();
        btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "Admin Page", font, 50);
        btn->setSideToSide(window.getSize());
        btn->setOutlineThickness(0);
        btn->setFillColor(sf::Color(0, 0, 0, 150));
        btn->setTextColor(sf::Color(255, 255, 255));
        buttons.push_back(btn);
        addButtonOptions(buttons, {300.f, 75.f}, options, window.getSize(), font, 50.f);

        std::vector<std::string> menusOptions = {"Add", "Modify", "Delete", "Back"};
        std::vector<Button*> mainButtons; // The buttons you see when you click users or faculties, etc..
        Button::resetButtonHeight();
        btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, "Template Page", font, 50);
        btn->setSideToSide(window.getSize());
        btn->setOutlineThickness(0);
        btn->setFillColor(sf::Color(0, 0, 0, 150));
        btn->setTextColor(sf::Color(255, 255, 255));
        mainButtons.push_back(btn);
        addButtonOptions(mainButtons, {300.f, 75.f}, menusOptions, window.getSize(), font, 50.f);

        sf::Texture texture;
        if(!texture.loadFromFile("img/admin-page-background.jpg"))
        {
            std::cout << "Image not loaded";
        }
        sf::Sprite background(texture);
        while(window.isOpen())
        {
            while(window.pollEvent(event))
            {
                auto iter = buttons.begin();
                bool btnPressed = false;
                switch(event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    ++iter;

                    for(; iter < buttons.end(); ++iter)
                    {
                        auto& i = *iter;
                        i->windowHover(window);
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Button::Left)
                    {
                        ++iter;
                        for(; iter < buttons.end(); ++iter)
                        {
                            auto& i = *iter;
                            if(i->isMouseOver(window))
                            {
                                btnPressed = true;
                                break;
                            }
                        }
                        if(btnPressed)
                        {
                            if(iter == buttons.begin()+1)
                            {
                                // "Users menu"
                                userPage(window, background, font, db, mainButtons);
                            }
                            else if(iter == buttons.begin()+2)
                            {
                                // "Faculties menu"
                                facultiesPage(window, background, font, db, mainButtons);
                            }
                            else if(iter == buttons.begin()+3)
                            {
                                // "Majors menu"
                                majorsPage(window, background, font, db, mainButtons);
                            }
                            else if(iter == buttons.begin()+4)
                            {
                                // "Courses menu"
                                coursesPage(window, background, font, db, mainButtons);
                            }
                            else if(iter == buttons.begin()+5)
                            {
                                window.close();
                                return ;
                            }
                        }
                    }
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                        return ;
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
    }

    void userPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
    {
        bool pageClosed = false;
        sf::Event event;
        mainButtons[0]->setText("User Page", true);
        while(!pageClosed && window.isOpen())
        {
            while(window.pollEvent(event))
            {
                auto iter = mainButtons.begin();
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    return ;
                    break;
                case sf::Event::MouseMoved:
                    ++iter;

                    for(; iter < mainButtons.end(); ++iter)
                    {
                        auto& i = *iter;
                        i->windowHover(window);
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Button::Left)
                    {
                        if(mainButtons[mainButtons.size()-1]->isMouseOver(window))
                        {
                            pageClosed = true;
                            return ;
                        }
                        else if(mainButtons[1]->isMouseOver(window))
                        {
                            // user add page
                            add::userPage(window, background, font, db, mainButtons[0]);
                        }
                    }
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape)
                    {
                        pageClosed = true;
                        return ;
                    }
                    break;
                default:
                    break;
                }
            }
            window.clear();
            window.draw(background);
            for(auto& i : mainButtons)
                i->draw(window);
            window.display();
        }
    }

    void facultiesPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
    {
        bool pageClosed = false;
        sf::Event event;
        mainButtons[0]->setText("Faculties Page", true);
        while(!pageClosed && window.isOpen())
        {
            while(window.pollEvent(event))
            {
                auto iter = mainButtons.begin();
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    return ;
                    break;
                case sf::Event::MouseMoved:
                    ++iter;

                    for(; iter < mainButtons.end(); ++iter)
                    {
                        auto& i = *iter;
                        i->windowHover(window);
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Button::Left)
                    {
                        if(mainButtons[mainButtons.size()-1]->isMouseOver(window))
                        {
                            pageClosed = true;
                            return ;
                        }
                    }
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape)
                    {
                        pageClosed = true;
                        return ;
                    }
                    break;
                default:
                    break;
                }
            }
            window.clear();
            window.draw(background);
            for(auto& i : mainButtons)
                i->draw(window);
            window.display();
        }
    }

    void coursesPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
    {
        bool pageClosed = false;
        sf::Event event;
        mainButtons[0]->setText("Courses Page", true);
        while(!pageClosed && window.isOpen())
        {
            while(window.pollEvent(event))
            {
                auto iter = mainButtons.begin();
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    return ;
                    break;
                case sf::Event::MouseMoved:
                    ++iter;

                    for(; iter < mainButtons.end(); ++iter)
                    {
                        auto& i = *iter;
                        i->windowHover(window);
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Button::Left)
                    {
                        if(mainButtons[mainButtons.size()-1]->isMouseOver(window))
                        {
                            pageClosed = true;
                            return ;
                        }
                    }
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape)
                    {
                        pageClosed = true;
                        return ;
                    }
                    break;
                default:
                    break;
                }
            }
            window.clear();
            window.draw(background);
            for(auto& i : mainButtons)
                i->draw(window);
            window.display();
        }
    }

    void majorsPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
    {
        bool pageClosed = false;
        sf::Event event;
        mainButtons[0]->setText("Majors Page", true);
        while(!pageClosed && window.isOpen())
        {
            while(window.pollEvent(event))
            {
                auto iter = mainButtons.begin();
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    return ;
                    break;
                case sf::Event::MouseMoved:
                    ++iter;

                    for(; iter < mainButtons.end(); ++iter)
                    {
                        auto& i = *iter;
                        i->windowHover(window);
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Button::Left)
                    {
                        if(mainButtons[mainButtons.size()-1]->isMouseOver(window))
                        {
                            pageClosed = true;
                            return ;
                        }
                    }
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape)
                    {
                        pageClosed = true;
                        return ;
                    }
                    break;
                default:
                    break;
                }
            }
            window.clear();
            window.draw(background);
            for(auto& i : mainButtons)
                i->draw(window);
            window.display();
        }
    }

    // Admin add pages
    namespace add
    {
        void userPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, Button* titleBtn)
        {
            #define BTN_SIZE {500.f, 40.f}
            #define BTN_CHAR_SIZE 25

            Button::setButtonsTotalHeight(titleBtn->getSize().y + 35.f);

            sf::Event event;
            std::vector<Button*> buttons;
            Button* btn;
            TextInput *username, *password, *firstName, *lastName, *country, *dob, *status, *gender;
            bool pageClosed = false;                                             // status reffers to wheter is a student or a prof
            bool keyPressed = false;

            // Setting up the buttons that appear on the screen
            buttons.push_back(titleBtn);
            btn = new Button(&Button::setLeft, window.getSize(), BTN_SIZE, "Enter username", font, BTN_CHAR_SIZE);
            btn->setOutlineThickness(0.0f);
            btn->setFillColor(sf::Color(255, 255, 255, 100));
            buttons.push_back(btn);
            username = new TextInput(&Button::setLeft, window.getSize(), BTN_SIZE, font, BTN_CHAR_SIZE);
            username->setOutlineThickness(0.0f);
            buttons.push_back(username);
            btn = new Button(&Button::setLeft, window.getSize(), BTN_SIZE, "Enter password", font, BTN_CHAR_SIZE);
            btn->setOutlineThickness(0.0f);
            btn->setFillColor(sf::Color(255, 255, 255, 100));
            buttons.push_back(btn);
            password = new TextInput(&Button::setLeft, window.getSize(), BTN_SIZE, font, BTN_CHAR_SIZE);
            password->setOutlineThickness(0.0f);
            buttons.push_back(password);
            btn = new Button(&Button::setLeft, window.getSize(), BTN_SIZE, "Enter first name", font, BTN_CHAR_SIZE);
            btn->setOutlineThickness(0.0f);
            btn->setFillColor(sf::Color(255, 255, 255, 100));
            buttons.push_back(btn);
            firstName = new TextInput(&Button::setLeft, window.getSize(), BTN_SIZE, font, BTN_CHAR_SIZE);
            firstName->setOutlineThickness(0.0f);
            buttons.push_back(firstName);
            btn = new Button(&Button::setLeft, window.getSize(), BTN_SIZE, "Enter last name", font, BTN_CHAR_SIZE);
            btn->setOutlineThickness(0.0f);
            btn->setFillColor(sf::Color(255, 255, 255, 100));
            buttons.push_back(btn);
            lastName = new TextInput(&Button::setLeft, window.getSize(), BTN_SIZE, font, BTN_CHAR_SIZE);
            lastName->setOutlineThickness(0.0f);
            buttons.push_back(lastName);
            Button::setButtonsTotalHeight(buttons[1]->getPosition().y);
            btn = new Button(&Button::setRight, window.getSize(), BTN_SIZE, "Enter country of origin", font, BTN_CHAR_SIZE);
            btn->setOutlineThickness(0.0f);
            btn->setFillColor(sf::Color(255, 255, 255, 100));
            buttons.push_back(btn);
            country = new TextInput(&Button::setRight, window.getSize(), BTN_SIZE, font, BTN_CHAR_SIZE);
            country->setOutlineThickness(0.0f);
            buttons.push_back(country);
            btn = new Button(&Button::setRight, window.getSize(), BTN_SIZE, "Enter date of birth(dd/mm/yyyy)", font, BTN_CHAR_SIZE);
            btn->setOutlineThickness(0.0f);
            btn->setFillColor(sf::Color(255, 255, 255, 100));
            buttons.push_back(btn);
            dob = new TextInput(&Button::setRight, window.getSize(), BTN_SIZE, font, BTN_CHAR_SIZE);
            dob->setOutlineThickness(0.0f);
            buttons.push_back(dob);
            btn = new Button(&Button::setRight, window.getSize(), BTN_SIZE, "Is student/prof?(S/s=Student, P/p=Prof)", font, BTN_CHAR_SIZE);
            btn->setOutlineThickness(0.0f);
            btn->setFillColor(sf::Color(255, 255, 255, 100));
            buttons.push_back(btn);
            status = new TextInput(&Button::setRight, window.getSize(), BTN_SIZE, font, BTN_CHAR_SIZE);
            status->setOutlineThickness(0.0f);
            buttons.push_back(status);
            btn = new Button(&Button::setRight, window.getSize(), BTN_SIZE, "Is male/female(M/m=Male, F/f=Female)", font, BTN_CHAR_SIZE);
            btn->setOutlineThickness(0.0f);
            btn->setFillColor(sf::Color(255, 255, 255, 100));
            buttons.push_back(btn);
            gender = new TextInput(&Button::setRight, window.getSize(), BTN_SIZE, font, BTN_CHAR_SIZE);
            gender->setOutlineThickness(0.0f);
            buttons.push_back(gender);
            btn = new Button(&Button::setCenter, window.getSize(), {500.f, 50.f}, "NEXT", font, 30);
            btn->setFillColor(sf::Color(255, 255, 255, 200));
            btn->setOutlineThickness(0);
            buttons.push_back(btn);
            std::vector<TextInput*> inputs = {username, password, firstName, lastName, country, dob, status, gender};
            bool isStudent = false;
            Date* DoB = nullptr;
            while(!pageClosed)
            {               
                for(auto& i : inputs)
                    i->handleEvent(event, window, keyPressed);
                while(window.pollEvent(event))
                {
                    switch(event.type)
                    {
                        case sf::Event::Closed:
                            window.close();
                            return ;
                        case sf::Event::MouseMoved:
                            btn->windowHover(window);
                            break;
                        case sf::Event::MouseButtonPressed:
                            if(event.mouseButton.button == sf::Mouse::Button::Left && btn->isMouseOver(window))
                            {
                                // This means the admin pressed next
                                /* Debugging purposes

                                bool isAnyOptionWrong = false;
                                for(auto& i : inputs)
                                {
                                    if(i->isSelected())
                                        i->setSelected(false);
                                    if(i->getText().empty()) // Checks if an input box is empty
                                    {
                                        i->setOutlineThickness(3.f);
                                        i->setOutlineColor(sf::Color::Red);
                                        isAnyOptionWrong = true;
                                    }
                                    else if(i->isOutlined()) // Checks if an input box was empty before and now it's not empty anymore
                                    {
                                        i->setOutlineThickness(0.f);
                                    }
                                    
                                    if(i == dob)
                                    {
                                        std::istringstream ss(dob->getText());
                                        std::string day, month, year;

                                        std::getline(ss, day, '/');
                                        std::getline(ss, month, '/');
                                        std::getline(ss, year);

                                        if((day.empty() || month.empty() || year.empty()) || (day.size() > 2 || month.size() > 2 || year.size() != 4))
                                        {
                                            i->setOutlineThickness(3.f);
                                            i->setOutlineColor(sf::Color::Red);
                                            isAnyOptionWrong = true;
                                        }
                                        else
                                        {
                                            try
                                            {
                                                int int_day = std::stoi(day);
                                                int int_month = std::stoi(month);
                                                int int_year = std::stoi(year);
                                                DoB = new Date(int_day, int_month, int_year);
                                            }
                                            catch(const std::exception& e)
                                            {
                                                isAnyOptionWrong = true;
                                                i->setOutlineThickness(3.f);
                                                i->setOutlineColor(sf::Color::Red);
                                            }
                                        }
                                    }
                                    else if(i == status)
                                    {
                                        char c = static_cast<char>(std::tolower(status->getText()[0]));
                                        if(c != 'p' && c != 's')
                                        {
                                            // Typed something other than p or s in the input box
                                            i->setOutlineThickness(3.f);
                                            i->setOutlineColor(sf::Color::Red);
                                            isAnyOptionWrong = true;
                                        }
                                        else if(c == 's')
                                        {
                                            isStudent = true;
                                        }
                                    }
                                    else if(i == gender)
                                    {
                                        char c = static_cast<char>(std::tolower(gender->getText()[0]));
                                        if(c != 'm' && c != 'f')
                                        {
                                            // Typed something other than p or s in the input box
                                            i->setOutlineThickness(3.f);
                                            i->setOutlineColor(sf::Color::Red);
                                            isAnyOptionWrong = true;
                                        }
                                    }
                                }
                                */
                                if(true)//(!isAnyOptionWrong)
                                {
                                    // bool isMale = (static_cast<char>(std::tolower(gender->getText()[0])) == 'm') ? true : false;
                                    // User* user = new User(username->getText(), firstName->getText(), lastName->getText(), country->getText(), isMale, DoB);
                                    bool isMale = true;
                                    Date* dob = new Date(10, 10, 10);
                                    User* user = new User("test", "test", "test", "test", true, dob);
                                    isStudent = true;
                                    // All the options are right, now I need to have 2 different screens, 1 for student, 1 for professor
                                    // In case of the student I have to select it's major, and for the professor I need to select the courses the prof will be teaching
                                    if(isStudent)
                                    {
                                        // Here will go the student screen
                                        // Will be 2 screens, 1 where you select the user faculty and another
                                        // where you select the major by the faculty already selected
                                        studentMenu(window, background, font, db, titleBtn, user);
                                    }
                                    else
                                    {
                                        // Here will go the prof screen
                                        professorMenu(window, background, font, db, titleBtn, user);
                                    }
                                    if(!window.isOpen())
                                        return ;
                                }
                            }
                            break;
                        case sf::Event::KeyPressed:
                            if(event.key.code == sf::Keyboard::Escape)
                            {
                                // Will have to find a way to delete the buttons when I exit the page
                                return ;
                            }
                            break;
                    }
                }
                for(auto& i : inputs)
                    i->update();
                window.clear();
                window.draw(background);
                for(auto& i : buttons)
                    i->draw(window);
                window.display();
            }
        }
        void facultyPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
        {
            
        }
        void coursePage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
        {
            
        }
        void majorPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
        {
            
        }
        void studentMenu(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, Button* titleBtn, User* user)
        {
            sf::Event event;

            // First I will need to create a menu to select from the different faculties
            // And then I will need to create another menu to select a major from that faculty

            bool isFacultyMenu = true;
            bool isMajorMenu = false;

            std::vector<Faculty*> facultiesOptions;
            std::vector<Button*> facultiesButtons;
            std::vector<Major*> majorsOptions;
            std::vector<Button*> majorsButtons;
            Button* btn, *backBtn;

            facultiesButtons.push_back(titleBtn);
            majorsButtons.push_back(titleBtn);

            backBtn = new Button({490.f, 635.f}, {300.f, 75.f}, "Back", font);

            facultiesButtons.push_back(backBtn);
            majorsButtons.push_back(backBtn);

            Button::setButtonsTotalHeight(titleBtn->getSize().y + 35.f);

            int rc = sqlite3_exec(db, "SELECT * FROM faculties;", getAllFaculties, &facultiesOptions, 0);

            if(rc != SQLITE_OK)
            {
                std::cout << "There was an error trying to get the faculties for the student add page";
                return ;
            }

            if(facultiesOptions.size() < 6) 
            {   // In case we only have 5 options, we can show them in the center as such
                for(auto& i : facultiesOptions)
                {
                    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 75.f}, i->getName(), font);
                    btn->setOutlineThickness(0);
                    btn->setFillColor(sf::Color(255, 255, 255, 200));
                    facultiesButtons.push_back(btn);
                }
            }
            else
            {   // In case we have more than 5 options, we will arrange the options from left->center->right
                int k = 0;
                for(int j = 0; (j < 5) && (k < facultiesOptions.size()); ++j, ++k)
                {
                    btn = new Button(&Button::setLeft, window.getSize(), {300.f, 75.f}, facultiesOptions[k]->getName(), font);
                    btn->setOutlineThickness(0);
                    btn->setFillColor(sf::Color(255, 255, 255, 200));
                    facultiesButtons.push_back(btn);
                }
                Button::setButtonsTotalHeight(titleBtn->getSize().y + 35.f);
                for(int j = 0; (j < 5) && (k < facultiesOptions.size()); ++j, ++k)
                {
                    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 75.f}, facultiesOptions[k]->getName(), font);
                    btn->setOutlineThickness(0);
                    facultiesButtons.push_back(btn);
                }
                Button::setButtonsTotalHeight(titleBtn->getSize().y + 35.f);
                for(int j = 0; (j < 5) && (k < facultiesOptions.size()); ++j, ++k)
                {
                    btn = new Button(&Button::setRight, window.getSize(), {300.f, 75.f}, facultiesOptions[k]->getName(), font);
                    btn->setFillColor(sf::Color(255, 255, 255, 200));
                    facultiesButtons.push_back(btn);
                }
            }

            while(window.isOpen())
            {
                while(isFacultyMenu)
                {
                    while(window.pollEvent(event))
                    {
                        auto iter = facultiesButtons.begin();

                        switch(event.type)
                        {
                            default:
                                break;
                            case sf::Event::Closed:
                                window.close();
                                return ;
                                break;
                            case sf::Event::KeyPressed:
                                if(event.key.code == sf::Keyboard::Escape)
                                {
                                    return ;
                                }
                                break;
                            case sf::Event::MouseMoved:
                                ++iter; 

                                for(; iter < facultiesButtons.end(); ++iter)
                                {
                                    auto& i = *iter;
                                    i->windowHover(window);
                                }
                                break;
                            case sf::Event::MouseButtonPressed:
                                if(event.mouseButton.button == sf::Mouse::Button::Left)
                                {
                                    if(backBtn->isMouseOver(window))
                                    {
                                        return ;
                                    }
                                    ++iter;

                                    for(; iter < facultiesButtons.end(); ++iter)
                                    {
                                        auto& i = *iter;
                                        if(i->isMouseOver(window))
                                        {
                                            // std::distance calculates the distance between the back button and the actual iterator
                                            // so I know at what distance I am at, so I can get the id for that faculty
                                            auto index = std::distance(facultiesButtons.begin()+2, iter);

                                            int facultyId =  facultiesOptions[index]->getId();
                                            std::string majorsQuery = "SELECT * FROM major WHERE facultyId = " + std::to_string(facultyId) + ";";

                                            rc = sqlite3_exec(db, majorsQuery.c_str(), getMajorByFacultyId, &majorsOptions, 0);

                                            if(rc != SQLITE_OK)
                                            {
                                                std::cout << "There was an error trying to extract the majors from the database\n";
                                                return ;
                                            }

                                            Button::setButtonsTotalHeight(titleBtn->getSize().y + 35.f);


                                            if(majorsOptions.size() < 6) 
                                            {   // In case we only have 5 options, we can show them in the center as such
                                                for(auto& i : majorsOptions)
                                                {
                                                    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 75.f}, i->getName(), font);
                                                    btn->setOutlineThickness(0);
                                                    btn->setFillColor(sf::Color(255, 255, 255, 200));
                                                    majorsButtons.push_back(btn);
                                                }
                                            }
                                            else
                                            {   // In case we have more than 5 options, we will arrange the options from left->center->right
                                                int k = 0;
                                                for(int j = 0; (j < 5) && (k < majorsOptions.size()); ++j, ++k)
                                                {
                                                    btn = new Button(&Button::setLeft, window.getSize(), {300.f, 75.f}, majorsOptions[k]->getName(), font);
                                                    btn->setOutlineThickness(0);
                                                    btn->setFillColor(sf::Color(255, 255, 255, 200));
                                                    majorsButtons.push_back(btn);
                                                }
                                                Button::setButtonsTotalHeight(titleBtn->getSize().y + 35.f);
                                                for(int j = 0; (j < 5) && (k < majorsOptions.size()); ++j, ++k)
                                                {
                                                    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 75.f}, majorsOptions[k]->getName(), font);
                                                    btn->setOutlineThickness(0);
                                                    majorsButtons.push_back(btn);
                                                }
                                                Button::setButtonsTotalHeight(titleBtn->getSize().y + 35.f);
                                                for(int j = 0; (j < 5) && (k < majorsOptions.size()); ++j, ++k)
                                                {
                                                    btn = new Button(&Button::setRight, window.getSize(), {300.f, 75.f}, majorsOptions[k]->getName(), font);
                                                    btn->setFillColor(sf::Color(255, 255, 255, 200));
                                                    majorsButtons.push_back(btn);
                                                }
                                            }
                                            isMajorMenu = true;
                                            isFacultyMenu = false;
                                            break;
                                        }
                                    }
                                }
                                break;
                        }
                    }
                    window.clear();
                    window.draw(background);

                    for(auto& i : facultiesButtons)
                        i->draw(window);

                    window.display();
                }
                while(isMajorMenu)
                {
                    while(window.pollEvent(event))
                    {
                        auto iter = majorsButtons.begin();

                        switch(event.type)
                        {
                            case sf::Event::Closed:
                                window.close();
                                return ;
                                break;
                            case sf::Event::MouseMoved:
                                ++iter; 

                                for(; iter < majorsButtons.end(); ++iter)
                                {
                                    auto& i = *iter;
                                    i->windowHover(window);
                                }
                                break;
                            case sf::Event::MouseButtonPressed:
                                if(event.mouseButton.button == sf::Mouse::Button::Left)
                                {
                                    if(backBtn->isMouseOver(window))
                                    {
                                        isFacultyMenu = true;
                                        isMajorMenu = false;
                                        for(int i = 0; i < majorsOptions.size(); i++)
                                        {
                                            delete majorsButtons[majorsButtons.size()-1];
                                            majorsButtons.pop_back();
                                        }                                        
                                        majorsOptions.clear();
                                        break;
                                    }
                                    else
                                    {
                                        ++iter;

                                        for(; iter < majorsButtons.end(); ++iter)
                                        {
                                            auto& i = *iter;
                                            if(i->isMouseOver(window))
                                            {
                                                // std::distance calculates the distance between the back button and the actual iterator
                                                // so I know at what distance I am at, so I can get the id for that faculty
                                                auto index = std::distance(majorsButtons.begin()+2, iter);

                                                int majorId =  majorsOptions[index]->getId();

                                                // This means that now I have all the data I need to add the user to the data base!
                                                // The default password will be newUser123 I will create an option in the login page
                                                // To reset your password, but for now this will do
                                                std::string defaultPassword = "newUser123";

                                                std::string sqlQuery = "INSERT INTO users (username, password, student, majorId, firstName, lastName, birthDay, birthMonth, birthYear, sexM, countryOrigin) VALUES ('" + 
                                                                        user->getUsername() + "', '" + defaultPassword + "', '" + "1'" + ", '" + std::to_string(majorId) + "', '" + user->getFirstName() + "', '" + 
                                                                        user->getLastName() + "', '" + std::to_string(user->getDateOfBirth()->getDay()) + "', '" + std::to_string(user->getDateOfBirth()->getMonth()) +
                                                                        "', '" + std::to_string(user->getDateOfBirth()->getYear()) + "', '" + (user->isMale() ? "1" : "0") + "', '" + user->getCountryOrigin() + "');";
                                                
                                                rc = sqlite3_exec(db, sqlQuery.c_str(), 0, 0, 0);
                                                if(rc != SQLITE_OK)
                                                {
                                                    std::cout << "There was an error trying to add the user to the database\n";
                                                }
                                                else
                                                {
                                                    // This means the user was added with success!
                                                    
                                                }
                                            }
                                        }
                                    }
                                }
                                break;
                            case sf::Event::KeyPressed:
                                if(event.key.code == sf::Keyboard::Escape)
                                {
                                    isFacultyMenu = true;
                                    isMajorMenu = false;
                                    for(int i = 0; i < majorsOptions.size(); i++)
                                    {
                                        delete majorsButtons[majorsButtons.size()-1];
                                        majorsButtons.pop_back();
                                    }
                                    majorsOptions.clear();
                                    break;
                                }
                        }
                    }
                    window.clear();
                    window.draw(background);

                    for(auto& i : majorsButtons)
                        i->draw(window);

                    window.display();
                }
            }      
        }
        void professorMenu(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, Button* titleBtn, User* user)
        {
            
        }
    }

    // admin modify pages
    namespace modify
    {
        void userPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
        {
            
        }
        void facultyPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
        {
            
        }
        void coursePage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
        {
            
        }
        void majorPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
        {
            
        }
    }

    // admin delete pages
    namespace del
    {
        void userPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
        {
            
        }
        void facultyPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
        {
            
        }
        void coursePage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
        {
            
        }
        void majorPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
        {
            
        }
    }
}