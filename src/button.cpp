#include "button.h"
#include <iostream>

int Button::m_buttonsTotalHeight = SPACE_BETWEEN_BUTTONS;

void Button::resetButtonHeight()
{
    m_buttonsTotalHeight = SPACE_BETWEEN_BUTTONS;
}

Button::Button()
{

}

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font& font, int textSize) 
{
    m_button.setSize(size);
    m_button.setPosition(position);
    m_button.setFillColor(sf::Color::White);
    m_button.setOutlineThickness(2.f);
    m_button.setOutlineColor(sf::Color::Black);

    m_text.setFont(font);
    m_text.setString(text);
    m_text.setCharacterSize(textSize);
    m_text.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    m_text.setPosition(position.x + size.x / 2.f, position.y + size.y / 2.f);
    Button::m_buttonsTotalHeight+=size.y + SPACE_BETWEEN_BUTTONS;
}

Button::Button(sf::Vector2f (*function)(const sf::Vector2u&, const sf::Vector2f&), const sf::Vector2u& windowSize, const sf::Vector2f& size, std::string text, sf::Font& font, int textSize)
{
    sf::Vector2f position=function(windowSize, size);
    new (this) Button(position, size, text, font, textSize);
}

Button::Button(sf::Vector2f position, std::string text, sf::Font& font, int textSize, const sf::Vector2f& boxThickness, bool addTotalHeight)
{
    m_text.setFont(font);
    m_text.setString(text);
    m_text.setCharacterSize(textSize);
    m_text.setFillColor(sf::Color::Black);

    // Calculate the size of the button based on the size of the text
    sf::FloatRect textRect = m_text.getLocalBounds();
    sf::Vector2f buttonSize(textRect.width + boxThickness.x, textRect.height + boxThickness.y);

    m_button.setSize(buttonSize);
    m_button.setPosition(position);
    m_button.setFillColor(sf::Color::White);
    m_button.setOutlineThickness(2.f);
    m_button.setOutlineColor(sf::Color::Black);

    // Center the text within the button
    m_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    m_text.setPosition(position.x + buttonSize.x / 2.f, position.y + buttonSize.y / 2.f);

    if(addTotalHeight)
        Button::m_buttonsTotalHeight += buttonSize.y + SPACE_BETWEEN_BUTTONS;
}

sf::Vector2f Button::setCenter(const sf::Vector2u& windowSize, const sf::Vector2f& size)
{
    sf::Vector2f toReturn;
    toReturn.x = windowSize.x / 2.f - size.x / 2.f;
    toReturn.y = Button::m_buttonsTotalHeight;
    return toReturn;
}

sf::Vector2f Button::setLeft(const sf::Vector2u& windowSize, const sf::Vector2f& size)
{
    sf::Vector2f toReturn;
    toReturn.x = 0.05f * windowSize.x;
    toReturn.y = Button::m_buttonsTotalHeight;
    return toReturn;
}

sf::Vector2f Button::setRight(const sf::Vector2u& windowSize, const sf::Vector2f& size)
{
    sf::Vector2f toReturn;
    toReturn.x = windowSize.x - 0.05f * windowSize.x - size.x;
    toReturn.y = Button::m_buttonsTotalHeight;
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

void Button::setPosition(const sf::Vector2f& position)
{
    m_button.setPosition(position);
    sf::FloatRect textRect = m_text.getLocalBounds();
    sf::Vector2f buttonSize = m_button.getSize();
    m_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    m_text.setPosition(position.x + buttonSize.x / 2.f, position.y + buttonSize.y / 2.f);
}

void Button::setButtonPosition(const sf::Vector2f& position)
{
    m_button.setPosition(position);
}

void Button::setSideToSide(const sf::Vector2u& windowSize)
{
    m_button.setPosition({0.0f, m_button.getPosition().y}); // Sets the Button to be side-to-side
    m_button.setSize({static_cast<float>(windowSize.x), m_button.getSize().y});
}


void Button::replaceText(const std::string& toReplace, const std::string& replace)
{
    std::string replacement = m_text.getString();
    replacement.replace(replacement.find(toReplace), toReplace.size(), replace);
    m_text.setString(replacement);
}

void Button::function()
{

}

void Button::isMouseOverFunction(void (*function)(Button&), Button& b)
{
    function(b);
}

sf::Vector2f Button::getPosition() const
{
    return m_button.getPosition();
}

sf::Vector2f Button::getSize() const
{
    return m_button.getSize();
}

void Button::setText(const std::string& text, const bool& setCenter)
{
    m_text.setString(text);
    if(setCenter)
    {
        sf::FloatRect textRect = m_text.getLocalBounds();
        sf::Vector2f position = this->getPosition();
        sf::Vector2f size = this->getSize();
        m_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
        m_text.setPosition(position.x + size.x / 2.f, position.y + size.y / 2.f);
    }
}

void Button::setTextPosition(const sf::Vector2f& position, const sf::Vector2f& size)
{
    m_text.setPosition(position.x, position.y + 0.25*size.y);
}   

void Button::setSize(const sf::Vector2f& size)
{
    m_button.setSize(size);
}

void Button::setPositionCenter(const sf::Vector2u& windowSize)
{
    float x = windowSize.x / 2.f - m_button.getSize().x / 2.f;
    float y = m_button.getPosition().y; // Preserve the original y position of the button

    sf::FloatRect textRect = m_text.getLocalBounds();
    sf::Vector2f size = m_button.getSize();
    m_button.setPosition({x, y}); // Set the new centered position of the button

    // Recalculate the position of the text based on the new centered position of the button
    sf::Vector2f position = m_button.getPosition();
    m_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    m_text.setPosition(position.x + size.x / 2.f, position.y + size.y / 2.f);
}

bool Button::isTextOutOfBounds()
{
    sf::FloatRect buttonBounds = m_button.getGlobalBounds();
    sf::FloatRect textBounds = m_text.getGlobalBounds();

    if (textBounds.left < buttonBounds.left ||
        textBounds.top < buttonBounds.top ||
        textBounds.left + textBounds.width > buttonBounds.left + buttonBounds.width ||
        textBounds.top + textBounds.height > buttonBounds.top + buttonBounds.height)
    {
        return true; 
    }

    return false;
}

bool Button::isOutlined() const
{
    if(m_button.getOutlineThickness() > 0.f)
        return true;
    return false;
}

void Button::setTextInBounds(const sf::Vector2f& buffer)
{
    sf::FloatRect buttonBounds = m_button.getGlobalBounds();
    sf::FloatRect textBounds = m_text.getGlobalBounds();

    sf::Vector2f newSize(textBounds.width + 2 * buffer.x, textBounds.height + buffer.y);

    // Update the size of the button
    m_button.setSize(newSize);

    sf::Vector2f newPosition(buttonBounds.left-buffer.x, m_button.getPosition().y);
    newPosition.x = std::min(newPosition.x, textBounds.left-buffer.x);
    // Move the button to the new position
    m_button.setPosition(newPosition);
}

void Button::windowHover(sf::RenderWindow& window)
{ 
    if (this->isMouseOver(window)) 
    {
        this->setOutlineThickness(3.f);
        this->setOutlineColor(sf::Color::Black);
        this->setFillColor(sf::Color(255, 255, 255, 250));
        m_hover = true;
    }
    else if(m_hover)
    {
        this->setOutlineThickness(0);
        this->setFillColor(sf::Color(255, 255, 255, 200));
        m_hover = false;
    }
}

void Button::setButtonsTotalHeight(float height)
{
    Button::m_buttonsTotalHeight = height;
}
