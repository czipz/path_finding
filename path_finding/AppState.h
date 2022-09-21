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

	bool m_VisualiseFlag;
	bool m_RestartFlag;

	bool m_LeftClickNodeFlag;
	bool m_LeftClickGridFlag;
	bool m_RightClickGridFlag;

	sf::RectangleShape m_Background;
	sf::Texture m_BackgroundTexture;
	sf::Text m_Text;
	sf::Font m_Font;

	int m_ColumnsNumber;
	float m_MouseX;
	float m_MouseY;
	int m_ColumnIndex;
	int m_RowIndex;
	int m_Index;


	void InitGui();
	void InitBackground();

public:
	AppState(sf::RenderWindow*, std::stack<State*>*, 
		const std::vector<std::string>&, const std::string&);
	virtual ~AppState();

	//Functions

	int  GetGridIndex() /*override*/;
	void UpdateGui(const float&);
	void RenderGui();

	void Update(const float&);

	void Render();
	void UpdateSFMLEvents(const float&) override;
};

