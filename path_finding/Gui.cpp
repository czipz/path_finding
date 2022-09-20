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

bool gui::Button::Contains(const sf::Vector2f& Something) const
{
	return m_Button.getGlobalBounds().contains(Something);
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

std::string gui::DropDownList::GetActiveElementText() const
{
	return m_ActiveElement->GetText();
}

void gui::DropDownList::UpdateButtonState(const sf::Vector2f& MousePos)
{
	m_ActiveElement->Update(MousePos);
	for (auto& e : m_List)
	{
		e->Update(MousePos);
	}
}

void gui::DropDownList::Update(const sf::Vector2f& MousePos, const float& ElapsedTime)
{

	//m_ActiveElement->Update(MousePos);
	if (m_ActiveElement->Contains(MousePos)/* && this->GetKeyTime()*/)
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
			//i->Update(MousePos);

			if (i->Contains(MousePos)/* && this->GetKeyTime()*/)
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

gui::Grid::Grid(const float& x, const float& y, const float& side, const int& GridIndex,
	sf::Color IdleColor, sf::Color ActiveColor, sf::Color OutlineColor)
	: m_GridIndex(GridIndex)
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
		m_GridState = GRID_STATES::GRID_BORDER;
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

void gui::Grid::ChangeToIdleState()
{
	if (m_GridState != GRID_STATES::GRID_BORDER)
	{
		m_GridState = GRID_STATES::GRID_IDLE;
		UpdateGridColor();
		m_Distance = 0;
	}	
}

void gui::Grid::ChangeToActiveState()
{
	if (m_GridState == GRID_STATES::GRID_IDLE && m_GridState != GRID_STATES::GRID_BORDER)
	{
		m_GridState = GRID_STATES::GRID_ACTIVE;
		UpdateGridColor();
		m_Distance = -1;
	}
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

bool gui::Grid::isBorder() const
{
	if (m_GridState == GRID_STATES::GRID_BORDER)
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

int gui::Grid::GetGridIndex() const
{
	return m_GridIndex;
}

void gui::Grid::ColorSearch()
{
	m_GridState = GRID_STATES::GRID_SEARCH;
	UpdateGridColor();
}

void gui::Grid::ColorPath()
{
	m_GridState = GRID_STATES::GRID_PATH;
	UpdateGridColor();
}

void gui::Grid::UpdateGridColor()
{
	switch (m_GridState)
	{
	case GRID_STATES::GRID_IDLE:
		m_Grid.setFillColor(m_IdleColor);
		break;
	case GRID_STATES::GRID_ACTIVE:
		m_Grid.setFillColor(m_ActiveColor);
		break;
	case GRID_STATES::GRID_BORDER:
		m_Grid.setFillColor(m_ActiveColor);
		break;
	case GRID_STATES::GRID_SEARCH:
		m_Grid.setFillColor(sf::Color::Blue);
		break;
	case GRID_STATES::GRID_PATH:
		m_Grid.setFillColor(sf::Color::Yellow);
		break;
	default:
		m_Grid.setFillColor(sf::Color::Red);
		break;
	}
}

void gui::Grid::SetDistance(int Distance) 
{
	m_Distance = Distance;
}

void gui::Grid::UpdateLeft(const sf::Vector2f& MousePos,
	 GridStartNode* StartNode, GridEndNode* EndNode)
{
	if (m_GridState != GRID_STATES::GRID_BORDER && m_GridState == GRID_STATES::GRID_IDLE &&
		!(m_Grid.getGlobalBounds().contains(StartNode->GetPosition()) || 
			m_Grid.getGlobalBounds().contains(EndNode->GetPosition())))
	{
		m_GridState = GRID_STATES::GRID_ACTIVE;
		m_Distance = -1;
		std::cout << "Left click " << m_Distance << std::endl;
		UpdateGridColor();
	}
}

void gui::Grid::UpdateRight(const sf::Vector2f& MousePos,
	GridStartNode* StartNode, GridEndNode* EndNode)
{
	if (m_GridState != GRID_STATES::GRID_BORDER && m_GridState == GRID_STATES::GRID_ACTIVE &&
		!(m_Grid.getGlobalBounds().contains(StartNode->GetPosition()) || 
			m_Grid.getGlobalBounds().contains(EndNode->GetPosition())))
	{
		m_GridState = GRID_STATES::GRID_IDLE;
		m_Distance = 0;
		std::cout << "Right click " << m_Distance << std::endl;
		UpdateGridColor();
	}
}

void gui::Grid::Render(sf::RenderTarget* Target)
{
	Target->draw(m_Grid);
}

////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

gui::GridStartNode::GridStartNode(const float& x, const float& y, const float& size)
	: m_NodeFlag(false), m_StartNodeIndex(976), m_ActiveToIdleFlag(false), m_ActiveToIdleIndex(-10000)
{
	m_StartTexture.loadFromFile("Images/Sprites/arrow.png");
	m_StartingPoint.setPosition(sf::Vector2f(x, y));
	m_StartingPoint.setTexture(&m_StartTexture);
	m_StartingPoint.setSize(sf::Vector2f(size, size));
}

gui::GridStartNode::~GridStartNode()
{

}

int gui::GridStartNode::GetIndex() const
{
	return m_StartNodeIndex;
}

void gui::GridStartNode::SetIndex(const int& Index)
{
	m_StartNodeIndex = Index;
}

const sf::Vector2f& gui::GridStartNode::GetPosition() const
{
	return m_StartingPoint.getPosition();
}

void gui::GridStartNode::SetPosition(const float& x, const float& y)
{
	m_StartingPoint.setPosition(sf::Vector2f(x, y));
}

bool gui::GridStartNode::Contains(const sf::Vector2f& Something) const
{
	return m_StartingPoint.getGlobalBounds().contains(Something);
}

void gui::GridStartNode::SetNodeFlag(const gui::GridEndNode& EndNode, std::vector<Grid*>& Grid,
	const sf::Vector2f& MousePos, const int& Index, const int& ColumnsNumber, const int& Side)
{
	if (m_NodeFlag)
	{
		m_NodeFlag = false;

		if (!Grid[Index]->isBorder() && !EndNode.Contains(MousePos))
		{
			Grid[Index]->ChangeToIdleState();
			Grid[Index]->SetDistance(1);
			m_StartNodeIndex = Index;
			std::cout << "Drop " << Grid[Index]->GetDistance() << std::endl;
			
		}
		else if (Grid[Index]->isBorder() || EndNode.Contains(MousePos))
		{
			std::cout << "Border/Node " << Grid[Index]->GetDistance() << std::endl;
			int ColumnIndex = static_cast<int>(m_StartingPoint.getPosition().x / Side);
			int RowIndex = static_cast<int>(m_StartingPoint.getPosition().y / Side) - 4;
			int LocalIndex = RowIndex * ColumnsNumber + ColumnIndex;
			Grid[LocalIndex]->SetDistance(1);
			m_StartNodeIndex = LocalIndex;
			std::cout << "Drop next to border/node " << Grid[LocalIndex]->GetDistance() << std::endl;
			std::cout << "LocalIndex: " << LocalIndex << std::endl;
		}
	}
}

bool gui::GridStartNode::GetNodeFlag() const
{
	return m_NodeFlag;
}

void gui::GridStartNode::Update(const sf::Vector2f& MousePos, const std::vector<Grid*>& Grid,
	const gui::GridEndNode& EndNode, const int& Index)
{
	 //Pick up the node
	int EndNodePositionX = EndNode.GetPosition().x;
	int EndNodePositionY = EndNode.GetPosition().y;
	if (!m_NodeFlag && m_StartingPoint.getGlobalBounds().contains(MousePos))
	{
		Grid[Index]->SetDistance(0);
		std::cout << "Pickup " << Grid[Index]->GetDistance() << std::endl;
		m_NodeFlag = true;
	}

	if (m_NodeFlag && !Grid[Index]->isBorder() && ((MousePos.x < EndNodePositionX - 1 ||
		MousePos.x > EndNodePositionX + 21) || (MousePos.y < EndNodePositionY - 1 ||
			MousePos.y > EndNodePositionY + 21)))
	{
		m_StartingPoint.setPosition(Grid[Index]->GetPosition());
		if (Index >= 0 && Index < Grid.size())
		{
			if (Grid[Index]->IsActive() && !m_ActiveToIdleFlag)
			{
				m_ActiveToIdleIndex = Index;
				Grid[m_ActiveToIdleIndex]->ChangeToIdleState();
				m_ActiveToIdleFlag = true;
			}
			if (m_ActiveToIdleIndex != Index && m_ActiveToIdleFlag)
			{
				Grid[m_ActiveToIdleIndex]->ChangeToActiveState();
				m_ActiveToIdleFlag = false;
			}
		}
	}
}

void gui::GridStartNode::Render(sf::RenderTarget* Target)
{
	Target->draw(m_StartingPoint);
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

gui::GridEndNode::GridEndNode(const float& x, const float& y, const float& size)
	: m_NodeFlag(false), m_EndNodeIndex(1007), m_ActiveToIdleFlag(false), m_ActiveToIdleIndex(-10000)
{
	m_EndTexture.loadFromFile("Images/Sprites/destination.png");
	m_DestinationPoint.setPosition(sf::Vector2f(x, y));
	m_DestinationPoint.setSize(sf::Vector2f(size, size));
	m_DestinationPoint.setTexture(&m_EndTexture);
}

gui::GridEndNode::~GridEndNode()
{

}

int gui::GridEndNode::GetIndex() const
{
	return m_EndNodeIndex;
}

void gui::GridEndNode::SetIndex(const int& Index)
{
	m_EndNodeIndex = Index;
}

const sf::Vector2f& gui::GridEndNode::GetPosition() const
{
	return m_DestinationPoint.getPosition();
}

void gui::GridEndNode::SetPosition(const float& x, const float& y)
{
	m_DestinationPoint.setPosition(sf::Vector2f(x, y));
}

bool gui::GridEndNode::Contains(const sf::Vector2f& Something) const
{
	return m_DestinationPoint.getGlobalBounds().contains(Something);
}

void gui::GridEndNode::SetNodeFlag(const gui::GridStartNode& StartNode, std::vector<Grid*>& Grid,
	const sf ::Vector2f& MousePos, const int& Index, const int& ColumnsNumber, const int& Side)
{
	if (m_NodeFlag)
	{
		m_NodeFlag = false;

		if (!Grid[Index]->isBorder() && !StartNode.Contains(MousePos))
		{
			Grid[Index]->ChangeToIdleState();
			Grid[Index]->UpdateGridColor();
			Grid[Index]->SetDistance(0);
			m_EndNodeIndex = Index;
			std::cout << "m_EndNodeIndex=" << m_EndNodeIndex << std::endl;
			std::cout << "Drop " << Grid[Index]->GetDistance() << std::endl;
		}
		else if (Grid[Index]->isBorder() || StartNode.Contains(MousePos))
		{
			std::cout << "Border/Node " << Grid[Index]->GetDistance() << std::endl;
			int ColumnIndex = static_cast<int>(m_DestinationPoint.getPosition().x / Side);
			int RowIndex = static_cast<int>(m_DestinationPoint.getPosition().y / Side) - 4;
			int LocalIndex = RowIndex * ColumnsNumber + ColumnIndex;
			Grid[LocalIndex]->SetDistance(0);
			m_EndNodeIndex = LocalIndex;
			std::cout << "Drop next to border/node " << Grid[LocalIndex]->GetDistance() << std::endl;
			std::cout << "LocalIndex: " << LocalIndex << std::endl;
		}
	}
}

bool gui::GridEndNode::GetNodeFlag() const
{
	return m_NodeFlag;
}

void gui::GridEndNode::Update(const sf::Vector2f& MousePos, const std::vector<Grid*>& Grid, 
	const gui::GridStartNode& StartNode, const int& Index)
{

	//Pick up node
	int StartNodePositionX = StartNode.GetPosition().x;
	int StartNodePositionY = StartNode.GetPosition().y;

	if (!m_NodeFlag && m_DestinationPoint.getGlobalBounds().contains(MousePos))
	{
		Grid[Index]->SetDistance(0);
		std::cout << "Pickup " << Grid[Index]->GetDistance() << std::endl;
		m_NodeFlag = true;
	}

	if (m_NodeFlag && !Grid[Index]->isBorder() && ((MousePos.x < StartNodePositionX - 1 ||
		MousePos.x > StartNodePositionX + 21) || (MousePos.y < StartNodePositionY - 1 ||
			MousePos.y > StartNodePositionY + 21)))
	{
		m_DestinationPoint.setPosition(Grid[Index]->GetPosition());
		if (Grid[Index]->IsActive() && !m_ActiveToIdleFlag)
		{
			m_ActiveToIdleIndex = Index;
			Grid[m_ActiveToIdleIndex]->ChangeToIdleState();
			m_ActiveToIdleFlag = true;
		}
		if (m_ActiveToIdleIndex != Index && m_ActiveToIdleFlag)
		{
			Grid[m_ActiveToIdleIndex]->ChangeToActiveState();
			m_ActiveToIdleFlag = false;
		}
	}
		
}

void gui::GridEndNode::Render(sf::RenderTarget* Target)
{
	Target->draw(m_DestinationPoint);
}
