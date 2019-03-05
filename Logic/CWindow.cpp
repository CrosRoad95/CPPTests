#include "StdInc.h"

sf::RenderWindow* g_pWindow;

void Create(const char* strName, uint width, uint heigth)
{
	// Request a 24-bits depth buffer when creating the window
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;

	sf::RenderWindow* pWindow = new sf::RenderWindow(sf::VideoMode(width, heigth), strName, sf::Style::Default, contextSettings);
	g_pWindow = pWindow;
	
	// Make it the active window for OpenGL calls
	pWindow->setActive();
	pWindow->setFramerateLimit(pGame->GetFrameLimit());

	// Set the color and depth clear values
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	//glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	// Configure the viewport (the same size as the window)
	glViewport(0, 0, pWindow->getSize().x, pWindow->getSize().y);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = static_cast<float>(pWindow->getSize().x) / pWindow->getSize().y;
	glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 6000.f);

	bool rotate = true;
	sf::Clock Clock;
	sf::Event event;

	pGame->GetWindow()->SetWindow(pWindow);

	CTexture::InitializeDefault();

	// in seconds, miliseconds after the comma
	Position3D pCameraPosition, pCameraLookAt;
	float fElapsedTime;
	while (pWindow->isOpen())
	{
		fElapsedTime = Clock.getElapsedTime().asMilliseconds();
		pGame->SetElapsedTime(fElapsedTime);
		while (pWindow->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				pWindow->close();
				break;
			case sf::Event::MouseMoved:
				//offsetX = pWindow->getSize().x / 2 - event.mouseMove.x;
				//offsetY = pWindow->getSize().y / 2 - event.mouseMove.y;
				//sf::Mouse::setPosition(sf::Vector2i(pWindow->getSize().x/2, pWindow->getSize().y/2), *pWindow);
				break;
			case sf::Event::KeyPressed:
				break;
			case sf::Event::Resized:
				glViewport(0, 0, event.size.width, event.size.height);
				printf("Resized\n");
				break;

			default:
				break;
			}
		}
		pWindow->clear(sf::Color(0, 0, 0, 255));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		pGame->GetCamera()->DoPulse();

		pGame->StaticDoPulse();
		pWindow->display();
	}
}

CWindow::CWindow(const char* strName, uint width, uint heigth) :
	m_cName(strName)
{
	std::thread(&Create, strName, width, heigth).detach();
}

void CWindow::CenterMouse()
{
	sf::Vector2u size = GetSize();
	sf::Vector2i position = GetPosition();
	sf::Mouse::setPosition(sf::Vector2i( position.x + size.x / 2, position.y + size.y / 2));
}