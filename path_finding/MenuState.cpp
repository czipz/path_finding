#include "MenuState.h"

void MenuState::InitButtons()
{
	m_Buttons["APP_STATE"] = new Button(100, 100, 200, 50, "Start",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	m_Buttons["EXIT_STATE"] = new Button(300, 300, 200, 50, "Exit",
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

MenuState::MenuState(sf::RenderWindow* Window, std::stack<State*>* States)
	: State(Window, States)
{
	this->InitButtons();
	std::cout << "Created Menu State\n";
	m_Background.setSize(sf::Vector2f(m_Window->getSize().x, m_Window->getSize().y));
	m_Background.setFillColor(sf::Color(0, 0, 100));
}

MenuState::~MenuState()
{
	std::cout << "Destroyed Menu State\n";
}

void MenuState::UpdateButtons()
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		it->second->Update(m_MousePosView);
	}

	// Start app
	if (m_Buttons["APP_STATE"]->IsPressed())
	{
		m_States->push(new AppState(m_Window, m_States));
	}
	// exit 
	if (m_Buttons["EXIT_STATE"]->IsPressed())
	{
		m_Quit = true;
	}
}

void MenuState::UpdateInput(const float& ElapsedTime)
{
	this->CheckForQuit();
}

void MenuState::Update(const float& ElapsedTime)
{
	this->UpdateInput(ElapsedTime);
	this->UpdateMousePositions();
	this->UpdateButtons();
}

void MenuState::Render()
{
	m_Window->draw(m_Background);
	this->RenderButtons();
}
