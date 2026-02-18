#include "Object.h"
#include "Script.h"
#include "SpriteUtils.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

Object::Object()
{
	m_sprite = new sf::Sprite(emptyTexture());
}

void Object::Start()
{
	for (Script*& script : m_scripts)
	{
		script->Start();
	}
}

void Object::SetTexture(const std::string& imgPath)
{
	sf::Texture& texture = SpriteUtils::GetOrLoadTexture(imgPath);
	// if texture.getSize() is a unsigned int, if the value is more than UINT_MAX I will be very very surprised.
	m_sprite->setTextureRect(sf::IntRect({ 0, 0 }, {(int)texture.getSize().x, (int)texture.getSize().y }));
	m_sprite->setTexture(texture);
}

void Object::SetPosition(Math::Vector2f newPos)
{
	m_sprite->setPosition(newPos);
}

void Object::SetSize(Math::Vector2f newSize)
{
	Math::Vector2f targetScale{};
	const sf::Vector2f size = m_sprite->getLocalBounds().size;
	targetScale.x = newSize.x / size.x;
	targetScale.y = newSize.y / size.y;

	m_sprite->setScale(targetScale);
}

Math::Vector2f Object::GetSize()
{

	//using getGlobalBounds().size would return the bounding box based on AABB collision, i want the size of the object.
	Math::Vector2f size;
	size.x = m_sprite->getScale().x * m_sprite->getLocalBounds().size.x;
	size.y = m_sprite->getScale().y * m_sprite->getLocalBounds().size.y;

	return size;
}

Math::Vector2f Object::GetPosition()
{
	return (Math::Vector2f)m_sprite->getPosition();
}

Math::Vector2f Object::GetMiddle()
{
	return (Math::Vector2f)m_sprite->getGlobalBounds().getCenter();
}

void Object::Update()
{
	for (Script*& script : m_scripts)
	{
		script->Update();
	}
}

Object::~Object()
{
	delete m_sprite;
}
