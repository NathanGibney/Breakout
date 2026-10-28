#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _particleManager(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _score(0), _scoreMult(1.f), _difficultyMult(1.f), _level(1), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 100);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);

    _scoreText.setFont(_font);
    _scoreText.setPosition(350, 30);
    _scoreText.setCharacterSize(36);
    _scoreText.setFillColor(sf::Color::White);

    _levelText.setFont(_font);
    _levelText.setPosition(200, 30);
    _levelText.setCharacterSize(36);
    _levelText.setFillColor(sf::Color::White);
}

void GameManager::initialize()
{
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);
    _particleManager = new ParticleManager(_window);

    // Create bricks
    //_brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
    _brickManager->createBricks(4, 8, 90.0f, 30.0f, 5.0f);
    //_brickManager->createBricks(6, 12, 70.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    
    _scoreText.setString("Score: " + std::to_string(_score));
    _levelText.setString("Level: " + std::to_string(_level));

    if (_lives <= 0)
    {
        _masterText.setString("Game over. Press enter to restart.");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            restart();
        }
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed. Press enter to continue.");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            advanceLevel();
        }
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);
    _paddle->mouseInput(*_window);

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
    _particleManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    // TODO screen shake.
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _particleManager->render();
    _window->draw(_masterText);
    _window->draw(_scoreText);
    _window->draw(_levelText);
    _ui->render();
}

void GameManager::increaseScore(int score)
{
    _score += (score * _scoreMult);
}

void GameManager::resetScore()
{
    _score = 0;
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

void GameManager::advanceLevel() //on level completion
{
    _level++;
    _brickManager->deleteBricks();
    _levelComplete = false;
    _scoreMult += 0.2f;
    _difficultyMult += 0.1f;
    _ball->setVelocityMult(_difficultyMult);
    _ball->resetBall();
    _masterText.setString("");
    _paddle->resetPos(_window);
    _powerupManager->resetPowerups();

    switch (_level)
    {
    case 1: _brickManager->createBricks(4, 8, 90.0f, 30.0f, 5.0f); break; //level 1 easy layout
    case 2: _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f); break; //level 2 medium layout
    default: _brickManager->createBricks(6, 12, 70.0f, 30.0f, 5.0f); break; //level 3 onwards hard layout
    }
}

void GameManager::restart() //on failure
{
    _level = 1;
    _brickManager->deleteBricks();
    _score = 0; _lives = 3; _levelComplete = false; _scoreMult = 1.f; _difficultyMult = 1.f;
    _brickManager->createBricks(4, 8, 90.0f, 30.0f, 5.0f);
    _ball->setVelocityMult(_difficultyMult);
    _ball->resetBall();
    _masterText.setString("");
    _ui->resetLives();
    _paddle->resetPos(_window);
    _powerupManager->resetPowerups();
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
ParticleManager* GameManager::getParticleManager() const { return _particleManager; }
int GameManager::getLevel() const { return _level; }
