#include "AppState.h"


void AppState::Init()
{
	State::Init();
	InitAlgorithms();
}

void AppState::InitGui()
{
	//Init Buttons
	m_Buttons["EXIT_STATE"] = new gui::Button(m_Window->getSize().x - 200,
		m_Window->getSize().y - 700, 150, 50, "Back",
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	
	m_Buttons["RESTART_GRID"] = new gui::Button(m_Window->getSize().x - 400,
		m_Window->getSize().y - 700, 150, 50, "Restart",
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	m_Buttons["VISUALISE"] = new gui::Button(m_Window->getSize().x - 600,
		m_Window->getSize().y - 700, 150, 50, "Visualise",
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	// Init Grid
	m_ColumnsNumber = m_Window->getSize().x / m_Side;
	for (unsigned y = 4; y < (m_Window->getSize().y / m_Side); ++y)
	{
		for (unsigned x = 0; x < (m_Window->getSize().x / m_Side); ++x)
		{
			if (y == 4  || y == m_Window->getSize().y / m_Side - 1 || x == 0 || x == m_Window->getSize().x / m_Side - 1)
			{
				m_Grid.push_back(new gui::Grid(m_Side * x, m_Side * y, m_Side, (y - 4) * m_ColumnsNumber + x,
					sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0)));
			}
			else
			{
				m_Grid.push_back(new gui::Grid(m_Side * x, m_Side * y, m_Side, (y - 4) * m_ColumnsNumber + x,
					sf::Color(169, 169, 169), sf::Color::Black, sf::Color::White));
			}
		}
	}

	//Init Grid Nodes
	m_StartNode = new gui::GridStartNode(m_Grid[976]->GetPosition().x, m_Grid[976]->GetPosition().y, m_Side);
	m_EndNode = new gui::GridEndNode(m_Grid[1007]->GetPosition().x, m_Grid[1007]->GetPosition().y, m_Side);
	m_Grid[m_StartNode->GetIndex()]->SetDistance(1);
	m_Grid[m_StartNode->GetIndex()]->SetGlobalDistance(Heuristic(m_StartNode, m_EndNode));
	m_Grid[m_StartNode->GetIndex()]->SetLocalDistance(0);
	std::cout << "Index = " << m_StartNode->GetIndex() << std::endl;
	std::cout << "StartNode Global Distance = " << m_Grid[m_StartNode->GetIndex()]->GetGlobalDistance() << std::endl;
}

int AppState::GetGridIndex()
{
	int MouseX = static_cast<int>(m_MousePosView.x);
	int MouseY = static_cast<int>(m_MousePosView.y);

	if (MouseX > m_Window->getSize().x)
	{
		MouseX = m_Window->getSize().x;
	}
	else if (MouseX < 0)
	{
		MouseX = 0;
	}

	int ColumnIndex = MouseX / m_Side;
	int RowIndex = MouseY / m_Side - 4;
	int Index = RowIndex * m_ColumnsNumber + ColumnIndex;

	return Index;
}

void AppState::InitBackground()
{
	m_Background.setSize(sf::Vector2f(m_Window->getSize().x, m_Window->getSize().y));
	m_BackgroundTexture.loadFromFile("Images/Backgrounds/bg2.png");
	m_Background.setTexture(&m_BackgroundTexture);

	m_Font.loadFromFile("Fonts/font1.ttf");
	m_Text.setString("Chosen algorithm: " + m_ActiveElementText);
	m_Text.setFont(m_Font);
	m_Text.setFillColor(sf::Color::White);
	m_Text.setCharacterSize(40);
	m_Text.setPosition(50, 20);
	
}

void AppState::InitAlgorithms()
{
	m_Algorithms.emplace("A*", new alg::A_Star());
	m_Algorithms.emplace("Dijkstra's", new alg::Dijkstra());
	m_Algorithms.emplace("Wavefront", new alg::Wavefront());
}

AppState::AppState(sf::RenderWindow* Window, std::stack<State*>* States, 
	const std::vector<std::string>& AlgList, const std::string& ActiveElementText)
	: State(Window, States)
	, m_Side(20)
	, m_ActiveElementText(ActiveElementText)
	, m_AlgList(AlgList)
	, m_VisualiseFlag(false)
	, m_LeftClickNodeFlag(false)
	, m_LeftClickGridFlag(false)
	, m_RightClickGridFlag(false)
	, m_RestartFlag(false)
{
	Init();
}

AppState::~AppState()
{
	std::cout << "Ending App State\n";

	delete m_StartNode;
	delete m_EndNode;

	for (auto& e : m_Grid)
	{
		delete e;
	}

	for (auto& e : m_Algorithms)
	{
		delete e.second;
	}
}

void AppState::UpdateGui()
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		it->second->Update(m_MousePosView);
	}

	if (GetGridIndex() >= 0 && GetGridIndex() < m_Grid.size() && !m_RestartFlag)
	{
		if (m_LeftClickNodeFlag && !m_EndNode->GetNodeFlag())
		{
			m_StartNode->Update(m_MousePosView, m_Grid, *m_EndNode, GetGridIndex());
		}

		if (m_LeftClickNodeFlag && !m_StartNode->GetNodeFlag())
		{
			m_EndNode->Update(m_MousePosView, m_Grid, *m_StartNode, GetGridIndex());
		}

		if (m_LeftClickGridFlag)
		{
			m_Grid[GetGridIndex()]->UpdateLeft(m_MousePosView, m_StartNode, m_EndNode);
		}

		if (m_RightClickGridFlag)
		{
			m_Grid[GetGridIndex()]->UpdateRight(m_MousePosView, m_StartNode, m_EndNode);
		}
	}
}

