#include "State.h"

State::State(sf::RenderWindow* Window, std::stack<State*>* States)
	: m_States(States)
	, m_Window(Window)
	, m_Quit(false)
{
}

State::~State()
{
	std::cout << "Deleted State\n";
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		delete it->second;
	}
}

const bool& State::GetQuit() const
{
	return m_Quit;
}

void State::UpdateMousePositions()
{
	m_MousePosView = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_Window));
	//system("cls");
	//std::cout << m_MousePosView.x << " " << m_MousePosView.y;
	//m_MousePosView = m_Window->mapPixelToCoords(sf::Mouse::getPosition(*m_Window));
}

void State::RenderBackground()
{
	m_Window->draw(m_Background);
}

void State::RenderText()
{
	m_Window->draw(m_Text);
}

void State::Init()
{
	InitGui();
	InitBackground();
}

void State::Update()
{
	UpdateMousePositions();
	UpdateSFMLEvents();
	UpdateGui();
}

void State::Render()
{
	RenderBackground();
	RenderText();
	RenderGui();
}
