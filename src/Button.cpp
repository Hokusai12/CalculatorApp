#include "Button.h"


namespace GUI
{
	Button::Button()
	{
		rectBox = sf::RectangleShape(sf::Vector2f(100.f, 100.f));
		rectBox.setPosition(sf::Vector2f(0.f, 0.f));
		if (!m_font.loadFromFile("assets/fonts/ArialTh.ttf"))
			std::cout << "Yeah that didn't work";

		m_text = sf::Text(sf::String(""), m_font);
		m_text.setOrigin(sf::Vector2f(0.f, 0.f));
		m_text.setCharacterSize(rectBox.getLocalBounds().height / 2);
		centerText();
		m_text.setFillColor(sf::Color::Black);
	}

	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::String text) :
		m_pos{ position },
		m_size{ size }
	{
		
		rectBox = sf::RectangleShape(m_size);
		rectBox.setPosition(m_pos);
		if (!m_font.loadFromFile("assets/fonts/ArialTh.ttf")) //Free-use font downloaded from dafont.com
		{
			std::cout << "Yeah that didn't work";
		}

		m_text = sf::Text(text, m_font); 
		m_text.setOrigin(sf::Vector2f(0.f, 0.f));
		m_text.setCharacterSize(rectBox.getLocalBounds().height / 2);
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
		sf::FloatRect buttonBoundingBox = rectBox.getLocalBounds();


		//Weird math because for whatever reason the text wouldn't naturally align to the center
		if (textBoundingBox.width > buttonBoundingBox.width)
			m_text.setPosition(sf::Vector2f(rectBox.getPosition().x - (buttonBoundingBox.width * 0.017), rectBox.getPosition().y - (buttonBoundingBox.height * 0.14) + (buttonBoundingBox.height / 2 - textBoundingBox.height / 2)));
		else
			m_text.setPosition(sf::Vector2f(rectBox.getPosition().x - (buttonBoundingBox.width * 0.017) + (buttonBoundingBox.width / 2 - textBoundingBox.width / 2), rectBox.getPosition().y - (buttonBoundingBox.height * 0.14) + (buttonBoundingBox.height / 2 - textBoundingBox.height / 2)));
	}

	Button Button::operator=(Button& button)
	{
		std::cout << button.getPos().x << ", " << button.getPos().y << std::endl;

		Button newButton;
		return newButton;
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

	sf::String Button::getText()
	{
		return m_text.getString();
	}
}