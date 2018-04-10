#pragma once

#include "Button.h"
#include "Car.h"
#include "Speedometer.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <tuple>

class CCarVisualController
{
public:
	CCarVisualController(CCar& car);
	void HandleEvent(sf::Event& event, sf::RenderWindow& window);
	void Update();
	void Draw(sf::RenderWindow& window);

private:
	using Btns = std::vector<std::tuple<CButton&, std::string, sf::Vector2f>>;

	void Init();
	void InitBtns();
	void InitBtn(CButton& btn, const std::string& texturePath, const sf::Vector2f& position);
	void InitSprite(sf::Sprite& sprite, sf::Texture& texture, const std::string& texturePath);
	void InitInfoMsg(const std::string& fontPath);
	void InitHelpMsg();

	void HandleCloseBtn(sf::RenderWindow& window, const sf::Event& event, const sf::Keyboard::Key& key);
	void HandlePowerBtn(sf::RenderWindow& window, const sf::Event& event, const sf::Keyboard::Key& key);
	void HandleGearBtn(sf::RenderWindow& window, const sf::Event& event, CButton& btn, Gear gear, const sf::Keyboard::Key& key);
	void HandleInfo();
	void HandleSetSpeed(const sf::Event& event);

	std::string CarInfo() const;

private:
	sf::Texture m_bgTexture;
	sf::Sprite m_bgSprite;

	CButton m_closeBtn;
	CButton m_powerBtn;
	CButton m_reverseGearBtn;
	CButton m_neutralGearBtn;
	CButton m_firstGearBtn;
	CButton m_secondGearBtn;
	CButton m_thridGearBtn;
	CButton m_fourhtGearBtn;
	CButton m_fifthGearBtn;

	sf::Font m_font;
	sf::Text m_info;
	sf::Text m_help;

	CSpeedometer m_speedometer;

	CCar& m_car;
};
