#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>
#include "button.h"
#include "professor.h"
#include "student.h"
#include "course.h"
#include "sql/sqlite3.h"

/*#define SLEEP_TIME 0

int main()
{
    /*
    sf::RenderWindow window(sf::VideoMode(640, 480), "Testing!");//, sf::Style::Titlebar | sf::Style::Close);
    sf::Font font;
    font.loadFromFile("src/arial.ttf");
    std::string text="da";
    bool apasat = false;

    Button button(&Button::setCenter, window.getSize(), sf::Vector2f(200.f, 50.f), "Catalog online yay", font);
    Button button2(&Button::setLeft, window.getSize(), sf::Vector2f(200.f, 50.f),  "buton2", font);
    Button button3(&Button::setLeft, window.getSize(), sf::Vector2f(200.f, 50.f),  "buton3", font);

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        window.clear();
        button.draw(window);
        window.display();
    }
    
    
    return 0;
}*/

int callbackFunction(void* data, int argc, char** argv, char** columnNames) {
    int* match = static_cast<int*>(data); // Cast the data pointer to an integer pointer

    // Process each row of the result
    for (int i = 0; i < argc; i++) {
        // Compare the ID and password values
        if (std::stoi(argv[0]) == match[0] && std::string(argv[2]) == match[1]) {
            // ID and password match
            *match = 1;
            break;
        }
    }

    return 0;
}

int main() {
    Major major("Info", 1);
    Student student("Test", major), student2;
    sqlite3* db;
    int rc = sqlite3_open("database.db", &db); // Open the database file

    if (rc == SQLITE_OK) {
        // Database opened successfully

        // Execute SQL queries

        // ... (Create table and insert data queries)

        if (rc == SQLITE_OK) {
            int id;
            std::string parola;
            std::cout << "Enter ID: ";
            std::cin >> id;
            std::cout << "Enter password: ";
            std::cin >> parola;

            int match = 0; // Variable to track if ID and password match
            int inputData[2] = { id, parola }; // Create an array to store the ID and password

            const char* selectQuery = "SELECT * FROM users;";
            rc = sqlite3_exec(db, selectQuery, callbackFunction, &match, 0);

            if (rc == SQLITE_OK) {
                if (match == 1) {
                    std::cout << "ID and password match." << std::endl;
                } else {
                    std::cout << "ID and password do not match." << std::endl;
                }
            }
        }

        // Close the database
        sqlite3_close(db);
    }

    return 0;
}
