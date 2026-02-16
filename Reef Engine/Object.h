#pragma once
#include "Vector2.h"
#include "EngineTypes.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

class Object 
{
public:
	Object();
	void Update();
	void Start();

	void SetTexture(const std::string& imgPath);

	void SetPosition(Math::Vector2f newPos);
	void SetSize(Math::Vector2f newSize);
	Math::Vector2f GetPosition();

	~Object();

	// lets you draw a sprite directly
	operator sf::Sprite&() const
	{
		return *m_sprite;
	}

private:
	sf::Sprite* m_sprite;
	ScriptVec m_scripts;
};

