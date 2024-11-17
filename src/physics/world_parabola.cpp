#include "world_shapes.hpp"

sf::Vector2f ws::WorldParabola::applyConstraint(sf::Vector2f point) const
{
    return sf::Vector2f();
}

sf::Vector2f ws::WorldParabola::getParticleSpawnPos(const size_t particleCounter)
{
    return sf::Vector2f();
}

const sf::Drawable& ws::WorldParabola::getDrawable() const
{
    return sf::VertexArray();
}

void ws::WorldParabola::initDrawable()
{
}
