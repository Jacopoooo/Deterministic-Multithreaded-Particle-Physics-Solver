#pragma once

#include <array>
#include "physics/physics_world.hpp"
#include "renderer/context.hpp"
#include "ui/button.hpp"
#include "renderer/renderer.hpp"

class Simulation {
public:
	Simulation(const size_t particlesNum, const size_t screenWidth, const size_t screenHeight, const float fps = 60.0f); 
	~Simulation();

	void run();
	const sf::Vector2u& getSize() const;
	
private:
	Renderer m_renderer;
	PhysicsWorld m_physicsWorld;
	RENDER_CONTEXT m_currContext;
	ButtonStyle m_baseButtonStyle;

	ws::WorldShape* m_worldShape = nullptr;

	std::array<Button, 3> m_buttons;
	std::array<ButtonStyle, 3> m_buttonStyles;

	sf::Text m_text; // più di uno
	sf::Font m_font;

	const size_t m_screenWidth, m_screenHeight;
	const size_t m_particlesNum;
	const float m_fps;

	const sf::Color m_particlesColor = sf::Color::Green; // temporaneo, poi creerò dei color utils che lo faranno random arcobaleno
	
	void initWSDependencies(const ws::SHAPE_TYPE worldShapeType);
	void initWSDependency(const ws::WorldShape* worldShape);
	void initSimulationText();
	void processEvents();
	bool loadFont(const std::string& path);
};