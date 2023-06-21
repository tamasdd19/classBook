#pragma once

#include <SFML/Graphics.hpp>
#include "button.h"
#define CHAR_SIZE 24

class TextInput : public Button
{
public:
    TextInput(sf::Vector2f position, sf::Vector2f size, sf::Font& font, int textSize=CHAR_SIZE);
    TextInput(sf::Vector2f (*function)(const sf::Vector2u&, const sf::Vector2f&), const sf::Vector2u& windowSize, sf::Vector2f size, sf::Font& font, int textSize=CHAR_SIZE);
    void deleteCharacter();
    void appendCharacter(const char&);
    void update();
    void removeCursor();
    void addCursor();
    void clearText();
    // void restartCursorTimer();
    // Getters
    bool getSelected() const;
    std::string getText() const;
    // Setters
    void setSelected(bool);
private:
    std::string m_text;
    bool m_selected;
    // bool m_showCursor;
    // sf::Clock m_cursorTimer; IDEEA FOR THE FUTURE

    // static const sf::Time CURSOR_BLINK_TIME;
};