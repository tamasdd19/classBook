#include "button.h"
#include <iostream>

int Button::m_buttonsTotalHeight = SPACE_BETWEEN_LINES;

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font& font) 
{
    m_button.setSize(size);
    m_button.setPosition(position);
    m_button.setFillColor(sf::Color::White);
    m_button.setOutlineThickness(2.f);
    m_button.setOutlineColor(sf::Color::Black);

    m_text.setFont(font);
    m_text.setString(text);
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    m_text.setPosition(position.x + size.x / 2.f, position.y + size.y / 2.f);
    Button::m_buttonsTotalHeight+=size.y + SPACE_BETWEEN_LINES;
}

Button::Button(sf::Vector2f (*function)(const sf::Vector2u&, const sf::Vector2f&), const sf::Vector2u& windowSize, sf::Vector2f size, std::string text, sf::Font& font)
{
    sf::Vector2f position=function(windowSize, size);
    new (this) Button(position, size, text, font);
}

sf::Vector2f Button::setCenter(const sf::Vector2u& windowSize, const sf::Vector2f& size)
{
    sf::Vector2f toReturn;
    toReturn.x = windowSize.x / 2.f - size.x / 2.f;
    toReturn.y = Button::m_buttonsTotalHeight;
    std::cout << toReturn.x << "   " << toReturn.y << std::endl;
    return toReturn;
}

sf::Vector2f Button::setLeft(const sf::Vector2u& windowSize, const sf::Vector2f& size)
{
    sf::Vector2f toReturn;
    toReturn.x = 0.05f * windowSize.x;
    toReturn.y = Button::m_buttonsTotalHeight;
    std::cout << toReturn.x << "   " << toReturn.y << std::endl;
    return toReturn;
}

sf::Vector2f Button::setRight(const sf::Vector2u& windowSize, const sf::Vector2f& size)
{
    sf::Vector2f toReturn;
    toReturn.x = windowSize.x - 0.05f * windowSize.x - size.x;
    toReturn.y = Button::m_buttonsTotalHeight;
    std::cout << toReturn.x << "   " << toReturn.y << std::endl;
    return toReturn;
}

void Button::draw(sf::RenderWindow& window) 
{
    if(!m_clear)
        window.draw(m_button);
    window.draw(m_text);
}
bool Button::isMouseOver(sf::RenderWindow& window) 
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::FloatRect buttonBounds = m_button.getGlobalBounds();
    return buttonBounds.contains(mousePos);
}

void Button::setTextColor(sf::Color color)
{
    m_text.setFillColor(color);
}

void Button::makeClear()
{
    this->setTextColor(sf::Color::White);
    m_clear = true;
}

void Button::makeNotClear()
{
    this->setTextColor(sf::Color::Black);
    m_clear = false;
}

void Button::setFillColor(sf::Color color) 
{
    m_button.setFillColor(color);
}

void Button::setOutlineColor(sf::Color color) 
{
    m_button.setOutlineColor(color);
}

void Button::setOutlineThickness(float thickness) 
{
    m_button.setOutlineThickness(thickness);
}

void Button::function()
{

}

void Button::isMouseOverFunction(void (*function)(Button&), Button& b)
{
    function(b);
}