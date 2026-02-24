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
	// sprite needs a texture
	inline static sf::Texture& emptyTexture()
	{
		static sf::Image image;
		image.resize({ 1, 1 });
		image.setPixel({ 0, 0 }, sf::Color::Transparent);
		static sf::Texture emptyTex(image);
		return emptyTex;
	}

	inline sf::Texture& GetOrLoadTexture(const std::string& imagePath)
	{
		if (imagePath.empty())
		{
			return emptyTexture();
		}

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

	/// <summary>
	/// UNSAFE: CALLS NEW, REMEMBER TO DELETE!!!!!!!!!!!!!!!
	/// </summary>
	/// <param name="imagePath"></param>
	/// <returns></returns>
	inline sf::Sprite* CreateSprite(const std::string& imagePath)
	{
		sf::Texture& tex = GetOrLoadTexture(imagePath);

		return new sf::Sprite(tex);
	}


}

