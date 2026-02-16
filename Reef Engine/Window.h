#pragma once
#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include <string>

class Window
{
public:
	Window(Math::Vector2u size, std::string name);
	~Window();
	sf::RenderWindow* Get();

protected:
	sf::RenderWindow* m_window;
	sf::Clock deltaClock;

};

