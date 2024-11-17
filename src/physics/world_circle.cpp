#include "world_shapes.hpp"

ws::WorldCircle::WorldCircle(const sf::Vector2f origin, const float radius) :
	m_origin(origin), m_radius(radius)
{
	initDrawable();
	m_center = m_origin + sf::Vector2f(m_radius, m_radius);

	constexpr float gravity = 50.0f;

	m_omega = sqrt(gravity / m_distanceFromSpawn);
}

sf::Vector2f ws::WorldCircle::applyConstraint(sf::Vector2f point) const
{
	
	const sf::Vector2f vec = point - m_center;
	const float dist = magnitude<float>(vec);

	//LOG("MAGNITUDE OF VECTOR DISTANCE")
		//LOG(dist);
	if (dist > m_radius - m_particlesRadius) {
		LOG("-----------------------------------------------")
		LOG("POINT BEFORE")
		LOG(point.x)
		LOG(point.y)
		const sf::Vector2f unitVector = vec / dist;
		point = m_center + unitVector * (dist - m_particlesRadius);
		LOG("POINT AFTER")
		LOG(point.x)
		LOG(point.y)
		LOG("-----------------------------------------------")

	}
	
	return point;
		
}

sf::Vector2f ws::WorldCircle::getParticleSpawnPos(const size_t particleCounter)
{
	++m_particlesCounter;
	const float theta = m_maxTheta + std::cos(m_omega * particleCounter);

	// + getRandomFloat(-m_noiseValue, m_noiseValue)
	const float spawnXCoord = m_center.x + m_distanceFromSpawn * std::sin(theta);
	const float spawnYCoord= m_center.y - m_distanceFromSpawn * std::cos(theta);
	LOG("X COORD")
	LOG(spawnXCoord)
	LOG("Y COORD")
	LOG(spawnYCoord)
	return sf::Vector2f(spawnXCoord, spawnYCoord);
}

const sf::Drawable& ws::WorldCircle::getDrawable() const
{
	return m_drawable;
}

void ws::WorldCircle::initDrawable()
{
	m_drawable.setRadius(m_radius);
	m_drawable.setPosition(m_origin);
	LOG("STANDARD POSITION")
		LOG(m_drawable.getPosition().x);
		LOG(m_drawable.getPosition().y);
	m_drawable.setOutlineColor(sf::Color::White);
	m_drawable.setFillColor(sf::Color::Transparent);
	m_drawable.setOutlineThickness(1.0f);
}
