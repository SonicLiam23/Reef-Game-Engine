#pragma once
#include "Vector2.h"
#include "Rect.h"
#include "EngineTypes.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "json.hpp"

class EditorEngine;

class Object 
{
public:
	Object();
	void Update();
	void Start();

	static ObjectIDMap objectIDMap;

	void SetTexture(const std::string& imgPath);
	void SetPosition(Math::Vector2f newPos);
	void SetSize(Math::Vector2f newSize);
	Math::Vector2f GetSize();
	Math::Vector2f GetPosition();
	Math::Vector2f GetMiddle();
	Math::Rect GetRect();
	std::string GetImagePath();
	bool IsColliding(Math::Vector2f point);
	void SetID(std::string newID);
	std::string GetID();


	// public as i was going to add a Get and Set, with no extra validation
	std::string name;
	

	

	~Object();

	// lets you draw a sprite directly, it's lazy but works :D
	operator sf::Sprite&() const
	{
		return *m_sprite;
	}


private:
	/// <summary>
	/// sf::sprite uses scale, m_rect uses pixel size. Calculate the "scale" from the pixel size and apply it.
	/// </summary>
	void ApplyRectToSprite();

	sf::Sprite* m_sprite;
	ScriptVec m_scripts;
	std::string m_localImgPath;
	Math::Rect m_rect;
	std::string m_id;
	


	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Object, name, m_id, m_rect, m_localImgPath);
};

