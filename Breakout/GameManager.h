#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"
#include "ParticleManager.h"


class GameManager {
public:
    GameManager(sf::RenderWindow* window);
    void initialize();
    void update(float dt);
    void loseLife();
    void render();
    void increaseScore(int _score);
    void resetScore();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);

    void advanceLevel();
    void restart();

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    ParticleManager* getParticleManager() const;
    sf::RenderWindow* getWindow() const;
    int getLevel() const;
    UI* getUI() const;


private:
    bool _pause;
    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    int _lives;
    bool _levelComplete;
    std::pair<POWERUPS, float> _powerupInEffect;
    int _score;
    float _scoreMult;
    float _difficultyMult;
    int _level;

    sf::Font _font;
    sf::Text _masterText;
    sf::Text _scoreText;
    sf::Text _levelText;

    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;
    ParticleManager* _particleManager;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn
};