void AppState::RenderGui()
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		it->second->Render(m_Window);
	}

	for (const auto& e : m_Grid)
	{
		e->Render(m_Window);
	}

	m_StartNode->Render(m_Window);
	m_EndNode->Render(m_Window);
}

int AppState::Heuristic(gui::GridStartNode* const StartNode, gui::GridEndNode* const EndNode) const
{
	int heuristic = sqrt(pow((StartNode->GetPosition().x - EndNode->GetPosition().x), 2) +
		pow((StartNode->GetPosition().x - EndNode->GetPosition().x), 2));

	return heuristic;
}

void AppState::UpdateSFMLEvents()
{
	while (m_Window->pollEvent(m_SfEvent))
	{
		switch (m_SfEvent.type)
		{
		case sf::Event::Closed:
			m_Window->close();
			break;
		case sf::Event::MouseButtonPressed:
			// Update Grid
			if (!m_VisualiseFlag && GetGridIndex() >= 0 && GetGridIndex() < m_Grid.size())
			{
				if (m_SfEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (!m_LeftClickNodeFlag && (m_StartNode->Contains(m_MousePosView) ||
						m_EndNode->Contains(m_MousePosView)))
						m_LeftClickNodeFlag = true;

					if (!m_LeftClickGridFlag && !m_StartNode->Contains(m_MousePosView) &&
						!m_EndNode->Contains(m_MousePosView))
					{
						m_LeftClickGridFlag = true;
					}
				}

				else if (m_SfEvent.mouseButton.button == sf::Mouse::Right)
				{
					if (!m_RightClickGridFlag)
						m_RightClickGridFlag = true;
				}
			}
			break;

		case sf::Event::MouseButtonReleased:
			if (!m_VisualiseFlag)
			{
				if (m_SfEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (m_LeftClickNodeFlag && GetGridIndex() >= 0 && GetGridIndex() < m_Grid.size())
					{
						m_LeftClickNodeFlag = false;
						m_StartNode->SetNodeFlag(*m_EndNode, m_Grid, m_MousePosView, GetGridIndex(), m_ColumnsNumber, m_Side);
						m_EndNode->SetNodeFlag(*m_StartNode, m_Grid, m_MousePosView, GetGridIndex(), m_ColumnsNumber, m_Side);
					}
					else if (m_LeftClickNodeFlag && (GetGridIndex() < 0 || GetGridIndex() > m_Grid.size()))
					{
						m_LeftClickNodeFlag = false;
						m_StartNode->SetPosition(m_StartNode->GetPosition().x, m_StartNode->GetPosition().y);
						int ColumnIndex = m_StartNode->GetPosition().x / m_Side;
						int RowIndex = m_StartNode->GetPosition().y / m_Side - 4;
						int LocalIndex = RowIndex * m_ColumnsNumber + ColumnIndex;
						m_Grid[LocalIndex]->SetDistance(1);
						m_StartNode->SetIndex(LocalIndex);
						m_Grid[LocalIndex]->ChangeToIdleState();

						m_EndNode->SetPosition(m_EndNode->GetPosition().x, m_EndNode->GetPosition().y);
						ColumnIndex = m_EndNode->GetPosition().x / m_Side;
						RowIndex = m_EndNode->GetPosition().y / m_Side - 4;
						LocalIndex = RowIndex * m_ColumnsNumber + ColumnIndex;
						m_Grid[LocalIndex]->SetDistance(0);
						m_EndNode->SetIndex(LocalIndex);
						m_Grid[LocalIndex]->ChangeToIdleState();

						m_Grid[m_StartNode->GetIndex()]->SetGlobalDistance(Heuristic(m_StartNode, m_EndNode));
						m_Grid[m_StartNode->GetIndex()]->SetLocalDistance(0);
					}

					if (m_LeftClickGridFlag)
					{
						m_LeftClickGridFlag = false;
					}

					if (m_Buttons["VISUALISE"]->Contains(m_MousePosView) && !m_RestartFlag)
					{
						std::thread Thread(&alg::Algorithm::Run, std::ref(*m_Algorithms[m_ActiveElementText]),
							std::ref(*m_StartNode), std::ref(*m_EndNode), std::ref(m_Grid), std::ref(m_VisualiseFlag), 
							std::ref(m_RestartFlag));
						Thread.detach();
					}

					if (m_Buttons["EXIT_STATE"]->Contains(m_MousePosView))
					{
						m_Quit = true;
					}

					// Clear Button
					if (m_Buttons["RESTART_GRID"]->Contains(m_MousePosView))
					{
						for (auto& e : m_Grid)
						{
							e->ChangeToIdleState();
						}
						m_StartNode->SetPosition(m_Grid[976]->GetPosition().x, m_Grid[976]->GetPosition().y);
						m_StartNode->SetIndex(976);
						m_EndNode->SetPosition(m_Grid[1007]->GetPosition().x, m_Grid[1007]->GetPosition().y);
						m_EndNode->SetIndex(1007);
						m_Grid[m_StartNode->GetIndex()]->SetDistance(1);
						m_Grid[m_StartNode->GetIndex()]->SetGlobalDistance(Heuristic(m_StartNode, m_EndNode));
						m_Grid[m_StartNode->GetIndex()]->SetLocalDistance(0);

						std::cout << "Reset " << m_Grid[m_StartNode->GetIndex()]->GetDistance() << std::endl;
						m_RestartFlag = false;
					}
				}
				else if (m_SfEvent.mouseButton.button == sf::Mouse::Right)
				{
					if (m_RightClickGridFlag)
						m_RightClickGridFlag = false;
				}
			}
			break;
		}
	}
}

