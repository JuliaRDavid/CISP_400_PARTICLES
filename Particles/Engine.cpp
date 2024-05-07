#include "Engine.h"

Engine::Engine()
{
	m_Window.create(VideoMode::getDesktopMode(), "Particles!", Style::Default);
}

void Engine::run()
{
	Clock ttpf;
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		ttpf.restart();
		Time sec = ttpf.getElapsedTime();

		input();
		update(sec.asSeconds());
		draw();
	}
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) m_Window.close();
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				for (int i = 0; i < 5; i++)
				{
					Particle p(m_Window, rand() % 25 + 25, Mouse::getPosition(m_Window));
					m_particles.push_back(p);
				}

			}
		}
	}

}

void Engine::update(float dtAsSeconds)
{

}

void Engine::draw()
{

}