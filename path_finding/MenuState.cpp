#include "MenuState.h"

void MenuState::InitGui()
{
	m_Buttons["EXIT_STATE"] = new gui::Button(m_Window->getSize().x - 200,
		m_Window->getSize().y - 75, 150, 50, "Exit",
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	m_Buttons["APP_STATE"] = new gui::Button(m_Window->getSize().x - 570,
		m_Window->getSize().y / 2 - 25, 150, 50, "Start",
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));


	m_AlgList = { "A*", "Dijkstra's", "Wavefront"};
	m_DropDownLists["ALGORITHMS"] = new gui::DropDownList(m_Window->getSize().x - 900, 
		m_Window->getSize().y / 2 - 25, 200, 50, m_AlgList, m_AlgList.size(), 0);
}

void MenuState::InitBackground()
{
	m_Background.setSize(sf::Vector2f(m_Window->getSize().x, m_Window->getSize().y));
	m_BackgroundTexture.loadFromFile("Images/Backgrounds/bg.png");
	m_Background.setTexture(&m_BackgroundTexture);
	m_Font.loadFromFile("Fonts/font1.ttf");
	m_Text.setFont(m_Font);
	m_Text.setString("Choose an algorithm:");
	m_Text.setFillColor(sf::Color::White);
	m_Text.setCharacterSize(19);
	m_Text.setPosition(390, 308);
}

MenuState::MenuState(sf::RenderWindow* Window, std::stack<State*>* States)
	: State(Window, States)
{
	Init();
}

MenuState::~MenuState()
{
	std::cout << "Destroyed Menu State\n";
	for (auto it = m_DropDownLists.begin(); it != m_DropDownLists.end(); ++it)
	{
		delete it->second;
	}
}

void MenuState::UpdateGui()
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		it->second->Update(m_MousePosView);
	}

	for (auto& [k, v] : m_DropDownLists)
	{
		v->UpdateButtonState(m_MousePosView);
	}
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

void MenuState::UpdateSFMLEvents()
{
	while (m_Window->pollEvent(m_SfEvent))
	{
		switch (m_SfEvent.type)
		{
		case sf::Event::Closed:
			m_Window->close();
			break;

		case sf::Event::MouseButtonReleased:
			if (m_SfEvent.mouseButton.button == sf::Mouse::Left)
			{
				// Start app
				if (m_Buttons["APP_STATE"]->Contains(m_MousePosView))
				{
					m_States->push(new AppState(m_Window, m_States, m_AlgList,
						m_DropDownLists["ALGORITHMS"]->GetActiveElementText()));
				}
				// exit 
				if (m_Buttons["EXIT_STATE"]->Contains(m_MousePosView))
				{
					m_Quit = true;
				}
				m_DropDownLists["ALGORITHMS"]->Update(m_MousePosView);
			}
			break;
		}
	}
}
