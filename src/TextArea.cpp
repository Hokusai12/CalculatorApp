#include "TextArea.h"
#include <iostream>

namespace GUI
{

	TextArea::TextArea()
	{
	}

	TextArea::TextArea(sf::Vector2f position, sf::Vector2f size, sf::String text, sf::Font& font) :
		m_pos {position},
		m_size {size},
		m_font {font}
	{
		m_textBox.setPosition(position);
		m_textBox.setSize(size);
		m_backgroundColor = sf::Color::White;
		m_textBox.setFillColor(sf::Color::White);
		m_text.setFont(font);
		m_text.setString(text);
		m_textColor = sf::Color::Black;
		m_text.setFillColor(sf::Color::Black);
		m_text.setCharacterSize(m_textBox.getLocalBounds().height / 2);
		alignText(Alignment::Center);
	}

	void TextArea::draw(sf::RenderWindow& window)
	{
		window.draw(m_textBox);
		window.draw(m_text);
	}

	void TextArea::operator=(const TextArea *display)
	{
		this->m_pos = display->m_pos;
		this->m_size = display->m_size;
		this->m_text = display->m_text;
		this->m_font.loadFromFile("assets/fonts/ArialTh.ttf");
		this->m_backgroundColor = display->m_backgroundColor;
		this->m_outlineColor = display->m_outlineColor;
		this->m_textBox = display->m_textBox;
		//this->centerText();
	}

	void TextArea::clearText()
	{
		m_text.setString("");
	}

	void TextArea::setColor(sf::Color fillColor, sf::Color outlineColor)
	{
		m_backgroundColor = fillColor;
		m_outlineColor = outlineColor;
		m_textBox.setFillColor(fillColor);
		m_textBox.setOutlineColor(outlineColor);
	}

	void TextArea::setText(sf::String newText)
	{
		m_text.setString(newText);
		alignText(Alignment::Center);
	}

	void TextArea::concatText(sf::String addText)
	{
		sf::String newText = m_text.getString() + addText;
		setText(newText);
	}

	void TextArea::alignText(Alignment alignment)
	{
		sf::FloatRect textBoundingBox = m_text.getLocalBounds();
		sf::FloatRect buttonBoundingBox = m_textBox.getLocalBounds();

		switch (alignment)
		{
		case Alignment::Right:
			m_text.setPosition(sf::Vector2f(buttonBoundingBox.left + buttonBoundingBox.width, m_textBox.getPosition().y - (buttonBoundingBox.height * 0.14) + (buttonBoundingBox.height / 2 - textBoundingBox.height / 2)));
			break;
		case Alignment::Left:
			m_text.setPosition(sf::Vector2f(buttonBoundingBox.left, m_textBox.getPosition().y - (buttonBoundingBox.height * 0.14) + (buttonBoundingBox.height / 2 - textBoundingBox.height / 2)));
			break;

		case Alignment::Center:
			m_text.setPosition(sf::Vector2f(m_textBox.getPosition().x - (buttonBoundingBox.width * 0.017) + (buttonBoundingBox.width / 2 - textBoundingBox.width / 2), m_textBox.getPosition().y - (buttonBoundingBox.height * 0.14) + (buttonBoundingBox.height / 2 - textBoundingBox.height / 2)));
			break;

		default:
			std::cout << "Not a valid alignment" << std::endl;
			break;
		}
	}
}