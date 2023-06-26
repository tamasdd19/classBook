#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Table
{
public:
    Table(sf::Vector2f position, float rowHeight, std::vector<std::vector<std::string>> data, sf::Font& font, unsigned int fontSize);

    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f m_position;
    float m_rowHeight;
    std::vector<std::vector<std::string>> m_data;
    sf::Font& m_font;
    unsigned int m_fontSize;
    unsigned int m_numRows;
    unsigned int m_numColumns;
    std::vector<sf::Text> m_cells;
    float m_cellWidth = 100.f; // Adjust the width of each cell as needed
};