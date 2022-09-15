#include "Button.h"

Button::Button(float x, float y, float width, float height, std::string Text, 
	sf::Color IdleColor, sf::Color HoverColor, sf::Color ActiveColor)
{
	m_ButtonState = BUTTON_STATES::BTN_IDLE;

	m_Button.setPosition(sf::Vector2f(x, y));
	m_Button.setSize(sf::Vector2f(width, height));

	m_Font.loadFromFile("Fonts/font.ttf");
	m_Text.setFont(m_Font);
	m_Text.setString(Text);
	m_Text.setFillColor(sf::Color::Red);
	m_Text.setCharacterSize(20);
	m_Text.setPosition(
		m_Button.getPosition().x + (width / 2.f) - m_Text.getGlobalBounds().width / 2.f,
		m_Button.getPosition().y + (height / 2.f) - m_Text.getGlobalBounds().height / 1.3f /*2.f*/
		);

	m_IdleColor = IdleColor;
	m_HoverColor = HoverColor;
	m_ActiveColor = ActiveColor;

	m_Button.setFillColor(m_IdleColor);
}

Button::~Button()
{

}

bool Button::IsPressed() const
{
	if (m_ButtonState == BUTTON_STATES::BTN_ACTIVE)
		return true;

	return false;
}

void Button::Update(const sf::Vector2f& MousePos)
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

void Button::Render(sf::RenderTarget* Target)
{
	Target->draw(m_Button);
	Target->draw(m_Text);
}
