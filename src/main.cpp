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
    // Process each row of the result
    for (int i = 0; i < argc; i++) {
        // Print column name and value
        std::cout << columnNames[i] << ": " << argv[i] << std::endl;
    }
    std::cout << std::endl;

    return 0;
}

int main()
{
    Major major("Info", 1);
    Student student("Test", major), student2;
    sqlite3* db;
    int rc = sqlite3_open("database.db", &db); // Open the database file

    if (rc == SQLITE_OK) {
        // Database opened successfully

        // Execute SQL queries
        const char* createTableQuery = "CREATE TABLE IF NOT EXISTS MyTable (ID INT, Name TEXT);";
        rc = sqlite3_exec(db, createTableQuery, 0, 0, 0);

        if (rc == SQLITE_OK) {
            // Table created successfully

            // Execute more SQL queries, e.g., insert data
            // const char* insertQuery = "INSERT INTO MyTable (ID, Name) VALUES (1, 'John');";
            // rc = sqlite3_exec(db, insertQuery, 0, 0, 0);

            if (rc == SQLITE_OK) {
                // Data inserted successfully

                // Query data
                const char* selectQuery = "SELECT * FROM MyTable;";
                rc = sqlite3_exec(db, selectQuery, callbackFunction, 0, 0);
                // You would need to define the callback function to process the query results
            }
        }

        // Close the database
        sqlite3_close(db);
    }

    return 0;
}