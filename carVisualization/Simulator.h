
#pragma once

#include "CarVisualController.h"
#include "Chronometer.h"

namespace Simulator
{
void MainLoop(sf::RenderWindow& window);

void PollEvent(sf::RenderWindow& window, sf::Event& event, CCarVisualController& carCntrll);
void Update(CCarVisualController& carCntrl);
void Draw(sf::RenderWindow& window, CCarVisualController& carCntrl);

} // namespace App
