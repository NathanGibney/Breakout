#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _velocityMult(1.f), _isFireBall(false), _isAlive(true), _direction({1,1})
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    // check for powerup, tick down or correct
    if (_timeWithPowerupEffect > 0.f)
    {
        _timeWithPowerupEffect -= dt;
    }
    else
    {
        if (_velocity != VELOCITY * _velocityMult)
            _velocity = VELOCITY * _velocityMult;   // reset speed.
        else
        {
            setFireBall(0);    // disable fireball
            setTrackerBall(0);
            _sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
        }        
    }

    // Fireball effect
    if (_isFireBall)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        _sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }
    else if (_isTrackerBall)
    {
        _sprite.setFillColor(sf::Color::Green);
    }

    if (_isTrackerBall)
    {
        sf::Vector2f target = { 0, 0 };
        if (_direction.y > 0)
        {
            target = _gameManager->getPaddle()->getBounds().getPosition();
        }

        if (target != sf::Vector2f(0, 0))
        {
            sf::Vector2 targetVelocity = (target - _sprite.getPosition());
            //float _temp = ((targetVelocity.x * targetVelocity.x) + (targetVelocity.y * targetVelocity.y));
            //_temp = sqrt(_temp);
            //targetVelocity /= _temp; //normalize target



            targetVelocity.x /= targetVelocity.y;

            _direction.x = targetVelocity.x;
        }
    }

    // Update position with a subtle floating-point error
    _sprite.move(_direction * _velocity * dt);

    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2u windowDimensions = _window->getSize();

    // bounce on walls
    if ((position.x >= windowDimensions.x - 2 * RADIUS && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
    }

    // lose life bounce
    if (position.y > windowDimensions.y)
    {
        _consecutiveHits = 0;

        _sprite.setPosition(0, 300);
        _direction = { 1, 1 };
        _gameManager->loseLife();
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        _consecutiveHits = 0;

        _direction.y *= -1; // Bounce vertically

        float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
        _direction.x = paddlePositionProportion * 2.0f - 1.0f;

        // Adjust position to avoid getting stuck inside the paddle
        _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * RADIUS);
    }

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
    if (collisionResponse != 0)
    {
        _consecutiveHits++; _gameManager->increaseScore(_consecutiveHits * 10);
    }
    if (_isFireBall) return; // no collisisons when in fireBall mode.
    if (collisionResponse == 1)
    {
        _direction.x *= -1; // Bounce horizontally
    }
    else if (collisionResponse == 2)
    {
        _direction.y *= -1; // Bounce vertically
    }
}

void Ball::render()
{
    _window->draw(_sprite);
}

void Ball::resetBall()
{
    _sprite.setPosition(0, 300);
    _velocity = 400.f;
    _direction = { 1, 1 };
    _isAlive = true;
    _consecutiveHits = 0;
}

void Ball::setVelocity(float coeff, float duration)
{
    _velocity = coeff * VELOCITY * _velocityMult;
    _timeWithPowerupEffect = duration;
}

void Ball::setFireBall(float duration)
{
    if (duration) 
    {
        _isFireBall = true;
        _timeWithPowerupEffect = duration;        
        return;
    }
    _isFireBall = false;
    _timeWithPowerupEffect = 0.f;    
}

void Ball::setTrackerBall(float duration)
{
    if (duration)
    {
        _isTrackerBall = true;
        _timeWithPowerupEffect = duration;
        return;
    }
    _isTrackerBall = false;
    _timeWithPowerupEffect = 0.f;
}

void Ball::setVelocityMult(float mult)
{
    _velocityMult = mult;
}
