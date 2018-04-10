#pragma once

class CButton
{
public:
	CButton();
	CButton(const std::string& texturePath, const sf::Vector2f& pos);
	void Draw(sf::RenderWindow& window);
	void SetColor(const sf::Color& color);
	bool IsPressed(const sf::RenderWindow& window, const sf::Event& event);
	bool HoverButton(const sf::RenderWindow& window, const sf::Event& event);
	void SetTexture(const std::string& texturePath);
	void SetPosition(const sf::Vector2f& pos);

private:
	bool MouseCursorOnButton(const sf::RenderWindow& window);

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};
