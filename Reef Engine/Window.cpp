#include "Window.h"
#include "Vector2.h"

Window::Window(Math::Vector2u size, std::string name) 
{
	m_window = new sf::RenderWindow(sf::VideoMode(size), name, sf::Style::Titlebar | sf::Style::Close);
}

Window::~Window()
{
	delete m_window;
}

sf::RenderWindow* Window::Get()
{
	return m_window;
}
