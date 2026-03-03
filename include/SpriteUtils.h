#pragma once
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include "EngineAPI.h"

namespace SpriteUtils
{
	ENGINE_API void Init();
	ENGINE_API void End();

	ENGINE_API sf::Texture& GetOrLoadTexture(const std::string& path);
	ENGINE_API sf::Sprite CreateSprite(const std::string& imagePath);
	ENGINE_API sf::Texture& EmptyTexture();
};
