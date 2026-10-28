#include "PowerupTrackerBall.h"

PowerupTrackerBall::PowerupTrackerBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos) : PowerupBase(window, paddle, ball, x_pos)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupTrackerBall::~PowerupTrackerBall()
{

}

std::pair<POWERUPS, float> PowerupTrackerBall::applyEffect()
{
    _ball->setTrackerBall(5.0f);
    return { trackerBall, 5.0f };
}