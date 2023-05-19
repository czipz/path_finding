#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>
#include <thread>
#include <future>


#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Gui.h"

class State
{
public:
	State(sf::RenderWindow*, std::stack<State*>*);
	virtual ~State();

	virtual void Update();
	virtual void Render();

	const bool& GetQuit() const;

protected:
	virtual void InitGui() = 0;
	virtual void InitBackground() = 0;

	void UpdateMousePositions();
	virtual void UpdateSFMLEvents() = 0;
	virtual void UpdateGui() = 0;

	void RenderBackground();
	void RenderText();
	virtual void RenderGui() = 0;

	virtual void Init();

protected:
	std::stack<State*>* m_States;
	sf::RenderWindow* m_Window;
	sf::Vector2f m_MousePosView;
	std::map<std::string, gui::Button*> m_Buttons;
	sf::Event m_SfEvent;

	bool m_Quit;

	sf::RectangleShape m_Background;
	sf::Texture m_BackgroundTexture;
	sf::Text m_Text;
	sf::Font m_Font;
};

