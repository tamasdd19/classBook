#include "input.h"

// const sf::Time TextInput::CURSOR_BLINK_TIME = sf::seconds(0.5f);

TextInput::TextInput(sf::Vector2f position, sf::Vector2f size, sf::Font& font, int textSize) 
    : Button(position, size, "", font, textSize)
{
    this->setTextPosition(position, size);
}

TextInput::TextInput(sf::Vector2f (*function)(const sf::Vector2u&, const sf::Vector2f&), const sf::Vector2u& windowSize, sf::Vector2f size, sf::Font& font, int textSize)
{
    sf::Vector2f position=function(windowSize, size);
    new (this) Button(position, size, "", font, textSize);
    this->setTextPosition(position, size);
}

void TextInput::deleteCharacter()
{
    if(m_text != "_")
    {
        m_text.pop_back();
        m_text.pop_back();
        m_text += '_';
    }
}

void TextInput::removeCursor()
{
    m_text.pop_back();
}

void TextInput::addCursor()
{
    m_text += '_';
}

void TextInput::clearText()
{
    m_text.clear();
}

void TextInput::appendCharacter(const char& c)
{
    m_text.pop_back();
    m_text += c;
    m_text += "_";
}

void TextInput::update()
{
    this->setText(m_text);
    // if(m_selected)
    // {
    //     // if(m_cursorTimer.getElapsedTime() >= CURSOR_BLINK_TIME)
    //     // {
    //     //     m_cursorTimer.restart();
    //     //     m_showCursor = false;
    //     // }
    //     // else
    //     //     m_showCursor = true;
    // }
}

// void TextInput::restartCursorTimer()
// {
//     m_cursorTimer.restart();
// }

// Getters
bool TextInput::getSelected() const
{
    return m_selected;
}

std::string TextInput::getText() const
{
    return m_text;
}

// Setters
void TextInput::setSelected(bool selected)
{
    m_selected = selected;
}