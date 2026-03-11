#pragma once
#include "Vector2.h"
#include "Rect.h"
#include "EngineTypes.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "json.hpp"
#include "EngineAPI.h"
#include "Script.h"
#include "SerializableFactory.h"


class ENGINE_API Object : public sf::Drawable
{
public:

	Object();
	void Update();
	void Init();
	void Start();

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
	void Destroy();
	bool MarkedForDeletion();
	void AddScript(ScriptUPtr script);
	void RemoveScript(int ind);
	ScriptVec& GetScripts();


	// public as i was going to add a Get and Set, with no extra validation
	std::string name;
	static ObjectIDMap& GetIDMap();

	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;

	Object(Object&&) = default;
	Object& operator=(Object&&) = default;
	

	~Object();

private:

	/// <summary>
	/// sf::sprite uses scale, m_rect uses pixel size. Calculate the "scale" from the pixel size and apply it.
	/// </summary>
	void ApplyRectToSprite();

	sf::Sprite m_sprite;
	ScriptVec m_scripts;
	std::string m_localImgPath;
	Math::Rect m_rect;
	std::string m_id;
	bool m_markedForDeletion;
	
	inline void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(m_sprite, states);
	}

	friend void to_json(nlohmann::json& j, const Object& obj);
	friend void from_json(const nlohmann::json& j, Object& obj);

};

void to_json(nlohmann::json& j, const Object& obj);
void from_json(const nlohmann::json& j, Object& obj);