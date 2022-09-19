#pragma once

#include "MenuState.h"

class App
{
private:
	// Variables
	sf::RenderWindow* m_Window;
	

	sf::Clock m_ElapsedTimeClock;
	float m_ElapsedTime;

	std::stack<State*> m_States;

	// Initializer functions
	void InitWindow();
	void InitStates();

public:
	App();
	virtual ~App();

	void UpdateElapsedTime();
	void Update();

	void Render();

	void Run();
};

