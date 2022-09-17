#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height, std::string Text,
	sf::Color IdleColor, sf::Color HoverColor, sf::Color ActiveColor)
{
	m_ButtonState = BUTTON_STATES::BTN_IDLE;

	m_Button.setPosition(sf::Vector2f(x, y));
	m_Button.setSize(sf::Vector2f(width, height));
	m_Button.setOutlineColor(sf::Color::Black);
	m_Button.setOutlineThickness(1);

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

void gui::Button::setOutlineThickness(int thick)
{
	m_Button.setOutlineThickness(thick);
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
////////////////////////////////////////////////////////////

gui::DropDownList::DropDownList(float x, float y, float width, float height, 
	std::vector<std::string> List, unsigned NrOfElements, unsigned default_index)
	: m_ShowList(false), m_KeyTimeMax(2.f), m_KeyTime(0.f)
{
	m_ActiveElement = new gui::Button(x, y, width, height, List[0],
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	for (int i = 0; i < NrOfElements; ++i)
	{
		m_List.push_back(new gui::Button(x, y + ((i+1) * height), width, height, List[i],
			sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)));
	}

	// Triangle on the Drop Down List
	m_Triangle.setRadius(10.f);
	m_Triangle.setPointCount(3);
	m_Triangle.setFillColor(sf::Color::White);
	m_Triangle.setPosition(560, 360);
	m_Triangle.setOrigin(10, 6.67);
	m_Triangle.rotate(180);
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

std::string gui::DropDownList::GetActiveElementText() const
{
	return m_ActiveElement->GetText();
}

void gui::DropDownList::Update(const sf::Vector2f& MousePos, const float& ElapsedTime)
{
	this->UpdateKeyTime(ElapsedTime);

	m_ActiveElement->Update(MousePos);
	if (m_ActiveElement->IsPressed() && this->GetKeyTime())
	{
		if (m_ShowList)
		{	
			m_ActiveElement->setOutlineThickness(1);
			m_Triangle.rotate(180);
			m_ShowList = false;
		}
		else
		{
			m_ActiveElement->setOutlineThickness(-3);
			m_Triangle.rotate(180);
			m_ShowList = true;
		}
	}

	if (m_ShowList)
	{
		for (auto& i : m_List)
		{
			i->Update(MousePos);

			if (i->IsPressed() && this->GetKeyTime())
			{
				m_ActiveElement->setOutlineThickness(1);
				m_Triangle.rotate(180);
				m_ShowList = false;
				m_ActiveElement->SetText(i->GetText());
			}
		}
	}
}

void gui::DropDownList::Render(sf::RenderTarget* Target)
{
	m_ActiveElement->Render(Target);
	Target->draw(m_Triangle);

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
	m_Grid.setOutlineThickness(-1);
	m_Grid.setPosition(sf::Vector2f(x, y));
	m_Grid.setSize(sf::Vector2f(side, side));
	m_Distance = 0;

	if (ActiveColor == sf::Color(0, 0, 0, 0))
	{
		m_GridState = GRID_STATES::GRID_ACTIVE;
		m_Grid.setFillColor(ActiveColor);
		m_Distance = -1;
	}

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
	//std::cout << m_KeyTime << std::endl;
}

void gui::Grid::ChangeToIdleState()
{
	if (m_GridState == GRID_STATES::GRID_ACTIVE && m_Grid.getFillColor() != sf::Color(0, 0, 0, 0))
		m_GridState = GRID_STATES::GRID_IDLE;
	if (m_Grid.getFillColor() != sf::Color(0, 0, 0, 0))
		m_Distance = 0;
}

const sf::Vector2f& gui::Grid::GetPosition() const
{
	return m_Grid.getPosition();
}

bool gui::Grid::IsActive() const
{
	if (m_GridState == GRID_STATES::GRID_ACTIVE)
		return true;
	
	return false;
}

bool gui::Grid::Contains(const sf::Vector2f& Something) const
{
	return m_Grid.getGlobalBounds().contains(Something);
}

int gui::Grid::GetDistance() const
{
	return m_Distance;
}

void gui::Grid::SetDistance(int Distance) 
{
	m_Distance = Distance;
}

void gui::Grid::Update(const sf::Vector2f& MousePos, const float& ElapsedTime,
	 GridStartNode* StartNode, GridEndNode* EndNode)
{
	this->UpdateKeyTime(ElapsedTime);

	if (m_Grid.getGlobalBounds().contains(MousePos) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		m_GridState == GRID_STATES::GRID_IDLE && this->GetKeyTime() && 
		!(m_Grid.getGlobalBounds().contains(StartNode->GetPosition()) ||
			m_Grid.getGlobalBounds().contains(EndNode->GetPosition())))
	{
		m_GridState = GRID_STATES::GRID_ACTIVE;
		m_Distance = -1;
		std::cout << "Left click " << m_Distance << std::endl;
	}

	if (m_Grid.getGlobalBounds().contains(MousePos) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Right) &&
		m_GridState == GRID_STATES::GRID_ACTIVE && this->GetKeyTime() &&
		m_Grid.getFillColor() != sf::Color(0, 0, 0, 0))
	{
		m_GridState = GRID_STATES::GRID_IDLE;
		m_Distance = 0;
		std::cout << "Right click " << m_Distance << std::endl;
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
	: m_KeyTimeMax(4.f), m_KeyTime(0.f), m_NodeFlag(false)
{
	m_StartTexture.loadFromFile("Images/Sprites/arrow.png");
	m_StartingPoint.setPosition(sf::Vector2f(x, y));
	m_StartingPoint.setTexture(&m_StartTexture);
	m_StartingPoint.setSize(sf::Vector2f(size, size));
}

gui::GridStartNode::~GridStartNode()
{

}

bool gui::GridStartNode::GetKeyTime()
{
	if (m_KeyTime >= m_KeyTimeMax)
	{
		m_KeyTime = 0.f;
		return true;
	}
	else
		return false;
}

void gui::GridStartNode::UpdateKeyTime(const float& ElapsedTime)
{
	if (m_KeyTime < m_KeyTimeMax)
		m_KeyTime += 10.f * ElapsedTime;
}

const sf::Vector2f& gui::GridStartNode::GetPosition() const
{
	return m_StartingPoint.getPosition();
}

void gui::GridStartNode::SetPosition(const float& x, const float& y)
{
	m_StartingPoint.setPosition(sf::Vector2f(x, y));
}

void gui::GridStartNode::UpdateNodePosition(const sf::Vector2f& MousePos, const std::vector<Grid*>& Grid)
{
	 //Drop  the node
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_NodeFlag && GetKeyTime() &&
		!std::any_of(Grid.begin(), Grid.end(), [&MousePos](auto& x)
			{ return (x->IsActive() && x->Contains(MousePos)); }))
	{
		m_NodeFlag = false;
		for (auto& e : Grid)
		{
			if (e->Contains(this->GetPosition()))
			{
				e->SetDistance(1);
				std::cout << "Drop " << e->GetDistance() << std::endl;
			}
		}
	}


	// Pick up the node
	if (m_StartingPoint.getGlobalBounds().contains(MousePos) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left) && GetKeyTime())
	{
		m_NodeFlag = true;
		for (auto& e : Grid)
		{
			if (e->GetDistance() == 1)
			{
				e->SetDistance(0);
				std::cout << "Pickup " << e->GetDistance() << std::endl;
			}
		}
	}

	if (m_NodeFlag)
	{
		for (const auto& e : Grid)
		{
			if (e->Contains(MousePos) && !e->IsActive())
			{
				m_StartingPoint.setPosition(e->GetPosition());
			}
		}
	}
}

void gui::GridStartNode::Update(const sf::Vector2f& MousePos,
	const float& side, const std::vector<Grid*>& Grid, const float& ElapsedTime)
{
	this->UpdateKeyTime(ElapsedTime);
	this->UpdateNodePosition(MousePos, Grid);

}

void gui::GridStartNode::Render(sf::RenderTarget* Target)
{
	Target->draw(m_StartingPoint);
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

gui::GridEndNode::GridEndNode(const float& x, const float& y, const float& size)
	: m_KeyTimeMax(4.f), m_KeyTime(0.f), m_NodeFlag(false)
{
	m_EndTexture.loadFromFile("Images/Sprites/destination.png");
	m_DestinationPoint.setPosition(sf::Vector2f(x, y));
	m_DestinationPoint.setSize(sf::Vector2f(size, size));
	m_DestinationPoint.setTexture(&m_EndTexture);
}

gui::GridEndNode::~GridEndNode()
{

}

bool gui::GridEndNode::GetKeyTime()
{
	if (m_KeyTime >= m_KeyTimeMax)
	{
		m_KeyTime = 0.f;
		return true;
	}
	else
		return false;
}

void gui::GridEndNode::UpdateKeyTime(const float& ElapsedTime)
{
	if (m_KeyTime < m_KeyTimeMax)
		m_KeyTime += 10.f * ElapsedTime;
}

const sf::Vector2f& gui::GridEndNode::GetPosition() const
{
	return m_DestinationPoint.getPosition();
}

void gui::GridEndNode::SetPosition(const float& x, const float& y)
{
	m_DestinationPoint.setPosition(sf::Vector2f(x, y));
}

void gui::GridEndNode::UpdateNodePosition(const sf::Vector2f& MousePos, const std::vector<Grid*>& Grid)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_NodeFlag && GetKeyTime() &&
		!std::any_of(Grid.begin(), Grid.end(), [&MousePos](auto& x)
			{ return (x->IsActive() && x->Contains(MousePos)); }))
		m_NodeFlag = false;

	if (m_DestinationPoint.getGlobalBounds().contains(MousePos) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left) && GetKeyTime())
	{
		m_NodeFlag = true;
	}

	if (m_NodeFlag)
	{
		for (const auto& e : Grid)
		{
			if (e->Contains(MousePos) && !e->IsActive())
			{
				m_DestinationPoint.setPosition(e->GetPosition());
			}
		}
	}
}

void gui::GridEndNode::Update(const sf::Vector2f& MousePos, 
	const float& side, const std::vector<Grid*>& Grid, const float& ElapsedTime)
{
	this->UpdateKeyTime(ElapsedTime);
	this->UpdateNodePosition(MousePos, Grid);

}

void gui::GridEndNode::Render(sf::RenderTarget* Target)
{
	Target->draw(m_DestinationPoint);
}
