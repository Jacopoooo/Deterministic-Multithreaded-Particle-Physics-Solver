#include "button.hpp"

bool Button::s_render = true;

Button::Button(const sf::Vector2f pos, const sf::Vector2f size, const ButtonStyle* style) :
    m_pos(pos), m_size(size), m_style(style), m_drawable(sf::Quads, 4)
{
    initDrawable();
}

Button::Button() : m_size(), m_pos()
{
}


bool Button::isHovering(const sf::Vector2i mousePos) const
{
    const bool xConstraints = mousePos.x >= m_pos.x && mousePos.x <= m_pos.x + m_size.x;
    const bool yConstraints = mousePos.y >= m_pos.y && mousePos.y <= m_pos.y + m_size.y;

    return xConstraints && yConstraints;
}

ws::SHAPE_TYPE Button::getShapeType() const
{
    return m_style->type;
}   

bool Button::listen(const int eventType, const sf::Vector2i mousePos)
{
    switch (eventType) {
        case sf::Event::MouseMoved: {
            if (isHovering(mousePos)) {
                m_isHovering = true;     
                setHoverState();
            }
            else if (m_isHovering) {
                m_isHovering = false;
                setToDefault();
            }
            break;
        }
        case sf::Event::MouseButtonPressed: {
            if (m_isHovering) {
                m_isClicked = true; 
                m_isHovering = false;
            }
            break;
        }
        case sf::Event::MouseButtonReleased: {
            if (m_isClicked) {
                s_render = false;
                m_isHovering = false;
                setToDefault();
                return true;
            }
        }
    }

    return false;
}


void Button::setToDefault() {    
    setColor(m_style->buttonColor);
    m_textDrawable.setFillColor(m_style->textColor);    
}

void Button::setHoverState() {
    setColor(m_style->onHoverButtonColor);
    m_textDrawable.setFillColor(m_style->onHoverTextColor);
}

void Button::setColor(const sf::Color newColor) {

    if (m_currColor == newColor) {return;}

    m_currColor = newColor;

    for (size_t i = 0; i < 4; ++i) {
        m_drawable[i].color = m_currColor;
    }
}

const sf::VertexArray& Button::getDrawable() const
{
    return m_drawable;
}

const sf::Text& Button::getTextDrawable() const
{
    return m_textDrawable;
}

void Button::operator=(const Button& other)
{
    m_drawable = other.m_drawable;
    m_textDrawable = other.m_textDrawable;
    m_style = other.m_style;
    m_pos = other.m_pos;
    m_size = other.m_size;
    m_currColor = other.m_currColor;
}

const sf::Vector2f Button::getPos() const
{
    return m_pos;
}

void Button::initText()
{
    m_textDrawable.setFillColor(m_style->textColor);
    m_textDrawable.setFont(*m_style->font);
    m_textDrawable.setCharacterSize(m_style->characterSize);

    sf::FloatRect textBounds = m_textDrawable.getLocalBounds();
    m_textDrawable.setOrigin((textBounds.left + textBounds.width) / 2.0f, (textBounds.top + textBounds.height) / 2.0f);
    m_textDrawable.setPosition(
        (m_pos.x + m_size.x)/2,
        (m_pos.y + m_size.y)/2
    );

}

void Button::initDrawable()
{
    m_drawable[0].position = m_pos;
    m_drawable[1].position = { m_pos.x + m_size.x, m_pos.y };
    m_drawable[2].position = m_pos + m_size;
    m_drawable[3].position = { m_pos.x, m_pos.y + m_size.y }; 

    setColor(m_style->buttonColor);

    initText();
}

