#pragma once
#include "State.h"

class AppState : public State
{
private:
	std::vector<gui::Grid*> m_Grid;
	gui::GridStartNode* m_StartNode;
	gui::GridEndNode* m_EndNode;
	unsigned short m_Side;

	sf::RectangleShape m_Background;
	sf::Texture m_BackgroundTexture;
	void InitGui();
	void InitBackground();

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

