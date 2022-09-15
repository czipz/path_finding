#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height, std::string Text,
	sf::Color IdleColor, sf::Color HoverColor, sf::Color ActiveColor)
{
	m_ButtonState = BUTTON_STATES::BTN_IDLE;

	m_Button.setPosition(sf::Vector2f(x, y));
	m_Button.setSize(sf::Vector2f(width, height));

	m_Font.loadFromFile("Fonts/font1.ttf");
	m_Text.setFont(m_Font);
	m_Text.setString(Text);
	m_Text.setFillColor(sf::Color::White);
	m_Text.setCharacterSize(25);
	m_Text.setPosition(
		m_Button.getPosition().x + (width / 2.f) - m_Text.getGlobalBounds().width / 2.f,
		m_Button.getPosition().y + (height / 2.f) - m_Text.getGlobalBounds().height / 1.3f /*2.f*/
		);

	m_IdleColor = IdleColor;
	m_HoverColor = HoverColor;
	m_ActiveColor = ActiveColor;

	m_Button.setFillColor(m_IdleColor);
}

gui::Button::~Button()
{

}

bool gui::Button::IsPressed() const
{
	if (m_ButtonState == BUTTON_STATES::BTN_ACTIVE)
		return true;

	return false; 
}

std::string gui::Button::GetText() const
{

	return m_Text.getString();
}

void gui::Button::SetText(const sf::String& Text)
{
	m_Text.setString(Text);
	m_Text.setPosition(
		m_Button.getPosition().x + (m_Button.getSize().x / 2.f) - m_Text.getGlobalBounds().width / 2.f,
		m_Button.getPosition().y + (m_Button.getSize().y / 2.f) - m_Text.getGlobalBounds().height / 1.3f /*2.f*/
	);
}

void gui::Button::Update(const sf::Vector2f& MousePos)
{
	m_ButtonState = BUTTON_STATES::BTN_IDLE;

	if (m_Button.getGlobalBounds().contains(MousePos))
	{
		m_ButtonState = BUTTON_STATES::BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_ButtonState = BUTTON_STATES::BTN_ACTIVE;
		}
	}

	switch (m_ButtonState)
	{
	case BUTTON_STATES::BTN_IDLE:
		m_Button.setFillColor(m_IdleColor);
		break;
	case BUTTON_STATES::BTN_HOVER:
		m_Button.setFillColor(m_HoverColor);
		break;
	case BUTTON_STATES::BTN_ACTIVE:
		m_Button.setFillColor(m_ActiveColor);
		break;
	default:
		m_Button.setFillColor(sf::Color::Red);
		break;
	}
}

void gui::Button::Render(sf::RenderTarget* Target)
{
	Target->draw(m_Button);
	Target->draw(m_Text);
}

////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

gui::DropDownList::DropDownList(float x, float y, float width, float height, std::vector<std::string> List, unsigned NrOfElements, unsigned default_index)
	: m_ShowList(false), m_KeyTimeMax(1.f), m_KeyTime(0.f)
{
	m_ActiveElement = new gui::Button(x, y, width, height, List[1],
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	for (int i = 0; i < NrOfElements; ++i)
	{
		m_List.push_back(new gui::Button(x, y + ((i+1) * height), width, height, List[i],
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)));
	}
}

gui::DropDownList::~DropDownList()
{
	delete m_ActiveElement;
	for (auto& e : m_List)
	{
		delete e;
	}
}

bool gui::DropDownList::GetKeyTime()
{
	if (m_KeyTime >= m_KeyTimeMax)
	{
		m_KeyTime = 0.f;
		return true;
	}
	else
		return false;
}

void gui::DropDownList::UpdateKeyTime(const float& ElapsedTime)
{
	if (m_KeyTime < m_KeyTimeMax)
		m_KeyTime += 10.f * ElapsedTime;
}

void gui::DropDownList::Update(const sf::Vector2f& MousePos, const float& ElapsedTime)
{
	this->UpdateKeyTime(ElapsedTime);

	m_ActiveElement->Update(MousePos);
	if (m_ActiveElement->IsPressed() && this->GetKeyTime())
	{
		if (m_ShowList)
			m_ShowList = false;
		
		else
			m_ShowList = true;
	}

	if (m_ShowList)
	{
		for (auto& i : m_List)
		{
			i->Update(MousePos);

			if (i->IsPressed() && this->GetKeyTime())
			{
				m_ShowList = false;
				m_ActiveElement->SetText(i->GetText());
			}
		}
	}
}

