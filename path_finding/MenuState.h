#pragma once
#include "AppState.h"

class MenuState : public State
{
private:
	sf::RectangleShape m_Background;

	void InitButtons();
public:
	MenuState(sf::RenderWindow*, std::stack<State*>*);
	virtual ~MenuState();

	void UpdateButtons();

	void UpdateInput(const float&);
	void Update(const float&);

	void Render();
};

