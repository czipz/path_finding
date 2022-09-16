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

	m_Buttons["RUN_ALGORITHM"] = new gui::Button(m_Window->getSize().x - 600,
		m_Window->getSize().y - 700, 150, 50, "Run",
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	// Init Grid
	for (unsigned y = 5; y < (m_Window->getSize().y / m_Side) - 1; ++y)
	{
		for (unsigned x = 1; x < (m_Window->getSize().x / m_Side) - 1; ++x)
			m_Grid.push_back(new gui::Grid(m_Side * x, m_Side * y, m_Side,
				sf::Color(169, 169, 169), sf::Color::Black, sf::Color::White));
	}

	//Init Grid Nodes
	m_StartNode = new gui::GridStartNode(m_Grid[883]->GetPosition().x, m_Grid[883]->GetPosition().y, m_Side);
	m_EndNode = new gui::GridEndNode(m_Grid[914]->GetPosition().x, m_Grid[914]->GetPosition().y, m_Side);
}

void AppState::InitBackground()
{
	m_Background.setSize(sf::Vector2f(m_Window->getSize().x, m_Window->getSize().y));
	m_BackgroundTexture.loadFromFile("Images/Backgrounds/bg2.png");
	m_Background.setTexture(&m_BackgroundTexture);
}

AppState::AppState(sf::RenderWindow* Window, std::stack<State*>* States)
	: State(Window, States), m_Side(20)
{
	std::cout << "Created App State\n";
	this->InitGui();
	this->InitBackground();
}

AppState::~AppState()
{
	std::cout << "Ending Game State\n";

	delete m_StartNode;
	delete m_EndNode;

	for (auto& e : m_Grid)
	{
		delete e;
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
		m_StartNode->SetPosition(m_Grid[883]->GetPosition().x, m_Grid[883]->GetPosition().y);
		m_EndNode->SetPosition(m_Grid[914]->GetPosition().x, m_Grid[914]->GetPosition().y);
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
	this->RenderGui();
}
