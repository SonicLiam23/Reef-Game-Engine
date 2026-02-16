#include "Object.h"
#include "Script.h"

void Object::Start()
{
	for (Script*& script : m_scripts)
	{
		script->Start();
	}
}

void Object::SetTexture(std::string imgPath)
{
	// TODO
	// add string to some map of sf::Textures
	// if i already have a texture for that string, use it
	// if not create it and use it
	// basically how i did it for my SDL2 engine
}

void Object::Update()
{
	for (Script*& script : m_scripts)
	{
		script->Update();
	}
}
