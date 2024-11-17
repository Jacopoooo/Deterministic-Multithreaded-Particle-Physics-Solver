#pragma once 

#include "../physics/physics_world.hpp"
#include "../ui/button.hpp"
#include "context.hpp"

// const Button* = dato costante, possibile riassegnazione del pointer

class Renderer {
public:
	Renderer(const size_t particlesNum, const size_t screenWidth, const size_t screenHeight);

	void render(RENDER_CONTEXT context);
	void setPhysicsWorld(const PhysicsWorld* physicsWorld);
	void setTextDrawable(const sf::Text* textDrawable);
	void setButtonDrawable(const Button* buttonDrawable, size_t index);
	void setWorldShapeDrawable(const ws::WorldShape* const worldShape);

	bool pollEvent(sf::Event& e);
	bool windowIsOpen() const;
	void closeWindow();
	sf::Vector2i getMouseCoords() const;

private:
	sf::RenderWindow m_window;
	const size_t m_particlesNum;
	const size_t m_particlesVerticesCount = 15;
	const size_t m_numButtonsVertices = 4;
	sf::VertexBuffer m_buffer;
	std::vector<sf::Vertex> m_buttonsVertices;

	const sf::Text* m_textDrawable = nullptr;
	std::array<const Button*, 3> m_buttons;
	const PhysicsWorld* m_physicsWorld = nullptr;
	const sf::Drawable* m_worldShapeDrawable = nullptr;

	RENDER_CONTEXT m_currContext;

	void loadBufferWithButtons();
	void renderButtonsText();
	void setBuffer(sf::VertexBuffer::Usage usage, sf::PrimitiveType type);
	void loadBufferWithParticles();
};