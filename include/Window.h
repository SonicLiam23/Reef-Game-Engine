#pragma once
#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include "EngineTypes.h"
#include <string>
#include "EngineAPI.h"

class ENGINE_API Window
{
public:
	Window(unsigned int scale, std::string name);
	~Window();
	sf::RenderWindow* Get();

	virtual void Update(ObjectVec& objects) = 0;
	virtual Math::Vector2i ConvertScreenPointToWorldCoords(Math::Vector2i point) = 0;

protected:
	sf::RenderWindow* m_window;
	sf::Clock deltaClock;
	unsigned int m_windowScale;
	const Math::Vector2i aspect{ 16, 9 };

};

