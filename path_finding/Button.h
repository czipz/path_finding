#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <iterator>
#include <algorithm>
#include <chrono>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

enum class BUTTON_STATES
{
	BTN_IDLE, BTN_HOVER, BTN_ACTIVE
};

class Button
{
private:
	BUTTON_STATES m_ButtonState;

	sf::RectangleShape m_Button;
	sf::Text m_Text;
	sf::Font m_Font;

	sf::Color m_IdleColor;
	sf::Color m_HoverColor;
	sf::Color m_ActiveColor;

public:
	Button(float, float, float, float, std::string,
		sf::Color, sf::Color, sf::Color);
	~Button();

	bool IsPressed() const;

	void Update(const sf::Vector2f&);
	void Render(sf::RenderTarget*);
};

