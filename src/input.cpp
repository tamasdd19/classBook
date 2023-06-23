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

void TextInput::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    // while(window.pollEvent(event))
    // {
        switch(event.type)
        {
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if(this->isMouseOver(window) && !this->getSelected())
                    {   // this works, great! 
                        this->setSelected(true);
                        // this->addCursor();
                    }
                    else
                    {
                        if(this->getSelected())
                        {
                            this->setSelected(false);
                            // this->removeCursor();
                        }
                    }
                }
                break;
            case sf::Event::TextEntered:
                if (event.text.unicode < 128 && this->getSelected())
                {
                    if (event.text.unicode == '\b' && !this->getText().empty()) // Handle backspace
                    {
                        this->deleteCharacter();
                    }
                    else
                    {
                        this->appendCharacter(static_cast<char>(event.text.unicode));
                    }
                }
                break;
            default:
                break;
        }
    // }
}

void TextInput::update()
{
    if(!m_password || m_text.empty())
    {
        this->setText(m_text);
        return ;
    }
    
    std::string aux = m_text;
    int i=1;
    while(aux[i]!='_')
    {
        aux[i] = '*';
        i++;
    }
    this->setText(aux);
    
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
    if(selected)
        this->addCursor();
    else
        this->removeCursor();
}

void TextInput::setIsPassword(bool is)
{
    m_password = is;
}