#include "menus.h"

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
    btn = new Button(&Button::setCenter, window.getSize(), {300.f, 100.f}, btnText, font, 50);
    btn->setPositionCenter(window.getSize());
    btn->setSideToSide(window.getSize());
    btn->setFillColor(sf::Color(0, 0, 0, 125));
    btn->setOutlineThickness(0);
    btn->setTextColor(sf::Color(255, 255, 255));
    
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

void adminPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db)
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
                            adminUserPage(window, background, font, db, mainButtons);
                        }
                        else if(iter == buttons.begin()+2)
                        {
                            // "Faculties menu"
                            adminFacultiesPage(window, background, font, db, mainButtons);
                        }
                        else if(iter == buttons.begin()+3)
                        {
                            // "Majors menu"
                            adminMajorsPage(window, background, font, db, mainButtons);
                        }
                        else if(iter == buttons.begin()+4)
                        {
                            // "Courses menu"
                            adminCoursesPage(window, background, font, db, mainButtons);
                        }
                        else if(iter == buttons.begin()+5)
                        {
                            window.close();
                            return ;
                        }
                    }
                }
            }
        }
        window.clear();
        window.draw(background);
        for(auto& i : buttons)
            i->draw(window);
        window.display();
    }
}

void adminUserPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
{
    bool pageClosed = false;
    sf::Event event;
    mainButtons[0]->setText("User Page", true);
    while(!pageClosed)
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
                    }
                }
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

void adminFacultiesPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
{
    bool pageClosed = false;
    sf::Event event;
    mainButtons[0]->setText("Faculties Page", true);
    while(!pageClosed)
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

void adminCoursesPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
{
    bool pageClosed = false;
    sf::Event event;
    mainButtons[0]->setText("Courses Page", true);
    while(!pageClosed)
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

void adminMajorsPage(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sqlite3* db, std::vector<Button*>& mainButtons)
{
    bool pageClosed = false;
    sf::Event event;
    mainButtons[0]->setText("Majors Page", true);
    while(!pageClosed)
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
namespace adminAdd
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

// admin modify pages
namespace adminModify
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
namespace adminDelete
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