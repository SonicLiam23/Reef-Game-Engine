#include "SpriteUtils.h"
#include <stdexcept>

namespace
{
	using TextureMap = std::unordered_map<std::string, sf::Texture>;

	TextureMap* map;

	sf::Texture* emptyTex;
}

namespace SpriteUtils
{
	ENGINE_API void Init()
	{
		if (map)
			return;

		map = new TextureMap();

		sf::Image img;
		img.resize({ 1, 1 });
		img.setPixel({ 0,0 }, sf::Color::Transparent);

		emptyTex = new sf::Texture(img);
	}

	ENGINE_API void End()
	{
		if (!map)
			return;

		map->clear();
		delete map;
		map = nullptr;

		delete emptyTex;
		emptyTex = nullptr;
	}

	ENGINE_API sf::Texture& GetOrLoadTexture(const std::string& imagePath)
	{
		if (imagePath.empty())
			return EmptyTexture();

		auto it = map->find(imagePath);
		if (it != map->end())
			return it->second;

		sf::Texture texture;
		if (!texture.loadFromFile(imagePath))
			throw std::runtime_error("Failed to load texture");

		auto result = map->emplace(imagePath, std::move(texture));
		return result.first->second;
	}

	ENGINE_API sf::Sprite CreateSprite(const std::string& imagePath)
	{
		sf::Texture& tex = GetOrLoadTexture(imagePath);

		return sf::Sprite(tex);
	}
	ENGINE_API sf::Texture& EmptyTexture()
	{
		return *emptyTex;
	}
}