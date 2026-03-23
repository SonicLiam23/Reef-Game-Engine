#include "Window.h"
#include "Vector2.h"
#include "Object.h"

Window::Window(unsigned int scale, std::string name) : m_window(nullptr), m_windowScale(scale), m_localViewCenter(0, 0), m_realViewCenter(&m_localViewCenter)
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

void Window::SetCameraPosition(Math::Vector2f newPosition)
{
	m_localViewCenter = newPosition;
	m_realViewCenter = &m_localViewCenter;
}

void Window::SetCameraPosition(Object* obj)
{
	m_localViewCenter = obj->GetPosition();
	m_realViewCenter = &m_localViewCenter;
}

void Window::AttachCameraToObject(Object* obj)
{

	m_realViewCenter = (const Math::Vector2f*)&obj->GetPositionByPtr();
}

const Math::Vector2f Window::GetCameraPosition() const
{
	return *m_realViewCenter;
}
