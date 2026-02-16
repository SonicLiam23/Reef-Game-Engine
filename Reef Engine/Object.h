#pragma once
#include "EngineTypes.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

class Object
{
public:
	void Update();
	void Start();

	void SetTexture(std::string imgPath);

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	ScriptVec m_scripts;
};

