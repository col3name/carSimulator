#pragma once

class CSpeedometer
{
public:
	void Init(const sf::Font& font);
	void SetSpeed(int speed);
	void Update();
	void Draw(sf::RenderWindow& window);

private:
	void InitDots();
	void InitSpeedText(const sf::Font& font);
	void InitArrow();

private:
	using Dots = std::vector<sf::CircleShape>;
	using Speeds = std::vector<sf::Text>;
	using Arrow = sf::ConvexShape;

	Dots m_dots;
	Speeds m_speeds;
	Arrow m_arrow;

	int m_Tospeed = 180;
	int m_currentSpeed = 0;
};
