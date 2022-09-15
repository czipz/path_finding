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

namespace gui
{
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
		std::string GetText() const;

		void SetText(const sf::String& Text);

		void Update(const sf::Vector2f&);
		void Render(sf::RenderTarget*);
	};

	class DropDownList
	{
	private:
		//sf::Font m_Font;
		gui::Button* m_ActiveElement;
		std::vector<gui::Button*> m_List;
		bool m_ShowList;

		float m_KeyTime;
		float m_KeyTimeMax;

	public:
		DropDownList(float, float, float, float, std::vector<std::string>, unsigned, unsigned);
		virtual ~DropDownList();

		bool GetKeyTime();
		void UpdateKeyTime(const float&);

		void Update(const sf::Vector2f&, const float&);
		void Render(sf::RenderTarget*);
	};
}


