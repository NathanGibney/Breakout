#pragma once
#include "PowerupBase.h"

class PowerupTrackerBall : public PowerupBase
{
public:
	PowerupTrackerBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos);
	~PowerupTrackerBall();

	std::pair<POWERUPS, float> applyEffect() override;
};

