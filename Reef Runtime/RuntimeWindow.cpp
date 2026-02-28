#include "RuntimeWindow.h"
#include "RuntimeEngine.h"
#include "SFML/Graphics.hpp"
#include "Object.h"

void RuntimeWindow::Start(RuntimeEngine* engine)
{
	m_attachedEngine = engine;

	m_window->setFramerateLimit(60);

}

void RuntimeWindow::Update(ObjectVec& objects)
{
	while (std::optional<sf::Event> eventOpt = m_window->pollEvent())
	{
		const sf::Event& event = *eventOpt;

		if (event.is<sf::Event::Closed>())
		{
			m_attachedEngine->End();
			m_window->close();
		}
	}

	m_window->clear();
	for (ObjectUPtr& obj : objects)
	{
		m_window->draw(*obj.get());
	}
	m_window->display();
}
