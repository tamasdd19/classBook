#include "table.h"

    Table::Table(sf::Vector2f position, float rowHeight, std::vector<std::vector<std::string>> data, sf::Font& font, unsigned int fontSize)
        : m_position(position), m_rowHeight(rowHeight), m_data(data), m_font(font), m_fontSize(fontSize)
    {
        // Calculate the table dimensions
        m_numRows = m_data.size();
        m_numColumns = (m_numRows > 0) ? m_data[0].size() : 0;

        // Initialize the table cells
        m_cells.resize(m_numRows * m_numColumns);
        for (unsigned int i = 0; i < m_numRows; ++i)
        {
            for (unsigned int j = 0; j < m_numColumns; ++j)
            {
                sf::Text& cell = m_cells[i * m_numColumns + j];
                cell.setFont(m_font);
                cell.setCharacterSize(m_fontSize);
                cell.setString(m_data[i][j]);

                // Set the position of the cell
                float x = m_position.x + j * m_cellWidth;
                float y = m_position.y + i * m_rowHeight;
                cell.setPosition(x, y);
            }
        }
    }

    void Table::draw(sf::RenderWindow& window)
    {
        for (const sf::Text& cell : m_cells)
        {
            window.draw(cell);
        }
    }
