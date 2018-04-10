#include "stdafx.h"
#include "CarVisualController.h"

static const std::map<Gear, std::string> GEAR_TO_STRING = {
	{ Gear::Reverse, "reverse" },
	{ Gear::Neutral, "neutral" },
	{ Gear::First, "first" },
	{ Gear::Second, "second" },
	{ Gear::Third, "third" },
	{ Gear::Fourth, "fourth" },
	{ Gear::Fifth, "fifth" },
};

CCarVisualController::CCarVisualController(CCar& car)
	: m_car(car)
{
	Init();
}

void CCarVisualController::HandleEvent(sf::Event& event, sf::RenderWindow& window)
{
	HandleInfo();

	HandleCloseBtn(window, event, sf::Keyboard::Escape);
	HandlePowerBtn(window, event, sf::Keyboard::P);
	HandleGearBtn(window, event, m_reverseGearBtn, Gear::Reverse, sf::Keyboard::R);
	HandleGearBtn(window, event, m_neutralGearBtn, Gear::Neutral, sf::Keyboard::N);
	HandleGearBtn(window, event, m_firstGearBtn, Gear::First, sf::Keyboard::Num1);
	HandleGearBtn(window, event, m_secondGearBtn, Gear::Second, sf::Keyboard::Num2);
	HandleGearBtn(window, event, m_thridGearBtn, Gear::Third, sf::Keyboard::Num3);
	HandleGearBtn(window, event, m_fourhtGearBtn, Gear::Fourth, sf::Keyboard::Num4);
	HandleGearBtn(window, event, m_fifthGearBtn, Gear::Fifth, sf::Keyboard::Num5);

	HandleSetSpeed(event);
}

void CCarVisualController::Update()
{
	m_speedometer.SetSpeed(m_car.GetSpeed());
	m_speedometer.Update();
}

void CCarVisualController::Draw(sf::RenderWindow& window)
{
	window.draw(m_bgSprite);
	m_closeBtn.Draw(window);
	m_powerBtn.Draw(window);
	m_reverseGearBtn.Draw(window);
	m_neutralGearBtn.Draw(window);
	m_firstGearBtn.Draw(window);
	m_secondGearBtn.Draw(window);
	m_thridGearBtn.Draw(window);
	m_fourhtGearBtn.Draw(window);
	m_fifthGearBtn.Draw(window);

	m_speedometer.Draw(window);
	window.draw(m_info);
	window.draw(m_help);
}

void CCarVisualController::Init()
{
	InitSprite(m_bgSprite, m_bgTexture, "include/image/bg.jpg");
	InitBtns();
	InitInfoMsg("include/font/Roboto-Medium.ttf");
	m_speedometer.Init(m_font);
	InitHelpMsg();
}

void CCarVisualController::InitBtns()
{
	InitBtn(m_closeBtn, std::string("include/image/exitBtn.png"), sf::Vector2f(720, 20));
	InitBtn(m_powerBtn, std::string("include/image/powerBtn.png"), sf::Vector2f(200, 20));
	InitBtn(m_reverseGearBtn, std::string("include/image/reverseGearBtn.png"), sf::Vector2f(200, 60));
	InitBtn(m_neutralGearBtn, std::string("include/image/neutralGearBtn.png"), sf::Vector2f(200, 130));
	InitBtn(m_firstGearBtn, std::string("include/image/firstGearBtn.png"), sf::Vector2f(270, 60));
	InitBtn(m_secondGearBtn, std::string("include/image/secondGearBtn.png"), sf::Vector2f(270, 130));
	InitBtn(m_thridGearBtn, std::string("include/image/thirdGearBtn.png"), sf::Vector2f(330, 60));
	InitBtn(m_fourhtGearBtn, std::string("include/image/fourthGearBtn.png"), sf::Vector2f(330, 130));
	InitBtn(m_fifthGearBtn, std::string("include/image/fifthGearBtn.png"), sf::Vector2f(390, 60));
}

void CCarVisualController::InitBtn(CButton& btn, const std::string& texturePath, const sf::Vector2f& position)
{
	btn.SetTexture(texturePath);
	btn.SetPosition(position);
}

void CCarVisualController::InitInfoMsg(const std::string& fontPath)
{
	if (!m_font.loadFromFile(fontPath))
	{
		throw std::logic_error("failed load font file");
	}
	m_info.setFont(m_font);
	m_info.setCharacterSize(20);
	m_info.setFillColor(sf::Color::Red);
	m_info.setStyle(sf::Text::Bold);
	m_info.setPosition({ 20.f, 300.f });
}

