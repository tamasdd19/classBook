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

std::map<sf::Keyboard::Key, char> keyToCharMapping = {
    {sf::Keyboard::A, 'A'},
    {sf::Keyboard::B, 'B'},
    {sf::Keyboard::C, 'C'},
    {sf::Keyboard::D, 'D'},
    {sf::Keyboard::E, 'E'},
    {sf::Keyboard::F, 'F'},
    {sf::Keyboard::G, 'G'},
    {sf::Keyboard::H, 'H'},
    {sf::Keyboard::I, 'I'},
    {sf::Keyboard::J, 'J'},
    {sf::Keyboard::K, 'K'},
    {sf::Keyboard::L, 'L'},
    {sf::Keyboard::M, 'M'},
    {sf::Keyboard::N, 'N'},
    {sf::Keyboard::O, 'O'},
    {sf::Keyboard::P, 'P'},
    {sf::Keyboard::Q, 'Q'},
    {sf::Keyboard::R, 'R'},
    {sf::Keyboard::S, 'S'},
    {sf::Keyboard::T, 'T'},
    {sf::Keyboard::U, 'U'},
    {sf::Keyboard::V, 'V'},
    {sf::Keyboard::W, 'W'},
    {sf::Keyboard::X, 'X'},
    {sf::Keyboard::Y, 'Y'},
    {sf::Keyboard::Z, 'Z'},
    {sf::Keyboard::Num1, '1'},
    {sf::Keyboard::Num2, '2'},
    {sf::Keyboard::Num3, '3'},
    {sf::Keyboard::Num4, '4'},
    {sf::Keyboard::Num5, '5'},
    {sf::Keyboard::Num6, '6'},
    {sf::Keyboard::Num7, '7'},
    {sf::Keyboard::Num8, '8'},
    {sf::Keyboard::Num9, '9'},
    {sf::Keyboard::Num0, '0'},
};

// Function to convert sf::Keyboard::Key to char
char keyToChar(sf::Keyboard::Key key)
{
    auto it = keyToCharMapping.find(key);
    if (it != keyToCharMapping.end())
    {
        return it->second;
    }
    return '\0'; // Return null character if mapping not found
}

void TextInput::handleEvent(sf::Event& event, sf::RenderWindow& window, bool& keyPressed)
{
    // while(window.pollEvent(event))
    // 
        switch(event.type)
        {
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if(this->isMouseOver(window) && !this->getSelected())
                    {   
                        this->setSelected(true);
                    }
                    else if(this->getSelected() && !this->isMouseOver(window))
                    {
                        this->setSelected(false);
                    }
                }
                break;
            case sf::Event::TextEntered:
                if (event.text.unicode < 128 && this->getSelected() && (!keyPressed || (this->getText()[this->getText().size()-2] != static_cast<char>(event.text.unicode) && event.text.unicode != '\b'))) //|| this->getText()[this->getText().size()-2] != static_cast<char>(event.text.unicode)))
                {
                    if (event.text.unicode == '\b' && !this->getText().empty())
                    {
                        this->deleteCharacter();
                    }
                    else
                    {
                        this->appendCharacter(static_cast<char>(event.text.unicode));
                        
                    }
                    keyPressed = true;
                }
                break;
            case sf::Event::KeyReleased:
                if(std::toupper(this->getText()[this->getText().size()-2]) == keyToChar(event.key.code))
                    keyPressed = false;
                break;
            default:
                break;
        }
}

void TextInput::update()
{
    if(!m_password || m_text.empty())
    {
        this->setText(m_text);
        return ;
    }
    else if(m_text[0] == 13)
    {
        m_text.erase(0,1);
    }
    std::string aux = m_text;
    int i=0;
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