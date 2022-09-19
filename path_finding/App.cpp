
#include "App.h"

void App::InitWindow()
{
	m_Window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Path Finding", sf::Style::Close);
    m_Window->setFramerateLimit(120);
}

void App::InitStates()
{
    m_States.push(new MenuState(m_Window, &m_States));
}

App::App()
{
    std::cout << "Starting App!\n";
    this->InitWindow();
    this->InitStates();
}

App::~App()
{
	delete m_Window;
    while (!m_States.empty())
    {
        delete m_States.top();
        m_States.pop();
    }
    std::cout << "Ending App!\n";
}

void App::UpdateElapsedTime()
{
    m_ElapsedTime = m_ElapsedTimeClock.restart().asSeconds();
    //std::cout << "ElapsedTime: " << m_ElapsedTime << std::endl;
}


void App::Update()
{
    if (!m_States.empty())
    {
        m_States.top()->Update(m_ElapsedTime);
        if (m_States.top()->GetQuit())
        {
            delete m_States.top();
            m_States.pop();
        }
    }
    else
    {
        m_Window->close();
    }
}

void App::Render()
{
    m_Window->clear();

    // Render items
    if (!m_States.empty())
        m_States.top()->Render();

    m_Window->display();
}

void App::Run()
{
    while (m_Window->isOpen())
    {
        this->UpdateElapsedTime();
        this->Update();
        this->Render();
    }
}
