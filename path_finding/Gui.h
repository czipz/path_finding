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

enum class GRID_STATES
{
	GRID_IDLE, GRID_ACTIVE, GRID_START, GRID_END
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

	class Grid
	{
	private:
		GRID_STATES m_GridState;

		sf::RectangleShape m_Grid;
		sf::Color m_IdleColor;
		sf::Color m_ActiveColor;
		sf::Color m_OutlineColor;

		float m_KeyTime;
		float m_KeyTimeMax;

	public:
		Grid(const float&, const float&, const float&, sf::Color, sf::Color, sf::Color);
		~Grid();

		bool GetKeyTime();
		void UpdateKeyTime(const float&);

		bool IsPressed() const;

		void ChangeToIdleState();

		const sf::Vector2f& GetPosition() const;

		void Update(const sf::Vector2f&, const float&);
		void Render(sf::RenderTarget*);
	};

	class GridStartNode
	{
	private:
		sf::RectangleShape m_StartSprite;
		sf::Texture m_StartTexture;

		sf::Sprite m_EndSprite;
		sf::Texture m_EndTexture;

	public:
		GridStartNode(const float&, const float&, const float&);
		~GridStartNode();

		const sf::Vector2f& GetPosition() const;
		void SetPosition();

		void Update(const sf::Vector2f&, const float&);
		void Render(sf::RenderTarget*);
	};

	class GridEndNode
	{
	private:
		sf::RectangleShape m_EndSprite;
		sf::Texture m_EndTexture;

	public:
		GridEndNode(const float&, const float&, const float&);
		~GridEndNode();

		const sf::Vector2f& GetPosition() const;
		void SetPosition();

		void Update(const sf::Vector2f&, const float&);
		void Render(sf::RenderTarget*);
	};
}


