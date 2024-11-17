#include "renderer.hpp"

Renderer::Renderer(const size_t particlesNum, const size_t screenWidth, const size_t screenHeight) : m_particlesNum(particlesNum), m_buffer(sf::VertexBuffer::Usage::Stream),
m_window(sf::VideoMode(screenWidth, screenHeight), "Particle Collision Multithreaded Solver")
{
	m_currContext = RENDER_CONTEXT::BUTTONS_CONTEXT;
	m_buffer.create(m_buttons.size() * m_numButtonsVertices);
	setBuffer(sf::VertexBuffer::Usage::Stream, sf::Quads);
	m_buttonsVertices.reserve(m_buttons.size() * m_numButtonsVertices);

}

void Renderer::render(RENDER_CONTEXT context)
{
	m_window.clear(sf::Color::Black);

	if (m_currContext == RENDER_CONTEXT::BUTTONS_CONTEXT && context == RENDER_CONTEXT::SIMULATION_CONTEXT) {
		m_currContext = context;
		setBuffer(sf::VertexBuffer::Usage::Stream, sf::Triangles);
	}

	switch (static_cast<unsigned int>(m_currContext)) {

		case 0: {
			loadBufferWithButtons();
			renderButtonsText();
			break;
		}
		case 1: {
			loadBufferWithParticles();
			//m_window.draw(m_buffer);
			m_window.draw(*m_worldShapeDrawable);
			//m_window.draw(*m_textDrawable);
			break;
		}
	}

	//LOG((int)m_buffer.getVertexCount());
	m_window.display();
}

void Renderer::setPhysicsWorld(const PhysicsWorld* physicsWorld)
{
	m_physicsWorld = physicsWorld;
}

void Renderer::setTextDrawable(const sf::Text* textDrawable)
{
	m_textDrawable = textDrawable;
}

void Renderer::setButtonDrawable(const Button* buttonDrawable, size_t index)
{
	m_buttons[index] = buttonDrawable;
}

void Renderer::setWorldShapeDrawable(const ws::WorldShape* const worldShape)
{
	m_worldShapeDrawable = &worldShape->getDrawable();
}


void Renderer::setBuffer(sf::VertexBuffer::Usage usage, sf::PrimitiveType type) {
	m_buffer.setUsage(usage);
	m_buffer.setPrimitiveType(type);
}


void Renderer::loadBufferWithButtons() {
	m_buttonsVertices.clear();

	for (const auto& btn : (m_buttons)) {
		const sf::VertexArray& drawable = btn->getDrawable();
		for (size_t i = 0; i < m_numButtonsVertices; ++i) {
			m_buttonsVertices.emplace_back(drawable[i].position, drawable[i].color);
		}
	}
	m_buffer.update(m_buttonsVertices.data(), m_buttonsVertices.size(), 0);
	m_window.draw(m_buffer);
}

void Renderer::renderButtonsText() {
	for (const auto btn : (m_buttons)) {
		m_window.draw(btn->getTextDrawable());
	}

	//LOG("RENDERED TEXT BUTTON DRAWABLES")
}

void Renderer::loadBufferWithParticles() {
	
	const std::vector<Particle>& particles = m_physicsWorld->getParticles();
	/*
	const size_t particlesCount = particles.size();

	const size_t particlesPerCircle = m_particlesVerticesCount * 3; // ogni punto è rappresentato da un triangolo

	std::vector<sf::Vertex> vertices;
	vertices.reserve(particlesCount * particlesPerCircle);

	if (m_buffer.getVertexCount() != particlesCount * particlesPerCircle)
		m_buffer.create(particlesCount * particlesPerCircle);
	
	const sf::Vector2f radiusAdjuster = sf::Vector2f(Particle::radius, Particle::radius);

	for (const auto& p : particles) {
		const sf::CircleShape& drawable = p.getDrawable();
		const sf::Color drawableColor = drawable.getFillColor();

		for (size_t i = 0; i < particlesPerCircle; ++i) {

			vertices.emplace_back(drawable.getPosition(), drawableColor);

			vertices.emplace_back(drawable.getPoint(i) + drawable.getPosition() - radiusAdjuster, drawableColor);

			vertices.emplace_back(drawable.getPoint((i+1) % m_particlesVerticesCount) + drawable.getPosition() - radiusAdjuster, drawableColor);
		}
	}
	
	m_buffer.update(vertices.data(), vertices.size(), 0);
		*/
	
	for (const auto& p : particles) {
		m_window.draw(p.getDrawable());
	}
	
}


// ------------------ WINDOW UTILS ------------------


bool Renderer::pollEvent(sf::Event& e)
{
	return m_window.pollEvent(e);
}

bool Renderer::windowIsOpen() const
{
	return m_window.isOpen();
}

void Renderer::closeWindow()
{
	m_window.close();
}

sf::Vector2i Renderer::getMouseCoords() const
{
	return sf::Mouse::getPosition(m_window);
}

