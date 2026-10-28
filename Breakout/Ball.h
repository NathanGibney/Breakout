#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void resetBall();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
    void setTrackerBall(float duration);
    void setVelocityMult(float mult);

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    bool _isTrackerBall;
    float _timeWithPowerupEffect;
    float _velocityMult;
    int _consecutiveHits; //number of bricks hit without returning to the paddle or dropping out of bounds

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

