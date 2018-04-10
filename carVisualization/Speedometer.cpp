#include "stdafx.h"
#include "Speedometer.h"

constexpr float SPEEDOMETER_RADIUS = 120.0f;
static const sf::Vector2f SPEEDOMETER_CENTER = { 540.0f, 400.0f };

namespace
{
	std::ostream& operator << (std::ostream& output, const sf::Vector2f& pos)
	{
		output << "(" << pos.x << ", " << pos.y << ")\n";
		return output;
	}

	template <typename T>
	std::string NumberToString(T number)
	{
		std::stringstream strm;
		strm << (number);
		return strm.str();
	}

	template<typename T>
	void DrawVectorData(sf::RenderWindow& window, const std::vector<T>& vect)
	{
		for (const auto& item : vect)
		{
			window.draw(item);
		}
	}
}

void CSpeedometer::Init(const sf::Font& font)
{
	InitDots();
	InitSpeedText(font);
	InitArrow();
}

void CSpeedometer::SetSpeed(int speed)
{
	m_Tospeed = speed;
}

void CSpeedometer::Update()
{
	(m_currentSpeed < m_Tospeed) ? ++m_currentSpeed : (m_currentSpeed > m_Tospeed) ? --m_currentSpeed : m_currentSpeed = m_currentSpeed;

	m_arrow.setRotation(60.0f + m_currentSpeed * 1.55f);
}

void CSpeedometer::Draw(sf::RenderWindow& window)
{
	DrawVectorData(window, m_dots);
	DrawVectorData(window, m_speeds);
	window.draw(m_arrow);
}

void CSpeedometer::InitDots()
{
	float from = 135.0f;
	float angle = from;
	float to = 405.0f;

	for (int i = 0; angle <= to; ++i, angle += 3.75f)
	{
		sf::Vector2f position(SPEEDOMETER_RADIUS * static_cast<float>(cos(angle * 0.0174533)) + SPEEDOMETER_CENTER.x, SPEEDOMETER_RADIUS * static_cast<float>(sin(angle * 0.0174533)) + SPEEDOMETER_CENTER.y);

		m_dots.push_back((i % 2 == 0) ? sf::CircleShape(2) : sf::CircleShape(1));
		m_dots[i].setOutlineColor(sf::Color::White);
		m_dots[i].setFillColor(sf::Color::White);
		m_dots[i].setPosition(position.x, position.y);

		std::cout << i;
	}
}

void CSpeedometer::InitSpeedText(const sf::Font& font)
{
	int from = 135;
	int angle = from;
	int to = 405;

	for (int i = 0; angle <= to; ++i, angle += 15)
	{
		sf::Vector2f position((SPEEDOMETER_RADIUS + 10.0f) * cos(angle * 0.0174533) + SPEEDOMETER_CENTER.x, (SPEEDOMETER_RADIUS + 10.0f) * sin(angle * 0.0174533) + SPEEDOMETER_CENTER.y);

		sf::Text speedText;
		m_speeds.push_back(speedText);
		m_speeds[i].setFont(font);
		m_speeds[i].setCharacterSize(15);
		m_speeds[i].setFillColor(sf::Color::Red);
		m_speeds[i].setStyle(sf::Text::Bold);
		m_speeds[i].setString(NumberToString(angle / 1.5 - 90));
		m_speeds[i].setPosition(position.x, position.y);
	}
}

void CSpeedometer::InitArrow()
{
	m_arrow.setPointCount(3);
	m_arrow.setPoint(0, sf::Vector2f(0.0f, 90.0f));
	m_arrow.setPoint(1, sf::Vector2f(30.0f, 90.0f));
	m_arrow.setPoint(0, sf::Vector2f(15.0f, 0.0f));
	m_arrow.setFillColor(sf::Color::Red);
	m_arrow.setOrigin(0.0f, 0.0f);
	m_arrow.setPosition(SPEEDOMETER_CENTER);
}
