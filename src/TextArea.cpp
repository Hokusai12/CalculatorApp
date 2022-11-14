#include "TextArea.h"
#include <iostream>

namespace GUI
{

	TextArea::TextArea(sf::Vector2f position, sf::Vector2f size, sf::String text)
	{
		m_textBox.setPosition(position);
		m_textBox.setSize(size);
		m_textBox.setFillColor(sf::Color::Color(180, 180, 180));
		m_backgroundColor = sf::Color::White;
		if (!m_font.loadFromFile("assets/fonts/ArialTh.ttf"))
			std::cout << "Failed to load font" << std::endl;
		m_text.setFont(m_font);
		m_text.setString(text);
		m_text.setOrigin(sf::Vector2f(0.f, 0.f));
		m_text.setFillColor(sf::Color::Black);
		m_textColor = sf::Color::Black;
		m_text.setCharacterSize(m_textBox.getLocalBounds().height / 2);
		alignText(Alignment::Center);
	}

	void TextArea::draw(sf::RenderWindow& window)
	{
		window.draw(m_textBox);
		window.draw(m_text);
	}

	void TextArea::clearText()
	{
		m_text.setString("");
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