void gui::DropDownList::Render(sf::RenderTarget* Target)
{
	m_ActiveElement->Render(Target);

	if (m_ShowList)
	{
		for (auto& i : m_List)
		{
			i->Render(Target);
		}
	}
}

/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

gui::Grid::Grid(const float& x, const float& y, const float& side,
	sf::Color IdleColor, sf::Color ActiveColor, sf::Color OutlineColor)
	: m_KeyTimeMax(4.f), m_KeyTime(0.f)
{
	m_GridState = GRID_STATES::GRID_IDLE;

	m_Grid.setFillColor(IdleColor);
	m_Grid.setOutlineColor(OutlineColor);
	m_Grid.setOutlineThickness(2);
	m_Grid.setPosition(sf::Vector2f(x, y));
	m_Grid.setSize(sf::Vector2f(side, side));

	m_IdleColor = IdleColor;
	m_ActiveColor = ActiveColor;
	m_OutlineColor = OutlineColor;
}

gui::Grid::~Grid()
{
	
}

bool gui::Grid::GetKeyTime()
{
	if (m_KeyTime >= m_KeyTimeMax)
	{
		m_KeyTime = 0.f;
		return true;
	}
	else
		return false;
}

void gui::Grid::UpdateKeyTime(const float& ElapsedTime)
{
	if (m_KeyTime < m_KeyTimeMax)
		m_KeyTime += 10.f * ElapsedTime;
}

bool gui::Grid::IsPressed() const
{
	if (m_GridState == GRID_STATES::GRID_ACTIVE)
		return true;

	return false;
}

void gui::Grid::ChangeToIdleState()
{
	if (m_GridState == GRID_STATES::GRID_ACTIVE)
		m_GridState = GRID_STATES::GRID_IDLE;
}

const sf::Vector2f& gui::Grid::GetPosition() const
{
	return m_Grid.getPosition();
}

void gui::Grid::Update(const sf::Vector2f& MousePos, const float& ElapsedTime)
{
	this->UpdateKeyTime(ElapsedTime);

	if (m_Grid.getGlobalBounds().contains(MousePos) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		m_GridState == GRID_STATES::GRID_IDLE &&
		this->GetKeyTime())
	{
		m_GridState = GRID_STATES::GRID_ACTIVE;
	}

	//if (m_Grid.getGlobalBounds().contains(MousePos) &&
	//	sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
	//	m_GridState == GRID_STATES::GRID_ACTIVE &&
	//	this->GetKeyTime())
	//{
	//	m_GridState = GRID_STATES::GRID_IDLE;
	//}


	switch (m_GridState)
	{
	case GRID_STATES::GRID_IDLE:
		m_Grid.setFillColor(m_IdleColor);
		break;
	case GRID_STATES::GRID_ACTIVE:
		m_Grid.setFillColor(m_ActiveColor);
		break;
	default:
		m_Grid.setFillColor(sf::Color::Red);
		break;
	}
}

void gui::Grid::Render(sf::RenderTarget* Target)
{
	Target->draw(m_Grid);
}

////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

gui::GridStartNode::GridStartNode(const float& x, const float& y, const float& size)
{
	m_StartTexture.loadFromFile("Images/Sprites/arrow.png");
	m_StartSprite.setPosition(sf::Vector2f(x, y));
	m_StartSprite.setSize(sf::Vector2f(size, size));
	m_StartSprite.setTexture(&m_StartTexture);
}

gui::GridStartNode::~GridStartNode()
{

}

const sf::Vector2f& gui::GridStartNode::GetPosition() const
{
	// TODO: insert return statement here
}

void gui::GridStartNode::SetPosition()
{
}

void gui::GridStartNode::Update(const sf::Vector2f&, const float&)
{

}

void gui::GridStartNode::Render(sf::RenderTarget* Target)
{
	Target->draw(m_StartSprite);
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

gui::GridEndNode::GridEndNode(const float& x, const float& y, const float& size)
{
	m_EndTexture.loadFromFile("Images/Sprites/destination.png");
	m_EndSprite.setPosition(sf::Vector2f(x, y));
	m_EndSprite.setSize(sf::Vector2f(size, size));
	m_EndSprite.setTexture(&m_EndTexture);
}

gui::GridEndNode::~GridEndNode()
{

}

const sf::Vector2f& gui::GridEndNode::GetPosition() const
{
	// TODO: insert return statement here
}

void gui::GridEndNode::SetPosition()
{
}

void gui::GridEndNode::Update(const sf::Vector2f&, const float&)
{

}

void gui::GridEndNode::Render(sf::RenderTarget* Target)
{
	Target->draw(m_EndSprite);
}
