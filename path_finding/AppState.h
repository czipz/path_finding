#pragma once
#include "State.h"

class AppState : public State
{
private:
	void InitButtons();
	sf::RectangleShape m_Background;

public:
	AppState(sf::RenderWindow*, std::stack<State*>*);
	virtual ~AppState();

	//Functions

	void UpdateButtons();

	void UpdateInput(const float&);
	void Update(const float&);

	void Render();
};

