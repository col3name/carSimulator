#include "stdafx.h"
#include "Simulator.h"

constexpr std::chrono::milliseconds FRAME_PERIOD(16);

void Simulator::MainLoop(sf::RenderWindow& window)
{
	CCar car;
	CCarVisualController carCntrl(car);
	CChronometer chronometer;

	while (window.isOpen())
	{
		chronometer.GrabDeltaTime();

		sf::Event event;
		PollEvent(window, event, carCntrl);
		Update(carCntrl);
		Draw(window, carCntrl);

		chronometer.WaitNextFrameTime(FRAME_PERIOD);
	}
}

void Simulator::Update(CCarVisualController& carCntrl)
{
	carCntrl.Update();
}

void Simulator::PollEvent(sf::RenderWindow& window, sf::Event& event, CCarVisualController& carCntrl)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		carCntrl.HandleEvent(event, window);
	}
}

void Simulator::Draw(sf::RenderWindow& window, CCarVisualController& carCntrl)
{
	window.clear();
	carCntrl.Draw(window);
	window.display();
}
