#include "State.h"

State::State(sf::RenderWindow* Window, std::stack<State*>* States)
{
	m_States = States;
	std::cout << "Created State\n";
	m_Window = Window;
	m_Quit = false;
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

void State::CheckForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		m_Quit = true;
}

void State::UpdateMousePositions()
{
	m_MousePosScreen = sf::Mouse::getPosition();
	m_MousePosWindow = sf::Mouse::getPosition(*m_Window);
	m_MousePosView = m_Window->mapPixelToCoords(sf::Mouse::getPosition(*m_Window));
	system("cls");
	std::cout << "m_MousePosScreen: " << m_MousePosScreen.x << ", " << m_MousePosScreen.y << std::endl;
	std::cout << "m_MousePosWindow: " << m_MousePosWindow.x << ", " << m_MousePosWindow.y << std::endl;
	std::cout << "m_MousePosView: " << m_MousePosView.x << ", " << m_MousePosView.y << std::endl;
}
