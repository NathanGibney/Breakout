#include "SFML/Graphics.hpp"
#pragma once

class Particle
{
public:
	Particle();

	sf::RectangleShape shape;
	float timer;
	sf::Vector2f pos;
	sf::Vector2f vel;
};

class ParticleManager //for brick breaking
{
private:
	std::vector<Particle> _particles;
	sf::RenderWindow* _window;

public:
	ParticleManager(sf::RenderWindow* window);
	void emitBrickParticles(sf::Vector2f);
	void update(float dt);
	void render();
};

