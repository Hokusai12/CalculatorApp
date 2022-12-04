#include "Button.h"


namespace GUI
{
	Button::Button()
	{
		m_rectBox = sf::RectangleShape(sf::Vector2f(100.f, 100.f));
		m_rectBox.setPosition(sf::Vector2f(0.f, 0.f));

		m_rectBox.setOutlineColor(sf::Color::Black);
		m_rectBox.setOutlineThickness(5.f);

		m_text = sf::Text(sf::String(""), m_font);
		m_text.setCharacterSize(m_rectBox.getLocalBounds().height / 2);
		centerText();
		m_text.setFillColor(sf::Color::Black);
		m_isActive = false;
	}

	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::String text, sf::Font font) :
		m_pos{ position },
		m_size{ size },
		m_isActive{ false },
		m_font {font}
	{
		
		m_rectBox = sf::RectangleShape(m_size);
		m_rectBox.setPosition(m_pos);

		m_text = sf::Text(text, m_font); 
		m_text.setCharacterSize(m_rectBox.getLocalBounds().height / 2);
		//Centering the text in the button
		centerText();
		m_outlineColor = sf::Color::Black;
		m_fillColor = sf::Color::White;
		m_rectBox.setOutlineColor(sf::Color::Black);
		m_rectBox.setOutlineThickness(5.f);
		m_rectBox.setFillColor(m_fillColor);
		m_text.setFillColor(sf::Color::Black);
	}

	void Button::setPosition(sf::Vector2f position)
	{
		m_pos = position;
		m_rectBox.setPosition(m_pos);
		centerText();
	}

	void Button::setSize(sf::Vector2f size)
	{
		m_size = size;
		m_rectBox.setSize(m_size);
	}

	void Button::setBoxColor(sf::Color newColor, sf::Color outline)
	{
		m_fillColor = newColor;
		m_outlineColor = outline;
		m_rectBox.setFillColor(newColor);
		m_rectBox.setOutlineColor(outline);
	}

	void Button::setText(sf::String newText, sf::Color textColor)
	{
		m_text = sf::Text(newText, m_font);
		m_text.setFillColor(textColor);
		centerText();
	}

	void Button::setTextSize(unsigned int newSize)
	{
		m_text.setCharacterSize(newSize);
	}

	void Button::centerText()
	{
		/*This will center the text vertically first
		and then horizontally if the text is smaller than the button
		If the text is larger than the button the text will left align and overflow*/
		sf::FloatRect textBoundingBox = m_text.getLocalBounds();
		sf::FloatRect buttonBoundingBox = m_rectBox.getLocalBounds();


		//Weird math because for whatever reason the text wouldn't naturally align to the center
		if (textBoundingBox.width > buttonBoundingBox.width)
			m_text.setPosition(sf::Vector2f(m_rectBox.getPosition().x - (buttonBoundingBox.width * 0.05), m_rectBox.getPosition().y - (buttonBoundingBox.height * 0.14) + (buttonBoundingBox.height / 2 - textBoundingBox.height / 2)));
		else
			m_text.setPosition(sf::Vector2f(m_rectBox.getPosition().x - (buttonBoundingBox.width * 0.05) + (buttonBoundingBox.width / 2 - textBoundingBox.width / 2), m_rectBox.getPosition().y - (buttonBoundingBox.height * 0.14) + (buttonBoundingBox.height / 2 - textBoundingBox.height / 2)));
	}

	void Button::operator=(const Button* button)
	{
		this->m_pos = button->m_pos;
		this->m_size = button->m_size;
		this->m_text = button->m_text;
		this->m_font.loadFromFile("assets/fonts/ArialTh.ttf");
		this->m_fillColor = button->m_fillColor;
		this->m_outlineColor = button->m_outlineColor;
		this->m_rectBox = button->m_rectBox;
		//this->centerText();
	}

	sf::Color Button::getOutlineColor()
	{
		return m_rectBox.getOutlineColor();
	}

	sf::Color Button::getFillColor()
	{
		return m_rectBox.getFillColor();
	}

	void Button::draw(sf::RenderWindow& window)
	{
		window.draw(m_rectBox);
		window.draw(m_text);
	}

	void Button::update(sf::RenderWindow &window)
	{
		m_isActive = contains(sf::Mouse::getPosition(window).x * 1.0f, sf::Mouse::getPosition(window).y * 1.0f);
		if (m_isActive)
		{
			m_rectBox.setFillColor(sf::Color::Yellow);
		}
		else
		{
			setBoxColor(m_fillColor);
		}
	}

	bool Button::isActive()
	{
		return m_isActive;
	}

	bool Button::contains(float x, float y)
	{
		sf::FloatRect bounds = m_rectBox.getGlobalBounds();
		if (x > bounds.left && x < bounds.left + bounds.width)
		{
			if (y > bounds.top && y < bounds.top + bounds.height)
			{
				return true;
			}
		}
		return false;
	}

	void Button::setFont(sf::Font newFont)
	{
		m_font = newFont;
	}

	sf::Vector2f Button::getPos()
	{
		return m_pos;
	}

	sf::Vector2f Button::getSize()
	{
		return m_size;
	}

	sf::String Button::getTextString() {
		return m_text.getString();
	}

	sf::Text Button::getText()
	{
		return m_text;
	}
}