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

	int m_ColumnsNumber;
	float m_MouseX;
	float m_MouseY;
	int m_ColumnIndex;
	int m_RowIndex;
	int m_Index;

	void Init() override;
	void InitGui() override;
	void InitBackground() override;
	void InitAlgorithms();

	int Heuristic(gui::GridStartNode* const, gui::GridEndNode* const) const;

public:
	AppState(sf::RenderWindow*, std::stack<State*>*, 
		const std::vector<std::string>&, const std::string&);

	virtual ~AppState();

	//Functions
	int  GetGridIndex();

	void UpdateGui() override;
	void UpdateSFMLEvents() override;

	void RenderGui() override;
};

