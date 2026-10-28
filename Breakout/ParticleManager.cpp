#include "ParticleManager.h"
#include <cstdlib>

Particle::Particle()
{
	shape.setSize(sf::Vector2f(5, 5));
	shape.setFillColor(sf::Color::Red);
}

ParticleManager::ParticleManager(sf::RenderWindow* window)
{
	_window = window;
}

void ParticleManager::emitBrickParticles(sf::Vector2f pos)
{
	for (int i = 0; i < 6; i++)
	{
		Particle _part;
		_part.timer = 1.f;
		_part.pos = pos;
		_part.shape.setPosition(pos);
		_part.vel.x = (rand() % 100) - 50;
		_part.vel.y = (rand() % 100) - 50;
		_particles.push_back(_part);
	}
}

void ParticleManager::update(float dt)
{
	/*for (auto& _part : _particles)
	{
		_part.timer -= dt;
		_part.pos += (_part.vel * dt);
		_part.shape.setPosition(_part.pos);
		if (_part.timer <= 0)
		{
			_particles.erase(_part);
		}
	}*/

	for (int i = 0; i < _particles.size(); i++)
	{
		auto& _part = _particles.at(i);
		_part.timer -= dt;
		_part.pos += (_part.vel * dt);
		_part.shape.setPosition(_part.pos);
		if (_part.timer <= 0)
		{
			_particles.erase(_particles.begin() + i);
		}
	}
}

void ParticleManager::render()
{
	for (auto& _part : _particles)
	{
		_window->draw(_part.shape);
	}
}