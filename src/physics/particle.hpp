#pragma once

#include "utils.hpp"

class Particle {
public:
	static constexpr size_t radius = 5;

	Particle(const sf::Vector2f pos, const sf::Color color);

	void draw(sf::RenderWindow& renderer) const;

	void setPos(const sf::Vector2f newPos);
	void incrementPos(const sf::Vector2f val);
	sf::Vector2f getPos() const;
	sf::Vector2f getOldPos() const;

	const sf::CircleShape& getDrawable() const;

	void accellerate(const sf::Vector2f acc);
	void updatePos(const float dt);
private:
	sf::Vector2f m_acceleration; 
	sf::Vector2f m_currPos;
	sf::Vector2f m_oldPos;
	sf::CircleShape m_drawable;
};