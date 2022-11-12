#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace GUI 
{


	class Button
	{
	private:
		sf::Vector2f m_pos;
		sf::Vector2f m_size;
		sf::Text m_text;
		sf::Font m_font;
		sf::RectangleShape m_rectBox;
		sf::Color m_outlineColor;
		sf::Color m_fillColor;
	public:
		Button(sf::Vector2f position, sf::Vector2f size, sf::String text);
		Button();
		
		void draw(sf::RenderWindow& window);
		void initNewButton(sf::Vector2f position, sf::Vector2f size, sf::Text text);//Initializes the new position and text for the =operator overload function
		void setColor(sf::Color newColor, sf::Color outline);
		void setText(sf::String newText, sf::Color textColor);
		void setTextSize(unsigned int newSize);
		void setFont(sf::Font newFont);
		void operator=(Button &button);
		sf::Vector2f getPos();
		sf::Vector2f getSize();
		sf::String getTextString();
		sf::Text getText();
		sf::Color getOutlineColor();
		sf::Color getFillColor();
	private:
		void centerText();
	};
	




}
