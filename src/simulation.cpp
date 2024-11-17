#include "simulation.hpp"

Simulation::Simulation(const size_t particlesNum, const size_t screenWidth, const size_t screenHeight, const float fps) :
    m_fps(fps), m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_physicsWorld(particlesNum, 8), m_particlesNum(particlesNum),
    m_renderer(m_particlesNum, screenWidth, screenHeight)
{
    m_currContext = RENDER_CONTEXT::BUTTONS_CONTEXT;

    if (!loadFont("../font/Minecraft.ttf")) {
        std::cout << "You are gay" << std::endl;
    }

        m_baseButtonStyle = {
            sf::Color::White, // Button color
            sf::Color::Magenta, // outline color
            sf::Color::Magenta, // onHoverButtonColor
            sf::Color::Magenta, // onClickButtonColor
            sf::Color::Black, // textColor
            sf::Color::White, // onHoverTextColor
            sf::Color::Black, // onClickTextColor
            15, // character size
            3.0f, // outline thickness 
            &m_font, // font
        };

    const float margin = 20.0f;
    const sf::Vector2f btnPos = { margin, static_cast<float>(m_screenHeight / 2) };
    const float spaceBetweenButtons = 50.0f;
    const sf::Vector2f addictiveFactor = { static_cast<float>(m_screenWidth / 3) + spaceBetweenButtons, 0.0f };

    const sf::Vector2f btnSize = { 400.0f, 200.0f };

    m_buttonStyles[0] = RectangleButtonStyle(m_baseButtonStyle);
    m_buttonStyles[1] = CircleButtonStyle(m_baseButtonStyle);
    m_buttonStyles[2] = ParabolaButtonStyle(m_baseButtonStyle);

    for (size_t i = 0; i < 3; ++i) {
        m_buttons[i] = { btnPos + addictiveFactor * static_cast<float>(i), btnSize, &m_buttonStyles[i]};
    }
    
    for (size_t i = 0; i < 3; ++i) {
        m_renderer.setButtonDrawable(&m_buttons[i], i);
    }
}

Simulation::~Simulation()
{
    delete m_worldShape;
}


void Simulation::run()
{
    const float dt = static_cast<float>(1 / m_fps);
    const size_t spawnSize = 1;

    while (m_renderer.windowIsOpen()) { 

        processEvents();
        
        if (m_currContext == RENDER_CONTEXT::SIMULATION_CONTEXT) { // TODO: Riprogettare sta logica - fa schifo

            if (m_physicsWorld.getParticles().size() < m_particlesNum) {

                for (size_t i = 0; i < spawnSize; ++i) {
                    m_physicsWorld.addParticle(m_particlesColor, m_worldShape->getParticleSpawnPos(i));
                }
            }

            m_physicsWorld.update(dt);
        }

        m_renderer.render(m_currContext);
    }
}



void Simulation::initWSDependencies(const ws::SHAPE_TYPE worldShapeType)
{
    switch (static_cast<unsigned int>(worldShapeType)) {
        case 0: {
            m_worldShape = new ws::WorldRect({ 50.0f, 50.0f }, { 500.0f, 500.0f});
            break;
        }
        case 1: {
            const sf::Vector2f center(300.0f, 150.0f);
            m_worldShape = new ws::WorldCircle(center, 300.0f);;
            break;
        }
        case 2: {
            m_worldShape = new ws::WorldParabola();
            break;
        }
    }
    initWSDependency(m_worldShape);
}

void Simulation::initWSDependency(const ws::WorldShape* worldShape)
{
    m_physicsWorld.setShape(worldShape);
    m_renderer.setWorldShapeDrawable(worldShape);
}


void Simulation::initSimulationText()
{
    m_text.setFillColor(sf::Color::White);
    m_text.setFont(m_font);
    m_text.setCharacterSize(15);
    m_text.setPosition(50, 50);
    // aggiungere stringa del testo
}


void Simulation::processEvents()
{
    sf::Event e;
    while (m_renderer.pollEvent(e)) {
        switch (e.type) {
            case sf::Event::Closed:
                m_renderer.closeWindow();
                break;
            case sf::Keyboard::Escape:
                m_renderer.closeWindow();
                break;
            default: {
                const sf::Vector2i mousePos = m_renderer.getMouseCoords();
                if (!Button::s_render) return;
                for (size_t i = 0; i < m_buttons.size(); ++i) {

                    if (m_buttons[i].listen(e.type, mousePos)) {

                        initWSDependencies(m_buttons[i].getShapeType());

                        m_currContext = RENDER_CONTEXT::SIMULATION_CONTEXT;

                        m_renderer.setPhysicsWorld(&m_physicsWorld);

                        initSimulationText();
                        m_renderer.setTextDrawable(&m_text);
                        break;
                    }
                }
            }

        }
    }
}

bool Simulation::loadFont(const std::string& path)
{
    return m_font.loadFromFile(path);
}

const sf::Vector2u& Simulation::getSize() const
{
    return { static_cast<unsigned int>(m_screenWidth), static_cast<unsigned int>(m_screenHeight)};
}
