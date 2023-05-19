#pragma once

#include "MenuState.h"

class App
{
private:
	// Variables
	sf::RenderWindow* m_Window;

	std::stack<State*> m_States;

	// Initializer functions
	void InitWindow();
	void InitStates();

public:
	App();
	virtual ~App();

	void Update();

	void Render();

	void Run();
};

