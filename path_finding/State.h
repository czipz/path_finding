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
#include "Button.h"

class State
{
protected:
	bool m_Quit;
	std::stack<State*>* m_States;
	sf::RenderWindow* m_Window;
	sf::Vector2i m_MousePosScreen;
	sf::Vector2i m_MousePosWindow;
	sf::Vector2f m_MousePosView;
	std::map<std::string, Button*> m_Buttons;

	virtual void InitButtons() = 0;

public:
	State(sf::RenderWindow*, std::stack<State*>*);
	virtual ~State();

	const bool& GetQuit() const;

	void CheckForQuit();

	virtual void UpdateButtons() = 0;
	void RenderButtons();

	void UpdateMousePositions();
	virtual void UpdateInput(const float&) = 0;
	virtual void Update(const float&) = 0;
	virtual void Render() = 0;
};

