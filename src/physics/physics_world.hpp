#pragma once

#include "particle.hpp"
#include "world_shapes.hpp"

class PhysicsWorld {
public:
	PhysicsWorld(const size_t particlesNum, const size_t substeps = 8);

	void addParticle(const sf::Color color, const sf::Vector2f pos);
	void removeParticle(const size_t index);

	void applyGravity();
	void updatePositions(const float dt);
	void applyConstraint();
	void separateParticles(Particle& p1, Particle& p2) const;
	void handleCollisions();
	void update(const float dt);

	const ws::WorldShape* getShape() const;
	void setShape(const ws::WorldShape* const worldShape);

	const std::vector<Particle>& getParticles() const;

private:
	const sf::Vector2f m_gravity = { 0.0f, 100.0f};
	const size_t m_substeps;
	std::vector<Particle> m_particles;
	const ws::WorldShape* m_shape = nullptr;
};