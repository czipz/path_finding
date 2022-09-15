#pragma once
#include "State.h"

class AppState : public State
{
private:
	void InitGui();
	sf::RectangleShape m_Background;

public:
	AppState(sf::RenderWindow*, std::stack<State*>*);
	virtual ~AppState();

	//Functions

	void UpdateGui(const float&);
	void RenderGui();

	void UpdateInput(const float&);
	void Update(const float&);

	void Render();
};

