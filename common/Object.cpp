#include "Object.h"
#include "Script.h"
#include "SpriteUtils.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"

ObjectIDMap Object::objectIDMap;

Object::Object()
{

}

void Object::Start()
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
	// script starts will be ran on runtime
}

void Object::SetTexture(const std::string& imgPath)
{
	sf::Texture& texture = SpriteUtils::GetOrLoadTexture(imgPath);
	// if texture.getSize() is a unsigned int, if the value is more than UINT_MAX I will be very very surprised.
	m_sprite->setTextureRect(sf::IntRect({ 0, 0 }, { (int)texture.getSize().x, (int)texture.getSize().y }));
	m_sprite->setTexture(texture);
	m_localImgPath = imgPath;

}

void Object::SetPosition(Math::Vector2f newPos)
{
	m_rect.position = newPos;
	m_sprite->setPosition(newPos);
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
	return (Math::Vector2f)m_sprite->getGlobalBounds().getCenter();
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
	size_t ind = objectIDMap[m_id];
	objectIDMap.erase(m_id);

	while (objectIDMap.count(newID) > 0)
	{
		newID.append(" (1)");
	}
	
	m_id = newID;
	objectIDMap[newID] = ind;

}

std::string Object::GetID()
{
	return m_id;
}

bool Object::IsColliding(Math::Vector2f point)
{
	return m_sprite->getGlobalBounds().contains(point);
}

void Object::Update()
{
	for (Script* script : m_scripts)
	{
		script->Update();
	}
}

Object::~Object()
{
	delete m_sprite;
}

void Object::ApplyRectToSprite()
{
	Math::Vector2f targetScale{};
	const sf::Vector2f size = m_sprite->getLocalBounds().size;
	targetScale.x = m_rect.size.x / size.x;
	targetScale.y = m_rect.size.y / size.y;

	m_sprite->setScale(targetScale);

	m_sprite->setPosition(m_rect.position);
}
