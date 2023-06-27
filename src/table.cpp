#include "table.h"

    Table::Table(sf::Vector2f position, float rowHeight, std::vector<std::vector<std::string>> data, sf::Font& font, unsigned int fontSize)
        : m_position(position), m_rowHeight(rowHeight), m_data(data), m_font(font), m_fontSize(fontSize)
    {
        m_numRows = m_data.size();
        m_numColumns = (m_numRows > 0) ? m_data[0].size() : 0;

        m_cells.resize(m_numRows * m_numColumns);
        for (unsigned int i = 0; i < m_numRows; ++i)
        {
            for (unsigned int j = 0; j < m_numColumns; ++j)
            {
                sf::Text& cell = m_cells[i * m_numColumns + j];
                cell.setFont(m_font);
                cell.setCharacterSize(m_fontSize);
                cell.setString(m_data[i][j]);

                float x = m_position.x + j * m_cellWidth;
                float y = m_position.y + i * m_rowHeight;
                cell.setPosition(x, y);
            }
        }
    }

void Table::draw(sf::RenderWindow& window)
{
    sf::Vector2f cellSize(m_cellWidth - 35.f, m_rowHeight - 25.f);

    for (unsigned int i = 0; i < m_numRows; ++i)
    {
        // Calculate the position of the row's background rectangle
        float x = m_position.x - 10.f;
        float y = m_position.y + i * (m_rowHeight) - 10.f;
        sf::Vector2f rectPosition(x, y);
        sf::Vector2f rectSize = cellSize;
        rectSize.x *= m_numColumns;

        // Create a rectangle shape for the row's background
        
        sf::RectangleShape rowBackground(rectSize);
        rowBackground.setPosition(rectPosition);
        // Set your desired background color here
        rowBackground.setFillColor(sf::Color(0, 0, 0, 150)); // Example: light gray

        // Draw the row's background
        window.draw(rowBackground);

        // Draw the text cells for the row
        for (unsigned int j = 0; j < m_numColumns; ++j)
        {
            const sf::Text& cell = m_cells[i * m_numColumns + j];
            window.draw(cell);
        }
    }
}

    sf::Vector2f Table::getSize() const 
    {
        float width = m_numColumns * m_cellWidth;
        float height = m_numRows * m_rowHeight;

        return sf::Vector2f(width, height);
    }
    
    void Table::setCenter(const sf::Vector2u& windowSize)
    {
        sf::Vector2f tableSize = getSize();
        sf::Vector2f centerPosition(
            (windowSize.x - tableSize.x) / 2.f,
            (windowSize.y - tableSize.y) / 2.f
        );

        m_position = centerPosition;
    }

sf::Vector2f Table::maxCellSize()
{
    float maxCellWidth = 0.f;
    float maxCellHeight = 0.f;

    for (const sf::Text& cell : m_cells)
    {
        float cellWidth = cell.getLocalBounds().width;
        float cellHeight = cell.getLocalBounds().height;

        if (cellWidth > maxCellWidth)
            maxCellWidth = cellWidth;

        if (cellHeight > maxCellHeight)
            maxCellHeight = cellHeight;
    }
    return sf::Vector2f(maxCellWidth, maxCellHeight);
}
