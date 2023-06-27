#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Table
{
public:
    Table(sf::Vector2f position, float rowHeight, std::vector<std::vector<std::string>> data, sf::Font& font, unsigned int fontSize);

    void draw(sf::RenderWindow& window);
    sf::Vector2f maxCellSize();
    sf::Vector2f getSize() const;

    void setCenter(const sf::Vector2u& windowSize);
private:
    sf::Vector2f m_position;
    float m_rowHeight;
    std::vector<std::vector<std::string>> m_data;
    sf::Font& m_font;
    unsigned int m_fontSize;
    unsigned int m_numRows;
    unsigned int m_numColumns;
    std::vector<sf::Text> m_cells;
    float m_cellWidth = 700.f;
};