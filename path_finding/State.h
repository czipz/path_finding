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
#include "Gui.h"

class State
{
protected:
	bool m_Quit;
	std::stack<State*>* m_States;
	sf::RenderWindow* m_Window;
	sf::Vector2i m_MousePosScreen;
	sf::Vector2i m_MousePosWindow;
	sf::Vector2f m_MousePosView;
	std::map<std::string, gui::Button*> m_Buttons;

	virtual void InitGui() = 0;

public:
	State(sf::RenderWindow*, std::stack<State*>*);
	virtual ~State();

	const bool& GetQuit() const;
	void CheckForQuit();

	virtual void UpdateGui(const float&) = 0;
	virtual void RenderGui() = 0;

	void UpdateMousePositions();
	virtual void UpdateInput(const float&) = 0;
	virtual void Update(const float&) = 0;
	virtual void Render() = 0;
};

