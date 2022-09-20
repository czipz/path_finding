#include "AppState.h"


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

	//Rows Number = m_Window->getSize().y / m_Side - 4;
	m_ColumnsNumber = m_Window->getSize().x / m_Side;

	for (unsigned y = 4; y < (m_Window->getSize().y / m_Side); ++y)
	{
		for (unsigned x = 0; x < (m_Window->getSize().x / m_Side); ++x)
		{
			if (y == 4  || y == m_Window->getSize().y / m_Side - 1 || x == 0 || x == m_Window->getSize().x / m_Side - 1)
				m_Grid.push_back(new gui::Grid(m_Side * x, m_Side * y, m_Side,
					sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0)));
			else
				m_Grid.push_back(new gui::Grid(m_Side * x, m_Side * y, m_Side,
					sf::Color(169, 169, 169), sf::Color::Black, sf::Color::White));
		}
	}

	//Init Grid Nodes
	m_StartNode = new gui::GridStartNode(m_Grid[976]->GetPosition().x, m_Grid[976]->GetPosition().y, m_Side);
	m_EndNode = new gui::GridEndNode(m_Grid[1007]->GetPosition().x, m_Grid[1007]->GetPosition().y, m_Side);
	m_Grid[976]->SetDistance(1);
}

int AppState::GetGridIndex()
{
	m_MouseX = m_MousePosView.x;
	m_MouseY = m_MousePosView.y;

	m_ColumnIndex = static_cast<int>(m_MouseX / m_Side);
	m_RowIndex = static_cast<int>(m_MouseY / m_Side) - 4;
	m_Index = m_RowIndex * m_ColumnsNumber + m_ColumnIndex;
	//std::cout << "Index = " << m_Index << std::endl;
	return m_Index;
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

AppState::AppState(sf::RenderWindow* Window, std::stack<State*>* States, 
	const std::vector<std::string>& AlgList, const std::string& ActiveElementText)
	: State(Window, States), m_Side(20), m_ActiveElementText(ActiveElementText), m_AlgList(AlgList),
		m_VisualiseFlag(false), m_LeftClickNodeFlag(false), m_LeftClickGridFlag(false), m_RightClickGridFlag(false)
{
	std::cout << "Created App State\n";
	this->InitGui();
	this->InitBackground();


	m_Algorithms.emplace("A*", new alg::A_Star());
	m_Algorithms.emplace("Dijkstra's", new alg::Dijkstra());
	m_Algorithms.emplace("Wavefront", new alg:: Wavefront());

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

void AppState::UpdateGui(const float& ElapsedTime)
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		it->second->Update(m_MousePosView);
	}

	if (GetGridIndex() >= 0 && GetGridIndex() < m_Grid.size())
	{
		if (m_LeftClickNodeFlag && !m_EndNode->GetNodeFlag())
			m_StartNode->Update(m_MousePosView, m_Grid, *m_EndNode, GetGridIndex());

		if (m_LeftClickNodeFlag && !m_StartNode->GetNodeFlag())
			m_EndNode->Update(m_MousePosView, m_Grid, *m_StartNode, GetGridIndex());

		if (m_LeftClickGridFlag)
		{
			m_Grid[GetGridIndex()]->UpdateLeft(m_MousePosView, m_StartNode, m_EndNode);
		}

		if (m_RightClickGridFlag)
		{
			m_Grid[GetGridIndex()]->UpdateRight(m_MousePosView, m_StartNode, m_EndNode);
		}
	}


	// Exit Button
	//if (m_Buttons["VISUALISE"]->IsPressed())
	//{
	//	//if (m_ActiveElementText == "A*")
	//	//	std::thread Thread(&alg::A_Star::Run, std::ref(m_A_Star),
	//	//		std::ref(*m_StartNode), std::ref(*m_EndNode), std::ref(ElapsedTime), std::ref(m_Grid));
	//	//else if (m_ActiveElementText == "Dijkstra's")
	//	//	std::thread Thread(&alg::Dijkstra::Run, std::ref(m_Dijkstra),
	//	//		std::ref(*m_StartNode), std::ref(*m_EndNode), std::ref(ElapsedTime), std::ref(m_Grid));
	//	//else if (m_ActiveElementText == "Wavefront")
	//	//	std::thread Thread(&alg::Wavefront::Run, std::ref(m_Wavefront),
	//	//		std::ref(*m_StartNode), std::ref(*m_EndNode),  std::ref(ElapsedTime), std::ref(m_Grid));
	//	std::thread Thread(&alg::Algorithm::Run, std::ref(*m_Algorithms[m_ActiveElementText]),
	//		std::ref(*m_StartNode), std::ref(*m_EndNode), std::ref(ElapsedTime), std::ref(m_Grid));
	//}
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

void AppState::Update(const float& ElapsedTime)
{
	UpdateMousePositions();
	UpdateSFMLEvents(ElapsedTime);
	UpdateGui(ElapsedTime);
}

void AppState::Render()
{
	m_Window->draw(m_Background);
	m_Window->draw(m_Text);
	this->RenderGui();
}

void AppState::UpdateSFMLEvents(const float& ElapsedTime)
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
			if (!m_VisualiseFlag)
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
					if (m_LeftClickNodeFlag)
					{
						m_LeftClickNodeFlag = false;
						m_StartNode->SetNodeFlag(*m_EndNode, m_Grid, m_MousePosView, GetGridIndex(), m_ColumnsNumber, m_Side);
						m_EndNode->SetNodeFlag(*m_StartNode, m_Grid, m_MousePosView, GetGridIndex(), m_ColumnsNumber, m_Side);
					}

					if (m_LeftClickGridFlag)
					{
						m_LeftClickGridFlag = false;
					}

					if (m_Buttons["VISUALISE"]->Contains(m_MousePosView))
					{
						m_VisualiseFlag = true;
						std::thread Thread(&alg::Algorithm::Run, std::ref(*m_Algorithms[m_ActiveElementText]),
							std::ref(*m_StartNode), std::ref(*m_EndNode), std::ref(ElapsedTime), std::ref(m_Grid), std::ref(m_VisualiseFlag));
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
						m_Grid[976]->SetDistance(1);

						std::cout << "Reset " << m_Grid[976]->GetDistance() << std::endl;
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

