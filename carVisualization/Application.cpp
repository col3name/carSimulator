#include "stdafx.h"
#include "Application.h"
#include "Simulator.h"

static const sf::Vector2f RESOLUTION = { 776.0f, 582 };
static const std::string WINDOW_TITLE = "Car simullator";

bool App::Execute()
{
	try
	{
		sf::RenderWindow window(sf::VideoMode(RESOLUTION.x, RESOLUTION.y), WINDOW_TITLE);

		Simulator::MainLoop(window);
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what() << std::endl;

		return false;
	}

	return true;
}
