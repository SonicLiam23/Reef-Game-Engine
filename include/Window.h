#pragma once
class Object;
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
	void SetCameraPosition(Math::Vector2f newPosition);
	void SetCameraPosition(Object* obj);
	void AttachCameraToObject(Object* obj);
	const Math::Vector2f GetCameraPosition() const;

	virtual void Update(ObjectVec& objects) = 0;
	virtual Math::Vector2i ConvertScreenPointToWorldCoords(Math::Vector2i point) = 0;

protected:
	sf::RenderWindow* m_window;
	sf::Clock deltaClock;
	unsigned int m_windowScale;
	const Math::Vector2i aspect{ 16, 9 };
	sf::View m_view;
	// points to the view centre, whether it be the local one stored or the middle of an object, so that when the camera moves, the view center is updated to match
	const Math::Vector2f* m_realViewCenter;
	Math::Vector2f m_localViewCenter;
};

