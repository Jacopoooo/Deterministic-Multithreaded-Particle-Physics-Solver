#pragma once

#include "particle.hpp"

namespace ws {
	
	enum class SHAPE_TYPE {
		RECTANGLE,
		CIRCLE,
		PARABOLA
	};

	class WorldShape {
	public:
		virtual sf::Vector2f applyConstraint(sf::Vector2f point) const = 0;
		virtual sf::Vector2f getParticleSpawnPos(const size_t particleCounter) = 0;
		virtual const sf::Drawable& getDrawable() const = 0;
	protected:
		size_t m_particlesCounter = 0;
		const float m_particlesRadius = Particle::radius; // TODO: introdurre un colore
	private:
		virtual void initDrawable() = 0;
	};	

	class WorldRect : public WorldShape {
	public:
		WorldRect(const sf::Vector2f origin, const sf::Vector2f size);

		sf::Vector2f applyConstraint(sf::Vector2f point) const override;

		sf::Vector2f getParticleSpawnPos(const size_t particleCounter) override;

		const sf::Drawable& getDrawable() const override;

		WorldRect& operator=(const WorldRect&) = default;

	private:
		const float m_margin = 5.0f;
		const float m_spaceBetweenParticles = 0.01f;
		const float m_spawnAreaWidth = 300.0f;

		const sf::Vector2f m_size;
		const sf::Vector2f m_origin;

		const sf::Vector2f m_startingSpawnPos;
		float m_occupiedSpaceByOneParticle;

		sf::VertexArray m_drawable;
	private:
		void initDrawable() override;
		void constrainToNearestPoint(sf::Vector2f& point) const;
	};


	class WorldCircle : public WorldShape {
	public:
		WorldCircle(const sf::Vector2f origin, const float radius);
		sf::Vector2f applyConstraint(sf::Vector2f point) const override;
		sf::Vector2f getParticleSpawnPos(const size_t particleCounter) override;
		const sf::Drawable& getDrawable() const override;
	private:
		const sf::Vector2f m_origin;
		sf::Vector2f m_center;

		const float m_radius;
		const float m_distanceFromSpawn = 10.0f;
		const float m_maxTheta = 20.0f;
		const float m_noiseValue = 0.5f;

		float m_omega;

		sf::CircleShape m_drawable;
	private:
		void initDrawable() override;
	};


	class WorldParabola : public WorldShape {
		sf::Vector2f applyConstraint(sf::Vector2f point) const override;
		sf::Vector2f getParticleSpawnPos(const size_t particleCounter) override;
		const sf::Drawable& getDrawable() const override;
		void initDrawable() override;
	};
}
