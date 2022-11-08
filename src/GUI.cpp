#include "GUI.h"


namespace GUI
{
	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::String text) :
		m_pos{ position },
		m_size{ size }
	{
		
		rectBox = sf::RectangleShape(m_size);
		rectBox.setPosition(m_pos);
		if (!m_font.loadFromFile("assets/fonts/Louis George Cafe.ttf")) //Free-use font downloaded from dafont.com
		{
			std::cout << "Yeah that didn't work";
		}

		m_text = sf::Text(text, m_font); 
		//Centering the text in the button
		centerText();
		m_text.setFillColor(sf::Color::Black);
	}

	void Button::draw(sf::RenderWindow& window)
	{
		window.draw(rectBox);
		window.draw(m_text);
	}

	void Button::setColor(sf::Color newColor, sf::Color outline)
	{
		rectBox.setFillColor(newColor);
		rectBox.setOutlineColor(outline);
	}

	void Button::setText(sf::String newText, sf::Color textColor)
	{
		m_text = sf::Text(newText, m_font);
	}

	void Button::centerText()
	{
		/*This will center the text vertically first
and then horizontally if the text is smaller than the button

If the text is larger than the button the text will left align and overflow*/
		sf::FloatRect textBoundingBox = m_text.getLocalBounds();
		sf::FloatRect buttonBoundingBox = rectBox.getLocalBounds();

			if (textBoundingBox.width > buttonBoundingBox.width)
			{
				m_text.setPosition(sf::Vector2f(rectBox.getPosition().x, rectBox.getPosition().y + (buttonBoundingBox.height / 2 - textBoundingBox.height / 2)));
			}
			else
			{
				m_text.setPosition(sf::Vector2f(rectBox.getPosition().x + (buttonBoundingBox.width / 2 - textBoundingBox.width / 2), rectBox.getPosition().y + (buttonBoundingBox.height / 2 - textBoundingBox.height / 2)));
			}
	}
}