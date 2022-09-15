#include "AppState.h"

void AppState::InitGui()
{
	m_Buttons["EXIT_STATE"] = new gui::Button(700, 500, 200, 50, "Exit",
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

AppState::AppState(sf::RenderWindow* Window, std::stack<State*>* States)
	: State(Window, States)
{
	std::cout << "Created App State\n";
	this->InitGui();
	m_Background.setSize(sf::Vector2f(m_Window->getSize().x, m_Window->getSize().y));
	m_Background.setFillColor(sf::Color(0, 0, 100));
}

AppState::~AppState()
{
	std::cout << "Ending Game State\n";
}

void AppState::UpdateGui(const float& ElapsedTime)
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		it->second->Update(m_MousePosView);
	}

	// exit 
	if (m_Buttons["EXIT_STATE"]->IsPressed())
	{
		m_Quit = true;
	}
}

void AppState::RenderGui()
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		it->second->Render(m_Window);
	}
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
