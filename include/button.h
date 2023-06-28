#pragma once

#include <SFML/Graphics.hpp>
#define SPACE_BETWEEN_LINES 25
#define CHAR_SIZE 24 // the default character size for text inside the button

class Button 
{
public:
    Button();
    Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font& font, int textSize=CHAR_SIZE);
    Button(sf::Vector2f (*function)(const sf::Vector2u&, const sf::Vector2f&), const sf::Vector2u& windowSize, const sf::Vector2f& size, std::string text, sf::Font& font, int textSize=CHAR_SIZE);
    Button(sf::Vector2f position, std::string text, sf::Font& font, int textSize, const sf::Vector2f& boxThickness, bool addTotalHeight);    // If you want to use the setRight, setCenter and setLeft functions, the height will be automaticaly determined by the class itself
    // In order for you to not overwrite them and to not have to do anything with the height itself. You can change how much space you want in between
    // options by changing the SPACE_BETWEEN_LINES macro up. 25px is set by default

    bool isMouseOver(sf::RenderWindow& );
    virtual void draw(sf::RenderWindow& );
    void makeClear();
    void makeNotClear();
    void isMouseOverFunction(void (*function)(Button&), Button&);
    void setTextColor(sf::Color );
    void setFillColor(sf::Color );
    void setOutlineColor(sf::Color );
    void setOutlineThickness(float );
    void setText(const std::string&);
    void setTextPosition(const sf::Vector2f&, const sf::Vector2f&);
    void setSize(const sf::Vector2f& size);
    void setPositionCenter(const sf::Vector2u& windowSize);
    void setPosition(const sf::Vector2f&);
    void replaceText(const std::string& toReplace, const std::string& replace);
    void function();
    static sf::Vector2f setCenter(const sf::Vector2u&, const sf::Vector2f&);
    static sf::Vector2f setLeft(const sf::Vector2u&, const sf::Vector2f&);
    static sf::Vector2f setRight(const sf::Vector2u&, const sf::Vector2f&);
    static void resetButtonHeight();
    sf::Vector2f getPosition() const;
    bool isTextOutOfBounds();
private:
    sf::RectangleShape m_button;
    sf::Text m_text;
    static int m_buttonsTotalHeight;
    bool m_clear = false;
};

