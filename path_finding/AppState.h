#pragma once
#include "State.h"
#include "Algorithm.h"

class AppState : public State
{
private:
	std::vector<gui::Grid*> m_Grid;
	gui::GridStartNode* m_StartNode;
	gui::GridEndNode* m_EndNode;
	unsigned short m_Side;

	std::string m_ActiveElementText;
	std::vector<std::string> m_AlgList;
	std::map<std::string, alg::Algorithm*> m_Algorithms;

	sf::RectangleShape m_Background;
	sf::Texture m_BackgroundTexture;
	sf::Text m_Text;
	sf::Font m_Font;

	void InitGui();
	void InitBackground();

public:
	AppState(sf::RenderWindow*, std::stack<State*>*, 
		const std::vector<std::string>&, const std::string&);
	virtual ~AppState();

	//Functions

	void UpdateGui(const float&);
	void RenderGui();

	void UpdateInput(const float&);
	void Update(const float&);

	void Render();
};

