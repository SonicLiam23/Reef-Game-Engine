#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>

namespace 
{
	using TextureMap = std::unordered_map<std::string, sf::Texture>;

	inline TextureMap& GetMap()
	{
		static TextureMap map;
		return map;
	}


}

namespace SpriteUtils
{
	inline sf::Texture& GetOrLoadTexture(const std::string& imagePath)
	{
		if (GetMap().find(imagePath) == GetMap().end())
		{
			sf::Texture texture;
			if (!texture.loadFromFile(imagePath))
			{
				throw std::runtime_error("Failed to load texture");
			}
			GetMap()[imagePath] = texture;
		}

		return GetMap()[imagePath];
	}

	inline sf::Sprite CreateSprite(const std::string& imagePath)
	{
		GetOrLoadTexture(imagePath);

		return sf::Sprite(GetMap()[imagePath]);
	}
}

