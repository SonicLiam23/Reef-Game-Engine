#include "Window.h"
#include "Vector2.h"

Window::Window(unsigned int scale, std::string name) 
{
	m_window = new sf::RenderWindow(sf::VideoMode({scale * aspect.x, scale * aspect.y}), name, sf::Style::Titlebar | sf::Style::Close);
}

Window::~Window()
{
	delete m_window;
}

sf::RenderWindow* Window::Get()
{
	return m_window;
}
