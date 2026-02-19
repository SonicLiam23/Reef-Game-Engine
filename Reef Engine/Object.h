#pragma once
#include "Vector2.h"
#include "Rect.h"
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
	Math::Vector2f GetSize();
	Math::Vector2f GetPosition();
	Math::Vector2f GetMiddle();
	Math::Rect GetRect();

	bool IsColliding(Math::Vector2f point);

	~Object();

	// lets you draw a sprite directly
	operator sf::Sprite&() const
	{
		return *m_sprite;
	}


private:
	sf::Sprite* m_sprite;
	ScriptVec m_scripts;

	// object initialized with an empty sprite, but a sprite needs a texture
	inline static sf::Texture& emptyTexture()
	{
		static sf::Image image;
		image.resize({ 1, 1 });
		image.setPixel({ 0, 0 }, sf::Color::Transparent);
		static sf::Texture emptyTex(image);
		return emptyTex;
	}
};