void CCarVisualController::InitHelpMsg()
{
	m_help.setFont(m_font);
	m_help.setCharacterSize(14);
	m_help.setFillColor(sf::Color::Red);
	m_help.setStyle(sf::Text::Bold);
	m_help.setPosition({ 20.f, 20.f });

	m_help.setString("(P/p - turn on/off)\nesc - exit\nW/w/Up - increase speed\nS/s/Down - reduce speed\nR/r - reverse gear\nN/n - neutral gear\n1 - first gear\n2 - second gear\n3 - third gear\n4 - fourth gear\n5 - fifth gear");
}

void CCarVisualController::InitSprite(sf::Sprite& sprite, sf::Texture& texture, const std::string& texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		throw std::logic_error("failed load file '" + texturePath + "'");
	}

	sprite.setTexture(texture);
	sprite.setPosition({ 0, 0 });
}

void CCarVisualController::HandleCloseBtn(sf::RenderWindow& window, const sf::Event& event, const sf::Keyboard::Key& key)
{
	m_closeBtn.SetColor(sf::Color::White);

	if (m_closeBtn.HoverButton(window, event))
	{
		m_closeBtn.SetColor(sf::Color::Blue);
	}
	if (m_closeBtn.IsPressed(window, event) || (event.type == sf::Event::KeyPressed && event.key.code == key))
	{
		window.close();
	}
}

void CCarVisualController::HandlePowerBtn(sf::RenderWindow& window, const sf::Event& event, const sf::Keyboard::Key& key)
{
	m_powerBtn.SetColor(sf::Color::White);

	if (m_powerBtn.HoverButton(window, event))
	{
		m_powerBtn.SetColor(sf::Color::Blue);
	}

	if (m_powerBtn.IsPressed(window, event) || (event.type == sf::Event::KeyPressed && event.key.code == key))
	{
		std::cout << "car engine ";

		if (m_car.IsTurnedOnEngine())
		{
			std::cout << ((m_car.TurnOffEngine()) ? "is " : "cann't be ") << " turned off";
		}
		else
		{
			std::cout << ((m_car.TurnOnEngine()) ? "is turned on" : "cann't be turned on");
		}

		std::cout << "\n";
	}
}

void CCarVisualController::HandleGearBtn(sf::RenderWindow& window, const sf::Event& event, CButton& btn, Gear gear, const sf::Keyboard::Key& key)
{
	btn.SetColor(sf::Color::White);

	if (btn.HoverButton(window, event))
	{
		btn.SetColor(sf::Color::Blue);
	}
	if (btn.IsPressed(window, event) || (event.type == sf::Event::KeyPressed && event.key.code == key))
	{
		std::cout << "set" << GEAR_TO_STRING.at(gear) << " gear " << ((m_car.SetGear(static_cast<int>(gear))) ? "success" : "failed") << "\n";

		std::cout << CarInfo();
	}
}

void CCarVisualController::HandleInfo()
{
	m_info.setString(CarInfo());
}

void CCarVisualController::HandleSetSpeed(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
	{
		int speed = m_car.GetSpeed();
		++speed;
		std::cout << "set speed: " << (m_car.SetSpeed(speed) ? "succes" : "failed") << "\n";

		std::cout << "the escape key was pressed" << std::endl;
		std::cout << "control:" << event.key.control << std::endl;
		std::cout << "alt:" << event.key.alt << std::endl;
		std::cout << "shift:" << event.key.shift << std::endl;
		std::cout << "system:" << event.key.system << std::endl;
	}

	if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
	{
		int speed = m_car.GetSpeed();
		--speed;
		std::cout << "set speed: " << (m_car.SetSpeed(speed) ? "succes" : "failed") << "\n";
	}
}

std::string CCarVisualController::CarInfo() const
{
	std::string directionMovementStr = m_car.GetDirectionMovement();
	Gear gear = m_car.GetGear();
	std::string gearStr = GEAR_TO_STRING.at(gear);
	int speed = m_car.GetSpeed();

	std::stringstream strm;

	strm << "Car info: \n"
		 << " - the condition of the car engine: " << ((m_car.IsTurnedOnEngine()) ? "on" : "off") << "\n"
		 << " - speed: " << speed << "\n"
		 << " - direction: " << directionMovementStr << "\n"
		 << " - gear: " << gearStr << "\n"
		 << "   ================\n\n";

	return strm.str();
}
