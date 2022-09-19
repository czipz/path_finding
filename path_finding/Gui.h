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
	GRID_ACTIVE = -1, GRID_IDLE
};


namespace gui
{
	class GridStartNode;

	class GridEndNode;

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

		bool Contains(const sf::Vector2f&) const;
		std::string GetText() const;

		void SetText(const sf::String& Text);
		void setOutlineThickness(int);

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

		sf::CircleShape m_Triangle;

	public:
		DropDownList(float, float, float, float, std::vector<std::string>, unsigned, unsigned);
		virtual ~DropDownList();

		std::string GetActiveElementText() const;
		void UpdateButtonState(const sf::Vector2f&);

		void Update(const sf::Vector2f&, const float&);
		void Render(sf::RenderTarget*);
	};

	class Grid
	{
	private:
		GRID_STATES m_GridState;
		int m_Distance;

		sf::RectangleShape m_Grid;
		sf::Color m_IdleColor;
		sf::Color m_ActiveColor;
		sf::Color m_OutlineColor;

		float m_KeyTime;
		float m_KeyTimeMax;

	public:
		Grid(const float&, const float&, const float&, sf::Color, sf::Color, sf::Color);
		~Grid();

		void ChangeToIdleState();

		const sf::Vector2f& GetPosition() const;
		bool IsActive() const;
		bool Contains(const sf::Vector2f&) const;

		void SetDistance(int);
		int GetDistance() const;
	
		
		void UpdateLeft(const sf::Vector2f&,
			GridStartNode*, GridEndNode*);
		void UpdateRight(const sf::Vector2f&,
			GridStartNode*, GridEndNode*);
		void Render(sf::RenderTarget*);
	};

	class GridStartNode
	{
	private:
		sf::RectangleShape m_StartingPoint;
		sf::Texture m_StartTexture;

		float m_KeyTime;
		float m_KeyTimeMax;

		bool m_NodeFlag;

	public:
		GridStartNode(const float&, const float&, const float&);
		~GridStartNode();

		const sf::Vector2f& GetPosition() const;
		void SetPosition(const float&, const float&);

		void Update(const sf::Vector2f&, const std::vector<Grid*>&, const int&);
		void Render(sf::RenderTarget*);
	};

	class GridEndNode
	{
	private:
		sf::RectangleShape m_DestinationPoint;
		sf::Texture m_EndTexture;

		float m_KeyTime;
		float m_KeyTimeMax;

		bool m_NodeFlag;

	public:
		GridEndNode(const float&, const float&, const float&);
		~GridEndNode();

		bool GetKeyTime();
		void UpdateKeyTime(const float&);

		const sf::Vector2f& GetPosition() const;
		void SetPosition(const float&, const float&);

		void UpdateNodePosition(const sf::Vector2f&, const std::vector<Grid*>&);

		void Update(const sf::Vector2f&, const std::vector<Grid*>&, const float&);
		void Render(sf::RenderTarget*);
	};
}


