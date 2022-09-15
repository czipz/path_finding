#include "AppState.h"

void AppState::InitGui()
{
	//Init Buttons
	m_Buttons["EXIT_STATE"] = new gui::Button(m_Window->getSize().x - 200,
		m_Window->getSize().y - 700, 150, 50, "Back",
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	
	m_Buttons["CLEAR_GRID"] = new gui::Button(m_Window->getSize().x - 400,
		m_Window->getSize().y - 700, 150, 50, "Clear",
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	m_Buttons["RUN_ALGORITHM"] = new gui::Button(m_Window->getSize().x - 650,
		m_Window->getSize().y - 700, 200, 50, "Run",
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	// Init Grid
	unsigned short side = 20;
	for (unsigned y = 5; y < (m_Window->getSize().y / side) - 1; ++y)
	{
		for (unsigned x = 1; x < (m_Window->getSize().x / side) - 1; ++x)
			m_Grid.push_back(new gui::Grid(side * x, side * y, side, 
				sf::Color(169, 169, 169), sf::Color::Black, sf::Color::White));
	}

	//Init Grid Nodes
	m_StartNode = new gui::GridStartNode(m_Grid[1]->GetPosition().x, m_Grid[1]->GetPosition().y, side);
	m_EndNode = new gui::GridEndNode(m_Grid[2]->GetPosition().x - 1, m_Grid[2]->GetPosition().y - 1, side);
}

AppState::AppState(sf::RenderWindow* Window, std::stack<State*>* States)
	: State(Window, States)
{
	std::cout << "Created App State\n";
	this->InitGui();
	m_Background.setSize(sf::Vector2f(m_Window->getSize().x, m_Window->getSize().y));
	m_Background.setFillColor(sf::Color(47, 79, 79));
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

	for (const auto& e : m_Grid)
	{
		e->Update(m_MousePosView, ElapsedTime);
	}

	// exit 
	if (m_Buttons["EXIT_STATE"]->IsPressed())
	{
		m_Quit = true;
	}

	if (m_Buttons["CLEAR_GRID"]->IsPressed())
	{
		for (auto& e : m_Grid)
		{
			e->ChangeToIdleState();
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
