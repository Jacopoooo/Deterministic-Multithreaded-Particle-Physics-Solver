#pragma once 

#include "../physics/world_shapes.hpp"
#include "../physics/utils.hpp"
#include <array>


class Simulation;

struct ButtonStyle {

	sf::Color buttonColor;
	sf::Color outlineColor;

	sf::Color onHoverButtonColor;
	sf::Color onClickButtonColor;

	sf::Color textColor;
	sf::Color onHoverTextColor;
	sf::Color onClickTextColor;

	size_t characterSize;

	float outlineThickness;

	const sf::Font* font = nullptr;

	ws::SHAPE_TYPE type;

	ButtonStyle() = default;
	ButtonStyle(const ButtonStyle&) = default;
	ButtonStyle& operator=(const ButtonStyle&) = default;
};

struct RectangleButtonStyle : ButtonStyle {
	const std::string buttonText = "Rectangle";

	RectangleButtonStyle() = default;

	RectangleButtonStyle(const ButtonStyle& style) : ButtonStyle(style) {
		type = ws::SHAPE_TYPE::RECTANGLE;
	}

	RectangleButtonStyle& operator=(const RectangleButtonStyle& other) {
		if (this != &other) {
			ButtonStyle::operator=(other);
		}
		return *this;
	}
};


struct CircleButtonStyle : ButtonStyle {
	const std::string buttonText = "Circle";

	CircleButtonStyle() = default;

	CircleButtonStyle(const ButtonStyle& style) : ButtonStyle(style) {
		type = ws::SHAPE_TYPE::CIRCLE;
	}

	CircleButtonStyle& operator=(const CircleButtonStyle& other) {
		if (this != &other) {
			ButtonStyle::operator=(other);
		}
		return *this;
	}
};

struct ParabolaButtonStyle : ButtonStyle {
	const std::string buttonText = "Parabola";

	ParabolaButtonStyle() = default;

	ParabolaButtonStyle(const ButtonStyle& style) : ButtonStyle(style) {
		type = ws::SHAPE_TYPE::PARABOLA;
	}

	ParabolaButtonStyle& operator=(const ParabolaButtonStyle& other) {
		if (this != &other) {
			ButtonStyle::operator=(other);
		}
		return *this;
	}
};

class Button {
public:
	Button(const sf::Vector2f pos, const sf::Vector2f size, const ButtonStyle* style); // TODO: cambiare da pointer a reference 
	Button();

	bool listen(const int eventType, const sf::Vector2i mousePos);

	const sf::Vector2f getPos() const;

	const sf::VertexArray& getDrawable() const;
	const sf::Text& getTextDrawable() const;

	ws::SHAPE_TYPE getShapeType() const;

	void operator=(const Button& other);

public:
	static bool s_render;

private:
	sf::VertexArray m_drawable;
	sf::Text m_textDrawable;

	const ButtonStyle* m_style = nullptr;

	sf::Vector2f m_pos;
	sf::Vector2f m_size;
	sf::Color m_currColor;

	bool m_isHovering = false;
	bool m_isClicked = false;

	bool isHovering(const sf::Vector2i mousePos) const;
	void setToDefault();
	void setHoverState();

	void initText();
	void initDrawable();

	void setColor(const sf::Color newColor);

	friend class Renderer;

};