#include <SFML/Graphics.hpp>

namespace GUI
{

	enum class Alignment
	{
		Right,
		Left,
		Center
	};


	class TextArea
	{
	private:
		sf::Vector2f m_pos;
		sf::Vector2f m_size;
		sf::Color m_backgroundColor;
		sf::Color m_outlineColor;
		sf::Color m_textColor;
		sf::RectangleShape m_textBox;
		sf::Text m_text;
		sf::Font m_font;

	public:
		TextArea();
		TextArea(sf::Vector2f position, sf::Vector2f size, sf::String text, sf::Font& font);
		void draw(sf::RenderWindow& window);
		void setText(sf::String newText);
		void concatText(sf::String addText);
		void setColor(sf::Color fillColor = sf::Color::White, sf::Color outlineColor = sf::Color::Transparent);
		sf::String getText() { return m_text.getString(); }
		void alignText(GUI::Alignment alignment);
		void clearText();
		void operator=(const TextArea *display);
	private:
	};
}