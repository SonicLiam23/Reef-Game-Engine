#include "Object.h"
#include "SpriteUtils.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SerializableFactory.h"


Object::Object() :  m_sprite(SpriteUtils::EmptyTexture()), m_markedForDeletion(false)
{
}

void Object::Init()
{
	m_sprite = SpriteUtils::CreateSprite(m_localImgPath);

	if (m_rect.size.IsZero())
	{
		m_rect.size = { 64, 64 };
	}
	if (name.empty())
	{
		name = "NO_NAME";
	}

	ApplyRectToSprite();

	// if user edits save file so 2 objects have the same ID, ensure its overridden
	SetID(m_id);
}

void Object::Start()
{
	for (ScriptUPtr& script : m_scripts)
	{
		script->Start();
	}
}

void Object::SetTexture(const std::string& imgPath)
{
	sf::Texture& texture = SpriteUtils::GetOrLoadTexture(imgPath);
	// if texture.getSize() is a unsigned int, if the value is more than UINT_MAX I will be very very surprised.
	m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { (int)texture.getSize().x, (int)texture.getSize().y }));
	m_sprite.setTexture(texture);
	m_localImgPath = imgPath;

}

void Object::SetPosition(Math::Vector2f newPos)
{
	m_rect.position = newPos;
	m_sprite.setPosition(newPos);
}

void Object::SetSize(Math::Vector2f newSize)
{
	m_rect.size = newSize;
	ApplyRectToSprite();
}

Math::Vector2f Object::GetSize()
{
	return m_rect.size;
}

Math::Vector2f Object::GetPosition()
{
	return m_rect.position;
}

Math::Vector2f Object::GetMiddle()
{
	return (Math::Vector2f)m_sprite.getGlobalBounds().getCenter();
}

Math::Rect Object::GetRect()
{
	return m_rect;
}

std::string Object::GetImagePath()
{
	return m_localImgPath;
}

void Object::SetID(std::string newID)
{
	std::string temp = newID;
	int count = 1;

	while (GetIDMap().find(temp) != GetIDMap().end())
	{
		temp = newID + std::to_string(count);
		++count;
	}

	newID = temp;

	size_t ind = GetIDMap()[m_id];
	GetIDMap().erase(m_id);

	m_id = newID;
	GetIDMap()[newID] = ind;
}

std::string Object::GetID()
{
	return m_id;
}

void Object::Destroy()
{
	m_markedForDeletion = true;
}

bool Object::MarkedForDeletion()
{
	return m_markedForDeletion;
}

void Object::AddScript(ScriptUPtr script)
{
	m_scripts.push_back(std::move(script));
}

void Object::RemoveScript(int ind)
{
	if (ind != m_scripts.size())
	{
		// swapping with the back
		std::swap(m_scripts[ind], m_scripts.back());
		m_scripts.pop_back();
	}
}

ScriptVec& Object::GetScripts()
{
	return m_scripts;
}

bool Object::IsColliding(Math::Vector2f point)
{
	return m_sprite.getGlobalBounds().contains(point);
}

void Object::Update()
{
	for (ScriptUPtr& script : m_scripts)
	{
		script->Update();
	}
}

ObjectIDMap& Object::GetIDMap()
{
	static ObjectIDMap IDMap;
	return IDMap;
}

Object::~Object() = default;

void Object::ApplyRectToSprite()
{
	Math::Vector2f targetScale{};
	const sf::Vector2f size = m_sprite.getLocalBounds().size;
	targetScale.x = m_rect.size.x / size.x;
	targetScale.y = m_rect.size.y / size.y;

	m_sprite.setScale(targetScale);

	m_sprite.setPosition(m_rect.position);
}

void to_json(nlohmann::json& j, const Object& obj)
{
	j["m_id"] = obj.m_id;
	j["m_localImgPath"] = obj.m_localImgPath;
	j["m_rect"] = obj.m_rect;
	j["name"] = obj.name;

	j["m_scripts"] = nlohmann::json::array();

	for (const ScriptUPtr& scriptPtr : obj.m_scripts)
	{
		nlohmann::json entry;
		entry["type"] = scriptPtr->GetTypeName();
		entry["data"] = scriptPtr->Serialize();

		j["m_scripts"].push_back(entry);
	}
}

void from_json(const nlohmann::json& j, Object& obj)
{
	obj.m_id = j.value("m_id", obj.m_id);
	obj.m_localImgPath = j.value("m_localImgPath", obj.m_localImgPath);
	if (j.contains("m_rect"))
		j.at("m_rect").get_to(obj.m_rect);
	obj.name = j.value("name", obj.name);

	obj.m_scripts.clear();

	if (j.contains("m_scripts"))
	{
		for (const auto& entry : j["m_scripts"])
		{
			if (!entry.contains("type") || !entry.contains("data"))
				continue;

			std::string type = entry.at("type").get<std::string>();

			auto script = SerializableFactory::Get().Create(type);
			if (!script)
				continue; // or throw

			script->Deserialize(entry.at("data"));

			obj.m_scripts.push_back(std::move(script));
			obj.m_scripts.back()->AttachedObject = &obj;
			obj.m_scripts.back()->REEF_ENGINE_INIT();
		}
	}
}

