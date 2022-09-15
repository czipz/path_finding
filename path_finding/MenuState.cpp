#include "MenuState.h"

void MenuState::InitGui()
{
	m_Buttons["EXIT_STATE"] = new gui::Button(m_Window->getSize().x - 200,
		m_Window->getSize().y - 75, 150, 50, "EXIT",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	m_Buttons["APP_STATE"] = new gui::Button(m_Window->getSize().x - 500,
		m_Window->getSize().y / 2 - 25, 150, 50, "START",
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));


	std::vector<std::string> List = { "A*", "Dijkstra" };
	m_DropDownLists["ALGORITHMS"] = new gui::DropDownList(m_Window->getSize().x - 900, m_Window->getSize().y / 2 - 25, 200, 50, List, List.size(), 0);
}

void MenuState::InitBackground()
{
	m_Background.setSize(sf::Vector2f(m_Window->getSize().x, m_Window->getSize().y));
	m_BackgroundTexture.loadFromFile("Images/Backgrounds/bg.png");
	m_Background.setTexture(&m_BackgroundTexture);
	m_Font.loadFromFile("Fonts/font.ttf");
	m_Text.setFont(m_Font);
	m_Text.setString("Choose an algorithm:");
	m_Text.setFillColor(sf::Color::White);
	m_Text.setCharacterSize(19);
	m_Text.setPosition(390, 308);
}

MenuState::MenuState(sf::RenderWindow* Window, std::stack<State*>* States)
	: State(Window, States)
{
	this->InitBackground();
	this->InitGui();
	std::cout << "Created Menu State\n";
}

MenuState::~MenuState()
{
	std::cout << "Destroyed Menu State\n";
	for (auto it = m_DropDownLists.begin(); it != m_DropDownLists.end(); ++it)
	{
		delete it->second;
	}
}

void MenuState::UpdateGui(const float& ElapsedTime)
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

	m_DropDownLists["ALGORITHMS"]->Update(m_MousePosView, ElapsedTime);
}

void MenuState::RenderGui()
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		it->second->Render(m_Window);
	}

	for (auto it = m_DropDownLists.begin(); it != m_DropDownLists.end(); ++it)
	{
		it->second->Render(m_Window);
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
	this->UpdateGui(ElapsedTime);
}

void MenuState::Render()
{
	m_Window->draw(m_Background);
	m_Window->draw(m_Text);
	this->RenderGui();
}
