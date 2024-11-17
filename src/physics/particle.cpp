#include "particle.hpp"

Particle::Particle(const sf::Vector2f pos, const sf::Color color) : m_currPos(pos), m_oldPos(m_currPos - sf::Vector2f(2.0f, 2.0f))
{
	m_drawable.setRadius(radius);
	m_drawable.setOrigin(sf::Vector2f(radius, radius));
	m_drawable.setPosition(pos);
	m_drawable.setFillColor(color);
	m_drawable.setPointCount(10); // TODO: mettere point count statico
}

void Particle::draw(sf::RenderWindow& renderer) const
{
	renderer.draw(m_drawable);
}

void Particle::setPos(const sf::Vector2f newPos)
{
	m_currPos = newPos;
}

void Particle::incrementPos(const sf::Vector2f value)
{
	m_currPos += value;
}

sf::Vector2f Particle::getPos() const
{
	return m_currPos;
}

sf::Vector2f Particle::getOldPos() const {

	return m_oldPos;
}

const sf::CircleShape& Particle::getDrawable() const
{
	return m_drawable;
}

void Particle::accellerate(const sf::Vector2f acc)
{
	m_acceleration = acc;
}

void Particle::updatePos(const float dt)
{
	const sf::Vector2f dx = m_currPos - m_oldPos;
	LOG("DX:")
	LOG(dx.x)
	LOG(dx.y)
	m_oldPos = m_currPos;

	m_currPos = m_currPos + dx + m_acceleration * dt * dt; // Verlet Integration

	m_drawable.setPosition(m_currPos);

	m_acceleration = {};
}


