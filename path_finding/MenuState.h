#pragma once
#include "AppState.h"

class MenuState : public State
{
private:
	sf::Font m_Font;
	sf::Text m_Text;
	sf::RectangleShape m_Background;
	sf::Texture m_BackgroundTexture;

	std::map<std::string, gui::DropDownList*> m_DropDownLists;

	void InitGui();
	void InitBackground();

public:
	MenuState(sf::RenderWindow*, std::stack<State*>*);
	virtual ~MenuState();

	void UpdateGui(const float&);
	void RenderGui();

	void UpdateInput(const float&);
	void Update(const float&);

	void Render();
};

