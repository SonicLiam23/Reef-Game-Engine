#include "Object.h"
#include "Script.h"
#include "SpriteUtils.h"

Object::Object()
{

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

	if (!m_sprite)
	{
		m_sprite = new sf::Sprite(texture);
		return;
	}
		
	m_sprite->setTexture(texture);
}

void Object::SetPosition(Math::Vector2f newPos)
{
	m_sprite->setPosition(newPos);
}

void Object::SetSize(Math::Vector2f newSize)
{
	m_sprite->setScale(newSize);
}

Math::Vector2f Object::GetPosition()
{
	return (Math::Vector2f)m_sprite->getPosition();
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
