#pragma once
#include "State.h"
#include "Algorithm.h"

class AppState : public State
{
public:
	AppState(sf::RenderWindow*, std::stack<State*>*, 
		const std::vector<std::string>&, const std::string&);

	virtual ~AppState();

private:
	//Functions
	int  GetGridIndex();

	void UpdateGui() override;
	void UpdateSFMLEvents() override;

	void RenderGui() override;

	void Init() override;
	void InitGui() override;
	void InitBackground() override;
	void InitAlgorithms();

	int Heuristic(gui::GridStartNode* const, gui::GridEndNode* const) const;

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
};

