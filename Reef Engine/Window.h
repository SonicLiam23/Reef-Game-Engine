#pragma once
#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include <string>

class Window
{
public:
	Window(unsigned int scale, std::string name);
	~Window();
	sf::RenderWindow* Get();

protected:
	sf::RenderWindow* m_window;
	sf::Clock deltaClock;
	unsigned int m_windowScale;
	const Math::Vector2i aspect{ 16, 9 };

};

