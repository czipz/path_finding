#pragma once
#include "AppState.h"

class MenuState : public State
{
public:
	MenuState(sf::RenderWindow*, std::stack<State*>*);
	virtual ~MenuState();

private:
	void UpdateGui() override;
	void RenderGui() override;
	void UpdateSFMLEvents() override;

private:
	std::vector<std::string> m_AlgList;
	std::map<std::string, gui::DropDownList*> m_DropDownLists;

	void InitGui() override;
	void InitBackground() override;
};

