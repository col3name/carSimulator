#include "stdafx.h"
#include "Button.h"

CButton::CButton() {}

CButton::CButton(const std::string& texturePath, const sf::Vector2f& pos)
{
	SetTexture(texturePath);
	SetPosition(pos);
}

void CButton::SetPosition(const sf::Vector2f& pos)
{
	m_sprite.setPosition(pos);
}

void CButton::SetTexture(const std::string& texturePath)
{
	if (!m_texture.loadFromFile(texturePath))
	{
		throw std::logic_error("Error load file: '" + texturePath + "'");
	}

	m_sprite.setTexture(m_texture);
}

void CButton::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void CButton::SetColor(const sf::Color& color)
{
	CButton::m_sprite.setColor(color);
}

bool CButton::IsPressed(const sf::RenderWindow& window, const sf::Event& event)
{
	return (event.type == sf::Event::MouseButtonPressed && MouseCursorOnButton(window));
}

bool CButton::HoverButton(const sf::RenderWindow& window, const sf::Event& event)
{
	return (event.type == sf::Event::MouseMoved && MouseCursorOnButton(window));
}

bool CButton::MouseCursorOnButton(const sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	return m_sprite.getGlobalBounds().contains(mousePosF);
}
