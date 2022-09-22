#pragma once
#include "AppState.h"

class MenuState : public State
{
private:
	sf::Font m_Font;
	sf::Text m_Text;
	sf::RectangleShape m_Background;
	sf::Texture m_BackgroundTexture;
	std::vector<std::string> m_AlgList;


	std::map<std::string, gui::DropDownList*> m_DropDownLists;

	void InitGui() override;
	void InitBackground();

public:
	MenuState(sf::RenderWindow*, std::stack<State*>*);
	virtual ~MenuState();

	void UpdateGui() override;
	void RenderGui() override;

	void Update() override;

	void Render() override;
	void UpdateSFMLEvents() override;
};

