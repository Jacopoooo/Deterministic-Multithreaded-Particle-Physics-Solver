#include "world_shapes.hpp"

ws::WorldRect::WorldRect(const sf::Vector2f origin, const sf::Vector2f size) :
	m_origin(origin), m_size(size), m_startingSpawnPos(m_origin.x + m_margin, m_origin.y + m_margin) {

		m_drawable = sf::VertexArray(sf::LineStrip, 5);

		m_occupiedSpaceByOneParticle = m_particlesRadius * 2 + m_spaceBetweenParticles;

		initDrawable();
}

sf::Vector2f ws::WorldRect::applyConstraint(sf::Vector2f point) const  
{
	if (!(point.x - m_particlesRadius >= m_origin.x && point.x + m_particlesRadius<= m_drawable[2].position.x
		&& point.y - m_particlesRadius >= m_origin.y && point.y + m_particlesRadius<= m_drawable[2].position.y)) {
		constrainToNearestPoint(point);
	}

	return point;
}

sf::Vector2f ws::WorldRect::getParticleSpawnPos(const size_t particleCounter)
{
	return m_startingSpawnPos + sf::Vector2f(0, m_occupiedSpaceByOneParticle * particleCounter);
}

const sf::Drawable& ws::WorldRect::getDrawable() const
{
	return m_drawable;
}

void ws::WorldRect::constrainToNearestPoint(sf::Vector2f& point) const
{
	if (point.x - m_particlesRadius< m_origin.x) {
		point.x = m_origin.x + m_particlesRadius;
	}
	else if (point.x + m_particlesRadius> m_drawable[2].position.x) {
		point.x = m_drawable[2].position.x - m_particlesRadius;
	}

	if (point.y - m_particlesRadius< m_origin.y) {
		point.y = m_origin.y + m_particlesRadius;
	}
	else if (point.y + m_particlesRadius> m_drawable[2].position.y) {
		point.y = m_drawable[2].position.y - m_particlesRadius;
		/*
			std::cout << "Bottom collision - Original Y: " << originalPoint.y
				<< " Radius: " << radius
				<< " Boundary: " << m_drawable[2].position.y
				<< " New Y: " << point.y << std::endl;

			std::cout << "Right collision - Original X: " << originalPoint.x
				<< " Radius: " << radius
				<< " Boundary: " << m_drawable[2].position.x
				<< " New X: " << point.x << std::endl;
		*/

	}
}

void ws::WorldRect::initDrawable()
{
	for (size_t i = 0; i < 5; ++i)
		m_drawable[i].color = sf::Color::White;

	m_drawable[0].position = m_origin;
	m_drawable[1].position = { m_origin.x + m_size.x, m_origin.y };
	m_drawable[2].position = m_origin + m_size;
	m_drawable[3].position = { m_origin.x, m_origin.y + m_size.y };
	m_drawable[4].position = m_drawable[0].position; // chiude il rettangolo
}
