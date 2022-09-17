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
	: State(Window, States), m_Side(20), m_ActiveElementText(ActiveElementText), m_AlgList(AlgList)
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

	// Update Nodes
	m_StartNode->Update(m_MousePosView, m_Side, m_Grid, ElapsedTime);
	m_EndNode->Update(m_MousePosView, m_Side, m_Grid, ElapsedTime);

	// Update Grid
	for (const auto& e : m_Grid)
	{
		e->Update(m_MousePosView, ElapsedTime, m_StartNode, m_EndNode);
	}

	// Exit Button
	if (m_Buttons["EXIT_STATE"]->IsPressed())
	{
		m_Quit = true;
	}

	// Clear Button
	if (m_Buttons["RESTART_GRID"]->IsPressed())
	{
		for (auto& e : m_Grid)
		{
			e->ChangeToIdleState();
		}
		m_StartNode->SetPosition(m_Grid[976]->GetPosition().x, m_Grid[976]->GetPosition().y);
		m_EndNode->SetPosition(m_Grid[1007]->GetPosition().x, m_Grid[1007]->GetPosition().y);
		m_Grid[976]->SetDistance(1);
		std::cout << "Reset " << m_Grid[976]->GetDistance() << std::endl;
	}

	// Exit Button
	if (m_Buttons["VISUALISE"]->IsPressed())
	{
		//std::cout << m_ActiveElementText << std::endl;
		m_Algorithms[m_ActiveElementText]->Run(*m_StartNode, *m_EndNode, ElapsedTime, m_Grid);
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

void AppState::UpdateInput(const float& ElapsedTime)
{
	this->CheckForQuit();
}

void AppState::Update(const float& ElapsedTime)
{
	this->UpdateMousePositions();
	this->UpdateInput(ElapsedTime);
	this->UpdateGui(ElapsedTime);
}

void AppState::Render()
{
	m_Window->draw(m_Background);
	m_Window->draw(m_Text);
	this->RenderGui();
}
