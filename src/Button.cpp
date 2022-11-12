#include "Button.h"


namespace GUI
{
	Button::Button()
	{
		m_rectBox = sf::RectangleShape(sf::Vector2f(100.f, 100.f));
		m_rectBox.setPosition(sf::Vector2f(0.f, 0.f));
		if (!m_font.loadFromFile("assets/fonts/ArialTh.ttf"))
			std::cout << "Yeah that didn't work";

		m_text = sf::Text(sf::String(""), m_font);
		m_text.setOrigin(sf::Vector2f(0.f, 0.f));
		m_text.setCharacterSize(m_rectBox.getLocalBounds().height / 2);
		centerText();
		m_text.setFillColor(sf::Color::Black);
	}

	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::String text) :
		m_pos{ position },
		m_size{ size }
	{
		
		m_rectBox = sf::RectangleShape(m_size);
		m_rectBox.setPosition(m_pos);
		if (!m_font.loadFromFile("assets/fonts/ArialTh.ttf")) //Free-use font downloaded from dafont.com
		{
			std::cout << "Yeah that didn't work" << std::endl;
		}

		m_text = sf::Text(text, m_font); 
		m_text.setOrigin(sf::Vector2f(0.f, 0.f));
		m_text.setCharacterSize(m_rectBox.getLocalBounds().height / 2);
		//Centering the text in the button
		centerText();
		m_outlineColor = sf::Color::Black;
		m_fillColor = sf::Color::White;
		m_rectBox.setOutlineColor(m_outlineColor);
		m_rectBox.setOutlineThickness(2.f);
		m_rectBox.setFillColor(m_fillColor);
		m_text.setFillColor(sf::Color::Black);
	}


	void Button::setColor(sf::Color newColor, sf::Color outline)
	{
		m_rectBox.setFillColor(newColor);
		m_rectBox.setOutlineColor(outline);
	}

	void Button::setText(sf::String newText, sf::Color textColor)
	{
		m_text = sf::Text(newText, m_font);
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
			m_text.setPosition(sf::Vector2f(m_rectBox.getPosition().x - (buttonBoundingBox.width * 0.017), m_rectBox.getPosition().y - (buttonBoundingBox.height * 0.14) + (buttonBoundingBox.height / 2 - textBoundingBox.height / 2)));
		else
			m_text.setPosition(sf::Vector2f(m_rectBox.getPosition().x - (buttonBoundingBox.width * 0.017) + (buttonBoundingBox.width / 2 - textBoundingBox.width / 2), m_rectBox.getPosition().y - (buttonBoundingBox.height * 0.14) + (buttonBoundingBox.height / 2 - textBoundingBox.height / 2)));
	}

	void Button::operator=(Button& button)
	{
		m_pos = button.getPos();
		m_size = button.getSize();
		m_font.loadFromFile("assets/fonts/ArialTh.ttf");
		m_text = sf::Text(button.getTextString(), m_font);
		m_outlineColor = button.getOutlineColor();
		m_fillColor = button.getFillColor();
		initNewButton(m_pos, m_size, m_text);
	}

	void Button::initNewButton(sf::Vector2f position, sf::Vector2f size, sf::Text text)
	{
		m_rectBox = sf::RectangleShape(m_size);
		m_rectBox.setPosition(m_pos);
		m_rectBox.setFillColor(m_fillColor);
		m_rectBox.setOutlineColor(m_outlineColor);
		if (!m_font.loadFromFile("assets/fonts/ArialTh.ttf")) //Free-use font downloaded from dafont.com
		{
			std::cout << "Yeah that didn't work" << std::endl;
		}
		m_text.setOrigin(sf::Vector2f(0.f, 0.f));
		m_text.setCharacterSize(m_rectBox.getLocalBounds().height / 2);
		//Centering the text in the button
		centerText();
		m_text.setFillColor(sf::Color::Black);
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