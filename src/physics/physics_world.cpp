#include "physics_world.hpp"

PhysicsWorld::PhysicsWorld(const size_t particlesNum, const size_t substeps) : m_substeps(substeps)
{
	m_particles.reserve(particlesNum);
}

void PhysicsWorld::addParticle(const sf::Color color, const sf::Vector2f pos)
{
	m_particles.emplace_back(pos, color);
}

void PhysicsWorld::removeParticle(const size_t index)
{
	if (index < m_particles.size())
		m_particles.erase(m_particles.begin() + index);
}

void PhysicsWorld::applyGravity()
{
	for (auto& p : m_particles) {
		p.accellerate(m_gravity);
	}
}

void PhysicsWorld::updatePositions(const float dt)
{
	for (auto& p : m_particles) {
		p.updatePos(dt);
	}
}

void PhysicsWorld::applyConstraint()
{
	for (auto& p : m_particles) {
		const sf::Vector2f currPos = p.getPos();
		const sf::Vector2f newPos = m_shape->applyConstraint(currPos);
		if (newPos != currPos) {
			/*
			LOG("NEW POS COORDS:");
			LOG(newPos.x);
			LOG(newPos.y);
			*/
			p.setPos(newPos);
		}
	}
}

/*
* 
* DELETED ELASTIC COLLISION
* 
void PhysicsWorld::setVelocityAfterCollision(Particle& p1, Particle& p2, const float dt) const
{
	const sf::Vector2f normal = p1.getPos() - p2.getPos();
	const sf::Vector2f unitNormal = normal / magnitude<float>(normal);

	const sf::Vector2f unitTangent = { -unitNormal.y, unitNormal.x };

	const float startV1NProj = dotProduct<float>(unitNormal, p1.getVelocity(dt));
	const float startV1TProj = dotProduct<float>(unitTangent, p1.getVelocity(dt));

	const float startV2NProj = dotProduct<float>(unitNormal, p2.getVelocity(dt));
	const float startV2TProj = dotProduct<float>(unitTangent, p2.getVelocity(dt));

	const float finalV1TProj = startV1TProj;
	const float finalV2TProj = startV2TProj; // tangent projections remains the same because there aren't any forces in the tangent directions

	const float finalV1NProj = startV2NProj;
	const float finalV2NProj = startV1NProj; // In elastic collisions the initial velocity is equal to the initial velocity of the other particle if masses are equal

	const sf::Vector2f finalV1N = finalV1NProj * unitNormal;
	const sf::Vector2f finalV1T = finalV1TProj * unitTangent;

	const sf::Vector2f finalV2N = finalV2NProj * unitNormal;
	const sf::Vector2f finalV2T = finalV2NProj * unitTangent;

	p1.setPosWithVelocity(finalV1N + finalV1T, dt);
	p2.setPosWithVelocity(finalV2N + finalV2T, dt);
}
*/

void PhysicsWorld::separateParticles(Particle& p1, Particle& p2) const
{
	const sf::Vector2f collisionAxis = p1.getPos() - p2.getPos();
	const float dist = magnitude<float>(collisionAxis);
	sf::Vector2f unitVector = {};
	if (dist != 0.0f) unitVector = collisionAxis / dist;

	const float delta = (p1.radius + p2.radius) - dist;

	p1.incrementPos(0.5f * delta * unitVector);
	p2.incrementPos(-0.5f * delta * unitVector);
}


void PhysicsWorld::handleCollisions()
{
	constexpr float eps = 0.0001f;
	for (size_t i = 0; i < m_particles.size() - 1;  ++i) {
		Particle& p1 = m_particles[i];
		for (size_t j = i + 1; j < m_particles.size(); ++j) {
			Particle& p2 = m_particles[j];
			const float centersDist = distance<float>(p1.getPos(), p2.getPos());
			if (centersDist - eps < p1.radius + p2.radius) {
				separateParticles(p1, p2);

			}
		}
	}
}

void PhysicsWorld::update(const float dt)
{
	const float sub_dt = static_cast<float>(dt / m_substeps);
	for (size_t i = m_substeps; --i;) {
		applyGravity();
		applyConstraint();
		updatePositions(sub_dt);
		handleCollisions();
	}
}

const ws::WorldShape* PhysicsWorld::getShape() const
{
	return m_shape;
}

void PhysicsWorld::setShape(const ws::WorldShape* const worldShape)
{
	m_shape = worldShape;
}

const std::vector<Particle>& PhysicsWorld::getParticles() const
{
	return m_particles;
}
